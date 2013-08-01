/*
 *      e_redimensionar.c
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
 *      Descripción: Implementacion de las funciones para redimensionar
 *                   una imagen_mapabit.
 */


#include "e_redimensionar.h"

#ifndef E_REDIMENSIONAR_C
#define E_REDIMENSIONAR_C



/*Prototipo para funciones de dimension*/
int dimensionar_1(mapa_t *, uint32_t, uint32_t, uint16_t);
int dimensionar_4(mapa_t *, uint32_t, uint32_t, uint16_t);
int dimensionar_8(mapa_t *, uint32_t, uint32_t, uint16_t);
int dimensionar_16(mapa_t *, uint32_t, uint32_t, uint16_t);
int dimensionar_24(mapa_t *, uint32_t, uint32_t, uint16_t);
int dimensionar_32(mapa_t *, uint32_t, uint32_t, uint16_t);

/*Prototipo para funciones de dimension*/
int dimensionar_mapa(mapa_t *, uint32_t, uint32_t, uint16_t, int \
                      (*)(mapa_t *, uint32_t, uint32_t, uint16_t));

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
int redimension(imagen_mapabit** imagen, uint16_t porcentaje)
{
   int result =0;  
   /*Puntero para la ejecucion de la funcion correcta
     para la redimension*/
   int (*func)(mapa_t *, uint32_t, uint32_t, uint16_t);
   switch ((*imagen)->bitCount)
   {
       case 1:func = dimensionar_1;
              break;
       case 4:func = dimensionar_4;
              break;
       case 8:func = dimensionar_8;
              break;
       case 16:func = dimensionar_16;
               break;
       case 24:func = dimensionar_24;
               break;
       case 32:func = dimensionar_32;
               break;
      default: return 0;
   }
 
   result = dimensionar_mapa( &(*imagen)->mapa, (*imagen)->width, (*imagen)->height, porcentaje, func);
   (*imagen)->width=(uint32_t)(porcentaje*(*imagen)->width)/100;
   (*imagen)->height=(uint32_t)(porcentaje*(*imagen)->height)/100;
      
   return result;
   
}



/*
 * Implementacion para funciones de dimension
 *  
 * name dimensionar_X
 *   Redimensiona una mapabit de X bitCount.
 *   reallocando memoria para guardar el resultado.
 * 
 * @param mapa_t * - Mapa para la redimension.
 * @param uint32_t - Ancho del mapa.
 * @param uint32_t - Alto del mapa.
 * @param uint16_t - Porcentaje a redimension.
 * 
 * @return int - Rotorna 1 si se pudo redimensionar, 0 en caso contrario.
 * 
 */
int dimensionar_1(mapa_t *mapa, uint32_t w, uint32_t h, uint16_t por)
{
   int c, f;
   uint32_t pos;
   /*Calculo del nuevo porcentaje.*/
   uint32_t tamw=(uint32_t)(por*w)/100;
   uint32_t tamh=(uint32_t)(por*h)/100;


   /*Variables, utilizadas para ubicar el pixel de la imagen original para luego
     calcular el promedio.*/
   double vc=(double)tamw/w;
   double vf=(double)tamh/h;

   pixel_1 *matrix;

   matrix=(pixel_1*)malloc((tamw*tamh)*sizeof(pixel_1));

   for(f=0;f<tamh;f++)
   {
     for(c=0;c<tamw;c++)
     {
       pos =c+(f*tamw);
       (matrix+pos)->p=promPixels(mapa, w, h, 1, c/vc, f/vf, 1);
       
     }
   }
              
   free(mapa->map_1); /*Se libera memoria.*/
   mapa->map_1=matrix;

   return 1;

}/*Fin dimensionar_1*/

int dimensionar_4(mapa_t *mapa, uint32_t w, uint32_t h, uint16_t por)
{
   int c, f;
   uint32_t pos;
   /*Calculo del nuevo porcentaje.*/
   uint32_t tamw=(uint32_t)(por*w)/100;
   uint32_t tamh=(uint32_t)(por*h)/100;

   /*Variables, utilizadas para ubicar el pixel de la imagen original para luego
     calcular el promedio.*/
   double vc=(double)tamw/w;
   double vf=(double)tamh/h;

   pixel_4  *matrix;

   matrix=(pixel_4*)malloc((tamw*tamh)*sizeof(pixel_4));

   for(f=0;f<tamh;f++)
   {
     for(c=0;c<tamw;c++)
     {
       pos =c+(f*tamw);
       (matrix+pos)->p=(uint8_t)promPixels(mapa, w, h, 4, c/vc, f/vf, 1);
   
     }
   }
              
   free(mapa->map_4); /*Se libera memoria.*/
   mapa->map_4=matrix;
   
   return 1;
   
}/*Fin dimensionar_4*/

