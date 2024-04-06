#ifndef TREE_H
#define TREE_H

// GtkTreeView debe estar asociado a un modelo de datos para mostrar información
GtkTreeStore *crear_modelo_datos_tree();

GtkWidget *crear_tree_view(GtkTreeStore *store);

void agregar_nodo_tree(GtkTreeStore *store, GtkTreeIter *padre, const char *texto);

void crear_columna_tree_view(GtkWidget *tree_view, const char *titulo);

#endif /* TREE_H */