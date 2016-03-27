/* play-rep.c */

#ifdef __cplusplus
extern "C" {
#endif

void	init_playing_report( void );
void	update_playing_report_paying_gold(
	long ls_mbr_n, gold_t gold
);
void	update_playing_report_staying_inn_mbr(
	long ls_mbr_n, stay_inn_kind_t kind
);
void	update_playing_report_staying_inn_party(
	stay_inn_kind_t kind
);
void	update_playing_report_wearing_equip(
	long ls_mbr_n, equip_kind_t kind
);
void	update_playing_report_making_dam(
	long ls_mbr_n, resi_kind_t kind, long dam
);
void	update_playing_report_made_dam(
	long ls_mbr_n, resi_kind_t kind, long dam
);
void	update_playing_report_using_spell(
	long ls_mbr_n, spell_kind_t kind
);
void	update_playing_report_used_spell(
	long ls_mbr_n, spell_kind_t kind
);
void	arrange_playing_report_1( long n, long d );
void	arrange_playing_report( long n, long d );
playing_report_t	*get_playing_report_mbr( long ls_mbr_n );
playing_report_t	*get_playing_report_party( void );
void	check_memory_play_rep_c( void );

#ifdef __cplusplus
}
#endif
