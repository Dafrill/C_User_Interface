
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "call.h"
#include "stats.h"
#include <gtk/gtk.h>



int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GUI");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget* box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), box);

    GtkWidget* button_load = gtk_button_new_with_label("Read a number from file");
    gtk_box_pack_start(GTK_BOX(box), button_load, FALSE, FALSE, 5);

    GtkWidget* entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "Insert a number...");
    gtk_box_pack_start(GTK_BOX(box), entry, FALSE, FALSE, 5);

    GtkWidget* button_submit = gtk_button_new_with_label("Submit");
    gtk_box_pack_start(GTK_BOX(box), button_submit, FALSE, FALSE, 5);

    GtkWidget* text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view), FALSE);

    GtkWidget* scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_vexpand(scrolled_window, TRUE);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
    gtk_box_pack_start(GTK_BOX(box), scrolled_window, TRUE, TRUE, 5);

    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    AppWidgets* app_wdgts = g_malloc(sizeof(AppWidgets));
    app_wdgts->entry = entry;
    app_wdgts->buffer = buffer;
    app_wdgts->window = window;

    g_signal_connect(button_load, "clicked", G_CALLBACK(on_open_file_clicked), app_wdgts);
    g_signal_connect(button_submit, "clicked", G_CALLBACK(on_submit_clicked), app_wdgts);

    gtk_widget_show_all(window);
    gtk_main();

    g_free(app_wdgts);
    return 0;
}