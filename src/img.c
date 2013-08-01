/*
 *      img.c
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
 *      Descripción: En esta libreria estan desarroladas las funciones,
 *                   para hacer un puente entre un archivo de imagen y
 *                   con la manipulacion de esta.
 */

#include "img.h"

#ifndef IMG_C
#define IMG_C


/*
 * 
 * name img_obtener_ext
 *   Esta funcion obtiene la extension de un archivo de imagen 
 *   desde una cadena.
 * 
 * @param char* - cadena donde se extraera la extension.
 * 
 * @return int - retorna el codigo de la extension, en caso de que no exista retorna -1
 * 
 */
int img_obtener_ext(char* cad)
{
   char* ext = strrchr(cad, 46); /*Obtenemos la direccion del ultimo punto en la cadena*/
   
   if (ext != NULL) /*Si existe un punto.
   Consultamos de que tipo de extension estamos hablando.*/
   {
    
     if( (strcmp(ext, ".bmp")==0) )
       return COD_BMP;
    
     if( (strcmp(ext, ".jpg")==0) || (strcmp(ext, ".jpeg")==0))
       return COD_JPG;
     
     if( (strcmp(ext, ".png")==0) )
       return COD_PNG;
   }
   
   return -1;
}

/*
 * 
 * name img_extraer_encabezado
 *   Esta funcion es la encargada de ejecutar la funcion correcta
 *   para la extraccion de un encabezado de imagen.
 * 
 * @param FILE* - Archivo del cual se extraera el encabezado
 * @param int - codigo de extension
 * @param ... Este parametro va a depender del tipo de codigo de extecion.
 *            Si estamos en un bmp, este recibira un encabezado de bmp
 *            y asi con las demas extensiones.
 * 
 * @return int retorna 1 si la operacion pudo realizarse o 0 en caso contrario
 * 
 */
int img_extraer_encabezado(FILE* archivo, int cod, ...)
{
    va_list pa;
    va_start(pa, cod);
    
    switch(cod)
    {
      case COD_BMP:{
                      _BMP_Header *encabezado;
                      encabezado = va_arg(pa, _BMP_Header*);
                      *encabezado = _BMP_extraerEncabezado(archivo);
                      va_end(pa);
                      return 1;
                   }
      case COD_JPG:
      case COD_PNG:
      default: printf("Extension no soportada.\n");
               return 0;
    }
}


  
/*
 * 
 * name img_extraer_mapa
 *   Es el puente entre la funcion de la extraccion de un mapa bit
 *   de un archivo de imagen con la imgen_mapabit, por ejemplo, si el 
 *   archivo de imagen es un bmp, llamara a la funcion para la extraccion
 *   del mapa bit de un bmp.
 * 
 * @param FILE* - archivo del cual se extraera el mapa.
 * @param imagen_mapabit ** - lugar donde se guardara el mapa.
 * @param int - codigo de extension. (definidos en el encabezado de la libreria)
 * @param ... - Este parametro va a depender del tipo de codigo de extecion.
 *              Si estamos en un bmp, este recibira un encabezado de bmp
 *              y asi con las demas extensiones.
 * 
 * @return imagen_mapabit - imagen_mapabit extraido.
 * 
 */
imagen_mapabit *img_extraer_mapa(FILE* archivo, imagen_mapabit **imagen, int cod, ...)
{
    va_list pa;
    va_start(pa, cod);
    
    switch(cod)
    {
      case COD_BMP:{
                      _BMP_Header *encabezado;
                      encabezado = va_arg(pa, _BMP_Header*);
                      va_end(pa);
                      if (*imagen == NULL)
                      {
                        *imagen = (imagen_mapabit*)malloc(sizeof(imagen_mapabit));
                        *(*imagen) = _BMP_extraerMapabit(archivo , *encabezado);
                      }
                      return *imagen;
                   }
      case COD_JPG:
      case COD_PNG:
      default: printf("Extension no soportada.\n");
               return NULL;
    }
}

