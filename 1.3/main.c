#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "header.h"

static GtkWidget *lahter1, *lahter2, *lahter3, *lahter4, *lahter5, *lahter6, *lahter7, *lahter8, *lahter9, *lahter10, *lahter11, *lahter12, *lahter13, *lahter14, *lahter15, *lahter16;
static GtkWidget *markeering1, *markeering2, *markeering3, *markeering4, *markeering5, *markeering6,  *markeering7, *markeering8, *markeering9; // muutumatud kirjed
static GtkWidget *teade1, *teade2;
static PangoFontDescription *kirjastiil1;

static void nupuvajutus(GtkWidget *widget, gpointer data)
{
	int l = gtk_entry_get_text_length(GTK_ENTRY(data));
	int staatus;
	char g_sisend[l], *aadress = NULL;
	char tvpuhver1[16][16], tvpuhver2[16][16];
	char yhtedepiirkond[16], m22ramatuspiirkond[16];
	int yhtesi = 0, kriipse = 0;
	char tv1[2], tv2[2], tv3[2], tv4[2], tv5[2], tv6[2], tv7[2], tv8[2], tv9[2], tv10[2], tv11[2], tv12[2], tv13[2], tv14[2], tv15[2], tv16[2]; // Karnaugh kaardi lahtrid t6ev22rtustabelist
	aadress = g_strdup(gtk_entry_get_text(GTK_ENTRY(data)));	// kuna gtk_entry_get_text tagastab const. char viida, siis tuleb muudetava viida saamiseks s6ne kopeerida g_strdup abil
	for(int i = 0; i < l; i++)	// sisendi lugemine puhvrisse
	{
		g_sisend[i] = *aadress;
		aadress++;
	}
	staatus = GenjaMin(l, g_sisend);
	if (staatus == 1)
	{
		gtk_frame_set_label(GTK_FRAME(teade2), "MDNK ja MKNK puuduvad!");
	}
	if (staatus != 1)	// uuendada kasutajaliidese t6ev22rtustabelit ainult siis kui funktsioon GenjaMin too edukalt l6petab
	{
		gtk_frame_set_label(GTK_FRAME(teade1), "Genereeritud!");
		gtk_frame_set_label(GTK_FRAME(teade2), "Minimeeritud!");
		FILE *TVTABEL = fopen("t6ev22rtustabel.txt", "r");
		for (int i = 0; i < 16; i++)
		{
			fscanf(TVTABEL, "%s%s", tvpuhver1[i], tvpuhver2[i]);
			if (tvpuhver2[i][0] == '1')
			{
				yhtedepiirkond[yhtesi] = tvpuhver1[i][0];
				yhtesi++;
			}
			else if (tvpuhver2[i][0] == '-')
			{
				m22ramatuspiirkond[kriipse] = tvpuhver1[i][0];
				kriipse++;
			}
		}
		yhtedepiirkond[yhtesi] = '\0';
		m22ramatuspiirkond[kriipse] = '\0';
		fclose(TVTABEL);
		tv1[0] = tvpuhver2[0][0];
		tv1[1] = '\0';
		tv2[0] = tvpuhver2[1][0];
		tv2[1] = '\0';
		tv3[0] = tvpuhver2[2][0];
		tv3[1] = '\0';
		tv4[0] = tvpuhver2[3][0];
		tv4[1] = '\0';
		tv5[0] = tvpuhver2[4][0];
		tv5[1] = '\0';
		tv6[0] = tvpuhver2[5][0];
		tv6[1] = '\0';
		tv7[0] = tvpuhver2[6][0];
		tv7[1] = '\0';
		tv8[0] = tvpuhver2[7][0];
		tv8[1] = '\0';
		tv9[0] = tvpuhver2[8][0];
		tv9[1] = '\0';
		tv10[0] = tvpuhver2[9][0];
		tv10[1] = '\0';
		tv11[0] = tvpuhver2[10][0];
		tv11[1] = '\0';
		tv12[0] = tvpuhver2[11][0];
		tv12[1] = '\0';
		tv13[0] = tvpuhver2[12][0];
		tv13[1] = '\0';
		tv14[0] = tvpuhver2[13][0];
		tv14[1] = '\0';
		tv15[0] = tvpuhver2[14][0];
		tv15[1] = '\0';
		tv16[0] = tvpuhver2[15][0];
		tv16[1] = '\0';
		gtk_frame_set_label(GTK_FRAME(lahter1), tv1);
		gtk_frame_set_label(GTK_FRAME(lahter2), tv2);
		gtk_frame_set_label(GTK_FRAME(lahter3), tv3);
		gtk_frame_set_label(GTK_FRAME(lahter4), tv4);
		gtk_frame_set_label(GTK_FRAME(lahter5), tv5);
		gtk_frame_set_label(GTK_FRAME(lahter6), tv6);
		gtk_frame_set_label(GTK_FRAME(lahter7), tv7);
		gtk_frame_set_label(GTK_FRAME(lahter8), tv8);
		gtk_frame_set_label(GTK_FRAME(lahter9), tv9);
		gtk_frame_set_label(GTK_FRAME(lahter10), tv10);
		gtk_frame_set_label(GTK_FRAME(lahter11), tv11);
		gtk_frame_set_label(GTK_FRAME(lahter12), tv12);
		gtk_frame_set_label(GTK_FRAME(lahter13), tv13);
		gtk_frame_set_label(GTK_FRAME(lahter14), tv14);
		gtk_frame_set_label(GTK_FRAME(lahter15), tv15);
		gtk_frame_set_label(GTK_FRAME(lahter16), tv16);
	}
	else if (staatus == 1)	// l2htesta tabel kui sisend ei sobi (et ei tekiks segadust)
	{
		gtk_frame_set_label(GTK_FRAME(teade1), "Sobimatu sisend!");
		gtk_frame_set_label(GTK_FRAME(lahter1), "  X");
		gtk_frame_set_label(GTK_FRAME(lahter2), "  X");
		gtk_frame_set_label(GTK_FRAME(lahter3), "  X");
		gtk_frame_set_label(GTK_FRAME(lahter4), "  X");
		gtk_frame_set_label(GTK_FRAME(lahter5), "  X");
		gtk_frame_set_label(GTK_FRAME(lahter6), "  X");
		gtk_frame_set_label(GTK_FRAME(lahter7), "  X");
		gtk_frame_set_label(GTK_FRAME(lahter8), "  X");
		gtk_frame_set_label(GTK_FRAME(lahter9), "  X");
		gtk_frame_set_label(GTK_FRAME(lahter10), "  X");
		gtk_frame_set_label(GTK_FRAME(lahter11), "  X");
		gtk_frame_set_label(GTK_FRAME(lahter12), "  X");
		gtk_frame_set_label(GTK_FRAME(lahter13), "  X");
		gtk_frame_set_label(GTK_FRAME(lahter14), "  X");
		gtk_frame_set_label(GTK_FRAME(lahter15), "  X");
		gtk_frame_set_label(GTK_FRAME(lahter16), "  X");
	}
}

