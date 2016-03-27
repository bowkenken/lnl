/* msg.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_msg( void );
void	reset_static_msg( void );
void	reset_msg( lang_kind_t kind );
lang_kind_t	get_lang_kind( void );
lang_kind_t	get_lang_kind_next( void );
lang_kind_t	set_lang_kind_next( lang_kind_t kind );
char	*get_lang_id_next( void );
bool_t	get_flg_lang_ls_priority( void );
bool_t	set_flg_lang_ls_priority( bool_t flg );
char	*get_lang_kind_name( lang_kind_t kind );
lang_kind_t	trans_lang_id_to_kind( char *id );
const char	*cut_utf_str( const char *s, long draw_len );
long	str_len_draw( const char *s );
long	str_len_draw_english( const char *s );
long	str_len_draw_japanese_euc( const char *s );
long	str_len_draw_japanese_utf_8( const char *s );
long	str_len_draw_japanese_sjis( const char *s );
void	check_memory_msg_c( void );

#ifdef __cplusplus
}
#endif
