/* request.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_request( void );
void	reset_static_request( void );
void	make_request_all( void );
request_t	*make_request_randm( void );
request_t	*make_request_rare_goods( request_t *req );
request_t	*make_request_tame_mnstr( request_t *req );
request_t	*make_request_rescue( request_t *req );
request_t	*make_request_tour_guide( request_t *req );
request_t	*make_request_exterminate( request_t *req );
request_t	*make_request_revenge( request_t *req );
request_t	*make_request_wanted_criminal( request_t *req );
bool_t	make_client( request_t *req, mnstr_kind_t kind, bool_t flg_now );
long	get_request_dun_max_lev_easy( void );
long	get_request_dun_max_lev_normal( void );
long	get_request_dun_max_lev( long dun_min_lev, long dun_max_lev );
void	set_request_dun_lev(
	request_t *req,
	long min_lev, long max_lev, long range_lev
);
n_msg_idx_t	get_ls_n_msg_idx_randm( n_msg_t ls[] );
request_t	*alloc_request( void );
void	free_request( request_t *req );
request_t	*get_request_ls( void );
long	get_request_n( void );
char	*get_request_kind_name( request_kind_t kind );
void	chk_request_limit( void );
bool_t	chk_request_limit_client( request_t *req );
void	chk_request_npc_contract( void );
void	chk_clr_request_npc_contract( void );
void	chk_set_request_npc_contract( void );
bool_t	set_request_msg( request_t *req );
void	set_request_msg_var(
	request_t *req,
	char *buf, long *buf_idx,
	char *fmt, long *fmt_idx
);
void	set_request_msg_var_dun_min_lev(
	request_t *req, char *buf, char *arg
);
void	set_request_msg_var_dun_max_lev(
	request_t *req, char *buf, char *arg
);
void	set_request_msg_var_dun_lev_range(
	request_t *req, char *buf, char *arg
);
void	set_request_msg_var_client(
	request_t *req, char *buf, char *arg
);
void	set_request_msg_var_rare_goods(
	request_t *req, char *buf, char *arg
);
void	set_request_msg_var_mnstr(
	request_t *req, char *buf, char *arg
);
void	set_request_msg_var_mnstr_n(
	request_t *req, char *buf, char *arg
);
void	set_request_msg_var_rescue_trgt(
	request_t *req, char *buf, char *arg
);
void	set_request_msg_var_client_family(
	request_t *req, char *buf, char *arg
);
void	set_request_msg_var_client_mate(
	request_t *req, char *buf, char *arg
);
void	set_request_msg_var_when_1(
	request_t *req, char *buf, char *arg
);
void	set_request_msg_var_when_2(
	request_t *req, char *buf, char *arg
);
void	set_request_msg_var_weapon(
	request_t *req, char *buf, char *arg
);
void	set_request_msg_var_ls(
	request_t *req, char *buf,
	n_msg_idx_t *n_msg_idx, n_msg_t ls_msg[],
	bool_t flg_quote
);
bool_t	set_request_heading( request_t *req );
bool_t	chr_contract_request(
	request_t *req,
	chr_kind_t kind, n_msg_idx_t n_idx_name, sex_t sex
);
void	chk_find_request_chr( chr_t *chr );
bool_t	finish_request( request_t *req );
bool_t	dont_finish_request( request_t *req );
void	chk_finish_request_chr_dead( chr_t *chr );
void	chk_finish_request_rare_goods( void );
bool_t	chk_finish_request_join( request_t *req, mnstr_t *npc );
void	chk_finish_request_exterminate(
	mnstr_kind_t mnstr_kind,
	long add,
	request_kind_t req_kind,
	bool_t flg_dec_add
);
bool_t	chk_finish_request_revenge( request_t *req, chr_t *chr );
bool_t	chk_finish_request_wanted_criminal( request_t *req );
void	close_all_request( chr_kind_t chr_kind );
bool_t	close_request( request_t *req, chr_kind_t chr_kind );
void	give_party_reward_item_randm();
bool_t	give_party_reward_item( item_t *item );
bool_t	chk_watch_request_client( request_t *req );
void	not_join_all_client( request_t *req, bool_t flg_success );
void	not_join_client( request_t *req, pet_t *npc, bool_t flg_success );
void	put_request_all_obj( void );
void	put_request_rare_goods( chr_t *chr );
void	put_request_item( void );
void	put_request_mnstr( void );
bool_t	is_client( chr_t *chr );
char	*cb_menu_request_mbr( menu_t **pp, menu_t **dflt );
char	*cb_menu_request_bar( menu_t **pp, menu_t **dflt );
char	*set_menu_request(
	menu_t **pp, menu_t **dflt,
	menu_call_back_t cb, bool_t flg_mbr
);
char	*cb_menu_sel_request_mbr( menu_t **pp, menu_t **dflt );
char	*cb_menu_sel_request_bar( menu_t **pp, menu_t **dflt );
char	*cb_menu_request_refresh( menu_t **pp, menu_t **dflt );
bool_t	ask_contract_request( request_t *req );
bool_t	ask_cancel_request( request_t *req );
char	*cv_idx_to_request_fmt( request_t *req );
char	*cv_idx_to_contract_name( request_t *req );
char	*cv_idx_to_client_name( request_t *req );
char	*cv_idx_to_mnstr_name( request_t *req );
char	*cv_idx_to_rescue_trgt_name( request_t *req );
char	*cv_idx_to_client_family_name( request_t *req );
char	*cv_idx_to_client_mate_name( request_t *req );
void	check_memory_request_c( void );

#ifdef __cplusplus
}
#endif
