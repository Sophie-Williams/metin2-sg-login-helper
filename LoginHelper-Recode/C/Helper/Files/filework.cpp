#include "..//..//..//H/inc.h"
void files_n::filework_c::setname( char* in )
{
	this->selfname = in;
	if ( main_n::main_p->debug ) debug_n::debug_p->debug( std::string( "file name " ).append( this->selfname ) );
}
std::string files_n::filework_c::getdirpath( )
{
	return this->path;
}
char* files_n::filework_c::getpathself( )
{
	return this->selfpath;
}
void files_n::filework_c::getpath( )
{
	auto base = GetModuleHandleA( NULL );
	if ( base )
	{
		GetModuleFileNameA( base , this->selfpath , ( sizeof( this->selfpath ) ) );

		if ( main_n::main_p->debug ) debug_n::debug_p->debug( std::string( "file path " ).append( this->selfpath ) );
	}
}
bool files_n::filework_c::is_metinfolder( )
{
	auto tmp = std::string( );
	auto tmp2 = std::string( );
	tmp = this->selfpath;
	tmp2 = this->selfname;
	if ( main_n::main_p->debug ) debug_n::debug_p->debug( "checking folder" );
	tmp.resize( tmp.size( )-tmp2.size( ) );
	if ( main_n::main_p->debug ) debug_n::debug_p->debug( std::string( "tmp2 " ).append( tmp2 ) );
	if ( main_n::main_p->debug ) debug_n::debug_p->debug( std::string( "sub selfname " ).append( tmp ) );
	this->path = tmp;
	std::ifstream bin( "metin2client.bin" );
	if ( bin.good( ) )
	{
		bin.close( );
		return 1;
	}
	else
	{
		debug_n::debug_p->debug( "running outside metin2 folder, closing" );
		system( "PAUSE" );
		bin.close( );
		ExitProcess( 0 );
	}
}
bool files_n::filework_c::getbin( )
{
	if ( this->is_metinfolder( ) )
	{
		auto tmp = this->path;
		tmp.append( "metin2client.bin" );
		main_n::main_p->binpath = tmp;
		if ( main_n::main_p->debug ) debug_n::debug_p->debug( std::string( "bin path " ).append( tmp ) );
		if ( main_n::main_p->binpath.size( )>0 )
			return 1;
		else
		{
			debug_n::debug_p->debug( "error while getting bin" );
			return 0;
		}
	}
	else
		return 0;
}
bool files_n::filework_c::makeexe( )
{
	if ( !this->path.size( ) ) return 0;
	auto tmp = this->path;
	main_n::main_p->exepath = tmp.append( "metin2client.exe" );
	if ( main_n::main_p->debug ) debug_n::debug_p->debug( std::string( "exe path " ).append( main_n::main_p->exepath ) );
	CopyFileA( main_n::main_p->binpath.c_str( ) , main_n::main_p->exepath.c_str( ) , TRUE );
	std::ifstream exe( "metin2client.exe" );
	Sleep( 100 );
	if ( exe.good( ) )
	{
		exe.close( );
		debug_n::debug_p->debug( "created quick launcher" );
		return 1;
	}
	else
	{
		exe.close( );
		debug_n::debug_p->debug( "failed creating quick launcher" );
		return 0;
	}
}
bool files_n::filework_c::loadaccs( )
{
	auto tmp = this->path;
	auto tmp_array = std::vector<std::string>( );
	auto tmp_product = std::string( );

	std::ifstream cfg( "helper_cfg" );
	if ( !cfg.is_open( ) ) return 0;
	while ( std::getline( cfg , tmp_product ) )
	{
		tmp_array.push_back( tmp_product );
	}
	cfg.close( );
	if ( tmp_array.size( )>0 )
	{
		for ( auto && object:tmp_array )
		{
			if ( strstr( object.c_str( ) , "#" ) )
			{
				files_n::acc tmpacc;
				auto pos = object.find_first_of( '#' );
				auto pseudo_pass = object.substr( pos+1 ) ,
					user = object.substr( 0 , pos );
				auto pos_pseudo = pseudo_pass.find_first_of( '+' );
				auto pseudo = pseudo_pass.substr( pos_pseudo+1 );
				auto pass = pseudo_pass.substr( 0 , pos_pseudo );
				if ( main_n::main_p->debug ) debug_n::debug_p->debug( std::string( "pseu: " ).append( pseudo ) );
				tmpacc.user = user;
				tmpacc.pass = pass;
				tmpacc.pseu = pseudo;
				this->accs.push_back( tmpacc );
			}
		}
		if ( this->accs.size( )>0 ) return 1;
	}
	else
	{
		debug_n::debug_p->debug( "account list empty use 'new' to add a account" );
		return 0;
	}
	return 1;
}
void files_n::filework_c::fetchmanaged( )
{
	for ( auto &&object:files_n::file_p->accs )
	{
		if ( !object.user.size( ) ) continue;
		for ( auto &&instance:game_n::game_p->instances )
		{
			if ( strstr( instance.title , object.user.c_str( ) ) )
			{
				debug_n::debug_p->debug( std::string( "found already managed account " ).append( object.user ) );
				Sleep( 500 );
				system( "cls" );
				object.ismanaged = 1;
				object.id = instance.id;
			}
			else
				continue;
		}
	}
}
bool files_n::filework_c::loadbutton( )
{
	auto tmp = this->path;
	auto tmp_array = std::vector<std::string>( );
	auto tmp_product = std::string( );

	std::ifstream cfg( "helper_cfg" );
	if ( !cfg.is_open( ) ) return 0;
	while ( std::getline( cfg , tmp_product ) )
	{
		tmp_array.push_back( tmp_product );
	}
	cfg.close( );
	if ( tmp_array.size( )>0 )
	{
		for ( auto && object:tmp_array )
		{
			if ( strstr( object.c_str( ) , "=" ) )
			{
				if ( main_n::main_p->debug ) debug_n::debug_p->debug( "button data found" );
				auto pos = object.find_first_of( '=' );
				auto x = object.substr( pos+1 ) ,
					y = object.substr( 0 , pos );
				auto x_int = atoi( x.c_str( ) );
				auto y_int = atoi( y.c_str( ) );
				files_n::file_p->button [ 0 ] = y_int;
				files_n::file_p->button [ 1 ] = x_int;
				if ( main_n::main_p->debug ) debug_n::debug_p->debug( std::string( x ).append( "x" ).append( y ) );
				debug_n::debug_p->debug( "button loaded" );
				return 1;
			}
		}
	}
	return 0;
}
bool files_n::filework_c::setupbutton( )
{
	auto test = 0;
	debug_n::debug_p->debug( "running button setup" );
	game_n::game_p->runclient( );
	for ( auto && object:game_n::game_p->instances )
	{
		if ( object.isold||object.used ) continue;
		if ( main_n::main_p->debug ) debug_n::debug_p->debug( "instance selected" );
		Sleep( 500 );
		if ( game_n::game_p->setfocus( object.hwnd ) )
		{
			object.used = 1;
			SetWindowPos( object.hwnd , HWND_TOP , 0 , 0 , 0 , 0 , SWP_NOSIZE );

			debug_n::debug_p->debug( "setup starting read carefully" );
			debug_n::debug_p->debug( "do not move the metin2 window while setting button position" );
			debug_n::debug_p->debug( "after pressing any key to continue you  will have to position the cursor on the  'OK' button inside of metin2" );
			debug_n::debug_p->debug( "once finished the game will close and restart trying to push the button" );
			debug_n::debug_p->debug( "you have 5 seconds to point the cursor to the 'OK' button" );
			system( "PAUSE" );
			Sleep( 5000 );
			auto pos = POINT( );
			GetCursorPos( &pos );
			files_n::file_p->button [ 0 ] = pos.x;
			files_n::file_p->button [ 1 ] = pos.y;
			debug_n::debug_p->debug( "button position recorded, running test" );
			game_n::game_p->killprocess( object.id );
			SetCursorPos( 0 , 0 );
			test = 1;
		}
	}
	if ( test )
	{
		game_n::game_p->runclient( );
		Sleep( 500 );
		for ( auto && newobject:game_n::game_p->instances )
		{
			if ( newobject.isold||newobject.used ) continue;
			if ( main_n::main_p->debug ) debug_n::debug_p->debug( "found new test instance" );
			if ( game_n::game_p->setfocus( newobject.hwnd ) )
			{
				if ( main_n::main_p->debug ) debug_n::debug_p->debug( "focused test instance" );
				newobject.used = 1;
				SetWindowPos( newobject.hwnd , HWND_TOP , 0 , 0 , 0 , 0 , SWP_NOSIZE );
				SetCursorPos( files_n::file_p->button [ 0 ] , files_n::file_p->button [ 1 ] );
				Sleep( 200 );
				POINT pos_cursor;
				HWND hwnd_outra_win;
				GetCursorPos( &pos_cursor );
				hwnd_outra_win = WindowFromPoint( pos_cursor );
				SendMessage( hwnd_outra_win , WM_LBUTTONDOWN , MK_LBUTTON , MAKELPARAM( pos_cursor.x , pos_cursor.y ) );
				SendMessage( hwnd_outra_win , WM_LBUTTONUP , 0 , MAKELPARAM( pos_cursor.x , pos_cursor.y ) );
				Sleep( 1000 );
				debug_n::debug_p->debug( "setup finished" );
				game_n::game_p->killprocess( newobject.id );

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
				sCombo.append( std::to_string( files_n::file_p->button [ 0 ] ) );
				sCombo.append( "=" );
				sCombo.append( std::to_string( files_n::file_p->button [ 1 ] ) );
				for ( auto &&aObj:sPreData )
				{
					if ( strstr( aObj.c_str( ) , "#" )||strstr( aObj.c_str( ) , "+" )||strstr( aObj.c_str( ) , "=" ) )
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

				return 1;
			}
		}
	}
	return 0;
}
/*loading routine*/
void files_n::filework_c::setup( )
{
	this->getpath( );
	if ( !this->getbin( ) )
	{
		debug_n::debug_p->debug( "filework failed at 0x1" );
		system( "PAUSE" );
		ExitProcess( 0 );
	}
	if ( !this->makeexe( ) )
	{
		debug_n::debug_p->debug( "filework failed at 0x2" );
		system( "PAUSE" );
		ExitProcess( 0 );
	}
	this->loadaccs( );
	game_n::game_p->refreshlist( );
	this->fetchmanaged( );
	this->loadbutton( );
	debug_n::debug_p->debug( "filework success" );
	this->done = 1;
	if ( files_n::file_p->button [ 0 ]==0||files_n::file_p->button [ 1 ]==0 )
	{
		debug_n::debug_p->debug( "no button saved, running setup" );
		this->setupbutton( );
	}
}
bool files_n::filework_c::reloadacc( )
{
	files_n::file_p->accs.clear( );
	return this->loadaccs( );
}
uint32_t files_n::filework_c::gethash( std::ifstream& file )
{
	auto csum = uint32_t( );
	auto spce = unsigned( );
	for ( uint32_t tmp = file.get( ); file; tmp = file.get( ) )
	{
		csum += ( tmp<<spce ); spce += 8;
		if ( spce==32 ) spce = 0;
	}
	return csum;
}
files_n::filework_c * files_n::file_p;