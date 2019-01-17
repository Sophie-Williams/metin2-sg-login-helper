#include "..//..//..//H/inc.h"
bool down_n::down_c::download( std::string pth , char* out , bool force )
{
	if ( !this->exists||force )
	{
		auto res = URLDownloadToFile( 0 , "http://patch.metin2sg.com/0.0.0.2/crclist.ver" , out , 0 , 0 );
		if ( SUCCEEDED( res ) ) return 1;
		else return 0;
	}
	else
	{
		std::ifstream file( out );
		if ( !file.is_open( ) ) return 0;
		auto tmp = std::string( );
		std::vector<std::string> content;
		while ( std::getline( file , tmp ) )
			content.push_back( tmp );
		this->cachedata = content;
		return 1;
	}
}
bool down_n::down_c::update( )
{
	std::ifstream binary( main_n::main_p->binpath );
	//this->preupdate = files_n::file_p->gethash( binary );
	binary.close( );
	debug_n::debug_p->debug( "game files outdated please update metin2" );
	debug_n::debug_p->debug( "open a new game instance once finished!" );
	debug_n::debug_p->debug( "waiting for update to finish ..." );
	auto patcher = files_n::file_p->path;
	patcher.append( "metin2.exe" );
	ShellExecuteA( NULL , "open" , patcher.c_str( ) , NULL , NULL , SW_SHOWDEFAULT );
	auto oldsize = game_n::game_p->instances.size( );
	while ( oldsize==game_n::game_p->instances.size( ) )
		game_n::game_p->refreshlist( );
	Sleep( 500 );
	debug_n::debug_p->debug( "updated!" );
	Sleep( 500 );
	SetWindowText( game_n::game_p->lasthwnd , "old pre update instance" );
	DeleteFile( "ver" );
	DeleteFile( "ver_" );
	DeleteFile( "metin2client.exe" );
	system( "cls" );
	binary.close( );
	ShellExecuteA( NULL , "open" , files_n::file_p->getpathself( ) , NULL , NULL , SW_SHOWDEFAULT );
	ExitProcess( 0 );
}
bool down_n::down_c::work( )
{
	this->cachedata = { };
	this->exists = 0;
	auto tmp = std::string( );
	auto pth = std::string( files_n::file_p->getdirpath( ) ); pth.append( "ver" );
	std::ifstream file( "ver" );
	if ( !file.is_open( ) ) this->exists = 0;
	if ( file.good( ) ) this->exists = 1;
	file.close( );
	auto ret = this->download( pth , "ver" );
	if ( this->exists )
	{
		debug_n::debug_p->debug( "checking for metin updates since first cache" );
		auto pth_update = std::string( files_n::file_p->getdirpath( ) );
		pth_update.append( "ver_" );
		auto ret_update = this->download( pth_update , "ver_" , 1 );
		if ( ret_update )
		{
			std::ifstream file( "ver_" );
			if ( !file.is_open( ) ) return 0;
			std::vector<std::string> content;
			while ( std::getline( file , tmp ) )
				content.push_back( tmp );
			file.close( );
			if ( this->cachedata==content )
			{
				DeleteFile( "ver_" );
				debug_n::debug_p->debug( "metin2 is up to date" );
				Sleep( 500 );
				return 1;
			}
			else this->update( );
		}
	}
	else if ( ret&&!this->exists )
	{
		debug_n::debug_p->debug( "caching version info" );
		Sleep( 1000 );
		system( "cls" );
		return 1;
	}
}
down_n::down_c* down_n::down_p;