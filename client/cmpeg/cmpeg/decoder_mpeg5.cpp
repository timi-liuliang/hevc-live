#include "decoder_mpeg5.h"
#include <assert.h>

namespace cmpeg 
{
	decoder_mpeg5::decoder_mpeg5()
		: decoder_base()
	{
		m_ctx = de265_new_decoder();
	}

	decoder_mpeg5::~decoder_mpeg5()
	{
	}

	bool decoder_mpeg5::write(int pts, const std::vector<uint8_t>& buffer)
	{
		de265_push_data(m_ctx, buffer.data(), buffer.size(), pts,  NULL);

		decode();

		return true;
	}

	bool decoder_mpeg5::decode()
	{
		de265_error err = DE265_OK;

		int more = 0;
		while ( true)
		{
			err = de265_decode( m_ctx, &more);
			if (err != DE265_OK) {
				break;
			}

			// show available images
			const de265_image* img = de265_get_next_picture(m_ctx);
			if (img) {
				int a = 10;
			}
		}

		return true;
	}
}