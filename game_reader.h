/*
*@brief Carga de espacios (interfaz)
*
*
*@file game_reader.h
*@author FJNR & AMH
*@version 1.0
*@date 05/02/2018
*@copyright GNU Public License
*/
#ifndef GAME_READ
#define GAME_READ

#include "game.h"
#include "command.h"
#include "space.h"

/*
 * @brief  Lee el fichero (funcionalidad de carga de espacios)
 * @param Game, es el string destino, en el que se copia el puntero al string de tipo char, "toks"
 * @param filename, puntero a char, que es el nombre del fichero que estamos accediendo
 * @return status, OK O ERROR
 */

STATUS game_reader_load_spaces(Game* game, char* filename,int* numcasillas);

#endif
