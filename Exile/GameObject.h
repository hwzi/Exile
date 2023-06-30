#pragma once

#include "Offsets.h"
#include "ClassData.h"
#include "Vector2.h"
#include "Vector3.h"
#include "SpellCastInfo.h"
#include "BuffManager.h"
#include "CharacterDataStack.h"
#include "SpellbookClient.h"
#include "CharacterData.h"
#include "Experience.h"
#include "HeroInventoryCommon.h"
#include "PathControllerCommon.h"
#include "SpellDataInst.h"

namespace Exile
{
	enum kGameObjectTeam
	{
		GameObjectTeam_None,
		GameObjectTeam_Order = 100,
		GameObjectTeam_Chaos = 200,
		GameObjectTeam_Neutral = 300
	};

	enum kGameObjectFlags
	{
		GameObjectFlags_AIBaseClient = 1 << 10,
		GameObjectFlags_AIMinionClient = 1 << 11,
		GameObjectFlags_AIHeroClient = 1 << 12,
		GameObjectFlags_AITurretClient = 1 << 13,
		GameObjectFlags_MissileClient = 1 << 15,
	};

	enum class GameObjectResourceType : BYTE
	{
		Mana,
		Energy,
		None,
		Shield,
		BattleFury,
		DragonFury,
		Rage,
		Heat,
		GnarFury,
		Ferocity,
		BloodWell,
		Wind,
		Other,
	};

	enum kGameObjectStatusFlags
	{
		GameObjectStatusFlags_Invulnerable = 1 << 0,
		GameObjectStatusFlags_MagicImmune = 1 << 6,
		GameObjectStatusFlags_PhysicalImmune = 1 << 7,
	};

	enum kGameObjectActionState
	{
		GameObjectActionState_CanAttack = 1 << 0,
		GameObjectActionState_CanCrit = 1 << 1,
		GameObjectActionState_CanCast = 1 << 2,
		GameObjectActionState_CanMove = 1 << 3,
		GameObjectActionState_Immovable = 1 << 4,
		GameObjectActionState_Stealthed = 1 << 5,
		GameObjectActionState_Obscured = 1 << 6,
		GameObjectActionState_Taunted = 1 << 7,
		GameObjectActionState_Feared = 1 << 8,
		GameObjectActionState_Fleeing = 1 << 9,
		GameObjectActionState_Supressed = 1 << 10,
		GameObjectActionState_Sleep = 1 << 11,
		GameObjectActionState_Ghosted = 1 << 13,
		GameObjectActionState_Charmed = 1 << 17,
		GameObjectActionState_Slowed = 1 << 24,
	};

	enum class DampenerState
	{
		Alive,
		Destroyed
	};

	enum class GameObjectCombatType
	{
		Melee = 1,
		Ranged,
	};

	enum class GameObjectOrder
	{
		None = 0,
		HoldPosition,
		MoveTo,
		AttackUnit,
		AutoAttackPet,
		AutoAttack,
		MovePet,
		AttackTo,
		Stop = 10,
	};

