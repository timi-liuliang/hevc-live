#include "decoder_mpeg5.h"
#include <assert.h>

namespace cmpeg 
{
	decoder_mpeg5::decoder_mpeg5()
		: decoder_base()
	{
	}

	decoder_mpeg5::~decoder_mpeg5()
	{
	}

	bool decoder_mpeg5::write(int pts, const std::vector<uint8_t>& buffer)
	{
		decoder_base::write(pts, buffer);

		return true;
	}

	bool decoder_mpeg5::decode()
	{
		//advance_decoded_time(1.0 / m_frame_rate);

		return true;
	}
}