/* scene.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_scene( void );
void	reset_static_scene( void );
void	chk_change_scene( void );
void	chk_change_scene_town( void );
void	chk_change_scene_dun( void );
void	chk_change_scene_battle( void );
void	chk_change_scene_battle_boss( void );
bool_t	scene_srch_boss( void );
bool_t	scene_srch_battle( void );
scene_n_t	change_scene( scene_n_t n );
scene_n_t	change_scene_gui( scene_n_t n );
scene_n_t	change_scene_sub( scene_n_t n, bool_t flg_gui );
scene_n_t	get_scene( void );
last_scene_n_t	change_last_scene( last_scene_n_t n );
last_scene_n_t	change_last_scene_gui( last_scene_n_t n );
last_scene_n_t	change_last_scene_sub( last_scene_n_t n, bool_t flg_gui );
last_scene_n_t	get_last_scene( void );
bool_t	chk_scene_group( scene_group_n_t group_n );
void	check_memory_scene_c( void );

#ifdef __cplusplus
}
#endif
