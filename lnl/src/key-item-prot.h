/* key-item.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_key_item( void );
void	init_key_item_debug( void );
bool_t	chk_key_item( star_drop_kind_t kind );
void	set_key_item( star_drop_kind_t kind, bool_t flg_have );
bool_t	chk_enter_last_stage( void );
void	event_boot_unit( long x, long y );
const char	*get_key_item_name( star_drop_kind_t kind );
void	check_memory_key_item_c( void );

#ifdef __cplusplus
}
#endif
