#pragma once

#include "Offsets.h"

namespace Exile
{
	enum class SpellTargettingType : BYTE
	{
		Self,
		Unit,
		LocationAoe,
		Cone,
		SelfAoe,
		SelfAndUnit,
		Location,
		Location2,
		LocationVector,
		LocationSummon = 10,
		Location3,
		LocationTunnel
	};

	class SpellDataResource
	{
	public:
		union
		{
			DEFINE_MEMBER_N(const char* DisplayNameLocalizationKey, Offsets::SpellDataResource::DisplayNameLocalizationKey)
			DEFINE_MEMBER_N(float eEffect1[7], Offsets::SpellDataResource::eEffect1)
			DEFINE_MEMBER_N(float eEffect2[7], Offsets::SpellDataResource::eEffect2)
			DEFINE_MEMBER_N(float eEffect3[7], Offsets::SpellDataResource::eEffect3)
			DEFINE_MEMBER_N(float eEffect4[7], Offsets::SpellDataResource::eEffect4)
			DEFINE_MEMBER_N(float eEffect5[7], Offsets::SpellDataResource::eEffect5)
			DEFINE_MEMBER_N(float eEffect6[7], Offsets::SpellDataResource::eEffect6)
			DEFINE_MEMBER_N(float eEffect7[7], Offsets::SpellDataResource::eEffect7)
			DEFINE_MEMBER_N(float eEffect8[7], Offsets::SpellDataResource::eEffect8)
			DEFINE_MEMBER_N(float eEffect9[7], Offsets::SpellDataResource::eEffect9)
			DEFINE_MEMBER_N(float eEffect10[7], Offsets::SpellDataResource::eEffect10)
			DEFINE_MEMBER_N(float eEffect11[7], Offsets::SpellDataResource::eEffect11)
			DEFINE_MEMBER_N(float aEffect1, Offsets::SpellDataResource::aEffect1)
			DEFINE_MEMBER_N(float aEffect2, Offsets::SpellDataResource::aEffect2)
			DEFINE_MEMBER_N(bool CantCancelWhileWindingUp, Offsets::SpellDataResource::CantCancelWhileWindingUp)
			DEFINE_MEMBER_N(bool CantCancelWhileChanneling, Offsets::SpellDataResource::CantCancelWhileChanneling)
			DEFINE_MEMBER_N(bool ChannelIsInterruptedByAttacking, Offsets::SpellDataResource::ChannelIsInterruptedByAttacking)
			DEFINE_MEMBER_N(bool CanMoveWhileChanneling, Offsets::SpellDataResource::CanMoveWhileChanneling)
			DEFINE_MEMBER_N(float MissileSpeed, Offsets::SpellDataResource::MissileSpeed)
		};
	};
}