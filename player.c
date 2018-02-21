/**
*@brief Manejo de jugadores (funcionalidad)
*
*
*@file player.c
*@author FJNR & AMH
*@version 1.0
*@date 06/02/2018
*@copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "object.h"
#include "space.h"
#include "player.h"


/*Estrucura que para las caracteristicas de player*/
struct _Player {
  Id player_id;
  char name[WORD_SIZE+1];
  Id space_id;/*objeto del inventario*/
  Id inventory_item_id;/*localicación*/
};



/*
 * @brief Se encarga de crear el jugador,
   y poner el caracter fin de cadena al final del nombre de este
 * @param id, de tipo Id
 * @return newPlayer, que es el puntero a la estructura
 */
Player* player_create (Id id){
  Player *newPlayer = NULL;
  if (id == NO_ID){
    return NULL;
  }
  newPlayer = (Player*)malloc(sizeof(Player));

  if (newPlayer==NULL){
    return NULL;
  }
  newPlayer->player_id=id;
  newPlayer->name[0] = '\0';
  newPlayer->inventory_item_id=NO_ID;

  return newPlayer;
}



/*
 * @brief Libera memoria para player.
 * @param Player: puntero a Player .
 * @return status OK o ERROR.
 */
STATUS player_destroy (Player* player){
  if(!player){
    return ERROR;
  }

  free(player);
  player = NULL;

  return OK;
}



/*
 * @brief Pone o cambia el nombre del jugador
 * @param objeto: puntero a Objeto.
 * @param name: puntero a char.
 * @return status OK o ERROR.
 */
STATUS player_set_name (Player* player, char* name){
  if (!player || !name){
    return ERROR;
  }
  if (!strcpy(player->name,name)){
    return ERROR;
  }

  return OK;
}



/*
 * @brief Pone o cambia el objeto del inventario
 * @param player: puntero a Player.
 * @param objeto: campo de Objeto.
 * @return status OK o ERROR.
 */
STATUS player_set_object(Player* player,Id object) {
  if (!player || !object) {
    return ERROR;
  }
  player->inventory_item_id = object;
  return OK;
}



/*
 * @brief Pone o cambia la localizacion de player
 * @param player: puntero a Player.
 * @param location: campo de Space.
 * @return status OK o ERROR.
 */
STATUS player_set_location(Player* player,Id location) {
  if (!player || !location) {
    return ERROR;
  }
  player->space_id = location;
  return OK;
}



/*
 * @brief Devuelve el nombre asignado a un jugador
 * @param jugador: puntero a Jugador.
 * @return name, el nombre que asignamos al jugador
 */
const char * player_get_name(Player* player) {
  if (!player) {
    return NULL;
  }
  return player->name;
}



/*
 * @brief Devuelve la inventory_item
 * @param jugador: puntero a Jugador.
 * @return player->inventory_item (objeto)
 */
Id player_get_inventory_item(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->inventory_item_id;
}



/*
 * @brief Devuelve la location
 * @param jugador: puntero a Jugador.
 * @return player->location(localizacion)
 */
Id player_get_location(Player* player) {
  if (!player) {
    return NO_ID;
  }
  return player->space_id;
}



/*
 * @brief Devuelve el id del jugador
 * @param jugador: puntero a Jugador.
 * @return player->player_id(identificador)
 */
Id player_get_id(Player * player){
  if (!player){
    return NO_ID;
  }
  return player->player_id;
}



/*
 * @brief Muestra por la pantalla de salida, tanto el id, como el nombre del jugador
 * @param jugador: puntero a Jugador.
 * @return status, OK o ERROR
 */
 /**
 * USO ALTERNATIVO ==> PLAYER PRINT: Control de errores Debugging
 */
STATUS player_print(Player* player) {
  if (!player) {
    return ERROR;
  }

  fprintf(stdout, "--> Player (Id: %ld; Name: %s)\n", player->player_id, player->name);

  if (NO_ID != player_get_inventory_item(player)) {
    fprintf(stdout, "---> inventory_item: %ld.\n",(long)player_get_inventory_item(player));
  }else {
    fprintf(stdout, "---> No inventory_item.\n");
  }
  if (NO_ID != player_get_location(player)) {
    fprintf(stdout, "---> Location: %ld.\n",(long)player_get_location(player));
  }else {
    fprintf(stdout, "---> No location.\n");
  }

  return OK;
}
