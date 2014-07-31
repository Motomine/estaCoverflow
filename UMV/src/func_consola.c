/*
 * func_consola.c
 *
 *  Created on: 30/07/2014
 *      Author: utnso
 */

#include "func_consola.h"


int cadenaEntera(char s[]) {
	int n = strlen(s);
	int ret = 0;
	int i;
	for (i = 0; s[i] != '\0'; i++) {
		ret += 10 ^ (n - i - 1) * (s[i] - '0');
	}
	return (ret);
}
char *crearSegmentoPorConsola(char **operacion) {
	uint32_t pid = atoi(operacion[3]);
	uint32_t tamSeg = atoi(operacion[4]);

	uint32_t base = crear_agregar_segmento(pid, tamSeg);

	char* publicacion = string_from_format(
			"Se creo segmento del programa: %d con inicio %d y tamaño %d \n",
			pid, base, tamSeg);

	return publicacion;
}

char* destruirSegmentosPorConsola(char** operacion) {
	uint32_t pid = atoi(operacion[3]);

	destruir_segmentos(pid);
	char* publicacion = string_from_format(
			"Se destruyeron todos los segmentos del programa %d\n", pid);

	return publicacion;
}

char *solicitarBytesPorConsola(char **operacion) {
	uint32_t pid = atoi(operacion[3]);
	uint32_t base = atoi(operacion[4]);
	uint32_t offset = atoi(operacion[5]);
	uint32_t tamSeg = atoi(operacion[6]);

	unsigned char *buffer = leer_segmento(base, tamSeg, offset, pid);

	char* publicacion = string_from_format(
			"La informacion solicitada es : %s \n", buffer);

	return publicacion;
}

char* retornarBufferPedido(char **operacion,char *cadena,int tamSeg){
//	int i;
//	int max= sizeof(operacion)/sizeof(operacion[0]);
////	cadena =  borrarEspaciosInnecesarios(cadena);
//	for(i=0;i<=max;i++){
//		string_length(operacion[i]);
//
//	}
	char* buffer=malloc(tamSeg);
	//FIXME

	memcpy(buffer,operacion[7],tamSeg);
	return buffer;
}

char *almacenarBytesPorConsola(char **operacion,char *cadena) {
	uint32_t pid = atoi(operacion[6]);
	uint32_t base = atoi(operacion[3]);
	uint32_t offset = atoi(operacion[4]);
	uint32_t tamSeg = atoi(operacion[5]);
	char* buffer = retornarBufferPedido(operacion,cadena,tamSeg);
	escribir_segmento(base, tamSeg, offset, buffer, pid);

	if (cadenasIguales(operacion[2], "archivo")) {
		txt_write_in_file(resultadoConsola, "Se almaceno correctamente el buffer: \n");
		txt_write_in_file(resultadoConsola,buffer);
		txt_write_in_file(resultadoConsola,"\n==================================================\n");
	}

	return string_from_format("Se almaceno correctamente \n");
}


int contadorEspacios(char *frase){
	int t=strlen(frase);
	int i,c=0;
	for(i=0;i<t;i++){
	if(frase[i]==' ') c++;
	}
	return c;
}
int cantidadDeArgumentosNoValida(int cantEspaciosCadena,int cantInvalidos){
	if(cantEspaciosCadena<cantInvalidos){
		printf("Forma incorrecta de ingresar argumentos\n\n");
		return 1;
	}
	return 0;
}

int cantidadDeArgumentos(int cantEspaciosCadena,int cantValidos){
	if(cantEspaciosCadena!=cantValidos){
		printf("Forma incorrecta de ingresar argumentos\n\n");
		return 1;
	}
	return 0;
}
int cadenasIguales(char *cadena1,char *cadena2){
	if (strlen(cadena1)==strlen(cadena2)){
		if(string_equals_ignore_case(cadena1,cadena2))
			return 1;
	}
	return 0;
}

char *borrarEspaciosInnecesarios(char *cadena){
	char **cadenaSinEspaciosExt=malloc(200);
	*cadenaSinEspaciosExt=cadena;
	string_trim(cadenaSinEspaciosExt);

	return (*cadenaSinEspaciosExt);
}

int noSeIngresoNada(char *cadena){
	if(string_is_empty(cadena)){
		printf("No se ingresó ningun comando\n");
		return 1;
	}
	return 0;
}

void manejo_consola(){
	while(1){
		consola();
		printf("===========================================================\n");
	}
}

