/* turn.c */

#ifdef __cplusplus
extern "C" {
#endif

long	init_turn();
void	reset_static_turn( void );
long	reset_turn( long n );
long	add_turn( long n );
long	inc_turn( void );
long	set_turn( long n );
long	get_turn( void );
long	reset_day( void );
long	inc_day( void );
long	set_game_date( long year, long month, long day );
long	set_game_day( long day );
long	get_game_day( void );
bool_t	chk_day( void );
bool_t	chk_morning( void );
bool_t	chk_evening( void );
bool_t	chk_night( void );
rate_t	get_morning_rate( void );
rate_t	get_evening_rate( void );
char	*get_calendar_str( void );
char	*get_stat_time_str( void );
char	*get_day_of_week_name( void );
day_of_week_t	get_day_of_week( void );
void	check_memory_turn_c( void );

#ifdef __cplusplus
}
#endif
