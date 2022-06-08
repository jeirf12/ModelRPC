const MAXNOM = 30;
struct nodo_cancion_1 {
  int id;
  char titulo[MAXNOM];
  char tipo[MAXNOM];
  double peso;
};
typedef struct nodo_cancion_1 nodo_cancion_1;
program interface3 {
  version interface3_version_1 {
    int notificarRegistroCancion(nodo_cancion_1 datosCancion) = 1;
  } = 1;
} = 0x22000003;
