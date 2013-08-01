/*
 *      main.c - pixelate
 *      
 *      Copyright (c) 2008 Delmo Carrozzo <dcardev@gmail.com>
 *     
 *      pixelate una sencilla interfaz de línea de órdenes para manipular 
 *      archivos de imagenes, desarrollado como trabajo final para la materia
 *      'Seminario de lenguajes - Taller C' de la Universidad Nacional de 
 *      La Plata (UNLP), en su versión 0.5 solo acepta archivos de tipo 
 *      BMP sin compresión.
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
 *      Descripción: Programa principal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "datos.h"
#include "arg_main.h"
#include "img.h"

/*
 * name ayuda(void)
 * 
 * Muestra el texto de ayuda en pantalla.
 * 
 * @param void
 * 
 * @return void
 * 
 */
void ayuda(void)
{
   printf("\n%s es una sencilla interfaz de línea de órdenes para manipular archivos de imagenes\n", PROGRAMA_NOMBRE);
   printf("en su version %s,  solo acepta imagenes de tipo BMP sin compresion.\n\n", PROGRAMA_VERSION);
   printf("Opciones:\n");
   printf("  -? o -h                - Muestra este texto de ayuda.\n");
   printf("  -r                     - Rota la imagen a 90°.\n");
   printf("  -r  N                  - Rota la imagen a N° (90°, -90° ,180°).\n");
   printf("  -n                     - Genera un negativo a la imagen.\n");
   printf("  -d                     - Duplica el tamaño de la imagen.\n");
   printf("  -f                     - Reduce a la mitad el tamaño de la imagen.\n");
   printf("  -x   %%                - Redimensiona la imagen en un porcentaje dado.\n");
   printf("  -b RADIO               - Produce un efecto blur de RADIO pixeles.\n");
   printf("  -lh ANCHO SPACIO COLOR - Dibuja lineas de COLOR horizontales de ANCHO pixeles, \n");
   printf("                           separadas por ESPACIO pixeles.\n");
   printf("  -lv ANCHO SPACIO COLOR - Dibuja lineas verticales de COLOR de ANCHO pixeles,\n");
   printf("                           separadas por ESPACIO pixeles.\n");
   printf("  -lb ANCHO SPACIO COLOR - Dibuja lineas verticales y horizontales de COLOR de ANCHO pixeles,\n");
   printf("                           separadas por ESPACIO pixeles.\n");
   printf("  -o SALIDA              - Especifica el nombre del archivo de imagen salida.\n");
   printf("  -i ENTRADA             - Especifica el nombre del archivo de imagen con el cual se trabajara.\n\n");
}/*Fina ayuda*/

/*
 * Filtrar: Devuelve el primer caracter luego de '-' 
 *          es usado para las estructuras Switch.
 */
char filtrar(char* opcion)
{
  if (strlen(opcion)<1) return 0;
  return (opcion[1]);
}
/*Configuracion de argumentos*/
void configurar_argumentos(argumentos_t *argu)
{
  arg_t aux;
  
  /*Imagen de entrada*/
  aux = arg_nuevo("-i", 1, 1, 1, 0);
  arg_agregar(argu, aux);
  
  /*Rotar*/
  aux = arg_nuevo("-r", 0, 1, 2, 3, "90", "-90", "180");
  arg_agregar(argu, aux);
  
  /*Negativo*/
  aux = arg_nuevo("-n", 0, 0, 2, 0);
  arg_agregar(argu, aux);

  /*Duplicar*/
  aux = arg_nuevo("-d", 0, 0, 2, 0);
  arg_agregar(argu, aux);
  
  /*Redimensionar a mitad*/
  aux = arg_nuevo("-f", 0, 0, 2, 0);
  arg_agregar(argu, aux);
  
  /*Redimensionar a un porcentaje*/
  aux = arg_nuevo("-x", 1, 1, 2, 0);
  arg_agregar(argu, aux);
  
  /*Blur*/
  aux = arg_nuevo("-b", 1, 1, 2, 0);
  arg_agregar(argu, aux);
  
  /*Lineas verticales*/
  aux = arg_nuevo("-lv", 3, 3, 2, 0);
  arg_agregar(argu, aux);
  
  /*Lineas horizontales*/
  aux = arg_nuevo("-lh", 3, 3, 2, 0);
  arg_agregar(argu, aux);
  
  /*Lineas horizontales y verticales*/
  aux = arg_nuevo("-lb", 3, 3, 2, 0);
  arg_agregar(argu, aux);
  
  /*Imagen salida*/
  aux = arg_nuevo("-o", 1, 1, 3, 0);
  arg_agregar(argu, aux);
  
  /*Comentarios*/
  aux = arg_nuevo("-s", 0, 0, 2, 0);
  arg_agregar(argu, aux);
}

