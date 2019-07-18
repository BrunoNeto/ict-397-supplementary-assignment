#include "Application.h"
#include "Exception.h"

int WINAPI WinMain(HINSTANCE Instance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT)
{
	hPrevInstance;
	try
	{
		// Create the application class, 
		// parse the command line and
		// start the app.
		CApplication lostTresureApp(Instance);
		lostTresureApp.ParseCmdLine(lpCmdLine);
		lostTresureApp.Run();
	}
	catch (CException& e)
	{
		MessageBox(NULL, e.what(), "Error", MB_OK | MB_ICONEXCLAMATION);
	}

	return 0;
}