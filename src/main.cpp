#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif


#include <stdlib.h>
#include <glib/gi18n.h>
#include <gtk/gtk.h>

static gboolean on_delete_event(GtkWidget * window, GdkEvent *event , gpointer data)
{
	gtk_main_quit();
	return FALSE;
}

static void create_window(GtkWidget *main_window;)
{
	gtk_container_set_border_width (GTK_CONTAINER (main_window), 5);
	g_signal_connect (G_OBJECT (main_window), "delete_event", G_CALLBACK (on_delete_event), NULL);

	GtkWidget *main_vbox;
	main_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
	gtk_container_add(GTK_CONTAINER(main_window), main_vbox);

	gtk_widget_show_all(main_window);
}

static void rm_file(char *filename)
{
	//fd = fopen();
	//syncfs(fd);
	//g_unlink(filename);

	std::string cmd_str;
	cmd_str = "shred -u ";
	gchar *quote = g_shell_quote(filename);
	cmd_str += quote;
	g_free(quote);
	system(cmd_str);
}

static void rm_dir(char *dirname)
{
	GDir *dir;
	dir = g_dir_open(it->c_str(), 0, NULL);
	if (!dir) {
		return;
	}
	const gchar *filename;
	while ((filename= g_dir_read_name(dir))!=NULL) {
		std::string fullfilename;
		fullfilename = dirname;
		fullfilename += G_DIR_SEPARATOR;
		fullfilename += filename;
		if (g_file_test(fullfilename.c_str(), G_FILE_TEST_IS_DIR)) {
			rm_dir(fullfilename.c_str();
		} else {
			rm_file(fullfilename.c_str());
		}
	}
	g_dir_close(dir);
	g_rmdir(dirname);
}

static void rm_file_or_dir(int file_or_dir_num, **file_or_dir_str)
{
	for (int i = 0; i <file_or_dir_num; i++) {
		if (g_file_test(file_or_dir_str[i]), G_FILE_TEST_IS_DIR) {
			rm_dir(file_or_dir_str[i]);
		} else {
			rm_file(file_or_dir_str[i])
		}
	}
}

static void are_you_sure()
{
}

static void activateMe(GtkApplication *app,gpointer user_data) {
	GtkWidget *window = gtk_application_window_new(app);
	gtk_window_set_position (GTK_WINDOW (main_window), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(window), _("rm-kill"));
	gtk_window_set_default_size(GTK_WINDOW(window),200,200);
	create_window(window);
}

int main(int argc,char **argv)
{
	bindtextdomain (GETTEXT_PACKAGE, RM_KILL_LOCALEDIR);
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);

	if (argc==1) {
		GtkApplication *app；
		int status;
		app = gtk_application_new("com.app.rm-kill",G_APPLICATION_FLAGS_NONE);
		g_signal_connect(app,"activate",G_CALLBACK(activateMe),NULL);
		status = g_application_run(G_APPLICATION(app),argc,argv);
		g_object_unref(app);
		return status;
	} else {
		real_rm = are_you_sure();
		if (real_rm) {
			rm_file_or_dir(argc-1, argv++);
		}
		return 0;
	}
}
