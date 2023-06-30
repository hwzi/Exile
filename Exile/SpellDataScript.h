#pragma once

#include "Offsets.h"

namespace Exile
{
	class SpellDataScript
	{
	public:
		union
		{
			DEFINE_MEMBER_N(unsigned int Hash, Offsets::SpellDataScript::Hash)
		};
	};
}