int main(int argc, char* argv[])
{
   FILE* iOrigen; /*Archivo de Origen.*/
   FILE* iDestino; /*Archivo de Destino.*/
   
   char* arch_destino="out.bmp";
   
   int hayAccion=0;
   int hayDestino=0;
   
   int cod_ext=-1;

   int comentario=1;/*Variable la cual indicara si se mostraran o no los comntarios
                      deribada de los argumentos.*/

   argumentos_t argu;
   
   argu = arg_crear(3);
   configurar_argumentos(&argu);

   
   /*
    * Este puntero contendra la direccion del encabezado del
    * archivo de imagen.
    * 
    */
   void *ptr_encabezado;

   /*Como solo soporta archivo BMP declaramos solo una
   variable encabezado que es del tipo BMP.*/
   _BMP_Header oEncabezado; /*Encabezado de la imagen de Origen para bmp.*/
   
   /*Esta variable funcionara como puente para el bitData de la imagen
     Origen hacian el de la de Destino, es decir, se extraera el bitData del
     Origen se modificara o no y luego se guardara en la Destino,
     Es inicializada el NULL para conocer su estado cuando se haga mas
     de una modificacion.*/
   imagen_mapabit* imagenO=NULL;
    
   if (argc==1) {ayuda();return 1;}

   if(filtrar(argv[1])=='h' || filtrar(argv[1])=='?')
   {
      ayuda();
   }
   else
   {
    if (argc>=4)
    /*El minimo de argumentos es de 3
       -i origen.bmp y que se desea hacer.*/
    {
    if(arg_comprobar(&argu, argc, argv))
    {
      /*Una vez que llegamos aca estamos en condiciones
       ejecutar las acciones.*/
      int i;
      for(i=1;i<argc;i++)
      {
        switch(filtrar(argv[i]))
        {
         case 'i':{
           if(comentario){printf("\nAbriendo archivo %s...", argv[i+1]);}
           fflush(stdout);
           
           cod_ext = img_obtener_ext(argv[2]); /*Obtenemos la extemsion*/
           
           if ((iOrigen = fopen(argv[2],"rb")))
           {
             if(comentario){printf("  Hecho.\n");}
             if(comentario){printf("Leyendo encabezado...");}
             fflush(stdout);

             switch(cod_ext)
             {
               case COD_BMP: 
                 ptr_encabezado = &oEncabezado;
                 break;
               case COD_JPG:
               case COD_PNG:
               default: 
                 printf("\nExtension no soportada.\n");
                 return 1;/*Salimos del programa*/
             }
             img_extraer_encabezado(iOrigen, cod_ext, ptr_encabezado);
             if(comentario){printf("  Hecho.\n\n");}
           } else 
           {
             printf("\nError al intentar abrir el archivo %s.\n\n", argv[i+1]);
             return 1;/*Salimos de programa.*/
             }
             i++;
         }
         break;
         case 's':{
           img_mostrar_encabezado(cod_ext, ptr_encabezado);
         }
         break;
         case 'r':{ hayAccion=1;
          int result;
          if (comentario) printf("Rotando imagen...");
          fflush(stdout);
          imagenO = img_extraer_mapa(iOrigen, &imagenO, cod_ext,ptr_encabezado);
          if ((i+1) >= argc)
          {
            result = img_efecto(&imagenO, EFECTO_ROTAR, 90, cod_ext, ptr_encabezado);
          }
          else
          {
            if (arg_esOpcion(&argu, argv[i+1]))
            {
              result = img_efecto(&imagenO, EFECTO_ROTAR, 90, cod_ext, ptr_encabezado);
            }
            else
            {
              result = img_efecto(&imagenO, EFECTO_ROTAR, atoi(argv[i+1]), cod_ext, ptr_encabezado);
              i++;
            }
          }
          
          if (result) {
            if(comentario)printf(" Hecho.\n");}
            else { if(comentario)printf(" Error.\n");}
          
          fflush(stdout);
        }
         break;
         case 'n':{ hayAccion=1;
          if (comentario) {printf("Creando negativo de imagen...");}
           fflush(stdout);
           imagenO = img_extraer_mapa(iOrigen, &imagenO, cod_ext,ptr_encabezado);
           switch(cod_ext)
           {
             case COD_BMP: 
                if ( oEncabezado.infoEncabezado.bitCount<=8){
                  imagenO->paleta = oEncabezado.paleta;
               }
               break;
             case COD_JPG:
             case COD_PNG:
             default: 
               printf("Extension no soportada.\n");
               return 1;/*Salimos del programa*/
           }
           
           if (img_efecto(&imagenO, EFECTO_NEGATIVO)) {
             if (comentario) printf(" Hecho.\n");}
           else { if (comentario) printf(" Error.\n");}
           fflush(stdout);
         }
         break;
         case 'x':{ hayAccion=1;
           imagenO = img_extraer_mapa(iOrigen, &imagenO, cod_ext,ptr_encabezado);
           int por=atoi(argv[i+1]);
           if(comentario){printf("Redimencionando la imagen a un %d%%...", por);}
           fflush(stdout);
           if (img_efecto(&imagenO, EFECTO_REDIMENSION, por, cod_ext, ptr_encabezado)){
             if (comentario) printf(" Hecho.\n");}
             else {
               if (comentario) printf(" Error.\n");}
           fflush(stdout);
           i++;
         }
         break;
         case 'd':{ hayAccion=1;
           imagenO = img_extraer_mapa(iOrigen, &imagenO, cod_ext,ptr_encabezado);
           if(comentario) printf("Redimencionando la imagen al doble...");
           if (img_efecto(&imagenO, EFECTO_REDIMENSION, 200, cod_ext, ptr_encabezado)){
             if (comentario) printf(" Hecho.\n");}
             else {
             if (comentario) printf(" Error.\n");}
           fflush(stdout);
         }
         break;
         case 'f':{ hayAccion=1;
           imagenO = img_extraer_mapa(iOrigen, &imagenO, cod_ext,ptr_encabezado);
           if(comentario) printf("Redimencionando la imagen a la mitad...");
           fflush(stdout);
           if (img_efecto(&imagenO, EFECTO_REDIMENSION, 50, cod_ext, ptr_encabezado)){
              if (comentario) printf(" Hecho.\n");}
              else {
                if (comentario) printf(" Error.\n");}
           fflush(stdout);
         }
         break;
         case 'b':{ hayAccion=1;       
           if(comentario){printf("Aplicando efecto blur...");}
           fflush(stdout);
           imagenO = img_extraer_mapa(iOrigen, &imagenO, cod_ext,ptr_encabezado);
           
           if (img_efecto(&imagenO, EFECTO_BLUR, atoi(argv[i+1]))){
             if (comentario) printf(" Hecho.\n"); }
               else {if (comentario) printf(" Error.\n"); }
           fflush(stdout);
           i++;
         }
         break;
         case 'l':{ hayAccion=1;
          if (comentario) printf("Dibujando lineas...");
           fflush(stdout);
           imagenO = img_extraer_mapa(iOrigen, &imagenO, cod_ext,ptr_encabezado);
           if (img_efecto(&imagenO, EFECTO_LINEAS, atoi(argv[i+1]), atoi(argv[i+2]), atoi(argv[i+3]), argv[i][2])){
             if (comentario) printf(" Hecho.\n"); }
               else {if (comentario) printf(" Error.\n"); }
           fflush(stdout);
           i+=3;
         }
         break;
         case 'o':{
           hayDestino=1;
           arch_destino=argv[i+1];
           i++;
         }
         break;
        } /*Fin switch*/
      } /*Fin for*/
     
       if (hayAccion)
       {
         imagenO = img_extraer_mapa(iOrigen, &imagenO, cod_ext,ptr_encabezado);
         
         cod_ext = img_obtener_ext(arch_destino); /*Obtenemos la extemsion*/
         if (comentario) printf("\nVerificando el bitMap...");
         fflush(stdout);
         switch(cod_ext)
         {
           case COD_BMP: ptr_encabezado = &oEncabezado;
             break;
                         /*Si se soportaria otro tipo de archivo*/
                         /*aqui tendriamos que convertir el encabezado*/
           case COD_JPG:
           case COD_PNG:
           default: 
             printf("\nExtension no soportada.\n");
             return 1;/*Salimos del programa*/
         }
         if (comentario) printf(" Hecho.\n");
         fflush(stdout);
         if(comentario)printf("Abriendo archivo %s y preparando para escribir...", arch_destino);
         fflush(stdout);
         if ( (iDestino=fopen(arch_destino,"wb")) )
         {
           if (comentario) printf(" Hecho.\n");
            fflush(stdout);
            
           if(comentario)printf("Escribiendo el nuevo archivo...");
           fflush(stdout);
           if (img_guardar(iDestino, &imagenO, cod_ext, ptr_encabezado)) {
            if (comentario) printf(" Hecho.\n\n"); }
              else {if (comentario) printf(" Error.\n\n"); }
         }
         else 
         {
           if (comentario) printf(" Error.\n");
            fflush(stdout);
            printf("Error al intentar abrir el archivo %s.\n\n", argv[i+1]);
            return 1;/*Salimos de programa.*/
         }
         /*Cerramos el archivo.*/
         fclose(iDestino);
       } /*Fin hayAccion*/
       
       /*Cerramos el archivo origen.*/    
       if (iOrigen!= NULL) fclose(iOrigen);
       
     } /*Fin arg_comprobar*/
    } /*Fin argc>=4*/
  } /*Fin else ayuda*/
  
  
  
  return 0;
} /*Fin programa principal.*/
