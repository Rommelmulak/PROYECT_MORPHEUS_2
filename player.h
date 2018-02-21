/**
*@brief Manejo de jugadores (funcionalidad)
*
*
*@file player.h
*@author FJNR & AMH
*@version 1.0
*@date 06/02/2018
*@copyright GNU Public License
*/

#ifndef PLAYER_H
#define PLAYER_H
#include "types.h"
#include "space.h"
#include "object.h"


/*Estructura que define un jugador(características)*/
typedef struct _Player Player; /*NUEVA / ANTIGUA*/

/*
 * @brief Se encarga de crear el jugador,
   y poner el caracter fin de cadena al final del nombre de este
 * @param id, de tipo Id
 * @return newPlayer, que es el puntero a la estructura
 */
Player* player_create (Id id);



/*
 * @brief Libera memoria para player.
 * @param Player: puntero a Player.
 * @return status OK o ERROR.
 */
STATUS player_destroy (Player * player);



/*
 * @brief Pone o cambia el nombre del jugador
 * @param jugador: puntero a Jugador.
 * @param name: puntero a char.
 * @return status OK o ERROR.
 */
STATUS player_set_name (Player* , char* name);



/*
 * @brief Pone o cambia el objeto del inventario
 * @param objeto: puntero a Objeto.
 * @param objeto: campo de Objeto.
 * @return status OK o ERROR.
 */
STATUS player_set_object(Player* player,Id object);



/*
 * @brief Pone o cambia la localizacion de player
 * @param player: puntero a Player.
 * @param location: campo de Space.
 * @return status OK o ERROR.
 */
STATUS player_set_location(Player* player,Id location);



/*
 * @brief Devuelve el nombre asignado a un jugador
 * @param jugador: puntero a Jugador.
 * @return name, el nombre que asignamos al jugador
 */
const char * player_get_name(Player* player);



/*
 * @brief Devuelve la inventory_item
 * @param jugador: puntero a Jugador.
 * @return player->inventory_item (objeto)
 */
Id player_get_inventory_item(Player* player);



/*
 * @brief Devuelve la location
 * @param jugador: puntero a Jugador.
 * @return player->location (localizacion)
 */
Id player_get_location(Player* player);



/*
 * @brief Devuelve el id del jugador
 * @param jugador: puntero a Jugador.
 * @return player->player_id(identificador)
 */
Id player_get_id(Player * player);



/*
 * @brief Muestra por la pantalla de salida, tanto el id, como el nombre del jugador
 * @param jugador: puntero a Jugador.
 * @return status, OK o ERROR
 */
/**
COMENTARIO ALTERNATIVO ==> PLAYER PRINT: Control de errores Debugging
*/
STATUS player_print(Player* player);

#endif
