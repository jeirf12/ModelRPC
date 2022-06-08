#include "interface3.h"

int *notificarregistrocancion_1_svc(nodo_cancion_1 *argp, struct svc_req *rqstp) {
	static int  result;
	printf("\n\t\tNueva Notificación!!");
	printf("\nUna canción nueva se ha registrado");
	printf("\nId: %d", argp->id);
	printf("\nTitulo: %s", argp->titulo);
	printf("\nTipo: %s", argp->tipo);
	printf("\nTamaño: %lf mb", argp->peso);
	printf("\n");
	result = 1;
	return &result;
}
