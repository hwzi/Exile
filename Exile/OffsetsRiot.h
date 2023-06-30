#pragma once

namespace Exile {
	namespace Offsets {
		enum class ClockFacade {
			Instance = 0x16852C8,
			GetGameTime = 0x720F80,

			FrameClock = 0x8,
		};

		enum class DeviceHandler {
			Instance = 0x2F49D38,

			Direct3DDevice = 0x1A0
		};

		enum class ManagerTemplate {
			AIBases = 0x2F1B4DC,
			Turrets = 0x2F1B45C,
			Heroes = 0x22D807C,
			Minions = 0x22D81F4,
		};

		enum class GameClient {
			Instance = 0x2F23618,

			GameState = 0x8,
		};

		enum class HashFunctions {
			TranslateString = 0x66CD10,
		};

		enum class HudManager {
			Instance = 0x168773C,

			CursorTargetLogic = 0x14,
			SelectLogic = 0x30,
		};

		enum class NetClient {
			Instance = 0x2F2B160,
			GetPing = 0x357490,
		};

		enum class ObjectManager {
			Instance = 0x16466F8,
			Player = 0x2F26120,

			ObjectsArray = 0x8,
			MaxObjects = 0xC,
		};

		enum class RenderLayer {
			Instance = 0x2F43C1C,
			WorldToScreen = 0x7D59E0,

			ClientWidth = 0x18,
			ClientHeight = 0x1C, 
			ViewMatrix = 0x64,
			ProjectionMatrix = 0xA4,
		};

		enum class RiotWindow {
			Instance = 0x2F3A798,
		};

		///////////////////////////////////FUNCTIONS//////////////////////////////////////

		enum class Functions {
			ChangerCharacterData = 0x181A00,
			IssueOrder = 0x1BE660,
			CastSpell = 0x59F3B0,
			GetAttackCastDelay = 0x5A5FE0,
			GetAttackDelay = 0x5A60C0,
		};

		///////////////////////////////////STRUCTS///////////////////////////////////////

		enum class HudCursorTargetLogic {
			CursorPosition = 0x1C,
			HoveredUnitId = 0x3C,
		};

		enum class GameObject {
			Virtual_GetBoundingRadius = 36,
			Virtual_GetPathController = 148,

			ClassData = 0x4,
			Id = 0x1C,
			Team = 0x44,
			Flags = 0x48,
			Name = 0x60,
			NetworkId = 0xB8,
			IsDead = 0x1D4,
			Position = 0x1DC,
			IsVisible = 0x3D0,
			Resource = 0x3F8,
			MaxResource = Resource + 0x10,
			ResourceType = MaxResource + 0x40,
			SecondaryResource = ResourceType + 0x10,
			MaxSecondaryResource = SecondaryResource + 0x10,
			StatusFlags = 0x504,
			IsUntargetableToEnemies = 0xD40,
			IsUntargetableToAllies = IsUntargetableToEnemies + 0x10,
			IsTargetable = IsUntargetableToAllies + 0x10,
			Health = 0xDE8,
			MaxHealth = Health + 0x10,
			AllShield = MaxHealth + 0x30,
			PhysicalShield = AllShield + 0x10,
			MagicalShield = PhysicalShield + 0x10,
			ActionState = 0x1040,
			CharacterIntermediate = 0x1658,
			CombatType = 0x2000,
			Buffs = 0x2100,
			Spellbook = 0x28A8,
			CharacterDataStack = 0x314C,
			SkinName = 0x32D4,
			CharacterData = 0x30D8,
			BaseCharacterData = CharacterData + 0x4,
			AttackData = 0x475C,
			Experience = 0x492C,
			HeroInventory = 0x4970,
		};

		enum class ClassData {
			Type = 0x0,
			Name = 0x18
		};

		enum class SpellCastInfo {
			SpellData = 0x0,
			Level = 0x54,
			StartPosition = 0x74,
			EndPosition = 0x80,
			TargetId = 0xA8,
			CastDelay = 0x4A8,
			Delay = 0x4B8,
			IsBasicAttack = 0x4C9,
			IsSpecialAttack = 0x4CA,
			Slot = 0x4D0,
			StartTime = 0x51C,
			CastEndTime = 0x520,
			EndTime = 0x524,
			SpellWasCast = 0x528,
			IsStopped = 0x52B,
			IsInstantCast = 0x52D,
		};

		enum class SpellData {
			Script = 0xC,
			Name = 0x18,
			Resource = 0x38,
		};

		enum class SpellDataScript {
			Name = 0x8,
			Hash = 0x88
		};

