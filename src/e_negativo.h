/*
 *      e_negativo.h
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
 *      Descripción: Crea el efecto negativo en una imagen_mapa bit
 *                   este consiste en setear para cada pixel el
 *                   el valor mayor que puede tomar menos el valor 
 *                   actual, esto para las imagenes de bitCount > 8
 *                   de lo contrario se modificara la paleta de la imagen
 *                   esto hay que tenerlo en cuenta ya que hay que se debe
 *                   conocer la paleta de la imgen tambien, la forma es la misma
 *                   para cada pixel  de la paleta se setea con el mayor 
 *                   valor posible menos el valor actual.
 */ 


#include <stdio.h>
#include <stdlib.h>
#include "bitmaps.h"


#ifndef E_NEGATIVO_H
#define E_NEGATIVO_H
/*
 * 
 * name negativo
 *   Crea el efecto negativo en la imagen_mapabit.
 *   Recuerde que se debe pasar la paleta de la misma
 *   para las imagenes bitCount <=8.
 * 
 * @param imagen_mapabit** - Imagen  la cual se aplicara el efecto
 * 
 * @return int - Retorna 1 si se logro el efecto, 0 en caso contrario
 * 
 */
int negativo(imagen_mapabit**); /*Implementada*/

#endif /*Fin E_NEGATIVO_H*/
