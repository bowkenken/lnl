/* mnstr-act.c */

#ifdef __cplusplus
extern "C" {
#endif

void	reset_static_mnstr_act( void );
void	set_act_mnstr_std( mnstr_t *p );
void	set_act_mnstr_cubus( mnstr_t *p, sex_t sex );
void	set_act_mnstr_metamorphose(
	mnstr_t *p, mnstr_kind_t kind, rate_t rate
);
void	set_act_mnstr_towner( mnstr_t *p );
void	set_act_towner_enter_door( mnstr_t *p );
void	set_act_towner_exit_door( mnstr_t *p );
void	set_act_mnstr_friendly( mnstr_t *p );
bool_t	set_act_tame_mnstr( mnstr_t *p );
bool_t	set_act_rescue_trgt( mnstr_t *p );
void	set_act_mnstr_phoenix( mnstr_t *p );
void	set_act_mnstr_unicorn( mnstr_t *p );
void	set_act_mnstr_leprechaun( mnstr_t *p );
void	set_act_mnstr_venus_fly_trap( mnstr_t *p );
void	set_act_mnstr_slime( mnstr_t *p );
void	set_act_mnstr_spore( mnstr_t *p );
void	set_act_mnstr_giant_rat( mnstr_t *p );
void	set_act_mnstr_giant_spider( mnstr_t *p );
void	set_act_mnstr_werewolf( mnstr_t *p );
void	set_act_mnstr_gigantic_centipede( mnstr_t *p );
void	set_act_mnstr_gargoyle( mnstr_t *p );
void	set_act_mnstr_mimic( mnstr_t *p );
void	set_act_mnstr_vampire( mnstr_t *p );
void	set_act_mnstr_incubus( mnstr_t *p );
void	set_act_mnstr_succubus( mnstr_t *p );
void	set_act_mnstr_exel( mnstr_t *p );
void	set_act_mnstr_exeler( mnstr_t *p );
void	set_act_mnstr_xex( mnstr_t *p );
void	set_act_mnstr_xx( mnstr_t *p );
void	check_memory_mnstr_act_c( void );

#ifdef __cplusplus
}
#endif
