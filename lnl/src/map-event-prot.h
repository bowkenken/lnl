/* map-event.c */

#ifdef __cplusplus
extern "C" {
#endif

void	reset_map_event( void );
void	reset_map_event_func( void );
void	reset_map_event_pos( void );
void	chk_map_event( long x, long y );
void	exec_map_event( char mnr, long x, long y );
void	set_map_event_tab( map_event_tab_t *tab );
map_event_func_t	set_map_event_func(
	char mnr, map_event_func_t func
);
map_event_func_t	get_map_event_func( char mnr );
void	set_map_event_pos( char mnr, long x, long y );
pos_t	get_map_event_pos( char mnr );
long	cv_face_to_map_event_n( char mnr );
void	check_memory_map_event_c( void );

#ifdef __cplusplus
}
#endif
