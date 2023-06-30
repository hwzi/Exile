#include "stdafx.h"
#include "NetClient.h"
#include "Functions.h"

namespace Exile
{
	NetClient* NetClient::Instance;

	unsigned int NetClient::GetPing()
	{
		return Functions::GetPing(this);
	}
}