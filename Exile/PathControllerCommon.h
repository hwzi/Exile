#pragma once

#include "NavigationPath.h"

namespace Exile
{
	class PathControllerCommon
	{
	public:
		union
		{
			DEFINE_MEMBER_N(bool HasNavigationPath, Offsets::PathControllerCommon::HasNavigationPath)
			DEFINE_MEMBER_N(Vector3 ServerPosition, Offsets::PathControllerCommon::ServerPosition)
		};

		NavigationPath* GetNavigationPath();
	};
}