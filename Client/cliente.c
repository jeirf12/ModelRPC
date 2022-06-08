#include "interface1.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int mostrarMenu();
int validarArchivo(char *nombreArchivo);
void registrarCancion(nodo_cancion *objCancion, char *nombreArchivo);
void enviarArchivoAlServidor(char *nombreArchivo, CLIENT *clnt);
void consultaCancion(CLIENT *clnt);
int esNumero(char *cadena);

void interface1_1(char *host) {
	CLIENT *clnt;
	int  *result_1;
	nodo_cancion  datosCancion;
	int  *result_2;
	char *nombreArchivo;

	#ifndef	DEBUG
	clnt = clnt_create(host, interface1, interface1_version_1, "tcp");
	if (clnt == NULL) {
		clnt_pcreateerror(host);
		exit(1);
	}
	#endif	/* DEBUG */
  	int option = 0;
  	char *strNombreArchivo;
  	do {
		option = mostrarMenu();
		switch (option) {
			case 1:
				nombreArchivo = (char*)malloc(20 * sizeof(char));
				strNombreArchivo = (char*)malloc(20 * sizeof(char));
				registrarCancion(&datosCancion, nombreArchivo);
  				strcpy(strNombreArchivo, nombreArchivo);
				if(validarArchivo(strNombreArchivo) == 0){
					if ((result_1 = enviardatoscancion_1(&datosCancion, clnt)) != NULL){
						if((result_2 = creararchivovacio_1(&nombreArchivo, clnt)) != NULL){
							printf("\n Archivo vacío creado en el servidor");
							printf("\n Procediendo a enviar en bloques el archivo");
							enviarArchivoAlServidor(nombreArchivo, clnt);
						}else{
							printf("\n Lo sentimos, ocurrió un error en la creación del archivo vacío");
						}
					}else{
						printf("\n Lo sentimos, ocurrió un error al registrar la canción");
					}
				}
				break;  
			case 2:consultaCancion(clnt); break;
			case 3: printf("\n Gracias por utilizar el programa!\n"); break;
			default: printf("\n Ingreso una opción incorrecta o que no existe\n"); break;
		}
	}while (option !=3);
	
	#ifndef	DEBUG
	clnt_destroy(clnt);
	#endif	 /* DEBUG */
}

int main(int argc, char *argv[]) {
	char *host;
	if (argc < 2) {
		printf("usage: %s server_host\n", argv[0]);
		exit(1);
	}
	host = argv[1];
	interface1_1(host);
	exit(0);
}

void registrarCancion(nodo_cancion *objCancion, char *nombreArchivo){
	printf("Ingrese el id de la canción: \n");
	scanf("%d", &objCancion->id);
	printf("Ingrese el titulo de la canción: \n");
	scanf("%s", objCancion->titulo);
	printf("Ingrese el tipo de la canción: \n");
	scanf("%s", objCancion->tipo);
	printf("Ingrese el tamaño de la canción: \n");
	scanf("%lf", &objCancion->peso);
	printf("Ingrese el nombre del archivo: \n");
	scanf("%s", nombreArchivo);
}

int mostrarMenu(){
	int outOpcion = 0;
	char *inOpcion;
	inOpcion = (char *)malloc(20*sizeof(char*));
	printf("\n======================= MENU =====================\n");
	printf("1. Ingresar y enviar datos de la Canción\n");
	printf("2. Consultar Canciones almacenadas en el servidor\n");
	printf("3. Salir\n");
	printf("==================================================\n");
	printf("Ingrese una opción: \n");
	scanf("%s", inOpcion);
	outOpcion = esNumero(inOpcion);
	return outOpcion;
}

int esNumero(char *cadena){
	char *copia = cadena;
	while (*copia && isdigit(*copia)) copia++;
	return (*copia ? 0 : atoi(cadena));
}

int validarArchivo(char *nombreArchivo){
	int bandera = 0;
  	struct stat buffer;
  	char *token;
	int exist = stat(nombreArchivo, &buffer);
	if (exist != 0) {
  		++bandera;
		printf("\n No existe la canción: %s\n", nombreArchivo);
	}
	strtok(nombreArchivo, ".");
	token = strtok(NULL, ".");
	if (token != NULL && strcmp(token, "mp3") != 0 && strcmp(token, "mp4") != 0) {
		++bandera;
		printf("\n El archivo no tiene extensión mp3 o mp4\n");
	}else if(token == NULL){
		++bandera;
		printf("\n El archivo no tiene extensión mp3 o mp4\n");
	}
	return bandera;
}


void enviarArchivoAlServidor(char *nombreArchivo, CLIENT *clnt) {
	FILE *file = fopen(nombreArchivo, "r");
	char bandera = 1;
	int pos = 0, cantidadBloques = 0;
	bloque objBLoque;
	objBLoque.nombreArchivo = (char *)malloc(20 * sizeof(char));
	strcpy(objBLoque.nombreArchivo, nombreArchivo);
	objBLoque.datos.datos_val = (char *)malloc(TAM_MAX_BLOQUE_ARCHIVO * sizeof(char));
	do {
    	objBLoque.datos.datos_len = fread(objBLoque.datos.datos_val, 1, TAM_MAX_BLOQUE_ARCHIVO, file);
    	objBLoque.dest_offset = pos;
   		pos = pos + objBLoque.datos.datos_len;
    	int *resultado = enviararchivo_1(&objBLoque, clnt);
    	if (resultado == (int *)NULL) {
    		clnt_perror(clnt, "call failed");
			bandera = 0;
    	} else {
    		cantidadBloques++;
    	}
  	} while (objBLoque.datos.datos_len == TAM_MAX_BLOQUE_ARCHIVO);

	free(objBLoque.datos.datos_val);
	fclose(file);
	if (bandera) printf("\n Canción enviada y registrada exitosamente a partir de %d bloques\n", cantidadBloques);
	else printf("\n Error al enviar canción\n");
}

void consultaCancion(CLIENT *clnt){
	char * nombreCancion;
	nodo_cancion *result_4;
	memset(result_4, 0, 0);
	nombreCancion = (char*)malloc(30*sizeof(char));
	printf("\n Ingrese el titulo de la canción a buscar: ");
	scanf("%s", nombreCancion);
	result_4 = consultarcancion_1(&nombreCancion, clnt);
	if (result_4 == (nodo_cancion *)NULL) {
		clnt_perror(clnt, "call failed");
	}else if (result_4->id > 0) {
		printf("\n Canción encontrada");
		printf("\n Id canción: %d", result_4->id);
		printf("\n Nombre canción: %s", result_4->titulo);
		printf("\n Tipo canción: %s", result_4->tipo);
		printf("\n Peso canción: %lf mb", result_4->peso);
	} else {
		printf("\n Lo sentimos.\n la canción %s no existe!", nombreCancion);
	}
}
