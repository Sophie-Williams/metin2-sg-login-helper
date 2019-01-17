#pragma once
/**/
#include "inc.h"
/**/
namespace main_n
{
	class main_c
	{
	private:
		int iversion = 0;
		bool is_setup = FALSE;
		std::string curpath = { };
		bool dbg_console( );
		void setupdiscord( );
		void updatediscord( );
	public:
		std::string binpath = { };
		std::string exepath = { };
		std::string lastusr = { };
		int64_t timer;
		bool debug = FALSE;
		void startup( char *argca [ ] );
		void worker( );
	};
	extern main_c* main_p;
}