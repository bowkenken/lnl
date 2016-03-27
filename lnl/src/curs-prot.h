/* curs.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_curs( void );
void	reset_static_curs( void );
bool_t	init_curs_color( void );
bool_t	init_curs_color_pair( curs_attr_t *p, short pair_n );
bool_t	chk_curs_draw( void );
void	ena_curs_draw( void );
void	dis_curs_draw( void );
bool_t	chk_curs( void );
void	ena_curs( void );
void	dis_curs( void );
void	curs_clearok( WINDOW *win, bool_t bf );
void	curs_initscr( void );
void	curs_endwin( void );
void	curs_keypad( WINDOW *win, bool_t bf );
void	curs_refresh( void );
curs_attr_t	get_current_attr( void );
void	curs_attrset_dflt( void );
void	curs_attrset_n( curs_attr_n_t n );
void	curs_attrset_dir( curs_attr_t *attr );
void	curs_attrset( long at );
void	curs_attron( long at );
void	curs_attroff( long at );
curs_attr_t	*get_curs_attr( void );
void	curs_echo( void );
void	curs_noecho( void );
void	curs_cbreak( void );
void	curs_nocbreak( void );
void	curs_raw( void );
void	curs_noraw( void );
void	curs_move( int scrn_y, int scrn_x );
void	curs_printw( char *s, ... );
void	curs_clear( void );
int	curs_getch( void );
void	curs_getnstr( char *s, int len );
bool_t	chk_color( void );
long	get_screen_col( void );
long	get_screen_row( void );
long	get_map_col( void );
long	get_map_row( void );
long	get_message_col( void );
long	get_message_row( void );
long	get_stat_bar_col( void );
long	get_stat_bar_row( void );
bool_t	chk_flg_screen_size_auto( void );
void	set_flg_screen_size_auto( bool_t flg );
long	get_screen_size_col( void );
void	set_screen_size_col( long n );
long	get_screen_size_row( void );
void	set_screen_size_row( long n );
long	get_screen_size_message( void );
void	set_screen_size_message( long n );
bool_t	chk_flg_resize_map( void );
void	set_flg_resize_map( bool_t flg );
bool_t	cmp_attr( curs_attr_t *a, curs_attr_t *b );
int	attr_dos( curs_attr_t *attr );
void	check_memory_curs_c( void );

#ifdef __cplusplus
}
#endif
