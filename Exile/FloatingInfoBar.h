#pragma once

#include "Offsets.h"

namespace Exile {
	class FloatingInfoBar {
	public:
		union {
			DEFINE_MEMBER_N(HudHealthBar* HudHealthBar, 0x20); // + 0xDC == Width
		};
	};
}