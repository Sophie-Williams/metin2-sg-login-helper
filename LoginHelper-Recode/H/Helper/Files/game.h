#pragma once
#include "../../inc.h"
namespace game_n
{
	struct game_window
	{
		HWND hwnd = 0;
		int id = 0;
		const char* class_ = "";
		const char* title = "";
		bool used = 0;
		bool focused = 0;
		bool isold = 0;
		files_n::acc acc;
	};

	class game_c
	{
	private:
		bool inputlocked = 0;
	public:
		int lastpid = 0;
		HWND lasthwnd ;
		DWORD patcherpid;
		HWND patcherhwnd;
		std::vector<game_window> instances;
		void runclient( );
		void refreshlist( );
		bool setfocus(HWND hw );
		void killprocess(DWORD id);
		void sendkey( WORD vk );
		bool login(files_n::acc account , game_n::game_window window );
		void sendtext( HWND hw , char *text );
		void sendmouse( );

	};
	extern game_c * game_p;
}