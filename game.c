/**
*@brief Implementa la interfaz del juego y todas las llamadas para cada comando
*
*
*@file game.c
*@author FJNR & AMH
*@version 1.0
*@date 03/02/2018
*@copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> /*Para rand()*/
#include "game.h"
#include "game_reader.h"
#include "player.h"
#include "object.h"
/*Evitar numeros "magicos" por el codigo*/
#define ID_J 1/*Id del player*/
#define ID_O 1/*Id del objeto*/
#define INIC_P 0/*Posicion inicial del jugador*/

#define MAX_CASILLAS 12 /*Numero de casillas (variable si modifi. data.dat)*/

#define N_CALLBACK 6

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
P. F.: Private Function
*/

/**
   Define el tipo de función para las llamadas a esta
*/
typedef void (*callback_fn)(Game* game);

/**
   Funciones de llamada para comando
*/
void game_callback_unknown(Game* game);
void game_callback_exit(Game* game);
void game_callback_following(Game* game);
void game_callback_previous(Game* game);
void game_callback_get(Game* game);
void game_callback_drop(Game* game);

/**
Array de punteros a funciones
static = unico en este modulo (evitar que se exponga) (cuidadin)
*/
static callback_fn game_callback_fn_list[N_CALLBACK]={
  game_callback_unknown,
  game_callback_exit,
  game_callback_following,
  game_callback_previous,
  game_callback_get,
  game_callback_drop
};


/**
   Funciones privadas, las cuales solo se ponen en el fichero.c
*/



/*
 * @brief Retorna el id de una casilla (asociándola con una posición predeterminada)
 * @param game, puntero a estructura,(dirección)
 * @param position, posición del espacio (en el array de punteros a Space)
 * @return NO_ID (si la posicion se sale de los límites), y si no, space_get_id (la posición)
 */
STATUS game_add_space(Game* game, Space* space);
Id     game_get_space_id_at(Game* game, int position);

STATUS game_set_player_location(Game* game, Id id);
STATUS game_set_object_location(Game* game, Id id);


 /*----------------------------------------------*/


/*
 * @brief Inicialización de la estructura Game
 * @param game, puntero a estructura Game (dirección)
 * @return status, OK O ERROR
 */
STATUS game_create(Game* game) {
  int i;

  for (i = 0; i < MAX_SPACES; i++) {/*Vacia el array spaces*/
    game->spaces[i] = NULL;
  }

  game->player = player_create(ID_J);/*1*/
  game->object = object_create(ID_O);/*1*/

  game_set_player_location(game,NO_ID);
  game_set_object_location(game,NO_ID);
  game->last_cmd = NO_CMD;

  return OK;
}



/*
 * @brief Crea el juego, carga las casillas (data.dat) y ponen el objeto y jugador
    en la posición primera.
 * @param game, puntero a estructura Game (dirección)
 * @param filename, fichero de casillas (data.dat)
 * @return status, OK O ERROR
 */
STATUS game_create_from_file(Game* game, char* filename) {
  int numcasillas;
  int random;
  time_t t;
  if (game_create(game) == ERROR)
    return ERROR;

  if (game_reader_load_spaces(game, filename,&numcasillas) == ERROR){
    return ERROR;
  }
  /*Para generacion random del objeto entorno al total de casillas en data.dat*/
  srand((unsigned) time(&t));
  random =(rand() %numcasillas);
  if (random == MAX_CASILLAS){
    random = random -1;
  }

    /*Colocamos en casilla 0 a player y random al player*/
  game_set_player_location(game, game_get_space_id_at(game, INIC_P));
  game_set_object_location(game, game_get_space_id_at(game, random));
  return OK;
}



/*
 * @brief Elimina las casillas creadas en la función anterior
 * @param game, puntero a estructura Game (dirección)
 * @return status, OK O ERROR
 */
STATUS game_destroy(Game* game) {
  int i = 0;

  for (i = 0; (i < MAX_SPACES) && (game->spaces[i] != NULL); i++) {
    space_destroy(game->spaces[i]);
  }
  player_destroy(game->player);
  object_destroy(game->object);

  return OK;
}



/*
 * @brief Crea una casilla una vez comprobado el array (hasta que apunte a NULL)
    el espacio que se añade es el parámetro
 * @param game, puntero a estructura Game (dirección)
 * @param space , puntero a estructura Space (dirección)
 * @return status, OK O ERROR
 */
