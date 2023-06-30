#include "stdafx.h"
#include "GameObject.h"
#include "Functions.h"
#include "EventManager.h"
#include "ObjectManager.h"
#include "HashFunctions.h"
#include "Damage.h"
#include "Orbwalker.h"

namespace Exile
{
	float GameObject::GetBoundingRadius()
	{
		return reinterpret_cast<float(__thiscall*)(GameObject*)>(this->VTable[(DWORD)Offsets::GameObject::Virtual_GetBoundingRadius])(this);
	}

	PathControllerCommon* GameObject::GetPathController()
	{
		return reinterpret_cast<PathControllerCommon*(__thiscall*)(GameObject*)>(this->VTable[(DWORD)Offsets::GameObject::Virtual_GetPathController])(this);
	}

	float GameObject::GetAttackCastDelay()
	{
		return Functions::GetAttackCastDelay(this, SpellSlot_BasicAttack);
	}

	float GameObject::GetAttackDelay()
	{
		return Functions::GetAttackDelay(this);
	}

	SpellDataInst* GameObject::GetSpell(kSpellSlot slot)
	{
		return reinterpret_cast<SpellDataInst*(__thiscall*)(SpellbookClient&, kSpellSlot)>(this->Spellbook.VTable[(DWORD)Offsets::SpellbookClient::Virtual_GetSpell])(this->Spellbook, slot);
	}

	kSpellState GameObject::GetSpellState(kSpellSlot slot)
	{
		bool unk;
		return reinterpret_cast<kSpellState(__thiscall*)(SpellbookClient&, kSpellSlot, bool*)>(this->Spellbook.VTable[(DWORD)Offsets::SpellbookClient::Virtual_GetSpellState])(this->Spellbook, slot, &unk);
	}

	void GameObject::CastSpell(kSpellSlot slot)
	{
		if (this->GetSpellState(slot) == SpellState_Ready) {
			auto spell = this->GetSpell(slot);
			if (EventManager::TriggerProcess(LeagueEvents::OnCastSpell, &this->Spellbook, spell, slot, this->Position, Vector3::Zero, this->NetworkId)) {
				Functions::CastSpell(&this->Spellbook, spell, slot, this->Position, Vector3::Zero, this->NetworkId);
			}
		}
	}

	void GameObject::CastSpell(kSpellSlot slot, Vector3 position)
	{
		if (this->GetSpellState(slot) == SpellState_Ready) {
			auto spell = this->GetSpell(slot);
			if (EventManager::TriggerProcess(LeagueEvents::OnCastSpell, &this->Spellbook, spell, slot, position, Vector3::Zero, 0U)) {
				Functions::CastSpell(&this->Spellbook, spell, slot, position, Vector3::Zero, 0);
			}
		}
	}

	void GameObject::CastSpell(kSpellSlot slot, Vector3 start_position, Vector3 end_position)
	{
		if (this->GetSpellState(slot) == SpellState_Ready) {
			auto spell = this->GetSpell(slot);
			if (EventManager::TriggerProcess(LeagueEvents::OnCastSpell, &this->Spellbook, spell, slot, end_position, start_position, 0U)) {
				Functions::CastSpell(&this->Spellbook, spell, slot, end_position, start_position, 0);
			}
		}
	}

	void GameObject::CastSpell(kSpellSlot slot, GameObject* target)
	{
		if (this->GetSpellState(slot) == SpellState_Ready) {
			auto spell = this->GetSpell(slot);
			if (EventManager::TriggerProcess(LeagueEvents::OnCastSpell, &this->Spellbook, spell, slot, target->Position, Vector3::Zero, target->NetworkId)) {
				Functions::CastSpell(&this->Spellbook, spell, slot, target->Position, Vector3::Zero, target->NetworkId);
			}
		}
	}

	void GameObject::IssueOrder(GameObjectOrder order, GameObject* target)
	{
		if (EventManager::TriggerProcess(LeagueEvents::OnIssueOrder, this, order, target->Position, target))
		{
			Functions::IssueOrder(this, order, target->Position, target, false, false, true);
		}
	}

