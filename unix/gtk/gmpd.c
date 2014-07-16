#include <gtk/gtk.h>
#include <string.h>

#define MPC_COM "mpc -h 0.0.0.0 -p 1337"

static void
mpd_com(GtkWidget * widget, gpointer data) {
    GError * error = NULL;

    char *com = MPC_COM;
    com = strndup(MPC_COM, BUFSIZ);
    snprintf(com + strlen(com) + 1, BUFSIZ, "%s", data);

    if (!g_spawn_command_line_async((const char *)com, &error) && error) {
        fprintf(stderr, "%s\n", error->message);
        g_error_free(error);
    }
}

int main(int argc, char **argv) {
    GtkWidget *window;
    GtkWidget *pause, *prev, *next;
    GtkWidget *button;
    GtkWidget *grid;

    gtk_init(&argc, &argv);

    // window settings
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "gmpd");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    // button grid settings
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // button previous
    prev = gtk_button_new_with_label("Previous");
    g_signal_connect(prev, "clicked", G_CALLBACK(mpd_com), (gpointer)"prev");
    gtk_grid_attach(GTK_GRID(grid), prev, 0, 0, 1, 1);

    // button next
    next = gtk_button_new_with_label("Next");
    g_signal_connect(next, "clicked", G_CALLBACK(mpd_com), (gpointer)"next");
    gtk_grid_attach(GTK_GRID(grid), next, 1, 0, 1, 1);

    // button quit
    button = gtk_button_new_with_label("Quit");
    g_signal_connect(button, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 1, 1);

    // button play pause
    pause = gtk_button_new_with_label("Play / Pause");
    g_signal_connect(pause, "clicked", G_CALLBACK(mpd_com), (gpointer)"toggle");
    gtk_grid_attach(GTK_GRID(grid), pause, 1, 1, 1, 1);
    
    // show everything
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
