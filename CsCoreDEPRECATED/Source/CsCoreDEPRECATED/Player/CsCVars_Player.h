// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "CsCVars.h"

// OnBoard
#pragma region

extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarLogPlayerStateOnBoard;

#pragma endregion OnBoard

// View
#pragma region

#define CS_CVAR_DRAW_PLAYER_VIEW_FORWARD_LENGTH 100.0f
#define CS_CVAR_DRAW_PLAYER_VIEW_FORWARD_THICKNESS 2.0f
#define CS_CVAR_DRAW_PLAYER_VIEW_RIGHT_LENGTH 100.0f
#define CS_CVAR_DRAW_PLAYER_VIEW_RIGHT_THICKNESS 2.0f

extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarDrawPlayerViewForward;
extern CSCOREDEPRECATED_API TAutoConsoleVariable<float> CsCVarDrawPlayerViewForwardLength;
extern CSCOREDEPRECATED_API TAutoConsoleVariable<float> CsCVarDrawPlayerViewForwardThickness;
extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarDrawPlayerViewRight;
extern CSCOREDEPRECATED_API TAutoConsoleVariable<float> CsCVarDrawPlayerViewRightLength;
extern CSCOREDEPRECATED_API TAutoConsoleVariable<float> CsCVarDrawPlayerViewRightThickness;

#pragma endregion View

// Pawn
#pragma region

#define CS_CVAR_DRAW_PLAYER_PAWN_FORWARD_LENGTH 100.0f
#define CS_CVAR_DRAW_PLAYER_PAWN_FORWARD_THICKNESS 2.0f
#define CS_CVAR_DRAW_PLAYER_PAWN_RIGHT_LENGTH 100.0f
#define CS_CVAR_DRAW_PLAYER_PAWN_RIGHT_THICKNESS 2.0f

extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarDrawPlayerPawnForward;
extern CSCOREDEPRECATED_API TAutoConsoleVariable<float> CsCVarDrawPlayerPawnForwardLength;
extern CSCOREDEPRECATED_API TAutoConsoleVariable<float> CsCVarDrawPlayerPawnForwardThickness;
extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarDrawPlayerPawnRight;
extern CSCOREDEPRECATED_API TAutoConsoleVariable<float> CsCVarDrawPlayerPawnRightLength;
extern CSCOREDEPRECATED_API TAutoConsoleVariable<float> CsCVarDrawPlayerPawnRightThickness;

#pragma endregion Pawn

extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarDrawPlayerViewTraceHitLocation;

// Save
#pragma region

extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarPlayerSaveRebuild;

#pragma endregion Save

// Local Player
#pragma region

	// Weapon
#pragma region

extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarDrawLocalPlayerWeaponFireProjectile;

#pragma endregion Weapon

	// Projectile
#pragma region

#define CS_CVAR_DRAW_LOCAL_PLAYER_PROJECTILE_PATH_INTERVAL 0.5f
#define CS_CVAR_DRAW_LOCAL_PLAYER_PROJECTILE_PATH_SEGMENTS_PER_INTERVAL 16
#define CS_CVAR_DRAW_LOCAL_PLAYER_PROJECTILE_PATH_THICKNESS 1.0f

extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarDrawLocalPlayerProjectilePath;
extern CSCOREDEPRECATED_API TAutoConsoleVariable<float> CsCVarDrawLocalPlayerProjectilePathInterval;
extern CSCOREDEPRECATED_API TAutoConsoleVariable<int32> CsCVarDrawLocalPlayerProjectilePathSegmentsPerInterval;
extern CSCOREDEPRECATED_API TAutoConsoleVariable<float> CsCVarDrawLocalPlayerProjectilePathThickness;

#pragma endregion Projectile

#pragma endregion Local Player

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Player

		// OnBoard
	extern CSCOREDEPRECATED_API const Type LogPlayerStateOnBoard;

	namespace Map
	{
	}
}

#pragma endregion CVarLog