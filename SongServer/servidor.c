#include "interface1.h"
#include "interface2.h"
#include "interface3.h"

nodo_cancion_1 *datosCancion;
nodo_cancion vectorCanciones[5];
char *rutaCancion;
int posicion = 0, tamanio = 5;
void enviarArchivoAlServidorRespaldo(char *nombreArchivo, CLIENT *clnt);

int *enviardatoscancion_1_svc(nodo_cancion *argp, struct svc_req *rqstp) {
	static int result;
	datosCancion = (nodo_cancion_1*)malloc(sizeof(struct nodo_cancion_1));
	printf("\n Invocando a registro de datos de la canción en el servidor de canciones ");
	if (posicion < tamanio) {
		printf("\n Datos de la canción Registradas en el servidor de canciones \n");
		datosCancion->id = argp->id;
		strcpy(datosCancion->titulo, argp->titulo);
		strcpy(datosCancion->tipo, argp->tipo);
		datosCancion->peso = argp->peso;
		vectorCanciones[++posicion] = *argp;
		result = 1;
	}
	return &result;
}

int *creararchivovacio_1_svc(char **argp, struct svc_req *rqstp) {
	static int result;
	if (posicion < tamanio) {
		rutaCancion = (char*)malloc(30*sizeof(char));
		char* token = strtok(*argp, ".");
		char* token2 = strtok(NULL, ".");
		char* chain = (char*)malloc(30*sizeof(char));
		chain = "misCanciones/%s_%d.%s";
		printf("\n Invocando al Servidor de Canciones en la creación de un archivo vacío");
		sprintf(rutaCancion, chain, token, posicion, token2);
		fopen(rutaCancion, "w");
		result = 1;
	}
	return &result;
}

int *enviararchivo_1_svc(bloque *argp, struct svc_req *rqstp) {
	CLIENT *clnt;
  	int *result_1;
	int *result_2;
	static int result;
	FILE *file;
  	file = fopen(rutaCancion, "a");
	if (file != NULL) result = 1;
	fseek(file, (*argp).dest_offset, SEEK_SET);
  	fwrite((*argp).datos.datos_val, 1, (*argp).datos.datos_len, file);
	fclose(file);
	if ((*argp).dest_offset == 0) printf("\n Primer bloque recibido exitosamente \n");
	else if ((*argp).datos.datos_len < TAM_MAX_BLOQUE_ARCHIVO) {
		printf("\n Ultimo bloque recibido exitosamente \n");
		printf("\n Enviando copia al servidor de respaldo.. \n");
		clnt = clnt_create("localhost", interface2, interface2_version_1, "tcp");
		if (clnt == NULL) {
			clnt_pcreateerror("localhost");
			exit(1);
		}
		result_1 = crearcopiacancion_1(&rutaCancion, clnt);
		if (result_1 == (int *)NULL) {
			clnt_perror(clnt, "call failed");
		} else {
			printf("\n Archivo vacío creado en el servidor de respaldo");
			printf("\n Procediendo a enviar en bloques el archivo al servidor de respaldo");
			enviarArchivoAlServidorRespaldo(rutaCancion, clnt);
		}
		clnt = clnt_create("localhost", interface3, interface3_version_1, "tcp");
		if (clnt == NULL) {
			clnt_pcreateerror("localhost");
			exit(1);
		}
		result_2 = notificarregistrocancion_1(datosCancion, clnt);
		if (result_2 == (int *)NULL) {
			clnt_perror(clnt, "call failed");
		} else printf("\n El servidor administrador ha sido notificado correctamente\n\n");
	}
	return &result;
}

nodo_cancion * consultarcancion_1_svc(char **argp, struct svc_req *rqstp) {
	static nodo_cancion result;
	memset(&result, 0, sizeof(nodo_cancion));
	printf("\n Invocando a consultar canción en el servidor de canciones");
	printf("\n Nombre de la canción a consultar: %s \n", *argp);
	for (int i = 0; i < tamanio; i++) {
		if (strcmp((&vectorCanciones[i])->titulo, *argp) == 0) {
			result = vectorCanciones[i];
			break;
		}
	}
	return &result;
}

void enviarArchivoAlServidorRespaldo(char *nombreArchivo, CLIENT *clnt) {
	FILE *file = fopen(nombreArchivo, "r");
	char bandera = 1;
	int pos = 0, cantidadBloques = 0;
	bloque_1 objBloque;
	objBloque.nombreArchivo = (char *)malloc(20 * sizeof(char));
	strcpy(objBloque.nombreArchivo, nombreArchivo);
	objBloque.datos.datos_val = (char *)malloc(TAM_MAX_BLOQUE_ARCHIVO * sizeof(char));
	do {
		objBloque.datos.datos_len = fread(objBloque.datos.datos_val, 1, TAM_MAX_BLOQUE_ARCHIVO, file);
		objBloque.dest_offset = pos;
		pos = pos + objBloque.datos.datos_len;
		int *resultado = enviarcopiacancion_1(&objBloque, clnt);
		if (resultado == (int *)NULL) {
			clnt_perror(clnt, "call failed");
			bandera = 0;
		} else {
			cantidadBloques++;
		}
	} while (objBloque.datos.datos_len == TAM_MAX_BLOQUE_ARCHIVO);

	free(objBloque.datos.datos_val);
	fclose(file);
	if (bandera) printf("\n Canción enviada exitosamente a partir de  %d bloques\n", cantidadBloques);
	else printf("\n Error al enviar canción\n");
}
