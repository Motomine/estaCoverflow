/*
 * functions.h
 *
 *  Created on: 24/05/2014
 *      Author: utnso
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "globales.h"
#include <commons/config.h>
#include <sys/stat.h>

void enviarProgramaAlKernel(char* programa);
void recibirSentencia();
char* obtenerPrograma(char* programa);
int conectarKernel();
void inicializarVariables();
int archivoDeConfiguracionValido();
void liberarEstructuras();

#endif /* FUNCTIONS_H_ */
