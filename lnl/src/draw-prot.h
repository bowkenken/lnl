/* draw.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_draw( void );
void	reset_static_draw( void );
void	ver_up_draw_ver_1_2_22( void );
void	measure_clk_tck( void );
void	print_wrn( const char *s, ... );
void	print_err( const char *s, ... );
void	print_lex_wrn( const char *s, ... );
void	print_lex_err( const char *s, ... );
void	print_words(
	const char *name,
	sex_t sex,
	const char *fmt_female,
	const char *fmt_male,
	...
);
void	print_words_win(
	const char *name,
	sex_t sex,
	const char *fmt_female,
	const char *fmt_male,
	...
);
void	print_words_sub(
	bool_t flg_draw_win,
	const char *name,
	const char *buf
);
const char	*get_words_line( const char *p, long draw_max_n );
const char	*get_next_char_str( const char *p );
long	get_next_char_len( const char *p );
void	print_msg_mbr( chr_t *chr, flg_msg_t flg, const char *s, ... );
void	print_msg_find( chr_t *chr, flg_msg_t flg, const char *s, ... );
void	print_msg( flg_msg_t flg, const char *s, ... );
void	more( flg_msg_t flg, bool_t flg_mul );
void	wipe_msg( void );
void	clr_msg( void );
void	redraw_msg( void );
void	scroll_1_msg( long add );
long	add_scroll_1_msg_idx( long add );
void	print_log_back_1( void );
void	print_log( void );
void	print_log_back( long idx );
long	get_ls_msg_idx( void );
long	get_ls_msg_line_per_page( void );
bool_t	set_msg_mul_line( bool_t flg );
bool_t	chk_msg_mul_line( void );
long	get_ls_msg_n( void );
void	draw_ls_msg( long n );
ls_msg_t	*get_ls_msg( long idx );
long	add_scroll_msg_idx( long add );
void	draw_stat_bar( void );
long	calc_stat_bar_line_n( void );
bool_t	get_flg_stat_bar_hint_chr( void );
void	set_flg_stat_bar_hint_chr( bool_t flg );
bool_t	get_flg_stat_bar_hint_obj( void );
void	set_flg_stat_bar_hint_obj( bool_t flg );
void	print_str( long scrn_x, long scrn_y, const char *s, ... );
bool_t	print_vfx(
	bool_t flg_gui, long scrn_x, long scrn_y, const char *s, ...
);
bool_t	print_vfx_cui(
	bool_t flg_gui, long scrn_x, long scrn_y, const char *s, ...
);
void	wipe_vfx( long map_x, long map_y, long dx, long dy );
bool_t	set_redraw_every_turn( bool_t flg );
bool_t	chk_redraw_every_turn( void );
void	wipe_all( void );
void	redraw_all( void );
void	set_cui_mouse_add_handler_map( void );
void	set_cui_mouse_add_handler_msg( void );
void	set_cui_mouse_add_handler_stat( void );
void	set_cui_mouse_add_handler_mbr_stat( long mbr_n );
void	draw_map( long map_x, long map_y, long dx, long dy );
void	draw_map_force( long map_x, long map_y, long dx, long dy );
void	draw_map_sub(
	long map_x, long map_y,
	long dx, long dy,
	bool_t flgForce
);
void	redraw_map( void );
void	redraw_map_force( void );
void	redraw_map_sub( bool_t flgForce );
void	wipe_map( void );
void	force_clr_redraw_map( void );
bool_t	cb_cui_mouse_scroll_map(
	long scroll_dir, long n, const char *macro
);
bool_t	cb_cui_mouse_scroll_msg(
	long scroll_dir, long n, const char *macro
);
void	draw_party( void );
void	draw_mbr( mbr_t *p );
void	draw_square( void );
void	draw_all_mnstr( void );
void	draw_mnstr( mnstr_t *p );
void	draw_all_pet( void );
void	draw_pet( pet_t *p );
void	draw_chr( chr_t *chr );
void	set_flg_update_chr( long mapX, long mapY, bool_t flg );
bool_t	get_flg_update_chr( long mapX, long mapY );
void	draw_door( long dr_n );
void	draw_item( item_t *p );
void	draw_trap( trap_t *p );
void	draw_menu( draw_menu_t *data );
bool_t	cb_cui_mouse_point_menu( long btn, long n, const char *macro );
bool_t	cb_cui_mouse_click_menu( long btn, long n, const char *macro );
bool_t	cb_cui_mouse_click_menu_page( long btn, long n, const char *macro );
bool_t	cb_cui_mouse_click_menu_outside(
	long btn, long n, const char *macro
);
void	set_cui_mouse_add_handler_common_scroll( void );
bool_t	cb_cui_mouse_point_dummy(
	long btn, long n, const char *macro
);
bool_t	cb_cui_mouse_click_common_scroll(
	long btn, long n, const char *macro
);
bool_t	cb_cui_mouse_scroll_common_scroll(
	long scroll_dir, long n, const char *macro
);
void	draw_menu_num( long figure, long sel_n, char num[] );
bool_t	cb_cui_mouse_point_menu_num( long btn, long n, const char *macro );
bool_t	cb_cui_mouse_click_menu_num( long btn, long n, const char *macro );
bool_t	cb_cui_mouse_click_menu_num_sel(
	long btn, long n, const char *macro
);
bool_t	cb_cui_mouse_scroll_menu_num_sel(
	long scroll_dir, long n, const char *macro
);
bool_t	get_flg_cui_mouse_scroll_menu_num_is_sel( void );
void	set_flg_cui_mouse_scroll_menu_num_is_sel( bool_t flg );
bool_t	get_flg_cui_mouse_r_click_menu_num_is_cancel( void );
void	set_flg_cui_mouse_r_click_menu_num_is_cancel( bool_t flg );
char	*get_str_open_win_item( char *kind );
char	*get_str_branch( char *kind );
bool_t	wipe_menu( void );
void	draw_all_mbr_stat( void );
void	draw_mbr_stat( mbr_t *mbr );
void	draw_misc_stat( void );
void	switch_stat_mode( long add );
stat_mode_t	get_stat_mode( void );
bool_t	cb_cui_mouse_click_stat( long btn, long n, const char *macro );
bool_t	cb_cui_mouse_click_switch_stat(
	long btn, long n, const char *macro
);
const char	*get_stat_dun_lev_str( void );
void	draw_misc_stat_time( bool_t flg_force );
gui_vfx_t	*alloc_gui_vfx_bash( bool_t flg_crtcl );
gui_vfx_t	*alloc_gui_vfx_arw( long dir_n );
gui_vfx_t	*alloc_gui_vfx_throw_item( char mjr, char mnr );
gui_vfx_t	*alloc_gui_vfx_spell( resi_kind_t resi );
gui_vfx_t	*alloc_gui_vfx_blast( blast_kind_t blast );
gui_vfx_t	*alloc_gui_vfx_ninja( spell_kind_t spell );
gui_vfx_t	*alloc_gui_vfx( void );
void	free_gui_vfx( gui_vfx_t *vfx );
void	clr_gui_vfx_all( void );
void	clr_gui_vfx( long map_x, long map_y );
void	set_gui_vfx( long map_x, long map_y, gui_vfx_t *vfx );
gui_vfx_t	*get_gui_vfx( long map_x, long map_y );
long	calc_dir_n( const pos_t *bgn, const pos_t *end );
bool_t	vfx_spell( spell_tab_t *tab, long arw_n, pos_t bgn[], pos_t end[] );
void	vfx_spell_typhoon( void );
void	vfx_spell_conflagration( long arw_n, pos_t end[] );
bool_t	vfx_spell_conflagration_sub( long x, long y, long height );
void	vfx_spell_earthquake( void );
void	vfx_spell_thunder( long arw_n, pos_t end[] );
void	draw_gui_vfx_spell_thunder( gui_vfx_t *gui_vfx, pos_t *pos );
void	vfx_spell_inundation( void );
void	vfx_hit( chr_t *chr, long x, long y );
void	vfx_crtcl( chr_t *chr, long x, long y );
void	vfx_ninja_crtcl( chr_t *chr, long x, long y );
void	get_vfx_attr( curs_attr_t *attr );
void	set_vfx_attr( const curs_attr_t *attr );
void	set_vfx_attr_n( curs_attr_n_t n );
void	vfx_arw(
	chr_kind_t kind,
	pos_t bgn[], pos_t end[],
	gui_vfx_t *gui_vfx,
	char c, long len
);
void	vfx_arw_line(
	pos_t bgn[], pos_t end[],
	gui_vfx_t *gui_vfx,
	const char *str, long len,
	long frame, long clr_frame, bool_t flg_clr
);
void	vfx_arw_mul_line(
	long arw_n, pos_t bgn[], pos_t end[],
	gui_vfx_t *gui_vfx,
	const char *str, long len,
	long frame, long clr_frame, bool_t flg_clr
);
void	vfx_num( chr_t *p, long n );
void	bgn_sync_vfx_num( void );
void	end_sync_vfx_num( void );
long	get_draw_num_frame( long len );
long	get_draw_num_sync_max_len( void );
bool_t	draw_num_sync( long idx );
void	draw_num( long map_x, long map_y, long n, chr_t *chr );
void	draw_num_x_1(
	long map_x, long map_y,
	long n, long idx,
	chr_t *chr
);
void	draw_lev_up( long map_x, long map_y, long n, chr_t *chr );
void	draw_blast(
	chr_kind_t kind,
	long map_x, long map_y,
	blast_t *p,
	gui_vfx_t *gui_vfx,
	char *str
);
void	draw_blast_cui(
	chr_kind_t kind,
	long map_x, long map_y,
	blast_t *p,
	gui_vfx_t *gui_vfx,
	char *str
);
void	draw_blast_sub(
	bool_t flg_cui,
	chr_kind_t kind,
	long map_x, long map_y,
	blast_t *p,
	gui_vfx_t *gui_vfx,
	char *str
);
void	draw_request( request_t *req );
void	draw_words( const char *name, const char *words, ... );
bool_t	cb_cui_mouse_click_words( long btn, long n, const char *macro );
void	redraw_mbr_data(
	mbr_t *org, mbr_t *mbr,
	long page_n, mbr_data_edit_kind_t edit_kind
);
void	draw_mbr_data_all(
	mbr_t *org, mbr_t *mbr,
	long page_n, mbr_data_edit_kind_t edit_kind
);
void	draw_mbr_data_all_cui(
	mbr_t *org, mbr_t *mbr,
	long page_n, mbr_data_edit_kind_t edit_kind
);
void	draw_mbr_data(
	mbr_t *org, mbr_t *mbr,
	data_n_t n, bool_t flg_rev,
	mbr_data_edit_kind_t edit_kind,
	bool_t flg_all
);
bool_t	cb_cui_mouse_point_mbr_data( long btn, long n, const char *macro );
bool_t	cb_cui_mouse_click_mbr_data( long btn, long n, const char *macro );
long	calc_mbr_data_idx( data_n_t next_n, data_n_t cur_n );
data_n_t	next_mbr_data(
	long page_n, data_n_t n, long d,
	mbr_data_edit_kind_t edit_kind
);
bool_t	chk_sel_data_n( data_n_t n, mbr_data_edit_kind_t edit_kind );
bool_t	gets_mbr_name( mbr_t *mbr );
bool_t	gets_mbr_face( mbr_t *mbr );
bool_t	gets_race_name( mbr_t *mbr );
bool_t	gets_pet_name( pet_t *pet );
void	print_skill_hint( long x, long y, skill_kind_t kind );
void	draw_edit_class_all(
	class_t *org, class_t *dst,
	edit_class_t sel_n, bool_t flg_sel_add
);
void	draw_edit_class(
	class_t *org, class_t *dst, edit_class_t n,
	bool_t flg_sel, bool_t flg_sel_add,
	bool_t flg_all
);
bool_t	cb_cui_mouse_point_edit_class( long btn, long n, const char *macro );
bool_t	cb_cui_mouse_click_edit_class( long btn, long n, const char *macro );
void	draw_edit_skill_all(
	class_t *org, class_t *dst,
	edit_skill_t sel_n
);
void	draw_edit_skill(
	class_t *org, class_t *dst, edit_skill_t n,
	bool_t flg_sel, bool_t flg_all
);
bool_t	cb_cui_mouse_point_edit_skill( long btn, long n, const char *macro );
bool_t	cb_cui_mouse_click_edit_skill( long btn, long n, const char *macro );
bool_t	gets_class_name( char *name );
bool_t	gets_item_alias( char *name );
bool_t	gets_auto_mark_info( char *name );
bool_t	gets_auto_mark_hint( char *name );
bool_t	gets_line( const char *prompt, char *s, long max_len );
bool_t	game_gets(
	long x, long y,
	const char *ttl, char *s, long len,
	bool_t flg_pick
);
void	game_gets_gui_sub( const char *ttl, char *s, long len );
void	pick_cntrl_str( char *s );
void	set_crsr( long x, long y );
void	reset_crsr( void );
void	draw_main_crsr( void );
void	draw_sub_crsr( void );
pos_t	*get_map_draw_pos( void );
pos_t	*get_map_draw_pos_gui( void );
rate_t	get_vfx_wait( void );
rate_t	set_vfx_wait( rate_t n );
flg_vfx_mbr_t	get_flg_vfx_mbr( void );
flg_vfx_mbr_t	set_flg_vfx_mbr( flg_vfx_mbr_t flg );
flg_vfx_mnstr_t	get_flg_vfx_mnstr( void );
flg_vfx_mnstr_t	set_flg_vfx_mnstr( flg_vfx_mnstr_t flg );
void	wait_clock( long frame );
void	wait_frame( long frame );
void	sleep_msec( long n );
void	wait_100_n_msec( long n );
void	wait_100_msec( void );
void	set_flg_break_key( bool_t flg_break );
bool_t	chk_flg_break_key( void );
long	read_char( long *p );
long	read_char_wait( long *p );
long	read_ctrl( long *p );
long	read_esc( long *p );
char	*get_reg_macro( void );
void	set_reg_macro( bool_t flg );
void	reg_macro_str( const char *s );
void	reg_macro( long c );
void	draw_replay( bool_t flg_redraw );
bool_t	get_key_pos( pos_t *pos );
long	get_key_num( void );
void	un_get_key( long c );
long	get_key_no_null( bool_t flg_clr_key_buf );
long	get_key( bool_t flg_clr_key_buf );
void	get_key_wait_cancel( bool_t flg_clr_key_buf );
void	get_key_wait_cancel_or_exec( bool_t flg_clr_key_buf );
void	get_key_wait_cancel_sub( bool_t flg_clr_key_buf, bool_t flg_exec );
long	get_key_sub( bool_t flg_clr_key_buf );
long	get_key_sub_1( bool_t flg_clr_key_buf, bool_t *p_flg_cont_exec );
long	get_key_sub_2( bool_t flg_clr_key_buf, bool_t *p_flg_cont_exec );
long	get_key_x68k( bool_t flg_clr_key_buf, bool_t *p_flg_cont_exec );
long	get_key_dos( bool_t *p_flg_cont_exec );
long	get_key_no_clr_dos( bool_t *p_flg_cont_exec );
long	get_key_half_wait( bool_t *p_flg_cont_exec );
long	get_key_std( bool_t *p_flg_cont_exec );
long	get_key_no_clr( bool_t *p_flg_cont_exec );
long	get_key_no_clr_default( bool_t *p_flg_cont_exec );
long	get_key_no_wait( void );
bool_t	chk_key_buf( void );
long	get_key_buf_char( void );
long	get_key_n( const char *p );
long	get_key_n_all( const char *p );
long	get_key_n_func( const char *p );
long	get_key_n_mouse( const char *p );
long	get_key_n_joystick( const char *p );
long	get_key_n_num( const char *p );
long	get_key_n_hex_dec( const char *p );
long	get_key_n_dec( const char *p );
long	get_key_n_oct( const char *p );
long	get_key_buf_char_sub( void );
bool_t	set_key_buf_char_head( long c );
bool_t	set_key_buf_char_tail( long c );
bool_t	set_key_buf_str_head( const char *s );
bool_t	set_key_buf_str_tail( const char *s );
bool_t	cv_key_buf_char_tail( long dst, long src );
long	get_key_tab_n( const char *key );
char	*get_key_tab_cmd( const char *key );
char	*get_key_tab_cmd_char( long c );
char	**get_key_tab( void );
void	set_key_tab( const char *key, const char *str );
void	set_key_tab_char( long c, const char *str );
long	*get_clk_tck( void );
bool_t	get_flg_draw_menu( void );
void	check_memory_draw_c( void );

#ifdef __cplusplus
}
#endif
