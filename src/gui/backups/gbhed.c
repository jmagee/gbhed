/* gbhed.c
 *  -al bhed cipher program
 *  -gtk frotend to abtranslate
 *
 * copyright (c) 2004 Josh Magee <liquidchile@liquichile.net> 
 *
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */


#include <config.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <gdk/gdkkeysyms.h>

#define GBHED_VERSION "gBhed 0.15"

static gboolean destroy();
static GtkWidget *xpm_label_box(gchar*, gchar*);
void print_gstring(GtkWidget*, gpointer*); 
char* get_gstring(gpointer);
void translate(GtkWidget*, GtkTextBuffer*[]);
void toggle_state(GtkWidget*, int); 
int mode;	/*yes, a global variable, MWAHAHAHAHA!*/
int make_menus(GtkWidget*, GtkWidget*); 
void about_message(GtkWidget*);
void help_message(GtkWidget*);
void buffer_message(GtkWidget*);
static gboolean entry_key_press(GtkWidget*,GdkEventKey*,gpointer);

int main(int argc, char *argv[]) {
	GtkWidget *window;
	GdkPixbuf *icon;	
	GtkWidget *fixed;
	GtkWidget *button_box;
	GtkWidget *button;
	GSList *radio_box;
	GtkWidget *frame;
	GtkWidget *frame2;
	GtkWidget *view;
	GtkTextBuffer *buffer;
	GtkTextBuffer *buffer2;
	GtkWidget *background;
	GtkWidget *HBlockX;

	gtk_init(&argc, &argv);

	/*Set up the window*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "gBhed");
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	g_signal_connect(GTK_OBJECT(window), "destroy", G_CALLBACK(destroy), NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 0);

	/*window icon*/
	icon = gdk_pixbuf_new_from_file(PIXMAPS_DIR "/rikku_icon2.xpm", NULL);
	gtk_window_set_icon(GTK_WINDOW(window), icon);	

	/*vertical box for menu*/
	HBlockX = gtk_vbox_new(FALSE, 1);
	gtk_container_set_border_width(GTK_CONTAINER(HBlockX), 0);
	make_menus(window, HBlockX);
	gtk_container_add(GTK_CONTAINER(window), HBlockX);

	/*Fixed container*/
	fixed = gtk_fixed_new();
	gtk_box_pack_end(GTK_BOX(HBlockX), fixed, FALSE, TRUE, 0);

	/* create viewport frame */	
	frame = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(frame),
					GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_widget_set_size_request(frame, 350, 100);

	/*pack the background into fixed container*/
	background  = gtk_image_new_from_file(PIXMAPS_DIR "/rikkubackground.jpg");
	gtk_fixed_put(GTK_FIXED(fixed), background, 0, 0);
	gtk_widget_show(background);

	/*create the view box, place it inside the viewport*/
	view = gtk_text_view_new();
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
	gtk_text_buffer_set_text(buffer, "Enter Text", -1);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(view), GTK_WRAP_WORD);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(frame), view);
	gtk_fixed_put(GTK_FIXED(fixed), frame, 20, 40);
	gtk_widget_show(view);
	
	GtkWidget *view_event; /*saving our view on the fly so we don't overwrie it next
				 because we are going to use it later*/
	view_event = view;

	/*new viewport and view box*/
	frame2 = gtk_scrolled_window_new(NULL,  NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(frame2),
					GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC); 
	gtk_widget_set_size_request(frame2, 350, 100);
	view = gtk_text_view_new();
	buffer2 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(view));
	gtk_text_view_set_editable(GTK_TEXT_VIEW(view), FALSE);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(view), GTK_WRAP_WORD);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(frame2), view);
	gtk_fixed_put(GTK_FIXED(fixed), frame2, 20, 280);
	gtk_widget_show(view);

	/* Radio Buttons */
	button = gtk_radio_button_new_with_label(NULL, "English->Al Bhed");
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), TRUE);
	mode = 1;	/*preset this option*/
	g_signal_connect(G_OBJECT(button), "toggled", G_CALLBACK(toggle_state), (gpointer)1);
	radio_box = gtk_radio_button_get_group(GTK_RADIO_BUTTON(button));
	gtk_fixed_put(GTK_FIXED(fixed), button, 30, 150);
	gtk_widget_show(button);

	button = gtk_radio_button_new_with_label(radio_box, "Al Bhed->English");
	g_signal_connect(G_OBJECT(button), "toggled", G_CALLBACK(toggle_state), (gpointer)2);
	gtk_fixed_put(GTK_FIXED(fixed), button, 190, 150);
	gtk_widget_show(button);

	button = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(button), "Al Bhed->Phonetics");
	g_signal_connect(G_OBJECT(button), "toggled", G_CALLBACK(toggle_state), (gpointer)3);
	gtk_fixed_put(GTK_FIXED(fixed), button, 120, 185);
	gtk_widget_show(button);

	/*the glorious translate button*/
	button_box = xpm_label_box(PIXMAPS_DIR "/rikku_icon.xpm", "Dnyhcmyda!");
	gtk_widget_show(button_box);
	button = gtk_button_new();
	/*connect signal here to something*/
	g_signal_connect(GTK_OBJECT(button), "clicked", G_CALLBACK(print_gstring), buffer);
	GtkTextBuffer *data[] = {buffer, buffer2};
	g_signal_connect(GTK_OBJECT(button), "clicked", G_CALLBACK(translate), data);
	gtk_container_add(GTK_CONTAINER(button), button_box);
	gtk_fixed_put(GTK_FIXED(fixed), button, 120, 220);
	gtk_widget_show(button);
	/*bind enter key to translate button*/
	g_signal_connect(G_OBJECT(view_event), "key_press_event", G_CALLBACK(entry_key_press), data);

	/*show it all on the screen*/
	gtk_widget_show(frame);
	gtk_widget_show(frame2);
	gtk_widget_show(fixed);
	gtk_widget_show(HBlockX);
	gtk_widget_show(window);

	gtk_main();

	return 0;
}

