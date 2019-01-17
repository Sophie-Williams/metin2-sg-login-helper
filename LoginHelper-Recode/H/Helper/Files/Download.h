#pragma once
#include "..//..//inc.h"
namespace down_n
{
	class down_c
	{
	private:
		uint32_t preupdate;
		bool exists = 0;
		bool difference = 0;
		std::vector<std::string> cachedata;
		bool download( std::string pth , char* filename, bool force = 0 );
		bool update( );
	public:
		std::string ver_sg = "-2";
		bool work( );
	};
	extern down_c* down_p;
}