/*
 * 
 * name img_guardar
 *   Esta funcion llamara a las funcionesmo correspondientes al tipo de archivo
 *   conocido por el codigo de extension, para guardar el encabezado y el mapa de bit
 *   en el archivo.
 *  
 * 
 * @param FILE* - Archivo donde se guardara el mapabit
 * @param imagen_mapabit ** - imagen a guardar
 * @param int - codigo de extension
 * @param ... Este parametro dependera de cod, por ejemplo,
 *            si se quiere guardar una imagen bmp, se recibira el 
 *            encabezado del mismo.
 * 
 * @return int - Retorna 1 si la operacion fue correcta, 0 en caso contrario.
 * 
 */
int img_guardar(FILE* archivo, imagen_mapabit **imagen, int cod, ...)
{

    va_list pa;
    va_start(pa, cod);
    
    switch(cod)
    {
      case COD_BMP:{
                      int result;
                      _BMP_Header *encabezado = va_arg(pa, _BMP_Header*);
                      int offSet = encabezado->encabezado.offSet;
                      
                      va_end(pa);
                      if (*imagen==NULL) return 0;
                      
                      result = _BMP_guardarEncabezado(archivo, *encabezado);
                      result = _BMP_guardarMapabit(archivo , *imagen, offSet);
                      
                      return result;
                   }
      case COD_JPG:
      case COD_PNG:
      default: printf("Extension no soportada.\n");
               return 0;
    }
}

/*
 * 
 * name img_mostrar_encabezado
 *   Muetra en encabezado de un archivo de imagen.
 * 
 * @param int - Condigo de extension
 * @param ... - Estructuras necesarias para mostrar el encabezado del archivo de
 *              imagen del tipo Cod
 * 
 * @return int - Retorna 1 si la operacion fue correcta, 0 en caso contrario.
 * 
 */
int img_mostrar_encabezado(int cod, ...)
{
    va_list pa;
    va_start(pa, cod);
    
    switch(cod)
    {
      case COD_BMP:{
                      _BMP_Header *encabezado;
                      char* name;
                      encabezado = va_arg(pa, _BMP_Header*);
                      name = va_arg(pa, char*);
                      va_end(pa);
                      return _BMP_imprimirEncabezado(*encabezado, name);
                   }
      case COD_JPG:
      case COD_PNG:
      default: printf("Extension no soportada.\n");
               return 0;
    }
}

/*
 * 
 * name img_efecto
 *   Aplica el efecto definido por el codigo de efecto.
 *   Los codigos de efecto.
 * 
 * @param imagen_mapabit ** - Imagen a la que se aplicara el efecto.
 * @param int - codigo de extension.
 * @param ... - Este parametro recibira las estructuras que se tengan
 *              que modificar junto con el efecto, ejemplo, el encabezado
 *              de un bmp cuando se rota.
 *              
 * @return int - Retorna 1 si la pudo hacer la operacion, 0 de lo contrario.
 * 
 */
