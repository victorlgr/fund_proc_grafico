/*
 * Seminário 2 - Grupo MMA
 * Cauê Montrose Bianchim, RA 11109715
 * Ismael Trinca Junior, RA 11131611
 * Rafael Branco Totino, RA 11201922308
 * Victor Luiz Gluz Romano, RA 11109915
 * Compilar o programa com "gcc -Wno-format -o gui gui.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic" e executar com ./gui
 *
 */

#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <string.h>


char header[] = "massa;mola;amortecedor;F;x0;v0;bool_iluminacao;red_iluminacao;green_iluminacao;blue_iluminacao;alpha_iluminacao;bool_textura\n";
char array_dados[10000] = "";
double massa = 0, mola = 0, amortecedor = 0, F = 0, x0 = 0, v0 = 0;
int bool_iluminacao = 0, bool_textura = 0;

GdkRGBA color;

GtkWidget *window;
GtkWidget *fixed;
GtkWidget *label_massa;
GtkWidget *input_massa;
GtkWidget *label_mola;
GtkWidget *input_mola;
GtkWidget *label_amortecedor;
GtkWidget *input_amortecedor;
GtkWidget *label_F;
GtkWidget *input_F;
GtkWidget *label_x0;
GtkWidget *input_x0;
GtkWidget *label_v0;
GtkWidget *input_v0;
GtkWidget *botao_iluminacao;
GtkWidget *cor_iluminacao;
GtkWidget *botao_textura;
GtkWidget *botao_executar;
GtkBuilder *builder;

void gerar_csv();

int main(int argc, char *argv[])
{

    gtk_init(&argc, &argv); // init Gtk

    builder = gtk_builder_new_from_file("gui.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, NULL);

    fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));

    label_massa = GTK_WIDGET(gtk_builder_get_object(builder, "label_massa"));
    input_massa = GTK_WIDGET(gtk_builder_get_object(builder, "input_massa"));

    label_mola = GTK_WIDGET(gtk_builder_get_object(builder, "label_mola"));
    input_mola = GTK_WIDGET(gtk_builder_get_object(builder, "input_mola"));

    label_amortecedor = GTK_WIDGET(gtk_builder_get_object(builder, "label_amortecedor"));
    input_amortecedor = GTK_WIDGET(gtk_builder_get_object(builder, "input_amortecedor"));

    label_F = GTK_WIDGET(gtk_builder_get_object(builder, "label_F"));
    input_F = GTK_WIDGET(gtk_builder_get_object(builder, "input_F"));

    label_x0 = GTK_WIDGET(gtk_builder_get_object(builder, "label_x0"));
    input_x0 = GTK_WIDGET(gtk_builder_get_object(builder, "input_x0"));

    label_v0 = GTK_WIDGET(gtk_builder_get_object(builder, "label_v0"));
    input_v0 = GTK_WIDGET(gtk_builder_get_object(builder, "input_v0"));

    botao_iluminacao = GTK_WIDGET(gtk_builder_get_object(builder, "botao_iluminacao"));
    cor_iluminacao = GTK_WIDGET(gtk_builder_get_object(builder, "cor_iluminacao"));

    botao_textura = GTK_WIDGET(gtk_builder_get_object(builder, "botao_textura"));

    botao_executar = GTK_WIDGET(gtk_builder_get_object(builder, "botao_executar"));

    gtk_widget_show(window);

    gtk_main();

    return EXIT_SUCCESS;
}

void on_input_massa_changed(GtkEntry *massa_ponteiro)
{
    char tmp[128];
    sprintf(tmp, "%s", gtk_entry_get_text(massa_ponteiro));
    massa = atof(tmp);
}

void on_input_mola_changed(GtkEntry *mola_ponteiro)
{
    char tmp[128];
    sprintf(tmp, "%s", gtk_entry_get_text(mola_ponteiro));
    mola = atof(tmp);
}

void on_input_amortecedor_changed(GtkEntry *amortecedor_ponteiro)
{
    char tmp[128];
    sprintf(tmp, "%s", gtk_entry_get_text(amortecedor_ponteiro));
    amortecedor = atof(tmp);
}

void on_input_x0_changed(GtkEntry *x0_ponteiro)
{
    char tmp[128];
    sprintf(tmp, "%s", gtk_entry_get_text(x0_ponteiro));
    x0 = atof(tmp);
}

void on_input_forca_changed(GtkEntry *F_ponteiro)
{
    char tmp[128];
    sprintf(tmp, "%s", gtk_entry_get_text(F_ponteiro));
    F = atof(tmp);
}

void on_input_v0_changed(GtkEntry *v0_ponteiro)
{
    char tmp[128];
    sprintf(tmp, "%s", gtk_entry_get_text(v0_ponteiro));
    v0 = atof(tmp);
}

void on_botao_executar_clicked(GtkButton *b)
{
    gerar_csv();
}

void on_botao_iluminacao_activate(GtkSwitch *iluminacao_ponteiro)
{
    bool_iluminacao = gtk_switch_get_active(iluminacao_ponteiro);
}

void on_cor_iluminacao_color_set(GtkColorButton *c)
{
    gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(c), &color);
}

void on_botao_textura_activate(GtkSwitch *textura_ponteiro)
{
    bool_textura = gtk_switch_get_active(textura_ponteiro);
}

void comma_to_dot(char *input) {
    char *ptr = NULL;
    while(ptr = strpbrk(input, ",")) {
        *ptr = '.';
    }
}

void gerar_csv()
{
    array_dados[0] = '\0';

    char massa_str[30];
    char mola_str[30];
    char amortecedor_str[30];
    char F_str[30];
    char x0_str[30];
    char v0_str[30];
    char bool_iluminacao_str[30];
    char bool_textura_str[30];
    char red_str[30];
    char green_str[30];
    char blue_str[30];
    char alpha_str[30];

    sprintf(massa_str, "%f;", massa);
    sprintf(mola_str, "%f;", mola);
    sprintf(amortecedor_str, "%f;", amortecedor);
    sprintf(F_str, "%f;", F);
    sprintf(x0_str, "%f;", x0);
    sprintf(v0_str, "%f;", v0);
    sprintf(bool_iluminacao_str, "%d;", bool_iluminacao);
    sprintf(red_str, "%f;", color.red);
    sprintf(green_str, "%f;", color.green);
    sprintf(blue_str, "%f;", color.blue);
    sprintf(alpha_str, "%f;", color.alpha);
    sprintf(bool_textura_str, "%d", bool_textura);

    strcat(array_dados, header);
    strcat(array_dados, massa_str);
    strcat(array_dados, mola_str);
    strcat(array_dados, amortecedor_str);
    strcat(array_dados, F_str);
    strcat(array_dados, x0_str);
    strcat(array_dados, v0_str);
    strcat(array_dados, bool_iluminacao_str);
    strcat(array_dados, red_str);
    strcat(array_dados, green_str);
    strcat(array_dados, blue_str);
    strcat(array_dados, alpha_str);
    strcat(array_dados, bool_textura_str);
    strcat(array_dados, "\0");

    comma_to_dot(array_dados);

    FILE *fp;
    fp = fopen("dados.csv", "w");
    fputs(array_dados, fp);
    fclose(fp);
}