	void GameObject::IssueOrder(GameObjectOrder order, Vector3 position)
	{
		if (EventManager::TriggerProcess(LeagueEvents::OnIssueOrder, this, order, position, nullptr))
		{
			Functions::IssueOrder(this, order, position, nullptr, false, false, true);
		}
	}

	bool GameObject::IsMe()
	{
		return this == ObjectManager::Player;
	}

	bool GameObject::IsMoving()
	{
		return this->GetPathController()->HasNavigationPath;
	}

	unsigned int GameObject::PathIndex()
	{
		return this->GetPathController()->GetNavigationPath()->Index;
	}

	unsigned int GameObject::PathCount()
	{
		return this->GetPathController()->GetNavigationPath()->Path.size();
	}

	Vector3 GameObject::GetPath(unsigned int index)
	{
		return this->GetPathController()->GetNavigationPath()->Path[index];
	}

	bool GameObject::IsDashing()
	{
		return this->GetPathController()->GetNavigationPath()->IsDashing;
	}

	float GameObject::DashSpeed()
	{
		return this->GetPathController()->GetNavigationPath()->DashSpeed;
	}

	Vector3 GameObject::ServerPosition()
	{
		return this->GetPathController()->ServerPosition;
	}

	unsigned int GameObject::RuneCount()
	{
		return 6;
	}

	GameObjectType GameObject::Type()
	{
		return this->GetClassData()->Type();
	}

	bool GameObject::IsStructure()
	{
		switch (this->GetClassData()->Type())
		{
		case GameObjectType::AITurretClient:
		case GameObjectType::BarracksDampener:
		case GameObjectType::HQ:
			return true;
		default:
			return false;
		}
	}

	bool GameObject::IsAlly()
	{
		return this->Team == ObjectManager::Player->Team;
	}

	bool GameObject::IsEnemy()
	{
		return this->Team != ObjectManager::Player->Team;
	}

	bool GameObject::IsNeutral()
	{
		return this->Team == GameObjectTeam_Neutral;
	}

	bool GameObject::IsMonster() {
		return this->Team == GameObjectTeam_Neutral && this->MaxHealth > 6.0f;
	}

	bool GameObject::IsBaseAI()
	{
		return this->Flags() & GameObjectFlags_AIBaseClient;
	}

	bool GameObject::IsMinion()
	{
		return this->Flags() & GameObjectFlags_AIMinionClient;
	}

	bool GameObject::IsHero()
	{
		return this->Flags() & GameObjectFlags_AIHeroClient;
	}

	bool GameObject::IsTurret()
	{
		return this->Flags() & GameObjectFlags_AITurretClient;
	}

	bool GameObject::IsMissile()
	{
		return this->Flags() & GameObjectFlags_MissileClient;
	}

	bool GameObject::IsInvulnerable()
	{
		return this->StatusFlags & GameObjectStatusFlags_Invulnerable;
	}

	bool GameObject::IsMagicImmune()
	{
		return this->StatusFlags & GameObjectStatusFlags_MagicImmune;
	}

	bool GameObject::IsPhysicalImmune()
	{
		return this->StatusFlags & GameObjectStatusFlags_PhysicalImmune;
	}

	bool GameObject::IsValidTarget(float range, bool onlyEnemyTeam, Vector3 rangeCheckFrom)
	{
		if (this->IsDead() || !this->IsVisible || !this->IsTargetable || this->IsUntargetableToAllies || this->StatusFlags & GameObjectStatusFlags_Invulnerable)
		{
			return false;
		}

		if (onlyEnemyTeam && this->Team == ObjectManager::Player->Team)
		{
			return false;
		}

		if (range != FLT_MAX)
		{
			auto position = this->Flags() & GameObjectFlags_AIBaseClient ? this->GetPathController()->ServerPosition : this->Position;
			return rangeCheckFrom.IsValid() ? rangeCheckFrom.DistanceSquared(position) < range * range : ObjectManager::Player->GetPathController()->ServerPosition.DistanceSquared(position) < range * range;
		}
		return true;
	}

	float GameObject::TotalHealth()
	{
		auto result = this->Health;
		if (this->Flags() & GameObjectFlags_AIHeroClient && this->BaseCharacterData->SkinHash == Character::Kled)
		{
			result += this->SecondaryResource;
		}
		return result;
	}