int consola(void) {
	char* cadena = malloc(200);
	int numeroComando = 0;

	printf("\nIngresar comando:\n");
	gets(cadena);
	//Controla que si se apreta enter solo no tire segmentation fault
	if(noSeIngresoNada(cadena))
		return 1;
	//Controla que si se puso un espacio delante o después de la cadena por descuido no tire SF
	char *cadenaSinEspacios=borrarEspaciosInnecesarios(cadena);
	//Divide la cadena ingresada en cada espacio ejemplo ingreso
	//retardo 10 , entonces operacion[0]=retardo y operación[1]=10
	char **operacion = string_split(cadenaSinEspacios, " ");

	numeroComando = cadenaEntera(operacion[0]);
	char *publicacion = NULL;
	char *comandoS = malloc(200);
	//Se utiliza posteriormente para saber que la cantidad de argumentos es la correcta
	int cantEspacios=contadorEspacios(cadenaSinEspacios);

	switch(numeroComando){

	case OPERACION:

		if (cantidadDeArgumentosNoValida(cantEspacios,1))
			return 0;

		comandoS = operacion[1];

		if (cadenasIguales(comandoS,"crearSegmento")) {
			if (cantidadDeArgumentos(cantEspacios,4))
				return 0;
			publicacion = crearSegmentoPorConsola(operacion);
		}

		if (cadenasIguales(comandoS, "destruirSegmento")) {
			if (cantidadDeArgumentos(cantEspacios,3))
				return 0;
			publicacion = destruirSegmentosPorConsola(operacion);
		}

		if (cadenasIguales(comandoS,"almacenarBytes")) {
			if (cantidadDeArgumentosNoValida(cantEspacios,7))
				return 0;
			publicacion = almacenarBytesPorConsola(operacion,cadenaSinEspacios);
			printf("%s \n", publicacion);
			break;
		}

		if (cadenasIguales(comandoS,"solicitarBytes")) {
			if (cantidadDeArgumentos(cantEspacios,6))
				return 0;
			publicacion = solicitarBytesPorConsola(operacion);
		}

		printf("%s \n", publicacion);

		if (cadenasIguales(operacion[2], "archivo")) {
			txt_write_in_file(resultadoConsola, publicacion);
			txt_write_in_file(resultadoConsola,"\n==================================================\n");
		}

		break;

	case RETARDO:
		if (cantidadDeArgumentos(cantEspacios,1))
			return 0;
		cambiar_retardo(atoi(operacion[1]));
		printf("Se cambio el retardo exitosamente\n");

		break;

	case ALGORITMO:
		if (cantidadDeArgumentos(cantEspacios,1))
			return 0;
		comandoS = operacion[1];
		if (cadenasIguales(comandoS,"first-fit"))
			cambiarAlgoritmo(0);

		if (cadenasIguales(comandoS,"worst-fit"))
			cambiarAlgoritmo(1);

		if(!cadenasIguales(comandoS,"worst-fit") && !cadenasIguales(comandoS,"first-fit")){
			printf("El algoritmo ingresado es incorrecto. Reintente\n");
			break;
		}

		if(algoritmoActual)
			printf("Se cambio el algoritmo de asignacion de memoria a: worst-fit\n");
		else
			printf("Se cambio el algoritmo de asignacion de memoria a: first-fit\n");

		break;

	case COMPACTAR:

		compactar_memoria();
		printf("Se compacto la memoria exitosamente\n");

		break;

	case DUMP:
		if (cantidadDeArgumentosNoValida(cantEspacios,1))
			return 0;

		if (cadenasIguales(operacion[1], "tablaDeSegmentos")) {

			imprime_estructuras_memoria();

		} else {
			if (cadenasIguales(operacion[1], "estructuraMp")) {

				imprime_estado_mem_ppal(operacion);

			} else {
				if (cadenasIguales(operacion[1], "contenidoMp")) {
					reporteContenidoMp(operacion);
				} else {
					printf("Comando no valido \n");
				}
			}
		}
		break;

	case HELP:
		printf("\n\t\t\t   ---COMANDOS---   \n operacion crearSegmento <archivo/consola> <id programa> <tamaño> \n operacion destruirSegmento <archivo/consola> <id programa>\n operacion solicitarBytes <archivo/consola> <id programa> <base> <offset> <tamaño>\n operacion almacenarBytes <archivo/consola> <base> <offset> <tamaño> <id programa> <buffer>\n\n retardo <milisegundos>\n\n algoritmo <firstFit/worstFit>\n\n compactacion \n\n dump tablaDeSegmentos <id programa/0>\n dump contenidoMp <offset> <tamaño>\n dump estructuraMp\n\n");
		break;

	default:
		printf("\n No es un comando válido \n");
	}

	free(comandoS);
	return (1);

}
