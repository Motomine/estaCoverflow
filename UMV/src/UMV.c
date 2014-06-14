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
#include "testeo.h"

void *consola();


int main(int argc, char** argv){
	logs = log_create("log","UMV.c",1,LOG_LEVEL_TRACE);
	/*if (argc < 2){
		log_error(logs, "No se envio ningun parametro");
		log_destroy(logs);
		return 0;
	}*/
	config = config_create("config");
	if(!archivo_config_valido()){
		log_error(logs,"Error en los parametros. Aborta el programa");
		log_destroy(logs);
		config_destroy(config);
	}
	inicializar_var_config();
	inicializar_umv(tamanioUMV);
	log_info(logs,"Se inicializo la umv");

	test_crea_elimina_UMV();

	eliminarUMV();
	log_destroy(logs);
	config_destroy(config);
	return 0;
}


void *consola(){
	int pid, cambioAlgoritmo ,nroOp, operacion, retardoNuevo;

	printf("Seleccione la operación segun...\n");
	printf("OPERACION = 1\n");
	printf("RETARDO = 2\n");
	printf("ALGORITMO = 3\n");
	printf("COMPACTACION = 4\n");
	printf("DUMP = 5\n");
	printf("Operacion solicitada: ");
	scanf("%d",&operacion);

	switch(operacion){
		case CAMBIO_PROCESO_ACTIVO:
			printf("Ingrese nuevo pid: ");
			scanf("%d",&pid);
			cambio_proceso_activo(pid);
			break;
		case OPERACION:
			printf("Ingrese operacion segun...");
			printf("LEER_SEGMENTO = 1\n");
			printf("ESCRIBIR_SEGMENTO = 2\n");
			printf("CREAR_SEGMENTO = 3\n");
			printf("ELIMINAR_SEGMENTOS = 4\n");
			printf("Ingrese operacion: ");
			scanf("%d",&nroOp);
			ejec_operacion(nroOp);

			break;
		case CAMBIAR_RETARDO:
			printf("Ingrese nuevo retardo: ");
			scanf("%d",&retardoNuevo);
			cambiar_retardo(retardoNuevo);
			break;
		case CAMBIAR_ALGORITMO:
			printf("Ingrese opcion segun...");
			printf("FIRST_FIT = 0\n");
			printf("WORST_FIT = 1\n");
			printf("Opcion:  ");
			scanf("%d",&cambioAlgoritmo);
			cambiarAlgoritmo(cambioAlgoritmo);
			break;
		case DUMP:
			dump();
			break;
	}
	return NULL;
}