static gboolean destroy(GtkWidget *widget, GdkEvent *event, gpointer data) {
	/*destroys the window on application quit*/
	g_print("Quiting...\n");
	gtk_main_quit();
	return FALSE;
}

static GtkWidget *xpm_label_box(gchar *xpm_filename, gchar *label_text) {
	/*packs the translate button with an icon and text*/
	GtkWidget *box;
	GtkWidget *label;
	GtkWidget *image;

	box = gtk_hbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(box), 2);

	image = gtk_image_new_from_file(xpm_filename);
	label = gtk_label_new(label_text);

	gtk_box_pack_start(GTK_BOX(box), image, FALSE, FALSE, 3);
	gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 3);

	gtk_widget_show(image);
	gtk_widget_show(label);

	return box;
}

void print_gstring(GtkWidget *widget, gpointer *buffer) {
	/*print the buffer*/
	char *mybuffer;

	GtkTextIter begin, end;
	gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer), &begin, &end);
	mybuffer = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer), &begin, &end, TRUE);
	g_print(mybuffer);
	g_print("\n");
}

char* get_gstring(gpointer buffer) {
	/*Returns the contents of the buffer*/
	char *mybuffer;

	GtkTextIter begin, end;
	gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(buffer), &begin, &end);
	mybuffer = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(buffer), &begin, &end, TRUE);

	return mybuffer;
}

void translate(GtkWidget *widget, GtkTextBuffer *buffer[]) {
	/*Processes the string translation process*/
	char text[1000];
	GString *text2;
	FILE *fp;
	char buf[1000];

	text2 = (GString*)get_gstring(buffer[0]);

	if(gtk_text_buffer_get_char_count(*buffer) > 600) {
		g_print("Buffer is too big!\n");
		buffer_message(NULL);
		return;
	}
	
	/*format our command line*/
	if(mode == 1) {	/*mode 1 is english to albhed*/
		g_print("%s%s %s", "abtranslate -e \"", (gchar*)text2, "\"");
		sprintf(text, "%s%s %s", "abtranslate -e ", (gchar*)text2, " ");
		
	}else if (mode == 2) { /*mode 2 is al bhed to english*/
		g_print("%s%s %s", "abtranslate -a \"", (gchar*)text2, "\"");
		sprintf(text, "%s%s %s", "abtranslate -a ", (gchar*)text2, " ");
	
	}else if(mode == 3) { /*mode 3 is al bhed to phonetics*/
		g_print("%s%s %s", "abtranslate -p \"", (gchar*)text2, "\"");
		sprintf(text, "%s%s %s", "abtranslate -p ", (gchar*)text2, "");

	}else { /*not valid mode*/
		g_print("%s%s %s", "abtranslate '", (gchar*)text2, "'");
		sprintf(text, "%s%s %s", "abtranslate '", (gchar*)text2, "'");
	
	}

	/*open a pipe and run the commmand through it*/
	fp = popen(text, "r");	
	fgets(buf, 1000, fp);
	g_print(buf);
	pclose(fp);

	/*now lets write it out to the other buffer*/
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer[1]), buf, -1);

}

