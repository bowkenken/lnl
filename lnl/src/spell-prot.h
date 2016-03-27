/* spell.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_spell( void );
void	reset_static_spell( void );
void	init_spell_debug( void );
void	init_spell_new_mbr( long ls_mbr_n );
void	init_spell_dflt( void );
void	init_spell_nin( void );
void	reset_spell( void );
char	*cb_menu_sel_spell( menu_t **pp, menu_t **dflt );
char	*menu_sel_spell( mbr_t *mbr );
char	*cb_menu_reg_spell( menu_t **pp, menu_t **dflt );
char	*cb_menu_reg_spell_remark( menu_t **pp, menu_t **dflt );
char	*cb_menu_dflt_spell_mag( menu_t **pp, menu_t **dflt );
char	*cb_menu_dflt_spell_sor( menu_t **pp, menu_t **dflt );
char	*cb_menu_dflt_spell_enc( menu_t **pp, menu_t **dflt );
char	*cb_menu_dflt_spell_sum( menu_t **pp, menu_t **dflt );
char	*cb_menu_dflt_spell_pri( menu_t **pp, menu_t **dflt );
char	*cb_menu_dflt_spell_sha( menu_t **pp, menu_t **dflt );
char	*cb_menu_dflt_spell_bar( menu_t **pp, menu_t **dflt );
char	*cb_menu_dflt_spell_nin( menu_t **pp, menu_t **dflt );
char	*menu_dflt_spell( menu_t **pp, menu_t **dflt, abl_kind_t kind );
char	*cb_menu_spell_no_learn( menu_t **pp, menu_t **dflt );
char	*cb_menu_spell( menu_t **pp, menu_t **dflt );
char	*cb_menu_spell_extent( menu_t **pp, menu_t **dflt );
bool_t	get_spell_flg_trgt( spell_tab_t *tab, extent_kind_t ex );
char	*menu_spell_trgt( mbr_t *mbr );
void	chr_cast_spell( chr_t *chr, spell_tab_t *tab, const char *fmt );
void	play_sound_spell( chr_t *chr, spell_kind_t kind );
void	chr_cast_spell_normal(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate
);
void	chr_cast_spell_spread(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate
);
void	chr_cast_spell_blast(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate,
	long x, long y, trgt_kind_t trgt_kind, void *p
);
void	chr_cast_spell_mass(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate
);
void	chr_cast_spell_mass_mbr(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate
);
void	chr_cast_spell_mass_pet(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate
);
void	chr_cast_spell_mass_mnstr(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate
);
void	chr_cast_spell_mass_item(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate
);
void	chr_cast_spell_mass_door(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate
);
void	chr_cast_spell_mass_trap(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate
);
void	chr_cast_spell_sub(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate,
	long x, long y, trgt_kind_t trgt_kind, void *p
);
void	counter_magic(
	chr_t *chr, bool_t flg_item,
	spell_tab_t *tab, rate_t rate,
	long x, long y, trgt_kind_t trgt_kind, void *p
);
reg_spell_t	*get_reg_spell( long mbr_n );
void	set_reg_spell(
	long mbr_n,
	spell_tab_t *tab,
	extent_kind_t extent_kind,
	trgt_t trgt
);
void	lost_trgt_reg_spell( void *p );
bool_t	chk_spell( chr_t *o_p, spell_tab_t *tab, bool_t flg_item );
bool_t	chk_cast_spell_trgt( spell_kind_t spell, trgt_kind_t trgt );
fx_kind_t	cv_spell_to_fx( spell_kind_t spell );
flg_stat_t	cv_spell_to_stat( spell_kind_t spell );
bool_t	chk_bar_limit( chr_t *chr );
bool_t	chk_bar_limit_lev( chr_t *chr );
chr_kind_t	get_inst_spell_chr_kind( chr_t *chr, spell_kind_t kind );
bool_t	chk_can_chr_cast_stat( chr_t *chr );
bool_t	chk_can_chr_cast_lev( chr_t *chr, spell_kind_t kind );
bool_t	chk_chr_learned_spell( chr_t *chr, spell_kind_t kind );
bool_t	set_chr_learned_spell( chr_t *chr, spell_kind_t kind, bool_t flg );
bool_t	learn_spell_pri( chr_t *chr );
void	learn_spell_sha( chr_t *chr );
void	learn_spell_bar( chr_t *chr );
bool_t	chk_chr_learned_spell_nin(
	chr_t *chr, spell_kind_t kind,
	bool_t flg_test
);
bool_t	chk_learn_spell_item( chr_t *chr, spell_kind_t kind );
void	arrange_cast_tab_1( long trgt_ls_mbr_n, long d );
void	arrange_cast_tab( long trgt_ls_mbr_n, long d );
void	remove_cast_tab( long trgt_ls_mbr_n );
bool_t	copy_cast_tab( cast_tab_t dst[], cast_tab_t src[] );
char	*get_spell_vfx_str( spell_kind_t spell_kind );
cast_tab_t	*get_cast_tab( chr_t *chr, spell_kind_t kind );
char	*get_spell_name( spell_kind_t kind );
spell_tab_t	*get_spell_tab( spell_kind_t kind );
gold_t	get_price_spell( spell_kind_t kind );
void	check_memory_spell_c( void );

#ifdef __cplusplus
}
#endif