	class GameObject
	{
	public:
		union
		{
			DEFINE_MEMBER_0(DWORD* VTable)
			DEFINE_MEMBER_N(unsigned short Id, Offsets::GameObject::Id)
			DEFINE_MEMBER_N(kGameObjectTeam Team, Offsets::GameObject::Team)
			DEFINE_MEMBER_N(std::string Name, Offsets::GameObject::Name)
			DEFINE_MEMBER_N(unsigned int NetworkId, Offsets::GameObject::NetworkId)
			DEFINE_MEMBER_N(Vector3 Position, Offsets::GameObject::Position)
			DEFINE_MEMBER_N(bool IsVisible, Offsets::GameObject::IsVisible)
			DEFINE_MEMBER_N(float Resource, Offsets::GameObject::Resource)
			DEFINE_MEMBER_N(float MaxResource, Offsets::GameObject::MaxResource)
			DEFINE_MEMBER_N(GameObjectResourceType ResourceType, Offsets::GameObject::ResourceType)
			DEFINE_MEMBER_N(float SecondaryResource, Offsets::GameObject::SecondaryResource)
			DEFINE_MEMBER_N(float MaxSecondaryResource, Offsets::GameObject::MaxSecondaryResource)
			DEFINE_MEMBER_N(kGameObjectStatusFlags StatusFlags, Offsets::GameObject::StatusFlags)
			DEFINE_MEMBER_N(bool IsUntargetableToEnemies, Offsets::GameObject::IsUntargetableToEnemies)
			DEFINE_MEMBER_N(bool IsUntargetableToAllies, Offsets::GameObject::IsUntargetableToAllies)
			DEFINE_MEMBER_N(bool IsTargetable, Offsets::GameObject::IsTargetable)
			DEFINE_MEMBER_N(float Health, Offsets::GameObject::Health)
			DEFINE_MEMBER_N(float MaxHealth, Offsets::GameObject::MaxHealth)
			DEFINE_MEMBER_N(float AllShield, Offsets::GameObject::AllShield)
			DEFINE_MEMBER_N(float PhysicalShield, Offsets::GameObject::PhysicalShield)
			DEFINE_MEMBER_N(float MagicalShield, Offsets::GameObject::MagicalShield)
			DEFINE_MEMBER_N(kGameObjectActionState ActionState, Offsets::GameObject::ActionState)
			DEFINE_CHARACTER_INTERMEDIATE(PassiveCooldownEndTime)
			DEFINE_CHARACTER_INTERMEDIATE(PassiveCooldownTotalTime)
			DEFINE_CHARACTER_INTERMEDIATE(PercentDamageToBarracksMinionMod)
			DEFINE_CHARACTER_INTERMEDIATE(FlatDamageReductionFromBarracksMinionMod)
			DEFINE_CHARACTER_INTERMEDIATE(FlatAttackDamageMod)
			DEFINE_CHARACTER_INTERMEDIATE(PercentAttackDamageMod)
			DEFINE_CHARACTER_INTERMEDIATE(PercentBonusAttackDamageMod)
			DEFINE_CHARACTER_INTERMEDIATE(FlatAbilityPowerMod)
			DEFINE_CHARACTER_INTERMEDIATE(PercentAbilityPowerMod)
			DEFINE_CHARACTER_INTERMEDIATE(FlatMagicReduction)
			DEFINE_CHARACTER_INTERMEDIATE(PercentMagicReduction)
			DEFINE_CHARACTER_INTERMEDIATE(AttackSpeedMod)
			DEFINE_CHARACTER_INTERMEDIATE(BaseAttackDamage)
			DEFINE_CHARACTER_INTERMEDIATE(FlatBaseAttackDamageMod)
			DEFINE_CHARACTER_INTERMEDIATE(PercentBaseAttackDamageMod)
			DEFINE_CHARACTER_INTERMEDIATE(BaseAbilityPower)
			DEFINE_CHARACTER_INTERMEDIATE(Armor)
			DEFINE_CHARACTER_INTERMEDIATE(BonusArmor)
			DEFINE_CHARACTER_INTERMEDIATE(MagicResist)
			DEFINE_CHARACTER_INTERMEDIATE(BonusMagicResist)
			DEFINE_CHARACTER_INTERMEDIATE(MoveSpeed)
			DEFINE_CHARACTER_INTERMEDIATE(AttackRange)
			DEFINE_CHARACTER_INTERMEDIATE(PhysicalLethality)
			DEFINE_CHARACTER_INTERMEDIATE(PercentArmorPenetration)
			DEFINE_CHARACTER_INTERMEDIATE(PercentBonusArmorPenetration)
			DEFINE_CHARACTER_INTERMEDIATE(FlatMagicPenetration)
			DEFINE_CHARACTER_INTERMEDIATE(PercentMagicPenetration)
			DEFINE_CHARACTER_INTERMEDIATE(PercentBonusMagicPenetration)
			DEFINE_MEMBER_N(GameObjectCombatType CombatType, Offsets::GameObject::CombatType)
			DEFINE_MEMBER_N(std::vector<BuffManager> Buffs, Offsets::GameObject::Buffs)
			DEFINE_MEMBER_N(CharacterDataStack CharacterDataStack, Offsets::GameObject::CharacterDataStack)
			DEFINE_MEMBER_N(std::string SkinName, Offsets::GameObject::SkinName)
			DEFINE_MEMBER_N(SpellbookClient Spellbook, Offsets::GameObject::Spellbook)
			DEFINE_MEMBER_N(Exile::CharacterData* CharacterData, Offsets::GameObject::CharacterData)
			DEFINE_MEMBER_N(Exile::CharacterData* BaseCharacterData, Offsets::GameObject::BaseCharacterData)
			DEFINE_MEMBER_N(SpellCastInfo* AttackData, Offsets::GameObject::AttackData)
			DEFINE_EXPERIENCE(unsigned int, Level)
			DEFINE_MEMBER_N(HeroInventoryCommon HeroInventory, Offsets::GameObject::HeroInventory)
		};
		DEFINE_MEMBER_ENCRYPTED(ClassData*, GetClassData, Offsets::GameObject::ClassData)
		DEFINE_MEMBER_ENCRYPTED(kGameObjectFlags, Flags, Offsets::GameObject::Flags)
		DEFINE_MEMBER_ENCRYPTED_BOOLEAN(IsDead, Offsets::GameObject::IsDead)

