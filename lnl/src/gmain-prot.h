/* gmain.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_game( void );
void	reset_static( void );
void	reset_static_game_main( void );
void	game_main( void );
void	game_over( void );
void	ending( void );
void	init_arg( void );
void	chk_arg( int argc, char **argv );
bool_t	chk_opt_num(
	const char *optarg, long *pn, bool_t flg_err_exit
);
bool_t	chk_opt_flg(
	const char *optarg, bool_t *flg, bool_t flg_err_exit
);
void	overwrite_arg();
void	usage( FILE *fp );
void	exit_game( long code );
void	close_game( long code );
void	about_game( bool_t flg_init );
void	version( FILE *fp );
void	child_ps( void );
void	init_signal( void );
void	signal_handler( int sig );
void	init_scrn( void );
void	reset_scrn( void );
void	ena_scrn( bool_t flg_initscr );
void	dis_scrn( void );
void	init_term( void );
bool_t	chk_term( void );
void	ena_term( void );
void	dis_term( void );
void	set_key_wait( void );
void	clr_key_wait( void );
void	child_ps_unix( void );
void	child_ps_dos( void );
void	init_term_unix( void );
bool_t	chk_term_unix( void );
void	ena_term_unix( void );
void	dis_term_unix( void );
void	set_key_wait_unix( void );
void	clr_key_wait_unix( void );
void	set_key_wait_vtime( long wait_vtime );
void	init_term_dos( void );
bool_t	chk_term_dos( void );
void	ena_term_dos( void );
void	dis_term_dos( void );
void	set_key_wait_dos( void );
void	clr_key_wait_dos( void );
bool_t	check_memory( check_memory_t mem, const char *msg );
void	check_memory_all( void );
void	check_memory_gmain_c( void );

#ifdef __cplusplus
}
#endif
