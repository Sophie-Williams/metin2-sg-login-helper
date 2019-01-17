#pragma once
#include "..//inc.h"
namespace discord_n
{
	class discord_c
	{
	public:
		int64_t launchtime;
		bool runningonstart = 0;
		bool appliedchange = 0;
		int usingcustom = 0;
		void setup( );
		void customsetup( int mode );
	};
	extern discord_c* discord_p;
}