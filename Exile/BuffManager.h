#pragma once

#include "BuffInstance.h"

namespace Exile
{
	class BuffManager
	{
	public:
		union
		{
			DEFINE_MEMBER_0(BuffInstance* Buff)
		};
		BYTE pad[0x4];
	};
}
