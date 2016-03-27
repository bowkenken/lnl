/* pet.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_pet( void );
void	reset_static_pet( void );
void	init_pet_dflt( void );
void	init_pet_debug( void );
pet_t	*make_pet( long dun_lev, pet_kind_t pet_kind, chr_t *owner );
pet_t	*make_pet_alloc( pet_t *p, long dun_lev, pet_kind_t pet_kind );
void	new_pet( pet_t *pet );
bool_t	reset_pet_resi( pet_t *pet );
void	clr_map_all_pet( void );
void	set_map_all_pet( void );
void	appear_all_pet( void );
void	appear_pet( pet_t *p );
void	move_phase_all_pet( void );
void	act_phase_all_pet( void );
void	dismissal_phase_all_pet( void );
void	set_act_pet_std( pet_t *p );
void	pet_mark_std( pet_t *p );
void	chk_trap_all_pet( void );
long	next_ls_pet_n( long n, long add );
pet_t	**get_party_pet( void );
pet_t	**get_ls_pet( void );
pet_t	*get_pet( long x, long y );
long	get_pet_n( pet_t *pet );
long	get_pet_ls_n( pet_t *pet );
pet_t	*get_npc_request( request_t *req );
void	clr_pet_owner( pet_t *p );
void	chk_pet_owner( pet_t *p );
bool_t	chk_can_join_pet( pet_t *p );
bool_t	chk_can_not_join_pet( pet_t *p );
bool_t	join_pet( pet_t *p );
bool_t	not_join_pet( pet_t *p );
void	garbage_collection_all_pet( void );
void	die_pet( pet_t *p, bool_t flg_msg );
void	remove_pet( pet_t *p );
bool_t	dismissal( pet_t *p );
long	calc_pet_n( void );
void	check_memory_pet_c( void );

#ifdef __cplusplus
}
#endif
