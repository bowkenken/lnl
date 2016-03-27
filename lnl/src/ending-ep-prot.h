/* ending-ep.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_ending( void );
void	init_epilogue( void );
bool_t	draw_ending( void );
void	set_flg_skip_scene_ending( bool_t flg );
bool_t	get_flg_skip_scene_ending( void );
bool_t	draw_epilogue( void );
void	draw_epilogue_story( long frame );
void	check_memory_ending_ep_c( void );

#ifdef __cplusplus
}
#endif
