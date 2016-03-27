/* replay.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_replay( void );
void	reset_static_replay( void );
void	reset_replay( long n );
void	reset_replay_slot( replay_slot_t sn );
bool_t	chk_reg_replay( long n );
void	bgn_reg_replay( long n );
void	bgn_reg_replay_play( void );
void	end_reg_replay( long n );
bool_t	set_replay_str(
	replay_kind_t kind, char *str
);
bool_t	set_replay_str_slot(
	replay_kind_t kind, replay_slot_t sn, char *str
);
bool_t	set_replay_char(
	replay_kind_t kind, long c
);
bool_t	set_replay_char_slot(
	replay_kind_t kind, replay_slot_t sn, long c
);
bool_t	ready_replay( replay_slot_t sn, bool_t flg_break );
bool_t	get_draw_replay( char *buf, long *idx, long *len );
void	get_draw_replay_gui( char *buf, long len );
void	chk_replay_key( long c );
long	get_replay_key( void );
long	get_replay_next_key( replay_t **pp, long *idx );
bool_t	get_flg_play_replay( void );
void	set_flg_play_replay( bool_t flg );
char	*get_msg_replay_kind( replay_t *p );
replay_slot_t	cv_slot_n( long n );
long	get_replay_randm_seed( long n );
long	get_replay_save_n( void );
replay_t	*get_replay_head( long n );
replay_t	*alloc_replay( void );
void	free_replay( replay_t *p );
void	check_memory_replay_c( void );

#ifdef __cplusplus
}
#endif
