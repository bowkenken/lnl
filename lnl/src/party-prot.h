/* party.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_party( void );
void	reset_static_party( void );
void	init_party_dflt( void );
void	init_party_debug( void );
item_t	*init_mbr_item(
	mbr_t *mbr, item_kind_t kind, item_kind_dat_t *sub_kind,
	bool_t flg_ident, bool_t curse, bool_t flg_eq
);
void	init_mbr_formation( void );
void	new_mbr_reset( mbr_t *mbr );
void	new_mbr(
	mbr_t *mbr, char *name, char face,
	race_t race, sex_t sex, long class_n, long ls_mbr_n
);
bool_t	reset_mbr_resi( mbr_t *mbr );
void	reset_mbr_dir( void );
void	reset_square_mbr_ind_pos( void );
void	set_square_mbr_ind_pos( long mbr_n, long x, long y );
void	get_square_mbr_abs_pos( long mbr_n, long *x, long *y );
void	get_square_mbr_map_pos( long mbr_n, long *x, long *y );
void	appear_party_auto( void );
void	appear_party( void );
bool_t	appear_party_sub_randm( void );
bool_t	appear_party_sub_srch( void );
void	appear_party_sub_force( void );
bool_t	appear_party_short( long bx, long by );
bool_t	appear_party_sub_area( long bx, long by );
void	appear_party_last_boss( void );
void	appear_party_map_event( char mnr );
long	get_party_dun_max_lev( void );
void	scroll_center_appear_party( void );
void	clr_map_all_mbr( void );
void	set_map_all_mbr( void );
void	move_all_mbr_trgt( void );
void	move_phase_all_mbr( void );
void	act_phase_all_mbr( void );
void	act_phase_party( void );
bool_t	chk_party_no_mbr( bool_t flg_enter_bar );
void	chk_trap_party( void );
bool_t	chk_auto_mnstr( mbr_t *mbr, long x1, long y1, long x2, long y2 );
bool_t	chk_auto_door_mbr( mbr_t *mbr, long x1, long y1, long x2, long y2 );
bool_t	chk_auto_door_mbr_sub( mbr_t *mbr, long x, long y );
void	die_mbr( mbr_t *mbr, bool_t flg_msg, bool_t flg_chk_game_over );
bool_t	chk_can_act_mbr( mbr_t *p );
bool_t	set_mbr_act_auto_mnstr( mbr_t *mbr, long x, long y );
void	mbr_peep_door( mbr_t *mbr, long dr_n );
void	clr_party_act( void );
void	join_mbr( long ls_mbr_n, long mbr_n );
void	not_join_mbr( long ls_mbr_n, long mbr_n );
void	collect_gold( mbr_t *mbr );
void	divide_gold( void );
void	give_gold( mbr_t *mbr_from, mbr_t *mbr_to, gold_t gold );
gold_t	get_party_gold( void );
void	add_party_gold( gold_t gold );
gold_t	sub_party_gold( gold_t gold );
void	exp_party( long exp, bool_t flg_set_max, bool_t flg_draw );
long	get_mbr_race_exp( mbr_t *mbr, long exp, abl_kind_t abl );
void	remove_mbr( mbr_t *mbr );
mbr_t	*get_mbr_nearest( long x, long y );
mbr_t	*get_mbr_near( long x, long y );
mbr_t	*get_mbr_disperse( mbr_t *mbr );
mbr_t	*get_mbr_randm( long x, long y );
mbr_t	*get_mbr_stagger( mbr_t *mbr );
mbr_t	*get_mbr_hp_min( void );
mbr_t	*get_mbr_hp_max( void );
mbr_t	*get_mbr_mp_min( void );
mbr_t	*get_mbr_mp_max( void );
mbr_t	*get_mbr_hp_mp_min_max( bool_t flg_hp, long min_max );
bool_t	chk_already_mark( void *p, mbr_t *mbr );
char	*get_race_str( race_t *race );
char	*get_race_str_main( race_t *race );
char	*get_race_str_sub( race_t *race );
char	*get_race_name( race_t *race );
bool_t	chk_not_exist_all_mbr( void );
mbr_t	**get_ls_mbr( void );
mbr_t	*get_ls_mbr_tail( void );
party_t	*get_party( void );
long	get_mbr_n( long x, long y );
mbr_t	*get_mbr( long x, long y );
flg_party_t	get_flg_party( void );
flg_party_t	set_flg_party( flg_party_t flg );
long	next_mbr( long mbr_n, long add );
long	next_ls_mbr( long ls_mbr_n, long add );
class_t	*get_class_tab( void );
bool_t	remove_class( long class_n );
bool_t	cmp_class( class_t *org, class_t *dst );
void	arrange_class_1( long class_n, long d );
void	arrange_class( long class_n, long d );
square_t	*get_square_mbr( void );
void	set_square_mbr( square_t *sq );
void	get_square_pos( long *x, long *y, bool_t flg_pre );
void	set_square_pos( long x, long y, bool_t flg_pre );
void	unset_square_pos( void );
void	check_memory_party_c( void );

#ifdef __cplusplus
}
#endif
