/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _INTERFACE1_H_RPCGEN
#define _INTERFACE1_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif

#define MAXNOM 30
#define TAM_MAX_NOM_ARCHIVO 128
#define TAM_MAX_BLOQUE_ARCHIVO 1024

struct bloque {
	char *nombreArchivo;
	struct {
		u_int datos_len;
		char *datos_val;
	} datos;
	int size;
	int dest_offset;
};
typedef struct bloque bloque;

struct nodo_cancion {
	int id;
	char titulo[MAXNOM];
	char tipo[MAXNOM];
	double peso;
};
typedef struct nodo_cancion nodo_cancion;



#define interface1 0x22000001
#define interface1_version_1 1

#if defined(__STDC__) || defined(__cplusplus)
#define enviarDatosCancion 1
extern  int * enviardatoscancion_1(nodo_cancion *, CLIENT *);
extern  int * enviardatoscancion_1_svc(nodo_cancion *, struct svc_req *);
#define crearArchivoVacio 2
extern  int * creararchivovacio_1(char **, CLIENT *);
extern  int * creararchivovacio_1_svc(char **, struct svc_req *);
#define enviarArchivo 3
extern  int * enviararchivo_1(bloque *, CLIENT *);
extern  int * enviararchivo_1_svc(bloque *, struct svc_req *);
#define consultarCancion 4
extern  nodo_cancion * consultarcancion_1(char **, CLIENT *);
extern  nodo_cancion * consultarcancion_1_svc(char **, struct svc_req *);
extern int interface1_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define enviarDatosCancion 1
extern  int * enviardatoscancion_1();
extern  int * enviardatoscancion_1_svc();
#define crearArchivoVacio 2
extern  int * creararchivovacio_1();
extern  int * creararchivovacio_1_svc();
#define enviarArchivo 3
extern  int * enviararchivo_1();
extern  int * enviararchivo_1_svc();
#define consultarCancion 4
extern  nodo_cancion * consultarcancion_1();
extern  nodo_cancion * consultarcancion_1_svc();
extern int interface1_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_bloque (XDR *, bloque*);
extern  bool_t xdr_nodo_cancion (XDR *, nodo_cancion*);
extern  bool_t xdr_bloque (XDR *, bloque*);
extern  bool_t xdr_nodo_cancion (XDR *, nodo_cancion*);

#else /* K&R C */
extern bool_t xdr_bloque ();
extern bool_t xdr_nodo_cancion ();
extern bool_t xdr_bloque ();
extern bool_t xdr_nodo_cancion ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_INTERFACE1_H_RPCGEN */