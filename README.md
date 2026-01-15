# API-listas-enlazadas
API para listas simplemente y doblemente enlazadas en lenguaje C.

El proyecto oculta las estruturas internas, maneja errores mediante un `enum` y sigue una convención consistente para todas las funciones.

## 🎯 Características
- ✅ Listas simplemente enlazadas (slist)
- ✅ Listas doblemente enlazadas (dlist)
- ✅ Manejo de errores con `ListStatus`
- ✅ API limpia y consistente
- ✅ Sin variables globales

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

## Uso de la API
### Incluir la API a tu proyecto
Copia la carpeta `include` y los archivos `.c` que necesites (`slist.c` o `dlist.c`) dentro de tu proyecto.

En tu código fuente:

```text
#include "slist.h"
```

Si usas listas doblemente enlazadas:

```text
#include "dlist.h"
```