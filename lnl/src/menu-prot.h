/* menu.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_var_menu( void );
void	init_menu( void );
void	init_macro_func( char *macro, const char *dflt );
void	reset_static_menu( void );
void	init_ls_menu_macro_func( void );
void	init_ls_menu_macro_mouse( void );
void	init_ls_menu_macro_mouse_sub(
	menu_t *ls, long i, long *kp, char *key_p, long macro_n
);
const char	*get_msg_menu_mouse( long n );
const char	*get_msg_menu_mouse_short_key( long n );
void	init_ls_menu_macro_joystick( void );
bool_t	chk_executing_menu( void );
char	*exec_menu( menu_t *p, menu_t *dflt, char *str_goto );
char	*exec_menu_sub( menu_t *p, menu_t *dflt, char *str_goto );
void	clr_menu_current_path( void );
const char	*get_menu_current_path( void );
void	push_menu_current_path( const char *path );
void	pop_menu_current_path( void );
void	set_flg_menu_dflt( bool_t flg );
bool_t	get_flg_menu_dflt( void );
bool_t	chk_err_menu_kind( menu_t *ls );
bool_t	set_menu_check_item( menu_t *p );
bool_t	set_menu_radio_item( menu_t *ls, menu_t *p );
ask_t	exec_menu_ask( const char *ttl, ask_t dflt, bool_t can_cancel );
ask_t	exec_menu_ask_no_msg(
	const char *ttl, ask_t dflt, bool_t can_cancel
);
char	*cb_menu_ask_init( menu_t **pp, menu_t **dflt );
char	*cb_menu_ask_yes( menu_t **pp, menu_t **dflt );
char	*cb_menu_ask_no( menu_t **pp, menu_t **dflt );
char	*exec_menu_sel_num( long *p, long min, long max );
void	sel_menu_clr( draw_menu_t *data );
menu_t	*sel_menu( menu_t *p, menu_t *dflt );
menu_t	*sel_menu_sub( menu_t *p, menu_t *dflt );
long	set_ls_menu(
	draw_menu_t *data,
	menu_t *p,
	long page_sel_n
);
menu_t	*srch_menu( menu_t *ls, const char *sub_path );
menu_t	*srch_next_menu(
	menu_t *ls, menu_t *p, bool_t flg_skip_hidden
);
menu_t	*srch_goto_menu( menu_t *p, char *str_goto );
void	set_chk_on_menu( menu_t *p, char *sub_path );
void	set_chk_off_menu( menu_t *p, char *sub_path );
bool_t	set_flg_menu( menu_t *p, char *sub_path, unsigned long flg );
bool_t	clr_flg_menu( menu_t *p, char *sub_path, unsigned long flg );
bool_t	equ_flg_menu(
	menu_t *p, char *sub_path, unsigned long flg, bool_t flg_set
);
void	wait_key( bool_t flg_can_move_crsr );
void	wait_key_ex( bool_t flg_exec_key, bool_t flg_can_move_crsr );
long	chk_key( bool_t flg_clr_key_buf, bool_t flg_chk_menu );
void	chk_dup_short_key( void );
void	chk_dup_short_key_init( void );
bool_t	chk_dup_short_key_main( menu_t *ls );
bool_t	chk_dup_short_key_sub( unsigned char c, menu_t *ls );
bool_t	chk_short_key( menu_t *ls, long c );
menu_t	*get_ls_menu_macro_func( void );
menu_t	*get_ls_menu_macro_mouse( void );
menu_t	*get_ls_menu_macro_joystick( void );
char	*get_macro_str( long n );
char	*get_macro_func( long n );
char	*get_macro_mouse_click( long n );
char	*get_macro_mouse_d_click( long n );
char	*get_macro_mouse_p_click( long n );
char	*get_macro_mouse_press( long n );
char	*get_macro_mouse_release( long n );
char	*get_macro_mouse_motion( long n );
char	*get_macro_joystick( long j, long n );
bool_t	get_flg_chk_menu( void );
bool_t	get_flg_chk_short_key( void );
bool_t	get_flg_space_select( void );
bool_t	set_flg_space_select( bool_t flg );
long	get_sel_menu_accel_key( void );
bool_t	get_flg_move_crsr_dflt( void );
bool_t	set_flg_move_crsr_dflt( bool_t flg );
void	check_memory_menu_c( void );

#ifdef __cplusplus
}
#endif
