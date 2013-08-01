/*
 *      e_rotar.h
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
 *      Descripción: Rota una imgen_mapabit, a un angulo dado,
 *                   los posibles son 90 horario y anti-horario
 *                   y 180.
 */



#include <stdio.h>
#include <stdlib.h>
#include "bitmaps.h"


#ifndef E_ROTAR_H
#define E_ROTAR_H

/*
 * 
 * name rotar
 *   Rota una imagen de mapa bit a un angulo dado
 *   estos pueden ser 90, -90 o 180.
 * 
 * @param imagen_mapabit** - Imagen para el rotar.
 * @param int - Angulo de rotacion (90, -90 o 180).
 * 
 * @return int - Retorna 1 si se pudo rotar, 0 en caso contrario.
 * 
 */
int rotar(imagen_mapabit**,int); /*Implementada*/

#endif /*Fin E_ROTAR_H*/
