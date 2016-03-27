/* main-dows.cpp */

#ifdef __cplusplus
extern "C" {
#endif

int	main_dows( int argc, char **argv );
void	init_main_sel_conf( void *cnf );
void	closeGameGui();
void	guiMapPrintStatBarHint( void );
void	printMapStatBar( const char *s, ... );
void	gexit( long code );
void	*main_thread( void *p );
int	main( int argc, char **argv );

#ifdef __cplusplus
}
#endif