int dimensionar_8(mapa_t *mapa, uint32_t w, uint32_t h, uint16_t por)
{
   int c, f;
   uint32_t pos;
   /*Calculo del nuevo porcentaje.*/
   uint32_t tamw=(uint32_t)(por*w)/100;
   uint32_t tamh=(uint32_t)(por*h)/100;

   /*Variables, utilizadas para ubicar el pixel de la imagen original para luego
     calcular el promedio.*/
   double vc=(double)tamw/w;
   double vf=(double)tamh/h;

   pixel_8  *matrix;

   matrix=(pixel_8*)malloc((tamw*tamh)*sizeof(pixel_8));

   for(f=0;f<tamh;f++)
   {
     for(c=0;c<tamw;c++)
     {
       pos =c+(f*tamw);
       (matrix+pos)->g=(uint8_t)promPixels(mapa, w, h, 8, c/vc, f/vf, 1);
     }
   }
              
   free(mapa->map_8); /*Se libera memoria.*/
   mapa->map_8=matrix;
   
  return 1;
   
}/*Fin dimensionar_8*/

int dimensionar_16(mapa_t *mapa, uint32_t w, uint32_t h, uint16_t por)
{
   int c, f;
   uint32_t pos, prom;
   /*Calculo del nuevo porcentaje.*/
   uint32_t tamw=(uint32_t)(por*w)/100;
   uint32_t tamh=(uint32_t)(por*h)/100;


   /*Variables, utilizadas para ubicar el pixel de la imagen original para luego
     calcular el promedio.*/
   double vc=(double)tamw/w;
   double vf=(double)tamh/h;

   pixel_16  *matrix;

   matrix=(pixel_16*)malloc((tamw*tamh)*sizeof(pixel_16));

   for(f=0;f<tamh;f++)
   {
     for(c=0;c<tamw;c++)
     {
       pos =c+(f*tamw);
       prom=promPixels(mapa, w, h, 16, c/vc, f/vf, 1);
       (matrix+pos)->r= R16(prom);
       (matrix+pos)->g= G16(prom);
       (matrix+pos)->b= B16(prom);

     }
   }
              
   free(mapa->map_16); /*Se libera memoria.*/
   mapa->map_16=matrix;

   return 1;

}/*Fin 16*/

int dimensionar_24(mapa_t *mapa, uint32_t w, uint32_t h, uint16_t por)
{

   int c, f;
   uint32_t pos, prom;
    
   /*Calculo del nuevo porcentaje.*/
   uint32_t tamw=(uint32_t)(por*w)/100;
   uint32_t tamh=(uint32_t)(por*h)/100;

   /*Variables, utilizadas para ubicar el pixel de la imagen original para luego
     calcular el promedio.*/
   double vc=(double)tamw/w;
   double vf=(double)tamh/h;

   pixel_24  *matrix;

   matrix=(pixel_24*)malloc((tamw*tamh)*sizeof(pixel_24));



   for(f=0;f<tamh;f++)
   {
     for(c=0;c<tamw;c++)
     {
       
       pos =c+(f*tamw);
       prom=promPixels(mapa, w, h, 24, c/vc, f/vf, 1);
       (matrix+pos)->r= R(prom);
       (matrix+pos)->g= G(prom);
       (matrix+pos)->b= B(prom);

     }
   }
              
   free(mapa->map_24); /*Se libera memoria.*/
   mapa->map_24 = matrix;

   return 1;

}/*Fin dimensionar_24*/

int dimensionar_32(mapa_t *mapa, uint32_t w, uint32_t h, uint16_t por)
{
   int c, f;
   uint32_t pos, prom;
   /*Calculo del nuevo porcentaje.*/
   uint32_t tamw=(uint32_t)(por*w)/100;
   uint32_t tamh=(uint32_t)(por*h)/100;

   /*Variables, utilizadas para ubicar el pixel de la imagen original para luego
     calcular el promedio.*/
   double vc=(double)tamw/w;
   double vf=(double)tamh/h;

   pixel_32  *matrix;

   matrix=(pixel_32*)malloc((tamw*tamh)*sizeof(pixel_32));

   for(f=0;f<tamh;f++)
   {
     for(c=0;c<tamw;c++)
     {
       pos =c+(f*tamw);
       prom=promPixels(mapa, w, h, 32, c/vc, f/vf, 1);
       (matrix+pos)->c= C(prom);
       (matrix+pos)->m= M(prom);
       (matrix+pos)->y= Y(prom);
       (matrix+pos)->k= K(prom);

     }
   }
              
   free(mapa->map_32); /*Se libera memoria.*/
   mapa->map_32=matrix;
   
   return 1;
   
}/*Fin dimensionar_32*/

/*Implementacion para funciones de dimension*/
int dimensionar_mapa(mapa_t *mapa, uint32_t w, uint32_t h, uint16_t por, int \
                      (*dimensionar)(mapa_t *, uint32_t, uint32_t, uint16_t))
{
   return dimensionar(mapa, w, h, por);
} /*Fin dimensionar_mapa*/



#endif /*E_REDIMENSIONAR*/
