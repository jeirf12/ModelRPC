const TAM_MAX_NOM_ARCHIVO = 128;
const TAM_MAX_BLOQUE_ARCHIVO = 1024;
struct bloque_1 {
  string nombreArchivo<TAM_MAX_NOM_ARCHIVO>;
  opaque datos<TAM_MAX_BLOQUE_ARCHIVO>;
  int size;
  int dest_offset;
};
typedef struct bloque_1 bloque_1;
program interface2 {
  version interface2_version_1 {
    int crearCopiaCancion(string nombreArchivo) = 1;
    int enviarCopiaCancion(bloque_1 *) = 2;
  } = 1;
} = 0x22000002;
