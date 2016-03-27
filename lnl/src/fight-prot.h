/* fight.c */

#ifdef __cplusplus
extern "C" {
#endif

void	reset_static_fight( void );
bool_t	fight_bash( chr_t *chr, chr_t *chr2, attack_t *dflt_attack );
bool_t	set_attack_chr_bash(
	chr_t *chr, attack_t *attack, long range, bool_t flg_ave
);
bool_t	set_attack_mbr_bash(
	mbr_t *mbr, attack_t *attack, long range, bool_t flg_ave
);
bool_t	set_attack_mnstr_bash(
	mnstr_t *mnstr, attack_t *attack, long range, bool_t flg_ave
);
bool_t	fight_throw( chr_t *o_p, chr_t *d_p, attack_t *dflt_attack );
bool_t	chk_fight_zap( mbr_t *mbr );
bool_t	fight_zap( mbr_t *mbr );
bool_t	set_attack_chr_throw(
	chr_t *chr, attack_t *attack, long range, bool_t flg_ave
);
bool_t	set_attack_mbr_throw(
	mbr_t *mbr, attack_t *attack, long range, bool_t flg_ave
);
bool_t	set_attack_mnstr_throw(
	mnstr_t *mnstr, attack_t *attack, long range, bool_t flg_ave
);
attack_t	*get_attack(
	bool_t flg_ave, attack_t *ls, long range,
	bool_t flg_bash, bool_t flg_monk,
	bool_t flg_throw, bool_t flg_spell
);
attack_t	*get_attack_ave(
	attack_t *ls, long range,
	bool_t flg_bash, bool_t flg_monk,
	bool_t flg_throw, bool_t flg_spell
);
attack_t	*get_attack_randm(
	attack_t *ls, long range,
	bool_t flg_bash, bool_t flg_monk,
	bool_t flg_throw, bool_t flg_spell
);
ratio_t	calc_attack_sum(
	attack_t *ls,
	bool_t flg_bash, bool_t flg_monk,
	bool_t flg_throw, bool_t flg_spell
);
bool_t	fight(
	chr_t *o_p, chr_t *d_p,
	const attack_t *attack, long range
);
long	calc_attack_n( chr_t *o_p, const attack_t *attack );
long	calc_attack_n_fig( chr_t *o_p, const attack_t *attack );
long	calc_attack_n_mon( chr_t *o_p, const attack_t *attack );
long	calc_attack_n_hun( chr_t *o_p, const attack_t *attack );
long	calc_counter_n( chr_t *d_p );
long	calc_two_sword_fencing_n( chr_t *o_p, const attack_t *attack );
bool_t	fight_x_1(
	chr_t *o_p, chr_t *d_p,
	const attack_t *attack, long range,
	bool_t flg_counter
);
bool_t	fight_two_sword_fencing(
	chr_t *o_p, chr_t *d_p,
	const attack_t *attack, long range
);
bool_t	fight_counter( chr_t *o_p, chr_t *d_p );
bool_t	spell_attack(
	chr_t *o_p, chr_t *d_p,
	resi_kind_t resi, bool_t flg_stick,
	abl_kind_t abl, rate_t rate
);
void	added_fx( chr_t *chr, resi_kind_t resi );
void	added_fx_wpn_randm_art(
	chr_t *o_p, chr_t *d_p,
	bool_t flg_throw
);
void	added_fx_wpn_randm_art_item(
	chr_t *o_p, chr_t *d_p,
	item_t *item
);
void	fight_fx( chr_t *o_p, chr_t *d_p, const attack_t *attack );
bool_t	chr_break_door( chr_t *chr, long dr_n );
bool_t	chr_break_trap( chr_t *chr, trap_t *trap );
bool_t	chr_break_item( chr_t *chr, item_t *item );
bool_t	chk_bane( chr_t *o_p, chr_t *d_p, bool_t flg_throw );
bool_t	chk_killer( chr_t *o_p, chr_t *d_p, bool_t flg_throw );
bool_t	chk_slayer( chr_t *o_p, chr_t *d_p, bool_t flg_throw );
bool_t	chk_guard( chr_t *o_p, chr_t *d_p, bool_t flg_throw );
bool_t	chk_block( chr_t *o_p, chr_t *d_p, bool_t flg_throw );
bool_t	chk_protect( chr_t *o_p, chr_t *d_p, bool_t flg_throw );
bool_t	chk_magic_protect( chr_t *o_p, chr_t *d_p, bool_t flg_throw );
long	get_hit( chr_t *p, const attack_t *attack );
long	get_dam( chr_t *p, const attack_t *attack );
long	get_def( chr_t *p );
abl_kind_t	get_def_abl( chr_t *p );
long	get_armor_def( chr_t *p, abl_kind_t abl );
long	get_ac( chr_t *p );
rate_t	get_crtcl( chr_t *o_p, chr_t *d_p, const attack_t *attack );
rate_t	get_wpn_crtcl( chr_t *p, const attack_t *attack );
rate_t	get_armor_crtcl( chr_t *p );
bool_t	chk_ninja_crtcl( chr_t *o_p, chr_t *d_p );
rate_t	add_hit( long n );
rate_t	add_wpn_crtcl( long n );
rate_t	add_dam( long n );
rate_t	add_dam_two_handed_wpn( mbr_t *mbr, item_t *wpn );
rate_t	add_def( long n );
rate_t	add_armor_crtcl( long n );
rate_t	add_ac( long n );
long	get_dam_stick( chr_t *p );
long	get_dam_spell( chr_t *p, abl_kind_t abl_main, abl_kind_t abl_sub );
rate_t	get_resi_def( chr_t *p, resi_kind_t resi );
rate_t	get_chr_throw_range_rate( chr_t *o_p, chr_t *d_p );
rate_t	get_throw_range_rate( long x1, long y1, long x2, long y2 );
char	*get_msg_attack( const attack_t *attack );
void	check_memory_fight_c( void );

#ifdef __cplusplus
}
#endif
