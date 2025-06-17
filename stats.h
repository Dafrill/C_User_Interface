#ifndef STATS_H
#define STATS_H

#include "call.h"
#include <gtk/gtk.h>
 typedef struct {
        GtkWidget* entry;
        GtkTextBuffer* buffer;
        GtkWidget* window; 
    } AppWidgets;


void print_stats(CallQueue* queue, GtkTextBuffer* buffer);

void on_open_file_clicked(GtkWidget* widget, gpointer user_data);
void on_submit_clicked(GtkWidget* widget, gpointer user_data);
void print_stats(CallQueue* queue, GtkTextBuffer* buffer);
void summary(double lambda, GtkTextBuffer* buffer);

#endif
