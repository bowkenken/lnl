/* call.cpp */

#ifdef __cplusplus
extern "C" {
#endif

void	gui_begin( void );
void	gui_end( void );
void	call_alloc_autorelease_pool( void );
void	call_release_autorelease_pool( void );
void	call_close_game_gui( void );
void	key_buf_lock( void );
void	key_buf_unlock( void );
bool_t	call_game_thread_create( void *(*func)( void * ) );
bool_t	call_game_thread_exit(
	void *(*func)( void * ), long code
);
const char	*call_get_home_dir( void );
void	call_ena_timer( void );
void	call_gui_map_cont_exec_set( bool_t flagExec );
void	call_gui_map_print_stat_bar_hint( void );
void	call_gui_menu_draw( draw_menu_t *data );
void	call_gui_menu_wipe( void );
long	call_cui_mouse_check_event( long c );
void	call_cui_mouse_reset_handler_tab( void );
long	call_cui_mouse_add_handler(
	bool_t flagEnable,
	long x, long y, long w, long h,
	bool_t (*funcPoint)( long btn, long n, const char *macro ),
	bool_t (*funcClick)( long btn, long n, const char *macro ),
	bool_t (*funcScroll)( long btn, long n, const char *macro ),
	long n,
	const char *macro
);
void	call_set_mouse_dflt_menu( long sel_n );
void	call_gui_message_set_flag_more( bool_t flag );
void	call_gui_message_draw( void );
void	call_gui_num_draw(
	volatile long *n, long min, long max, long figure
);
void	call_gui_num_wipe( void );
void	call_gui_input_string_draw(
	const char *ttl, const char *str, long len
);
void	call_gui_input_string_wipe( void );
void	call_gui_words_draw( const char *name, const char *str );
void	call_gui_words_draw_width(
	const char *name, const char *str,
	long w
);
void	call_gui_words_wipe( void );
void	call_gui_replay_bgn( void );
void	call_gui_replay_end( void );
void	call_gui_replay_draw( void );
void	call_gui_replay_wipe( void );
void	call_gui_class_edit_draw( class_t *p );
void	call_gui_class_edit_wipe( void );
void	call_gui_skill_edit_draw( class_t *p );
void	call_gui_skill_edit_wipe( void );
void	call_gui_chr_sheet_draw( mbr_t *org, mbr_t *mbr );
void	call_gui_chr_sheet_redraw( mbr_t *org, mbr_t *mbr );
void	call_gui_chr_sheet_wipe();
bool_t	call_sel_conf_eval_block_begin( void );
bool_t	call_sel_conf_eval_block_end( void );
bool_t	call_sel_conf_eval_set_num( long token, long n );
bool_t	call_sel_conf_eval_set_str( long token, char *str );
bool_t	call_sel_mbr_graph_begin( mbr_t *mbr );
void	call_sel_mbr_graph_end( void );
void	call_pcg_dun_reset( void );
void	call_pcg_dun_reload_all_mbr( void );
void	call_pcg_dun_draw_turn( bool_t flg_first );
void	call_pcg_dun_redraw( bool_t flgForce );
void	call_pcg_dun_draw(
	long map_x, long map_y,
	long map_w, long map_h,
	bool_t flagForce
);
void	call_pcg_dun_set_xx_attack(
	long kind, void *p );
void	call_pcg_dun_draw_string(
	long scrn_x, long scrn_y,
	const char *s, ... );
void	call_pcg_dun_draw_vfx(
	long scrn_x, long scrn_y,
	long scrn_w, long scrn_h );
void	call_pcg_dun_scroll( long map_x, long map_y );
long	call_pcg_dun_get_crsr_width( bool_t flagSub );
long	call_pcg_dun_get_crsr_height( bool_t flagSub );
long	call_pcg_dun_get_chr_draw_left( chr_t *chr, bool_t flagPre );
long	call_pcg_dun_get_chr_draw_right( chr_t *chr, bool_t flagPre );
long	call_pcg_dun_get_chr_draw_top( chr_t *chr, bool_t flagPre );
long	call_pcg_dun_get_chr_draw_bottom( chr_t *chr, bool_t flagPre );
bool_t	call_pcg_dun_clip_win( long mapX, long mapY, bool_t flg_gui );
bool_t	call_pcg_dun_clip_win_x( long mapX, bool_t flg_gui );
bool_t	call_pcg_dun_clip_win_y( long mapY, bool_t flg_gui );
void	call_demo_last_boss_reset( void );
bool_t	call_demo_last_boss_check_done( void );
void	call_demo_ending_skip_scene( void );
void	call_game_music_play_scene( bool_t flg_gui );
void	call_game_music_play( long kind, long idx );
void	call_game_music_replay( void );
void	call_game_music_set_volume( rate_t rate );
void	call_game_sound_play( long kind, long n );
void	call_game_sound_stop( void );
void	call_game_sound_set_volume( rate_t rate );
long	call_game_joystick_get_joy( void );
void	call_game_joystick_sel_joy( long n );
const char	*call_game_joystick_get_name( long n );
long	call_game_joystick_get_kind( void );
void	call_game_joystick_set_kind( long kind );
void	call_gui_stat_redraw( void );
void	call_gui_stat_draw( long n );
void	call_win_pos_set(
	win_kind_t k,
	long *px, long *py,
	long *pw, long *ph
);
bool_t	call_win_pos_get(
	win_kind_t k,
	long *px, long *py,
	long *pw, long *ph
);
long	call_key_get_char( void );
void	call_key_check_move_crsr( void );
void	call_sleep( long n );
void	check_memory_gui( void );

#ifdef __cplusplus
}
#endif
