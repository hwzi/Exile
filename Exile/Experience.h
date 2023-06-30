#pragma once

#include "Offsets.h"

namespace Exile
{
	class Experience
	{
	public:
		union
		{
			DEFINE_MEMBER_N(unsigned int Level, Offsets::Experience::Level)
		};
	};
}