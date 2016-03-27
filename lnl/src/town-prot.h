/* town.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_town( void );
void	reset_static_town( void );
void	reset_glow( void );
void	init_town_ptn_col_tab( void );
bool_t	set_town_ptn_dflt( town_ptn_t *ptn );
bool_t	set_town_ptn_init( town_ptn_t *ptn );
bool_t	set_town_ptn_head( town_ptn_t *ptn, char *s );
bool_t	set_town_ptn_col( town_ptn_t *ptn, char *s );
bool_t	set_town_ptn_col_count( town_ptn_t *ptn );
bool_t	set_town_ptn_map( town_ptn_t *ptn, char *s, long y );
bool_t	trans_town_ptn( town_ptn_t *dst, town_ptn_t *src );
void	make_town( void );
void	make_town_ptn( void );
void	make_field_town( town_ptn_t *ptn, long x, long y );
bool_t	extend_stairs( long x, long y );
void	make_streetlamp( void );
void	on_streetlamp( long x, long y );
bool_t	make_art_town( shop_n_t shop_n, void *art_ls );
void	make_door_town( long mx, long my, char mnr );
void	reset_shop_face_ls( void );
bool_t	set_shop_face_ls( char mnr );
bool_t	chk_shop_face_ls( void );
bool_t	appear_party_town( void );
bool_t	navi_party( shop_n_t shop_n );
bool_t	navi_party_stairs();
bool_t	open_door_shop( long n );
bool_t	enter_shop( void );
void	party_exit_shop( long dr_n );
void	say_welcome_shop_msg( shop_n_t shop_n );
const char	*get_npc_name_shop( shop_n_t shop_n, sex_t sex );
sex_t	get_npc_sex_shop( shop_n_t shop_n );
void	party_enter_bar( void );
void	party_exit_bar( void );
bool_t	chk_shop_open( shop_n_t shop_n, bool_t flg_print );
bool_t	chk_package_item( item_t *item );
void	stay_inn( stay_inn_kind_t kind );
void	take_bath( chr_t *chr );
bool_t	set_art_name( mbr_t *mbr, item_t *art, deal_kind_t kind );
bool_t	set_art_name_equip( mbr_t *mbr, item_t *art, equip_kind_t eq );
bool_t	chk_pay( mbr_t *mbr, gold_t price );
gold_t	get_price( shop_n_t shop_n, item_t *item, deal_kind_t deal_kind );
gold_t	discount( gold_t price, shop_n_t shop_n, deal_kind_t deal_kind );
gold_t	get_price_wpn( item_t *item );
gold_t	get_price_armor( item_t *item );
gold_t	get_price_stick( item_t *item );
gold_t	get_price_inst( item_t *item );
gold_t	get_price_light( item_t *item );
gold_t	get_price_inn( bool_t flg_short_stay );
gold_t	get_price_temple_remove_curse( mbr_t *mbr );
gold_t	get_price_temple_cure_status( mbr_t *mbr );
gold_t	get_price_temple_resurrection( mbr_t *mbr );
gold_t	get_price_temple_contribution( mbr_t *mbr );
shop_n_t	get_shop_n( char face_mnr );
char	get_shop_mnr_face( shop_n_t n );
char	*get_shop_name( shop_n_t shop_n );
void	set_map_sunshine( void );
void	chk_morning_glow( long turn );
void	chk_evening_glow( long turn );
long	get_glow_n( long turn, bool_t flg_morning );
void	set_map_glow( long dx, long dy, bool_t flg_morning );
void	hear_rumor( shop_n_t shop_n );
void	paying_gold( chr_t *chr, gold_t price );
void	paid_gold( chr_t *chr, gold_t price );
bool_t	chk_discount( void );
bool_t	chk_discount_day( void );
bool_t	chk_discount_turn();
bool_t	chk_discount_open();
bool_t	chk_discount_door( door_t *dr );
bool_t	chk_queue_chr( chr_t *chr );
bool_t	chk_discount_mark( chr_t *chr );
void	set_discount( void );
void	clr_discount( void );
void	set_discount_sold_out();
bool_t	set_discount_queue( door_t *dr );
discount_queue_t	*get_discount_queue( void );
long	get_discount_queue_n( chr_t *chr );
long	get_discount_queue_max_n( chr_t *chr );
void	chk_discount_queue( void );
void	chk_clr_chr_discount_queue( chr_t *chr );
void	chk_enter_discount_shop( chr_t *chr );
void	inc_discount_queue( chr_t *chr );
void	dec_discount_queue( long n );
bool_t	chk_party_in_shop( void );
door_t	*get_shop_door( shop_n_t n );
town_ptn_col_tab_t	*get_town_ptn_col_tab( void );
long	get_town_ptn_col_tab_max_n( void );
art_ls_pet_shop_t	*get_art_ls_pet_shop( void );
bool_t	save_town( void );
void	check_memory_town_c( void );

#ifdef __cplusplus
}
#endif
