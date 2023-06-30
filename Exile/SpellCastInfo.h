#pragma once

#include "Offsets.h"
#include "SpellData.h"
#include "Vector3.h"

namespace Exile
{
	enum kSpellSlot
	{
		SpellSlot_Unknown = -1,
		SpellSlot_Q,
		SpellSlot_W,
		SpellSlot_E,
		SpellSlot_R,
		SpellSlot_Summoner1,
		SpellSlot_Summoner2,
		SpellSlot_Item1,
		SpellSlot_Item2,
		SpellSlot_Item3,
		SpellSlot_Item4,
		SpellSlot_Item5,
		SpellSlot_Item6,
		SpellSlot_Trinket,
		SpellSlot_Recall,
		SpellSlot_SpecialAttack = 45,
		SpellSlot_BasicAttack = 65,
	};

	class SpellCastInfo
	{
	public:
		union
		{
			DEFINE_MEMBER_0(Exile::SpellData* SpellData)
			DEFINE_MEMBER_N(unsigned int Level, Offsets::SpellCastInfo::Level)
			DEFINE_MEMBER_N(Vector3 StartPosition, Offsets::SpellCastInfo::StartPosition)
			DEFINE_MEMBER_N(Vector3 EndPosition, Offsets::SpellCastInfo::EndPosition)
			DEFINE_MEMBER_N(unsigned short TargetId, Offsets::SpellCastInfo::TargetId)
			DEFINE_MEMBER_N(float CastDelay, Offsets::SpellCastInfo::CastDelay)
			DEFINE_MEMBER_N(float Delay, Offsets::SpellCastInfo::Delay)
			DEFINE_MEMBER_N(bool IsBasicAttack, Offsets::SpellCastInfo::IsBasicAttack)
			DEFINE_MEMBER_N(bool IsSpecialAttack, Offsets::SpellCastInfo::IsSpecialAttack)
			DEFINE_MEMBER_N(kSpellSlot Slot, Offsets::SpellCastInfo::Slot)
			DEFINE_MEMBER_N(float StartTime, Offsets::SpellCastInfo::StartTime)
			DEFINE_MEMBER_N(float CastEndTime, Offsets::SpellCastInfo::CastEndTime)
			DEFINE_MEMBER_N(float EndTime, Offsets::SpellCastInfo::EndTime)
			DEFINE_MEMBER_N(bool SpellWasCast, Offsets::SpellCastInfo::SpellWasCast)
			DEFINE_MEMBER_N(bool IsStopped, Offsets::SpellCastInfo::IsStopped)
			DEFINE_MEMBER_N(bool IsInstantCast, Offsets::SpellCastInfo::IsInstantCast)
		};

		bool IsAutoAttack();
		bool IsChanneling();
	};
}