/**
 * @brief Define un motor gráfico
 *
 * @file graphic_engine.c
 *@author FJNR & AMH
 * @version 1.0
 *@date 05/02/2018
 * @copyright GNU Public License
 */

#include <stdlib.h>
#include <stdio.h>
#include "screen.h"
#include "graphic_engine.h"

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
/*Estructura que define el Graphic_engine tamaño del area*/
struct _Graphic_engine{
  Area *map,
       *descript,
       *banner,
       *help,
       *feedback;
};



/*
 * @brief Tiene la función de crear el área (se generan unos puntos en la
    pantalla con: (x,y,width,height)) de los interfaces del juego
    (inicializa la estructura de Graphic_engine)
 * @param nada
 * @return "ge", el puntero que contiene los elementos de la estructura
    (punteros de tipo Area)
 */
Graphic_engine *graphic_engine_create(){
  /*Conserva el valor (static)*/
  static Graphic_engine *ge = NULL;

  if (ge)
    return ge;

  screen_init();
  ge = (Graphic_engine *) malloc(sizeof(Graphic_engine));
  /*Definicion de areas*/
  ge->map      = screen_area_init( 1, 1, 48, 13);
  ge->descript = screen_area_init(50, 1, 29, 13);
  ge->banner   = screen_area_init(28,15, 23,  1);
  ge->help     = screen_area_init( 1,16, 78,  2);
  ge->feedback = screen_area_init( 1,19, 78,  3);

  return ge;
}



/*
 * @brief Tiene la función de liberar la memoria de todos los campos de ge
 * @param "ge", el puntero a "Graphic_engine"
 * @return, ya que es una función de tipo void
 */
void graphic_engine_destroy(Graphic_engine *ge){
  if (!ge){
    return;
  }

  screen_area_destroy(ge->map);
  screen_area_destroy(ge->descript);
  screen_area_destroy(ge->banner);
  screen_area_destroy(ge->help);
  screen_area_destroy(ge->feedback);

  screen_destroy();
  free(ge);
}



/*
 * @brief Dibuja cada área en la pantalla de salida (se generan puntos en la
    pantalla con: (x,y,width,height))
 * @param "ge",  el puntero a "Graphic_engine"
 * @param "game", el puntero a "Game"
 * @return, ya que es una función de tipo void
 */
void graphic_engine_paint_game(Graphic_engine *ge, Game *game){
  Id id_act = NO_ID, id_back = NO_ID, id_next = NO_ID, obj_loc = NO_ID;
  Space* space_act = NULL;
  char obj='\0';
  char str[255];
  T_Command last_cmd = UNKNOWN;
  extern char *cmd_to_str[];
  /*Dibuja el área de mapa*/
  screen_area_clear(ge->map);
  if ((id_act = game_get_player_location(game)) != NO_ID){
    /* Obtiene la estructura de tipo Space para id_act (casilla actual),
      y el id de las casillas anterior (id_back) y posterior (id_next) respecto
      del jugador */
    space_act = game_get_space(game, id_act);
    id_back = space_get_north(space_act);
    id_next = space_get_south(space_act);


    if (game_get_object_location(game) == id_back)
      obj='*';
    else
      obj=' ';
    /*Casilla anterior (efecto de refresco)*/
    if (id_back != NO_ID) {
      sprintf(str, "  |         %2d|",(int) id_back);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |",obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "        ^");
      screen_area_puts(ge->map, str);
    }

    if (game_get_object_location(game) == id_act)
      obj='*';
    else
      obj=' ';
    /*Casilla actual (efecto de refresco)*/
    if (id_act != NO_ID) {
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  | 8D      %2d|",(int) id_act);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |",obj);
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
    }

    if (game_get_object_location(game) == id_next)
      obj='*';
    else
      obj=' ';
    /*Casilla siguiente (efecto de refresco)*/
    if (id_next != NO_ID) {
      sprintf(str, "        v");
      screen_area_puts(ge->map, str);
      sprintf(str, "  +-----------+");
      screen_area_puts(ge->map, str);
      sprintf(str, "  |         %2d|",(int) id_next);
      screen_area_puts(ge->map, str);
      sprintf(str, "  |     %c     |",obj);
      screen_area_puts(ge->map, str);
    }
  }

  /*Dibuja la zona descriptiva*/
  screen_area_clear(ge->descript);
  if ((obj_loc = game_get_object_location(game)) != NO_ID){
    sprintf(str, "  Object location:%d", (int)obj_loc);
    screen_area_puts(ge->descript, str);
  }/*if (game_get_last_command(game) == GET && obj_loc == id_next)*/
  else {
    sprintf(str , "You have an object now");
    screen_area_puts(ge->descript, str);
  }

  /*Dibuja la zona del banner*/
  screen_area_puts(ge->banner, " The game of the Goose ");

  /*Dibuja la zona de help*/
  screen_area_clear(ge->help);
  sprintf(str, " The commands you can use are:");
  screen_area_puts(ge->help, str);
  sprintf(str, "     following=>f / previous=>p / exit=>e / get=>g / drop=>d");
  screen_area_puts(ge->help, str);

  /*Dibuja el área de feedback*/
  last_cmd = game_get_last_command(game);
  sprintf(str, " %s", cmd_to_str[last_cmd-NO_CMD]);
  screen_area_puts(ge->feedback, str);

  /*Lo pasa al terminal*/
  screen_paint();
  printf("prompt:> ");
}
