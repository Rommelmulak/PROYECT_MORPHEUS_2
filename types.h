/**
 * @brief It defines common types
 *
 * @file types.h
 *@author FJNR & AMH
 * @version 1.0
 *@date 05/02/2018
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000
#define NO_ID -1

typedef long Id;
/**
Enumeración de códigos de error DE BOOL
*/
typedef enum {
  FALSE, TRUE
} BOOL;
/**
Enumeración de códigos de error de STATUS
*/
typedef enum {
  ERROR, OK
} STATUS;
/**
Enumeración de direcciones
*/
typedef enum {
  N, S, E, W
} DIRECTION;

#endif
