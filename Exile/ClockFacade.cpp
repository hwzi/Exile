#include "stdafx.h"
#include "ClockFacade.h"
#include "Functions.h"

namespace Exile
{
	ClockFacade* ClockFacade::Instance;

	float ClockFacade::GetGameTime()
	{
		return Functions::GetGameTime(this->FrameClock);
	}
}