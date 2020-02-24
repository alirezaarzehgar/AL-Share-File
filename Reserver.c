#include "header.h"

int Reserver()
{

	GtkWidget* win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	lab 	       = gtk_label_new("server not found");
	GtkWidget* fix = gtk_fixed_new();
	GtkWidget* res = gtk_button_new_with_label("reserve file");
        GtkWidget* spi = gtk_spin_button_new(((GtkAdjustment*) gtk_adjustment_new (8080, 0, 99999, 1, 0, 0)) , 0, 0);
	GtkWidget* ent = gtk_entry_new();
        GtkWidget* Ent = gtk_entry_new();

	GtkWidget* l[3];
	l[0] = gtk_label_new("port");
        l[1] = gtk_label_new("IP");
        l[2] = gtk_label_new("name");

	// desine
	gtk_widget_set_usize(GTK_WIDGET(win), 220, 240);
	gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(win), "Sendr");
        gtk_widget_set_usize(GTK_WIDGET(res), 110, 30);
        gtk_widget_set_usize(GTK_WIDGET(lab), 200, 30);
        gtk_widget_set_usize(GTK_WIDGET(spi), 130, 30);
        gtk_widget_set_usize(GTK_WIDGET(ent), 130, 30);
        gtk_widget_set_usize(GTK_WIDGET(Ent), 130, 30);
        gtk_window_set_resizable(GTK_WINDOW(win), FALSE);

	gtk_entry_set_text(GTK_ENTRY(ent), "192.168.1.10");
	gtk_entry_set_text(GTK_ENTRY(Ent), "File.txt");

	//color
	GdkColor back;
	GdkColor btn;

	gdk_color_parse("#1a1a1a", &back);
        gdk_color_parse("#0a0a0a", &btn);

	gtk_widget_modify_bg(GTK_WIDGET(win), GTK_STATE_NORMAL, &back);
        gtk_widget_modify_bg(GTK_WIDGET(res), GTK_STATE_NORMAL,  &btn);

	// fixed puts
	gtk_fixed_put(GTK_FIXED(fix), lab, 10, 0);
        gtk_fixed_put(GTK_FIXED(fix), res, 60, 60);
        gtk_fixed_put(GTK_FIXED(fix), l[0], 9, 100);
        gtk_fixed_put(GTK_FIXED(fix), spi, 50, 100);
        gtk_fixed_put(GTK_FIXED(fix), l[1], 9, 140);
        gtk_fixed_put(GTK_FIXED(fix), ent, 50, 140);
        gtk_fixed_put(GTK_FIXED(fix), l[2], 9, 180);
        gtk_fixed_put(GTK_FIXED(fix), Ent, 50, 180);


	// signals
        g_signal_connect(win, "delete-event", G_CALLBACK(Winhide), NULL);
        g_signal_connect(res,   "clicked"     , G_CALLBACK(Ip_create), (GtkEntry*)ent);
        g_signal_connect(res,   "clicked"     , G_CALLBACK(Port_create), (GtkSpinButton*)spi);
        g_signal_connect(res,   "clicked"     , G_CALLBACK(name_create), (GtkEntry*)Ent);
	g_signal_connect(res,   "clicked"     , G_CALLBACK(Reserv), NULL);
	// show
	gtk_container_add(GTK_CONTAINER(win), fix);
	gtk_widget_show_all(win);
	return 0;
}

int Reserv()
{
        int sockfd;
        struct sockaddr_in serv_addr;

        if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
        {
                gtk_label_set_text(GTK_LABEL(lab), "Error : Could not create socket");
                return 1;
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);
        serv_addr.sin_addr.s_addr = inet_addr(ip);
	g_print(ip);

        if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
        {
                gtk_label_set_text(GTK_LABEL(lab), "Error : Connect Failed");
                return 1;
        }

        char* buffer = (char*) malloc (sizeof(char*)*100000000);
	char file_name[1024];

	send(sockfd, "hello", 5, 0);
        read(sockfd, buffer, 100000);

	FILE* f = fopen(fname, "w");

	fprintf(f, "%s", buffer);

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

void Port_create(GtkWidget* w, GtkSpinButton* s)
{
        port = gtk_spin_button_get_value_as_int(s);
}

void Ip_create(GtkWidget* w, GtkEntry* e)
{
	char tmp[30];
	sprintf(tmp, "%s", gtk_entry_get_text(GTK_ENTRY(e)));

	for(int i = 0; i < strlen(tmp); i++)
	{
		ip[i] = tmp[i];
	}
}

void name_create(GtkWidget* w, GtkEntry* e)
{
        sprintf(fname, "%s", gtk_entry_get_text(GTK_ENTRY(e)));
}

void MainHide()
{
	gtk_widget_hide(GTK_WIDGET(window));
}
