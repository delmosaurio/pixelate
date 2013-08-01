/*
 *      e_blur.c
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
 *      Descripción: Implementacion de las funciones para llevar a cabo
 *                   el efecto desenfoque (blur). 
 */


#include "e_blur.h"

#ifndef E_BLUR_C
#define E_BLUR_C



/*Prototipo de la funciones para aplicar blur*/
int blur_1(mapa_t * , uint32_t, uint32_t, int);
int blur_4(mapa_t * , uint32_t, uint32_t, int);
int blur_8(mapa_t * , uint32_t, uint32_t, int);
int blur_16(mapa_t * , uint32_t, uint32_t, int);
int blur_24(mapa_t * , uint32_t, uint32_t, int);
int blur_32(mapa_t * , uint32_t, uint32_t, int);

/*Prototipo de la funcion para aplicar el efecto*/
int aplicar_blur(mapa_t * , uint32_t, uint32_t, int, int (*)(mapa_t * , uint32_t, uint32_t, int));

/*
 * 
 * name blur
 *   Aplica un efecto de desenfoque (blur) a una
 *   imagen_mapabit de un radio dado.
 *   Tiene el trabajo de seleccionar la funcion correcta para
 *   llevar acabo el efecto, esto lo da la cantidad de bit por
 *   pixels de la imagen.
 * 
 * @param imagen_mapabit** - Imagen a la cual se aplicara el efecto.
 * @param int - Radio del efecto.
 * 
 * @return int - retorna 1 si la operacion pudo realizarse o 0 en caso contrario
 * 
 */
int blur(imagen_mapabit** imagen, int radio)
{

   /*Funcion para la ejecucion del efecto
    va a depender del bitCpunt de la imagen.*/
   int (*func)(mapa_t * , uint32_t, uint32_t, int);
   
   
   switch ((*imagen)->bitCount)
   {
     case 1:func = blur_1;
            break;
     case 4:func = blur_4;
            break;
     case 8:func = blur_8;
            break;
     case 16:func = blur_16;
             break;
     case 24:func = blur_24;
             break;
     case 32:func = blur_32;
             break;
     default:return 0;
   }
 
   return aplicar_blur( &(*imagen)->mapa, (*imagen)->width, (*imagen)->height, radio, func);

}

/*
 *  Implementacion de la funciones para aplicar blur
 *  
 * name blur_X
 *   Crea el efecto para la imagen de X bitCount.
 * 
 * @param mapa_t * - Mapa al cual se aplicara el efecto
 * @param uint32_t - ancho del mapa.
 * @param uint32_t - alto del mapa.
 * @param int - radio para el efecto.
 *  
 * @return int - retorna 1 si la operacion pudo realizarse o 0 en caso contrario
 * 
 */
int blur_1(mapa_t *mapa, uint32_t w, uint32_t h, int radio)
{
    int c, f, pos;
    uint32_t prom;
    pixel_1  *matrix, *inicio;
   
    inicio=mapa->map_1;
    matrix=(pixel_1*)malloc((w*h)*sizeof(pixel_1));

    for(f=0;f<h;f++)/*Se recorre.*/
    {
      for(c=0;c<w;c++)
      {
        pos =  (c+(f*w));
        prom=promPixels(mapa, w, h, 1, c, f, radio);/*Se calcula el promedio con la mapa original.*/
        (matrix+pos)->p=(uint8_t)prom; /* Se guarda en el nuevo bitmap.*/
      } 
    }
    free(inicio);
    mapa->map_1 = matrix;

    return 1;

} /*Fn blur_1*/

