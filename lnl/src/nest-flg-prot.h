/* nest-flg.c */

#ifdef __cplusplus
extern "C" {
#endif

void	reset_static_nest_flg( void );
long	make_nest_flg( void );
long	bgn_nest_flg( long flg_n );
long	end_nest_flg( long flg_n );
long	set_nest_flg( long flg_n, long n );
long	chk_nest_flg( long flg_n );
void	check_memory_nest_flg_c( void );

#ifdef __cplusplus
}
#endif
