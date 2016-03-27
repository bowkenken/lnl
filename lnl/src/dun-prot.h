/* dun.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_dun( void );
void	init_crsr_ptn( void );
void	reset_static_dun( void );
long	get_crsr_ptn_max_n( void );
long	set_crsr_ptn_max_n( long n );
long	get_main_crsr_ptn_n( void );
long	set_main_crsr_ptn_n( long n );
long	get_sub_crsr_ptn_n( void );
long	set_sub_crsr_ptn_n( long n );
void	reset_crsr_ptn( void );
void	reset_dun( bool_t flg_wall );
crsr_ptn_t	*get_main_crsr_ptn( void );
crsr_ptn_t	*get_sub_crsr_ptn( void );
bool_t	set_crsr_ptn( crsr_ptn_t *dst, crsr_ptn_t *src );
void	up_dun_town( void );
void	up_dun( long d );
void	up_dun_msg( void );
void	enter_last_boss_dun( void );
void	reset_all_save( bool_t flg_appear );
void	reset_all( bool_t flg_appear );
void	make_dun( void );
void	make_dun_last_boss( void );
void	make_fence( void );
void	make_area( room_ptn_t *ptn, area_t max_n, long x, long y );
bool_t	make_area_boss( room_ptn_t *ptn, area_t max_n, long x, long y );
bool_t	make_area_last_boss( room_ptn_t *ptn, area_t max_n, long x, long y );
bool_t	chk_boss_dun_lev( long dun_lev );
void	set_room( room_ptn_t *room, area_t n, long x, long y, long flg_rev );
bool_t	chk_lighted_room( void );
bool_t	chk_lighted_path( void );
void	make_path( long area_x, long area_y );
long	chk_extend_path_h( long ax, long ay, long d );
long	chk_extend_path_v( long ax, long ay, long d );
bool_t	chk_room( long ax, long ay );
void	finish_path( long mx, long my, long dx, long dy );
bool_t	chk_finish_path( long mx, long my, long dx, long dy );
void	connect_room( long ax, long ay, long dx, long dy );
void	make_door_path( long mx, long my, long dx, long dy );
void	make_door_room( long mx, long my );
door_t	*make_door( long bx, long by, long ex, long ey, char mnr );
bool_t	chk_face_window( long bx, long by, long ex, long ey );
door_t	*make_door_flg(
	long bx, long by,
	long ex, long ey,
	char mnr, flg_door_t flg
);
void	set_face_door( long dr_n );
bool_t	chk_find_door( long dr_n );
bool_t	break_door( chr_t *chr, long dr_n );
void	get_near_pos_door( pos_t *pos, door_t *dr, chr_t *chr );
bool_t	make_hide_cross_path( long ax, long ay );
bool_t	chk_cross_path( long mx, long my );
void	hide_cross_path( long mx, long my );
void	make_stairs_randm( char face );
void	make_stairs( long x, long y, char face );
bool_t	make_stairs_sub( long x, long y, char face );
bool_t	set_statue( long x, long y, long dun_lev, bool_t flg_self );
void	set_map_total( long x, long y, long dx, long dy );
void	set_map_total_water( long x, long y, long dx, long dy );
void	set_map_total_bg( long x, long y, long dx, long dy );
void	set_face_from_map_obj(
	bool_t flg_chk_find,
	long x, long y, char *mjr, char *mnr,
	bool_t flg_gui
);
void	set_map_total_crsr_attr(
	pos_t *crsr, crsr_ptn_t *ptn, long x, long y, long dx, long dy
);
void	set_map_total_obj( long x, long y, long dx, long dy );
void	set_map_total_square( long x, long y, long dx, long dy );
void	set_map_total_square_n(
	long mbr_n, long x, long y, long dx, long dy
);
void	set_map_total_chr( long x, long y, long dx, long dy );
void	set_map_total_chr_1( long x, long y );
void	set_map_total_crsr_ptn(
	pos_t *crsr, crsr_ptn_t *ptn,
	long x, long y, long dx, long dy
);
curs_attr_n_t	get_curs_attr_n_map_obj(
	char mjr, char mnr, flg_map_t flg
);
void	line_path( long x1, long y1, long x2, long y2, sect_t sect );
void	put_path( long x, long y, long dx, long dy, sect_t sect );
bool_t	open_door( long n );
bool_t	close_door( long n );
bool_t	jam_door( long n );
bool_t	disarm_door( long n );
bool_t	srch_door( long n );
void	detect_door( long x, long y, long r );
void	find_obj( long x, long y );
void	find_obj_fill( long x, long y );
void	find_obj_fill_field( long x, long y );
void	on_light_area( long x, long y, bool_t flg_find );
void	off_light_area( long x, long y, bool_t flg_find );
void	turn_light_area( long x, long y, bool_t flg_on, bool_t flg_find );
void	turn_light_field(
	long x, long y, sect_t sect, bool_t flg_on, bool_t flg_find
);
void	turn_light_door( door_t *dr, bool_t flg_on, bool_t flg_find );
bool_t	turn_light_obj( long x, long y, bool_t flg_on );
bool_t	turn_light_chr( long x, long y, bool_t flg_on );
long	calc_light_depth( long x, long y );
bool_t	chk_find( pos_t *pos1, pos_t *pos2 );
bool_t	chk_find_pos( long x, long y );
dun_t	*get_dun( void );
long	get_dun_lev( void );
door_t	*get_door( long x, long y );
door_t	*get_door_nearest( long x, long y, act_kind_t act_kind );
door_t	*get_door_near( long x, long y, act_kind_t act_kind );
door_t	*get_door_disperse( mbr_t *mbr, act_kind_t act_kind );
door_t	*get_door_randm( long x, long y, act_kind_t act_kind );
door_t	*get_door_towner( long x, long y, long r );
void	set_door_pos_chk_find(
	door_t *p, long x, long y, pos_t *pos, long *dx, long *dy
);
bool_t	chk_mark_door( door_t *p, act_kind_t act_kind );
bool_t	up_stairs( void );
bool_t	down_stairs( void );
bool_t	down_stairs_last_boss( void );
bool_t	chk_stairs( long face );
void	scroll_map( long x, long y );
bool_t	srch_map_obj( char face_mjr, char face_mnr, long *x, long *y );
bool_t	is_map_wall( long x, long y );
bool_t	clip_pos( long x, long y );
bool_t	clip_x( long n );
bool_t	clip_y( long n );
bool_t	clip_draw_pos( long x, long y );
bool_t	clip_draw_x( long n );
bool_t	clip_draw_y( long n );
bool_t	chk_rate_room( long dun_lev );
bool_t	chk_rate_door_open( long dun_lev );
bool_t	chk_rate_door_jammed( long dun_lev );
bool_t	chk_rate_door_broken( long dun_lev );
bool_t	chk_rate_door_secret( long dun_lev );
bool_t	chk_rate_hide_cross_path( long dun_lev );
char	get_chr_mjr_crsr( void );
char	get_chr_mnr_crsr( void );
char	get_chr_crsr( bool_t flg_mjr );
long	chk_nest_flg_dun( void );
bool_t	save_dun( void );
void	check_memory_dun_c( void );

#ifdef __cplusplus
}
#endif
