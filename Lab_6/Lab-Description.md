# Лабораторная работа №6. Графический интерфейс GTK+
## Цели работы
1. Освоить работу с графическими окнами с использованием библиотеки GTK+.
## Справка
### Простое приложение GTK
```cpp
#include <gtk/gtk.h>

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    GtkWidget *p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(p_window, "destroy",
                     G_CALLBACK(gtk_main_quit),
                     NULL);
    gtk_widget_show(p_window);
    gtk_main();
    return 0;
}
```
### Обработка событий
```cpp
#include <gtk/gtk.h>

void on_destroy() {
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    GtkWidget *p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect( p_window, "destroy", G_CALLBACK(on_destroy), NULL);
    gtk_widget_show(p_window);
    gtk_main();
    return 0;
}
```
### Рисование с cairo
```cpp
g_signal_connect(p_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
GtkWidget *p_draw = gtk_drawing_area_new();
gtk_container_add(GTK_CONTAINER(p_window), p_draw);
g_signal_connect(G_OBJECT(p_draw),
                 "expose",
                 G_CALLBACK(on_draw), NULL);
gboolean on_draw(GtkWidget *widget, GdkEventExpose *event, gpointer data) { 
    cairo_t *c = gdk_cairo_create(gtk_widget_get_window(widget)); cairo_move_to(c, 30, 30);
    cairo_show_text(c, "Text");
    cairo_set_line_width(c, 1.0); cairo_set_source_rgb(c, 0, 0, 0); cairo_rectangle(c, 10, 10, 100, 100);
    cairo_stroke(c);
    cairo_destroy(c);
    g_print("draw\n");
    return TRUE; 
}
```
### Создание меню в GTK
```cpp
vbox = gtk_vbox_new(FALSE, 0);
gtk_container_add(GTK_CONTAINER(p_window), vbox);
GtkWidget *menubar = gtk_menu_bar_new();
GtkWidget *menu_file = gtk_menu_new();
GtkWidget *mi_file = gtk_menu_item_new_with_label("File");
GtkWidget *mi_quit = gtk_menu_item_new_with_label("Quit");
gtk_menu_item_set_submenu(GTK_MENU_ITEM(mi_file), menu_file); gtk_menu_shell_append(GTK_MENU_SHELL(menu_file), mi_quit);
gtk_menu_shell_append(GTK_MENU_SHELL(menubar), mi_file);
gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);
```
### Сборка проекта при помощи GNU C++
Для сборки необходимо наличие пакета с библиотеками для разработки Gtk+. 

Для установки в **Debian, Ubuntu**:
```sh
sudo apt-get install libgtk3.0-dev
```
Для установки в **RedHat, CentOS**:
```sh
sudo yum install gtk3-devel
```
В некоторых сборках **GNU/Linux** при сборке проекта требуется указать пути к установленной библиотеке для gcc/g++. Для этого поможет утилита `pkg-config`.
```sh
g++ -o prog prog.cpp `pkg-config --cflags --libs gtk+-3.0`
```

## Задание лабораторной работы:
С использованием библиотеки Gtk+ разработать программу, которая будет отображать на окне фигуру – прямоугольник.

У окна программы должно быть меню, в котором есть 3 пункта со следующими элементами.
1. Меню «File»
   
   Элемент «Exit» - выход из программы
2. Меню «Brush»

    Элемент «Red» - прямоугольник рисуется красным цветом заливки
    
    Элемент «Yellow» - прямоугольник рисуется жёлтым цветом заливки

    Элемент «Brown» - прямоугольник рисуется коричневым цветом заливки
3. Меню «Pen»

    Элемент «Green» - контур прямоугольника рисуется зелёным цветом

    Элемент «Blue» - контур прямоугольника рисуется синим цветом

    Элемент «Pink» - контур прямоугольника рисуется розовым цветом