	float GameObject::TotalMaxHealth()
	{
		auto result = this->MaxHealth;
		if (this->Flags() & GameObjectFlags_AIHeroClient && this->BaseCharacterData->SkinHash == Character::Kled)
		{
			result += this->MaxSecondaryResource;
		}
		return result;
	}

	float GameObject::TotalShield()
	{
		auto result = this->AllShield;
		if (this->Flags() & GameObjectFlags_AIHeroClient && this->BaseCharacterData->SkinHash == Character::Blitzcrank)
		{
			for (auto buffManager : this->Buffs)
			{
				auto buff = buffManager.Buff;
				if (buff->IsActive())
				{
					auto hash = buff->Script->Hash;
					if (hash == 0x6FF6CCC4 // "BlitzcrankManaBarrierCD"
					|| hash == 0xDEE0E3A1) // "ManaBarrier"
					{
						return result;
					}
				}
			}
			result += this->Resource * 0.5f;
		}
		return result;
	}

	bool GameObject::CanAttack()
	{
		return this->ActionState & GameObjectActionState_CanAttack;
	}

	bool GameObject::CanCrit()
	{
		return this->ActionState & GameObjectActionState_CanCrit;
	}

	bool GameObject::CanCast()
	{
		return this->ActionState & GameObjectActionState_CanCast;
	}

	bool GameObject::CanMove()
	{
		return this->ActionState & GameObjectActionState_CanMove;
	}

	bool GameObject::IsImmovable()
	{
		return this->ActionState & GameObjectActionState_Immovable;
	}

	bool GameObject::IsStealthed()
	{
		return this->ActionState & GameObjectActionState_Stealthed;
	}

	bool GameObject::IsTaunted()
	{
		return this->ActionState & GameObjectActionState_Taunted;
	}

	bool GameObject::IsFeared()
	{
		return this->ActionState & GameObjectActionState_Feared;
	}

	bool GameObject::IsFleeing()
	{
		return this->ActionState & GameObjectActionState_Fleeing;
	}

	bool GameObject::IsSupressed()
	{
		return this->ActionState & GameObjectActionState_Supressed;
	}

	bool GameObject::IsAsleep()
	{
		return this->ActionState & GameObjectActionState_Sleep;
	}

	bool GameObject::IsGhosted()
	{
		return this->ActionState & GameObjectActionState_Ghosted;
	}

	bool GameObject::IsCharmed()
	{
		return this->ActionState & GameObjectActionState_Charmed;
	}

	bool GameObject::IsSlowed()
	{
		return this->ActionState & GameObjectActionState_Slowed;
	}

	bool GameObject::IsDisarmed()
	{
		return !(this->ActionState & (GameObjectActionState_CanAttack | GameObjectActionState_Charmed | GameObjectActionState_Fleeing | GameObjectActionState_Taunted | GameObjectActionState_Sleep | GameObjectActionState_Supressed)) && !(this->StatusFlags & GameObjectStatusFlags_Invulnerable);
	}

	bool GameObject::IsRooted()
	{
		return !(this->ActionState & (GameObjectActionState_CanMove | GameObjectActionState_Charmed | GameObjectActionState_Fleeing | GameObjectActionState_Taunted | GameObjectActionState_Sleep | GameObjectActionState_Supressed)) && !(this->StatusFlags & GameObjectStatusFlags_Invulnerable);
	}

	bool GameObject::IsSilenced()
	{
		return !(this->ActionState & (GameObjectActionState_CanCast | GameObjectActionState_Charmed | GameObjectActionState_Fleeing | GameObjectActionState_Taunted | GameObjectActionState_Sleep | GameObjectActionState_Supressed)) && !(this->StatusFlags & GameObjectStatusFlags_Invulnerable);
	}

	bool GameObject::IsStunned()
	{
		return !(this->ActionState & (GameObjectActionState_CanAttack | GameObjectActionState_CanMove | GameObjectActionState_CanCast | GameObjectActionState_Charmed | GameObjectActionState_Fleeing | GameObjectActionState_Taunted | GameObjectActionState_Sleep | GameObjectActionState_Supressed)) && !(this->StatusFlags & GameObjectStatusFlags_Invulnerable);
	}

