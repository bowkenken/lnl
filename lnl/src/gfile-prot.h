/* gfile.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_game_file( void );
void	reset_static_game_file( void );
char	*init_dir_game( const char *home, const char *dir, bool_t flg_GPL );
const char	*get_home_dir( void );
void	get_path_game_data_txt( char *path, long n );
void	get_path_game_data_bin( char *path, long n );
void	get_path_game_data_cnf( char *path, long n );
void	get_path_game_data_rep( char *path, long n );
void	get_path_bug_repo_txt( char *path );
void	get_path_bug_repo_bin( char *path );
void	get_path_bug_repo_cnf( char *path );
void	get_path_bug_repo_rep( char *path );
FILE	*open_game_data( char type, long n, bool_t flg_txt );
FILE	*open_game_data_cnf( char type, long n );
FILE	*open_game_replay( char type, long n );
void	remove_replay_file( long n );
long	load_char( FILE *fp, bool_t flg_chk_eof );
char	*load_line_skip_spc( FILE *fp, bool_t flg_chk_eof );
char	*load_line( FILE *fp, bool_t flg_chk_eof );
char	*set_rc_lex_file_name( char *name );
char	*get_rc_lex_file_name( void );
long	clr_rc_lex_line( void );
long	inc_rc_lex_line( void );
long	dec_rc_lex_line( void );
long	get_rc_lex_line( void );
bool_t	set_rc_lex_err( bool_t flg );
bool_t	get_rc_lex_err( void );
rc_token_t	rc_lex( FILE *fp, rc_union_t *u, bool_t flg_err_exit );
void	rc_unlex( FILE *fp, const rc_union_t *u, rc_token_t t );
rc_token_t	rc_lex_char( FILE *fp, rc_union_t *u, bool_t flg_err_exit );
rc_token_t	rc_lex_str( FILE *fp, rc_union_t *u, bool_t flg_err_exit );
long	rc_lex_oct( FILE *fp, long len, bool_t flg_err_exit );
long	rc_lex_dec( FILE *fp, long len, bool_t flg_err_exit );
long	rc_lex_hex_dec( FILE *fp, long len, bool_t flg_err_exit );
long	rc_lex_digit( FILE *fp, long base, long len, bool_t flg_err_exit );
void	rc_lex_id( FILE *fp, rc_union_t *u, bool_t flg_err_exit );
long	rc_lex_getc( FILE *fp, bool_t flg_chk_eof, bool_t flg_err_exit );
void	rc_lex_ungetc( FILE *fp, long c );
bool_t	rename_back_up_file( char *fname );
square_dir_t	trans_idx_to_square_dir( long idx );
long	trans_square_dir_to_idx( square_dir_t dir );
chr_kind_t	trans_idx_to_chr_kind( long idx );
long	trans_chr_kind_to_idx( chr_kind_t k );
position_kind_t	trans_idx_to_position_kind( long idx );
long	trans_position_kind_to_idx( position_kind_t k );
main_race_t	trans_idx_to_main_race_kind( long idx );
long	trans_main_race_kind_to_idx( main_race_t k );
sub_race_t	trans_idx_to_sub_race_kind( long idx );
long	trans_sub_race_kind_to_idx( sub_race_t k );
sex_t	trans_idx_to_sex_kind( long idx );
long	trans_sex_kind_to_idx( sex_t k );
long	get_abl_kind_trans_tab_max_n( void );
abl_kind_t	trans_idx_to_abl_kind( long idx );
long	trans_abl_kind_to_idx( abl_kind_t k );
move_kind_t	trans_idx_to_move_kind( long idx );
long	trans_move_kind_to_idx( move_kind_t k );
long	get_move_ls_trans_tab_max_n( void );
move_ls_kind_t	trans_idx_to_move_ls_kind( long idx );
long	trans_move_ls_kind_to_idx( move_ls_kind_t k );
act_kind_t	trans_idx_to_act_kind( long idx );
long	trans_act_kind_to_idx( act_kind_t k );
trgt_kind_t	trans_idx_to_trgt_kind( long idx );
long	trans_trgt_kind_to_idx( trgt_kind_t k );
dist_t	trans_idx_to_dist_kind( long idx );
long	trans_dist_kind_to_idx( dist_t k );
auto_mark_trgt_t	trans_idx_to_am_trgt( long idx );
long	trans_am_trgt_to_idx( auto_mark_trgt_t k );
auto_mark_dist_t	trans_idx_to_am_dist( long idx );
long	trans_am_dist_to_idx( auto_mark_dist_t k );
auto_mark_act_t	trans_idx_to_am_act( long idx );
long	trans_am_act_to_idx( auto_mark_act_t k );
auto_mark_cond_t	trans_idx_to_am_cond( long idx );
long	trans_am_cond_to_idx( auto_mark_cond_t k );
dflt_auto_mark_t	trans_idx_to_am_dflt( long idx );
long	trans_am_dflt_to_idx( dflt_auto_mark_t k );
attitude_t	trans_idx_to_attitude_kind( long idx );
long	trans_attitude_kind_to_idx( attitude_t k );
item_kind_t	trans_idx_to_item_kind( long idx );
long	trans_item_kind_to_idx( item_kind_t k );
star_drop_kind_t	trans_idx_to_key_item_kind( long idx );
long	trans_key_item_kind_to_idx( star_drop_kind_t k );
wpn_kind_t	trans_idx_to_wpn_kind( long idx );
long	trans_wpn_kind_to_idx( wpn_kind_t k );
bow_kind_t	trans_idx_to_bow_kind( long idx );
long	trans_bow_kind_to_idx( bow_kind_t k );
armor_kind_t	trans_idx_to_armor_kind( long idx );
long	trans_armor_kind_to_idx( armor_kind_t k );
wpn_randm_art_kind_t	trans_idx_to_wpn_randm_art_kind( long idx );
long	trans_wpn_randm_art_kind_to_idx( wpn_randm_art_kind_t k );
armor_randm_art_kind_t	trans_idx_to_armor_randm_art_kind( long idx );
long	trans_armor_randm_art_kind_to_idx( armor_randm_art_kind_t k );
long	get_potion_trans_tab_max_n( void );
potion_kind_t	trans_idx_to_potion_kind( long idx );
long	trans_potion_kind_to_idx( potion_kind_t k );
long	get_scroll_trans_tab_max_n( void );
scroll_kind_t	trans_idx_to_scroll_kind( long idx );
long	trans_scroll_kind_to_idx( scroll_kind_t k );
stick_kind_t	trans_idx_to_stick_kind( long idx );
long	trans_stick_kind_to_idx( stick_kind_t k );
acce_kind_t	trans_idx_to_acce_kind( long idx );
long	trans_acce_kind_to_idx( acce_kind_t k );
ring_kind_t	trans_idx_to_ring_kind( long idx );
long	trans_ring_kind_to_idx( ring_kind_t k );
amulet_kind_t	trans_idx_to_amulet_kind( long idx );
long	trans_amulet_kind_to_idx( amulet_kind_t k );
necklace_kind_t	trans_idx_to_necklace_kind( long idx );
long	trans_necklace_kind_to_idx( necklace_kind_t k );
inst_kind_t	trans_idx_to_inst_kind( long idx );
long	trans_inst_kind_to_idx( inst_kind_t k );
anthology_kind_t	trans_idx_to_anthology_kind( long idx );
long	trans_anthology_kind_to_idx( anthology_kind_t k );
light_kind_t	trans_idx_to_light_kind( long idx );
long	trans_light_kind_to_idx( light_kind_t k );
wish_level_t	trans_idx_to_wish_level( long idx );
long	trans_wish_level_to_idx( wish_level_t k );
food_kind_t	trans_idx_to_food_kind( long idx );
long	trans_food_kind_to_idx( food_kind_t k );
tobacco_kind_t	trans_idx_to_tobacco_kind( long idx );
long	trans_tobacco_kind_to_idx( tobacco_kind_t k );
tobacco_brand_t	trans_idx_to_tobacco_brand( long idx );
long	trans_tobacco_brand_to_idx( tobacco_brand_t k );
pipe_kind_t	trans_idx_to_pipe_kind( long idx );
long	trans_pipe_kind_to_idx( pipe_kind_t k );
rare_goods_kind_t	trans_idx_to_rare_goods_kind( long idx );
long	trans_rare_goods_kind_to_idx( rare_goods_kind_t k );
coin_kind_t	trans_idx_to_coin_kind( long idx );
long	trans_coin_kind_to_idx( coin_kind_t k );
long	get_spell_kind_trans_tab_max_n( void );
spell_kind_t	trans_idx_to_spell_kind( long idx );
long	trans_spell_kind_to_idx( spell_kind_t k );
mnstr_kind_t	trans_idx_to_mnstr_kind( long idx );
long	trans_mnstr_kind_to_idx( mnstr_kind_t k );
trap_kind_t	trans_idx_to_trap_kind( long idx );
long	trans_trap_kind_to_idx( trap_kind_t k );
fx_kind_t	trans_idx_to_fx_kind( long idx );
long	trans_fx_kind_to_idx( fx_kind_t k );
request_kind_t	trans_idx_to_request_kind( long idx );
long	trans_request_kind_to_idx( request_kind_t k );
long	get_stay_inn_kind_trans_tab_max_n( void );
stay_inn_kind_t	trans_idx_to_stay_inn_kind( long idx );
long	trans_stay_inn_kind_to_idx( stay_inn_kind_t k );
bool_t	copy_file( const char *src, const char *dst );
char	*cat_path( const char *path, const char *file );
bool_t	chk_exist_file( const char *s );
bool_t	chk_exist_dir( const char *s );
bool_t	make_dir( const char *path );
bool_t	make_dir_node( const char *path );
char	*cv_esc_quote_c( const long c );
char	*cv_esc_quote_str( const char *str );
char	*cv_esc_ctrl_str( const char *str );
long	srandm_crypt( long n );
long	randm_crypt( long c );
void	reset_load_save( char *path, bool_t flg_txt );
void	set_flg_crypt_txt( bool_t flg_txt );
void	reset_load_crypt( FILE *fp, bool_t flg_txt );
void	reset_save_crypt( FILE *fp, bool_t flg_txt );
void	reset_save_crypt_tab( void );
long	set_save_crypt_tab( FILE *fp, long n );
long	save_crypt_tab( FILE *fp, const char *s, ... );
long	save_crypt_str( FILE *fp, const char *s, ... );
long	load_crypt_str( FILE *fp, char *buf, long n );
long	load_crypt_c( FILE *fp );
long	load_crypt_c_sub( FILE *fp );
void	un_load_crypt_c( FILE *fp, long c );
void	check_memory_gfile_c( void );

#ifdef __cplusplus
}
#endif
/* gf-conf.c */

