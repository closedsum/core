// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"

#pragma once

extern CSPRJ_API TAutoConsoleVariable<int32> CsCVarLogProjectileCollision;

#define CS_CVAR_DRAW_PROJECTILE_IMPACT_NORMAL_LENGTH 100.0f
#define CS_CVAR_DRAW_PROJECTILE_IMPACT_NORMAL_THICKNESS 2.0f
#define CS_CVAR_DRAW_PROJECTILE_IMPACT_NORMAL_DURATION 0.25f

extern CSPRJ_API TAutoConsoleVariable<int32> CsCVarDrawProjectileImpactNormal;
extern CSPRJ_API TAutoConsoleVariable<float> CsCVarDrawProjectileImpactNormalLength;
extern CSPRJ_API TAutoConsoleVariable<float> CsCVarDrawProjectileImpactNormalThickness;
extern CSPRJ_API TAutoConsoleVariable<float> CsCVarDrawProjectileImpactNormalDuration;

extern CSPRJ_API TAutoConsoleVariable<int32> CsCVarDrawProjectileCollision;

#define CS_CVAR_DRAW_PROJECTILE_PATH_INTERVAL 0.5f
#define CS_CVAR_DRAW_PROJECTILE_PATH_SEGMENTS_PER_INTERVAL 16
#define CS_CVAR_DRAW_PROJECTILE_PATH_THICKNESS 1.0f

extern CSPRJ_API TAutoConsoleVariable<int32> CsCVarDrawProjectilePath;
extern CSPRJ_API TAutoConsoleVariable<float> CsCVarDrawProjectilePathInterval;
extern CSPRJ_API TAutoConsoleVariable<int32> CsCVarDrawProjectilePathSegmentsPerInterval;
extern CSPRJ_API TAutoConsoleVariable<float> CsCVarDrawProjectilePathThickness;

// Scoped Timers
extern CSPRJ_API TAutoConsoleVariable<int32> CsCVarLogProjectileScopedTimer;
extern CSPRJ_API TAutoConsoleVariable<int32> CsCVarLogProjectileScopedTimerLaunchSetCollision;
extern CSPRJ_API TAutoConsoleVariable<int32> CsCVarLogProjectileScopedTimerLaunchSetVisualTrail;

// CVarLog
#pragma region

namespace NCsCVarLog
{
	extern CSPRJ_API const Type LogProjectileCollision;
	// Scoped Timers
	extern CSPRJ_API const Type LogProjectileScopedTimer;
	extern CSPRJ_API const Type LogProjectileScopedTimerLaunchSetCollision;
	extern CSPRJ_API const Type LogProjectileScopedTimerLaunchSetTrailVisual;

	namespace Map
	{
		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(LogProjectileCollision);
		// Scoped Timers
		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(LogProjectileScopedTimer);
		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(LogProjectileScopedTimerLaunchSetCollision);
		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(LogProjectileScopedTimerLaunchSetTrailVisual);
	}
}

#pragma endregion CVarLog

// CVarDraw
#pragma region

namespace NCsCVarDraw
{
	extern CSPRJ_API const Type DrawProjectileImpactNormal;
	extern CSPRJ_API const Type DrawProjectileImpactNormalLength;
	extern CSPRJ_API const Type DrawProjectileImpactNormalThickness;
	extern CSPRJ_API const Type DrawProjectileImpactNormalDuration;

	extern CSPRJ_API const Type DrawProjectileCollision;

	extern CSPRJ_API const Type DrawProjectilePath;
	extern CSPRJ_API const Type DrawProjectilePathInterval;
	extern CSPRJ_API const Type DrawProjectilePathSegmentsPerInterval;
	extern CSPRJ_API const Type DrawProjectilePathThickness;

	namespace Map
	{
		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(DrawProjectileImpactNormal);
		//extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(DrawProjectileImpactNormalLength);
		//extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(DrawProjectileImpactNormalThickness);
		//extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(DrawProjectileImpactNormalDuration);

		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(DrawProjectileCollision);

		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(DrawProjectilePath);
		//extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(DrawProjectilePathInterval);
		//extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(DrawProjectilePathSegmentsPerInterval);
		//extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(DrawProjectilePathThickness);
	}
}

#pragma endregion CVarLog

// ScopedGroup
#pragma region

namespace NCsScopedGroup
{
	extern CSPRJ_API const Type Projectile;

	namespace Map
	{
		extern CSPRJ_API CS_DECLARE_ADD_TO_CVAR_MAP(Projectile);
	}
}

#pragma endregion ScopedGroup