/*
 *      e_rotar.c
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
 *      Descripción: Implementacion de las funciones para el ratado
 *                   de una imagen_mapabit.
 */


#include "e_rotar.h"

#ifndef E_ROTAR
#define E_ROTAR

/*Prototipo para funciones para el rotado*/
int rotar_1(mapa_t *, uint32_t, uint32_t, uint32_t (*)(int, int, uint32_t, uint32_t));
int rotar_4(mapa_t *, uint32_t, uint32_t, uint32_t (*)(int, int, uint32_t, uint32_t));
int rotar_8(mapa_t *, uint32_t, uint32_t, uint32_t (*)(int, int, uint32_t, uint32_t));
int rotar_16(mapa_t *, uint32_t, uint32_t, uint32_t (*)(int, int, uint32_t, uint32_t));
int rotar_24(mapa_t *, uint32_t, uint32_t, uint32_t (*)(int, int, uint32_t, uint32_t));
int rotar_32(mapa_t *, uint32_t, uint32_t, uint32_t (*)(int, int, uint32_t, uint32_t));

/*Prototipo para funciones para el rotado*/
int rotar_mapa(mapa_t *, uint32_t, uint32_t, uint32_t (*)(int, int, uint32_t, uint32_t), \
             int (*)(mapa_t *, uint32_t, uint32_t, uint32_t (*)(int, int, uint32_t, uint32_t)));

/*Prototipo para funciones para el calculo de posicion*/
uint32_t c_angulo_90h(int, int, uint32_t, uint32_t);
uint32_t c_angulo_90a(int, int, uint32_t, uint32_t);
uint32_t c_angulo_180(int, int, uint32_t, uint32_t);

uint32_t c_angulo(int, int, uint32_t, uint32_t, uint32_t (*)(int, int, uint32_t, uint32_t));

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
int rotar(imagen_mapabit** imagen,int angulo)
{
  int result=0;
   /*Puntero a funcion que rotara el mapa.*/
   int (*frot)(mapa_t *, uint32_t, uint32_t, uint32_t (*)(int, int, uint32_t, uint32_t));
   /*Puntero a la funcion que devulve el calculo de la nueva
     posicion del pixel dentro del mapa.*/
   
   uint32_t (*ang)(int, int, uint32_t, uint32_t);

   if (angulo == 180)
   {
     ang = c_angulo_180;
   }
     else if (angulo == -90)
     {
       ang = c_angulo_90a;
     }
      else
      {
        ang = c_angulo_90h;
      }
   

   switch ((*imagen)->bitCount)
   {
       case 1:frot = rotar_1;
              break;
       case 4:frot = rotar_4;
              break;
       case 8:frot = rotar_8;
              break;
       case 16:frot = rotar_16;
               break;
       case 24:frot = rotar_24;
               break;
       case 32:frot = rotar_32;
               break;
       default: return 0;
   }
   
   uint32_t w = (*imagen)->width;
   uint32_t h = (*imagen)->height;
   
  result =  rotar_mapa(&(*imagen)->mapa, w, h, ang, frot);

 if(angulo != 180)
 {
    (*imagen)->width=h;
    (*imagen)->height=w;
 }
 
 return result;
}


/*
 * Implementacion para funciones para el rotado
 *  
 * name rotar_X
 *   Rota el mapa de X bitCount
 * 
 * @param mapa_t * - Mapa para el rotado
 * @param uint32_t - ancho del mapa.
 * @param uint32_t - alto del mapa.
 * 
 * //Funcion para el calculo de la nueva posicion 
 * //dependiendo del angulo.
 * @param uint32_t (*ang)(int, int, uint32_t, uint32_t) 
 *                   
 * 
 * @return int - Retorna 1 si se pudo rotar, 0 en caso contrario.
 * 
 */

