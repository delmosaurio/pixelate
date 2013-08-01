/*
 *      e_blur.h
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
 *      Descripción: Esta libreria, en conjunto con 'bitmaps' aplica
 *                   un efecto desenfoque (blur) a una imagen_mapabit
 *                   definida en bitmaps.h.
 * 
 *                   El blur consiste en setear para cada pixel
 *                   de la imagen nueva el promedio de pixeles
 *                   de un radio dado que determina el valor del
 *                   efecto.
 *                    
 */

#include <stdio.h>
#include <stdlib.h>
#include "bitmaps.h"


#ifndef E_BLUR_H
#define E_BLUR_H

 /*Menor valor posible para efecto blur*/
 #ifndef LIMITE_MIN_BLUR
  #define LIMITE_MIN_BLUR 1
 #endif

 /*Mayor valor posible para efecto blur*/
 #ifndef LIMITE_MAX_BLUR
  #define LIMITE_MAX_BLUR 250
 #endif

/*
 * 
 * name blur
 *   Aplica un efecto de desenfoque (blur) a una
 *   imagen_mapabit de un radio dado.
 * 
 * @param imagen_mapabit** - Imagen a la cual se aplicara el efecto.
 * @param int - Radio del efecto.
 * 
 * @return int - retorna 1 si la operacion pudo realizarse o 0 en caso contrario
 * 
 */
int blur(imagen_mapabit**, int); /*Implementada*/

#endif
