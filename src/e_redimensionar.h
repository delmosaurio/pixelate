/*
 *      e_redimensionar.h
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
 *      Descripción: Redimensiona una imgen_mapabit a un porcentaje
 *                   dado, los limites de la nueva resolucion, estan
 *                   definidos a contunuacion.
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include "bitmaps.h"


#ifndef E_REDIMENSIONAR_H
#define E_REDIMENSIONAR_H

 #ifndef MAX_DIMENSION
  #define MAX_DIMENSION 20000
 #endif

 #ifndef MIN_DIMENSION
  #define MIN_DIMENSION 10
 #endif
 
 
/*
 * 
 * name redimension
 *   Redimensionar una imagen_mapabit a un porcentaje dado.
 * 
 * @param imagen_mapabit** - Imagen para la redimension.
 * @param uint16_t - porcentaje para la redimension.
 * 
 * @return int - Retorna 1 si se pudo redimensionar, 0 en caso contrario.
 * 
 */
int redimension(imagen_mapabit**, uint16_t); /*Implementada*/

#endif /*Fin E_REDIMENSIONAR_H*/
