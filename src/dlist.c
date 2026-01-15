#include "dlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
} Node;

struct DList {
    Node *head;
    Node *tail;
    int count;
};

DList *dlist_create(void) {
    DList *list = malloc(sizeof(DList)); // creamos la lista

    if (!list) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    return list;
}

ListStatus dlist_size(DList *list, int *count) {
    if (!list) return LIST_ERR_NULL;

    *count = list->count;
    return LIST_OK;
}

ListStatus dlist_size_bytes(DList *list, size_t *bytes) {
    if (!list) return LIST_ERR_NULL;
    if (!bytes) return LIST_ERR_NULL;

    *bytes = sizeof(DList) + list->count * sizeof(Node); // tamaño de DList + tamaño de todos los Node
    return LIST_OK;
}

ListStatus dlist_is_empty(DList *list, bool *is_empty) {
    if (!list->head) return LIST_ERR_EMPTY;

    *is_empty = (list->head == NULL);
    return LIST_OK;
}

ListStatus dlist_contains(DList *list, int value, bool *found) {
    if (!list) return LIST_ERR_NULL;
    if (!list->head) return LIST_ERR_EMPTY;

    Node *actual = list->head;

    while (actual) { // mover actual a la posición
        if (actual->value == value) { // se encuentra
            *found = true;
            return LIST_OK;
        }

        actual = actual->next;
    }

    *found = false;
    return LIST_OK;
}

ListStatus dlist_push_back(DList *list, int value) {
    if (!list) return LIST_ERR_NULL;

    Node *new = malloc(sizeof(Node)); // nuevo nodo
    if (!new) return LIST_ERR_ALLOC;

    new->value = value;
    new->next = NULL;
    new->prev = NULL;

    if (!list->head) { // lista vacía
        list->head = new;
        list->tail = new;
    } else {
        list->tail->next = new;
        new->prev = list->tail;
        list->tail = new;
    }

    list->count++;
    return LIST_OK;
}

ListStatus dlist_push_front(DList *list, int value) {
    if (!list) return LIST_ERR_NULL;

    Node *new = malloc(sizeof(Node)); // nuevo nodo
    if (!new) return LIST_ERR_ALLOC;

    new->value = value;
    new->next = NULL;
    new->prev = NULL;

    if (!list->head) { // lista vacía
        list->head = new;
        list->tail = new;
    } else {
        list->head->prev = new;
        new->next = list->head;
        list->head = new;
    }

    list->count++;
    return LIST_OK;
}

static ListStatus dlist_validate_position(DList *list, int pos, int cond) {
    if (cond == 0) {
        if (pos > list->count + 1 || pos < 1) return LIST_ERR_OUT_OF_RANGE;
    } else {
        if (pos > list->count || pos < 1) return LIST_ERR_OUT_OF_RANGE;
    }

    return LIST_OK;
}

ListStatus dlist_insert_in_position(DList *list, int value, int pos) {
    if (!list) return LIST_ERR_NULL;
    if (dlist_validate_position(list, pos, 0) != LIST_OK) return LIST_ERR_OUT_OF_RANGE;

    if (pos == 1) { // insertar al inicio
        return dlist_push_front(list, value);
    }

    if (pos == list->count + 1) { // insertar al final
        return dlist_push_back(list, value);
    }

    // cualquiera entre head y tail
    Node *new = malloc(sizeof(Node)); // número a insertar
    if (!new) return LIST_ERR_ALLOC;
    new->value = value;

    Node *before_new = list->head; // posición antes del la indicada

    int i = 1;
    while (before_new && i < pos - 1) { // mover before_new antes de pos
        before_new = before_new->next;
        i++;
    }

    new->next = before_new->next; // apuntamos al siguiente de new
    before_new->next->prev = new; // apuntamos el siguiente de new a new
    new->prev = before_new; // apuntamos a before_new
    before_new->next = new; // apuntamos a new
    list->count++;
    return LIST_OK;
}

ListStatus dlist_change_value(DList *list, int value, int pos) {
    if (!list) return LIST_ERR_NULL;
    if (dlist_validate_position(list, pos, 1) != LIST_OK) return LIST_ERR_OUT_OF_RANGE;

    Node *actual = list->head;

    for (int i = 0; i < pos - 1; i++) { // mover actual a la posición
        actual = actual->next;
    }

    actual->value = value;
    return LIST_OK;
}

