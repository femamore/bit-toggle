#include <gtk/gtk.h>

typedef struct {
    GtkToggleButton *toggles[8];
    GtkLabel *label;
} BitToggleData;

static void
change_bit (GtkToggleButton *button, 
            gpointer        user_data)
{
    BitToggleData *data = user_data;

    int value = 0;

    for (int i = 0; i < 8; i++) {
        if (gtk_toggle_button_get_active (data->toggles[i]))
            value |= (1 << (7 - i));
    }

    char buf[64];
    snprintf (buf, sizeof (buf), "Decimal: %d    Hex: 0x%02X    Bin: 0b%08b", value, value, value);
    gtk_label_set_text (GTK_LABEL (data->label), buf);
}

static void 
activate (GtkApplication *app, 
		  gpointer		  user_data) 
{
    GtkWidget *window;
    GtkWidget *vbox, *hbox;
    GtkWidget *label;
    GtkWidget *toggle1, *toggle2, *toggle3, *toggle4, *toggle5, *toggle6, *toggle7, *toggle8;

	GtkWidget *toggles[8] = {toggle1, toggle2, toggle3, toggle4, toggle5, toggle6, toggle7, toggle8};

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Bit Toggle");
    gtk_window_set_default_size (GTK_WINDOW (window), 400, 400);

    vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 12);
	gtk_widget_set_halign (vbox, GTK_ALIGN_CENTER);
	gtk_widget_set_valign (vbox, GTK_ALIGN_CENTER);

    hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 6);

    label = gtk_label_new ("Decimal: 0       Hex: 0x00    Bin: 0b00000000");

    BitToggleData *data = g_malloc (sizeof(BitToggleData));
    data -> label = GTK_LABEL (label);

    for (int i = 0; i < 8; i++) {
        GtkWidget *toggle = gtk_toggle_button_new();
        data->toggles[i] = GTK_TOGGLE_BUTTON (toggle);
        gtk_box_append (GTK_BOX (hbox), toggle);
        g_signal_connect (toggle, "toggled", G_CALLBACK (change_bit), data);
    }

    gtk_box_append (GTK_BOX (vbox), hbox);
    gtk_box_append (GTK_BOX (vbox), label);
	gtk_window_set_child (GTK_WINDOW (window), vbox);
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
