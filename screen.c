/**
*@brief Implementa la pantalla
*
*
*@file screen.c
*@author FJNR & AMH
*@version 1.0
*@date 04/02/2018
*@copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "screen.h"

#pragma GCC diagnostic ignored "-Wpedantic"

#define ROWS 23
#define COLUMNS 80
#define TOTAL_DATA (ROWS * COLUMNS) + 1

#define BG_CHAR '~'
#define FG_CHAR ' '
#define PROMPT " prompt:> "

#define ACCESS(d, x, y) (d + ((y) * COLUMNS) + (x)) /*puntero a void */
/**                 Definidos en:
                        ||
                        ||
                        V
WORD_SIZE = 1000 <==types.h
MAX_SPACES = 100 <==space.h
FIRST_SPACE = 1 <==space.h
NO_ID = -1 <==types.h
NO_CMD = -1 <==command.h
UNKNOWN = 0 <==command.h
EXIT = 1 <==command.h
FOLLOWING = 2 <==command.h
PREVIOUS = 3 <==command.h
SCREEN_MAX_STR = 80 <==screen.h
P.F.: Private Function
*/

/*Estructura que define la posición y tamaño de cada área ,y un puntero a char
  (cursor) que sirve para una "linked list"*/
struct _Area{
  int x, y, width, height;
  char *cursor;
};

char *__data;

/****************************/
/*    Funciones Privadas   */
/****************************/
int  screen_area_cursor_is_out_of_bounds(Area* area);
void screen_area_scroll_up(Area* area);
void screen_utils_replaces_special_chars(char* str);

/****************************/
/* Implementación de Funciones */
/****************************/


/*
 * @brief Reserva memoria dinámica para data y pone todos los caractes a BG_CHAR
 * @param nada
 * @return, nada ya que es una función de tipo void
 */
void screen_init(){
  screen_destroy(); /* Eliminar si se inicializó previamente */
  __data = (char *) malloc(sizeof(char) * TOTAL_DATA);

  if (__data){
    memset(__data, (int) BG_CHAR, TOTAL_DATA); /* Llena el fondo */
    *(__data + TOTAL_DATA - 1) = '\0';/* Cadena terminada en -NULL*/
  }
}



/*
 * @brief Libera memoria dinámica para "__data"
 * @param nada
 * @return, nada ya que es una función de tipo void
 */
void screen_destroy(){
  if (__data)
    free(__data);
}



/*
 * @brief Colorea la pantalla de azul donde no hay interfaz
    y de gris donde se desarrolla el juego.
 * @param nada
 * @return,nada ya que es una función de tipo void
 */
void screen_paint(){
  char *src = NULL;
  char dest[COLUMNS + 1];
  int i=0;

  memset(dest, 0, COLUMNS + 1);

  if (__data){
    /* pone (__data); */
    puts("\033[2J"); /*Limpia el terminal*/
    for (src=__data; src < (__data + TOTAL_DATA - 1); src+=COLUMNS){
      memcpy(dest, src, COLUMNS);
      /* printf("%s\n", dest); */
      for (i=0; i<COLUMNS; i++){
      	if (dest[i] == BG_CHAR){
      	  printf("\033[0;34;44m%c\033[0m", dest[i]); /* fg:azul(34); bg:azul(44) */
      	}
        else{
      	  printf("\033[0;30;47m%c\033[0m", dest[i]); /* fg:negro(30); bg:blanco(47)*/
      	}
      }
      printf("\n");
    }
  }
}



/*
 * @brief Escribe por pantalla prompt: y coge las columnas al imprimir
 * @param str, un puntero a char, el string
 * @return,nada ya que es una función de tipo void
 */
void screen_gets(char *str){
  fprintf(stdout, PROMPT);
  if (fgets(str, COLUMNS, stdin))
    *(str + strlen(str) - 1) = 0; /* Replaza el carácter de nueva línea con '/0' */
}



/*
 * @brief Crea memoria dinámica para el area y copia el caracter c a los
  primeros n caracteres del string
 * @param x, coordenada cuadrada de un área
 * @param y, coordenada cuadrada de un área
 * @param width, la anchura
 * @param height, la altura
 * @return area, la estructura
 */
