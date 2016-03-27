/* main-iphone.cpp */

#ifdef __cplusplus
extern "C" {
#endif

void	init_iphone( int argc, char **argv, UIWindow *window );
void    gexit( long code );
void    *main_thread( void *p );
void	alloc_autorelease_pool( void );
void	release_autorelease_pool( void );
void	init_iphone_gui( int argc, char **argv );
void	init_iphone_cui( int argc, char **argv );
void	init_iphone_cui_mouse( int argc, char **argv );
void	*main_thread_cui( void *p );
void	ena_timer( void );
void	init_main_sel_conf( GraphConf *cnf );
void	init_main_win( void );
void	closeGameGui();
void	guiMapPrintStatBarHint( void );
void	printMapStatBar( const char *s, ... );
void	configure_map( void );

#ifdef __cplusplus
}
#endif
