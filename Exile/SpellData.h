#pragma once

#include "Offsets.h"
#include "SpellDataScript.h"
#include "SpellDataResource.h"

namespace Exile
{
	class SpellData
	{
	public:
		union
		{
			DEFINE_MEMBER_N(SpellDataScript* Script, Offsets::SpellData::Script)
			DEFINE_MEMBER_N(std::string Name, Offsets::SpellData::Name)
			DEFINE_MEMBER_N(SpellDataResource* Resource, Offsets::SpellData::Resource)
		};
	};
}