int img_efecto(imagen_mapabit **imagen, int cod, ...)
{
    va_list pa;
    va_start(pa, cod);
    
    if (*imagen==NULL)
    {
      printf("No hay mapa bit al cual aplicar efecto.");
      return 0;
    }
    
    switch(cod)
    {
      case EFECTO_BLUR:{
          int radio = va_arg(pa, int);
          if (radio<LIMITE_MIN_BLUR || radio>LIMITE_MAX_BLUR)
          {
            printf("Efecto blur fuera de los limites.");
            return 0;
          }
          return blur(imagen, radio);
       }
      case EFECTO_LINEAS:{
         int ancho = va_arg(pa, int);
         int espacio = va_arg(pa, int);
         uint32_t color = va_arg(pa, uint32_t);
         char tipo = va_arg(pa, int);
         tipo=(tipo=='V')?'v':tipo;
         tipo=(tipo=='H')?'h':tipo;
         tipo=(tipo=='B')?'b':tipo;
         return dibujarLinea(imagen, ancho, espacio, color, tipo);
       }
      case EFECTO_NEGATIVO:{
         return negativo(imagen);
      }
      case EFECTO_REDIMENSION:{
         int result=0;
         int por= va_arg(pa, int);
         int cod_ext=va_arg(pa, int);
         _BMP_Header *encabezado= va_arg(pa, _BMP_Header*);
         va_end(pa);
         
         uint32_t wa = (*imagen)->width;
         uint32_t ha = (*imagen)->height;
         uint16_t bc = (*imagen)->bitCount;
         
         if (wa > ha)
         {
           if ( ( ((uint32_t)(por * wa)/100) > MAX_DIMENSION ) || ( ((uint32_t)(por * ha)/100) < MIN_DIMENSION ) )
           {
             printf("Porcentaje fuera de los limites.");
             return 0;
           }
         }
         else
         {
           if ( ( ((uint32_t)(por * ha)/100) > MAX_DIMENSION ) || ( ((uint32_t)(por * wa)/100) < MIN_DIMENSION ) )
           {
             printf("Porcentaje fuera de los limites.");
             return 0;
           }
         }
         result = redimension(imagen, por);
        switch (cod_ext)
        {
          case COD_BMP:{
                           if(result)
                           {                                 
                             uint32_t dxw=(uint32_t)(por*wa)/100;
                             uint32_t dxh=(uint32_t)(por*ha)/100;
                             encabezado->infoEncabezado.width =dxw;
                             encabezado->infoEncabezado.height =dxh;
                             encabezado->infoEncabezado.xPixelsPerM *=(por*encabezado->infoEncabezado.xPixelsPerM)/100;
                             encabezado->infoEncabezado.yPixelsPerM *=(por*encabezado->infoEncabezado.yPixelsPerM)/100;
                             uint16_t bcc=bc*wa;
                             (encabezado)->infoEncabezado.imageSize=(bcc+((bcc%32)?(32-(bcc%32)):0))*(ha/8);
                             (encabezado)->encabezado.fileSize=( (encabezado)->infoEncabezado.imageSize ) + ( (encabezado)->encabezado.offSet );
                           }
                        }
                       break;
          case COD_JPG:
          case COD_PNG:
          default: printf("Extension no soportada.\n");
                  return 0;
        }
        return result;
      }
      case EFECTO_ROTAR:{
        int result=0;
        int angulo= va_arg(pa, int);
        int cod_ext=va_arg(pa, int);
       _BMP_Header *encabezado= va_arg(pa, _BMP_Header*);
        va_end(pa);
        
        uint32_t wa = (*imagen)->width;
        uint32_t ha = (*imagen)->height;
        uint16_t bc = (*imagen)->bitCount;
        
        if (angulo != 90 && angulo != -90 && angulo != 180)
        {
          printf("Al angulo %d para el rotado es invalido.", angulo);
          return 0;
        } 
        result = rotar(imagen, angulo);
        
        switch (cod_ext)
        {
          case COD_BMP:{
            if(result && angulo != 180)
            { 
              
              (encabezado)->infoEncabezado.width = ha;
              (encabezado)->infoEncabezado.height= wa;
              uint32_t tempx=(encabezado)->infoEncabezado.xPixelsPerM;
              (encabezado)->infoEncabezado.xPixelsPerM =(encabezado)->infoEncabezado.yPixelsPerM;
              (encabezado)->infoEncabezado.yPixelsPerM = tempx;
              uint16_t bcc=bc*wa;
              (encabezado)->infoEncabezado.imageSize=(bcc+((bcc%32)?(32-(bcc%32)):0))*(ha/8);
              (encabezado)->encabezado.fileSize=( (encabezado)->infoEncabezado.imageSize ) + ( (encabezado)->encabezado.offSet );
            }
           }
           break;
          case COD_JPG:
          case COD_PNG:
          default: printf("Extension no soportada.\n");
                  return 0;
        }

        return result;
      }
      default: printf("Efecto inexistente.");
               return 0;
    }
}


#endif /*Fin IMG_C*/

