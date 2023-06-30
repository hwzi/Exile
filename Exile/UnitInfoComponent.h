#pragma once

#include "Offsets.h"

namespace Exile {
	class UnitInfoComponent {
	public:
		union {
			DEFINE_MEMBER_N(FloatingInfoBar* FloatingInfoBar, 0x14);
		};
	};
}