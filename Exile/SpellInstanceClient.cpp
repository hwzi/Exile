#include "stdafx.h"
#include "SpellInstanceClient.h"

namespace Exile {
	SpellCastInfo* SpellInstanceClient::GetCastInfo() {
		return (SpellCastInfo*)((DWORD)this + (DWORD)Offsets::SpellInstanceClient::CastInfo);
	}
}