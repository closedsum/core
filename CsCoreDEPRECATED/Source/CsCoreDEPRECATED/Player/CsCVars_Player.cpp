// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Player/CsCVars_Player.h"

// OnBoard
#pragma region

TAutoConsoleVariable<int32> CsCVarLogPlayerStateOnBoard(
	TEXT("log.playerstate.onboard"),
	0,
	TEXT("Log PlayerState OnBoard"),
	ECVF_SetByConsole
);

#pragma endregion OnBoard

// View
#pragma region

TAutoConsoleVariable<int32> CsCVarDrawPlayerViewForward(
	TEXT("draw.player.view.forward"),
	0,
	TEXT("Draw the Forward vector from the center of the Player capsule."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<float> CsCVarDrawPlayerViewForwardLength(
	TEXT("draw.player.view.forwardlength"),
	CS_CVAR_DRAW_PLAYER_VIEW_FORWARD_LENGTH,
	TEXT("Length of the forward vector to be drawn from the Player view."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<float> CsCVarDrawPlayerViewForwardThickness(
	TEXT("draw.player.view.forwardthickness"),
	CS_CVAR_DRAW_PLAYER_VIEW_FORWARD_THICKNESS,
	TEXT("Thickness of the forward vector to be drawn from the Player view."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawPlayerViewRight(
	TEXT("draw.player.view.right"),
	0,
	TEXT("Draw the Right vector from the Player view."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<float> CsCVarDrawPlayerViewRightLength(
	TEXT("draw.player.view.rightlength"),
	CS_CVAR_DRAW_PLAYER_VIEW_RIGHT_LENGTH,
	TEXT("Length of the right vector to be drawn from the Player view."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<float> CsCVarDrawPlayerViewRightThickness(
	TEXT("draw.player.view.rightthickness"),
	CS_CVAR_DRAW_PLAYER_VIEW_RIGHT_THICKNESS,
	TEXT("Thickness of the right vector to be drawn from the Player view."),
	ECVF_SetByConsole
);

#pragma endregion View

// Pawn
#pragma region

TAutoConsoleVariable<int32> CsCVarDrawPlayerPawnForward(
	TEXT("draw.player.pawn.forward"),
	0,
	TEXT("Draw the Forward vector from the center of the Player capsule."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<float> CsCVarDrawPlayerPawnForwardLength(
	TEXT("draw.player.pawn.forwardlength"),
	CS_CVAR_DRAW_PLAYER_PAWN_FORWARD_LENGTH,
	TEXT("Length of the forward vector to be drawn from the center of the Player capsule."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<float> CsCVarDrawPlayerPawnForwardThickness(
	TEXT("draw.player.pawn.forwardthickness"),
	CS_CVAR_DRAW_PLAYER_PAWN_FORWARD_THICKNESS,
	TEXT("Thickness of the forward vector to be drawn from the center of the Player capsule."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawPlayerPawnRight(
	TEXT("draw.player.pawn.right"),
	0,
	TEXT("Draw the Right vector from the center of the Player capsule."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<float> CsCVarDrawPlayerPawnRightLength(
	TEXT("draw.player.pawn.rightlength"),
	CS_CVAR_DRAW_PLAYER_PAWN_RIGHT_LENGTH,
	TEXT("Length of the right vector to be drawn from the center of the Player capsule."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<float> CsCVarDrawPlayerPawnRightThickness(
	TEXT("draw.player.pawn.rightthickness"),
	CS_CVAR_DRAW_PLAYER_PAWN_RIGHT_THICKNESS,
	TEXT("Thickness of the right vector to be drawn from the center of the Player capsule."),
	ECVF_SetByConsole
);

#pragma endregion Pawn

TAutoConsoleVariable<int32> CsCVarDrawPlayerViewTraceHitLocation(
	TEXT("draw.player.view.tracehitlocation"),
	0,
	TEXT("Draw the Location traced out from the Player's Camera Location."),
	ECVF_SetByConsole
);

// Save
#pragma region

TAutoConsoleVariable<int32> CsCVarPlayerSaveRebuild(
	TEXT("player.save.rebuild"),
	0,
	TEXT("Player Save Rebuild."),
	ECVF_SetByConsole
);

#pragma endregion Save

// Local Player
#pragma region

	// Weapon
#pragma region

TAutoConsoleVariable<int32> CsCVarDrawLocalPlayerWeaponFireProjectile(
	TEXT("draw.localplayer.weapon.fireprojectile"),
	0,
	TEXT("Draw Projectile destinations from Weapon owned by the Local Player."),
	ECVF_SetByConsole
);

#pragma endregion Weapon

	// Projectile
#pragma region

TAutoConsoleVariable<int32> CsCVarDrawLocalPlayerProjectilePath(
	TEXT("draw.localplayer.projectile.path"),
	0,
	TEXT("Draw the Path for a Projectile instigated by the Local Player."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<float> CsCVarDrawLocalPlayerProjectilePathInterval(
	TEXT("draw.localplayer.projectile.pathinterval"),
	CS_CVAR_DRAW_LOCAL_PLAYER_PROJECTILE_PATH_INTERVAL,
	TEXT("The interval at which segments are drawn for the Path of a Projectile instigated by the Local Player."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawLocalPlayerProjectilePathSegmentsPerInterval(
	TEXT("draw.localplayer.projectile.pathsegmentsperinterval"),
	CS_CVAR_DRAW_LOCAL_PLAYER_PROJECTILE_PATH_SEGMENTS_PER_INTERVAL,
	TEXT("Number of segments used to draw the Path for a Projectile instigated by the Local Player."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<float> CsCVarDrawLocalPlayerProjectilePathThickness(
	TEXT("draw.localplayer.projectile.paththickness"),
	CS_CVAR_DRAW_LOCAL_PLAYER_PROJECTILE_PATH_THICKNESS,
	TEXT("Thickness of the Path to be drawn for a Projectile instigated by the Local Player."),
	ECVF_SetByConsole
);

#pragma endregion Projectile

#pragma endregion Local Player

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Player

		// OnBoard
	CSCOREDEPRECATED_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogPlayerStateOnBoard);

	namespace Map
	{
	}
}

#pragma endregion CVarLog