	float GameObject::TotalBaseAttackDamage()
	{
		return (this->BaseAttackDamage + this->FlatBaseAttackDamageMod) * (1.0f + this->PercentBaseAttackDamageMod);
	}

	float GameObject::TotalBonusAttackDamage()
	{
		return this->FlatAttackDamageMod * (1.0f + this->PercentBonusAttackDamageMod);
	}

	float GameObject::TotalAttackDamage()
	{
		return (this->TotalBaseAttackDamage() + this->TotalBonusAttackDamage()) * (1.0f + this->PercentAttackDamageMod);
	}

	float GameObject::TotalAbilityPower()
	{
		return this->BaseAbilityPower + this->FlatAbilityPowerMod * (1.0f + this->PercentAbilityPowerMod);
	}

	float GameObject::GetAutoAttackRange(GameObject* target)
	{
		auto sourceFlags = this->Flags();

		if (sourceFlags & GameObjectFlags_AIHeroClient)
		{
			auto result = this->AttackRange + this->GetBoundingRadius();
			if (target)
			{
				result += target->GetBoundingRadius();
				switch (this->BaseCharacterData->SkinHash)
				{
				case Character::Caitlyn:
					if (target->Flags() & GameObjectFlags_AIBaseClient && target->FindBuff(0x1E8B8CA0)) // caitlynyordletrapinternal
					{
						result += 650.0f;
					}
					break;
				}
			}
			return result;
		}
		else if (sourceFlags & GameObjectFlags_AIMinionClient)
		{
			switch (this->BaseCharacterData->SkinHash)
			{
			case Character::AzirSoldier:
				return this->BaseCharacterData->Properties->AttackRange - this->GetBoundingRadius();
			}
		}

		return 0.0f;
	}

	bool GameObject::IsInAutoAttackRange(GameObject* target) {
		if (this == ObjectManager::Player && this->BaseCharacterData->SkinHash == Character::Azir) {
			for (auto soldier : SDK::Orbwalker::AzirSoldiers) {
				if (!soldier->IsDead() && ObjectManager::Player->GetPathController()->ServerPosition.IsInRange(soldier->Position, 790.0f)) {
					auto pathController = soldier->GetPathController();
					if ((!pathController->HasNavigationPath || !pathController->GetNavigationPath()->IsDashing) && soldier->IsInAutoAttackRange(target)) {
						return true;
					}
				}
			}
		}

		return this->GetPathController()->ServerPosition.IsInRange(target->GetPathController()->ServerPosition, this->GetAutoAttackRange(target));
	}

	bool GameObject::IsMelee()
	{
		return this->CombatType == GameObjectCombatType::Melee;
	}

	bool GameObject::IsRanged()
	{
		return !this->IsMelee();
	}

	unsigned int GameObject::BuffCount()
	{
		return this->Buffs.size();
	}

	BuffInstance* GameObject::GetBuff(unsigned int index)
	{
		return this->Buffs[index].Buff;
	}

	BuffInstance* GameObject::FindBuff(unsigned int hash)
	{
		for (auto buffManager : Buffs)
		{
			auto buff = buffManager.Buff;
			if (buff->IsActive() && buff->Script->Hash == hash)
			{
				return buff;
			}
		}
		return nullptr;
	}


	BuffInstance* GameObject::FindBuff(std::string name)
	{
		for (auto buffManager : Buffs)
		{
			auto buff = buffManager.Buff;
			if (buff->IsActive() && buff->Script->Name == name)
			{
				return buff;
			}
		}
		return nullptr;
	}

	SpellCastInfo* GameObject::ActiveSpell()
	{
		return this->Spellbook.ActiveSpellInstance->GetCastInfo();
	}

	Character GameObject::Hash()
	{
		return this->BaseCharacterData->SkinHash;
	}