STATUS game_add_space(Game* game, Space* space) {
  int i = 0;

  if (space == NULL) {
    return ERROR;
  }

  while ( (i < MAX_SPACES) && (game->spaces[i] != NULL)){
    i++;
  }

  if (i >= MAX_SPACES) {
    return ERROR;
  }

  game->spaces[i] = space;

  return OK;
}



/*
 * @brief Retorna el id de una casilla (asociándola con una posición predeterminada)
 * @param game, puntero a estructura,(dirección)
 * @param position, posición del espacio (en el array de punteros a Space)
 * @return NO_ID (si la posicion se sale de los límites), y si no, space_get_id (la posición)
 */
Id game_get_space_id_at(Game* game, int position) {

  if (position < 0 || position >= MAX_SPACES) {
    return NO_ID;
  }

  return space_get_id(game->spaces[position]);
}



/*
 * @brief Retorna la casilla (asociándola con una posición predeterminada)
    y con el id (param)
 * @param game, puntero a estructura,(dirección)
 * @param id, Entero (identificador)
 * @return NULL (si el id esta corrupto, o al final de la función),
    y el array "spaces", de la estructura, si coincide con el id pasado como argumento
 */
Space* game_get_space(Game* game, Id id){
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    if (id == space_get_id(game->spaces[i])){
      return game->spaces[i];
    }
  }

  return NULL;
}



/**
 * @brief funcionalidad de modificar la localizacion del jugador mediante el id
 * @param game, puntero a Game (dirección)
 * @param id, Entero de tipo Id (identificador)
 * @return status, OK O ERROR
 */
STATUS game_set_player_location(Game* game, Id id) {
  if (id == NO_ID) {
    return ERROR;
  }/*game_get_space (game,id)=>id*/
  if (player_set_location(game->player,id)==ERROR){
    return ERROR;
  }
  return OK;
}



/**
 * @brief funcionalidad de modificar la localizacion del objeto mediante el id
 * @param game,puntero a la estructura Game
 * @param id_espacio, campo de la estructura Id
 * @return status, OK O ERROR
 */
STATUS game_set_object_location(Game* game, Id id_espacio) {
  int i;
  Id space_aux , object_id_aux;
  if (!game || id_espacio == NO_ID) {
    return ERROR;
  }
  for (i=0;i<MAX_SPACES;i++){
    space_aux = space_get_id(game->spaces[i]);
    /*Si id del arg coincide con el del espacio que busca el bucle coloca objeto*/
    if (space_aux == id_espacio){
      object_id_aux = object_get_id(game->object);
      space_set_object(game->spaces[i],object_id_aux);

      return OK;
    }
  }
    /*object_set_location (game->object,id);*/
  return ERROR;
}



/**
 * @brief Devuelve la posicion del jugador (estructura game)
 * @param game, puntero a la estructura Game
 * @return la posición del jugador, modificada de la estructura
 */
Id game_get_player_location(Game* game) {

  return player_get_location(game->player);
}



/**
 * @brief Devuelve la posicion del objeto (estructura game)
 * @param game, puntero a la estructura Game
 * @return la posición del objeto, modificada de la estructura
 *//*  return location(id) o NO_ID (id)
*/
Id game_get_object_location(Game* game) {
  int i;
  Id space_aux , object_aux, location;

  if (!game){
    return NO_ID;
  }
  else {
    object_aux = object_get_id(game->object);


    for (i=0;i<MAX_SPACES;i++){
      space_aux = space_get_object(game->spaces[i]);
      /*Si id (objeto_en_casilla) == id (objeto)*/
      if (space_aux == object_aux){
        location = space_get_id(game->spaces[i]);

        return location;
      }
    }
  }
  return NO_ID;/*puede darse el caso de que no lo encuentre porque no este*/
}



/**
 * @brief Actualizacion de los comandos (muestra el último).
 * @param game, puntero a la estructura Game
 * @param cmd, enumeración (identificador de cada comando)
 * @return status, OK O ERROR
 */
STATUS game_update(Game* game, T_Command cmd) {
  game->last_cmd = cmd;
  (*game_callback_fn_list[cmd])(game);

  return OK;
}



