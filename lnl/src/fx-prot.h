/* fx.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_fx( void );
void	reset_static_fx( void );
void	inc_turn_all_fx( void );
void	inc_day_all_fx( void );
void	natural_cure_hp_chr( chr_t *chr );
void	natural_cure_mp_chr( chr_t *chr );
void	natural_cure_exp_chr( chr_t *chr );
void	modifier_cure_hp_chr( chr_t *chr );
void	modifier_cure_mp_chr( chr_t *chr );
void	sober( chr_t *chr );
void	dec_turn_fx_all_mbr( long turn );
void	dec_turn_fx_all_pet( long turn );
void	dec_turn_fx_all_mnstr( long turn );
void	dec_turn_fx_chr( chr_t *chr, long turn );
abl_kind_t	get_fx_to_abl( fx_kind_t kind );
long	get_fx_to_abl_add( fx_kind_t kind );
void	exec_all_fx( chr_t *chr );
fx_t	*set_fx( chr_t *chr, fx_kind_t kind, long turn );
void	exec_fx( fx_t *p );
void	clr_fx( fx_t *fx );
bool_t	set_fx_stat( fx_t *fx, flg_stat_t flg );
bool_t	clr_fx_stat( fx_t *fx, flg_stat_t flg );
void	set_fx_abl( fx_t *fx );
void	clr_fx_abl( fx_t *fx );
bool_t	set_fx_resi( fx_t *fx );
bool_t	clr_fx_resi( fx_t *fx );
void	set_fx_pow_up_hp( fx_t *fx );
void	clr_fx_pow_up_hp( fx_t *fx );
bool_t	set_fx_magic_wpn( fx_t *fx );
bool_t	clr_fx_magic_wpn( fx_t *fx );
bool_t	add_fx_magic_wpn( fx_t *fx, long n );
bool_t	set_fx_magic_armor( fx_t *fx );
bool_t	clr_fx_magic_armor( fx_t *fx );
bool_t	add_fx_magic_armor( fx_t *fx, long n );
bool_t	set_fx_speed( fx_t *fx );
bool_t	clr_fx_speed( fx_t *fx );
bool_t	clr_fx_flg_chr( fx_t *fx, flg_chr_t flg );
void	set_fx_bless( fx_t *fx );
void	clr_fx_bless( fx_t *fx );
void	set_fx_store_light( fx_t *fx );
void	clr_fx_store_light( fx_t *fx );
bool_t	set_fx_polymorph( fx_t *fx );
bool_t	clr_fx_polymorph( fx_t *fx );
bool_t	cancel_fx_vanish( chr_t *chr );
void	exec_fx_poison( fx_t *fx );
void	exec_fx_fear( fx_t *fx );
void	exec_fx_weak( fx_t *fx );
void	exec_fx_store_light( fx_t *fx );
modifier_t	*get_modifier_song_mbr( void );
modifier_t	*get_modifier_song_mnstr( void );
modifier_t	*get_modifier_song_pet( void );
void	reset_modifier_all_song( void );
void	set_modifier_all_song( chr_t *chr );
void	set_modifier_all_song_sub(
	chr_t *chr,
	spell_tab_t *tab, extent_kind_t extent
);
void	set_modifier_all_song_limit( chr_t *chr, spell_tab_t *tab );
void	set_modifier_song( modifier_t *mod, spell_tab_t *tab );
void	quaff_potion( chr_t *chr, item_t *item, bool_t flg_dec );
bool_t	quaff_potion_std( chr_t *chr, fx_kind_t fx_k );
bool_t	quaff_potion_abl( chr_t *chr, fx_kind_t fx_k );
bool_t	quaff_potion_resi( chr_t *chr, fx_kind_t fx_k );
bool_t	quaff_potion_cure_lev( chr_t *chr );
bool_t	quaff_potion_cure_hp_light( chr_t *chr );
bool_t	quaff_potion_cure_hp_moderate( chr_t *chr );
bool_t	quaff_potion_cure_hp_serious( chr_t *chr );
bool_t	quaff_potion_cure_hp_max( chr_t *chr );
bool_t	quaff_potion_cure_poison( chr_t *chr );
bool_t	quaff_potion_cure_status( chr_t *chr );
bool_t	quaff_potion_detect_mnstr( chr_t *chr );
bool_t	quaff_potion_poison( chr_t *chr );
bool_t	quaff_potion_pow_up_hp( chr_t *chr );
bool_t	quaff_potion_speed( chr_t *chr, long sgn_n );
void	fill_potion( mbr_t *mbr, item_t *potion );
bool_t	fx_drink_liquor( chr_t *chr, item_t *item, liquor_kind_t kind );
bool_t	drink_liquor( chr_t *chr, liquor_kind_t kind );
void	read_scroll( chr_t *chr, item_t *item );
bool_t	read_scroll_sleep( chr_t *chr );
bool_t	read_scroll_identify_item( chr_t *chr );
bool_t	read_scroll_identify_all_item( chr_t *chr );
bool_t	read_scroll_detect_item( chr_t *chr );
bool_t	read_scroll_teleport( chr_t *chr );
bool_t	read_scroll_pow_up_wpn_hit( chr_t *chr );
bool_t	read_scroll_pow_up_wpn_crtcl( chr_t *chr );
bool_t	read_scroll_pow_up_wpn_dam( chr_t *chr );
bool_t	read_scroll_pow_up_armor_def( chr_t *chr );
bool_t	read_scroll_pow_up_armor_crtcl( chr_t *chr );
bool_t	read_scroll_pow_up_armor_ac( chr_t *chr );
bool_t	read_scroll_protect_armor( chr_t *chr );
bool_t	read_scroll_boomerang( chr_t *chr );
bool_t	read_scroll_remove_curse( chr_t *chr );
bool_t	read_scroll_recall( void );
void	read_scroll_nin( chr_t *chr, scroll_kind_t kind );
bool_t	zap_stick( chr_t *chr, item_t *item );
bool_t	fx_std( chr_t *chr, fx_kind_t fx_k );
bool_t	set_fx_std( chr_t *chr, fx_kind_t fx_k );
bool_t	fx_light( long x, long y );
bool_t	fx_darkness( long x, long y );
bool_t	fx_knock( door_t *door );
bool_t	fx_lock( door_t *door );
bool_t	fx_disarm_trap( trap_t *trap, chr_t *chr );
bool_t	fx_short_teleport_party( long bx, long by );
bool_t	fx_teleport_party_charge( void );
bool_t	fx_teleport_party( void );
bool_t	short_teleport_party( long bx, long by );
bool_t	teleport_party_charge( void );
bool_t	chk_teleport_party( void );
bool_t	teleport_party( void );
bool_t	fx_teleport( trgt_kind_t trgt_kind, void *p );
bool_t	teleport_chr( chr_t *chr );
bool_t	fx_recall( void );
bool_t	recall( void );
bool_t	chk_recall( void );
void	exec_recall( long n );
bool_t	fx_shelter( long x, long y );
bool_t	fx_create_food( chr_t *chr );
bool_t	fx_identify_all_item( mbr_t *mbr );
bool_t	fx_detect_item( chr_t *chr );
bool_t	fx_detect_door( chr_t *chr );
bool_t	fx_detect_trap( chr_t *chr );
bool_t	fx_detect_mnstr( chr_t *chr );
bool_t	fx_darkvision( chr_t *chr );
bool_t	fx_escape( long bx, long by );
bool_t	fx_sanctuary( chr_t *chr, abl_kind_t abl );
bool_t	fx_weak_attack(
	chr_t *o_p, trgt_kind_t trgt_kind, void *d_p,
	fx_kind_t fx_kind, abl_kind_t abl
);
void	fx_polymorph( chr_t *chr );
bool_t	fx_magic_missile(
	chr_t *o_p,
	trgt_kind_t trgt_kind, void *d_p,
	rate_t rate
);
bool_t	fx_spell_attack(
	chr_t *o_p, trgt_kind_t trgt_kind, void *d_p,
	resi_kind_t resi, abl_kind_t abl, rate_t rate
);
bool_t	fx_death_spell( chr_t *o_p, trgt_kind_t trgt_kind, void *trgt_p );
bool_t	fx_abl( chr_t *chr, fx_kind_t fx_kind );
bool_t	fx_acid( chr_t *chr );
bool_t	fx_acid_mbr( mbr_t *mbr );
bool_t	fx_acid_mnstr( mnstr_t *mnstr );
bool_t	fx_poison( chr_t *chr );
bool_t	fx_pow_up_hp( chr_t *chr );
void	pow_up_hp( fx_t *fx, long add_lev );
bool_t	fx_magic_wpn_armor( chr_t *chr, fx_kind_t kind );
bool_t	magic_wpn(
	fx_t *fx,
	rate_t wpn_hit, rate_t wpn_crtcl, rate_t wpn_dam
);
bool_t	magic_armor(
	fx_t *fx,
	rate_t armor_def, rate_t armor_crtcl, rate_t armor_ac
);
bool_t	fx_speed_up( chr_t *chr1, chr_t *chr2, long add );
void	fx_energy_drain_all_mbr( bool_t flg_set_max );
bool_t	fx_energy_drain( chr_t *chr, bool_t flg_set_max );
bool_t	fx_resi( chr_t *chr, fx_kind_t fx_kind );
bool_t	pow_up_resi( chr_t *chr, resi_kind_t resi );
bool_t	pow_down_resi( chr_t *chr, resi_kind_t resi );
bool_t	pow_up_down_resi( chr_t *chr, resi_kind_t resi, long n );
bool_t	fx_summon_monster( chr_t *chr, pet_kind_t kind, long n, long turn );
bool_t	fx_dismissal( chr_t *chr );
bool_t	fx_summon_bone( chr_t *chr, long turn );
bool_t	fx_summon_bone_mbr( mbr_t *mbr, long turn );
bool_t	fx_summon_bone_mnstr( mnstr_t *mnstr, long turn );
item_t	*exec_menu_sel_bone( mbr_t *mbr );
char	*cb_menu_sel_bone( menu_t **pp, menu_t **dflt );
bool_t	fx_cure_hp_light( chr_t *chr, long lev );
bool_t	fx_cure_hp_moderate( chr_t *chr, long lev );
bool_t	fx_cure_hp_serious( chr_t *chr, long lev );
bool_t	fx_cure_hp_max( chr_t *chr, long lev );
bool_t	fx_cure_hp( chr_t *chr, long lev, rate_t rate );
bool_t	fx_cure_mp_max( chr_t *chr, long lev );
bool_t	fx_cure_mp( chr_t *chr, long lev, rate_t rate );
bool_t	fx_transfer_mp( chr_t *chr, spell_tab_t *tab, rate_t rate );
bool_t	fx_cure_lev( chr_t *chr );
bool_t	fx_cure_exp_party( void );
bool_t	fx_cure_exp( chr_t *chr );
bool_t	fx_resurrection( chr_t *chr, bool_t flg_put );
bool_t	resurrection( chr_t *chr, bool_t flg_put );
bool_t	fx_heal( chr_t *chr );
bool_t	fx_cure_all_stat( chr_t *chr );
bool_t	fx_cure_stat( chr_t *chr, fx_kind_t fx_kind );
bool_t	fx_bless( chr_t *chr );
bool_t	fx_store_light( chr_t *chr );
bool_t	fx_remove_curse( chr_t *chr1, chr_t *chr2 );
bool_t	remove_curse( chr_t *chr1, mbr_t *mbr2, rate_t difficulty );
bool_t	fx_dispel_undead(
	chr_t *o_p,
	trgt_kind_t trgt_kind, void *d_p,
	rate_t rate
);
bool_t	fx_poltergeist( chr_t *chr );
bool_t	fx_pow_up_wpn_hit( mbr_t *mbr );
bool_t	fx_pow_up_wpn_crtcl( mbr_t *mbr );
bool_t	fx_pow_up_wpn_dam( mbr_t *mbr );
bool_t	fx_pow_up_armor_def( mbr_t *mbr );
bool_t	fx_pow_up_armor_crtcl( mbr_t *mbr );
bool_t	fx_pow_up_armor_ac( mbr_t *mbr );
bool_t	fx_protect_armor( mbr_t *mbr );
bool_t	fx_boomerang( mbr_t *mbr );
bool_t	pow_up_wpn_hit( item_t *wpn );
bool_t	pow_up_wpn_crtcl( item_t *wpn );
bool_t	pow_up_wpn_dam( item_t *wpn );
bool_t	pow_up_armor_def( item_t *armor );
bool_t	pow_up_armor_crtcl( item_t *armor );
bool_t	pow_up_armor_ac( item_t *armor );
long	calc_per_pow_up_wpn_hit( item_t *wpn );
long	calc_per_pow_up_wpn_crtcl( item_t *wpn );
long	calc_per_pow_up_wpn_dam( item_t *wpn );
long	calc_per_pow_up_wpn( item_t *wpn );
long	calc_per_pow_up_armor_def( item_t *armor );
long	calc_per_pow_up_armor_crtcl( item_t *armor );
long	calc_per_pow_up_armor_ac( item_t *armor );
long	calc_per_pow_up_armor( item_t *armor );
bool_t	protect_armor( item_t *armor );
void	fx_cast_spell( chr_t *chr, spell_tab_t *tab );
void	fx_word_of_destruction( chr_t *chr, spell_tab_t *tab );
bool_t	rub_lamp( chr_t *chr, item_t *item );
bool_t	fx_wish( chr_t *chr, wish_level_t wish_level );
bool_t	fx_wish_chk_price(
	chr_t *chr,
	wish_level_t wish_level,
	wish_kind_t kind
);
bool_t	fx_wish_exec(
	chr_t *chr,
	wish_level_t wish_level,
	wish_kind_t kind
);
bool_t	fx_wish_pay_price(
	chr_t *chr,
	wish_level_t wish_level,
	wish_kind_t kind
);
bool_t	chk_wish_price_exp( chr_t *chr, wish_kind_t kind );
bool_t	chk_wish_price_gold( chr_t *chr, wish_kind_t kind );
bool_t	chk_wish_price_contribution( chr_t *chr, wish_kind_t kind );
void	pay_wish_price_exp( chr_t *chr, wish_kind_t kind );
void	pay_wish_price_gold( chr_t *chr, wish_kind_t kind );
void	pay_wish_price_contribution( chr_t *chr, wish_kind_t kind );
long	calc_wish_price_exp( chr_t *chr, wish_kind_t kind );
gold_t	calc_wish_price_gold( chr_t *chr, wish_kind_t kind );
gold_t	calc_wish_price_contribution( chr_t *chr, wish_kind_t kind );
wish_kind_t	exec_menu_wish( mbr_t *mbr, wish_level_t wish_level );
char	*cb_menu_sel_wish( menu_t **pp, menu_t **dflt );
bool_t	fx_wish_armageddon( chr_t *chr, wish_level_t wish_level );
bool_t	fx_wish_cure_hp( chr_t *chr, wish_level_t wish_level );
bool_t	fx_wish_cure_mp( chr_t *chr, wish_level_t wish_level );
bool_t	fx_wish_resurrection( chr_t *chr, wish_level_t wish_level );
bool_t	fx_wish_artifact( chr_t *chr, wish_level_t wish_level );
bool_t	fx_wpn_randm_art_drain(
	char mnr,
	chr_t *o_p, chr_t *d_p,
	long o_dam, bool_t flg_throw
);
bool_t	fx_wpn_randm_art_drain_hp(
	chr_t *o_p, chr_t *d_p,
	long o_dam, bool_t flg_throw
);
bool_t	fx_wpn_randm_art_drain_mp(
	chr_t *o_p, chr_t *d_p,
	long o_dam, bool_t flg_throw
);
bool_t	fx_wpn_randm_art_drain_exp(
	chr_t *o_p, chr_t *d_p,
	long o_dam, bool_t flg_throw
);
bool_t	eat_food( chr_t *chr, item_t *item );
bool_t	chk_mnstr_catch_food( chr_t *chr, item_t *item );
bool_t	fx_mnstr_catch_food( chr_t *chr, item_t *item );
bool_t	smoke_tobacco( mbr_t *mbr, item_t *item );
void	inc_turn_smoke( mbr_t *mbr );
void	inc_day_smoke( mbr_t *mbr );
void	dispose_tobacco( mbr_t *mbr, item_t *item );
void	dispose_tobacco_sub( item_t *disposal, item_t *tobacco );
void	contribution( chr_t *chr, gold_t gold, gold_t spell_gold );
void	set_stomach( chr_t *chr );
void	digest( chr_t *chr );
void	take_meal_chr( chr_t *chr, rate_t rate );
void	take_meal_fill_chr( chr_t *chr );
bool_t	faint( chr_t *chr );
void	abstain( chr_t *chr );
void	fraternize( chr_t *chr );
bool_t	dec_infra_vision( chr_t *chr );
void	randm_teleport( chr_t *chr );
void	randm_teleport_party( chr_t *chr );
gold_t	fx_pick_gold( chr_t *o_p, chr_t *d_p, rate_t rate, long max_n );
void	catch_chr( mnstr_t *mnstr, chr_t *chr );
void	release_chr( mnstr_t *mnstr );
void	release_all_mbr( void );
void	release_chr_all_ref( chr_t *chr );
void	inc_chr_caught( chr_t *chr, long n );
blast_t	*get_blast_spell( spell_kind_t kind );
blast_t	*get_blast( blast_kind_t kind );
void	set_blast_size( blast_t *p );
flg_stat_t	cv_fx_kind_to_flg_stat( fx_kind_t fx_kind );
resi_kind_t	cv_fx_kind_to_resi_kind( fx_kind_t fx_kind );
void	lost_fx_chr( chr_t *chr );
void	lost_fx_chr_sub( chr_t *chr, fx_t *fx );
fx_t	*asgn_fx( fx_t *p );
void	free_fx( fx_t *p );
void	free_fx_all( fx_t *p );
void	ins_ls_fx( fx_t *ls, fx_t *p );
fx_t	*srch_fx( fx_t *ls, fx_kind_t kind );
void	check_memory_fx_c( void );

#ifdef __cplusplus
}
#endif
