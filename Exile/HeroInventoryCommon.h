#pragma once

#include "Offsets.h"
#include "InventorySlot.h"

namespace Exile
{
	class HeroInventoryCommon
	{
	public:
		union
		{
			DEFINE_MEMBER_N(InventorySlot* Slots[39], Offsets::HeroInventoryCommon::Slots)
		};
	};
}