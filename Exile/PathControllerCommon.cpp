#include "stdafx.h"
#include "PathControllerCommon.h"

namespace Exile {
	NavigationPath* PathControllerCommon::GetNavigationPath() {
		return (NavigationPath*)((DWORD)this + (DWORD)Offsets::PathControllerCommon::NavigationPath);
	}
}