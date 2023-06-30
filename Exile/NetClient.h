#pragma once

namespace Exile
{
	class NetClient
	{
	public:
		static NetClient* Instance;

		unsigned int GetPing();
	};
}