#pragma once

#include <cmpeg/render_base.h>

struct SDL_Surface;
struct SDL_Overlay;

namespace example
{
	class render_sdl : public cmpeg::render_base 
	{
	public:
		render_sdl();
		virtual void resize(int width, int height);
		virtual void render(const uint8_t* Y, const uint8_t* Cr, const uint8_t* Cb);

	private:
		SDL_Surface* m_screen;
		SDL_Overlay* m_bmp;
		int			 m_width;
		int			 m_height;
	};
}