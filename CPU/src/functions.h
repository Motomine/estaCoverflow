/*
 * functions.h
 *
 *  Created on: 03/06/2014
 *      Author: utnso
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <commons/config.h>
#include "globales.h"

int conectarUMV();
int conectarKernel();
int recibirQuantum();
int obtenerPosicion(char variable);
void inicializarEstructuras();
void liberarEstructuras();
int archivoDeConfiguracionValido();

#endif /* FUNCTIONS_H_ */