int rotar_1(mapa_t *mapa, uint32_t w, uint32_t h, uint32_t (*ang)(int, int, uint32_t, uint32_t))
{
   int c, f, pos, post;
   pos=0;
   post=0;

  pixel_1 *inicio = mapa->map_1;
   pixel_1 *matrix = (pixel_1*)malloc((w*h)*sizeof(pixel_1));

   for(f=0;f<h;f++) /*Se copia*/
   {
     for(c=0;c<w;c++)
     {
        pos = c+(f*w); 
        *(matrix+pos) = *(inicio+pos);
      }
    }
    if (ang == c_angulo_180)
    {
      for(f=0;f<h;f++)  /*Se rota*/
      {
        for(c=0;c<w;c++)
        {
          pos = ang( c, f, w, h);
          post = c+(f*w);
          *(inicio+post) = *(matrix+pos);
  
        }
       }
     }
     else
     {
       for(f=0;f<w;f++)  /*Se rota*/
       {
         for(c=0;c<h;c++)
         {
           pos = ang( c, f, w, h);
           post = c+(f*h);
           *(inicio+post) = *(matrix+pos);

         }
       }
     }
     
return 1;
     
} /*Fin rotar_1*/

int rotar_4(mapa_t *mapa, uint32_t w, uint32_t h, uint32_t (*ang)(int, int, uint32_t, uint32_t))
{
   int c, f, pos, post;
   pos=0;
   post=0;

   pixel_4 *inicio = mapa->map_4;
   pixel_4 *matrix = (pixel_4*)malloc((w*h)*sizeof(pixel_4));

   for(f=0;f<h;f++)  /*Se copia*/
   {
     for(c=0;c<w;c++)
     {
        pos = c+(f*w); 
        *(matrix+pos) = *(inicio+pos);
      }
    }
    if (ang == c_angulo_180)
    {
      for(f=0;f<h;f++)  /*Se rota*/
      {
        for(c=0;c<w;c++)
        {
          pos = ang( c, f, w, h);
          post = c+(f*w);
          *(inicio+post) = *(matrix+pos);

        }
       }
     }
     else
     {
       for(f=0;f<w;f++)  /*Se rota*/
       {
         for(c=0;c<h;c++)
         {
           pos = ang( c, f, w, h);
           post = c+(f*h);
           *(inicio+post) = *(matrix+pos);

         }
       }
     }

return 1;
     
} /*Fin rotar_4*/

int rotar_8(mapa_t *mapa, uint32_t w, uint32_t h, uint32_t (*ang)(int, int, uint32_t, uint32_t))
{
   int c, f, pos, post;
   pos=0;
   post=0;

   pixel_8 *inicio = mapa->map_8;
   pixel_8 *matrix = (pixel_8*)malloc((w*h)*sizeof(pixel_8));

   for(f=0;f<h;f++)  /*Se copia*/
   {
     for(c=0;c<w;c++)
     {
        pos = c+(f*w); 
        *(matrix+pos) = *(inicio+pos);
      }
   }
    if (ang == c_angulo_180)
    {
      for(f=0;f<h;f++)  /*Se rota*/
      {
        for(c=0;c<w;c++)
        {
          pos = ang( c, f, w, h);
          post = c+(f*w);
          *(inicio+post) = *(matrix+pos);

        }
       }
     }
     else
     {
       for(f=0;f<w;f++)  /*Se rota*/
       {
         for(c=0;c<h;c++)
         {
           pos = ang( c, f, w, h);
           post = c+(f*h);
           *(inicio+post) = *(matrix+pos);

         }
       }
     }

return 1;

} /*Fin rotar_8*/

int rotar_16(mapa_t *mapa, uint32_t w, uint32_t h, uint32_t (*ang)(int, int, uint32_t, uint32_t))
{
   int c, f, pos, post;
   pos=0;
   post=0;


   pixel_16 *inicio = mapa->map_16;
   pixel_16 *matrix = (pixel_16*)malloc((w*h)*sizeof(pixel_16));

   for(f=0;f<h;f++)  /*Se copia*/
   {
     for(c=0;c<w;c++)
     {
        pos = c+(f*w); 
        *(matrix+pos) = *(inicio+pos);
      }
    }
    if (ang == c_angulo_180)
    {
      for(f=0;f<h;f++)  /*Se rota*/
      {
        for(c=0;c<w;c++)
        {
          pos = ang( c, f, w, h);
          post = c+(f*w);
          *(inicio+post) = *(matrix+pos);
          
        }
       }
     }
     else
     {
       for(f=0;f<w;f++)  /*Se rota*/
       {
         for(c=0;c<h;c++)
         {
           pos = ang( c, f, w, h);
           post = c+(f*h);
           *(inicio+post) = *(matrix+pos);
           
         }
       }
     }

return 1;

} /*Fin rotar_16*/