Area* screen_area_init(int x, int y, int width, int height){
  int i = 0;
  Area* area = NULL;

  if ( (area  = (Area*) malloc (sizeof(struct _Area))) ){
    *area = (struct _Area) {x, y, width, height, ACCESS(__data, x, y)};

    for (i=0; i < area->height; i++) /*Si i es menor que la altura  se copia el caracter ' ' que equivale a 32 en ASCII a el string
    que genera ACCESS tantas veces como lo indique la anchura */
      memset(ACCESS(area->cursor, 0, i), (int) FG_CHAR, (size_t) area->width);
  }

  return area;
}



/*
 * @brief Libera memoria almacenada de manera dinamica de area
 * @param area, la estructura
 * @return nada, porque es una función de tipo void
 */
void screen_area_destroy(Area* area){
  if(area)
    free(area);
}



/*
 * @brief Borra lo que hay en la pantalla
 * @param area, la estructura
 * @return nada, porque es una función de tipo void
 */
void screen_area_clear(Area* area){
  int i = 0;

  if (area){
    screen_area_reset_cursor(area);

    for (i=0; i < area->height; i++)
      memset(ACCESS(area->cursor, 0, i), (int) FG_CHAR, (size_t) area->width);
  }
}



/*
 * @brief Resetea el cursor
 * @param area, la estructura
 * @return nada, porque es una función de tipo void
 */
void screen_area_reset_cursor(Area* area){
  if (area)
    area->cursor = ACCESS(__data, area->x, area->y);
}



/*
 * @brief Si la pantalla se va del limite la sube y se remplazan los caracteres
    especiales/
 * @param area, la estructura
 * @param str, un puntero a char, el string
 * @return nada, porque es una función de tipo void
 */
void screen_area_puts(Area* area, char *str){
  int len = 0;
  char *ptr = NULL;

  if (screen_area_cursor_is_out_of_bounds(area))
    screen_area_scroll_up(area);

  screen_utils_replaces_special_chars(str);

  /*Este bucle, le dice al cursor la anchura con la que tiene que inicializarse
   y a continuación se encarga de seguirlo*/
  for (ptr = str; ptr < (str + strlen(str)); ptr+=area->width){
    memset(area->cursor, FG_CHAR, area->width);
    /*si el tamano de ptr es menor que la anchura se le asigna la len el tamano
      de ptr si no se le asigna la anchura*/
    len = (strlen(ptr) < area->width)? strlen(ptr) : area->width;
    memcpy(area->cursor, ptr, len);
    area->cursor += COLUMNS; /*cursor += height*/
  }
}



/*
 * @brief Devuelve el atributo cursor cuando se sitúa en la esquina superior derecha (sumando la altura y achura), es decir, cuado se sale de límites
 * @param area, la estructura
 * @return las coordenadas del cursor, x e y (la altura y anchura)
 */
int screen_area_cursor_is_out_of_bounds(Area* area){
  return area->cursor > ACCESS(__data,area->x + area->width,area->y + area->height - 1);
}



/*
 * @brief Subir la pantalla donde se juega
 * @param area, la estructura
 * @return nada, ya que es una función de tipo void
 */
void screen_area_scroll_up(Area* area){
  for(area->cursor = ACCESS(__data, area->x, area->y);
      area->cursor < ACCESS(__data, area->x + area->width, area->y + area->height - 2);
      area->cursor += COLUMNS){
    memcpy(area->cursor, area->cursor+COLUMNS, area->width);
  }
}



/*
 * @brief  Reemplaza los caracteres con tilde o la letra 'ñ', por esto: '??'
 * @param str, un puntero a char, el string
 * @return nada, ya que es una función de tipo void
 */
void screen_utils_replaces_special_chars(char* str){
  char *pch = NULL;
  /*Localiza la primera aparición de la cadena apuntada
  str de cualquier carácter de la cadena apuntada por "ÁÉÍÓÚÑáéíóúñ".*/
  while ((pch = strpbrk (str, "ÁÉÍÓÚÑáéíóúñ"))){
    memcpy(pch, "??", 2);
  }
}
