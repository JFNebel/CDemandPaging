# Proyecto: Paginación por demanda
Este proyecto contiene la aplicación pagingdemand.c que simula la traducción de una dirección lógica a una física en el contexto de paginación por demanda. El sistema soporta direcciones lógicas de 16 bits (8 bits para número de página y 8 bits para tamaño de página) las cuales tienen que estar expresadas en un archivo de texto (addresses.txt) en base decimal dentro de la misma carpeta que pagingdemand.c. Es importante recalcar que el formato de addresses.txt consta de una cifra decimal por línea cuyo valor debe estar en [0, 65535] por lo explicado respecto a 16 bits. Finalmente, el programa hace uso del binario BACKING_STORE.bin para definir el valor obtenido una vez hecha la traducción de dirección lógica a física. En caso de querer usar otro archivo binario o tener otro path, se debe modificar la constante del mismo nombre en include/pagingdemand.h (ver especificaciones). El programa recibe como primer parámetro al archivo de direcciones y como segundo parámetro el nombre del archivo que se desea generar con las traducciones realizadas. Éste último mostrará, para cada línea de addresses.txt: dirección lógica, dirección física y valor correspondiente. 

## Compilación


#### Para compilar el programa:
```
make
```

#### Para limpiar object files y ejecutable:
```
make clean
```

### Uso:

```
./pagingdemand [archivo .txt de direcciones lógicas] [nombre del reporte a generar]

Ejemplo:
./pagingdemand addresses.txt data.txt

```
### Resultados típicos:<br/>

```
Ejecución usando addresses.txt (contenido de data.txt):

Virtual address: 16916 Physical address: 20 Value: 0
Virtual address: 62493 Physical address: 285 Value: 0
Virtual address: 30198 Physical address: 758 Value: 29
Virtual address: 53683 Physical address: 947 Value: 108
Virtual address: 40185 Physical address: 1273 Value: 0
Virtual address: 28781 Physical address: 1389 Value: 0
Virtual address: 24462 Physical address: 1678 Value: 23
Virtual address: 48399 Physical address: 1807 Value: 67
                           .
                           .
                           .
Virtual address: 8940 Physical address: 46572 Value: 0
Virtual address: 9929 Physical address: 44745 Value: 0
Virtual address: 45563 Physical address: 46075 Value: 126
Virtual address: 12107 Physical address: 2635 Value: -46

```



### Especificaciones:<br/>
El programa pagingdemand acepta 3 argumentos contando al programa:
1) El arg 1 es el programa en sí: ./pagingdemand.
2) El arg 2 es el archivo de direcciones virtuales: addresses.txt.
3) El arg 3 es el nombre del archivo a generar con la traducción realizada, ej.: data.txt.
4) Este programa destina 2^8 para números de página y 2^8 para tamaños de página, es decir, no aceptará un archivo que contenga líneas con números mayores a 65535 en el archivo de direcciones lógicas.
5) El programa viene con un archivo binario (.bin) BACKUP_STORE que debe estar en la misma carpeta que el .c, si se desea usar otro archivo, modificar el PATH en el .h.
6) Si usted obtiene el error 6, es porque ingresó mal la dirección del archivo de direcciones lógicas (addresses.txt) o el archivo binario BACKUP_STORE.bin no se encuentra en la misma carpeta que el .c y el nuevo PATH no ha sido configurado correctamente en el.h.




PLANTILLA:          ./pagingdemand addresses.txt data.txt



## Autor
- Juan F. Nebel Dunn