#ifdef __cplusplus
extern "C" {
#endif

bool_t	load_game_conf( void );
void	ver_up_game_conf_1_0_15( void );
void	ver_up_game_data_cnf_1_2_22( void );
bool_t	load_game_conf_head( FILE *fp, ver_t *ver );
void	load_game_conf_data_ver_1( FILE *fp, const ver_t *ver );
bool_t	load_game_conf_parse_ver_1( FILE *fp, const ver_t *ver );
bool_t	load_game_conf_set_val(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, long val
);
bool_t	load_game_conf_set_str(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, char *str
);
bool_t	load_game_conf_id_char_str(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, long c, char *str
);
bool_t	load_game_conf_id_num_str(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, long n, char *str
);
bool_t	load_game_conf_id_str_num_str(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, char *str1, long n, char *str2
);
bool_t	load_game_conf_id_char(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, long c
);
bool_t	load_game_conf_id_brace(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id
);
bool_t	load_game_conf_lang( char *id, char *str );
bool_t	load_game_conf_clk_tck( char *id, long val );
bool_t	load_game_conf_screen_size_auto( char *id, long val );
bool_t	load_game_conf_screen_size_col( char *id, long val );
bool_t	load_game_conf_screen_size_row( char *id, long val );
bool_t	load_game_conf_screen_size_message( char *id, long val );
bool_t	load_game_conf_screen_resize_map( char *id, long val );
bool_t	load_game_conf_scroll( char *id, char *str );
bool_t	load_game_conf_cursor_number_main( char *id, long val );
bool_t	load_game_conf_cursor_number_sub( char *id, long val );
bool_t	load_game_conf_joystick_kind( char *id, char *str );
bool_t	load_game_conf_clr_key_buf_every( char *id, long val );
bool_t	load_game_conf_clr_key_buf_menu( char *id, long val );
bool_t	load_game_conf_space_select( char *id, long val );
bool_t	load_game_conf_redraw_every_turn( char *id, long val );
bool_t	load_game_conf_mul_line( char *id, long val );
bool_t	load_game_conf_stat_bar_hint_chr( char *id, long val );
bool_t	load_game_conf_stat_bar_hint_obj( char *id, long val );
bool_t	load_game_conf_move_crsr_dflt( char *id, long val );
bool_t	load_game_conf_double_click_wait( char *id, long val );
bool_t	load_game_conf_music_volume( char *id, long val );
bool_t	load_game_conf_sound_volume( char *id, long val );
bool_t	load_game_conf_joystick_number( char *id, long val );
bool_t	load_game_conf_audio_buf_siz( char *id, long val );
bool_t	load_game_conf_gnome( char *id, long val );
bool_t	load_game_conf_set_window_position( char *id, long val );
bool_t	load_game_conf_win_pos( char *id, long val, win_kind_t kind );
bool_t	load_game_conf_vfx_mbr( flg_vfx_mbr_t flg, long val );
bool_t	load_game_conf_vfx_mnstr( flg_vfx_mnstr_t flg, long val );
bool_t	load_game_conf_vfx_wait( char *id, long val );
bool_t	load_game_conf_color_name( char *id, char *name );
bool_t	load_game_conf_color_fg( char *id, char *color );
bool_t	load_game_conf_color_bg( char *id, char *color );
bool_t	load_game_conf_attribute_underline( char *id, long val );
bool_t	load_game_conf_attribute_reverse( char *id, long val );
bool_t	load_game_conf_attribute_blink( char *id, long val );
bool_t	load_game_conf_attribute_bold( char *id, long val );
bool_t	load_game_conf_set_key( char *id, long c, char *str );
bool_t	load_game_conf_unset_key( char *id, long c );
bool_t	load_game_conf_set_macro_func(
	char *id, char *joy, long n, char *macro
);
bool_t	load_game_conf_menu(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id
);
bool_t	load_game_conf_menu_line(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id
);
bool_t	load_game_data_cnf( long n );
void	reset_load_game_data_cnf( void );
bool_t	chk_load_game_data_cnf( void );
bool_t	load_game_data_cnf_ver_1( FILE *fp, const ver_t *ver );
bool_t	load_game_data_cnf_parse_ver_1(
	FILE *fp, const ver_t *ver
);
bool_t	load_game_data_cnf_id_num_eq_str_ver_1(
	FILE *fp, const ver_t *ver,
	char *id, long n, char *str
);
bool_t	load_game_data_cnf_block_ver_1(
	FILE *fp, const ver_t *ver,
	char *id, long n
);
bool_t	save_game_conf( void );
bool_t	save_game_conf_ver_1( const ver_t *ver );
bool_t	save_game_conf_contents( FILE *fp, const ver_t *ver );
bool_t	save_game_conf_language( FILE *fp, const ver_t *ver );
bool_t	save_game_conf_frame_rate( FILE *fp, const ver_t *ver );
bool_t	save_game_conf_screen_size( FILE *fp, const ver_t *ver );
bool_t	save_game_conf_scroll( FILE *fp, const ver_t *ver );
bool_t	save_game_conf_crsr_ptn_n( FILE *fp, const ver_t *ver );
bool_t	save_game_conf_flg( FILE *fp, const ver_t *ver );
bool_t	save_game_conf_audio_buf_siz( FILE *fp, const ver_t *ver );
bool_t	save_game_conf_gnome( FILE *fp, const ver_t *ver );
bool_t	save_game_conf_set_window_position( FILE *fp, const ver_t *ver );
bool_t	save_game_conf_win_pos( FILE *fp, const ver_t *ver );
bool_t	save_game_conf_mouse( FILE *fp, const ver_t *ver );
bool_t	save_game_conf_sound( FILE *fp, const ver_t *ver );
bool_t	save_game_conf_joystick( FILE *fp, const ver_t *ver );
bool_t	save_game_conf_vfx( FILE *fp, const ver_t *ver );
bool_t	save_game_conf_color( FILE *fp, const ver_t *ver );
bool_t	save_game_conf_color_sub(
	FILE *fp, char *name, curs_attr_n_t attr_n
);
bool_t	save_game_conf_user_menu( FILE *fp, const ver_t *ver );
bool_t	save_game_conf_key_tab( FILE *fp, const ver_t *ver );
bool_t	save_game_conf_func( FILE *fp, const ver_t *ver );
bool_t	save_game_conf_func_sub(
	FILE *fp,
	const ver_t *ver,
	const char *tag,
	const char *joy,
	long n,
	const char *macro
);
bool_t	save_game_data_cnf_ver_1( const ver_t *ver, long n );
bool_t	save_game_data_cnf_contents(
	FILE *fp, const ver_t *ver
);
void	back_up_game_conf( void );
const char	*get_win_kind_name( win_kind_t k );
const char	*cv_joystick_kind_to_name( joy_kind_t k );
joy_kind_t	cv_joystick_name_to_kind( const char *name );
char	*cv_color_to_name( int color );
int	cv_name_to_color( char *name );
void	check_memory_gf_conf_c( void );

#ifdef __cplusplus
}
#endif
/* gf-crsr.c */