int rotar_24(mapa_t *mapa, uint32_t w, uint32_t h, uint32_t (*ang)(int, int, uint32_t, uint32_t))
{
   int c, f, pos, post;
   pos=0;
   post=0;

   pixel_24 *inicio = mapa->map_24;
   pixel_24 *matrix = (pixel_24*)malloc((w*h)*sizeof(pixel_24));

   for(f=0;f<h;f++)  /*Se copia*/
   {
     for(c=0;c<w;c++)
     {
        pos = c+(f*w); 
        *(matrix+pos) = *(inicio+pos);
      }
    }
    if (ang == c_angulo_180)
    {
      for(f=0;f<h;f++)  /*Se rota*/
      {
        for(c=0;c<w;c++)
        {
          
          pos = ang( c, f, w, h);
          post = c+(f*w);
          *(inicio+post) = *(matrix+pos);
   
         
        }
       }
     }
     else
     {
       for(f=0;f<w;f++)  /*Se rota*/
       {
         for(c=0;c<h;c++)
         {
           
           pos = ang( c, f, w, h);
           post = c+(f*h);
           *(inicio+post) = *(matrix+pos);

           
         }
       }
     }

return 1;

} /*Fin rotar_24*/

int rotar_32(mapa_t *mapa, uint32_t w, uint32_t h, uint32_t (*ang)(int, int, uint32_t, uint32_t))
{
   int c, f, pos, post;
   pos=0;
   post=0;
   pixel_32 *inicio = mapa->map_32;
   pixel_32 *matrix = (pixel_32*)malloc((w*h)*sizeof(pixel_32));

   for(f=0;f<h;f++)  /*Se copia*/
   {
     for(c=0;c<w;c++)
     {
        pos = c+(f*w); 
        *(matrix+pos) = *(inicio+pos);
      }
    }
    if (ang == c_angulo_180)
    {
      for(f=0;f<h;f++)  /*Se rota*/
      {
        for(c=0;c<w;c++)
        {
          pos = ang( c, f, w, h);
          post = c+(f*w);
          *(inicio+post) = *(matrix+pos);

          
        }
       }
     }
     else
     {
       for(f=0;f<w;f++)  /*Se rota*/
       {
         for(c=0;c<h;c++)
         {
           pos = ang( c, f, w, h);
           post = c+(f*h);
           *(inicio+post) = *(matrix+pos);

         }
       }
     }

  return 1;

} /*Fin rotar_32*/


/*Implementacion para funciones para el rotado*/
int rotar_mapa(mapa_t *mapa, uint32_t w, uint32_t h, uint32_t (*ang)(int, int, uint32_t, uint32_t), \
                int (*func)(mapa_t *, uint32_t, uint32_t, uint32_t (*)(int, int, uint32_t, uint32_t)))
{
      return func(mapa, w, h, ang);
} /*Fin rotar_mapa*/


/*
 *
 * Implementacion para funciones para el calculo de posicion
 *  
 * name c_angulo_XX
 *   Calculo de la nueva posicion en el mapa para el angulo XX
 * 
 * @param int - Columna para el calculo
 * @param int - Fila para el calculo
 * @param uint32_t - Ancho del mapa al cual se le esta aplicando el rotado 
 * @param uint32_t - Alto del mapa al cual se le esta aplicando el rotado
 * 
 * @return uint32_t - Nueva posicion en el mapa.
 * 
 */

uint32_t c_angulo_90h(int c, int f, uint32_t w, uint32_t h)
{
  return (f+(((h-1)-c)*w));
} /*Fin c_angulo_90h*/

uint32_t c_angulo_90a(int c, int f, uint32_t w, uint32_t h)
{
  return (((w-1)-f)+(c*w));
} /*Fin c_angulo_90a*/

uint32_t c_angulo_180(int c, int f, uint32_t w, uint32_t h)
{
  return (((w-1)-c)+(((h-1)-f)*w));
} /*Fin c_angulo_180*/

#endif /*E_ROTAR*/
