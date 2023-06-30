#include "stdafx.h"
#include "Functions.h"
#include "Offsets.h"

namespace Exile {
	fnGetGameTime Functions::GetGameTime;
	fnTranslateString Functions::TranslateString;
	fnGetPing Functions::GetPing;
	fnChangerCharacterData Functions::ChangerCharacterData;
	fnIssueOrder Functions::IssueOrder;
	fnCastSpell Functions::CastSpell;
	fnGetAttackCastDelay Functions::GetAttackCastDelay;
	fnGetAttackDelay Functions::GetAttackDelay;
	fnWorldToScreen Functions::WorldToScreen;

	void Functions::Initialize() {
		GetGameTime = (fnGetGameTime)DEFINE_RVA(Offsets::ClockFacade::GetGameTime);
		TranslateString = (fnTranslateString)DEFINE_RVA(Offsets::HashFunctions::TranslateString);
		GetPing = (fnGetPing)DEFINE_RVA(Offsets::NetClient::GetPing);
		ChangerCharacterData = (fnChangerCharacterData)DEFINE_RVA(Offsets::Functions::ChangerCharacterData);
		IssueOrder = (fnIssueOrder)DEFINE_RVA(Offsets::Functions::IssueOrder);
		CastSpell = (fnCastSpell)DEFINE_RVA(Offsets::Functions::CastSpell);
		GetAttackCastDelay = (fnGetAttackCastDelay)DEFINE_RVA(Offsets::Functions::GetAttackCastDelay);
		GetAttackDelay = (fnGetAttackDelay)DEFINE_RVA(Offsets::Functions::GetAttackDelay);
		WorldToScreen = (fnWorldToScreen)DEFINE_RVA(Offsets::RenderLayer::WorldToScreen);
	}
}