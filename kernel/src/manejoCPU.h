#include <commons/collections/queue.h>
#include <semaphore.h>
#include <libs/manejoDelPCB.h>
#include <libs/sockets.h>
#include <commons/log.h>
#include <commons/config.h>


void manejoCPU(int fd);
bool condicion(registroPCB* pcb);


