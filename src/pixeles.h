/*
 *      pixeles.h
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
 *      Descripción: 
 *            pixel:Menor unidad posible con la que se compone cualquier 
 *                  imagen digital en una computadora.
 *                  
 *                  Este archivo contiene las Estructuras para el manejo
 *                  de pixeles. Contiene las definiciones de
 *                  pixel monocromo. 1 bit; (blanco y negro)
 *                  pixel Grises. 4 bits; (16 colores)
 *                  pixel Grises. 8 bits; (256 colores)
 *                  pixel RGB16. 2 Bytes; (high color)
 *                  pixel RGB. 3 Bytes;   (True color) en RGB
 *                  pixel CMYK. 4 Bytes;  (True color) en CMYK
 *                  
 */


#include <stdint.h> 


#ifndef PIXELES_H
#define PIXELES_H

/*
 * Monocromo.
 *
 * Estructura que representa un bit.
 * si bien esta definida con un unsigned char,
 * esta puede tomar los valores 1 o 0 logicamente hablando.
 *
 */

typedef struct
{
   uint8_t p; /*1 bits*/
} pixel_1;

/*
 * Grises.
 *
 * Estructura que representa un pixel de 4 bits.
 * si bien esta definida con un unsigned char,
 * esta usa 4 bits (los menos representativos).
 *
 */

typedef struct
{
   uint8_t p; /*4 bits*/
} pixel_4;

/*
 * 256 colores.
 *
 * Estructura que representa un byte por pixel.
 */
typedef struct
{
   uint8_t g; /*8 bits*/
} pixel_8;


/*
 * 2^16 colores. (high color)
 *
 * Representa  16 bit por pixeles.
 */
typedef struct
{
   uint8_t r; /*5 bits*/
   uint8_t g; /*6 bits*/
   uint8_t b; /*5 bits*/

} pixel_16;


/*
 * 2^24 colores. (true color) 
 *
 * Representa 24 bits por pixel.
 * Paleta: RGB (rojo, verde, azul)
 */
typedef struct
{
   uint8_t b; /*8 bits*/
   uint8_t g; /*8 bits*/
   uint8_t r; /*8 bits*/
} pixel_24;

/*
 * 2^32 colores. (true color)
 *
 * Representa 32 bits por pixel.
 * paleta: CMYK (cian, magenta, amarillo, clave)
 */
typedef struct
{
   uint8_t c; /*8 bits*/
   uint8_t m; /*8 bits*/
   uint8_t y; /*8 bits*/
   uint8_t k; /*8 bits*/

} pixel_32;

#endif /*PIXELES_H*/

