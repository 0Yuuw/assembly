#include <gtk/gtk.h>
#include <complex.h>
#include <math.h>

complex double complex_sqrt(complex double x) {
    double complex sqrt_x = csqrt(x);
    return sqrt_x;
}

static void calculate(GtkWidget *widget, gpointer data) {
    GtkEntry *real_entry = GTK_ENTRY(data);
    const gchar *real_str = gtk_entry_get_text(real_entry);
    double real_part = atof(real_str);

    GtkEntry *imaginary_entry = GTK_ENTRY(g_object_get_data(G_OBJECT(real_entry), "imaginary"));
    const gchar *imaginary_str = gtk_entry_get_text(imaginary_entry);
    double imaginary_part = atof(imaginary_str);

    complex double num = real_part + imaginary_part * I;
    complex double result = complex_sqrt(num);

    char result_str[100];
    snprintf(result_str, sizeof(result_str), "%.2f + %.2fi", creal(result), cimag(result));

    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(widget)),
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               "Square root: %s",
                                               result_str);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *real_label;
    GtkWidget *imaginary_label;
    GtkWidget *real_entry;
    GtkWidget *imaginary_entry;
    GtkWidget *calculate_button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 150);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    real_label = gtk_label_new("Real:");
    gtk_grid_attach(GTK_GRID(grid), real_label, 0, 0, 1, 1);

    imaginary_label = gtk_label_new("Imaginary:");
    gtk_grid_attach(GTK_GRID(grid), imaginary_label, 0, 1, 1, 1);

    real_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), real_entry, 1, 0, 1, 1);

    imaginary_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), imaginary_entry, 1, 1, 1, 1);
    g_object_set_data(G_OBJECT(real_entry), "imaginary", imaginary_entry);

    calculate_button = gtk_button_new_with_label("Calculate");
    g_signal_connect(calculate_button, "clicked", G_CALLBACK(calculate), real_entry);
    gtk_grid_attach(GTK_GRID(grid), calculate_button, 0, 2, 2, 1);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
