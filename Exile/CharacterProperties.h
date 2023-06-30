#pragma once

#include "Offsets.h"

namespace Exile {
	class CharacterProperties {
	public:
		union {
			DEFINE_MEMBER_N(float AttackRange, Offsets::CharacterProperties::AttackRange)
		};
	};
}