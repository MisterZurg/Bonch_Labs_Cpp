#include <gtk/gtk.h>
#include <cairo.h>
/*
 * Задание
    С использованием библиотеки Gtk+ разработать программу,
    которая будет отображать на окне фигуру – прямоугольник.
    У окна программы должно быть меню, в котором есть 3 пункта со следующими элементами.
        1.	Меню «File»
	            Элемент «Exit» - выход из программы
        2.	Меню «Brush»
                Элемент «Red» - прямоугольник рисуется красным цветом заливки
                Элемент «Yellow» - прямоугольник рисуется жёлтым цветом заливки
                Элемент «Brown» - прямоугольник рисуется коричневым цветом заливки
        3.	Меню «Pen»
                Элемент «Green» - контур прямоугольника рисуется зелёным цветом
                Элемент «Blue» - контур прямоугольника рисуется синим цветом
                Элемент «Pink» - контур прямоугольника рисуется розовым цветом
 */

int color = 0;

// =====================

static void red_clicked(GtkWidget *widget, gpointer data) {
    color = 1;
    gtk_widget_queue_draw((GtkWidget *) data);
}

static void yellow_clicked(GtkWidget *widget, gpointer data) {
    color = 2;
    gtk_widget_queue_draw((GtkWidget *) data);
}

static void brown_clicked(GtkWidget *widget, gpointer data) {
    color = 3;
    gtk_widget_queue_draw((GtkWidget *) data);
}

static void green_clicked(GtkWidget *widget, gpointer data) {
    color = 4;
    gtk_widget_queue_draw((GtkWidget *) data);
}

static void blue_clicked(GtkWidget *widget, gpointer data) {
    color = 5;
    gtk_widget_queue_draw((GtkWidget *) data);
}

static void pink_clicked(GtkWidget *widget, gpointer data) {
    color = 6;
    gtk_widget_queue_draw((GtkWidget *) data);
}

// =====================

static void do_drawing_red(cairo_t *cr) {
    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_rectangle(cr, 10, 10, 150, 100);
    cairo_fill(cr);
}

static void do_drawing_yellow(cairo_t *cr) {
    cairo_set_source_rgb(cr, 1, 1, 0);
    cairo_rectangle(cr, 10, 10, 150, 100);
    cairo_fill(cr);
}

static void do_drawing_brown(cairo_t *cr) {
    cairo_set_source_rgb(cr, 0.5, 0.3, 0.05);
    cairo_rectangle(cr, 10, 10, 150, 100);
    cairo_fill(cr);
}

static void do_drawing_green(cairo_t *cr) {
    cairo_set_line_width(cr, 3.0);
    cairo_set_source_rgb(cr, 0, 1, 0);
    cairo_rectangle(cr, 10, 10, 150, 100);
    cairo_stroke(cr);
}

static void do_drawing_blue(cairo_t *cr) {
    cairo_set_line_width(cr, 3.0);
    cairo_set_source_rgb(cr, 0, 0, 1);
    cairo_rectangle(cr, 10, 10, 150, 100);
    cairo_stroke(cr);
}

static void do_drawing_pink(cairo_t *cr) {
    cairo_set_line_width(cr, 3.0);
    cairo_set_source_rgb(cr, 1, 0.4, 0.7);
    cairo_rectangle(cr, 10, 10, 150, 100);
    cairo_stroke(cr);
}

gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,
                       gpointer user_data) {
    switch (color) {
        case 1:
            do_drawing_red(cr);
            break;
        case 2:
            do_drawing_yellow(cr);
            break;
        case 3:
            do_drawing_brown(cr);
            break;
        case 4:
            do_drawing_green(cr);
            break;
        case 5:
            do_drawing_blue(cr);
            break;
        case 6:
            do_drawing_pink(cr);
            break;
    }

    return FALSE;
}

// =========================================================

int main(int argc, char *argv[]) {

    GtkWidget *window;
    GtkWidget *box;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    gtk_window_set_title(GTK_WINDOW(window), "Rectangle drawer");

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    GtkWidget *menubar = gtk_menu_bar_new();
    GtkWidget *fileMenu = gtk_menu_new();
    GtkWidget *brushMenu = gtk_menu_new();
    GtkWidget *penMenu = gtk_menu_new();

    GtkWidget *fileMi = gtk_menu_item_new_with_label("File");
    GtkWidget *quitMi = gtk_menu_item_new_with_label("Quit");
    GtkWidget *brushMi = gtk_menu_item_new_with_label("Brush");
    GtkWidget *redMi = gtk_menu_item_new_with_label("Red");
    GtkWidget *yellowMi = gtk_menu_item_new_with_label("Yellow");
    GtkWidget *brownMi = gtk_menu_item_new_with_label("Brown");
    GtkWidget *penMi = gtk_menu_item_new_with_label("Pen");
    GtkWidget *greenMi = gtk_menu_item_new_with_label("Green");
    GtkWidget *blueMi = gtk_menu_item_new_with_label("Blue");
    GtkWidget *pinkMi = gtk_menu_item_new_with_label("Pink");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitMi);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(brushMi), brushMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(brushMenu), redMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(brushMenu), yellowMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(brushMenu), brownMi);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(penMi), penMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(penMenu), greenMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(penMenu), blueMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(penMenu), pinkMi);

    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), brushMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), penMi);

    gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 0);

    GtkWidget *darea = gtk_drawing_area_new();

    gtk_widget_set_size_request(darea, 300, 300);

    gtk_box_pack_start(GTK_BOX(box), darea, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(quitMi), "activate",
                     G_CALLBACK(gtk_main_quit), NULL);

    g_signal_connect(G_OBJECT(darea), "draw",
                     G_CALLBACK(on_draw_event), NULL);

    g_signal_connect(G_OBJECT(redMi), "activate",
                     G_CALLBACK(red_clicked), darea);

    g_signal_connect(G_OBJECT(yellowMi), "activate",
                     G_CALLBACK(yellow_clicked), darea);

    g_signal_connect(G_OBJECT(brownMi), "activate",
                     G_CALLBACK(brown_clicked), darea);

    g_signal_connect(G_OBJECT(greenMi), "activate",
                     G_CALLBACK(green_clicked), darea);

    g_signal_connect(G_OBJECT(blueMi), "activate",
                     G_CALLBACK(blue_clicked), darea);

    g_signal_connect(G_OBJECT(pinkMi), "activate",
                     G_CALLBACK(pink_clicked), darea);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
