/**
*@brief Manejo de objetos (funcionalidad)
*
*
*@file object.c
*@author FJNR & AMH
*@version 1.0
*@date 05/02/2018
*@copyright GNU Public License
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "object.h"

/*Estructura que define un objeto(características) */
struct _Object {
  Id id;
  char name[WORD_SIZE+1];
  Id object_weapon;/*armas:Utilidad posterior*/
  Id object_tool;/*utiles:Utilidad posterior*/
  Id object_key;/*llaves:Utilidad posterior*/
  Id location;
};



/*
 * @brief Se encarga de crear el objeto,
   y poner el caracter fin de cadena al final del nombre de este
 * @param id, de tipo Id
 * @return newObject, que es el puntero a la estructura
 */
Object* object_create (Id id){
  Object *newObject = NULL;
  if (id == NO_ID){
    return NULL;
  }
  newObject = (Object*)malloc(sizeof(Object));

  if (newObject==NULL){
    return NULL;
  }
  newObject->id=id;
  newObject->name[0]='\0';

  return newObject;
}



/*
 * @brief Libera memoria para objeto.
 * @param objeto: puntero a Objeto.
 * @return status OK o ERROR.
 */
STATUS object_destroy (Object* object){
  if(!object){
    return ERROR;
  }

  free(object);
  object = NULL;

  return OK;
}


/*
 * @brief Devuelve el id de un objeto
 * @param objeto: puntero a Objeto.
 * @return Id NO_ID o puntero (object->id).
 */
Id object_get_id(Object *object){
  if (object==NULL){
    return NO_ID;
  }
  else {
    return object->id;
  }
}



/*
 * @brief Devuelve el nombre asignado a un objeto
 * @param objeto: puntero a Objeto.
 * @return name, el nombre que asignamos al objeto
 */
const char * object_get_name(Object* object) {
  if (!object) {
    return NULL;
  }
  return object->name;
}



/*
 * @brief Devuelve el id asignado a un objeto
 * @param objeto: puntero a Objeto.
 * @return location, campo object->location
 */
Id object_get_location(Object* object){
  if (object == NULL){
    return NO_ID;
  }
  else {
    return object->location;
  }
}



/*
 * @brief Devuelve el arma
 * @param objeto: puntero a Objeto.
 * @return arma, el arma
 */
Id object_get_weapon(Object* objeto) {
  if (!objeto) {
    return NO_ID;
  }
  return objeto->object_weapon;
}



/*
 * @brief Devuelve la herramienta
 * @param objeto: puntero a Objeto.
 * @return tool, el nombre que asignamos a la herramienta
 */
Id object_get_tool(Object* objeto) {
  if (!objeto) {
    return NO_ID;
  }
  return objeto->object_tool;
}



/*
 * @brief Devuelve la llave
 * @param objeto: puntero a Objeto.
 * @return llave, la llave
 */
Id object_get_key(Object* objeto) {
  if (!objeto) {
    return NO_ID;
  }
  return objeto->object_key;
}



/*
 * @brief Pone o cambia el arma
 * @param objeto: puntero a Objeto.
 * @param id: del type Id
 * @return status OK o ERROR.
 */
STATUS object_set_weapon(Object* object, Id id) {
  if (!object || id == NO_ID) {
    return ERROR;
  }
  object->object_weapon = id;
  return OK;
}



/*
 * @brief Pone o cambia el id del objeto conforme a la location
 * @param objeto: puntero a Objeto.
 * @param id: del type Id
 * @return status OK o ERROR.
 */
STATUS object_set_location(Object* object , Id id){
  if (!object || id == NO_ID){
    return ERROR;
  }
  object->location = id;
  return OK;
}



/*
 * @brief Pone o cambia el tool
 * @param objeto: puntero a Objeto.
 * @param id: del type Id
 * @return status OK o ERROR.
 */
STATUS object_set_tool(Object* object, Id id) {
  if (!object || id == NO_ID) {
    return ERROR;
  }
  object->object_tool = id;
  return OK;
}



/*
 * @brief Pone o cambia la llave
 * @param objeto: puntero a Objeto.
 * @param id: del type Id
 * @return status OK o ERROR.
 */
STATUS object_set_key(Object* object, Id id) {
  if (!object || id == NO_ID) {
    return ERROR;
  }
  object->object_tool = id;
  return OK;
}



/*
 * @brief Pone o cambia el nombre del objeto
 * @param objeto: puntero a Objeto.
 * @param name: puntero a char.
 * @return status OK o ERROR.
 */
STATUS object_set_name (Object* object, char* name){
  if (!object || !name){
    return ERROR;
  }
  if (!strcpy(object->name,name)){
    return ERROR;
  }

  return OK;
}



/*
 * @brief Muestra por la pantalla de salida, tanto el id, como el nombre del objeto
 * @param objeto: puntero a Objeto.
 * @return status, OK o ERROR
 */
STATUS object_print(Object* object) {
  Id idaux = NO_ID;

  if (!object) {
    return ERROR;
  }

  fprintf(stdout, "--> Object (Id: %ld; Name: %s)\n", object->id, object->name);

  idaux = object_get_weapon(object);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> Weapon: %ld.\n", idaux);
  }else {
    fprintf(stdout, "---> No weapon.\n");
  }
  idaux = object_get_tool(object);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> Tool: %ld.\n", idaux);
  }else {
    fprintf(stdout, "---> No tool.\n");
  }

  idaux = object_get_key(object);
  if (NO_ID != idaux) {
    fprintf(stdout, "---> Key: %ld.\n", idaux);
  }else {
    fprintf(stdout, "---> No key.\n");
  }

  return OK;
}
