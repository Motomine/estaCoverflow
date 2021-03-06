/*
 ============================================================================
 Name        : UMV.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "functions.h"
#include "func_consola.h"

sem_t yaEscribio;
sem_t mutexOpera;

int main(int argc, char** argv){

 	logs = log_create("log","UMV.c",0,LOG_LEVEL_TRACE);

	if (argc < 2){
		log_error(logs, "No se envio ningun parametro");
		log_destroy(logs);
		return 0;
	}
	config = config_create(argv[1]);

	if(!archivo_config_valido()){
		log_error(logs,"El archivo de configuracion no tiene todos los campos necesarios");
		log_destroy(logs);
		config_destroy(config);
		return 0;
	}
	inicializar_var_config();
	inicializar_umv(tamanioUMV);
	log_debug(logs,"Se creo la umv");

	sem_init(&yaEscribio,0,0);
	sem_init(&mutexOpera,0,1);

	int termina = 0;
	int socket;
	t_length* tam = malloc(sizeof(t_length));
	int s = crearServidor(puerto, logs);
	if(s == -1){
		log_error(logs,"No se creo el servidor");
		return 0;
	}
	else
		log_info(logs,"Se creo el servidor");

	do{
		socket = aceptarConexion(s, logs);
		if(!socket){
			log_error(logs,"[MAIN KERNEL]Error al aceptar la conexion");
			log_destroy(logs);
			return 0;
		}else
			log_info(logs,"[MAIN KERNEL]Se acepto la conexion");

		if(!recibirMenu(socket, tam, logs)){
			log_error(logs, "[MAIN KERNEL]Error al hacer el handshake: KERNEL");
			termina = 1;
		}else{
			if (tam->menu == SOY_KERNEL){

				log_debug(logs,"Levanto el hilo: Consola");
				pthread_create(&pthread_consola, NULL, (void*)manejo_consola, NULL);

				log_debug(logs,"[MAIN KERNEL]Se conecto: Kernel");
				pthread_create(&pthread_kernel, NULL, (void*)funcion_kernel, (void*)socket);
			}else
				log_error(logs, "[MAIN KERNEL]Se esta esperando la conexion del kernel");
		}
		if(termina)
			break;
	}while(tam->menu != SOY_KERNEL);

	while(1){
		if(termina)
			break;

		socket = aceptarConexion(s, logs);
		if(!socket)
			log_error(logs,"[MAIN CPU] Error al aceptar la conexion");
		else
			log_info(logs,"[MAIN CPU] Se acepto la conexion");

		if(!recibirMenu(socket, tam, logs))
			log_error(logs, "[MAIN CPU] Error al hacer el handshake: CPU");
		else{
			if (tam->menu == SOY_CPU){
				log_debug(logs,"[MAIN CPU] Se conecto: CPU");
				pthread_create(&pthread_CPU, NULL, (void*)funcion_CPU, (void*)socket);
			}else{
				log_error(logs, "[MAIN CPU] Error en handshake: NO ES CPU");
			}
		}
	}
	pthread_join(pthread_consola,NULL);
	pthread_join(pthread_kernel,NULL);
	log_destroy(logs);
	config_destroy(config);
	return 0;
}