#ifdef __cplusplus
extern "C" {
#endif

bool_t	load_crsr_ptn( crsr_ptn_t *ptn, long *max_n );
bool_t	load_crsr_ptn_head( FILE *fp, crsr_ptn_t *ptn );
bool_t	load_crsr_ptn_misc( FILE *fp, crsr_ptn_t *ptn );
bool_t	load_crsr_ptn_data( FILE *fp, crsr_ptn_t *ptn );
bool_t	save_crsr_ptn( crsr_ptn_t *ptn, long max_n );
void	back_up_crsr_ptn( void );
void	check_memory_gf_crsr_c( void );

#ifdef __cplusplus
}
#endif
/* gf-gconf.c */

#ifdef __cplusplus
extern "C" {
#endif

bool_t	load_graph_conf( char *path );
bool_t	load_graph_conf_head( FILE *fp, ver_t *ver );
void	load_graph_conf_data_ver_1( FILE *fp, const ver_t *ver );
bool_t	load_graph_conf_parse_ver_1( FILE *fp, const ver_t *ver );
bool_t	load_graph_conf_block_begin(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, long val
);
bool_t	load_graph_conf_block_end(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, long val
);
bool_t	load_graph_conf_set_val(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, long val
);
bool_t	load_graph_conf_set_str(
	FILE *fp, const ver_t *ver, bool_t flg_err_exit,
	char *id, char *str
);
void	check_memory_gf_gconf_c( void );

#ifdef __cplusplus
}
#endif
/* gf-outmap.c */

