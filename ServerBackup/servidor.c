#include "interface2.h"

char *rutaCancion;

int *crearcopiacancion_1_svc(char **argp, struct svc_req *rqstp) {
	static int result;
	rutaCancion = (char*)malloc(30*sizeof(char));
  	char* token = strtok(*argp, "/");
	char* token2 = strtok(NULL, "/");
  	char* chain = (char*)malloc(30*sizeof(char));
	chain = "%s/copia_%s";
	printf("\n Invocando a Servidor de Respaldo en la creación de un archivo vacío\n");
  	sprintf(rutaCancion, chain, token, token2);
	fopen(rutaCancion, "w");
	return &result;
}

int *enviarcopiacancion_1_svc(bloque_1 *argp, struct svc_req *rqstp) {
	static int  result;
  	result = 0;
	FILE *file;

	file = fopen(rutaCancion, "a");
	if (file == NULL) result = 1;
	fseek(file, (*argp).dest_offset, SEEK_SET);
	fwrite((*argp).datos.datos_val, 1, (*argp).datos.datos_len, file);
	fclose(file);

	if ((*argp).dest_offset == 0) printf("\n Primer bloque recibido exitosamente \n");
	else if ((*argp).datos.datos_len < TAM_MAX_BLOQUE_ARCHIVO) printf("\n Ultimo bloque recibido exitosamente \n");
	return &result;
}
