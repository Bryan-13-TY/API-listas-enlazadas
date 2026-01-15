#ifndef LIST_STATUS_h
#define LIST_STATUS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @enum ListStatus
 * @brief Códigos de estado para las operaciones de la lista.
 * 
 * Todas las funciones de la APLI devuelven uno de los estos valores
 * para indicar éxito o el tipo de error ocurrido.
 */
typedef enum {
    LIST_OK = 0, /**< Operación exitosa */
    LIST_ERR_NULL = -1, /**< Lista NULL */
    LIST_ERR_EMPTY = -2, /**< Lista vacía */
    LIST_ERR_ALLOC = -3, /**< Error al reservar memoria */
    LIST_ERR_OUT_OF_RANGE = -4, /**< Posición fuera de rango */
    LIST_ERR_NOT_FOUND = -5 /**< Elemento no encontrado */
} ListStatus;

#ifdef __cplusplus
}
#endif

#endif /* LIST_STATUS_H */