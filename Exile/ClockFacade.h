#pragma once

#include "Offsets.h"

namespace Exile
{
	class ClockFacade
	{
	public:
		static ClockFacade* Instance;

		union
		{
			DEFINE_MEMBER_N(DWORD* FrameClock, Offsets::ClockFacade::FrameClock)
		};

		float GetGameTime();
	};
}