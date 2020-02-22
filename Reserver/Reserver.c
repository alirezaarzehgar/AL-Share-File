#include <gtk/gtk.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

GtkWidget* lab;

int NUMBER = 0;
int port;
char ip[10];
char fname[1000];

int Reserv();

int main(int argc, char** argv)
{
	sprintf(ip, argv[2]);
	port = atoi(argv[1]);
        sprintf(fname, argv[3]);


	gtk_init(&argc, &argv);
	GtkWidget* win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	lab 	       = gtk_label_new("server not found");
	GtkWidget* fix = gtk_fixed_new();
	GtkWidget* res = gtk_button_new_with_label("reserve file");

	// desine
	gtk_widget_set_usize(GTK_WIDGET(win), 200, 200);
	gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(win), argv[1]);
        gtk_widget_set_usize(GTK_WIDGET(res), 100, 30);
        gtk_widget_set_usize(GTK_WIDGET(lab), 120, 30);

	//color
	GdkColor back;
	GdkColor btn;

	gdk_color_parse("#1a1a1a", &back);
        gdk_color_parse("#0a0a0a", &btn);

	gtk_widget_modify_bg(GTK_WIDGET(win), GTK_STATE_NORMAL, &back);
        gtk_widget_modify_bg(GTK_WIDGET(res), GTK_STATE_NORMAL,  &btn);

	// fixed puts
	gtk_fixed_put(GTK_FIXED(fix), lab, 40, 50);
        gtk_fixed_put(GTK_FIXED(fix), res, 50, 100);

	// signals
	g_signal_connect(win,   "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect(res,   "clicked"     , G_CALLBACK(Reserv), NULL);

	// show
	gtk_container_add(GTK_CONTAINER(win), fix);
	gtk_widget_show_all(win);
	gtk_main();
	return 0;
}

int Reserv()
{
        int sockfd;
        struct sockaddr_in serv_addr;

        if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
        {
                printf("\n Error : Could not create socket \n");
                return 1;
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);
        serv_addr.sin_addr.s_addr = inet_addr(ip);

        if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
        {
                printf("\n Error : Connect Failed \n");
                return 1;
        }

        char buffer[1024];
	char file_name[1024];

	send(sockfd, "hello", 5, 0);
        read(sockfd, buffer, 1024);

	FILE* f = fopen(fname, "w");

	fprintf(f, buffer, 1024);

	fclose(f);

	close(sockfd);

        char Mess[1024];
        sprintf(Mess, "%s reserving from %d ip",fname, ip);

        // message
        GtkWidget* box = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CANCEL, "Message");
        gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(box), Mess);
        int response = gtk_dialog_run(GTK_DIALOG(box));

        return 0;
}

