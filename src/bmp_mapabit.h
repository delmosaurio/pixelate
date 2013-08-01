/*
 *      bmp_mapabit.h
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
 *      Descripción: Prototipo de funciones, para la manipulacion
 *                   de mapa de bit de archivos bmp.
 *                   Esta libreria junto con 'bmp_encabezado' son las encargadas
 *                   de extraer y guardar informacion de archivos bmp.
 *                   Esta trabajo junto con 'bitmaps' para guardar y extraer
 *                   mapabits de los archivos bmp, tambien necesita de la
 *                   'bmp_encabezado' para obtener informacion de como extraer
 *                   y guadar el mapa.
 * 
 */


#include <stdint.h> 
#include <stdlib.h>
#include <stdio.h>
#include "bitmaps.h"
#include "bmp_encabezado.h"

#ifndef BMP_MAPABIT_H
#define BMP_MAPABIT_H

/*
 * 
 * name _BMP_extraerMapabit
 *   Extrae el mapa de bit del archivo bmp.
 *   Asegurese de haber extraido el encabezado del
 *   bmp anteriormente.
 * 
 * @param FILE* - Archivo bmp del cual se extraera el mapa.
 * @param _BMP_Header- Encabezado del bmp.
 * 
 * @return imagen_mapabit - Retorno de la imagen_mapabit extraida del bmp.
 * 
 */
imagen_mapabit _BMP_extraerMapabit(FILE* , _BMP_Header ); /*Implementada*/

/*
 * 
 * name _BMP_guardarMapabit
 *   Guarda un mapa de bits dentro de un archivo de imagen bmp.
 * 
 * @param FILE* - Archivo donde se guardara la imagen.
 * @param imagen_mapabit* - imagen_mapabit que se guardara
 * @param uint32_t - comienzo en el archivo donde se empieza a guardar
 *                   el mapa, es obtenido del encabezado del bmp.
 * 
 * @return int - Retorna 1 si se realizo la operacion, 0 en caso contrario.
 * 
 */
int _BMP_guardarMapabit(FILE* , imagen_mapabit*, uint32_t); /*Implementada*/

#endif /*Fin BMP_MAPABIT_H*/
