#include "slist.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    // valores devueltos por parámetros
    
    int count = 0; // número de nodos
    int pos = 0; // posición devuelta
    int sum = 0; // suma de toda la lista
    int value = 0; // valor del nodo devuelto
    bool found = false; // búsqueda de un número
    size_t list_bytes; // tamaño de la lista en bytes

    SList *list = slist_create(); // crear lista
    ListStatus list_status; // crear estatus de la lista

    // insertar valores en la lista
    list_status = slist_push_back(list, 1);
    if (LIST_OK == list_status) printf("\n>> Numero insertado correctamente");
    list_status = slist_push_front(list, 2);
    if (LIST_OK == list_status) printf("\n>> Numero insertado correctamente");
    list_status = slist_push_front(list, 3);
    if (LIST_OK == list_status) printf("\n>> Numero insertado correctamente");
    
    list_status = slist_insert_in_position(list, 10, 4);
    if (LIST_OK == list_status) printf("\n>> Numero insertado correctamente");
    if (LIST_ERR_OUT_OF_RANGE == list_status) printf("\n>> Posicion invalida");

    list_status = slist_push_back(list, 4);
    if (LIST_OK == list_status) printf("\n>> Numero insertado correctamente");
    list_status = slist_push_front(list, 5);
    if (LIST_OK == list_status) printf("\n>> Numero insertado correctamente");

    slist_show(list);

    // operaciones sobre la lista
    list_status = slist_contains(list, 3, &found);
    if (LIST_OK == list_status && found) printf("\n>> El numero esta en la lista");
    if (LIST_OK == list_status && !found) printf("\n>> El numero no esta en la lista");

    list_status == slist_free_in_position(list, 4);
    if (LIST_OK == list_status) printf("\n>> Numero eliminado correctamente");

    slist_show(list);

    list_status = slist_search_for_position(list, 3, &value);
    if (LIST_OK == list_status) printf("\n>> Numero en la posicion 3: %d", value);

    list_status = slist_search_for_value(list, 5, &pos);
    if (LIST_OK == list_status) printf("\n>> Posicion del numero 5: %d", pos);

    list_status = slist_size(list, &count);
    if (LIST_OK == list_status) printf("\n>> Hay %d numeros en la lista", count);

    list_status = slist_size_bytes(list, &list_bytes);
    if (LIST_OK == list_status) printf("\n>> Tamaño de la liste en bytes: %zu", list_bytes);

    list_status = slist_sum(list, &sum);
    if (LIST_OK == list_status) printf("\n>> Suma de los números en la lista: %d", sum);

    // destruir la lista
    list_status = slist_destroy(list);
    if (LIST_OK == list_status) printf("\n>> Lista destruida correctamente");

    return 0;
}