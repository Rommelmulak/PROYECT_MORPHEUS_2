/**
*@brief Manejo de conjuntos
*
*
*@file set.c
*@author FJNR & AMH
*@version 1.0
*@date 19/02/2018
*@copyright GNU Public License
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_ID 96
/*Para no desaprovechar memoria...*/
#define Set_Empty(x) (x==0)/*Macro para ver si el conjunto esta vacio*/
#define Set_Full(x) (x > MAX_ID)/*Macro para ver si el conjunto esta lleno*/

/*Estructura que define un conjunto(características) */
struct _Set {
  Id id_array[MAX_ID];
  int num_array_actual;
};



/*
 * @brief Se encarga de crear el conjunto
 * @param nada
 * @return conj_create (nuevo conjunto recien creado)
 */
Set * set_create (){
  Set *conj_create;
  conj_create = (Set*)malloc (sizeof(Set));
  if (conj_create == NULL){
    return NULL;
  }
  else {
    conj_create->id_array[0] = '\0';
    conj_create->n_array_actual = 0;
  }
  return conj_create;
}



/*
 * @brief Se encarga de liberar el conjunto
 * @param set puntero a Set
 * @return nada (void)
 */
void set_destroy (Set * set){
  int i;
  if (set == NULL){
    return NULL;
  }
  else {
    for (i=0;i<MAX_ID;i++){
      free(set->id_array[i]);
    }

    set = NULL;
    free(set);

    return;
  }
}



/*
 * @brief Se encarga de anadir un elemento (id) al conjunto
 * @param set puntero a Set
 * @param id (Id) identificador nuevo
 * @return status OK o ERROR
 */
STATUS set_add_element (Set *set , Id id){
  int i;
  if (set == NULL){
    return ERROR;
  }
  if (Set_Full(set->num_array_actual)==1){
    return ERROR;
  }
  else {
    for (i=0;set->id_array[i]!=0 && i< MAX_ID;i++);
  }
  if (i >=MAX_ID){
    return ERROR;
  }
  else {
    set->id_array[i] = id;
    (set->num_array_actual)++;
  }
  return OK;
}


/*
 * @brief Se encarga de sacar un elmento si queremos
 * @param set puntero a Set
 * @return Id el identificador que usaremos
 */
Id  set_element_pop (Set *set){
  Id temp;

  if(!set){
    return ERROR;
  }
  /*Set_empty no es una funcion, es una macro (devuelve 1 = verdadero)*/
  if (Set_Empty(set->num_array_actual) ==1){
    return NO_ID
  }
  else {
    set->num_array_actual--;
    temp = set->id_array[set->num_array_actual];
    set->id_array[set->num_array_actual] = NULL;
    return temp;
  }
}


/////////////////////////////////////////////////////////////////////////


EleStack * stack_pop(Stack *s) {
    EleStack *temp;
    if (s==NULL) return NULL;

    if (stack_isEmpty(s) == TRUE) return NULL;

    s->tope--;
    temp = s->datos[s->tope];
    s->datos[s->tope] = NULL;
    return temp;
}


//////////////////////////////////////////////////////////////////////////


/**------------------------------------------------------------------
 * @brief Inserta un elemento en la pila.
 * @param un elemento y la pila donde insertarlo.
 * @return NULL si no logra insertarlo por pila llena o la pila resultante
 * ------------------------------------------------------------------*/
Status stack_push(Stack *s, const EleStack *ele) {
    if (s==NULL || ele==NULL) return ERROR;
    if ( stack_isFull (s) ==TRUE) return ERROR;

    s->datos[s->tope] = elestack_copy(ele);
    if (s->datos[s->tope]==NULL) return ERROR;

    s->tope++;
    return OK;
 }


 /**------------------------------------------------------------------
 Imprime toda la pila, colocando el elemento en la cima al principio de la impresión (y un elemento por línea). Entrada: pila y fichero donde imprimirla. Salida: Devuelve el número de caracteres escritos.
 ------------------------------------------------------------------*/
 int stack_print(FILE *f, const Stack *s) {



 }


STATUS set_print(Set* set) {
  Id idaux = NO_ID;

  if (!set) {
    return ERROR;
  }

  fprintf(stdout, "--> Set (Id: %ld; Number of Elements: %d)\n", set->id_array, set->num_array_actual);

  if (NO_ID != idaux) {
    fprintf(stdout, "---> Weapon: %ld.\n", idaux);
  }else {
    fprintf(stdout, "---> No weapon.\n");
  }
  return OK;
}