/**
 * @brief Devuelve el último comando que se ha introducido.
 * @param game, puntero a la estructura Game
 * @return cmd, el último comando.
 */
T_Command game_get_last_command(Game* game){

  return game->last_cmd;
}



/**
 * @brief Imprime la "info" de todas las casillas ,y la posición del jugador y
    del objeto.
 * @param game, puntero a la estructura Game
 * @return nada
 */
void game_print_data(Game* game) {
  int i = 0;

  printf("\n\n-------------\n\n");

  printf("=> Spaces: \n");
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    space_print(game->spaces[i]);
  }

  printf("=> Object location: %d\n", (int) game_get_object_location(game));
  printf("=> Player location: %d\n", (int) game_get_player_location(game));
  printf("prompt:> ");
}



/**
 * @brief Posible llamada a la finalización del juego
 * @param game, puntero a la estructura Game
 * @return bool, TRUE or FALSE
 */
BOOL game_is_over(Game* game) {

  return FALSE;
}

/*----------------------------------------------*/
/**
   Callbacks : implementación para cada comando.
*/

void game_callback_unknown(Game* game) {
}
void game_callback_exit(Game* game) {
}



/**
 * @brief Implementa la función del comando following
 * @param game, puntero a la estructura Game
 * @return, ya que es una función de tipo void
 */
void game_callback_following(Game* game) {
  int i = 0;
  Id current_id = NO_ID;/*-1*/
  Id space_id = NO_ID;/*id del jugador*/

  space_id = game_get_player_location(game);
  if (space_id == NO_ID) {
    return;
  }
  /*Recorre todos los espacios*/
  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);

    if (current_id == space_id) {
      current_id = space_get_south(game->spaces[i]);

      if (current_id != NO_ID) {
	       game_set_player_location(game, current_id);
      }
      return;
    }
  }
}



/**
 * @brief Implementa la función del comando previous
 * @param game, puntero a la estructura Game
 * @return, ya que es una función de tipo void
 */
void game_callback_previous(Game* game) {
  int i = 0;
  Id current_id = NO_ID;
  Id space_id = NO_ID;

  space_id = game_get_player_location(game);

  if (NO_ID == space_id) {
    return;
  }

  for (i = 0; i < MAX_SPACES && game->spaces[i] != NULL; i++) {
    current_id = space_get_id(game->spaces[i]);

    if (current_id == space_id) {
      current_id = space_get_north(game->spaces[i]);

      if (current_id != NO_ID) {
	       game_set_player_location(game, current_id);
      }
      return;
    }
  }
}



/**
 * @brief Implementa la función del comando get
 * @param game, puntero a la estructura Game
 * @return, ya que es una función de tipo void
 */
void game_callback_get(Game* game) {
  Id current_id = NO_ID;
  Space *current_space = NULL;
  Id object = NO_ID;

  current_id = game_get_player_location(game);

  if (NO_ID == current_id) {
    return;
  }

  current_space = game_get_space(game, current_id);

  if (current_space == NULL){
    return;
  }

  /* Si el jugador está en casilla con un objeto,
   y decide cogerlo (se le asigna) y desaparece de la casilla */
  if (space_get_object(current_space) == NO_ID){
    return;
  }
  object = object_get_id(game->object);
  player_set_object(game->player, object);

  /* Quitar de la casilla el objeto que se recoge */
  space_set_object(current_space, NO_ID);

  return;
}



/**
 * @brief Implementa la función del comando drop
 * @param game, puntero a la estructura Game
 * @return, ya que es una función de tipo void
 */
void game_callback_drop(Game* game) {
  Id current_id = NO_ID;
  Space *current_space = NULL;
  Id object = NO_ID;
  current_id = game_get_player_location(game);

  if (NO_ID == current_id) {
    return;
  }

  current_space = game_get_space(game, current_id);

  if (current_space == NULL){
    return;
  }

  /* Si el jugador está en casilla sin objeto,
  lo deja (se le asigna) y aparece en la casilla */
  if (space_get_object(current_space) == NO_ID && player_get_inventory_item(game->player) != NO_ID){
    object = object_get_id(game->object);
    player_set_object(game->player,NO_ID);

    /* Poner en la casilla el objeto */
    space_set_object(current_space, object);

    return;
  }
}
