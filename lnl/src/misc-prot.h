/* misc.c */

#ifdef __cplusplus
extern "C" {
#endif

void	reset_static_misc( void );
char	*fmt_gold( gold_t gold );
char	*fmt_num( long n );
long	un_fmt_num( const char *s );
long	get_pading_len( const char *s, long min_len );
long	sgn_l( long n );
long	min_l( long n1, long n2 );
long	max_l( long n1, long n2 );
void	srandm( long n );
long	get_randm_seed( void );
long	randm( long n );
long	randm_sub( long n );
bool_t	rate_randm( rate_t rate );
bool_t	per_randm( long per );
long	count_randm_rate( rate_t rate );
long	gui_randm( long n );
rate_t	modified_rate( rate_t rate, long n );
bool_t	chk_ver_old( const ver_t *ver, long mjr, long mnr, long pat );
bool_t	chk_ver_new( const ver_t *ver, long mjr, long mnr, long pat );
bool_t	chk_ver_new_match( const ver_t *ver, long mjr, long mnr, long pat );
bool_t	chk_ver_match( const ver_t *ver, long mjr, long mnr, long pat );
long	str_len_std( const char *s );
char	*str_nz_cpy( char *dst, const char *src, int len );
char	*str_max_n_cat( char *dst, const char *src, int len );
void	str_trim_tail( char *str, const char *spc_char );
void	sn_printf( char *s, long n, const char *fmt, ... );
void	vsn_printf( char *s, long n, const char *fmt, va_list argptr );
bool_t	chk_flg( unsigned long var, unsigned long flg );
bool_t	chk_flg_or( unsigned long var, unsigned long flg );
void	*alloc_mem( long size, bool_t flg_exit );
void	free_mem( void *p );
void	check_memory_misc_c( void );

#ifdef __cplusplus
}
#endif
