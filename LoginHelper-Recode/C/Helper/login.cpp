#include "..//..//H/inc.h"
bool login_n::login_c::setup( files_n::acc cur_acc )
{
	this->cur_acc = cur_acc;
	if ( this->cur_acc.ismanaged )
	{
		std::cout<<"account is already managed create new instance y/n ";
		auto tmp_answer = std::string( );
		std::cin>>tmp_answer;
		if ( strstr( tmp_answer.c_str( ) , "y" ) )
		{
			debug_n::debug_p->debug( "closing old instance" );
			game_n::game_p->killprocess( this->cur_acc.id );
			this->cur_acc.ismanaged = 0;
			this->cur_acc.id = 0;
		}
		else
		{
			return 0;
		}
	}
	game_n::game_p->runclient( );
	return 1;
}
bool login_n::login_c::prework( )
{
re:
	if ( !game_n::game_p->setfocus( this->instance.hwnd ) )
	{
		Sleep( 75 );
		goto re;
	}
	debug_n::debug_p->debug( "instance in focus" );
	return 1;
}
bool login_n::login_c::work( )
{
	for ( auto && object:game_n::game_p->instances )
	{
		if ( object.isold||object.used||object.acc.ismanaged ) continue;
		if ( !object.id||!object.class_||!object.hwnd ) continue;
		if ( main_n::main_p->debug ) debug_n::debug_p->debug( "new instance selected" );
		Sleep( 50 );
		this->instance = object;
		if ( this->prework( ) )
		{
			BlockInput( TRUE );
			Sleep( 100 );
			SetWindowPos( object.hwnd , HWND_TOP , 0 , 0 , 0 , 0 , SWP_NOSIZE );
			SetCursorPos( files_n::file_p->button [ 0 ] , files_n::file_p->button [ 1 ] );
			game_n::game_p->sendmouse( );
			SetWindowText( object.hwnd , std::string( "Metin2 SG - managed:" ).append( this->cur_acc.user ).c_str( ) );
			if ( !game_n::game_p->login( this->cur_acc , object ) )
			{
				BlockInput( FALSE );
				debug_n::debug_p->debug( "something went wrong during game_n::game_p->login" );
				return 0;
			}
			BlockInput( FALSE );
			Sleep( 1000 );
			for ( auto &&obj:files_n::file_p->accs )
			{
				if ( !obj.user.size( ) ) continue;
				if ( strstr( object.title , obj.user.c_str( ) ) )
					object.acc = obj;
				else
					continue;
			}
			this->cur_acc.ismanaged = 1;
			this->cur_acc.id = object.id;
			this->cur_acc.hwnd = object.hwnd;
			main_n::main_p->lastusr = this->cur_acc.pseu;
			object.used = 1;
			return 1;
		}
	}
}
login_n::login_c* login_n::login_p;