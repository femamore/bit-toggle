#include <gtk/gtk.h>

static void 
activate (GtkApplication *app, 
		  gpointer		  user_data) 
{
    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *toggle1, *toggle2, *toggle3, *toggle4, *toggle5, *toggle6, *toggle7, *toggle8;

	GtkWidget *toggles[8] = {toggle1, toggle2, toggle3, toggle4, toggle5, toggle6, toggle7, toggle8};

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Bit Toggle");
    gtk_window_set_default_size (GTK_WINDOW (window), 400, 400);

    box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 12);
	gtk_widget_set_halign (box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign (box, GTK_ALIGN_CENTER);

    toggle1 = gtk_toggle_button_new ();

    gtk_box_append (GTK_BOX (box), toggle1);

    toggle2 = gtk_toggle_button_new ();

    gtk_box_append (GTK_BOX (box), toggle2);

    toggle3 = gtk_toggle_button_new ();

    gtk_box_append (GTK_BOX (box), toggle3);

    toggle4 = gtk_toggle_button_new ();

    gtk_box_append (GTK_BOX (box), toggle4);

    toggle5 = gtk_toggle_button_new ();

    gtk_box_append (GTK_BOX (box), toggle5);

    toggle6 = gtk_toggle_button_new ();

    gtk_box_append (GTK_BOX (box), toggle6);

    toggle7 = gtk_toggle_button_new ();

    gtk_box_append (GTK_BOX (box), toggle7);

    toggle8 = gtk_toggle_button_new ();

    gtk_box_append (GTK_BOX (box), toggle8);

	gtk_window_set_child (GTK_WINDOW (window), box);
    gtk_window_present (GTK_WINDOW (window));
}

int 
main (int	argc, 
	  char **argv) 
{
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.femamore.BitToggle", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}
