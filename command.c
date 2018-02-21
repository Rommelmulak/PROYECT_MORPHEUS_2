/*
*@brief Implementa los comandos
*
*@file command.c
*@author FJNR & AMH
*@version 1.0
*@date 01/02/2018
*@copyright GNU Public License
*/

#include <stdio.h>
#include <strings.h>
#include "command.h"

#define CMD_LENGHT 30
#define N_CMD 7

/* Puntero a char, es una tabla de comandos que el jugador introduce por pantalla */
char *cmd_to_str[N_CMD] = {"No command", "Unknown", "Exit", "Following", "Previous,","Get","Drop"};
/*Puntero a char, es una tabla de comandos que tendra que pulsar el jugador en la partida*/
char *short_cmd_to_str[N_CMD] = {"","","e","f","p","g","d"};




/**
* @brief Implementa los comandos, recogiendo el "input" ,
   transformándolo en un valor numérico de T_command;
* @param No param.
* @return cmd (campo de estructura T_command)
*/
T_Command get_user_input(){
  T_Command cmd = NO_CMD;/*-1*/
  char input[CMD_LENGHT] = "";/*Variable "input" (string), leera el comando*/
  int i=UNKNOWN - NO_CMD + 1; /*2*/

  if (scanf("%s", input) > 0){/*Si lee el comando correctamente*/
    cmd = UNKNOWN; /*cmd=0, siempre*/
    while (cmd == UNKNOWN && i /*=2*/ < N_CMD /*=7*/){ /*Compara el comando introducido por el jugador con los de la lista*/

      if (!strcasecmp(input,short_cmd_to_str[i]) || !strcasecmp(input,cmd_to_str[i])){/*Si coinciden "cmd" = el valor que le correponde*/
        cmd = i /*=2*/ + NO_CMD/*=-1*/;
      }
      else{
	      i++;
      }
    }
  }
  /*Hay seis posibles cmd: "", "e", "f", "p", "g", "d"*/
  return cmd;
}