int blur_4(mapa_t *mapa, uint32_t w, uint32_t h, int radio)
{
    int c, f, pos;
    uint32_t prom;
    pixel_4  *matrix,*inicio;
    
    inicio=mapa->map_4;
    matrix=(pixel_4*)malloc((w*h)*sizeof(pixel_4));

    for(f=0;f<h;f++)
    {
      for(c=0;c<w;c++)
      {
         pos = (c+(f*w)); 
         prom=promPixels(mapa, w, h, 4,c, f, radio);
         (matrix+pos)->p=(uint8_t)prom;
       } 
     }

    free(mapa->map_4);
    mapa->map_4=matrix;

    return 1;

} /*Fn blur_4*/


int blur_8(mapa_t *mapa, uint32_t w, uint32_t h, int radio)
{
    int c, f, pos;
    uint32_t prom;
    pixel_8  *matrix, *inicio;

    inicio=mapa->map_8;
    matrix=(pixel_8*)malloc((w*h)*sizeof(pixel_8));
    for(f=0;f<h;f++)
    {
      for(c=0;c<w;c++)
      {
          pos = (c+(f*w)); 
          prom=promPixels(mapa, w, h, 8, c, f, radio);
          (matrix+pos)->g=(uint8_t)prom;
         
       } 
     }

    free(mapa->map_8); /*Se libera memoria.*/
    mapa->map_8=matrix;

    return 1;

} /*Fn blur_8*/

int blur_16(mapa_t *mapa, uint32_t w, uint32_t h, int radio)
{
    int c, f, pos;
    uint32_t prom;
    pixel_16  *matrix, *inicio;
   
    inicio=mapa->map_16;
    matrix=(pixel_16*)malloc((w*h)*sizeof(pixel_16));

    for(f=0;f<h;f++)
    {
      for(c=0;c<w;c++)
      {
         pos = c+(f*w); 
         prom=promPixels(mapa, w, h, 16, c, f, radio);
         (matrix+pos)->r = R16(prom);
         (matrix+pos)->g = G16(prom);
         (matrix+pos)->b = B16(prom);
         
      }
     }

    free(mapa->map_16); /*Se libera memoria.*/
    mapa->map_16=matrix;

    return 1;

} /*Fn blur_16*/

int blur_24(mapa_t *mapa, uint32_t w, uint32_t h, int radio)
{
    int c, f, pos;
    uint32_t prom;
    pixel_24  *matrix;
    matrix=(pixel_24*)malloc((w*h)*sizeof(pixel_24));
    

     
     for(f=0;f<h;f++)
     {
       for(c=0;c<w;c++)
       {

          pos = c+(f*w); 
          prom=promPixels(mapa, w, h, 24, c, f, radio);
          (matrix+pos)->r = R(prom);
          (matrix+pos)->g = G(prom);
          (matrix+pos)->b = B(prom);
         
        }
      }

    free(mapa->map_24); /*Se libera memoria.*/
    mapa->map_24 = matrix;
    
    return 1;
    
} /*Fn blur_24*/

int blur_32(mapa_t *mapa, uint32_t w, uint32_t h, int radio)
{
    int c, f, pos;
    pixel_32  *matrix, *inicio;
    uint32_t prom;
   
    inicio=mapa->map_32;
    matrix=(pixel_32*)malloc((w*h)*sizeof(pixel_32));

   for(f=0;f<h;f++)
   {
     for(c=0;c<w;c++)
     {
        pos = c+(f*w); 
        prom=promPixels(mapa, w, h, 32, c, f, radio);
		   (matrix+pos)->c = C(prom);
		   (matrix+pos)->m = M(prom);
		   (matrix+pos)->y = Y(prom);
		   (matrix+pos)->k = K(prom);

      } 
    }

    free(mapa->map_32); /*Se libera memoria.*/
    mapa->map_32 = matrix;

    return 1;

} /*Fn blur_32*/

/*Implementacion de la funcion para aplicar el efecto*/
int aplicar_blur(mapa_t *mapa, uint32_t w, uint32_t h, int radio, int (*blur)(mapa_t * , uint32_t, uint32_t, int))
{
    return blur(mapa, w, h, radio);
} /*Fn aplicar_blur*/

#endif /*Fin E_BLUR_C*/
