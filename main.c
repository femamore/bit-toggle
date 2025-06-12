#include <gtk/gtk.h>

typedef struct {
    GtkToggleButton *toggles[8];
    GtkLabel *label;
} BitToggleData;

static void
free_bit_toggle_data (GtkWidget *widget, 
                      gpointer user_data)
{
    g_free(user_data);
}

void
int_to_binary (int value, char *buf)
{
    for (int i = 7; i >= 0; i--) 
        buf[7 - i] = (value & (1 << i)) ? '1' : '0';

    buf[8] = '\0';
}

static void
reset_toggles (GtkToggleButton *button,
               gpointer        user_data)
{
    BitToggleData *data = user_data;

    for (int i = 0; i < 8; i++)
        gtk_toggle_button_set_active (data->toggles[i], FALSE);

    gtk_label_set_text (data->label, "Decimal: 0    Hex: 0x00    Bin: 0b00000000");
}

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
    char bin[9];
    int_to_binary (value, bin);
    snprintf (buf, sizeof (buf), "Decimal: %d    Hex: 0x%02X    Bin: 0b%s", value, value, bin);
    gtk_label_set_text (GTK_LABEL (data->label), buf);
}

static void 
activate (GtkApplication *app, 
		  gpointer		  user_data) 
{
    GtkWidget *window;
    GtkWidget *vbox, *hbox;
    GtkWidget *label;
    GtkWidget *reset_button;

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Bit Toggle");
    gtk_window_set_default_size (GTK_WINDOW (window), 400, 400);

    vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 12);
	gtk_widget_set_halign (vbox, GTK_ALIGN_CENTER);
	gtk_widget_set_valign (vbox, GTK_ALIGN_CENTER);

    hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 6);

    label = gtk_label_new ("Decimal: 0       Hex: 0x00    Bin: 0b00000000");

    BitToggleData *data = g_malloc (sizeof (BitToggleData));
    data -> label = GTK_LABEL (label);

    for (int i = 0; i < 8; i++) {
        GtkWidget *toggle = gtk_toggle_button_new ();
        data->toggles[i] = GTK_TOGGLE_BUTTON (toggle);
        gtk_box_append (GTK_BOX (hbox), toggle);
        g_signal_connect (toggle, "toggled", G_CALLBACK (change_bit), data);
    }

    reset_button = gtk_button_new_with_label ("Reset");
    g_signal_connect (reset_button, "clicked", G_CALLBACK (reset_toggles), data);

    gtk_box_append (GTK_BOX (vbox), hbox);
    gtk_box_append (GTK_BOX (vbox), label);
    gtk_box_append (GTK_BOX (vbox), reset_button);
	gtk_window_set_child (GTK_WINDOW (window), vbox);

    g_object_set_data_full (G_OBJECT(window), "bit-data",
                            data, g_free);

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
