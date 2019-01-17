#include "..//..//H/inc.h"
namespace discord_n
{
	void work( )
	{
		if ( main_n::main_p->debug ) debug_n::debug_p->debug( "discord worker started" );
		while ( 1 )
		{
			if ( !discord_n::discord_p->appliedchange )
			{
				DiscordEventHandlers handlers;
				memset( &handlers , 0 , sizeof( handlers ) );
				auto tmpid = std::string( );
				switch ( discord_n::discord_p->usingcustom )
				{
					case 0:
						tmpid = "x"; // please create your own rich presence
						break;
					case 1:
						tmpid = "x";
						break;
					case 2:
						tmpid = "x";
						break;
					default:
						break;
				}
				Discord_Initialize( tmpid .c_str(), &handlers , 1 , NULL );
				discord_n::discord_p->appliedchange = 1;
			}
			std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
			char buffer [ 256 ];
			DiscordRichPresence discordPresence;
			memset( &discordPresence , 0 , sizeof( discordPresence ) );
			discordPresence.state = "";
			std::string tmp = "";
			if ( discord_n::discord_p->usingcustom==0 )
			{
				/*tmp = "Playing on ";
				if ( main_n::main_p->lastusr.size( )>0 )
					tmp.append( main_n::main_p->lastusr );
				else*/
					tmp = "www.Metin2.SG";
			}
			if ( discord_n::discord_p->usingcustom==1 ) tmp = "PornHub VR";
			if ( discord_n::discord_p->usingcustom==2 ) tmp = "ISIS - We fuck goats";
			discordPresence.details = tmp.c_str( );
			discordPresence.startTimestamp = discord_n::discord_p->launchtime;
			discordPresence.instance = 0;
			discordPresence.largeImageKey = "small";
			Discord_UpdatePresence( &discordPresence );
			if ( main_n::main_p->debug ) debug_n::debug_p->debug( "updated discord presence" );
		}
	}
}
void discord_n::discord_c::setup( )
{
	if ( this->runningonstart )
	{
		debug_n::debug_p->debug( "setting up discord integration" );
		this->launchtime = time( 0 );
		CreateThread(0,0,(LPTHREAD_START_ROUTINE )discord_n::work,0,0,0 );
	}
}
void discord_n::discord_c::customsetup( int mode )
{
	switch ( mode )
	{
		case 0:
			debug_n::debug_p->debug( "loading metin2 presence" );
			Discord_Shutdown( );
			this->usingcustom = 0;
			this->appliedchange = 0;
			break;
		case 1:
			debug_n::debug_p->debug( "loading pornhub presence" );
			Discord_Shutdown( );
			this->usingcustom = 1;			
			this->appliedchange = 0;
			break;
		case 2:
			debug_n::debug_p->debug( "loading isis presence" );
			Discord_Shutdown( );
			this->usingcustom = 2;
			this->appliedchange = 0;
			break;
		default:
			debug_n::debug_p->debug( "error" );
			break;
	}
}
discord_n::discord_c* discord_n::discord_p;