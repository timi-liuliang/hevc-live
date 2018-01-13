#include <cmpeg/player.h>
#include <Windows.h>
#include "render_sdl.h"

int main() 
{

#ifdef _WIN32
	INT rc;
	WSADATA wsaData;
	rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (rc)
	{
		printf("WSAStartup Failed\n");
		return -1;
	}
#endif

	example::render_sdl render;

	cmpeg::player mpeg_player( &render, "ws://118.190.156.61:10002/camera_0");
	mpeg_player.play();

#ifdef _WIN32
	//delete ws;
	WSACleanup();
#endif
}
