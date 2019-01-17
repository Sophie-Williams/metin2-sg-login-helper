#include  "..//..//H/inc.h"
namespace alive_n
{
	void worker( )
	{
		while ( 1 )
		{
			std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
			for ( auto && instances:game_n::game_p->instances )
			{
				if ( !instances.title )continue;
				if ( !instances.hwnd )continue;
				/*get rid of killed windows*/
				if ( !IsWindow( instances.hwnd ) )
				{
					game_n::game_window tmp;
					for ( auto&&acc:files_n::file_p->accs )
					{											
						if ( instances.hwnd == acc.hwnd )
						{
							acc.ismanaged = 0;
							acc.id = 0;
						}
						else
							continue;
					}
					instances = tmp;
				}
				else
					continue;
			}
		}
	}
}
bool alive_n::alive_c::setup( )
{
	CreateThread( 0 , 0 , ( LPTHREAD_START_ROUTINE ) alive_n::worker , 0 , 0 , 0 );
	this->issetup = 1;
	debug_n::debug_p->debug( "alivecheck worker created" );
	return 1;
}
alive_n::alive_c* alive_n::alive_p;