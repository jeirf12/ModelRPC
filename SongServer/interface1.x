const MAXNOM = 30;
const TAM_MAX_NOM_ARCHIVO = 128;
const TAM_MAX_BLOQUE_ARCHIVO = 1024;
struct bloque {
  string nombreArchivo<TAM_MAX_NOM_ARCHIVO>;
  opaque datos<TAM_MAX_BLOQUE_ARCHIVO>;
  int size;
  int dest_offset;
};
struct nodo_cancion {
  int id;
  char titulo[MAXNOM];
  char tipo[MAXNOM];
  double peso;
};
typedef struct bloque bloque;
typedef struct nodo_cancion nodo_cancion;
program interface1 {
  version interface1_version_1 {
    int enviarDatosCancion(nodo_cancion datosCancion) = 1;
    int crearArchivoVacio(string nombreArchivo) = 2;
    int enviarArchivo(bloque *) = 3;
    nodo_cancion consultarCancion(string nombreCancion) = 4;
  } = 1;
} = 0x22000001;
