#pragma once

#include "Offsets.h"

namespace Exile
{
	class DeviceHandler
	{
	public:
		static DeviceHandler* Instance;

		union
		{
			DEFINE_MEMBER_N(IDirect3DDevice9* Direct3DDevice, Offsets::DeviceHandler::Direct3DDevice)
		};
	};
}