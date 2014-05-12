/*
 ============================================================================
 Name        : kernel.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <commons/collections/queue.h>
#include <commons/collections/list.h>
#include <parser/metadata_program.h>
#include <commons/config.h>
#include <commons/log.h>
#include <pthread.h>
#include <libs/sockets.h>

//ESTRUCTURAS

typedef struct {
	t_medatada_program medatadaprogram;
	int peso;
} t_medatada_program_con_prioridad;
typedef struct{
	t_log *logs;
	t_config *config;
	int socket_conectado;
	int bytesRecibidos;
	char buffer[1024 ];
	int error;
	t_medatada_program programa;
}PLP;

//DECLARACION DE FUNCIONES
//void manejar_cola_ready (t_list *colaReady , t_medatada_program programaNuevo);
//int calcular_peso(t_medatada_program programa);
//t_medatada_program_con_prioridad obtener_programa_con_peso(t_medatada_program programaNuevo, t_medatada_program_con_prioridad programaConPeso);
void *programador_largo_plazo(void* auxPLP);
//bool comparador (void *, void *);
void *programador_corto_plazo(void*);

//FUNCION PRINCIPAL


int main() {

	t_log *logs = log_create("log", "kernel.c", 0, LOG_LEVEL_TRACE);
	t_config *config = config_create("config.cnf");
	int port = config_get_int_value(config, "PUERTO_PROGRAM");
	int socket_conectado = crearServidor(port, logs);
	pthread_t thr1;//, thr2;
	PLP auxPLP;
//		char *PCP = "PCP";
	int  r1;//, r2;

	if(socket_conectado < 0 ){
		log_error(logs, "El servidor no se creo correctamente");
		perror("El proceso no se realizo correctamente.");
		config_destroy(config);
		log_destroy(logs);

	}else{
		r1 = pthread_create( &thr1, NULL, programador_largo_plazo, (void*) &auxPLP);
//		r2 = pthread_create( &thr2, NULL, programador_corto_plazo, (void*) PCP);};


	};
	return 0;
};


/*
//FUNCIONES AUXILIARES
void manejar_cola_new(){
	t_queue *colaNew;
	t_list *colaReady;
	t_medatada_program programaNuevo;
	colaNew = queue_create();
	colaReady = list_create();
	queue_push(colaNew , &programaNuevo);//ingresa un nuevo programa
	//el plp manda señal
	queue_pop(colaNew);
	manejar_cola_ready(colaReady , programaNuevo);//el plp manda señal
};
t_medatada_program_con_prioridad obtener_programa_con_peso(t_medatada_program programaNuevo,t_medatada_program_con_prioridad programaConPeso){
	programaConPeso.peso = calcular_peso(programaNuevo);
	programaConPeso.medatadaprogram.instruccion_inicio = programaNuevo.instruccion_inicio;
    programaConPeso.medatadaprogram.instrucciones_size = programaNuevo.instrucciones_size;
    programaConPeso.medatadaprogram.instrucciones_serializado = programaNuevo.instrucciones_serializado;
	programaConPeso.medatadaprogram.etiquetas_size = programaNuevo.etiquetas_size;
	programaConPeso.medatadaprogram.etiquetas = programaNuevo.etiquetas;
	programaConPeso.medatadaprogram.cantidad_de_funciones = programaNuevo.cantidad_de_funciones;
	programaConPeso.medatadaprogram.cantidad_de_etiquetas = programaNuevo.cantidad_de_etiquetas;
	return (programaConPeso);
};
int calcular_peso(t_medatada_program programa)
		{int peso;
		peso=(5 * programa.cantidad_de_funciones) + (3 * programa.cantidad_de_etiquetas)+programa.instrucciones_size;
	return(peso);};
void manejar_cola_ready(t_list *colaReady,t_medatada_program programaNuevo){
	t_medatada_program_con_prioridad programaConPeso;//entra el archivo
	programaConPeso = obtener_programa_con_peso(programaNuevo, programaConPeso);
	list_add(colaReady ,&programaConPeso);
	list_sort(colaReady, comparador);//ordeno la lista
};
bool comparador (void *uno, void *dos){
	t_medatada_program_con_prioridad *aux1, *aux2;
	aux1 = (t_medatada_program_con_prioridad*) uno;
	aux2 = (t_medatada_program_con_prioridad*) dos;
	if ((aux1->peso) > (aux2->peso))
		return 1;
	else
		return 0;
	return 0;
};
void* programador_largo_plazo (void *auxPLP){
	PLP *varPLP = (PLP*) auxPLP;
	while (1){
		varPLP->bytesRecibidos = recv(varPLP->socket_conectado, varPLP->buffer, 1024, 0); //buffer es la variable que recibe
		if(varPLP->bytesRecibidos >= 0){
			printf("Recibio: %s\n", varPLP->buffer);
			if (memcmp(varPLP->buffer, "fin", varPLP->bytesRecibidos) == 0){
				varPLP->error = 0;
				break;
			}
		}else{
			printf("Hubo un error");
			varPLP->error = 0;
		}
		varPLP-> error = 1;
	//	crearNuevoPCB()
		manejar_cola_new();
	};
	return auxPLP;
};

*/
