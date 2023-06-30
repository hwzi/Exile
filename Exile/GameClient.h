#pragma once

#include "Offsets.h"

namespace Exile
{
	enum class GameState
	{
		PreGame,
		Spawn,
		GameLoop,
		EndGame,
		PreExit,
		Exit,
	};

	class GameClient
	{
	public:
		static GameClient* Instance;

		union
		{
			DEFINE_MEMBER_N(GameState GameState, Offsets::GameClient::GameState)
		};
	};
}