		//VTable functions
		float GetBoundingRadius();
		PathControllerCommon* GetPathController();
		
		//Functions
		float GetAttackCastDelay();
		float GetAttackDelay();
		SpellDataInst* GetSpell(kSpellSlot slot);
		kSpellState GetSpellState(kSpellSlot slot);
		void CastSpell(kSpellSlot slot);
		void CastSpell(kSpellSlot slot, Vector3 position);
		void CastSpell(kSpellSlot slot, Vector3 start_position, Vector3 end_position);
		void CastSpell(kSpellSlot slot, GameObject* target);
		void IssueOrder(GameObjectOrder order, GameObject* target);
		void IssueOrder(GameObjectOrder order, Vector3 position);

		//Extensions
		bool IsMe();
		bool IsMoving();
		unsigned int PathIndex();
		unsigned int PathCount();
		Vector3 GetPath(unsigned int index);
		bool IsDashing();
		float DashSpeed();
		Vector3 ServerPosition();
		unsigned int RuneCount();
		GameObjectType Type();
		bool IsStructure();
		bool IsAlly();
		bool IsEnemy();
		bool IsNeutral();
		bool IsMonster();
		bool IsBaseAI();
		bool IsMinion();
		bool IsHero();
		bool IsTurret();
		bool IsMissile();
		bool IsInvulnerable();
		bool IsMagicImmune();
		bool IsPhysicalImmune();
		bool IsValidTarget(float range = FLT_MAX, bool onlyEnemyTeam = false, Vector3 rangeCheckFrom = Vector3::Zero);
		float TotalHealth();
		float TotalMaxHealth();
		float TotalShield();
		bool CanAttack();
		bool CanCrit();
		bool CanCast();
		bool CanMove();
		bool IsImmovable();
		bool IsStealthed();
		bool IsTaunted();
		bool IsFeared();
		bool IsFleeing();
		bool IsSupressed();
		bool IsAsleep();
		bool IsGhosted();
		bool IsCharmed();
		bool IsSlowed();
		bool IsDisarmed();
		bool IsRooted();
		bool IsSilenced();
		bool IsStunned();
		float TotalBaseAttackDamage();
		float TotalBonusAttackDamage();
		float TotalAttackDamage();
		float TotalAbilityPower();
		float GetAutoAttackRange(GameObject* target = nullptr);
		bool IsInAutoAttackRange(GameObject* target);
		bool IsMelee();
		bool IsRanged();
		unsigned int BuffCount();
		BuffInstance* GetBuff(unsigned int index);
		BuffInstance* FindBuff(unsigned int hash);
		BuffInstance* FindBuff(std::string name);
		SpellCastInfo* ActiveSpell();
		Character Hash();
		bool IsLaneMinion();
		bool IsSiegeMinion();
		bool IsPet();
		bool IsWard();
		bool IsPlant();
		bool IsLargeMonster();
		bool IsEpicMonster();
		SpellData* GetBasicAttack();
		unsigned int ItemSlotsCount();
		InventorySlot* GetItem(unsigned int index);
		InventorySlot* FindItem(Item itemId);
		float GetAutoAttackDamage(GameObject* target);
	};
}
