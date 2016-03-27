/* mnstr.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_mnstr( void );
void	init_mnstr_lev_tab( mnstr_lev_tab_t stage[], long *n );
void	reset_static_mnstr( void );
void	reset_mnstr( void );
void	new_mnstr( mnstr_t *mnstr );
mnstr_t	*make_mnstr_rand( long x, long y, bool_t flg_fix_pos, long dun_lev );
mnstr_t	*make_mnstr(
	long x, long y, bool_t flg_fix_pos,
	long dun_lev,
	mnstr_kind_t mnstr_kind
);
mnstr_t	*make_mnstr_alloc(
	mnstr_t *p,
	long x, long y, bool_t flg_fix_pos,
	long dun_lev,
	mnstr_kind_t mnstr_kind
);
bool_t	make_mnstr_special( mnstr_t *p, long dun_lev );
mnstr_t	*make_npc_rand( long x, long y, long dun_lev );
void	move_phase_all_mnstr( void );
void	act_phase_all_mnstr( void );
void	dismissal_phase_all_mnstr( void );
bool_t	chk_can_act_mnstr( mnstr_t *p );
void	set_act_mnstr( mnstr_t *p );
mbr_t	*mnstr_mark_mbr_std( mnstr_t *p );
mbr_t	*mnstr_mark_mbr_cubus( mnstr_t *p, sex_t sex );
mbr_t	*mnstr_mark_mbr_common( mnstr_t *p, sex_t sex );
mbr_t	*mnstr_mark_mbr_adjoin( mnstr_t *p );
bool_t	mnstr_move_or_atack_std( mnstr_t *p );
void	set_enemy_mnstr_group( chr_t *o_p, chr_t *d_p );
void	inc_turn_all_mnstr( void );
bool_t	increase_mnstr( mnstr_t *p );
bool_t	chk_auto_door_mnstr( mnstr_t *p, long x1, long y1, long x2, long y2 );
bool_t	chk_auto_door_mnstr_open( mnstr_t *p, long x, long y );
bool_t	chk_auto_door_mnstr_break( mnstr_t *p, long x, long y );
void	set_flg_find_all_mnstr( void );
bool_t	set_flg_find_mnstr( mnstr_t *p );
bool_t	chk_flg_work_find_mbr( mnstr_t *p );
void	set_flg_work_find_mbr( mnstr_t *p, bool_t flg );
void	chk_boss_find_mbr( mnstr_t *p );
void	chk_trap_all_mnstr( void );
void	die_mnstr_drop_item( mnstr_t *p );
void	die_mnstr( mnstr_t *p, bool_t flg_msg );
bool_t	chk_die_boss( mnstr_t *p );
bool_t	is_boss( mnstr_t *p );
bool_t	is_last_boss( mnstr_t *p );
bool_t	is_xx( mnstr_t *p );
void	die_boss( mnstr_t *m );
void	garbage_collection_all_mnstr( void );
void	mnstr_drop_gold( mnstr_t *p );
void	mnstr_drop_bone( mnstr_t *p );
void	mnstr_drop_item( mnstr_t *p );
void	mnstr_drop_key_item( mnstr_t *p );
void	set_find_all_mnstr( void );
void	print_ls_mnstr( void );
mnstr_kind_t	get_npc_kind_randm( void );
char	*get_mnstr_mjr_name( char mjr );
char	*get_mnstr_name( mnstr_kind_t mnstr_kind );
mnstr_tab_t	*get_mnstr_tab( mnstr_kind_t mnstr_kind, long dun_lev );
mnstr_tab_t	*get_mnstr_tab_rand( long dun_lev );
mnstr_tab_t	*get_mnstr_tab_rand_dun_lev( long dun_lev );
mnstr_tab_t	*get_mnstr_tab_rand_sub(
	long dun_lev, bool_t flg_no_chk_max
);
mnstr_tab_t	*get_mnstr_tab_friendly( void );
mnstr_tab_t	*get_towner_tab_rand( void );
long	get_mnstr_lev_tab_max( void );
mnstr_lev_tab_t	*get_mnstr_lev_tab( mnstr_kind_t mnstr_kind, long dun_lev );
void	ins_ls_mnstr( mnstr_t *ls, mnstr_t *p );
long	calc_mnstr_exp( mnstr_kind_t mnstr_kind, long dun_lev );
long	calc_mnstr_exp_sub( mnstr_kind_t mnstr_kind, long dun_lev );
long	calc_mnstr_abl_lev( long dun_lev, abl_kind_t k, mnstr_tab_t *tab );
rate_t	calc_mnstr_group_rate( long group_n );
gold_t	calc_mnstr_gold( long dun_lev, rate_t rate );
bool_t	can_move_mnstr_tab( mnstr_tab_t *tab, long x, long y );
mnstr_t	*get_mnstr( long x, long y );
mnstr_t	*get_mnstr_nearest( long x, long y );
mnstr_t	*get_mnstr_near( long x, long y );
mnstr_t	*get_mnstr_disperse( mbr_t *mbr );
mnstr_t	*get_mnstr_hp_min( long x, long y );
mnstr_t	*get_mnstr_hp_max( long x, long y );
mnstr_t	*get_mnstr_mp_min( long x, long y );
mnstr_t	*get_mnstr_mp_max( long x, long y );
mnstr_t	*get_mnstr_hp_mp_min_max(
	long x, long y, bool_t flg_hp, long min_max
);
mnstr_t	*get_mnstr_randm( long x, long y );
bool_t	already_mark_mnstr( mnstr_t *mnstr, mbr_t *mbr );
mnstr_t	*get_mnstr_randm2( long x, long y );
chr_t	*get_mnstr_friend( mnstr_t *p, long x, long y );
mnstr_kind_t	get_mnstr_kind_from_face( char mjr, char mnr );
mnstr_t	*get_last_boss( last_boss_kind_t kind );
mnstr_t	*get_mnstr_used( void );
void	check_memory_mnstr_c( void );

#ifdef __cplusplus
}
#endif
