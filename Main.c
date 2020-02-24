#include "header.h"

int main(int argc, char** argv)
{
	gtk_init(&argc, &argv);
        window           = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        GtkWidget* Sen    = gtk_button_new_with_label("Send File");
        GtkWidget* Res    = gtk_button_new_with_label("Reverse File");
        GtkWidget* fix    = gtk_fixed_new();

        // desine
        gtk_widget_set_usize(GTK_WIDGET(window), 200, 180);
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
        gtk_widget_set_usize(GTK_WIDGET(Sen), 100, 30);
        gtk_widget_set_usize(GTK_WIDGET(Res), 100, 30);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

        //color
        GdkColor back;
        GdkColor btn;

        gdk_color_parse("#0a0a0a", &back);
        gdk_color_parse("#050505", &btn);

        gtk_widget_modify_bg(GTK_WIDGET(Res), GTK_STATE_NORMAL, &btn);
        gtk_widget_modify_bg(GTK_WIDGET(Sen), GTK_STATE_NORMAL, &btn);
        gtk_widget_modify_bg(GTK_WIDGET(window), GTK_STATE_NORMAL, &back);
        // fixed puts
        gtk_fixed_put(GTK_FIXED(fix), Sen, 50, 50);
        gtk_fixed_put(GTK_FIXED(fix), Res, 50, 120);

        // signal
        g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
        g_signal_connect(Sen, "clicked", G_CALLBACK(Sender), NULL);
        g_signal_connect(Sen, "clicked", G_CALLBACK(MainHide), NULL);
        g_signal_connect(Res, "clicked", G_CALLBACK(Reserver), NULL);
        g_signal_connect(Res, "clicked", G_CALLBACK(MainHide), NULL);

        // show
        gtk_container_add(GTK_CONTAINER(window), fix);
        gtk_widget_show_all(GTK_WIDGET(window));
	gtk_main();
}