#ifdef __cplusplus
extern "C" {
#endif

char	*get_out_map_file_name( char *s );
bool_t	out_map_file( void );
void	check_memory_gf_outmap_c( void );

#ifdef __cplusplus
}
#endif
/* gf-replay.c */

#ifdef __cplusplus
extern "C" {
#endif

bool_t	load_game_replay( bool_t flg_txt_data, long n );
void	reset_load_game_replay( long n );
bool_t	load_game_replay_head_ver_1( FILE *fp, ver_t *ver, bool_t flg_txt );
bool_t	load_game_replay_ver_1( FILE *fp, const ver_t *ver, bool_t flg_txt );
bool_t	load_game_replay_parse_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	load_game_replay_id_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	char *id
);
bool_t	load_game_replay_str_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	char *str
);
bool_t	save_game_replay( void );
bool_t	save_game_replay_slot( long n );
bool_t	save_bug_repo_replay( void );
bool_t	copy_file_bug_repo( void );
bool_t	save_game_replay_ver_1( const ver_t *ver, long n );
bool_t	save_game_replay_contents(
	FILE *fp, const ver_t *ver, long n
);
void	check_memory_gf_replay_c( void );

#ifdef __cplusplus
}
#endif
/* gf-save.c */

#ifdef __cplusplus
extern "C" {
#endif

bool_t	load_game_data( bool_t flg_txt, long n );
void	set_flg_exit_shop( bool_t flg );
bool_t	get_flg_exit_shop( void );
void	appear_load_game_data( long slot_n );
void	ver_up_game_data_1_0_4( void );
void	ver_up_game_data_1_1_1( void );
void	ver_up_game_data_1_1_3( void );
void	ver_up_game_data_1_2_6( void );
void	ver_up_game_data_1_2_12( void );
void	ver_up_game_data_1_2_27( void );
void	ver_up_game_data_1_2_35( void );
void	ver_up_game_data_1_2_36( void );
void	reset_load_game_data( void );
bool_t	chk_load_game_data( void );
bool_t	load_game_data_head_ver_1( FILE *fp, ver_t *ver, bool_t flg_txt );
bool_t	load_game_data_ver_1( FILE *fp, const ver_t *ver, bool_t flg_txt );
bool_t	load_game_data_parse_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	load_game_data_id_eq_num_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	char *id, long n
);
bool_t	load_game_data_id_num_eq_str_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	char *id, long n, char *str
);
bool_t	load_game_data_auto_mark_ttl_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long n, char *ttl
);
bool_t	load_game_data_block_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	char *id, long n
);
bool_t	load_game_data_square_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	load_game_data_class_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long n
);
bool_t	load_game_data_mbr_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long n
);
bool_t	load_game_data_pet_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long n
);
bool_t	load_game_data_chr_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	chr_t *chr
);
bool_t	load_game_data_chr_fx_all_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	chr_t *chr
);
bool_t	load_game_data_chr_fx_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	chr_t *chr
);
bool_t	load_game_data_fx_data_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	fx_data_t *fx_data
);
bool_t	load_game_data_modifier_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	modifier_t *m
);
bool_t	load_game_data_potion_color_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	load_game_data_scroll_ttl_syllable_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	load_game_data_stick_material_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	stick_kind_t kind
);
bool_t	load_game_data_acce_material_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	acce_kind_t kind
);
bool_t	load_game_data_potion_identified_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	load_game_data_scroll_identified_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	load_game_data_item_mbr_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long ls_mbr_n
);
bool_t	load_game_data_item_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	load_game_data_item_wpn_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	load_game_data_item_armor_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	load_game_data_item_potion_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	load_game_data_item_scroll_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	load_game_data_item_stick_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	load_game_data_item_acce_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	load_game_data_item_inst_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	load_game_data_item_anthology_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	load_game_data_item_light_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	load_game_data_item_spike_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	load_game_data_item_food_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	load_game_data_item_chest_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	load_game_data_item_tobacco_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	load_game_data_item_pipe_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	load_game_data_item_disposal_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	load_game_data_item_rare_goods_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	load_game_data_item_bone_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	load_game_data_item_coin_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	load_game_data_item_junk_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	load_game_data_key_item_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	load_game_data_auto_mark_ls_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long ls_mbr_n
);
bool_t	load_game_data_auto_mark_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long ls_mbr_n, long auto_mark_n
);
bool_t	load_game_data_auto_mark_appoint_item_ls_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long ls_mbr_n
);
bool_t	load_game_data_auto_mark_appoint_item_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long ls_mbr_n, long auto_mark_n
);
bool_t	load_game_data_flg_srch_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	load_game_data_spell_ls_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long ls_mbr_n
);
bool_t	load_game_data_mbr_formation_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	load_game_data_pet_formation_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	load_game_data_request_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	load_game_data_playing_report_mbr_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long ls_mbr_n
);
bool_t	load_game_data_playing_report_party_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long ls_mbr_n
);
bool_t	load_game_data_playing_report_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	playing_report_t *p
);
bool_t	load_game_data_n( FILE *fp, long *n );
bool_t	load_game_data_s( FILE *fp, char *s, long len );
bool_t	load_game_data_c( FILE *fp, char *c );
bool_t	load_game_data_skip_c( FILE *fp, char c, bool_t flg_draw );
bool_t	load_game_data_skip_token( FILE *fp, rc_token_t c, bool_t flg_draw );
bool_t	save_game_data( bool_t flg_txt, long n );
bool_t	save_game_data_sub( bool_t flg_txt, long n );
bool_t	save_game_data_ver_1( const ver_t *ver, bool_t flg_txt, long n );
bool_t	save_game_data_contents(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_randm_seed_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_dun_lev_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_turn_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_square_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_class_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_mbr_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_chr_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	chr_t *chr
);
bool_t	save_game_data_fx_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	fx_t *fx
);
bool_t	save_game_data_fx_data_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	fx_data_t *fx_data
);
bool_t	save_game_data_modifier_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	const modifier_t *m
);
bool_t	save_game_data_work_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	chr_t *chr
);
bool_t	save_game_data_item_all_mbr_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_item_mbr_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr
);
bool_t	save_game_data_item_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	save_game_data_item_wpn_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	save_game_data_item_armor_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	save_game_data_item_potion_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	save_game_data_item_scroll_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	save_game_data_item_stick_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	save_game_data_item_acce_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	save_game_data_item_inst_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	save_game_data_item_anthology_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	save_game_data_item_light_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	save_game_data_item_spike_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	save_game_data_item_food_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	save_game_data_item_chest_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	save_game_data_item_tobacco_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	save_game_data_item_pipe_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	save_game_data_item_disposal_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	save_game_data_item_rare_goods_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	save_game_data_item_bone_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	save_game_data_item_coin_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	save_game_data_item_junk_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	mbr_t *mbr, item_t *item
);
bool_t	save_game_data_potion_color_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_scroll_ttl_syllable_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_stick_material_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	stick_kind_t kind
);
bool_t	save_game_data_acce_material_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	acce_kind_t kind
);
bool_t	save_game_data_potion_identified_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_scroll_identified_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_key_item_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_auto_mark_ls_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_auto_mark_appoint_item_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	long ls_mbr_n
);
bool_t	save_game_data_flg_srch_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_auto_mark_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	const auto_mark_t *a, long auto_mark_n
);
bool_t	save_game_data_spell_ls_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_spell_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	cast_tab_t *tab
);
bool_t	save_game_data_mbr_formation_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_pet_formation_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_request_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_playing_report_mbr_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_playing_report_party_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt
);
bool_t	save_game_data_playing_report_ver_1(
	FILE *fp, const ver_t *ver, bool_t flg_txt,
	playing_report_t *p
);
bool_t	get_save_load_ttl(
	char *msg, long n,
	bool_t flg_txt, bool_t flg_replay
);
bool_t	get_game_data_head_time(
	char *str, long n,
	bool_t flg_txt, bool_t flg_replay
);
void	check_memory_gf_save_c( void );

#ifdef __cplusplus
}
#endif
/* gf-town.c */

#ifdef __cplusplus
extern "C" {
#endif

bool_t	load_town_ptn( town_ptn_t *ptn );
bool_t	load_town_ptn_head( FILE *fp, town_ptn_t *ptn );
bool_t	load_town_ptn_col( FILE *fp, town_ptn_t *ptn );
bool_t	load_town_ptn_map( FILE *fp, town_ptn_t *ptn );
bool_t	save_town_ptn( town_ptn_t *ptn );
void	save_town_ptn_col_1byte( FILE *fp, town_ptn_t *ptn );
void	save_town_ptn_col_2byte( FILE *fp );
void	back_up_town_ptn( void );
void	check_memory_gf_town_c( void );

#ifdef __cplusplus
}
#endif
