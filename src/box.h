#ifndef BOX_H
#define BOX_H

GtkWidget *crear_box(GtkOrientation orientation, int spacing);

void agregar_widget_box(GtkWidget *box, GtkWidget *widget, gboolean expand, gboolean fill, guint padding);

#endif /* BOX_H */