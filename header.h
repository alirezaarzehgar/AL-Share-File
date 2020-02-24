#include <gtk/gtk.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>


#ifndef HEADER_H_
#define HEADER_H_

GtkWidget* window;

void Winhide(gpointer win);
void MainHide();


int Reserver();
int Sender();

int port;
int new_s;

int Send(GtkWidget* w, GtkFileSelection *fs);
int Send_filew();
void Port_create(GtkWidget* w, GtkSpinButton* s);

GtkWidget* lab;

char ip[10];
char fname[1000];

int Reserv();

void Ip_create(GtkWidget* w, GtkEntry* e);
void name_create(GtkWidget* w, GtkEntry* e);

#endif /* header.h */