	bool GameObject::IsLaneMinion()
	{
		switch (this->BaseCharacterData->SkinHash)
		{
		case Character::SRU_ChaosMinionMelee:
		case Character::SRU_OrderMinionMelee:
		case Character::SRU_ChaosMinionRanged:
		case Character::SRU_OrderMinionRanged:
		case Character::SRU_ChaosMinionSiege:
		case Character::SRU_OrderMinionSiege:
		case Character::SRU_ChaosMinionSuper:
		case Character::SRU_OrderMinionSuper:
		case Character::HA_ChaosMinionMelee:
		case Character::HA_OrderMinionMelee:
		case Character::HA_ChaosMinionRanged:
		case Character::HA_OrderMinionRanged:
		case Character::HA_ChaosMinionSiege:
		case Character::HA_OrderMinionSiege:
		case Character::HA_ChaosMinionSuper:
		case Character::HA_OrderMinionSuper:
			return true;
		default:
			return false;
		}
	}

	bool GameObject::IsSiegeMinion() {
		switch (this->BaseCharacterData->SkinHash) {
		case Character::SRU_ChaosMinionSiege:
		case Character::SRU_OrderMinionSiege:
		case Character::HA_ChaosMinionSiege:
		case Character::HA_OrderMinionSiege:
			return true;
		default:
			return false;
		}
	}

	bool GameObject::IsPet()
	{
		switch (this->BaseCharacterData->SkinHash)
		{
		case Character::AnnieTibbers:
		case Character::EliseSpiderling:
		case Character::GangplankBarrel:
		case Character::HeimerTBlue:
		case Character::HeimerTYellow:
		case Character::IvernMinion:
		case Character::MalzaharVoidling:
		case Character::ShacoBox:
		case Character::VoidSpawn:
		case Character::VoidSpawnTracer:
		case Character::YorickGhoulMelee:
		case Character::YorickBigGhoul:
		case Character::ZyraThornPlant:
		case Character::ZyraGraspingPlant:
			return true;
		default:
			return false;
		}
	}

	bool GameObject::IsWard()
	{
		switch (this->BaseCharacterData->SkinHash)
		{
		case Character::JammerDevice:
		case Character::SightWard:
		case Character::BlueTrinket:
		case Character::YellowTrinket:
			return true;
		default:
			return false;
		}
	}

	bool GameObject::IsPlant()
	{
		switch (this->BaseCharacterData->SkinHash)
		{
		case Character::SRU_Plant_Health:
		case Character::SRU_Plant_Satchel:
		case Character::SRU_Plant_Vision:
			return true;
		default:
			return false;
		}
	}

	bool GameObject::IsLargeMonster()
	{
		switch (this->BaseCharacterData->SkinHash)
		{
		case Character::SRU_Razorbeak:
		case Character::SRU_Murkwolf:
		case Character::SRU_Gromp:
		case Character::SRU_Krug:
		case Character::SRU_Red:
		case Character::SRU_Blue:
		case Character::Sru_Crab:
			return true;
		default:
			return false;
		}
	}

	bool GameObject::IsEpicMonster()
	{
		switch (this->BaseCharacterData->SkinHash)
		{
		case Character::SRU_Dragon_Air:
		case Character::SRU_Dragon_Earth:
		case Character::SRU_Dragon_Fire:
		case Character::SRU_Dragon_Water:
		case Character::SRU_Dragon_Elder:
		case Character::SRU_Baron:
		case Character::SRU_RiftHerald:
			return true;
		default:
			return false;
		}
	}

	SpellData* GameObject::GetBasicAttack()
	{
		return this->AttackData->SpellData;
	}

	unsigned int GameObject::ItemSlotsCount()
	{
		return 7;
	}

	InventorySlot* GameObject::GetItem(unsigned int index)
	{
		return this->HeroInventory.Slots[index];
	}

	InventorySlot* GameObject::FindItem(Item itemId)
	{
		auto inventorySlots = this->HeroInventory.Slots;
		for (auto i = 0; i < 7; i++)
		{
			auto item = inventorySlots[i];
			auto itemInfo = item->ItemInfo;
			if (itemInfo && itemInfo->ItemData->ItemId == itemId)
			{
				return item;
			}
		}
		return nullptr;
	}

	float GameObject::GetAutoAttackDamage(GameObject* target)
	{
		return SDK::Damage::CalculateAutoAttackDamage(this, target);
	}
}