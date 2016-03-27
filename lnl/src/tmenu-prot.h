/* tmenu.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_town_menu( void );
void	reset_static_town_menu( void );
char	*menu_shop_sel_mbr( shop_n_t shop_n, bool_t flg_pet );
char	*cb_menu_temple_init( menu_t **pp, menu_t **dflt );
char	*cb_menu_temple_remove_curse( menu_t **pp, menu_t **dflt );
char	*cb_menu_temple_cure_status( menu_t **pp, menu_t **dflt );
char	*cb_menu_temple_resurrection( menu_t **pp, menu_t **dflt );
char	*cb_menu_temple_contribution( menu_t **pp, menu_t **dflt );
char	*menu_restaurant( void );
bool_t	chk_shop_order( shop_n_t shop_n );
char	*menu_order( void );
char	*menu_order_sel_mbr( void );
char	*cb_menu_order_sel( menu_t **pp, menu_t **dflt );
void	next_g_sel_mbr( bool_t flg_loop );
char	*cb_menu_order_chose( menu_t **pp, menu_t **dflt );
bool_t	chk_order_milk( mbr_t *mbr, shop_n_t shop_n, item_t *item );
char	*menu_shop( shop_n_t shop_n, mbr_t *mbr, char *str_goto );
void	set_ls_menu_shop( long *k, deal_kind_t deal_kind );
char	*cb_menu_shop_data( menu_t **pp, menu_t **dflt );
char	*menu_town_mbr_data(
	mbr_data_edit_kind_t edit_kind,
	bool_t flg_ls_mbr
);
char	*cb_menu_pet_shop_data( menu_t **pp, menu_t **dflt );
char	*menu_town_pet_data( void );
char	*cb_menu_shop_collect_gold( menu_t **pp, menu_t **dflt );
char	*cb_menu_shop_divide_gold( menu_t **pp, menu_t **dflt );
char	*cb_menu_shop_give_gold( menu_t **pp, menu_t **dflt );
char	*cb_menu_shop( menu_t **pp, menu_t **dflt );
char	*cb_menu_shop_buy( menu_t **pp, menu_t **dflt );
char	*cb_menu_shop_sale_item( menu_t **pp, menu_t **dflt );
char	*cb_menu_shop_sale_equip( menu_t **pp, menu_t **dflt );
long	menu_shop_buy(
	shop_n_t g_shop_n, mbr_t *g_sel_mbr, item_t *item
);
long	menu_shop_sale_item(
	shop_n_t shop_n, mbr_t *mbr, item_t *item
);
long	menu_shop_sale_equip(
	shop_n_t shop_n, mbr_t *mbr, item_t *item
);
long	menu_shop_sale(
	shop_n_t shop_n, mbr_t *mbr, item_t *item,
	deal_kind_t deal_kind, bool_t flg_auto_sale
);
item_t	*get_begin_article(
	mbr_t *mbr, shop_n_t shop_n, deal_kind_t kind
);
item_t	*get_next_article( item_t *art, deal_kind_t kind );
bool_t	chk_end_article( item_t *art, item_t *art_head, deal_kind_t kind );
bool_t	chk_deal_article(
	item_t *art, shop_n_t shop_n, deal_kind_t deal_kind
);
shop_n_t	get_shop_deal_article( item_t *art, deal_kind_t deal_kind );
char	*menu_bar( void );
char	*cb_menu_bar_order( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_form( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_form_init( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_form_sub( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_form_sub_init( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_join( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_join_sub_init( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_join_sub( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_not_join( menu_t **pp, menu_t **dflt );
void	next_g_sel_ls_mbr( void );
char	*cb_menu_bar_edit_mbr( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_edit_mbr_init( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_edit_mbr_sub( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_data_form( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_data_edit( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_arrange_up( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_arrange_down( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_arrange_top( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_arrange_bottom( menu_t **pp, menu_t **dflt );
void	menu_bar_arrange_1( mbr_t *mbr, long d );
void	menu_bar_arrange( mbr_t *mbr, long d );
char	*cb_menu_bar_new_mbr( menu_t **pp, menu_t **dflt );
bool_t	exec_menu_new_mbr( void );
char	*cb_menu_bar_remove_mbr( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_remove_mbr_sub( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_edit_class( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_edit_class_sub( menu_t **pp, menu_t **dflt );
char	*menu_edit_class( long n );
char	*cb_menu_bar_arrange_up_class( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_arrange_down_class( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_arrange_top_class( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_arrange_bottom_class( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_edit_skill( menu_t **pp, menu_t **dflt );
char	*menu_edit_skill( long n );
char	*cb_menu_bar_new_class( menu_t **pp, menu_t **dflt );
char	*menu_new_class( long n );
long	exec_edit_class( class_t *org, bool_t flg_new );
long	exec_edit_skill( class_t *org, bool_t flg_new );
void	set_edit_skill_n( edit_skill_t n );
edit_skill_t	get_edit_skill_n( void );
char	*exec_sel_skill_edit( class_t *work, long slot );
char	*exec_sel_skill( skill_kind_t *ret_kind );
char	*cb_menu_sel_skill( menu_t **pp, menu_t **dflt );
char	*cb_menu_bar_remove_class( menu_t **pp, menu_t **dflt );
rate_t	calc_abl_total( class_t *p );
bool_t	exec_menu_ask_edit_class(
	class_t *org, class_t *work, bool_t flg_new
);
bool_t	exec_menu_ask_edit_skill(
	class_t *org, class_t *work, bool_t flg_new
);
void	menu_edit_class_inc_abl(
	class_t *p, edit_class_t n, long add
);
char	*cb_menu_load_bar( menu_t **pp, menu_t **dflt );
char	*cb_menu_save_bar( menu_t **pp, menu_t **dflt );
void	menu_load_start( void );
void	menu_load_bar( void );
void	menu_save_bar( void );
char	*menu_inn( void );
char	*cb_menu_inn_stay( menu_t **pp, menu_t **dflt );
char	*cb_menu_inn_short_stay( menu_t **pp, menu_t **dflt );
char	*cb_menu_inn_stay_in_mews( menu_t **pp, menu_t **dflt );
char	*cb_menu_inn_bath( menu_t **pp, menu_t **dflt );
char	*cb_menu_magic_guild_init( menu_t **pp, menu_t **dflt );
char	*cb_menu_magic_guild( menu_t **pp, menu_t **dflt );
char	*cb_menu_magic_guild_no_learn( menu_t **pp, menu_t **dflt );
char	*cb_menu_pet_shop_init( menu_t **pp, menu_t **dflt );
char	*cb_menu_pet_shop_take( menu_t **pp, menu_t **dflt );
char	*cb_menu_pet_shop_take_sel( menu_t **pp, menu_t **dflt );
char	*cb_menu_pet_shop_leave( menu_t **pp, menu_t **dflt );
char	*cb_menu_pet_shop_leave_sel( menu_t **pp, menu_t **dflt );
char	*cb_menu_pet_shop_name( menu_t **pp, menu_t **dflt );
char	*cb_menu_pet_shop_name_sel( menu_t **pp, menu_t **dflt );
char	*cb_menu_pet_shop_remove( menu_t **pp, menu_t **dflt );
char	*cb_menu_pet_shop_remove_sel( menu_t **pp, menu_t **dflt );
char	*cb_menu_pet_shop_buy( menu_t **pp, menu_t **dflt );
char	*cb_menu_pet_shop_buy_sel( menu_t **pp, menu_t **dflt );
char	*cb_menu_town_init( menu_t **pp, menu_t **dflt );
char	*cb_menu_navi_init( menu_t **pp, menu_t **dflt );
char	*cb_menu_navi( menu_t **pp, menu_t **dflt );
char	*cb_menu_navi_stairs( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_sale( menu_t **pp, menu_t **dflt );
bool_t	set_menu_auto_sale( menu_t *ls, mbr_t *mbr );
char	*cb_menu_auto_sale_chk( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_sale_exec( menu_t **pp, menu_t **dflt );
shop_n_t	get_cur_shop_n( void );
void	set_cur_shop_n( shop_n_t n );
void	check_memory_tmenu_c( void );

#ifdef __cplusplus
}
#endif
