/**
*@brief Manejo de conjuntos (interfaz)
*
*
*@file set.h
*@author FJNR & AMH
*@version 1.0
*@date 19/02/2018
*@copyright GNU Public License
*/

#ifndef SET_H
#define SET_H

/*Estructura que define un conjunto(características) */
typedef struct _Set Set;



/*
 * @brief Se encarga de crear el conjunto
 * @param nada
 * @return conj_create (nuevo conjunto recien creado)
 */
Set * set_create ();



/*
 * @brief Se encarga de liberar el conjunto
 * @param set puntero a Set
 * @return nada (void)
 */
void set_destroy (Set * set);



/*
 * @brief Se encarga de anadir un elemento (id) al conjunto
 * @param set puntero a Set
 * @param id (Id) identificador nuevo
 * @return status OK o ERROR
 */
STATUS set_add_element (Set *set , Id id);



/*
 * @brief Se encarga de sacar un elmento si queremos
 * @param set puntero a Set
 * @return Id el identificador que usaremos
 */
Id  set_element_pop (Set *set);













#endif
