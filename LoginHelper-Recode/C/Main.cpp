#include "../H/inc.h"
/**/
int main( int arg , char *argca [ ] )
{
	main_n::main_p = new main_n::main_c( );
	debug_n::debug_p = new debug_n::debug_c( );
	files_n::file_p = new files_n::filework_c( );
	game_n::game_p = new game_n::game_c( );
	alive_n::alive_p = new alive_n::alive_c( );
	discord_n::discord_p = new discord_n::discord_c( );
	down_n::down_p = new down_n::down_c( );
	login_n::login_p = new login_n::login_c( );

	main_n::main_p->startup( argca );
	main_n::main_p->worker( );
}