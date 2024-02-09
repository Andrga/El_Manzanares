//
// Enables Visual C++'s memory leak detection
//
// This header only works for Windows. In Linux or macOS, please add
// -fsanitize=address to the compiler's command line to check leaks.
//

#if defined(_WIN32) && defined(_DEBUG)
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
	#include <stdlib.h>
	#if defined(_MSC_VER) && !defined(DBG_NEW)
		#define DBG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
		#define new DBG_NEW
	#endif

// The following code activates the memory leak analysis when exiting
// the program. It uses inline variables, a new feature of C++17, that
// is not available in old versions of Visual Studio (before VS 2017).
// In that case, you should comment the line that starts with inline and
// call the _CrtSetDbgFlag function in the main function.

class crt_leak_setflag_dummy
{
	struct constructor
	{
		constructor() { _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); }
	};
	static constructor ctor;
};
inline crt_leak_setflag_dummy::constructor crt_leak_setflag_dummy::ctor;

#endif
