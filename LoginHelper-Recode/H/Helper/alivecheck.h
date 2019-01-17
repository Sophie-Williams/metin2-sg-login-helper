#pragma once
#include "..//inc.h"
namespace alive_n
{
	class alive_c
	{
	private:
		bool issetup;
	public:
		void worker( );
		bool setup( );
	};
	extern alive_c* alive_p;
}