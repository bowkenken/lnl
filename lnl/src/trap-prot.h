/* trap.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_trap( void );
void	reset_static_trap( void );
void	reset_trap( void );
trap_t	*make_trap( long x, long y, long dun_lev );
trap_t	*make_trap_std( trap_kind_t kind, long x, long y, long dun_lev );
bool_t	make_trap_alloc( long dun_lev, trap_t *trap, long tab_n );
bool_t	set_trap( long x, long y, trap_t *trap );
bool_t	set_trap_face_mnr( trap_t *trap );
void	make_chk_trap_room( long dun_lev );
void	make_trap_room( long area_x, long area_y, long dun_lev );
void	chk_trap_chest( item_t *chest, chr_t *chr, rate_t rate );
void	chk_trap( chr_t *chr, chr_t *thief );
void	find_trap( trap_t *trap );
void	caught_trap( trap_t *trap, chr_t *chr );
void	set_trap_arw_pos( chr_t *chr, long *x, long *y );
void	caught_trap_pit( chr_t *chr );
void	caught_trap_chute( chr_t *chr );
void	disarm_trap( trap_t *p );
void	detect_trap( long x, long y, long r );
bool_t	chk_through_trap( long x, long y );
bool_t	chk_map_sanctuary( long x, long y );
long	calc_trap_lev( trap_t *p );
void	ins_ls_trap( trap_t *ls, trap_t *p );
trap_t	*alloc_trap( void );
void	free_trap_chest( item_t *chest );
void	free_trap( trap_t *p );
trap_t	*get_trap_free_next( void );
trap_t	*get_dun_trap_asgn( void );
trap_t	*get_trap( long x, long y );
trap_t	*get_trap_nearest( chr_t *chr, act_kind_t act_kind );
trap_t	*get_trap_near( chr_t *chr, act_kind_t act_kind );
trap_t	*get_trap_disperse( chr_t *chr, act_kind_t act_kind );
trap_t	*get_trap_randm( chr_t *chr, act_kind_t act_kind );
trap_t	*get_trap_identified( chr_t *chr, act_kind_t act_kind );
trap_t	*get_trap_un_identified( chr_t *chr, act_kind_t act_kind );
trap_t	*get_trap_identified_sub(
	chr_t *chr, act_kind_t act_kind,
	bool_t flg_identified
);
bool_t	chk_get_trap( chr_t *chr, act_kind_t act_kind, trap_t *p );
bool_t	chk_mark_trap( trap_t *p, act_kind_t act_kind );
trap_tab_t	*get_trap_tab( trap_kind_t kind );
long	get_trap_tab_n( trap_kind_t kind );
void	check_memory_trap_c( void );

#ifdef __cplusplus
}
#endif
