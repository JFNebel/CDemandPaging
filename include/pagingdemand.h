//Header Files
#include <stdio.h>
#include <stdlib.h>

//Constantes
#define LINEA_MAXIMA 100
#define TAMANO_PAGINA 256
#define MAX_MEM 65535
#define NUM_ENTRADAS 256
#define PAGE_FAULT -42
#define PATH_BIN "BACKING_STORE.bin"
 

//Funciones
void ayuda();
void initialize();
