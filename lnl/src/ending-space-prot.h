/* ending-space.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_space( void );
long	add_z_speed_space( long azv );
void	move_space( void );
bool_t	draw_space( bool_t flg_draw_staff_roll );
void	draw_star( long x, long y, long z );
void	wipe_star( long x, long y );
void	draw_staff_roll( void );
void	draw_the_end( void );
void	draw_staff_roll_line( long x, long y, const char *str );
long	get_star_n( void );
void	check_memory_ending_space_c( void );

#ifdef __cplusplus
}
#endif