ListStatus dlist_search_for_value(DList *list, int value, int *pos) {
    if (!list) return LIST_ERR_NULL;
    if (!list->head) return LIST_ERR_EMPTY;

    Node *actual = list->head;
    int pos_local = 0;
    bool found = false;

    while (actual) { // mover actual a la posición
        if (actual->value == value) { // se encuentra
            found = true;
            break;
        }

        actual = actual->next;
        pos_local++;
    }

    if (found) {
        *pos = pos_local;
        return LIST_OK;
    }

    return LIST_ERR_NOT_FOUND;
}

ListStatus dlist_search_for_position(DList *list, int pos, int *value) {
    if (!list) return LIST_ERR_NULL;
    if (!list->head) return LIST_ERR_EMPTY;
    if (dlist_validate_position(list, pos, 1) != LIST_OK) return LIST_ERR_OUT_OF_RANGE;

    Node *actual = list->head;

    int i = 1;
    while (actual && i < pos) { // mover actual a pos
        actual = actual->next;
        i++;
    }

    *value = actual->value;
    return LIST_OK;
}

ListStatus dlist_front(DList *list, int *value) {
    if (!list) return LIST_ERR_NULL;
    if (!list->head) return LIST_ERR_EMPTY;

    *value = list->head->value;
    return LIST_OK;
}

ListStatus dlist_back(DList *list, int *value) {
    if (!list) return LIST_ERR_NULL;
    if (!list->tail) return LIST_ERR_EMPTY;

    *value = list->tail->value;
    return LIST_OK;
}

ListStatus dlist_free_in_position(DList *list, int pos) {
    if (!list) return LIST_ERR_NULL;
    if (!list->head) return LIST_ERR_EMPTY;

    Node *actual = list->head;
    Node *after_actual = NULL;
    Node *before_actual = NULL;

    if (pos == list->count) { // último de la lista
        int i = 1;
        while (actual && i < pos - 1) { // mover actual antes de pos
            actual = actual->next;
            i++;
        }

        after_actual = actual->next; // apuntamos al último
        free(after_actual); // liberamos al último

        list->tail = actual; // actualizamos tail
        list->tail->next = NULL; // apuntamos a NULL
        list->count--;
        return LIST_OK;
    }

    if (pos == 1) { // primero de la lista
        actual = list->head;
        list->head = list->head->next; // actualizamos head
        free(actual); // liberamos al primero
        list->head->prev = NULL;
        list->count--;
        return LIST_OK;
    }

    if (dlist_validate_position(list, pos, 1) != LIST_OK) return LIST_ERR_OUT_OF_RANGE;

    // cualquiera entre head y tail
    int i = 1;
    while (actual && i < pos - 1) { // mover actual antes de pos
        actual = actual->next;
        i++;
    }

    before_actual = actual; // apuntamos al anterior
    after_actual = actual->next->next; // apuntamos al siguiente
    free(actual->next); // liberamos
    before_actual->next = after_actual; // unimos las listas
    after_actual->prev = before_actual; // unimos las listas
    list->count--;
    return LIST_OK;
}

ListStatus dlist_clear(DList *list) {
    if (!list) return LIST_ERR_NULL;
    if (!list->head) return LIST_ERR_EMPTY;

    Node *actual = list->head;
    Node *next = NULL;

    while (actual) {
        next = actual->next; // nodo siguiente
        free(actual); // liberamos nodo actual
        actual = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    return LIST_OK;
}

ListStatus dlist_sum(DList *list, int *sum) {
    if (!list) return LIST_ERR_NULL;
    if (!list->head) return LIST_ERR_EMPTY;

    Node *actual = list -> head;
    int total = 0;

    while (actual) {
        total += actual->value;
        actual = actual->next;
    }

    *sum = total;
    return LIST_OK;
}

ListStatus dlist_destroy(DList *list) {
    if (!list) return LIST_ERR_NULL;

    slist_clear(list);
    free(list);
    return LIST_OK;
}

void dlist_show(DList *list) {
    Node *actual = list->head;

    printf("\n\nElementos de la lista: ");
    printf("NULL <-> ");
    while (actual) {
        printf("%d <-> ", actual->value);
        actual = actual->next;
    }

    printf("NULL");

    actual = list->tail;

    printf("NULL <-> ");
    while (actual) {
        printf("%d <-> ", actual->value);
        actual = actual->prev;
    }

    printf("NULL");
}