/*
*@brief Carga de espacios (funcionalidad)
*
*@file game_reader.c
*@author FJNR & AMH
*@version 1.0
*@date 05/02/2018
*@copyright GNU Public License
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "game_reader.h"
#include "types.h"
#include "space.h"
#include "command.h"/*Ya vienen en "game_reader.h"*/
#include "game.h" /*Ya vienen en "game_reader.h"*/

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

/*
 * @brief  Lee el fichero (funcionalidad de carga de espacios)
 * @param Game, es el string destino, en el que se copia el puntero al string de tipo char, "toks"
 * @param filename, puntero a char, que es el nombre del fichero que estamos accediendo
 * @return status, OK O ERROR
 */

STATUS game_reader_load_spaces(Game* game, char* filename, int *numcasillas) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID;
  Space* space = NULL;
  /*Suponemos OK*/
  STATUS status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  /**
  Este bucle:
  -Establece donde se copiará el string leído,
  -Escanea el fichero por líneas (1000 como máximo) y almacena en "line"
  */
  while (fgets(line, WORD_SIZE, file)) {
    /*Si los 3 primeros caracteres son #s: */
    if (strncmp("#s:", line, 3) == 0) {
      /*Rompemos la cadena en trozos y los separamos con el caracter "|"*/
      /*Se asigna a las variables el valor obtenido del archivo correspondiente*/
      toks = strtok(line + 3, "|");
      /*"atol" convierte la porción inicial de la cadena apuntada por "toks" a una representación de "id", y lo devuelve.*/
      /*Por lo tanto, "id" = valor convertido*/
      id = atol(toks);
      *numcasillas =(int)id;
      toks = strtok(NULL, "|");
      strcpy(name, toks);

      toks = strtok(NULL, "|");
      north = atol(toks);

      toks = strtok(NULL, "|");
      east = atol(toks);

      toks = strtok(NULL, "|");
      south = atol(toks);

      toks = strtok(NULL, "|");
      west = atol(toks);

    #ifdef DEBUG /*Se ejecuta el código de dentro si debug está debug definido*/

      printf("Leído: %ld|%s|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west);


    #endif
    /*Asignamos los nuevos valores (leídos con fgets)*/
      space = space_create(id);
      if (space != NULL) {
	      space_set_name(space, name);
	      space_set_north(space, north);
	      space_set_east(space, east);
	      space_set_south(space, south);
	      space_set_west(space, west);
	      game_add_space(game, space);
      }
    }
  }
  /*Se modifica el estado del código de error y devuelve
    un valor distinto de cero si se detectan errores*/
  if (ferror(file)) {
    status = ERROR;
  }
  fclose(file);

  return status;
}