static gboolean klahvivajutus(GtkWidget *widget, GdkEventKey *event, gpointer data)	// ESC klahvi vajutusel v2ljumine
{
	if (event->keyval == GDK_KEY_Escape)
	{
		gtk_main_quit();
		return TRUE;
	}
	return FALSE;
}

int main(int argc, char * argv[])
{
	system("GDK_BACKEND=broadway");
	//system("broadwayd :6");
	kirjastiil1 = pango_font_description_from_string("Times New Roman 22");
	gtk_init(&argc, &argv);	// GTK k2ivitamine
	GtkWidget *aken = gtk_window_new(GTK_WINDOW_TOPLEVEL); // uue akna loomine (vastava viida algv22rtustamine)
	GtkWidget *lahter = gtk_entry_new(); // uue lahtri loomine (vastava viida algv22rtustamine)
	GtkWidget *konteiner = gtk_grid_new();
	GtkWidget *nupp = gtk_button_new_with_label("Genereeri");
	GtkWidget *kirje = gtk_label_new("Matriklinumber: ");
	GtkWidget *staatus2 = gtk_label_new("\t    Staatus: ");
	GtkWidget *kirje1 = gtk_label_new("Karnaugh' kaart:  \tx\342\202\203x\342\202\204 ");
	GdkPixbuf *ikoon = gdk_pixbuf_new_from_file("ikoon.ico", NULL);
	GtkWidget *laotis = gtk_layout_new(NULL, NULL);
	gtk_window_set_position(GTK_WINDOW(aken), GTK_WIN_POS_CENTER); // akna paigutamine ekraani keskele
	gtk_window_set_title(GTK_WINDOW(aken), "Loogikafunktsiooni genereerija-minimeerija");	// akna pealkirja m22ramine
	gtk_window_set_icon(GTK_WINDOW(aken), ikoon);
	g_signal_connect(aken, "destroy", G_CALLBACK(gtk_main_quit), NULL);	// akna sulgemisel programmi katkestamine
	g_signal_connect(aken, "key_press_event", G_CALLBACK(klahvivajutus), NULL);	// akna sulgemiseks ESC klahvi vajutusel
	gtk_container_add(GTK_CONTAINER(aken), konteiner); // sisendi lahtri lisamine vastavasse konteinerisse
	gtk_window_set_resizable(GTK_WINDOW(aken), FALSE);
	g_signal_connect(nupp, "clicked", G_CALLBACK(nupuvajutus), lahter);	// genereerimise nupu vajutuse signaali sidumine funktsiooniga
	g_signal_connect(lahter, "activate", G_CALLBACK(nupuvajutus), lahter); 	// return klahvi vajutuse signaali sidumine funktsiooniga
	lahter1 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(lahter1), "  X");
	lahter2 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(lahter2), "  X");
	lahter3 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(lahter3), "  X");
	lahter4 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(lahter4), "  X");
	lahter5 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(lahter5), "  X");
	lahter6 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(lahter6), "  X");
	lahter7 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(lahter7), "  X");
	lahter8 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(lahter8), "  X");
	lahter9 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(lahter9), "  X");
	lahter10 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(lahter10), "  X");
	lahter11 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(lahter11), "  X");
	lahter12 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(lahter12), "  X");
	lahter13 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(lahter13), "  X");
	lahter14 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(lahter14), "  X");
	lahter15 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(lahter15), "  X");
	lahter16 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(lahter16), "  X");
	teade1 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(teade1), "Ootel...");
	teade2 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(teade2), "Ootel...");
	markeering1 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(markeering1), "\t\t\t\tx\342\202\201x\342\202\202  00");
	markeering3 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(markeering3), "  00\t");
	markeering4 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(markeering4), "  01\t");
	markeering5 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(markeering5), "  10\t");
	markeering6 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(markeering6), "  11\t");
	markeering7 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(markeering7), "\t\t\t\t\t01\t");
	markeering8 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(markeering8), "\t\t\t\t\t11\t");
	markeering9 = gtk_frame_new(NULL);
	gtk_frame_set_label(GTK_FRAME(markeering9), "\t\t\t\t\t10\t");
	//gtk_frame_set_label_align(lahter1, 0.5);
	gtk_widget_set_size_request(lahter, 400, 60);	// lahtri suuruse m22ramine
	gtk_widget_set_size_request(teade1, 300, 60);
	gtk_widget_set_size_request(lahter1, 60, 60);
	gtk_widget_set_size_request(lahter5, 60, 60);
	gtk_widget_set_size_request(lahter9, 60, 60);
	gtk_widget_set_size_request(lahter13, 60, 60);
	gtk_grid_attach(GTK_GRID(konteiner), kirje, 0, 0, 2, 2);	// kirje 0 lisamine konteinerisse
	gtk_grid_attach(GTK_GRID(konteiner), staatus2, 0, 8, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), lahter, 4, 0, 2, 2);	// lahtri lisamine konteinerisse
	gtk_grid_attach(GTK_GRID(konteiner), nupp, 8, 0, 2, 2);	// nupu lisamine konteinerisse
	gtk_grid_attach(GTK_GRID(konteiner), kirje1, 12, 0, 2, 2);	// kirje 1 lisamine konteinerisse
	gtk_grid_attach(GTK_GRID(konteiner), lahter1, 16, 8, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), lahter2, 20, 8, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), lahter3, 28, 8, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), lahter4, 24, 8, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), lahter5, 16, 12, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), lahter6, 20, 12, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), lahter7, 28, 12, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), lahter8, 24, 12, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), lahter9, 16, 20, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), lahter10, 20, 20, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), lahter11, 28, 20, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), lahter12, 24, 20, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), lahter13, 16, 16, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), lahter14, 20, 16, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), lahter15, 28, 16, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), lahter16, 24, 16, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), teade1, 4, 8, 2, 2);	// teate 1 lisamine konteinerisse
	gtk_grid_attach(GTK_GRID(konteiner), teade2, 4, 16, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), markeering1, 12, 8, 2, 2);	// markeeringu 1 lisamine konteinerisse
	gtk_grid_attach(GTK_GRID(konteiner), markeering3, 16, 0, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), markeering4, 20, 0, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), markeering6, 24, 0, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), markeering5, 28, 0, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), markeering7, 12, 12, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), markeering8, 12, 16, 2, 2);
	gtk_grid_attach(GTK_GRID(konteiner), markeering9, 12, 20, 2, 2);
	gtk_widget_override_font(lahter, kirjastiil1);
	gtk_widget_override_font(kirje, kirjastiil1);
	gtk_widget_override_font(nupp, kirjastiil1);
	gtk_widget_override_font(kirje1, kirjastiil1);
	gtk_widget_override_font(markeering1, kirjastiil1);
	gtk_widget_override_font(nupp, kirjastiil1);
	gtk_widget_override_font(markeering3, kirjastiil1);
	gtk_widget_override_font(markeering4, kirjastiil1);
	gtk_widget_override_font(markeering5, kirjastiil1);
	gtk_widget_override_font(markeering6, kirjastiil1);
	gtk_widget_override_font(markeering7, kirjastiil1);
	gtk_widget_override_font(markeering8, kirjastiil1);
	gtk_widget_override_font(markeering9, kirjastiil1);
	gtk_widget_override_font(teade1, kirjastiil1);
	gtk_widget_override_font(teade2, kirjastiil1);
	gtk_widget_override_font(lahter1, kirjastiil1);
	gtk_widget_override_font(lahter2, kirjastiil1);
	gtk_widget_override_font(lahter3, kirjastiil1);
	gtk_widget_override_font(lahter4, kirjastiil1);
	gtk_widget_override_font(lahter5, kirjastiil1);
	gtk_widget_override_font(lahter6, kirjastiil1);
	gtk_widget_override_font(lahter7, kirjastiil1);
	gtk_widget_override_font(lahter8, kirjastiil1);
	gtk_widget_override_font(lahter9, kirjastiil1);
	gtk_widget_override_font(lahter10, kirjastiil1);
	gtk_widget_override_font(lahter11, kirjastiil1);
	gtk_widget_override_font(lahter12, kirjastiil1);
	gtk_widget_override_font(lahter13, kirjastiil1);
	gtk_widget_override_font(lahter14, kirjastiil1);
	gtk_widget_override_font(lahter15, kirjastiil1);
	gtk_widget_override_font(lahter16, kirjastiil1);
	gtk_widget_override_font(staatus2, kirjastiil1);
	gtk_widget_show_all(aken);	// akna n2htavaks tegemine
	gtk_main();
	return 0;
}
