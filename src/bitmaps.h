/*
 *      bitmaps.h
 *      
 *      Copyright (c) 2008 Delmo Carrozzo <dcardev@gmail.com>
 *      
 *      Este archivo es parte de pixelate.
 *      
 *      pixelate es Software Libre; Usted puede redistribuirlo y/o modificarlo 
 *      bajo los términos de la Licencia Pública General de la GNU según los 
 *      datos publicados por la Free Software Foundation, de la versión 2
 *      de la Licencia,o bien (a su elección) cualquier versión posterior.
 *      
 *      Usted debe haber recibido una copia de la Licencia Pública General
 *      de la GNU junto con este programa, si no es asi, ingrese en 
 *      <http://www.gnu.org/licenses/>.
 *      
 *      
 *      Realizado para: Grupo 11 - Taller C
 *      
 *      Descripción: 
 *           bitmap: Matriz de pixeles, donde cada uno de estos tiene 
 *                 un valor que determina el color de una tabla de valores 
 *                 posibles Y asi el conjunto forma una imagen digital.
 *                 Para comprender un pixel vea (pixeles.h).
 *               
 *                 Prototipo de funciones y estructuras, para la manipulacion
 *                 de mapa de bits en memoria.
 *                 Esta libreria esta pensada para manipular imagenes de mapabit
 *                 independientemente cual sea el tipo de imagen, es decir, el mapa
 *                 de una imagen, es igual para un archivo bmp, jpeg, png, etc...
 *                 cambia la forma en que son guardados estos archivos, por lo tanto
 *                 otras librerias se encargan de extraer el mapa de el archivo, sea cual
 *                 sea la extension y estas estrcuturas se encargan de representarlo.
 */

#include <stdint.h>  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pixeles.h" 
#include "colores.h" 

#ifndef BITMAPS_H
#define BITMAPS_H

/* ESTRUCTURAS */

/*
 * Esta estructura abstrae la paleta del mapabit
 * si es que necesita, es usada para archivos 
 * con bitCount <=8, y para las imagenes de 16
 * contine las mascaras para manipular los pixeles.
 */
typedef struct
{
   uint8_t blue;
   uint8_t green;
   uint8_t red;
   uint8_t reserved;
} paleta_t;

/*
 * Esta estructura es la abstraccion de una imagen para poder manipular 
 * el bitmaps de imagenes de 1, 4, 8, 16, 24, 32.
 * la union mapa dependera del campo bitCount quien contendra la
 * cantidad de bit por pixeles.
 * 
 * @see pixeles.h 
 * 
 */
typedef union
{ 
  pixel_1 *map_1;   /*para mapabit de 1 bit*/
  pixel_4 *map_4;   /*para mapabit de 4 bit*/
  pixel_8 *map_8;   /*para mapabit de 8 bit*/
  pixel_16 *map_16; /*para mapabit de 16 bit*/
  pixel_24 *map_24; /*para mapabit de 24 bit*/
  pixel_32 *map_32; /*para mapabit de 32 bit*/
} mapa_t;

typedef struct
{
   uint32_t width; /*Ancho de la imagen*/ 
   uint32_t height; /*Alto de la imagen*/
   uint16_t bitCount; /*Bit por pixels*/
   uint32_t colorsUsed; /*Colores usados. (0 indica 'todos')*/
   paleta_t *paleta; /*Paleta para imagenes bitCount<=8*/
   /*Union*/
   mapa_t mapa; /*bitMap data.*/
} imagen_mapabit;


/* PROTOTIPOS */

/*
 * 
 * name nueva_imagen
 *   Crea una nueva imagen_mapabit alocando memoria para sus elementos.
 * 
 * @param uint32_t - Ancho del mapa de bits
 * @param uint32_t - Alto del mapa de bits.
 * @param uint16_t - bit por pixels del mapa de bits.
 * @param uint32_t - colores usados del mapa de bits.
 * 
 * @return imagen_mapabit - Nueva estructura inicializada.
 * 
 */
imagen_mapabit nueva_imagen( uint32_t, uint32_t, uint16_t, uint32_t);  /*Implementada*/

/*
 * 
 * name promPixels
 *   Calcula el promedio de pixeles en un radio especificado.
 * 
 * @param mapa_t * - mapa del cual se extraera el promedio
 * @param uint32_t - ancho de mapa.
 * @param uint32_t - alto del mapa.
 * @param uint16_t - bits por pixels del mapa.
 * @param int - columna de inicio.
 * @param int - fila para el inicio.
 * @param int - radio.
 * 
 * @return uint32_t - Promedio calculado, luego para dividir el los difirentes colores
 *                    consulte los macros definidos en colores.h.
 * 
 */
uint32_t promPixels(mapa_t *, uint32_t, uint32_t, uint16_t, int, int, int); /*Implementada*/

#endif /*BITMAPS_H*/
