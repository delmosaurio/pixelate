/*
 *      bmp_encabezado.h
 *      
 *      Copyright (c) 2008 Delmo Carrozzo <dcardev@gmail.com>
 *      
 *      Este archivo es parte de pixelate.
 *      
 *      pixelate es Software Libre; Usted puede redistribuirlo y/o modificarlo 
 *      bajo los términos de la Licencia Pública General de la GNU según los 
 *      datos publicados por la Free Software Foundation, de la versión 3
 *      de la Licencia,o bien (a su elección) cualquier versión posterior.
 *      
 *      Usted debe haber recibido una copia de la Licencia Pública General
 *      de la GNU junto con este programa, si no es asi, ingrese en 
 *      <http://www.gnu.org/licenses/>.
 *      
 *      
 *      Realizado para: Grupo 11 - Taller C
 *      
 *      Descripción: Prototipo de funciones y estructuras, para manipular encabezados
 *                   de archivos bmp. Esta libreria junto con bmp_mapabit.h son las
 *                   encargadas de extraer y guardar informacion de archivos bmp, esta
 *                   se encarga de los encabezados, extraccion, guardado y mostrado
 *                   de un encabezado. Esta preparada para trabajar con archivos bmp
 *                   sin compresion y con pixels de 1, 4, 8, 16, 24, 32.
 *                   Trabaja en conjunto con bitmaps.h, usando su estructura paleta
 *                   para la representacion de una paleta para, la imagenes que la
 *                   necesitian.
 */

#include <stdint.h>   /*Tipos de datos.*/
#include <stdlib.h>
#include <stdio.h>

#include "bitmaps.h"

#ifndef BMP_ENCABEZADO_H
#define BMP_ENCABEZADO_H


/* ESTRUCTURAS */

/*
 * Esta estructura abstraera un encabezado(header)
 * de un archivo BMP.
 */
typedef struct 
{
   uint16_t type; /*Tipo de encabezado.*/
   uint32_t fileSize; /*Tamaño del archivo.*/
   uint32_t reserved; /*Reservado (no usado)*/
   uint32_t offSet; /*Dreccion del primer elemento del bitmap dentro del archivo.*/

} _BMP_FileHeader;

/*
 * Esta estructura abstraera la informacion de un encabezado(InfoHeader).
 *
 */
typedef struct
{
   uint32_t size; /*Tamaño contenedor.*/
   uint32_t width; /*Ancho de la imagen.*/
   uint32_t height; /*Alto de la imagen.*/
   uint16_t planes; /*Numero de planos.*/
   uint16_t bitCount; /*Bits por pixel.*/
   uint32_t compresion; /*Conpresion.*/
   uint32_t imageSize; /*Tamaño del bitmap.*/
   uint32_t xPixelsPerM; /*Resolucion horizontal.*/
   uint32_t yPixelsPerM; /*Resolucion vertical.*/
   uint32_t colorsUsed; /*Colores usados. (0 indica 'todos')*/
   uint32_t colorsImportant; /*Colores importantes. (0 indica 'todos')*/

} _BMP_InfoHeader;

/*
 * Esta estructura esta deribada de las anteriores,
 * intenta abstraer todo un encabezado de un BMP.
 *
 */
typedef struct
{

  _BMP_FileHeader encabezado;
  _BMP_InfoHeader infoEncabezado;
  paleta_t *paleta; /*Definida en bitmaps.h*/

} _BMP_Header;


/* PROTOTIPOS */

/*
 * 
 * name _BMP_extraerEncabezado
 *   Extrae un encabezado de un archivo bmp, tambien si
 *   la imagene es con bits por pixels menor o igual a 8
 *   extraera la paleta de colores correspondiente.
 * 
 * @param FILE* - Archivo bmp del cual se extraera el encabezado.
 * 
 * @return _BMP_Header - Encabezado extraido
 * 
 */
_BMP_Header _BMP_extraerEncabezado(FILE* archivo);     /*Implementada*/

/*
 * 
 * name _BMP_guardarEncabezado
 *   Guarda un encabezado dentro de un archivo bmp
 *   guardando tabien su paleta si es que tiene.
 * 
 * @param FILE* - 
 * @param _BMP_Header - 
 * 
 * @return int - Retorna 1 si se pudo realizar la operacion 0 en caso contrario
 * 
 */
int _BMP_guardarEncabezado(FILE* archivo, _BMP_Header encabezado);     /*Implementada*/

/*
 * 
 * name _BMP_imprimirEncabezado
 *   Imprime en pantalla el encabezado de un bmp
 *   imprimiendo tambien su paleta.
 * 
 * @param _BMP_Header - Encabezado a imprimer
 * @param char* - Nombre del archivo.
 * 
 * @return int - Retorna 1 si se pudo realizar la operacion 0 en caso contrario.
 * 
 */
int _BMP_imprimirEncabezado(_BMP_Header encabezado,char* nomArchivo);    /*Implementada*/

#endif /*Fin BMP_ENCABEZADO_H*/
