#pragma once

#include <stdint.h>

namespace cmpeg
{
	class render_base
	{
	public:
		virtual ~render_base() {}
		virtual void resize(int widht, int height) = 0;
		virtual void render(uint8_t* Y, uint8_t* Cr, uint8_t* Cb) = 0;
	};
}