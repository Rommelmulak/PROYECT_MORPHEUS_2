/**
*@brief Manejo de objetos (interfaz)
*
*
*@file object.h
*@author FJNR & AMH
*@version 1.0
*@date 05/02/2018
*@copyright GNU Public License
*/

#ifndef OBJECT_H
#define OBJECT_H
#include "types.h"

/*Estructura que define un objeto(características)*/
typedef struct _Object Object; /*NUEVA / ANTIGUA*/



/*
 * @brief Se encarga de crear el objeto,
   y poner el caracter fin de cadena al final del nombre de este
 * @param id, de tipo Id
 * @return newObject, que es el puntero a la estructura
 */
Object* object_create (Id id);



/*
 * @brief Libera memoria para objeto.
 * @param objeto: puntero a Objeto.
 * @return status OK o ERROR.
 */
STATUS object_destroy (Object* object);



/*
 * @brief Devuelve el id de un objeto
 * @param objeto: puntero a Objeto.
 * @return Id NO_ID o puntero (object->id).
 */
Id object_get_id(Object *object);



/*
 * @brief Devuelve el nombre asignado a un objeto
 * @param objeto: puntero a Objeto.
 * @return name, el nombre que asignamos al objeto
 */
const char * object_get_name(Object* object);


/*
 * @brief Devuelve el id asignado a un objeto
 * @param objeto: puntero a Objeto.
 * @return location, campo object->location
 */
Id object_get_location(Object* object);



/*
 * @brief Devuelve el arma
 * @param objeto: puntero a Objeto.
 * @return arma, el arma
 */
Id object_get_weapon(Object* objeto);



/*
 * @brief Devuelve la herramienta
 * @param objeto: puntero a Objeto.
 * @return tool, el nombre que asignamos a la herramienta
 */
Id object_get_tool(Object* objeto);



/*
 * @brief Devuelve la llave
 * @param objeto: puntero a Objeto.
 * @return llave, la llave
 */
Id object_get_key(Object* objeto);



/*
 * @brief Pone o cambia el arma
 * @param objeto: puntero a Objeto.
 * @param id: del type Id
 * @return status OK o ERROR.
 */
STATUS object_set_weapon(Object* object, Id id);



/*
 * @brief Pone o cambia el id del objeto conforme a la location
 * @param objeto: puntero a Objeto.
 * @param id: del type Id
 * @return status OK o ERROR.
 */
STATUS object_set_location(Object* object , Id id);



/*
 * @brief Pone o cambia el tool
 * @param objeto: puntero a Objeto.
 * @param id: del type Id
 * @return status OK o ERROR.
 */
STATUS object_set_tool(Object* object, Id id);



/*
 * @brief Pone o cambia la llave
 * @param objeto: puntero a Objeto.
 * @param id: del type Id
 * @return status OK o ERROR.
 */
STATUS object_set_key(Object* object, Id id);


/*
 * @brief Pone o cambia el nombre del objeto
 * @param objeto: puntero a Objeto.
 * @param name: puntero a char.
 * @return status OK o ERROR.
 */
STATUS object_set_name (Object* object , char* name);



/*
 * @brief Muestra por la pantalla de salida, tanto el id, como el nombre del objeto
 * @param objeto: puntero a Objeto.
 * @return status, OK o ERROR
 */
STATUS object_print(Object* object);

#endif
