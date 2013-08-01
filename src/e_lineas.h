/*
 *      e_lineas.h
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
 *      Descripción: Dibuja lineas verticales y/o horizontales en una
 *                   imagen_mapabit, con un ancho, espacion entre lineas
 *                   y un color.
 */

#include <stdio.h>
#include <stdlib.h>
#include "bitmaps.h"


#ifndef E_LINEAS_H
#define E_LINEAS_H
/*
 * 
 * name dibujarLinea
 *   Dibuja lineas en una imagen_mapabit, esta pueden ser
 *   verticales y/o horizontales.
 *   
 * @param imagen_mapabit** - imagen para dibujar las lineas.
 * @param int - ancho de la linea.
 * @param int - espacio entre linea y linea.
 * 
 *   //Si el color sobrepasa los limites del pixel se tomara
 *   //el menor o el mayor valor posible respectivamente.
 *   //Ejemplo si es de 8 bits y se pasa el '1500' se tomara el '255'
 *   //Ejemplo si es de 8 bits y se pasa el '-150' se tomara el '0' 
 * @param uint32_t - color de la linea.
 * @param char - tipo de linea ( 'v'ertical , 'h'orizontal, 'b'oth)
 * 
 * @return int - retorna 1 si se puedo realizar la operacion, 0 en caso contrario
 * 
 */
int dibujarLinea(imagen_mapabit**,int, int, uint32_t,char); /*Implementada*/

#endif /*Fin E_LINEAS_H*/