void toggle_state(GtkWidget *widget, int toggle) {
	/*sets the translation mode based on the toggle state*/
	if(toggle == 1) {
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
			g_print("toggling 1\n");
			mode = 1;
			g_print("%i\n", mode);
		}

	}else if(toggle == 2) {
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
			g_print("toggling 2\n");
			mode = 2;
			g_print("%i\n", mode);
		}

	}else if(toggle == 3) {
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget))) {
			g_print("toggling 3\n");
			mode = 3;
			g_print("%i\n", mode);
		}
	
	}else{
		g_print("A non existant toggle was pressed!\n");
	}
}

int make_menus(GtkWidget *window, GtkWidget *HBlockX) {
	/*creates the menubar*/
	GtkItemFactoryEntry menu_items[] = {
		{"/_File",	NULL,	NULL, 0,	"<Branch>"},
		{"/_File/_Quit","<CTRL>Q", (void*)destroy, 0,"<StockItem>", GTK_STOCK_QUIT},
		{"/_Help",	NULL,	NULL,	0,	"<LastBranch>"},
		{"/_Help/_About", NULL,	about_message,	0,	"<Item>"},
		{"/_Help/_Help", NULL,	help_message,	0,	"<StockItem>", GTK_STOCK_HELP},
	};

	gint nmenu_items = sizeof(menu_items) / sizeof(menu_items[0]);
	
	GtkWidget *menubar;
	GtkItemFactory *item_factory;
	GtkAccelGroup *accel_group;
	GtkWidget *alignment;

	accel_group = gtk_accel_group_new();
	item_factory = gtk_item_factory_new(GTK_TYPE_MENU_BAR, "<main>", accel_group);
	gtk_item_factory_create_items(item_factory, nmenu_items, menu_items, NULL);
	gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);

	alignment = gtk_alignment_new(0, 0, 1, 0);
	GtkWidget *menu_hbox;
	menu_hbox = gtk_hbox_new(FALSE, 1);
	gtk_container_set_border_width(GTK_CONTAINER(menu_hbox), 0);
	gtk_box_pack_start(GTK_BOX(HBlockX), menu_hbox, FALSE, TRUE, 0);

	menubar = gtk_item_factory_get_widget(item_factory, "<main>");
	gtk_box_pack_start(GTK_BOX(menu_hbox), menubar, TRUE, TRUE, 0);

	gtk_widget_show(menubar);
	gtk_widget_show(menu_hbox);

	return 0;
}

void about_message(GtkWidget *window) {
	/*pop up an about dialogue*/
	GtkWidget *dialog;
	GtkWidget *label;
	GtkWidget *about_text1, *about_text2, *about_text3, *about_text4, *about_text5;
	GtkWidget *about_text6, *about_text7, *about_text8, *about_text9, *about_text10;
	GtkWidget *about_text11;
	GtkWidget *VBox;
	GtkWidget *about_rikku;
	GdkPixbuf *icon;
	FILE *fp;
	char buf[100];
	char text[100];

	dialog = gtk_dialog_new_with_buttons("About gBhed", GTK_WINDOW(window),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_STOCK_OK, GTK_RESPONSE_NONE, NULL);

	
	icon = gdk_pixbuf_new_from_file(PIXMAPS_DIR "/rikku_icon2.xpm", NULL);
	gtk_window_set_icon(GTK_WINDOW(dialog), icon);	

	/*will probably replace all this shit with a textview box*/

	about_rikku  = gtk_image_new_from_file(PIXMAPS_DIR "/about_rikku.jpg");
	label = gtk_label_new("About");

	about_text1 = gtk_label_new(GBHED_VERSION);

	fp = popen("abtranslate --version", "r");	
	fgets(buf, 100, fp);
	g_print(buf);
	pclose(fp);
	
	sprintf(text, " Using: %s", buf);
	about_text2 = gtk_label_new(text);

	about_text3 = gtk_label_new(NULL);
	about_text4 = gtk_label_new(NULL);
	about_text5 = gtk_label_new(NULL);
	about_text6 = gtk_label_new("\nCopyright (c) 2004-2005 Josh Magee");
	about_text7 = gtk_label_new("<liquidchile@liquidchile.net>");
	about_text8 = gtk_label_new(NULL);
	about_text9 = gtk_label_new(NULL);
	about_text10 = gtk_label_new(NULL);
	about_text11 = gtk_label_new(NULL);

	gtk_label_set_markup(GTK_LABEL(about_text3), "<span size='x-small'>gBhed is an Al Bhed translator based on the Al Bhed</span>");
	gtk_label_set_markup(GTK_LABEL(about_text4), "<span size='x-small'>language/cipher from the Final Fantasy X series.</span>");
	gtk_label_set_markup(GTK_LABEL(about_text5), "<span size='x-small'>It is written in GTK+ and distributed under the GPL.</span>");
	gtk_label_set_markup(GTK_LABEL(about_text8), "<span size='x-small'>\nFinaly Fantasy, Rikku, yht dra Al Bhed Myhkiyka</span>");
	gtk_label_set_markup(GTK_LABEL(about_text9), "<span size='x-small'>Lubonekrd (l) Square Enix Co., Ltd.</span>");
	gtk_label_set_markup(GTK_LABEL(about_text10), "<span size='x-small'>\nDrec bnuknys ec eh hu fyo yvvemeydat fedr un ahtuncat po</span>");
	gtk_label_set_markup(GTK_LABEL(about_text11), "<span size='x-small'>Square Enix, Final Fantasy, un yhodrehk amca.</span>");
/*
	gtk_label_set_markup(about_text8, "<span size='x-small'>\nFinal Fantasy, Rikku, and the Al Bhed Language: </span>");
	gtk_label_set_markup(about_text9, "<span size='x-small'>Copyright (c) Square Enix Co., Ltd.</span>");
	gtk_label_set_markup(about_text10, "<span size='x-small'>\nThis program is in no way affiliated with or endorsed by</span>");
	gtk_label_set_markup(about_text11, "<span size='x-small'>Square Enix, Final Fantasy, or anything else.</span>");

*/
	VBox = gtk_vbox_new(FALSE, 1);
	gtk_box_pack_start(GTK_BOX(VBox), label, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(VBox), about_rikku, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(VBox), about_text1, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(VBox), about_text2, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(VBox), about_text3, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(VBox), about_text4, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(VBox), about_text5, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(VBox), about_text6, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(VBox), about_text7, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(VBox), about_text8, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(VBox), about_text9, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(VBox), about_text10, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(VBox), about_text11, TRUE, TRUE, 0);


	g_signal_connect_swapped(GTK_OBJECT(dialog), "response", G_CALLBACK(gtk_widget_destroy),
					GTK_OBJECT(dialog));
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), VBox);
	gtk_widget_show_all(dialog);
}

