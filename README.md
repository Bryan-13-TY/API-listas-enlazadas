# API-listas-enlazadas
API para listas simplemente y doblemente enlazadas en lenguaje C.

El proyecto oculta las estruturas internas, maneja errores mediante un `enum` y sigue una convención consistente para todas las funciones.

## 🎯 Características
- ✅ Listas simplemente enlazadas (slist)
- ✅ Listas doblemente enlazadas (dlist)
- ✅ Manejo de errores con `ListStatus`
- ✅ API limpia y consistente
- ✅ Sin variables globales

---

## 📁 Estructura de la API
```text
Listas-enlazadas-API/
├── examples/
│   ├── dlist_example.c
│   └── slist_example.c
├── include/
│   ├── dlist.h
│   ├── list_status.h
│   └── slist.h
├── src/
│   ├── dlist.c
│   └── slist.c
├── .gitignore
└── README.md
```

---

## 🚀 Uso de la API
### 📦 Incluir la API a tu proyecto
Copia la carpeta `include/` y los archivos `.c` que necesites (`slist.c` o `dlist.c`) dentro de tu proyecto.

En tu código fuente:
```text
#include "slist.h"
```
Si usas listas doblemente enlazadas:
```text
#include "dlist.h"
```

### 🧪 Ejemplo mínimo de uso
```text
#include "slist.h"
#include <stdio.h>

int main(void) {
    SList *list = slist_create(); // crear lista

    slist_push_back(list, 1);
    slist_push_front(list, 15);
    slist_push_back(list, 9);

    slist_show(list);
    slist_destroy(list);
}
```

### ⚠️ Manejo de errores
Todas las fuciones devuelve un valor de tipo `ListStatus`, a excepción de `slits_show`, que solo imprime la lista.
```text
ListStatus list_status; // crear estatus de la lista

if (list_status != LIST_OK) {
    /* manejar error */
}
```

### Estados posibles (`ListStatus`)
- `LIST_OK` - Operación exitosa
- `LIST_ERR_NULL` - Lista NULL
- `LIST_ERR_EMPTY` - Lista vacía
- `LIST_ERR_ALLOC` - Error al reservar memoria
- `LIST_ERR_OUT_OF_RANGE` - Posición fuera de rango
- `LIST_ERR_NOT_FOUND` - Elemento no encontrado

### Convenciones de la API
- Todas las funciones devuelve `ListStatus`, excepto `slist_show` 
- Los datos se devuelven mediante parámetros de salida
- `list == NULL` siempre se considera un error 
- Una lista vacía se defin como `list->head == NULL`
- Las estructuras internas no son accesibles al usurio

---

## 🔧 Compilación
⚠️ Todos los comandos deben ejecutarse desde la raíz del proyecto.

### Compilación básica (listas simples)
```text
gcc -Wall -Wextra -Iinclude src/slist.c examples/slist_example.c -o app
```

### Compilación por etapas (recomendado)
```text
gcc -Wall -Wextra -Iinclude src/slist.c src/dlist.c examples/slist_example.c -o app
```

### Compilación por etapas (recomendada)
```text
gcc -Iinclude -c src/slist.c
gcc -Iinclude -c src/dlist.c
gcc -Iinclude -c examples/slist_example.c

gcc slist.o dlist.o slist_example.o -o app
```

---

## 📚 Ejemplos (no disponibles aún)
La carpeta `examples/` contiene programas de ejemplo que muestran cómo usar la API correctamente.