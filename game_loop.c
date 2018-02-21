/**
 * @brief Define el bucle del juego
 *
 * @file game_loop.c
 * @author FRNJ & AMH
 * @version 1.0
 * @date 05-02-2018
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "graphic_engine.h"


int main(int argc, char *argv[]){
  Game game;
  T_Command command = NO_CMD;
  Graphic_engine *gengine;

  /*Describe como tenemos que ejecutar el programa correctamente
    y que le tenemos que pasar como argumento*/
  if (argc < 2){
    fprintf(stderr, "Use: %s <game_data_file>\n", argv[0]);

    return 1;
  }
  /*En caso de que el juego no se pueda crear, avisa por pantalla,
    y devuelve el error*/
	if (game_create_from_file(&game, argv[1]) == ERROR){
    fprintf(stderr, "Error while initializing game.\n");

    return 1;
  }
  /*En caso de que el graphic_engine no pueda crearse saltara
    por pantalla un error y se liberara memoria*/
	if ((gengine = graphic_engine_create()) == NULL){
    fprintf(stderr, "Error while initializing graphic engine.\n");
    game_destroy(&game);

    return 1;
  }
  /*Esta función evita que el juego termine, a excepción de que el
    jugador pulse "EXIT"*/
	while ((command != EXIT) && !game_is_over(&game)){
		graphic_engine_paint_game(gengine, &game);
    command = get_user_input();
    game_update(&game, command);

	}
  /* Cuando el bucle termina, libera memoria con game_destroy y graphic_engine_destroy,
    y termina el juego */
  game_destroy(&game);
	graphic_engine_destroy(gengine);

return 0;
}
