#pragma once

#include "Offsets.h"
#include "ItemData.h"

namespace Exile
{
	class ItemInfo
	{
	public:
		union
		{
			DEFINE_MEMBER_N(ItemData* ItemData, Offsets::ItemInfo::ItemData)
		};
	};
}