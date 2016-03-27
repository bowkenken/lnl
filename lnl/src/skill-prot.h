/* skill.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_skill( void );
void	init_skill_group_tab( void );
rate_t	calc_skill_rate( mbr_t *mbr, skill_kind_t skill_kind );
rate_t	calc_skill_sub_rate(
	mbr_t *mbr,
	skill_kind_t main_kind,
	skill_kind_t sub_kind
);
long	calc_skill_siege_mbr_n( mbr_t *mbr );
long	calc_skill_phalanx_mbr_n( mbr_t *mbr );
const char	*get_skill_hint( skill_kind_t skill_kind );
bool_t	chk_ena_skill( mbr_t *mbr, skill_kind_t skill_kind );
const char	*get_skill_name_from_slot( mbr_t *mbr, long skill_n );
const char	*get_skill_name_from_kind( skill_kind_t skill_kind );
long	get_skill_lev_from_slot( mbr_t *mbr, long skill_n );
long	get_skill_exp_from_slot( mbr_t *mbr, long skill_n );
long	get_skill_need_exp_from_slot( mbr_t *mbr, long skill_n );
bool_t	add_skill_group_tab(
	skill_group_kind_t group_kind,
	skill_kind_t skill_kind
);
bool_t	clr_skill_to_class( long class_n, long skill_n );
bool_t	set_skill_to_class( long class_n, long skill_n, skill_kind_t kind );
skill_kind_t	get_skill_from_class( long class_n, long skill_n );
skill_tab_t	*get_skill_n_tab( skill_kind_t kind );
skill_tab_t	*get_skill_tab( void );
skill_kind_t	get_skill_kind_from_group(
	skill_group_kind_t kind, long n
);
const char	*get_skill_group_name( skill_group_kind_t kind );
rate_t	calc_skill_exp_rate( class_t *p, skill_kind_t skill_kind );
skill_kind_t	cv_resi_to_skill_dam( resi_kind_t resi );
skill_kind_t	cv_resi_to_skill_resi( resi_kind_t resi );
skill_kind_t	cv_stat_to_skill_stat( flg_stat_t stat );
void	check_memory_skill_c( void );

#ifdef __cplusplus
}
#endif
