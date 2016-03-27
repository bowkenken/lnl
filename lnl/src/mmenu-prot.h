/* mmenu.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_var_main_menu( void );
void	init_main_menu( void );
void	reset_static_main_menu( void );
char	*exec_menu_sel_mbr(
	mbr_t **mbr, char *ttl,
	bool_t flg_sel_dead, bool_t flg_sel_pet
);
char	*cb_menu_sel_mbr( menu_t **pp, menu_t **dflt );
char	*exec_menu_sel_abl( mbr_t *mbr, abl_kind_t *abl );
char	*cb_menu_sel_abl( menu_t **pp, menu_t **dflt );
char	*exec_menu_point_crsr( void );
char	*exec_menu_race( race_t *race );
char	*cb_menu_main_race( menu_t **pp, menu_t **dflt );
char	*cb_menu_sub_race( menu_t **pp, menu_t **dflt );
char	*exec_menu_sex( sex_t *sex );
char	*cb_menu_sex( menu_t **pp, menu_t **dflt );
char	*exec_menu_class( long *class_n );
char	*cb_menu_class( menu_t **pp, menu_t **dflt );
char	*exec_menu_sel_obj( trgt_kind_t *trgt_kind, pos_t pos );
char	*cb_menu_main_init( menu_t **pp, menu_t **dflt );
char	*cb_menu_exec( menu_t **pp, menu_t **dflt );
char	*cb_menu_auto_mark( menu_t **pp, menu_t **dflt );
char	*cb_menu_mark( menu_t **pp, menu_t **dflt );
char	*cb_menu_sel_obj_init( menu_t **pp, menu_t **dflt );
char	*cb_menu_sel_obj( menu_t **pp, menu_t **dflt );
char	*cb_menu_sel_obj_auto( menu_t **pp, menu_t **dflt );
bool_t	menu_switch_mark_mbr(
	trgt_kind_t trgt_kind_1, pos_t pos1,
	trgt_kind_t trgt_kind_2, pos_t pos2
);
bool_t	menu_switch_mark_mnstr(
	trgt_kind_t trgt_kind_1, pos_t pos1,
	trgt_kind_t trgt_kind_2, pos_t pos2
);
bool_t	menu_switch_mark_item(
	trgt_kind_t trgt_kind_1, pos_t pos1,
	trgt_kind_t trgt_kind_2, pos_t pos2
);
bool_t	menu_switch_mark_door(
	trgt_kind_t trgt_kind_1, pos_t pos1,
	trgt_kind_t trgt_kind_2, pos_t pos2
);
bool_t	menu_switch_mark_trap(
	trgt_kind_t trgt_kind_1, pos_t pos1,
	trgt_kind_t trgt_kind_2, pos_t pos2
);
bool_t	menu_switch_mark_square(
	trgt_kind_t trgt_kind_1, pos_t pos1,
	trgt_kind_t trgt_kind_2, pos_t pos2
);
bool_t	menu_switch_mark_pos(
	trgt_kind_t trgt_kind_1, pos_t pos1,
	trgt_kind_t trgt_kind_2, pos_t pos2
);
bool_t	menu_mark_mbr( pos_t pos1, pos_t pos2 );
bool_t	menu_mark_mnstr( pos_t pos1, pos_t pos2 );
bool_t	menu_mark_item( pos_t pos1, pos_t pos2 );
char	*cb_menu_mark_item( menu_t **pp, menu_t **dflt );
bool_t	menu_mark_door( pos_t pos1, pos_t pos2 );
char	*cb_menu_mark_door( menu_t **pp, menu_t **dflt );
bool_t	menu_mark_trap( pos_t pos1, pos_t pos2 );
char	*cb_menu_mark_trap( menu_t **pp, menu_t **dflt );
bool_t	menu_mark_square( pos_t pos1 );
bool_t	menu_mark_pos( pos_t pos1, pos_t pos2 );
bool_t	menu_mark_square_pos( pos_t pos );
char	*menu_dist_mbr( void );
char	*menu_dist_mnstr( void );
char	*cb_menu_dist_init( menu_t **pp, menu_t **dflt );
char	*cb_menu_dist( menu_t **pp, menu_t **dflt );
char	*cb_menu_dist_act( menu_t **pp, menu_t **dflt );
char	*cb_menu_item( menu_t **pp, menu_t **dflt );
char	*cb_menu_item_init( menu_t **pp, menu_t **dflt );
char	*cb_menu_item_sel( menu_t **pp, menu_t **dflt );
char	*cb_menu_item_sel_init( menu_t **pp, menu_t **dflt );
char	*menu_item_sel_init_dead( menu_t **pp, menu_t **dflt );
char	*cb_menu_item_use( menu_t **pp, menu_t **dflt );
char	*cb_menu_item_zap( menu_t **pp, menu_t **dflt );
char	*cb_menu_item_smoke( menu_t **pp, menu_t **dflt );
char	*cb_menu_item_fill_lamp( menu_t **pp, menu_t **dflt );
char	*cb_menu_item_ready_throw( menu_t **pp, menu_t **dflt );
char	*cb_menu_item_send( menu_t **pp, menu_t **dflt );
char	*cb_menu_item_receive( menu_t **pp, menu_t **dflt );
char	*cb_menu_item_put_in_chest( menu_t **pp, menu_t **dflt );
char	*cb_menu_item_ls_chest( menu_t **pp, menu_t **dflt );
char	*cb_menu_chest_sel( menu_t **pp, menu_t **dflt );
char	*cb_menu_item_drop( menu_t **pp, menu_t **dflt );
char	*cb_menu_item_alias( menu_t **pp, menu_t **dflt );
char	*cb_menu_item_chk( menu_t **pp, menu_t **dflt );
char	*cb_menu_goto_equip( menu_t **pp, menu_t **dflt );
long	get_equip_ttl_max_len( void );
char	*cb_menu_equip( menu_t **pp, menu_t **dflt );
char	*cb_menu_equip_init( menu_t **pp, menu_t **dflt );
char	*cb_menu_equip_sel( menu_t **pp, menu_t **dflt );
char	*cb_menu_equip_sel_init( menu_t **pp, menu_t **dflt );
char	*cb_menu_equip_wear_sel_self( menu_t **pp, menu_t **dflt );
char	*cb_menu_equip_wear_sel_other( menu_t **pp, menu_t **dflt );
char	*menu_equip_wear_sel( menu_t **pp, menu_t **dflt );
char	*cb_menu_equip_wear_init( menu_t **pp, menu_t **dflt );
char	*cb_menu_equip_wear( menu_t **pp, menu_t **dflt );
char	*cb_menu_equip_take_off_self( menu_t **pp, menu_t **dflt );
char	*cb_menu_equip_take_off_other( menu_t **pp, menu_t **dflt );
char	*menu_equip_take_off( menu_t **pp, menu_t **dflt );
char	*cb_menu_goto_item( menu_t **pp, menu_t **dflt );
char	*cb_menu_move( menu_t **pp, menu_t **dflt );
void	menu_move_square( void );
char	*cb_menu_fight( menu_t **pp, menu_t **dflt );
char	*cb_menu_load_wiz( menu_t **pp, menu_t **dflt );
char	*cb_menu_save_wiz( menu_t **pp, menu_t **dflt );
void	menu_load_wiz( void );
void	menu_save_wiz( void );
bool_t	menu_load( bool_t flg_txt, bool_t flg_new_game );
bool_t	menu_save( bool_t flg_txt );
bool_t	menu_save_n( bool_t flg_txt, long save_n );
long	menu_sel_save_load(
	bool_t flg_save, bool_t flg_txt, bool_t flg_new_game
);
void	set_ttl_menu_save_load(
	menu_t *ls, bool_t flg_save, bool_t flg_txt
);
char	*cb_menu_save_load( menu_t **pp, menu_t **dflt );
char	*cb_menu_new_game( menu_t **pp, menu_t **dflt );
void	set_flg_no_save( bool_t flg );
bool_t	get_flg_no_save( void );
bool_t	exec_menu_identify_item( mbr_t *mbr );
char	*cb_menu_identify_item( menu_t **pp, menu_t **dflt );
char	*cb_menu_identify_item_no_sel( menu_t **pp, menu_t **dflt );
bool_t	exec_menu_resurrection( mbr_t *mbr );
char	*cb_menu_resurrection( menu_t **pp, menu_t **dflt );
menu_t	*get_ls_menu_main( void );
menu_t	*get_ls_menu_sel_obj( void );
menu_t	*get_menu_dflt_main( void );
void	set_menu_dflt_main( menu_t *p );
void	update_crsr( void );
pos_t	*get_main_crsr( void );
pos_t	*get_pre_main_crsr( void );
pos_t	*get_sub_crsr( void );
pos_t	*get_pre_sub_crsr( void );
long	get_sel_mbr_n( void );
void	set_sel_mbr_n( long n );
void	check_memory_mmenu_c( void );

#ifdef __cplusplus
}
#endif
