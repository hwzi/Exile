#pragma once

#include "stdafx.h"
#include "GameObject.h"

namespace Exile {
	namespace SDK {
		enum kOrbwalkerMode {
			OrbwalkerMode_None = 0,
			OrbwalkerMode_Combo = 1 << 0,
			OrbwalkerMode_Harass = 1 << 1,
			OrbwalkerMode_LastHit = 1 << 2,
			OrbwalkerMode_LaneClear = 1 << 3,
			OrbwalkerMode_JungleClear = 1 << 4,
			OrbwalkerMode_Flee = 1 << 5
		};

		enum class OrbwalkerTargetType {
			Hero,
			Monster,
			Minion,
			Structure
		};

		namespace Orbwalker {
			extern GameObject* LastHitMinion;
			extern GameObject* AlmostLastHitMinion;
			extern GameObject* LaneClearMinion;
			extern GameObjectOrder LastOrder;
			extern float LastAttackOrder;
			extern float LastMoveOrder;
			extern float LastShouldWait;
			extern GameObject* LastTarget;
			extern Vector3 LastMovePosition;
			extern float LastAttack;
			extern float LastAttackCastEndTime;
			extern unsigned int ActiveMode;

			//special stuff for champions
			extern bool IsAzir;
			extern std::vector<GameObject*> AzirSoldiers;
			extern bool IsAshe;
			extern bool IsGraves;
			extern bool IsRengar;
			extern bool AttackUsesAmmo;
			extern kSpellSlot AttackResetSlot;
			extern unsigned int AttackResetHash;
			extern bool IsDashAttackReset;

			//stuff people can set
			extern GameObject* ForcedTarget;
			extern Vector3 ForcedPosition;

			void Initialize();
			void Dispose();

			bool OnIssueOrder(GameObject* unit, GameObjectOrder order, Vector3 position, GameObject* target);
			void OnSpellCast(kSpellSlot slot);
			void OnProcessSpell(GameObject* unit, SpellCastInfo* castInfo);
			void OnStopCast(GameObject* unit, float castEndTime);
			void OnNewPath(GameObject* unit, NavigationPath* navigationPath);
			void OnCreateObject(GameObject* unit);
			void OnDeleteObject(GameObject* unit);
			void OnGameUpdate();
			void OnDraw();

			void ResetAutoAttack();
			Vector3 GetOrbwalkPosition();
			GameObject* GetTarget();
			GameObject* GetTargetByType(OrbwalkerTargetType targetType);
			bool ShouldWait();
			void OrbwalkTo(Vector3 position);
			void MoveTo(Vector3 position);
			float GetAttackCastDelay(GameObject* target = nullptr);
			float GetAttackDelay(GameObject* target = nullptr);
			float GetAttackMissileSpeed();
			bool CanAttack();
			bool CanMove();
		}
	}
}