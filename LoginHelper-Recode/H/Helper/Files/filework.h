#pragma once
#include "..//..//inc.h"
namespace files_n
{
	struct acc
	{
		std::string user = { };
		std::string pass = { };
		std::string pseu = { };
		DWORD id = 0;
		HWND hwnd = 0;
		bool ismanaged = 0;
	};
	class filework_c
	{
	private:
		char*selfname = "";
		char selfpath [ MAX_PATH ];
		void getpath( );
		bool is_metinfolder( );
		bool getbin( );
		bool makeexe( );
		bool loadaccs( );
		bool loadbutton( );
	public:
		bool done = 0;
		int button [ 2 ];
		std::string path;
		std::vector<acc> accs;
		std::string getdirpath( );
		void setname( char* in );
		char* getpathself( );
		bool setupbutton( );
		bool reloadacc( );
		void fetchmanaged( );
		uint32_t gethash( std::ifstream& file );
		void setup( );
	};
	extern filework_c * file_p;
}