void help_message(GtkWidget *window) {
	/*displays help...this should be expanded to be a better help dialogue
	 * but it'll do  for now ;-)*/
	GtkWidget *dialog;
	GtkWidget *help_text;
	GdkPixbuf *icon;

	dialog = gtk_dialog_new_with_buttons("Help", GTK_WINDOW(window),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_STOCK_OK, GTK_RESPONSE_NONE, NULL);

	icon = gdk_pixbuf_new_from_file(PIXMAPS_DIR "/rikku_icon.xpm", NULL);
	gtk_window_set_icon(GTK_WINDOW(dialog), icon);	

	help_text = gtk_label_new(" Al Bhed is technically a cipher, but throughout final\n Fantasy it is referred to as a laguange.  Generally\n proper nouns are not translated.  Any text you do not\n want translated should be put into square [brackets].\n\n Any special characters, (such as quotes) should\n be preceeded by the escape character \\ .\n");
	g_signal_connect_swapped(GTK_OBJECT(dialog), "response", G_CALLBACK(gtk_widget_destroy),						GTK_OBJECT(dialog));
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), help_text);
	gtk_widget_show_all(dialog);
}

void buffer_message(GtkWidget *window) {
	/*Error message to warn that warn user they have entered too much text
	 * into the buffer*/

	GtkWidget *dialog;
	GtkWidget *warn_text;
	GdkPixbuf *icon;

	dialog = gtk_dialog_new_with_buttons("Error", GTK_WINDOW(window),
						GTK_DIALOG_DESTROY_WITH_PARENT,
						GTK_STOCK_OK, GTK_RESPONSE_NONE, NULL);

	icon = gdk_pixbuf_new_from_file(PIXMAPS_DIR "/rikku_icon.xpm", NULL);
	gtk_window_set_icon(GTK_WINDOW(dialog), icon);	

	warn_text = gtk_label_new("You have entered to much text.  Try again. ");
	g_signal_connect_swapped(GTK_OBJECT(dialog), "response", G_CALLBACK(gtk_widget_destroy),						GTK_OBJECT(dialog));
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), warn_text);
	gtk_widget_show_all(dialog);
}


static gboolean entry_key_press(GtkWidget *entry, GdkEventKey *event, gpointer data) {
	/*if someone presses enter, it is the same as clicking translate*/

	switch(event->keyval)  {
		case GDK_Return:
		case GDK_KP_Enter:
			if(!(event->state & (GDK_SHIFT_MASK | GDK_CONTROL_MASK))) {
				translate(entry, data);
				return TRUE;
				break;
			}
	}
	return FALSE;
}

