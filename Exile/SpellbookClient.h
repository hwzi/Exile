#pragma once

#include "Offsets.h"
#include "SpellInstanceClient.h"

namespace Exile
{
	enum kSpellState
	{
		SpellState_Ready,
		SpellState_NotAvailable = 1 << 1,
		SpellState_NotLearned = 1 << 2,
		SpellState_Supressed = 1 << 3,
		SpellState_Disabled = 1 << 4,
		SpellState_Cooldown = 1 << 5,
		SpellState_NoMana = 1 << 6
	};

	class SpellbookClient
	{
	public:
		union
		{
			DEFINE_MEMBER_0(DWORD* VTable)
			DEFINE_MEMBER_N(SpellInstanceClient* ActiveSpellInstance, Offsets::SpellbookClient::ActiveSpellInstance)
		};
	};
}