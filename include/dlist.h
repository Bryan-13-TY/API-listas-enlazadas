#ifndef DLIST_H
#define DLIST_H

#include "list_status.h"

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DList DList;

/**
 * @brief Crea una lista doblemente enlazada.
 * 
 * @return
 * - LIST_OK si se creó correctamente
 * - NULL si falla malloc
 */
DList *dlist_create(void);

/**
 * @brief Obtiene el número de elementos en la lista.
 * 
 * @param list Lista válida
 * @param count Puntero donde se almacena el número de elementos
 * 
 * @return
 * - LIST_OK si se obtuvó el número de elementos correctamente
 * - LIST_ERR_NULL si la lista no existe o no fue creada
 */
ListStatus dlist_size(DList *list, int *count);

/**
 * @brief Obtiene el tamaño total de la lista en bytes.
 * 
 * @param list Lista válida
 * @param bytes Puntero donde se almacena el número de bytes
 * 
 * @return
 * - LIST_OK si se obtuvó el tamaño en bytes
 * - LIST_ERR_NULL si la lista no existe o no fue creada
 */
ListStatus dlist_size_bytes(DList *list, size_t *bytes);

/**
 * @brief Determina si la lista esta vacía.
 * 
 * @param list Lista válida
 * @param is_empty Puntero donde se almecena el resultado
 * 
 * @return
 * - LIST_OK si se determinó el resultado
 * - LIST_ERR_NULL si la lista está vacía
 */
ListStatus dlist_is_empty(DList *list, bool *is_empty);

/**
 * @brief Busca un elemento en la lista.
 * 
 * @param list Lista válida
 * @param value Elemento a buscar
 * @param found Puntero donde se almacena el resultado
 * 
 * @return
 * - LIST_OK si el elemento se encontró o no
 * - LIST_ERR_NULL si la lista no existe o no fue creada
 * - LIST_ERR_EMPTY si la lista está vacía
 */
ListStatus dlist_contains(DList *list, int value, bool *found);

/**
 * @brief Inserta un elemento al final de la lista.
 * 
 * @param list Lista válida
 * @param value Elemento a insertar
 * 
 * @return
 * - LIST_OK si se insertó el elemento correctamente
 * - LIST_ERR_EMPTY si la lista está vacía
 * - LIST_ERR_ALLOC si malloc falla
 */
ListStatus dlist_push_back(DList *list, int value);

/**
 * @brief Inserta un elemento al inicio de la lista.
 * 
 * @param list Lista válida
 * @param value Elemento a insertar
 * 
 * @return
 * - LIST_OK si se insertó el elemento correctamente
 * - LIST_ERR_NULL si la lista no existe o no fue creada
 * - LIST_ERR_ALLOC si malloc falla
 */
ListStatus dlist_push_front(DList *list, int value);

/**
 * @brief Inserta un elemento en cualquier posición válida de la lista.
 * 
 * @param list Lista válida
 * @param value Elemento a insertar
 * @param pos Posición en la que se inserta
 * 
 * @return
 * - LIST_OK si se insertó el elemento correctamente
 * - LIST_ERR_NULL si la lista no existe o no fue creada
 * - LIST_ERR_OUT_OF_RANGE posición fuera de rango
 * - LIST_ERR_ALLOC si malloc falla
 */
ListStatus dlist_insert_in_position(DList *list, int value, int pos);

/**
 * @brief Reemplaza un elemento de la lista.
 * 
 * @param list Lista válida
 * @param value Elemento por reemplazar
 * @param pos Posición del elemento a reemplazar
 * 
 * @return
 * - LIST_OK si se reemplazó el elemento correctamente
 * - LIST_ERR_NULL si la lista no existe o no fue creada
 * - LIST_ERR_OUT_OF_RANGE posición fuera de rango
 */
ListStatus dlist_change_value(DList *list, int value, int pos);

/**
 * @brief Devuelve la posición del elemento a buscar en la lista.
 * 
 * @param list Lista válida
 * @param value Elemento a buscar en la lista
 * @param pos Puntero donde se almacena la posición
 * 
 * @return
 * - LIST_OK si el elemento se encontró
 * - LIST_ERR_NULL si la lista no existe o no fue creada
 * - LIST_ERR_EMPTY si la lista está vacía
 * - LIST_ERR_NOT_FOUND si no se encontró el elemento
 */
ListStatus dlist_search_for_value(DList *list, int value, int *pos);

/**
 * @brief Devuelve el elemento en la posición solicitada
 * 
 * @param list Lista válida
 * @param pos Posición solicitada
 * @param value Puntero donde se almacena el elemento
 * 
 * @return
 * - LIST_OK si el elemento se encontró
 * - LIST_ERR_NULL si la lista no existe o no fue creada
 * - LIST_ERR_EMPTY si la lista está vacía
 * - LIST_ERR_OUT_OF_RANGE posición fuera de rango
 */
ListStatus dlist_search_for_position(DList *list, int pos, int *value);

/**
 * @brief Devuelve el primer elemento de la lista.
 * 
 * @param list Lista válida
 * @param value Putero donde se almacena el elemento
 * 
 * @return
 * - LIST_OK si se devolvió el elemento correctamente
 * - LIST_ERR_NULL si la lista no existe o no fue creada
 * - LIST_ERR_EMPTY si la lista está vacía
 */
ListStatus dlist_front(DList *list, int *value);

/**
 * @brief Devuelve el último elemento de la lista.
 * 
 * @param list Lista válida
 * @param value Puntero donde se almacena el elemento
 * 
 * @return
 * - LIST_OK si se devolvió el elemento correctamente
 * - LIST_ERR_NULL si la lista no existe o no fue creada
 * - LIST_ERR_EMPTY si la lista está vacía
 */
ListStatus dlist_back(DList *list, int *value);

/**
 * @brief Elimina un elemento de la lista en cualquier posición.
 * 
 * @param list Lista válida
 * @param pos Posición del elemento a liberar
 * 
 * @return
 * - LIST_OK si el elemento se eliminó correctamente
 * - LIST_ERR_NULL si la lista no existe o no fue creada
 * - LIST_ERR_EMPTY si la lista está vacía
 * - LIST_ERR_OUT_OF_RANGE posición fuera de rango
 */
ListStatus dlist_free_in_position(DList *list, int pos);

/**
 * @brief Vacía toda la lista.
 * 
 * @param list Lista válida
 * 
 * @return
 * - LIST_OK si la lista se vació correctamente
 * - LIST_ERR_NULL si la lista no existe o no fue creada
 * - LIST_ERR_EMPTY si la lista está vacía
 */
ListStatus dlist_clear(DList *list);

/**
 * @brief Suma todos los elemento de la lista.
 * 
 * @param list Lista válida
 * @param sum Puntero donde se almacena la suma
 * 
 * @return
 * - LIST_OK si la suma se hizó correctamente
 * - LIST_ERR_NULL si la lista no existe o no fue creada
 * - LIST_ERR_EMPTY su la lista está vacía
 */
ListStatus dlist_sum(DList *list, int *sum);

/**
 * @brief Destruye toda la lista.
 * 
 * @param list Lista válida
 * 
 * @return
 * - LIST_OK si la lista se destruyó correctamente
 * - LIST_ERR_NULL si la lista no existe o no fue creada
 */
ListStatus dlist_destroy(DList *list);

/**
 * @brief Imprime la lista.
 * 
 * @param list Lista válida
 */
void dlist_show(DList *list);

#ifdef __cplusplus
}
#endif

#endif /* DLIST_H */