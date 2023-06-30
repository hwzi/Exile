#pragma once

#include "NetClient.h"
#include "CharacterDataStack.h"
#include "GameObject.h"

namespace Exile {
	typedef float(__thiscall* fnGetGameTime)(DWORD* frameClock);
	typedef const char* (__cdecl* fnTranslateString)(const char* str);
	typedef unsigned int(__thiscall* fnGetPing)(NetClient* netClient);
	typedef int(__thiscall* fnChangerCharacterData)(CharacterDataStack* characterDataStack, const char* skinName, int skinId, bool a4, bool a5, bool a6, bool a7, bool a8, bool a9);
	typedef int(__thiscall* fnIssueOrder)(GameObject* unit, GameObjectOrder order, Vector3& position, GameObject* target, bool attackMove, bool a6, bool a7);
	typedef void(__thiscall* fnCastSpell)(SpellbookClient* spellbook, SpellDataInst* spell, kSpellSlot slot, Vector3& endPosition, Vector3& startPosition, unsigned int target_network_id);
	typedef float(__cdecl* fnGetAttackCastDelay)(GameObject* unit, kSpellSlot slot);
	typedef float(__cdecl* fnGetAttackDelay)(GameObject* unit);
	typedef bool(__cdecl* fnWorldToScreen)(Vector3& position, Vector3& out);

	namespace Functions {
		extern fnGetGameTime GetGameTime;
		extern fnTranslateString TranslateString;
		extern fnGetPing GetPing;
		extern fnChangerCharacterData ChangerCharacterData;
		extern fnIssueOrder IssueOrder;
		extern fnCastSpell CastSpell;
		extern fnGetAttackCastDelay GetAttackCastDelay;
		extern fnGetAttackDelay GetAttackDelay;
		extern fnWorldToScreen WorldToScreen;

		void Initialize();
	}
}