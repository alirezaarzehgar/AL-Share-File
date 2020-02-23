#include <gtk/gtk.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int port;
int new_s;
struct sockaddr_in sa;

int Send(GtkWidget* w, GtkFileSelection *fs);
int Send_filew();
void Port_create(GtkWidget* w, GtkSpinButton* s);

int main(int argc, char** argv)
{
        // create ui gtk
	gtk_init(&argc, &argv);
	GtkWidget* win    = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget* select_send   = gtk_button_new_with_label("Send file");
        GtkWidget* fix    = gtk_fixed_new();
        GtkWidget* spi    = gtk_spin_button_new(((GtkAdjustment*) gtk_adjustment_new (8080, 0, 99999, 1, 0, 0)) , 0, 0);

	// desine
	gtk_widget_set_usize(GTK_WIDGET(win), 200, 200);
	gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
	gtk_widget_set_usize(GTK_WIDGET(select_send), 100, 30);
        gtk_widget_set_usize(GTK_WIDGET(spi), 100, 30);
	gtk_window_set_title(GTK_WINDOW(win), "Sender");

	//color
	GdkColor back;
	GdkColor btn;

	gdk_color_parse("#0a0a0a", &back);
	gdk_color_parse("#050505", &btn);

	gtk_widget_modify_bg(GTK_WIDGET(select_send), GTK_STATE_NORMAL, &btn);
	gtk_widget_modify_bg(GTK_WIDGET(win), GTK_STATE_NORMAL, &back);
	// fixed puts
	gtk_fixed_put(GTK_FIXED(fix), select_send, 50, 50);
	gtk_fixed_put(GTK_FIXED(fix), spi, 50, 120);

	// signal
	g_signal_connect(win, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
        g_signal_connect(select_send, "clicked", G_CALLBACK(Port_create), (GtkSpinButton*)spi);
	g_signal_connect(select_send, "clicked", G_CALLBACK(Send_filew), NULL);

	// show
	gtk_container_add(GTK_CONTAINER(win), fix);
	gtk_widget_show_all(GTK_WIDGET(win));
	gtk_main();
	return 0;
}

int Send(GtkWidget* w, GtkFileSelection *fs)
{
        int server;
        if((server = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
        	printf("error for creat socket!\n");
        	return -1;
	}

        sa.sin_family = AF_INET;
        sa.sin_addr.s_addr = INADDR_ANY;
        sa.sin_port = htons(port);

        if(bind(server, (struct sockaddr *)&sa, sizeof(sa)) < 0)
        {
        	printf("port not found!\n");
        	return -1;
	}

        if(listen(server, 3) < 0)
        {
        	printf("error for listenning!\n");
        	return -1;
	}

        int size = sizeof(sa);
        if((new_s = accept(server, (struct sockaddr *)&sa, (socklen_t *)&size)) < 0)
        {
        	printf("error for accept!\n");
        	return -1;
	}

	char str[1024];
	char* file_media = (char*) malloc (sizeof(char*)*100000000);

        read(new_s, str, 1024);

	FILE* f = fopen(gtk_file_selection_get_filename (GTK_FILE_SELECTION (fs)), "r");

	g_print("send file\n");

	int KK;
	for(KK = 0; !feof(f); KK++)
	{
		int tmp = fgetc(f);

		if(feof(f)) break;

		file_media[KK] = tmp;
	}

	send(new_s, file_media, KK, 0);

	close(new_s);
	close(server);

	char Mess[1024];
	sprintf(Mess, "your file sended to port %d", port);

        // message
        GtkWidget* box = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CANCEL, "Message");
        gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(box), Mess);
        int response = gtk_dialog_run(GTK_DIALOG(box));


	return 0;
}

int Send_filew()
{

        GtkWidget* filew = gtk_file_selection_new ("File selection");

        g_signal_connect (filew , "destroy", G_CALLBACK (gtk_widget_destroy), NULL);

        g_signal_connect (GTK_FILE_SELECTION (filew)->ok_button, "clicked", G_CALLBACK (Send), (gpointer) filew);

        g_signal_connect_swapped (GTK_FILE_SELECTION (filew)->cancel_button, "clicked", G_CALLBACK (gtk_widget_destroy), G_OBJECT (filew));

        gtk_widget_show (filew);

        return 0;
}

void Port_create(GtkWidget* w, GtkSpinButton* s)
{
        port = gtk_spin_button_get_value_as_int(s);
}
