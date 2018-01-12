#include "render_sdl.h"
#include <SDL.h>
#include <vector>

#undef main

namespace example
{
	render_sdl::render_sdl()
		: m_screen(NULL)
		, m_bmp(NULL)
		, m_width(0)
		, m_height(0)
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
			fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
			return;
		}
	}

	void render_sdl::resize(int width, int height)
	{
		m_width = width;
		m_height = height;

		m_screen = SDL_SetVideoMode(width, height, 0, 0);
		if (!m_screen)
			return;

		m_bmp = SDL_CreateYUVOverlay(width, height, SDL_YV12_OVERLAY, m_screen);
	}

	void render_sdl::render(uint8_t* Y, uint8_t* Cr, uint8_t* Cb)
	{
		SDL_LockYUVOverlay(m_bmp);

		m_bmp->pixels[0] = Y;
		m_bmp->pixels[1] = Cr;
		m_bmp->pixels[2] = Cb;
		m_bmp->pitches[0] = 640;
		m_bmp->pitches[1] = 320;
		m_bmp->pitches[2] = 320;

		SDL_UnlockYUVOverlay(m_bmp);

		SDL_Rect rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = m_width;
		rect.h = m_height;

		SDL_DisplayYUVOverlay(m_bmp, &rect);
	}
}