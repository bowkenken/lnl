/* last-boss.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_last_boss( void );
void	init_last_boss_parts( last_boss_parts_t *parts );
void	reset_static_last_boss( void );
bool_t	chk_last_boss_can_spell( spell_kind_t spell_kind );
bool_t	chk_last_boss_demo( void );
bool_t	chk_draw_last_boss( void );
void	draw_last_boss( void );
void	draw_words_exel( const char *str );
void	draw_words_exeler( const char *str );
void	draw_words_xex( const char *str );
void	draw_words_xx( const char *str );
void	draw_exel( void );
void	draw_exel_enter( void );
void	draw_exel_hyper( void );
void	draw_exeler( void );
void	draw_exeler_enter( void );
void	draw_exeler_hyper( void );
void	draw_xex( void );
void	set_pos_last_boss( mnstr_t *p, long x, long y );
void	open_last_boss_gate( void );
void	event_begin_last_boss( long x, long y );
void	scroll_last_boss( void );
void	draw_xx_enter( void );
void	set_xx_enter( void );
bool_t	draw_xex_breakdown( void );
bool_t	chk_xex_breakdown_field( long x, long y );
void	draw_xex_breakdown_line( long y );
void	draw_xex_breakdown_all_field( void );
void	draw_xex_earthquake( pos_t *draw, pos_t base_draw );
void	draw_xex_lava( long y );
void	chk_die_all_last_boss( void );
void	chk_die_last_boss( last_boss_kind_t kind );
void	die_all_last_boss( void );
bool_t	chk_xx_pos( long x, long y );
bool_t	chk_xx_range( void );
void	set_last_boss_ptn( void );
bool_t	get_open_xx_jaw( void );
void	set_open_xx_jaw( bool_t flg_open_jaw );
bool_t	get_slap_xx_arm_left( void );
bool_t	get_slap_xx_arm_right( void );
void	set_slap_xx_arm_left( bool_t flg_slap_arm );
void	set_slap_xx_arm_right( bool_t flg_slap_arm );
last_boss_joint_t	*get_joint( last_boss_parts_t *parts, char mnr );
void	get_attack_skull_pos( pos_t *p );
void	get_attack_jaw_pos( pos_t *p );
void	set_last_boss_parts(
	last_boss_ptn_t *ptn,
	last_boss_parts_t *parts,
	long x, long y
);
void	reset_last_boss_ptn( last_boss_ptn_t *ptn );
void	set_map_total_last_boss_bg( long x, long y, long dx, long dy );
void	set_map_total_last_boss_fg( long x, long y, long dx, long dy );
void	set_map_total_last_boss(
	last_boss_ptn_t *ptn,
	long x, long y, long dx, long dy
);
last_boss_ptn_t	*get_last_boss_ptn_bg( void );
last_boss_ptn_t	*get_last_boss_ptn_fg( void );
pos_t	get_xx_pos( void );
void	wait_frame_gui( long frame );
void	act_mnstr_xx( mnstr_t *p );
void	play_sound_xx( xx_act_kind_t kind );
void	xx_spell( mnstr_t *p, spell_kind_t kind );
void	xx_act_heat( mnstr_t *p );
void	xx_act_heat_draw( mnstr_t *p );
void	xx_act_cold( mnstr_t *p );
void	xx_act_cold_draw( mnstr_t *p );
pos_t	*get_xx_laser_dxy( void );
void	xx_act_mind( mnstr_t *p );
void	xx_act_mind_draw( mnstr_t *p );
void	xx_act_acid( mnstr_t *p );
void	xx_act_acid_draw( mnstr_t *p );
void	xx_act_rotation( mnstr_t *p );
void	xx_act_rotation_draw( mnstr_t *p );
void	xx_act_whirl( mnstr_t *p );
void	xx_act_whirl_draw( mnstr_t *p );
void	xx_act_fan( mnstr_t *p );
void	xx_act_fan_draw( mnstr_t *p );
void	xx_act_slap( mnstr_t *p );
void	xx_act_slap_draw( mnstr_t *p );
void	check_memory_last_boss_c( void );

#ifdef __cplusplus
}
#endif
