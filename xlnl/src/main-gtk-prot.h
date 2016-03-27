/* main-gtk.cpp */

#ifdef __cplusplus
extern "C" {
#endif

int	main( int argc, char **argv );
void	init_gtk_gui( int argc, char **argv );
void	init_gtk_cui( int argc, char **argv );
void	init_gtk_cui_mouse( int argc, char **argv );
void	*main_thread_cui( void *p );
void	ena_timer( void );
void	init_main_sel_conf( GraphConf *cnf );
void	init_main_win( void );
void	closeGameGui();
void	guiMapPrintStatBarHint( void );
void	printMapStatBar( const char *s, ... );
gint	handle_delete(
	GtkWidget *widget, GdkEvent *event, gpointer user_data
);
void	handle_destroy(
	GtkWidget *widget, gpointer user_data
);
gint	handle_map_expose(
	GtkWidget *widget, GdkEventExpose *event
);
gint	handle_map_configure(
	GtkWidget *widget, GdkEventConfigure *event
);
void	configure_map( void );
void	handle_map_scroll_changed(
	GtkAdjustment *adjustment,
	gpointer user_data
);
gint	handle_map_draw( gpointer p );
gint	handle_map_motion_notify(
	GtkWidget *widget, GdkEventMotion *event
);
void	handle_exec_clicked(
	GtkWidget *widget, gpointer *data
);
void	handle_cont_exec_clicked(
	GtkToggleButton *btn,
	gpointer user_data
);
void	handle_auto_mark_clicked(
	GtkWidget *widget, gpointer *data
);
void	handle_user_menu_clicked(
	GtkWidget *widget, gpointer *data
);
void	handle_spell_clicked(
	GtkWidget *widget, gpointer *data
);
void	handle_square_clicked(
	GtkWidget *widget, gpointer *data
);
void	handle_cancel_clicked(
	GtkWidget *widget, gpointer *data
);
void	handle_ok_clicked(
	GtkWidget *widget, gpointer *data
);
void	exec_cancel_clicked( void );
void	exec_ok_clicked( void );
gint	handle_map_button_press(
	GtkWidget *widget, GdkEventMotion *event
);
gint	handle_map_button_release(
	GtkWidget *widget, GdkEventMotion *event
);
gint	handle_map_scroll(
	GtkWidget *widget, GdkEventScroll *event
);

#ifdef __cplusplus
}
#endif
