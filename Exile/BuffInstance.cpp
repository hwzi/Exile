#include "stdafx.h"
#include "BuffInstance.h"

namespace Exile
{
	bool BuffInstance::IsActive()
	{
		return this->Script && !this->ScriptInfo.empty() || this->IsPermanent;
	}

	unsigned int BuffInstance::GetCount()
	{
		return this->ScriptInfo.size();
	}

	BuffScriptInstance* BuffInstance::GetScriptInstance()
	{
		return (BuffScriptInstance*)this->ScriptInfo.back();
	}
}