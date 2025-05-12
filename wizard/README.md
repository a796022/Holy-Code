# Wizard - Editor de Árboles Jerárquicos

Una aplicación GTK para crear y editar estructuras de árbol jerárquicas.

## Estructura del Proyecto

### Componentes Principales

#### GUI (`GUI.cs`)
La interfaz gráfica principal de la aplicación, construida con GTK#. Incluye:
- Ventana principal con tamaño y título configurables
- Panel dividido (Paned) con:
  - Árbol jerárquico a la izquierda
  - Panel de entrada a la derecha
- Barra de menú con opciones de Archivo (Abrir/Guardar)
- Soporte para atajos de teclado

#### Gestión de Árboles

- **TreeBuilder** (`TreeBuilder.cs`): 
  - Carga árboles desde archivos de texto
  - Interpreta la indentación (4 espacios) para determinar la jerarquía
  - Construye la estructura del árbol en el TreeStore de GTK

- **TreeNodeSaver** (`TreeNodeSaver.cs`):
  - Guarda el árbol en archivos de texto
  - Preserva la jerarquía usando indentación
  - Procesa recursivamente todos los nodos

#### Gestión de Estado

- **SessionManager** (`SessionManager.cs`):
  - Guarda/restaura el estado de la aplicación
  - Almacena el último archivo abierto
  - Sigue el estándar XDG Base Directory (guarda en ~/.local/share/wizard/)

#### Control de Teclado

- **KeyboardShortcutManager** (`KeyboardShortcutManager.cs`):
  - Maneja atajos de teclado (Ctrl+S, Ctrl+O)
  - Conecta con las acciones de la GUI
  - Gestión limpia de eventos

### Formato de Archivo

Los árboles se guardan en archivos de texto plano usando indentación para representar la jerarquía:
```
Nodo Raíz
    Hijo 1
        Nieto 1
    Hijo 2
        Nieto 2
        Nieto 3
```

### Características

- Crear y editar árboles jerárquicos
- Guardar/cargar árboles desde archivos
- Expandir/colapsar nodos
- Añadir nodos hijos al nodo seleccionado
- Persistencia de la última sesión
- Atajos de teclado para operaciones comunes

### Requisitos

- .NET Core
- GTK# 3
- Sistema operativo compatible con XDG Base Directory (Linux/Unix)