		enum class SpellDataResource {
			DisplayNameLocalizationKey = 0x88,
			eEffect1 = 0xD0,
			eEffect2 = eEffect1 + 0x1C,
			eEffect3 = eEffect2 + 0x1C,
			eEffect4 = eEffect3 + 0x1C,
			eEffect5 = eEffect4 + 0x1C,
			eEffect6 = eEffect5 + 0x1C,
			eEffect7 = eEffect6 + 0x1C,
			eEffect8 = eEffect7 + 0x1C,
			eEffect9 = eEffect8 + 0x1C,
			eEffect10 = eEffect9 + 0x1C,
			eEffect11 = eEffect10 + 0x1C,
			aEffect1 = 0x200,
			aEffect2 = 0x204,
			CantCancelWhileWindingUp = 0x37A,
			CantCancelWhileChanneling = 0x37C,
			ChannelIsInterruptedByAttacking = 0x37F,
			CanMoveWhileChanneling = 0x390,
			MissileSpeed = 0x450,
		};

		enum class CharacterIntermediate {
			PassiveCooldownEndTime = 0x20,
			PassiveCooldownTotalTime = 0x30,
			PercentDamageToBarracksMinionMod = 0x40,
			FlatDamageReductionFromBarracksMinionMod = 0x50,
			FlatAttackDamageMod = 0x70,
			PercentAttackDamageMod = 0x80,
			PercentBonusAttackDamageMod = 0x90,
			FlatAbilityPowerMod = 0xB0,
			PercentAbilityPowerMod = 0xC0,
			FlatMagicReduction = 0xD0,
			PercentMagicReduction = 0xE0,
			AttackSpeedMod = 0x100,
			BaseAttackDamage = 0x130,
			FlatBaseAttackDamageMod = 0x150,
			PercentBaseAttackDamageMod = 0x160,
			BaseAbilityPower = 0x170,
			Armor = 0x1C0,
			BonusArmor = 0x1D0,
			MagicResist = 0x1E0,
			BonusMagicResist = 0x1F0,
			MoveSpeed = 0x220,
			AttackRange = 0x240,
			PhysicalLethality = 0x280,
			PercentArmorPenetration = 0x290,
			PercentBonusArmorPenetration = 0x2A0,
			FlatMagicPenetration = 0x2D0,
			PercentMagicPenetration = 0x2F0,
			PercentBonusMagicPenetration = 0x300,
		};

		enum class BuffInstance {
			Type = 0x4,
			Script = 0x8,
			StartTime = 0xC,
			ExpireTime = 0x10,
			ScriptInfo = 0x20,
			IsPermanent = 0x70,
			Counter = 0x74,
		};

		enum class BuffScript {
			Virtual_GetDisplayName = 14,

			Name = 0x8,
			Hash = 0x88
		};

		enum class BuffScriptInstance {
			CasterId = 0x4
		};

		enum class SpellbookClient {
			Virtual_GetSpellState = 1,
			Virtual_GetSpell = 19,

			ActiveSpellInstance = 0x20
		};

		enum class SpellInstanceClient {
			CastInfo = 0x8
		};

		enum class SpellDataInst {
			Level = 0x20,
			fEffect1 = 0x84,
			fEffect2 = fEffect1 + 0x4,
			fEffect3 = fEffect2 + 0x4,
			fEffect4 = fEffect3 + 0x4,
			fEffect5 = fEffect4 + 0x4,
			fEffect6 = fEffect5 + 0x4,
			fEffect7 = fEffect6 + 0x4,
			fEffect8 = fEffect7 + 0x4,
			fEffect9 = fEffect8 + 0x4,
			fEffect10 = fEffect9 + 0x4,
			fEffect11 = fEffect10 + 0x4,
			SpellData = 0x12C,
		};

		enum class CharacterDataStack {
			SkinName = 0xC,
			SkinId = 0x24
		};

		enum class CharacterData {
			SkinName = 0x4,
			SkinHash = 0x10,
			Properties = 0x1C
		};

		enum class CharacterProperties {
			AttackRange = 0x19C,
		};

		enum class Experience {
			Level = 0x10,
		};

		enum class HeroInventoryCommon {
			Slots = 0x18,
		};

		enum class InventorySlot {
			ItemInfo = 0xC
		};

		enum class ItemInfo {
			ItemData = 0x20,
		};

		enum class ItemData {
			ItemId = 0x64,
		};

		enum class PathControllerCommon {
			HasNavigationPath = 0x198,
			NavigationPath = 0x19C,
			ServerPosition = 0x2BC,
		};

		enum class NavigationPath {
			Index = 0x0,
			StartPosition = 0x8,
			EndPosition = StartPosition + 0xC,
			Path = EndPosition + 0xC,
			DashSpeed = 0x34,
			IsDashing = 0x4C
		};

		enum class AvatarClient
		{
			HasRunes = 0x1E4,
			Runes = 0x300,
		};

		enum class RuneInstance {
			Id = 0x4,
		};
	}
}