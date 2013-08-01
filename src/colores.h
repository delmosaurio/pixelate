/*
 *      colores.h
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
 *      Descripción: Contiene Macros para el manejo de los diferentes
 *                   colores de imagenes, asi como la extraccion de
 *                   colores azul, rojo, verde de un color de tipo
 *                   RGB y tambien la union de estos.
 *                   Las paletas soportadas son las de RGB para 24 y 16
 *                   bits y CMYK.
 */



#include <stdint.h> 

#ifndef COLORES_H
#define COLORES_H


/*
 * Este macro obtiene el color Rojo en RGB.
 */
#ifndef R
#define R(color) (uint8_t)((color&0xFF0000)>>16)
#endif

/*
 * Este macro obtiene el color verde en RGB.
 */
#ifndef G
#define G(color) (uint8_t)((color&0xFF00)>>8)
#endif

/*
 * Este macro obtiene el color azul en RGB.
 */
#ifndef B
#define B(color) (uint8_t)(color&0xFF)
#endif

/*
 * Este macro une los colores en RGB.
 */
#ifndef RGB
#define RGB(r, g, b) (uint32_t)((r)<<16 | (g)<<8 | b)
#endif



/*
 * Este macro obtiene el color Rojo en RGB16.
 */
#ifndef R16
#define R16(color) (uint8_t)((color&0xF800)>>11)
#endif

/*
 * Este macro obtiene el color verde en RGB16.
 */
#ifndef G16
#define G16(color) (uint8_t)((color&0x07E0)>>5)
#endif

/*
 * Este macro obtiene el color azul en RGB16.
 */
#ifndef B16
#define B16(color) (uint8_t)(color&0x001F)
#endif

/*
 * Este macro une los colores en RGB.
 */
#ifndef RGB16
#define RGB16(r, g, b) (uint32_t)((r)<<11 | (g)<<5 | b)
#endif


/*
 * Este macro obtiene el color Cian en CMYK.
 */
#ifndef C
#define C(color) (uint8_t)((color&0xFF000000)>>24)
#endif

/*
 * Este macro obtiene el color Magenta en CMYK.
 */
#ifndef M
#define M(color) (uint8_t)((color&0xFF0000)>>16)
#endif

/*
 * Este macro obtiene el color Yellow en CMYK.
 */
#ifndef Y
#define Y(color) (uint8_t)((color&0xFF00)>>8)
#endif

/*
 * Este macro obtiene la Key en CMYK.
 */
#ifndef K
#define K(color) (uint8_t)((color&0xFF))
#endif

/*
 * Este macro une los colores en CMYK.
 */
#ifndef CMYK
#define CMYK(c, m, y, k) (uint32_t)((c)<<24 | (m)<<16 | (y)<<8 | k)
#endif

#endif /*Fin COLORES_H*/
