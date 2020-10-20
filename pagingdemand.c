/** ProyectoFinal: Paging On Demand
 * @author Juan Nebel
 * 12/09/20
 */

#include "./include/pagingdemand.h"

int main(int argc, char *argv[])
{

    //Doy un enter para mas claridad en la consola:
    printf("\n");

    //Validamos el numero de args
    if (argc != 3)
    {
        fprintf(stderr, "Numero de argumentos invalido!(0):\n");
        ayuda();
        return (-1);
    }

    //Abrimos los recursos a utilizar
    char linea[LINEA_MAXIMA];
    FILE *fp    = fopen(argv[1], "r");
    FILE *fpEsc = fopen(argv[2],"w");
    FILE *fpBin = fopen(PATH_BIN,"rb");

    //Validamos la apertura de los recursos
    if(fp == NULL || fpBin == NULL)
    {
        fprintf(stderr, "Uno de los recursos necesarios no fue ingresado correctamente (6):\n");
        ayuda();
        return (-1);
    }

    //Creamos el arreglo que representa la tabla de paginacion y el arreglo(matriz) que representa la memoria fisica
    int pageTable[NUM_ENTRADAS];
    char pMem[NUM_ENTRADAS][NUM_ENTRADAS];

    //Llenamos la page table (vacia) de PAGE_FAULTS:
    initialize(pageTable, NUM_ENTRADAS);

    int lineaNum = 0; //--> Contador de linea
    int frame = 0; // --> Contador de frame libre



    //Recorremos cada linea del archivo
    while(fgets(linea,LINEA_MAXIMA,fp)!=NULL)
    {
        unsigned int vaddress = atoi(linea); //--> Direccion virtual extraida de addresses.txt

        //Validamos que el valor de las lineas del .txt sea valido
        if (vaddress > MAX_MEM)
        {
            fprintf(stderr, "La linea (%d) del archivo de direcciones logicas excede la capacidad de memoria del sistema(4):\n", (lineaNum + 1));
            ayuda();
            return (-1);
        }

        //Conseguimos los datos de interes que brinda la linea que no necesitan validacion:
        int pageNum  = vaddress / TAMANO_PAGINA; //Nos da el indice de pagina (trunca hacia abajo)
        int offset   = vaddress % TAMANO_PAGINA;  //El modulo nos da el sobrante/despazamiento/offset
        
        //Declaramos los datos de la linea que necesitan validacion PAGE_FAULT
        int frameNum;
        int paddress;

        //Verificamos PAGE_FAULT
        if(pageTable[pageNum]==PAGE_FAULT)
        {
            //Mapeamos entrada en tabla de paginacion
            frameNum           = frame;
            pageTable[pageNum] = frameNum;
            frame++; //--> Nos movemos al siguiente frame libre

            //============================================== ACCESO AL ARCHIVO BINARIO =======================================//

            //Colocamos el puntero en la posicion correcta dentro del bin
            int posicionBin = pageNum * TAMANO_PAGINA;
            fseek(fpBin, posicionBin, SEEK_SET);

            //Leemos el binario y guardamos el valor en la memoria fisica
            int rc = 0;
            rc = fread(&pMem[frameNum], 1, TAMANO_PAGINA, fpBin);

            //============================================== FIN SECCION BINARIO ============================================//

        }else{
            //Si entra en este else es porque no hubo page fault
            frameNum = pageTable[pageNum];            
        }


        int value = pMem[frameNum][offset]; // --> Casteamos char a int (Accedemos al char correcto por el offset)
        paddress = frameNum * TAMANO_PAGINA + offset; // --> Direccion fisica
        lineaNum++; // --> Permite imprimir la linea exacta donde ocurre un error en el .txt


        //Print de lo que se escribira en el archivo:
        //printf("%d Virtual address: %d Physical address: %d Value: %d\n", (lineaNum),vaddress, paddress, value);
        fprintf(fpEsc, "Virtual address: %d Physical address: %d Value: %d\n", vaddress, paddress, value);

        //Testing break (solo para pruebas):
        //if(lineaNum == 5)
        //    break;
    }


    //Cerramos recursos
    fclose(fp);
    fclose(fpEsc);
    fclose(fpBin);

    //Doy otro enter para mejor claridad en la consola:
    printf("\n");
    return 0;
}



/*=====================================================Funciones===============================================*/

/* La funcion ayuda, permite mostrar en consola el uso correcto el ejecutable. Deber ser llamada
 * cuando existe un input erroneo por parte del usuario.
 */
void ayuda()
{
    printf("\n/*************************************************AYUDA*******************************************************/\n");
    printf("\nEl programa pagingdemand acepta 3 argumentos contando al programa:\n");
    printf("1) El arg 1 es el programa en si: ./pagingdemand\n");
    printf("2) El arg 2 es el archivo de direcciones virtuales: addresses.txt\n");
    printf("3) El arg 3 es el nombre del archivo a generar con la traduccion realizada, ej.: data.txt\n");
    printf("4) Este programa destina 2^8 para numeros de pagina y 2^8 para tamanos de pagina, es decir, no aceptara \nun archivo que contenga lineas con numeros enteros mayores a 65535 en el archivo de direcciones logicas\n");
    printf("5) El programa viene con un archivo binario (.bin) BACKUP_STORE que debe estar en la misma carpeta que el .c,\nsi se desea usar otro archivo modificar el PATH en el .h\n");
    printf("6) Si usted obtiene el error 6, es porque ingreso mal la direccion del archivo de direcciones logicas (addresses.txt)\no el archivo binario BACKUP_STORE.bin no se encuentra en la misma carpeta que el .c y el nuevo PATH no ha sido \nconfigurado correctamente en el.h\n");
    printf("\nPLANTILLA:\n\t\t./pagingdemand addresses.txt data.txt\n\n");
}

/* La funcion initialize me sirve para recorrer un arreglo (pageTable) y llenarlo de la constante definida en el .h para representar un PAGE_FAULT. En abstracto, me permite tener una pageTable vacia. 
 */
void initialize(int *pageTable, int size){
    for(int i=0; i<size; i++){
        pageTable[i] = PAGE_FAULT;
    }
}