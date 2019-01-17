#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <tchar.h>
#include <urlmon.h>
#include <dos.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <Psapi.h>
#include <processthreadsapi.h>
#include <TlHelp32.h>
#include <thread>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <wincrypt.h>
#include "discord-rpc.h"
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "discord-rpc.lib")
/**/
#include "Helper\debug.h"

#include "Helper\Files\filework.h"
#include "Helper\Files\game.h"
#include "Helper\alivecheck.h"
#include "Helper\Discord.h"
#include "Helper\Files\Download.h"
#include "Helper\login.h"

#include "mainfn.h"
