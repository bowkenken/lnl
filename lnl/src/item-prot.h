/* item.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_item( void );
void	reset_static_item( void );
void	reset_item( void );
void	close_item( void );
void	init_wpn( void );
void	init_armor( void );
void	init_potion( void );
void	init_color_tab( void );
void	reset_potion_tab( void );
void	reset_potion_color( void );
void	init_scroll( void );
void	init_ttl_syllable_tab( void );
void	init_scroll_tab( void );
void	reset_scroll_ttl_syllable( void );
void	init_stick( void );
void	init_wand_material_tab( void );
void	init_rod_material_tab( void );
void	init_staff_material_tab( void );
void	reset_wand_tab( void );
void	reset_rod_tab( void );
void	reset_staff_tab( void );
void	reset_wand_material( void );
void	reset_rod_material( void );
void	reset_staff_material( void );
void	init_stick_material_tab(
	stick_kind_t kind,
	long *max_n,
	ls_identified_t **tab_p, n_msg_t *idx_tab
);
void	reset_stick_tab(
	stick_kind_t kind,
	long *max_n,
	ls_identified_t *tab, n_msg_t *idx_tab
);
void	reset_stick_material(
	stick_kind_t kind,
	long *max_n,
	ls_identified_t *tab, n_msg_t *idx_tab
);
void	init_acce( void );
void	init_ring_material_tab( void );
void	init_amulet_material_tab( void );
void	init_necklace_material_tab( void );
void	reset_ring_tab( void );
void	reset_amulet_tab( void );
void	reset_necklace_tab( void );
void	reset_ring_material( void );
void	reset_amulet_material( void );
void	reset_necklace_material( void );
void	init_acce_material_tab(
	acce_kind_t kind,
	long *max_n,
	ls_identified_t **tab_p, n_msg_t *idx_tab
);
void	reset_acce_tab(
	acce_kind_t kind,
	long *max_n,
	ls_identified_t *tab, n_msg_t *idx_tab
);
void	reset_acce_material(
	acce_kind_t kind,
	long *max_n,
	ls_identified_t *tab, n_msg_t *idx_tab
);
void	init_inst( void );
void	init_anthology( void );
void	init_light( void );
void	init_food( void );
void	init_tobacco( void );
void	init_pipe( void );
void	init_rare_goods( void );
void	init_bone( void );
void	init_coin( void );
void	init_item_town( void );
void	reset_item_town( void );
void	garbage_collection_all_item( void );
void	set_flg_item_garbage( item_t *item, bool_t flg );
item_kind_t	make_item( long x, long y, long dun_lev );
item_t	*make_item_sub( long dun_lev, bool_t flg_chest );
item_t	*make_item_wpn_rand( long dun_lev );
item_t	*make_item_wpn( long dun_lev, long n, bool_t curse );
rate_t	gen_slayer_rate( long dun_lev );
bool_t	add_slayer( wpn_t *wpn, long dun_lev );
void	make_item_wpn_randm_art( wpn_t *wpn, long dun_lev );
void	make_item_wpn_randm_art_n( wpn_t *wpn, long max_n );
long	gen_wpn_randm_art_n( long dun_lev );
void	add_wpn_randm_art(
	wpn_randm_art_kind_t kind,
	wpn_randm_art_t *art
);
void	gen_wpn_randm_art_face(
	wpn_randm_art_kind_t kind,
	char *mjr, char *mnr
);
bool_t	chk_dup_wpn_randm_art( wpn_t *wpn, long n );
item_t	*make_item_armor_rand( long dun_lev );
item_t	*make_item_armor( long dun_lev, long n, bool_t curse );
rate_t	gen_armor_resi_rate( long dun_lev );
bool_t	add_armor_resi( item_t *p, long dun_lev, resi_kind_t resi );
resi_kind_t	gen_armor_resi_kind( long dun_lev );
void	make_item_armor_randm_art( armor_t *armor, long dun_lev );
void	make_item_armor_randm_art_n( armor_t *armor, long max_n );
long	gen_armor_randm_art_n( long dun_lev );
void	add_armor_randm_art(
	armor_randm_art_kind_t kind,
	armor_randm_art_t *art
);
void	gen_armor_randm_art_face(
	armor_randm_art_kind_t kind,
	char *mjr, char *mnr
);
bool_t	chk_dup_armor_randm_art( armor_t *armor, long n );
item_t	*make_item_potion_rand( long dun_lev );
item_t	*make_item_potion( long dun_lev, long n );
item_t	*make_item_scroll_rand( long dun_lev );
item_t	*make_item_scroll( long dun_lev, long n );
item_t	*make_item_stick_rand( long dun_lev );
item_t	*make_item_stick( long dun_lev, long n );
long	calc_stick_use_n(
	stick_kind_t kind, long dun_lev, long use_n, bool_t flg_randm
);
item_t	*make_item_acce_rand( long dun_lev );
item_t	*make_item_acce( long dun_lev, long n );
item_t	*make_item_inst_rand( long dun_lev );
item_t	*make_item_inst( long dun_lev, long n, bool_t curse );
rate_t	gen_inst_limit_rate( long dun_lev );
rate_t	gen_inst_spell_rate( long dun_lev );
spell_kind_t	gen_inst_spell_kind( long dun_lev, long tab_n );
bool_t	add_inst_spell( inst_t *p, long dun_lev, spell_kind_t kind );
item_t	*make_item_anthology_rand( long dun_lev );
item_t	*make_item_anthology( long dun_lev, long n );
item_t	*make_item_light_rand( long dun_lev );
item_t	*make_item_light( long dun_lev, long n );
item_t	*make_item_spike_rand( long dun_lev );
item_t	*make_item_spike( long dun_lev );
item_t	*make_item_food_rand( long dun_lev );
item_t	*make_item_food( long dun_lev, long n );
item_t	*make_item_chest_rand( long dun_lev );
item_t	*make_item_chest( long dun_lev, long contents_n, bool_t flg_trap );
item_t	*make_item_chest_alloc(
	item_t *item,
	long dun_lev, long contents_n, bool_t flg_trap
);
item_t	*make_item_tobacco_rand( long dun_lev );
item_t	*make_item_tobacco( long dun_lev, long n );
item_t	*make_item_pipe_rand( long dun_lev );
item_t	*make_item_pipe( long dun_lev, long n );
item_t	*make_item_disposal_rand( long dun_lev );
item_t	*make_item_disposal( long dun_lev );
item_t	*make_item_rare_goods_rand( long dun_lev );
item_t	*make_item_rare_goods( long dun_lev, long n );
item_t	*make_item_bone_rand( long dun_lev );
item_t	*make_item_bone( long dun_lev, mnstr_tab_t *tab );
item_t	*make_item_coin_rand( long dun_lev );
item_t	*make_item_coin( long dun_lev, long n );
item_t	*make_item_junk_rand( long dun_lev );
item_t	*make_item_junk( long dun_lev );
item_t	*make_item_sel(
	item_kind_t kind,
	long k1, long k2, long k3,
	long dun_lev
);
bool_t	fx_wish_artifact_wpn( chr_t *chr, wish_level_t wish_level );
bool_t	fx_wish_artifact_armor( chr_t *chr, wish_level_t wish_level );
void	set_item_face( item_t *item );
void	set_item_name( item_t *item );
bool_t	set_item_name_wpn( item_t *item );
const char	*get_wpn_randm_art_name( item_t *item );
bool_t	set_item_name_armor( item_t *item );
const char	*get_armor_randm_art_name( item_t *item );
bool_t	set_item_name_potion( item_t *item );
bool_t	set_item_name_scroll( item_t *item );
long	get_scroll_nin_lev( scroll_kind_t scroll_kind );
bool_t	set_item_name_stick( item_t *item );
bool_t	set_item_name_acce( item_t *item );
bool_t	set_item_name_inst( item_t *item );
bool_t	set_item_name_anthology( item_t *item );
bool_t	set_item_name_light( item_t *item );
bool_t	set_item_name_spike( item_t *item );
bool_t	set_item_name_food( item_t *item );
bool_t	set_item_name_chest( item_t *item );
bool_t	set_item_name_tobacco( item_t *item );
bool_t	set_item_name_pipe( item_t *item );
bool_t	set_item_name_disposal( item_t *item );
bool_t	set_item_name_rare_goods( item_t *item );
bool_t	set_item_name_bone( item_t *item );
bool_t	set_item_name_coin( item_t *item );
bool_t	set_item_name_junk( item_t *item );
bool_t	clean_all_disposal( mbr_t *mbr );
bool_t	identify_item( item_t *item );
bool_t	identify_potion( item_t *item );
bool_t	identify_scroll( item_t *item );
bool_t	identify_stick( item_t *item );
bool_t	identify_acce( item_t *item );
bool_t	send_item( mbr_t *mbr );
bool_t	receive_item( mbr_t *mbr );
bool_t	hand_item( chr_t *dst, chr_t *src, item_t *item, long n );
bool_t	put_item( item_t *item, long x, long y, long max_r, bool_t flg_mbr );
bool_t	put_item_sub( item_t *item, long x, long y, long *np );
bool_t	put_item_in_chest( item_t *p, long x, long y );
bool_t	drop_item( long x, long y, item_t *item, long n );
bool_t	pick_up_item( mbr_t *mbr, long x, long y );
bool_t	give_party_item(
	item_t *item,
	bool_t flg_force,
	bool_t flg_print
);
bool_t	give_mbr_item(
	mbr_t *mbr,
	item_t *item,
	bool_t flg_force
);
bool_t	give_mbr_item_print(
	mbr_t *mbr,
	item_t *item,
	bool_t flg_force,
	bool_t flg_print
);
bool_t	give_mbr_item_sub( mbr_t *mbr, item_t *item );
bool_t	equip_item_sel( mbr_t *mbr, item_t *item );
bool_t	equip_item( mbr_t *mbr, item_t *item, equip_kind_t kind );
bool_t	equip_item_sub( mbr_t *mbr, item_t *item, equip_kind_t kind );
bool_t	chk_singly_equip( item_t *item, equip_kind_t kind );
bool_t	chk_equip_two_handed_wpn(
	mbr_t *mbr, item_t *item, equip_kind_t kind
);
bool_t	chk_bar_limit_inst( chr_t *chr );
bool_t	chk_equip_kind( item_t *item, equip_kind_t kind );
bool_t	take_off_item( mbr_t *mbr, equip_kind_t kind );
bool_t	take_off_item_sub( mbr_t *mbr, equip_kind_t kind );
bool_t	chk_take_off_curse( mbr_t *mbr, equip_kind_t kind );
bool_t	put_item_in_chest_quick( mbr_t *mbr, item_t *item );
bool_t	break_item_fragile( item_t *item, bool_t flg_mbr );
void	break_item_contents( item_t *chest, mbr_t *mbr );
bool_t	break_item( item_t *item, bool_t flg_mbr );
bool_t	chk_can_break_item( item_t *item );
bool_t	open_item( item_t *item, mbr_t *mbr );
bool_t	open_item_pos( long x, long y, item_t *item, mbr_t *mbr );
bool_t	disarm_item( item_t *item );
void	set_item_alias( item_t *item );
void	chk_item_data( item_t *item );
void	chk_item_data_wpn( item_t *item );
void	chk_item_data_wpn_randm_art_ls( item_t *item );
void	chk_item_data_wpn_randm_art( wpn_randm_art_t *art );
const char	*get_wpn_randm_art_add_stat_name( char mnr );
fx_kind_t	get_wpn_randm_art_add_stat_fx( char mnr );
const char	*get_wpn_randm_art_drain_name( char mnr );
void	chk_item_data_armor( item_t *item );
void	chk_item_data_armor_randm_art_ls( item_t *item );
void	chk_item_data_armor_randm_art( armor_randm_art_t *art );
const char	*get_armor_randm_art_resi_stat_name( char mnr );
const char	*get_armor_randm_art_healing_name( char mnr );
char	cv_flg_stat_to_armor_randm_art_mnr( flg_stat_t stat );
bool_t	chk_randm_art( item_t *item );
rate_t	calc_rate_abl_equip( mbr_t *mbr, abl_kind_t abl );
bool_t	teleport_item( item_t *item );
void	detect_item( long x, long y, long r );
bool_t	cmp_item( item_t *p1, item_t *p2 );
long	inc_item( item_t *item, long n );
void	inc_turn_all_item( void );
long	count_mbr_item_n( mbr_t *mbr );
long	get_item_bundle( item_t *item );
bool_t	chk_range_chr_bash( chr_t *chr );
bool_t	chk_range_mbr_bash( chr_t *chr );
bool_t	chk_range_mnstr_bash( chr_t *chr );
bool_t	chk_range_chr_throw( chr_t *chr );
bool_t	chk_range_mbr_throw( chr_t *chr );
bool_t	chk_range_mnstr_throw( chr_t *chr );
bool_t	chk_range_attack_sub( chr_t *chr, long r );
bool_t	drop_arw( long x, long y, item_t *item );
void	dec_throw( mbr_t *mbr, bool_t flg_drop, long x, long y );
bool_t	chk_come_back_arw( mbr_t *mbr );
bool_t	reload_arw( mbr_t *mbr );
char	get_item_mjr( item_t *item );
char	get_item_mnr( item_t *item );
wpn_tab_t	*get_wpn_tab( wpn_kind_t kind );
wpn_tab_t	*get_wpn_tab_head( void );
armor_tab_t	*get_armor_tab( armor_kind_t kind );
armor_tab_t	*get_armor_tab_head( void );
potion_tab_t	*get_potion_tab( potion_kind_t kind );
potion_tab_t	*get_potion_tab_head( void );
scroll_tab_t	*get_scroll_tab( scroll_kind_t kind );
scroll_tab_t	*get_scroll_tab_head( void );
stick_tab_t	*get_stick_tab( stick_kind_t kind, spell_kind_t spell );
stick_tab_t	*get_stick_tab_head( void );
acce_tab_t	*get_acce_tab(
	ring_kind_t ring_kind,
	amulet_kind_t amulet_kind,
	necklace_kind_t necklace_kind
);
acce_tab_t	*get_acce_tab_head( void );
inst_tab_t	*get_inst_tab( inst_kind_t kind );
inst_tab_t	*get_inst_tab_head( void );
anthology_tab_t	*get_anthology_tab( anthology_kind_t kind );
anthology_tab_t	*get_anthology_tab_head( void );
light_tab_t	*get_light_tab(
	light_kind_t kind,
	wish_level_t wish_level
);
light_tab_t	*get_light_tab_head( void );
food_tab_t	*get_food_tab( food_kind_t kind );
food_tab_t	*get_food_tab_head( void );
tobacco_tab_t	*get_tobacco_tab( tobacco_kind_t kind, tobacco_brand_t brand );
tobacco_tab_t	*get_tobacco_tab_head( void );
pipe_tab_t	*get_pipe_tab( pipe_kind_t kind );
pipe_tab_t	*get_pipe_tab_head( void );
rare_goods_kind_t	get_rare_goods_randm();
rare_goods_tab_t	*get_rare_goods_tab( rare_goods_kind_t kind );
rare_goods_tab_t	*get_rare_goods_tab_head( void );
coin_tab_t	*get_coin_tab( coin_kind_t kind );
coin_tab_t	*get_coin_tab_head( void );
long	get_wpn_tab_n( wpn_tab_t *p );
long	get_armor_tab_n( armor_tab_t *p );
long	get_potion_tab_n( potion_tab_t *p );
long	get_scroll_tab_n( scroll_tab_t *p );
long	get_stick_tab_n( stick_tab_t *p );
long	get_acce_tab_n( acce_tab_t *p );
long	get_inst_tab_n( inst_tab_t *p );
long	get_anthology_tab_n( anthology_tab_t *p );
long	get_light_tab_n( light_tab_t *p );
long	get_food_tab_n( food_tab_t *p );
long	get_tobacco_tab_n( tobacco_tab_t *p );
long	get_pipe_tab_n( pipe_tab_t *p );
long	get_rare_goods_tab_n( rare_goods_tab_t *p );
long	get_coin_tab_n( coin_tab_t *p );
item_t	*get_item( long x, long y );
void	copy_item( item_t *dst, item_t *src );
void	del_item( item_t *p );
void	inc_chest_ref( item_t *chest );
void	dec_chest_ref( item_t *chest );
void	remove_mbr_del_item( long ls_mbr_n );
void	move_ls_item( item_t *dst, item_t *src );
item_t	*alloc_item( void );
void	free_item_ls( item_t *ls );
void	free_item( item_t *p );
void	ins_ls_item( item_t *ls, item_t *p );
bool_t	ins_sort_item( item_t *ls, item_t *item );
bool_t	chk_ins_sort_item( item_t *ls, item_t *item, long max_n );
bool_t	chk_have_chest( mbr_t *mbr );
bool_t	ins_sort_item_chest( item_t *ls, item_t *item );
bool_t	chk_ins_sort_item_chest( item_t *ls, item_t *item );
bool_t	chk_give_mbr_chest( mbr_t *mbr, item_t *item );
bool_t	chk_item_is_equip( item_t *p );
bool_t	chk_dagger( const wpn_tab_t *arw_tab );
bool_t	chk_bow( const wpn_tab_t *arw_tab, const wpn_tab_t *bow_tab );
long	count_ls_item( item_t *ls, item_kind_t kind );
void	arrange_item_1( long n, long d );
void	arrange_item( long n, long d );
void	arrange_equip_1( long n, long d );
void	arrange_equip( long n, long d );
item_t	*get_item_free_next( void );
item_t	*get_mbr_item_asgn( mbr_t *mbr );
item_t	*get_mbr_item_asgn_equip( mbr_t *mbr );
item_t	*get_dun_item_asgn( void );
item_t	*get_shop_bar_item_asgn( void );
item_t	*get_shop_wpn_item_asgn( void );
item_t	*get_shop_armor_item_asgn( void );
item_t	*get_shop_temple_item_asgn( void );
item_t	*get_shop_alchemy_item_asgn( void );
item_t	*get_shop_music_item_asgn( void );
item_t	*get_shop_grocery_item_asgn( void );
item_t	*get_shop_restaurant_item_asgn( void );
item_t	*get_shop_tearoom_item_asgn( void );
item_t	*get_shop_tobacco_item_asgn( void );
bool_t	chk_wpn_randm_art(
	wpn_randm_art_kind_t kind,
	char mnr,
	chr_t *o_p,
	chr_t *d_p,
	bool_t flg_throw
);
bool_t	chk_armor_randm_art(
	armor_randm_art_kind_t kind,
	char mnr,
	chr_t *o_p,
	chr_t *d_p
);
bool_t	chk_wpn_randm_art_item(
	wpn_randm_art_kind_t kind,
	char mnr,
	item_t *item
);
bool_t	chk_armor_randm_art_item(
	armor_randm_art_kind_t kind,
	char mnr,
	item_t *item
);
rate_t	get_resi_armor( mbr_t *p, resi_kind_t resi );
bool_t	chk_wear_armor( mbr_t *mbr );
spell_kind_t	get_inst_spell_kind( mbr_t *mbr );
long	expr_wpn_add_hit( long lev );
long	expr_wpn_add_crtcl( long lev );
long	expr_wpn_add_dam( long lev );
long	expr_armor_add_def( long lev );
long	expr_armor_add_crtcl( long lev );
long	expr_armor_add_ac( long lev );
long	expr_light_turn( long max );
char	*get_item_mjr_name( char mjr );
char	*get_item_mnr_name( char mjr, char mnr );
char	*get_item_equip_name( equip_kind_t kind );
item_t	*get_item_mbr( long ls_mbr_n, item_kind_t kind );
item_t	*get_item_mbr_randm( long ls_mbr_n );
item_t	*get_item_mbr_anthology( mbr_t *mbr, anthology_kind_t kind );
item_t	*get_item_nearest(
	chr_t *chr, act_kind_t act_kind, bool_t flg_auto_menu
);
item_t	*get_item_near(
	chr_t *chr, act_kind_t act_kind, bool_t flg_auto_menu
);
item_t	*get_item_disperse(
	chr_t *chr, act_kind_t act_kind, bool_t flg_auto_menu
);
item_t	*get_item_randm(
	chr_t *chr, act_kind_t act_kind, bool_t flg_auto_menu
);
item_t	*get_item_own(
	chr_t *chr, act_kind_t act_kind, bool_t flg_auto_menu
);
item_t	*get_item_identified(
	chr_t *chr, act_kind_t act_kind, bool_t flg_auto_menu
);
item_t	*get_item_un_identified(
	chr_t *chr, act_kind_t act_kind, bool_t flg_auto_menu
);
item_t	*get_item_identified_sub(
	chr_t *chr, act_kind_t act_kind, bool_t flg_auto_menu,
	bool_t flg_identified
);
item_t	*get_item_food(
	chr_t *chr, act_kind_t act_kind, bool_t flg_auto_menu
);
item_t	*randm_wpn( item_t *eq );
item_t	*randm_armor( item_t *eq );
bool_t	chk_mark_item( item_t *p, act_kind_t act_kind );
bool_t	chk_own_item( item_t *item, mbr_t *mbr );
bool_t	chk_appoint_item( item_t *item, mbr_t *mbr );
bool_t	chk_mbr_have_rare_goods(
	mbr_t *mbr, rare_goods_kind_t kind,
	mnstr_kind_t mnstr_kind,
	bool_t flg_del_item
);
long	get_chest_n( long dun_lev );
ls_identified_t	*get_color_tab( void );
n_msg_t	*get_color_idx_tab( void );
n_msg_t	*get_ttl_syllable_idx_tab( void );
ls_identified_t	*get_wand_material_tab( void );
ls_identified_t	*get_rod_material_tab( void );
ls_identified_t	*get_staff_material_tab( void );
n_msg_t	*get_stick_material_idx_tab( void );
ls_identified_t	*get_ring_material_tab( void );
ls_identified_t	*get_amulet_material_tab( void );
ls_identified_t	*get_necklace_material_tab( void );
n_msg_t	*get_acce_material_idx_tab( void );
void	check_memory_item_c( void );

#ifdef __cplusplus
}
#endif
