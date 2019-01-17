#include "../../../H/inc.h"
/*api*/
BOOL CALLBACK EnumWindowsProc( HWND hWND , LPARAM lParam )
{
	DWORD procid;
	char cWindowClass [ 80 ];
	char cWindowTitle [ 80 ];
	GetClassNameA( hWND , cWindowClass , sizeof( cWindowClass ) );
	GetWindowTextA( hWND , cWindowTitle , sizeof( cWindowTitle ) );
	if ( strstr( cWindowTitle , "Metin2 SG" ) )
	{
		GetWindowThreadProcessId( hWND , &procid );
		debug_n::debug_p->debug( "new instance found" );
		if ( main_n::main_p->debug ) debug_n::debug_p->debug( std::string( "pid: " ).append( std::to_string( procid ) ).append( " | title: " ).append( cWindowTitle ) );
		game_n::game_window instance;
		instance.class_ = cWindowClass;
		instance.title = cWindowTitle;
		instance.id = procid;
		instance.hwnd = hWND;
		if ( !files_n::file_p->done ) instance.isold = 1;
		game_n::game_p->lastpid = procid;
		game_n::game_p->lasthwnd = hWND;
		for ( auto &&obj:files_n::file_p->accs )
		{
			if ( !obj.user.size( ) ) continue;
			if ( strstr( cWindowTitle , obj.user.c_str( ) ) )
			{
				instance.acc = obj;
				obj.ismanaged = 1;
				obj.id = procid;
				obj.hwnd = hWND;
				break;
			}
			else
				continue;
		}
		if ( instance.acc.ismanaged ) debug_n::debug_p->debug( std::string( "managed window found user: " ).append( instance.acc.user ) );
		game_n::game_p->instances.push_back( instance );
	}
	if ( strstr( cWindowTitle , "old pre update instance" ) )
	{
		GetWindowThreadProcessId( hWND , &procid );
		game_n::game_p->killprocess( procid );
	}
	if ( !discord_n::discord_p->runningonstart )
	{
		if ( strstr( cWindowTitle , "Discord" ) )
		{
			debug_n::debug_p->debug( "discord was found" );
			debug_n::debug_p->debug( cWindowTitle );
			discord_n::discord_p->runningonstart = 1;
		}
	}
	return TRUE;
}
void game_n::game_c::runclient( )
{
	if ( main_n::main_p->debug ) debug_n::debug_p->debug( "running new instance" );
	auto oldsize = this->instances.size( );
	ShellExecuteA( NULL , "open" , main_n::main_p->exepath.c_str( ) , NULL , NULL , SW_SHOWDEFAULT );
	while ( oldsize==this->instances.size( ) )
		this->refreshlist( );
	debug_n::debug_p->debug( "new instance added" );
}
void game_n::game_c::refreshlist( )
{
	EnumWindows( EnumWindowsProc , NULL );
}
bool game_n::game_c::setfocus( HWND h )
{
	SetForegroundWindow( h );
	SetActiveWindow( h );
	auto cur = GetForegroundWindow( );
	Sleep( 100 );
	if ( cur!=h ) return 0;
	return 1;
}
void game_n::game_c::killprocess( DWORD id )
{
	auto h = OpenProcess( PROCESS_TERMINATE , FALSE , id );
	if ( h==NULL )return;
	TerminateProcess( h , 0 );
	CloseHandle( h );
}
void game_n::game_c::sendkey( WORD vk )
{
	INPUT input [ 2 ];
	input [ 0 ].ki.wVk = vk;
	input [ 0 ].ki.wScan = 0;
	input [ 0 ].ki.dwFlags = 0;
	input [ 0 ].ki.time = 0;
	input [ 0 ].ki.dwExtraInfo = 0;
	input [ 0 ].type = INPUT_KEYBOARD;
	input [ 1 ].ki.wVk = vk;
	input [ 1 ].ki.wScan = 0;
	input [ 1 ].ki.dwFlags = KEYEVENTF_KEYUP;
	input [ 1 ].ki.time = 0;
	input [ 1 ].ki.dwExtraInfo = 0;
	input [ 1 ].type = INPUT_KEYBOARD;
	SendInput( 2 , input , sizeof( INPUT ) );
}
void game_n::game_c::sendtext( HWND hw , char *text )
{
	auto iLength = strlen( text );
	for ( auto i = 0; i<iLength; i++ )
		PostMessageA( hw , WM_CHAR , text [ i ] , 0 );
}
bool game_n::game_c::login( files_n::acc acc_data , game_n::game_window window )
{
	if ( !IsWindow( window.hwnd ) )
	{
		debug_n::debug_p->debug( "window is missing aborting login" );
		return 0;
	}
	this->setfocus( window.hwnd );
	game_n::game_p->sendtext( window.hwnd , ( char* ) acc_data.user.c_str( ) );
	Sleep( 50 );
	game_n::game_p->sendkey( VK_RETURN );
	Sleep( 50 );
	this->setfocus( window.hwnd );
	game_n::game_p->sendtext( window.hwnd , ( char* ) acc_data.pass.c_str( ) );
	Sleep( 50 );
	game_n::game_p->sendkey( VK_RETURN );
	return 1;
}
void game_n::game_c::sendmouse( )
{
	Sleep( 75 );
	POINT pos_cursor;
	HWND hwnd_outra_win;
	GetCursorPos( &pos_cursor );
	hwnd_outra_win = WindowFromPoint( pos_cursor );
	SendMessage( hwnd_outra_win , WM_LBUTTONDOWN , MK_LBUTTON , MAKELPARAM( pos_cursor.x , pos_cursor.y ) );
	SendMessage( hwnd_outra_win , WM_LBUTTONUP , 0 , MAKELPARAM( pos_cursor.x , pos_cursor.y ) );
}
game_n::game_c * game_n::game_p;
