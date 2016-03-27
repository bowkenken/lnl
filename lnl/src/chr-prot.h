/* chr.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_chr( void );
void	reset_static_chr( void );
bool_t	chk_flg_run_exec_all_phase( void );
void	exec_all_phase( void );
void	clr_chr_find( void );
void	chk_chr_find( void );
void	set_flg_mbr_find_mnstr( bool_t flg_find );
void	set_flg_mnstr_find_mbr( bool_t flg_find );
void	set_flg_boss_find_mbr( bool_t flg_find );
bool_t	chk_flg_mbr_find_mnstr( void );
bool_t	chk_flg_mnstr_find_mbr( void );
bool_t	chk_flg_boss_find_mbr( void );
void	last_boss_phase( void );
void	draw_phase( bool_t flg_first_phase );
void	move_phase_chr( chr_t *chr );
void	act_phase_chr( chr_t *chr );
void	dismissal_phase_chr( chr_t *chr );
bool_t	chk_can_act_chr( chr_t *chr );
bool_t	chk_bash_or_move( chr_t *chr );
void	bash_or_move( chr_t *chr );
void	act_throw_mnstr_null( chr_t *chr );
bool_t	chk_assist_chr( chr_t *chr );
bool_t	chk_adjoin_chr_trgt( chr_t *chr );
void	clr_map_chr( chr_t *chr );
void	set_map_chr( chr_t *chr );
void	clr_map_chr_dun( chr_t *chr );
void	set_map_chr_dun( chr_t *chr );
void	set_clr_map_chr_dun(
	chr_t *chr, char mjr, char mnr, flg_map_t flg
);
void	set_map_chr_hyper_boss( chr_t *chr );
void	move_chr( chr_t *chr );
void	move_chr_sub( chr_t *chr );
void	move_chr_std( chr_t *chr );
void	move_chr_mbr( chr_t *chr );
bool_t	chk_move_chr_dir( chr_t *chr, long *nx, long *ny );
bool_t	chk_move_chr_far_axis( chr_t *chr, long *nx, long *ny );
bool_t	chk_move_chr_cross_axis( chr_t *chr, long *nx, long *ny );
bool_t	chk_move_chr_scan_x( chr_t *chr, long sx, long *lx );
bool_t	chk_move_chr_scan_y( chr_t *chr, long sy, long *ly );
void	chk_chr_force_move( chr_t *chr );
bool_t	chk_chr_stagger( chr_t *chr );
bool_t	chk_chr_stagger_sub( chr_t *chr, flg_stat_t flg, long rate );
void	move_chr_stagger( chr_t *chr );
void	move_chr_wander( chr_t *chr );
void	move_chr_towner( chr_t *chr );
void	turn_dir_towner( chr_t *chr );
move_kind_t	get_move_kind_rand( chr_t *chr );
bool_t	chk_auto_door( chr_t *chr, long x1, long y1, long x2, long y2 );
bool_t	can_move_chr( chr_t *chr, long x, long y );
bool_t	can_move_chr_pos( chr_t *chr, long x, long y, long dx, long dy );
bool_t	can_move_chr_sub( chr_t *chr, long x, long y );
bool_t	can_move_chr_towner( chr_t *chr, long d );
void	die_chr(
	chr_t *chr,
	bool_t flg_msg, bool_t flg_add_exp, bool_t flg_chk_game_over
);
bool_t	chk_save_life( chr_t *chr );
bool_t	steal( chr_t *chr, chr_t *trgt );
bool_t	mbr_steal_mbr( mbr_t *mbr, chr_t *trgt, char *item_name );
bool_t	mbr_steal_mnstr( mbr_t *mbr, chr_t *trgt, char *item_name );
bool_t	mnstr_steal_mbr( mnstr_t *mnstr, chr_t *trgt, char *item_name );
bool_t	mnstr_steal_mnstr( mnstr_t *mnstr, chr_t *trgt, char *item_name );
void	act_chr_auto_door( chr_t *chr, long x, long y );
bool_t	chr_open_door( chr_t *chr, long dr_n );
bool_t	chr_close_door( chr_t *chr, long dr_n );
bool_t	chr_jam_door( chr_t *chr, long dr_n );
bool_t	chr_disarm_door( chr_t *chr, long dr_n );
void	chr_peep_door( chr_t *chr, long dr_n );
void	chr_chk_door( chr_t *chr, long dr_n );
bool_t	chr_disarm_trap( chr_t *chr, trap_t *trap );
bool_t	chr_disarm_trap_abl(
	chr_t *chr, trap_t *trap,
	abl_kind_t abl_main, abl_kind_t abl_sub
);
bool_t	chr_chk_trap( chr_t *chr, trap_t *trap );
bool_t	chr_open_item( chr_t *chr, item_t *item );
bool_t	chr_disarm_item( chr_t *chr, item_t *item );
bool_t	chr_disarm_item_abl(
	chr_t *chr, item_t *item,
	abl_kind_t abl_main, abl_kind_t abl_sub
);
void	chr_chk_item( chr_t *chr, item_t *item );
void	chr_srch_obj( chr_t *chr );
bool_t	chr_srch_obj_sub( chr_t *chr, long x, long y );
void	chr_srch_auto_off( chr_t *chr );
void	chr_enter_door( chr_t *chr, door_t *dr );
void	move_chr_trgt( chr_t *chr );
long	calc_chr_dx( chr_t *chr1, chr_t *chr2 );
long	calc_chr_dy( chr_t *chr1, chr_t *chr2 );
long	get_trgt_range( chr_t *chr );
long	get_chr_left( long x, long dx );
long	get_chr_top( long y, long dy );
long	get_chr_right( long x, long dx );
long	get_chr_bottom( long y, long dy );
bool_t	chk_auto_mark_cont( chr_t *chr );
void	clr_chr_trgt_act( chr_t *chr, bool_t flg_force );
void	clr_chr_trgt( chr_t *chr );
bool_t	set_chr_act(
	chr_t *chr, act_kind_t kind,
	void *p, void *p2,
	long n, long n2
);
void	clr_chr_act( chr_t *chr );
void	lost_trgt( void *p );
void	mark_mbr( chr_t *chr, mbr_t *mbr, dist_t dist );
void	mark_mnstr_no_regist( chr_t *chr, mnstr_t *mnstr, dist_t dist );
void	mark_mnstr_dflt( chr_t *chr, mnstr_t *mnstr );
void	mark_mnstr( chr_t *chr, mnstr_t *mnstr, dist_t dist );
void	mark_mnstr_null_no_regist( chr_t *chr, long x, long y, dist_t dist );
void	mark_mnstr_null_dflt( chr_t *chr, long x, long y );
void	mark_mnstr_null( chr_t *chr, long x, long y, dist_t dist );
void	mark_item( chr_t *chr, item_t *item, dist_t dist );
void	mark_door( chr_t *chr, door_t *dr, dist_t dist );
void	mark_trap( chr_t *chr, trap_t *trap, dist_t dist );
void	mark_discount_queue( chr_t *chr );
void	mark_discount_queue_sub( chr_t *chr );
void	mark_square( chr_t *chr );
void	mark_pos( chr_t *chr, long x, long y, dist_t dist );
void	stop_zapping( chr_t *chr );
void	chr_srch_begin( chr_t *chr );
void	chr_srch_end( chr_t *chr );
bool_t	chk_infra_vision( chr_t *chr );
bool_t	chr_light_up( chr_t *chr, bool_t flg_on );
void	put_chr( chr_t *chr, long x, long y );
void	exp_chr(
	chr_t *chr,
	long exp,
	bool_t flg_set_max,
	bool_t flg_print_exp,
	bool_t flg_print_lev
);
bool_t	exp_mbr(
	mbr_t *mbr,
	long exp,
	bool_t flg_set_max,
	bool_t flg_print_lev,
	bool_t flg_draw_lev
);
bool_t	exp_mbr_skill(
	mbr_t *mbr,
	long exp,
	bool_t flg_set_max,
	bool_t flg_print_lev,
	bool_t flg_draw_lev
);
long	exp_mbr_skill_1(
	mbr_t *mbr,
	long exp,
	skill_kind_t kind,
	bool_t flg_set_max
);
bool_t	exp_mnstr(
	mnstr_t *mnstr,
	long exp,
	bool_t flg_set_max,
	bool_t flg_print_lev,
	bool_t flg_draw_lev
);
bool_t	chk_lev_up(
	chr_t *chr, bool_t flg_set_max,
	bool_t flg_print, bool_t flg_draw
);
bool_t	set_lev_up(
	chr_t *chr,
	abl_kind_t abl,
	long add,
	bool_t flg_set_max,
	bool_t flg_print );
void	set_modifier( chr_t *chr );
void	set_modifier_fx_data_equip( chr_t *chr );
void	set_modifier_fx_data_fx( chr_t *chr );
void	set_modifier_fx_data_song( chr_t *chr );
bool_t	calc_modifier_equip( chr_t *chr );
bool_t	reset_modifier( modifier_t *m );
bool_t	get_modifier_equip( chr_t *chr, modifier_t *m );
bool_t	set_modifier_equip( chr_t *chr, modifier_t *m );
bool_t	get_modifier_fx( chr_t *chr, modifier_t *m );
bool_t	set_modifier_fx( chr_t *chr, modifier_t *m );
bool_t	chk_resi_stat( chr_t *chr, flg_stat_t stat );
bool_t	chk_resi_stat_or( chr_t *chr, flg_stat_t stat );
rate_t	set_move_rate( chr_t *chr );
rate_t	get_move_rate( chr_t *chr );
const char	*get_sex_name( mnstr_kind_t kind, sex_t sex );
char	*get_abl_name( abl_kind_t kind );
abl_kind_t	get_sub_abl( abl_kind_t abl_main );
long	calc_lev_to_exp( long lev, abl_kind_t abl );
long	calc_need_exp( long lev, abl_kind_t abl );
long	get_exp( chr_t *chr, abl_kind_t abl );
long	get_lev( chr_t *chr, abl_kind_t abl );
long	get_lev_max( chr_t *chr, abl_kind_t abl );
rate_t	get_resi( chr_t *chr, resi_kind_t resi );
rate_t	get_resi_max( chr_t *chr, resi_kind_t resi );
const char	*get_resi_name( resi_kind_t kind );
bool_t	chk_modified_lev( chr_t *chr, abl_kind_t abl );
long	calc_abl_to_val( chr_t *chr, abl_kind_t abl );
long	calc_lev_to_val( long lev, abl_kind_t abl );
long	calc_max_hp( chr_t *chr );
long	calc_max_mp( chr_t *chr );
long	calc_resi( rate_t resi, long n );
long	get_generalist_lev( chr_t *chr );
long	get_specialist_lev( chr_t *chr );
abl_kind_t	get_specialist_abl( chr_t *chr );
chr_dir_idx_t	get_chr_dir_idx( chr_t *chr );
void	sort_all_chr( bool_t flg_gui );
void	sort_chr( chr_t *head, chr_t *chr, bool_t flg_gui );
chr_t	*get_sort_chr_head( void );
long	add_hp( chr_t *chr, long n, bool_t flg_vfx, bool_t flg_force );
long	add_mp( chr_t *chr, long n, bool_t flg_vfx );
rate_t	add_resi( chr_t *chr, resi_kind_t kind, rate_t n, bool_t flg_vfx );
gold_t	get_chr_gold( chr_t *chr );
gold_t	add_chr_gold( chr_t *chr, gold_t gold );
rate_t	use_contribution_rate( chr_t *chr );
bool_t	use_contribution( chr_t *chr, rate_t rate );
bool_t	chk_pay_contribution( chr_t *chr, gold_t gold );
bool_t	pay_contribution( chr_t *chr, gold_t gold );
void	curs_attrset_chr( chr_t *chr, long n, bool_t flg_crtcl );
square_t	*get_square( chr_t *chr );
void	set_square( chr_t *chr, square_t *sq );
char	*get_trgt_name( trgt_t *trgt );
trgt_kind_t	get_trgt_kind_from_chr( chr_t *chr );
chr_kind_t	get_chr_kind_from_trgt( trgt_t *trgt );
void	copy_chr( chr_t *dst, chr_t *src );
bool_t	cmp_chr( chr_t *p1, chr_t *p2 );
rate_t	calc_rate_equip(
	chr_t *chr, abl_kind_t abl_main, abl_kind_t abl_sub
);
rate_t	calc_rate_equip_flg_msg(
	chr_t *chr, abl_kind_t abl_main, abl_kind_t abl_sub,
	bool_t flg_msg
);
bool_t	chk_find_chr( chr_t *p1, chr_t *p2 );
void	clr_all_chr_flg_blast( void );
bool_t	is_mbr( chr_t *p );
bool_t	is_mnstr( chr_t *p );
bool_t	is_mnstr_or_pet( chr_t *p );
bool_t	is_pet( chr_t *p );
void	set_chr_id( chr_t *chr, chr_t **ls, long max );
long	calc_chr_id1( char *name );
long	calc_chr_id2( char *name );
bool_t	roll(
	chr_t *p1, abl_kind_t abl_m1, abl_kind_t abl_s1,
	chr_t *p2, abl_kind_t abl_m2, abl_kind_t abl_s2
);
bool_t	chr_roll(
	chr_t *chr, abl_kind_t abl_main, abl_kind_t abl_sub,
	long difficulty
);
bool_t	resi_roll(
	chr_t *o_p, abl_kind_t o_abl,
	chr_t *d_p, resi_kind_t d_resi
);
long	roll_dice( long n, bool_t flg_add );
void	check_memory_chr_c( void );

#ifdef __cplusplus
}
#endif
