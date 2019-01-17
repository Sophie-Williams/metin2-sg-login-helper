#include "../H/inc.h"
/**/
bool main_n::main_c::dbg_console( )
{
	AllocConsole( );
	SetConsoleTitle( "Account manager" );
	debug_n::debug_p->debug( "version 1.7 by Kichiro Hashimoto" );
	debug_n::debug_p->debug("source https://github.com/kichiro1337/metin2-sg-login-helper");
	return 1;
}
void main_n::main_c::startup( char *argca [ ] )
{
	if ( !main_n::main_p->dbg_console( ) ) ExitProcess( 0 );
	debug_n::debug_p->debug( "running startup " );
	debug_n::debug_p->debug( "preparing gamefiles" );
	std::string tmp = argca [ 0 ];
	auto pos = tmp.find_last_of( "\\" );
	if ( std::string::npos!=pos ) tmp.erase( 0 , pos+1 );
	files_n::file_p->setname( ( char* ) tmp.c_str( ) );
	files_n::file_p->setup( );
	alive_n::alive_p->setup( );
	discord_n::discord_p->setup( );
	auto ret = down_n::down_p->work( );
	if ( !ret )
	{
		debug_n::debug_p->debug( "unexpected error" );
		Sleep( 1000 );
		ExitProcess( 0 );
	}
}
void main_n::main_c::worker( )
{
	debug_n::debug_p->debug( ". . ." );
	Sleep( 2000 );
	system( "cls" );
start:
	std::cout<<"[-] enter command: ";
	auto cmdin = std::string( );
	std::cin>>cmdin;
	if ( cmdin=="help"||cmdin=="?" )
	{
		if ( main_n::main_p->debug ) debug_n::debug_p->debug( "help command receivied" );
		debug_n::debug_p->debug( "commands:" );
		debug_n::debug_p->debug( "'help' / '?' will list all commands" );
		debug_n::debug_p->debug( "'add' / 'new' will run the setup for a new account" );
		debug_n::debug_p->debug( "'button' will run the button setup again" );
		debug_n::debug_p->debug( "'list' will list all psuedos loaded" );
		debug_n::debug_p->debug( "'update' will check for updates of metin" );
		debug_n::debug_p->debug( "'discord' will list available discord presences" );
	}
	if ( cmdin=="button" )
	{
		debug_n::debug_p->debug( "running button setup" );
		files_n::file_p->setupbutton( );
	}
	if ( cmdin=="discord" )
	{
		auto tmp = std::string( );
		debug_n::debug_p->debug( "select presence" );
		debug_n::debug_p->debug( "0 - Metin2 SG" );
		debug_n::debug_p->debug( "1 - PornHub VR" );
		debug_n::debug_p->debug( "2 - ISIS" );
		std::cout<<"[-] selection: ";
		std::cin>>tmp;
		auto tmp_val = int( );
		tmp_val = atoi( tmp.c_str( ) );
		discord_n::discord_p->customsetup( tmp_val );
		Sleep( 1000 );
		system( "cls" );
		goto start;
	}
	if ( cmdin=="list" )
	{
		for ( auto &&acc:files_n::file_p->accs )
		{
			auto tmp = std::string( );
			if ( !acc.user.size( ) ) continue;
			tmp = acc.pseu;
			debug_n::debug_p->debug( std::string( "pseudo found: " ).append( tmp ) );
		}
	}
	if ( cmdin.size( )>0 )
	{
		for ( auto &&acc:files_n::file_p->accs )
		{
			auto tmp = std::string( );
			auto tmp_2 = std::string( );
			tmp = acc.pseu;
			tmp_2 = acc.user;
			if ( cmdin==tmp||cmdin==tmp_2 )
			{
				if ( !login_n::login_p->setup( acc ) )
				{
					debug_n::debug_p->debug( "login_n::login_p->setup´has failed" );
					Sleep( 2000 );
					system( "cls" );
					goto start;
				}
				if ( !login_n::login_p->work( ) )
				{
					debug_n::debug_p->debug( "login_n::login_p->work has failed" );
					Sleep( 2000 );
					system( "cls" );
					goto start;
				}
				debug_n::debug_p->debug( "login completed" );
				acc = login_n::login_p->cur_acc;
				Sleep( 1000 );
				system( "cls" );
				goto start;
			}
		}
	}
	if ( cmdin=="new"||cmdin=="add" )
	{
		debug_n::debug_p->debug( "adding new acc to list" );
		std::cout<<"[-] username: ";
		auto username = std::string( );
		std::cin>>username;

		std::cout<<"[-] password: ";
		auto password = std::string( );
		std::cin>>password;

		std::cout<<"[-] pseudo name: ";
		auto pseudo = std::string( );
		std::cin>>pseudo;

		std::ifstream iOrig;
		std::vector<std::string> sPreData;
		std::string sTmp;
		iOrig.open( "helper_cfg" );
		while ( getline( iOrig , sTmp ) )
		{
			sPreData.push_back( sTmp );
			sPreData.push_back( "\n" );
		}
		iOrig.close( );
		std::ofstream oFileStream;
		oFileStream.open( "helper_cfg" );
		std::string sCombo;
		sCombo.append( username );
		sCombo.append( "#" );
		sCombo.append( password );
		sCombo.append( "+" );
		sCombo.append( pseudo );

		for ( auto &&aObj:sPreData )
		{
			if ( strstr( aObj.c_str( ) , "+" )||strstr( aObj.c_str( ) , "#" )||strstr( aObj.c_str( ) , "=" ) )
			{
				if ( aObj.size( )>0 )
				{
					sCombo.append( "\n" );
					sCombo.append( aObj );
				}
			}
			else
				continue;
		}

		oFileStream<<sCombo;
		oFileStream.close( );

		debug_n::debug_p->debug( "added account" );

		files_n::acc tmpacc;
		tmpacc.user = username;
		tmpacc.pass = password;
		tmpacc.pseu = pseudo;

		files_n::file_p->accs.push_back( tmpacc );

		Sleep( 1000 );
		system( "cls" );
		goto start;
	}
	if ( cmdin=="update" )
	{
		debug_n::debug_p->debug( "checking for updates" );
		if ( down_n::down_p->work( ) )
			debug_n::debug_p->debug( "update success" );
		else
			debug_n::debug_p->debug( "up to date" );
		Sleep( 2000 );
	}
	goto start;
}
main_n::main_c* main_n::main_p;