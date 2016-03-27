/* amenu.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_auto_menu( void );
void	reset_static_auto_menu( void );
void	reset_ls_flg_ena_auto_mark();
void	init_auto_mark_all_appoint( void );
void	init_auto_mark_appoint( long ls_mbr_n );
void	init_auto_mark_all_mbr( void );
void	init_auto_mark_mbr( long ls_mbr_n );
void	init_auto_mark_new_mbr( long ls_mbr_n );
void	set_dflt_auto_mark_mbr( long ls_mbr_n );
void	set_dflt_auto_mark( long ls_mbr_n, auto_mark_t ls[] );
auto_mark_t	*srch_dflt_auto_mark( long ls_mbr_n, dflt_auto_mark_t n );
void	ver_up_auto_mark_1_0_4( long ls_mbr_n );
void	ver_up_auto_mark_1_1_1( long ls_mbr_n );
void	ver_up_auto_mark_1_1_3( void );
void	ver_up_auto_mark_1_2_35( void );
void	ver_up_auto_mark_1_2_36( void );
void	cv_msg_ttl_auto_mark( char *ttl );
char	*menu_auto_mark( menu_t **pp, menu_t **dflt );
void	set_menu_auto_mark( menu_t **dflt );
char	*cb_menu_auto_mark_sel_edit( menu_t **pp, menu_t **dflt );
void	set_menu_auto_mark_sel_edit( menu_t **dflt );
char	*cb_menu_auto_mark_sel_edit_sel( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark_exec( menu_t **pp, menu_t **dflt );
void	set_auto_mark_cont( mbr_t *mbr );
bool_t	exec_menu_auto_mark( mbr_t *mbr );
bool_t	exec_menu_auto_mark_mnstr( mbr_t *mbr );
bool_t	exec_menu_auto_mark_item( mbr_t *mbr );
bool_t	exec_menu_auto_mark_door( mbr_t *mbr );
bool_t	exec_menu_auto_mark_trap( mbr_t *mbr );
bool_t	exec_menu_auto_mark_mbr( mbr_t *mbr );
char	*cb_menu_auto_mark_edit( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark_edit_init(
	menu_t **pp, menu_t **dflt
);
char	*cb_menu_auto_mark_position( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark_trgt_init(
	menu_t **pp, menu_t **dflt
);
char	*cb_menu_auto_mark_trgt( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark_dist_init(
	menu_t **pp, menu_t **dflt
);
char	*cb_menu_auto_mark_dist( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark_act_init( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark_act( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark_cond_init(
	menu_t **pp, menu_t **dflt
);
char	*cb_menu_auto_mark_cond( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark_appoint_item(
	menu_t **pp, menu_t **dflt
);
char	*set_menu_auto_mark_appoint_item(
	menu_t *ls, long *k, char mjr_key,
	auto_mark_appoint_item_t **apo
);
char	*cb_menu_auto_mark_appoint_item_init(
	menu_t **pp, menu_t **dflt
);
char	*cb_menu_auto_mark_appoint_item_mnr(
	menu_t **pp, menu_t **dflt
);
char	*cb_menu_auto_mark_edit_macro_bind( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark_edit_macro_reg_macro(
	menu_t **pp, menu_t **dflt
);
char	*cb_menu_auto_mark_cont( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark_priority( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark_copy_large( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark_paste_large( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark_copy_small( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark_paste_small( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark_edit_name( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark_remove( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark_arrange_up( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark_arrange_down( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark_arrange_top( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark_arrange_bottom( menu_t **pp, menu_t **dflt );
char	*menu_auto_mark_arrange_1( long n, long d );
char	*menu_auto_mark_arrange( long n, long d );
bool_t	arrange_auto_mark_1( long n, long d );
bool_t	arrange_auto_mark( long n, long d );
bool_t	arrange_auto_mark_mbr_1( long n, long d );
bool_t	arrange_auto_mark_mbr( long ls_mbr_n, long d );
bool_t	remove_auto_mark_mbr( long ls_mbr_n );
bool_t	chk_dup_dflt_auto_mark( dflt_auto_mark_t n );
char	*get_msg_menu_auto_mark_edit_position( mbr_t *mbr );
char	*get_msg_menu_auto_mark_edit_trgt( mbr_t *mbr );
char	*get_msg_menu_auto_mark_edit_dist( mbr_t *mbr );
char	*get_msg_menu_auto_mark_edit_act( mbr_t *mbr );
char	*get_msg_menu_auto_mark_edit_cond( mbr_t *mbr );
long	get_auto_mark_cur_n( void );
auto_mark_appoint_item_t	*get_auto_mark_appoint_item( mbr_t *mbr );
char	*get_msg_ttl_auto_mark_code( long n );
char	*get_msg_ttl_auto_mark_name( long n );
char	*get_msg_ttl_auto_mark_info( long n );
char	*get_msg_ttl_auto_mark_hint( long n );
auto_mark_t	*get_auto_mark(
	long ls_mbr_n, long auto_mark_n, position_kind_t position_kind
);
bool_t	chk_flg_ena_auto_mark( long n );
void	set_flg_ena_auto_mark( long n, bool_t flg );
auto_mark_appoint_item_t	*get_ls_auto_mark_appoint_item(
	long ls_mbr_n, long n
);
void	check_memory_amenu_c( void );

#ifdef __cplusplus
}
#endif
