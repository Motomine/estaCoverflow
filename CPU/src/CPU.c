/*
 ============================================================================
 Name        : CPU.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "globales.h"
#include "functions.h"
#include "funcionesParser.h"

int main(int argc, char** argv){

	logs = log_create("log", "CPU.c", 1, LOG_LEVEL_TRACE);

/*	if (argc < 2){
		log_error(logs, "No se pasaron parametros.");
		log_destroy(logs);
		return 0;
	}*/

	//config = config_create(argv[1]);
	config = config_create("config");
	diccionarioDeVariables = dictionary_create();
	tam = malloc(sizeof(t_length));

	if (!archivo_de_configuracion_valido()){
		log_error(logs, "El archivo de configuracion no tiene todos los campos necesarios");
		liberar_estructuras();
		return 0;
	}

	socketUMV = conectar_UMV();
	socketKernel = conectar_kernel();
	if(socketKernel < 0 || socketUMV < 0){
		log_error(logs, "El programa tuvo que finalizar insatisfactoriamente porque fallo alguna conexion");
		liberar_estructuras();
		return 0;
	}
	tam->menu = SOY_CPU;
	enviarMenu(socketUMV, tam, logs);

	int quantum = recibir(1);
	tamanioStack = recibir(2);
	int retardo = recibir(3);

	inicializar_funciones_parser();
	diccionarioDeVariables = dictionary_create();

	int pc;
	seguir = 1;

	signal(SIGUSR1, manejar_senial);
	pcb = malloc(sizeof(registroPCB));
	while (seguir){
		int cont = 0;
		ejecutando = 0;
		log_debug(logs, "Recibiendo un PCB...");
		if(!recibirDatos(socketKernel, tam, (void*)pcb, logs)){
			log_error(logs, "Se produjo un error al recibir el PCB del kernel");
			break;
		}
		tam->menu = PID_ACTUAL;
		tam->length = sizeof(int);
		log_debug(logs, "Enviando el pid %d a la UMV", pcb->pid);
		if(!enviarDatos(socketUMV, tam, &pcb->pid, logs))
			log_error(logs, "Se produjo un error enviando el pid a la UMV");

		pedir_stack();
		cargar_diccionario();

		systemCall = false;
		ejecutando = 1; //Si se llama la senial SIGUSR1 espera a que concluya el quantum
		while (quantum > cont && !systemCall){
			pc = pcb->program_counter;
			sleep(2);
			char* sentencia = recibir_sentencia();
			analizadorLinea(strdup(sentencia), &functions, &kernel_functions);

			if (pc == pcb->program_counter)
				pcb->program_counter++;
			cont++;
			log_debug(logs, "Concluyo el quantum %d\n\n\n", cont);
			sleep(retardo/1000);
		}
		if (!systemCall){
			tam->menu = CONCLUYO_UN_QUANTUM;
			tam->length = sizeof(registroPCB);
			if (!enviarDatos(socketKernel, tam, pcb, logs))
				log_error(logs, "Se produjo un error al notificar al pcp que concluyo un quantum.");
			retorno_de_stack();
		}


		if (signalCall){
			cerrarSocket(socketKernel);
			cerrarSocket(socketUMV);
		}
		dictionary_clean(diccionarioDeVariables);
	}

	liberar_estructuras();

	return 0;
}
