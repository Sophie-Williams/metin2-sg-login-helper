#pragma once
#include "..//inc.h"
namespace login_n
{
	class login_c
	{
	public:
		files_n::acc cur_acc;
		game_n::game_window instance;
		bool setup( files_n::acc cur_acc );
		bool prework( );
		bool work( );
	};
	extern login_c* login_p;
}