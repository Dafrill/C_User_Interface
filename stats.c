#include <stdio.h>
#include "stats.h"
#include <gtk/gtk.h>


void on_open_file_clicked(GtkWidget* widget, gpointer user_data) {
    AppWidgets* app_wdgts = (AppWidgets*) user_data;

    GtkWidget* dialog = gtk_file_chooser_dialog_new("Choose a file",
        GTK_WINDOW(app_wdgts->window),
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_Open", GTK_RESPONSE_ACCEPT,
        NULL);

    gint res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        FILE* file = fopen(filename, "r");
        double loaded_number = 0.0;

        if (file) {
            if (fscanf(file, "%lf", &loaded_number) == 1) {
                gtk_text_buffer_set_text(app_wdgts->buffer, "", -1); 
                summary(loaded_number, app_wdgts->buffer);
            } else {
                gtk_text_buffer_set_text(app_wdgts->buffer, "Error: failed to read number from file.\n", -1);
            }
            fclose(file);
        } else {
            gtk_text_buffer_set_text(app_wdgts->buffer, "Error: could not open file.\n", -1);
        }

        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

void on_submit_clicked(GtkWidget* widget, gpointer user_data) {
    AppWidgets* app_wdgts = (AppWidgets*) user_data;

    if (!GTK_IS_ENTRY(app_wdgts->entry) || !GTK_IS_TEXT_BUFFER(app_wdgts->buffer)) {
        g_warning("Invalid widgets passed to on_submit_clicked");
        return;
    }

    const char* text = gtk_entry_get_text(GTK_ENTRY(app_wdgts->entry));
    char* endptr;
    double value = strtod(text, &endptr);

    if (endptr == text || *endptr != '\0') {

        gtk_text_buffer_set_text(app_wdgts->buffer, "Invalid number entered in the text field.\n", -1);
        return;
    }

    
    gtk_text_buffer_set_text(app_wdgts->buffer, "", -1);

    summary(value, app_wdgts->buffer);
}

void print_stats(CallQueue* queue, GtkTextBuffer* buffer) {
    int totalCalls = 0;
    double totalDuration = 0;
    double totalWaitTime = 0;
    double currentTime = 0;

    Call* current = queue->head;

    while (current) {
        totalCalls++;

       
        if (current->arrivalTime > currentTime) {
            currentTime = current->arrivalTime;
        }

        
        double waitTime = currentTime - current->arrivalTime;
        totalWaitTime += waitTime;

        
        currentTime += current->duration;

        
        totalDuration += current->duration;

        current = current->next;
    }

   
    char buf[512];
    if (totalCalls > 0) {
        snprintf(buf, sizeof(buf),
            "Call statistics:\n"
            "Number of calls: %d\n"
            "Average call duration: %.2f seconds\n"
            "Average waiting time: %.2f seconds\n"
            "Total switchboard operation time: %.2f seconds\n",
            totalCalls, totalDuration / totalCalls, totalWaitTime / totalCalls, currentTime);
    } else {
        snprintf(buf, sizeof(buf), "No calls to display.\n");
    }

  
    gtk_text_buffer_set_text(buffer, buf, -1);
}

void summary(double lambda, GtkTextBuffer* buffer) {
    int liczbaPolaczen = generate_poisson(lambda);
    char result[256];
    sprintf(result, "Generated %d calls.\n", liczbaPolaczen);
    gtk_text_buffer_set_text(buffer, result, -1);

    CallQueue queue;
    init_queue(&queue);

    for (int i = 0; i < liczbaPolaczen; i++) {
        int arrival = rand() % 3600;
        double duration = generate_normal(180.0, 60.0);
        enqueue(&queue, i + 1, arrival, duration);
    }

   
    print_stats(&queue, buffer);

    clear_queue(&queue);
}

