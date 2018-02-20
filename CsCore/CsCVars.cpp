// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"
#include "CsCore.h"

// Loading
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerLoading(
	TEXT("log.manager.loading"),
	0,
	TEXT("Log Manager Loading"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarManagerLoadingAsyncOrder(
	TEXT("manager.loading.asyncorder"),
	-1,
	TEXT("Set Load Async Order for Async Loading. -1 = UNSET, 0 = None (Bulk), 1 = FirstToAst, 2 = Bulk"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDisplayLoading(
	TEXT("display.loading"),
	0,
	TEXT("Display Loading on HUD"),
	ECVF_SetByConsole
);

#pragma endregion Loading

// Input
#pragma region

TAutoConsoleVariable<int32> CsCVarLogInputs(
	TEXT("log.inputs"),
	0,
	TEXT("Log Inputs"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputAll(
	TEXT("log.input.all"),
	0,
	TEXT("Log Input All"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputActions(
	TEXT("log.input.actions"),
	0,
	TEXT("Log Input Actions"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputAxis(
	TEXT("log.input.axis"),
	0,
	TEXT("Log Input Axis"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputLocations(
	TEXT("log.input.locations"),
	0,
	TEXT("Log Input Locatons"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputRotations(
	TEXT("log.input.rotations"),
	0,
	TEXT("Log Input Rotations"),
	ECVF_SetByConsole
);

#pragma endregion Input

// OnBoard
#pragma region

TAutoConsoleVariable<int32> CsCVarLogPlayerStateOnBoard(
	TEXT("log.playerstate.onboard"),
	0,
	TEXT("Log PlayerState OnBoard"),
	ECVF_SetByConsole
);

#pragma endregion OnBoard

// Json
#pragma region

TAutoConsoleVariable<int32> CsCVarLogJsonDataFilenames(
	TEXT("log.json.datafilenames"),
	0,
	TEXT("Log Json Data Filenames on Save."),
	ECVF_SetByConsole
);

#pragma endregion Json

// Motion Controller
#pragma region

TAutoConsoleVariable<float> CsCVarMotionControllerTraceFrequencey(
	TEXT("motioncontroller.tracefrequency"),
	0.01667f,
	TEXT("Set frequency at which we trace from a motion controller out to the world."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawMotionControllerTrace(
	TEXT("draw.motioncontroller.trace"),
	0,
	TEXT("Draw the trace from the motion controller out to the world."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawMotionControllerMaxTouchSenseRange(
	TEXT("draw.motioncontroller.maxtouchsenserange"),
	0,
	TEXT("Draw the range, as a sphere, for max touch sense range for each motion controller."),
	ECVF_SetByConsole
);

#pragma endregion Motion Controller

// Pooled Actor
#pragma region

TAutoConsoleVariable<int32> CsCVarDrawPooledActorRootLocation(
	TEXT("draw.pooledactor.rootlocation"),
	0,
	TEXT("Draw the location of the root component of the Pooled Actor."),
	ECVF_SetByConsole
);

#pragma endregion Pooled Actor

// Interactive Actor
#pragma region

TAutoConsoleVariable<int32> CsCVarLogInteractiveActorPhysicsStateChange(
	TEXT("log.interactive.actor.physicsstatechange"),
	0,
	TEXT("Log Interactive Actor Physics State changes (Set and Clear)."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerInteractiveActorTransactions(
	TEXT("log.manager.interactive.actor.transactions"),
	0,
	TEXT("Log Manager Interactive Actor Allocation and DeAllocation."),
	ECVF_SetByConsole
);

#pragma endregion Interactive Actor

// Interactive AI Pawn
#pragma region

TAutoConsoleVariable<int32> CsCVarLogInteractiveAIPawnPhysicsStateChange(
	TEXT("log.interactive.aipawn.physicsstatechange"),
	0,
	TEXT("Log Interactive AI Pawn Physics State changes (Set and Clear)."),
	ECVF_SetByConsole
);

#pragma endregion Interactive AI Pawn

// Script
#pragma region

TAutoConsoleVariable<int32> CsCVarLogOverrideFunctions(
	TEXT("log.override.functions"),
	0,
	TEXT("Log Override Functions used by Script."),
	ECVF_SetByConsole
);

#pragma endregion Script

// Sound
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerSoundTransactions(
	TEXT("log.manager.sound.transactions"),
	0,
	TEXT("Log Manager Sound Allocation and DeAllocation."),
	ECVF_SetByConsole
);

#pragma endregion Sound

// FX
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerFxTransactions(
	TEXT("log.manager.fx.transactions"),
	0,
	TEXT("Log Manager FX Allocation and DeAllocation."),
	ECVF_SetByConsole
);

#pragma endregion FX

// Weapon
#pragma region

TAutoConsoleVariable<int32> CsCVarDrawWeaponFireProjectile(
	TEXT("draw.weapon.fireprojectile"),
	0,
	TEXT("Draw Projectile destinations from Weapon."),
	ECVF_SetByConsole
);

#pragma endregion Weapon

// Projectile
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerProjectileTransactions(
	TEXT("log.manager.projectile.transactions"),
	0,
	TEXT("Log Manager Projectile Allocation and DeAllocation."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawProjectileImpactNormal(
	TEXT("draw.projectile.impactnormal"),
	0,
	TEXT("Draw the Impact Normal for a Projectile hitting a surface."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<float> CsCVarDrawProjectileImpactNormalLength(
	TEXT("draw.projectile.impactnormallength"),
	CS_CVAR_DRAW_PROJECTILE_IMPACT_NORMAL_LENGTH,
	TEXT("Length of the Impact Normal to be drawn from the surface hit by a Projectile."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<float> CsCVarDrawProjectileImpactNormalThickness(
	TEXT("draw.projectile.impactnormalthickness"),
	CS_CVAR_DRAW_PROJECTILE_IMPACT_NORMAL_THICKNESS,
	TEXT("Thickness of the Impact Normal to be drawn from the surface hit by a Projectile."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<float> CsCVarDrawProjectileImpactNormalDuration(
	TEXT("draw.projectile.impactnormalduration"),
	CS_CVAR_DRAW_PROJECTILE_IMPACT_NORMAL_THICKNESS,
	TEXT("Duration of the Impact Normal to be drawn from the surface hit by a Projectile."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawProjectileCollision(
	TEXT("draw.projectile.collision"),
	0,
	TEXT("Draw the Collision for a Projectile."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawProjectilePath(
	TEXT("draw.projectile.path"),
	0,
	TEXT("Draw the Path for a Projectile."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<float> CsCVarDrawProjectilePathInterval(
	TEXT("draw.projectile.pathinterval"),
	CS_CVAR_DRAW_PROJECTILE_PATH_INTERVAL,
	TEXT("The interval at which segments are drawn for the Path of a Projectile."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawProjectilePathSegmentsPerInterval(
	TEXT("draw.projectile.pathsegmentsperinterval"),
	CS_CVAR_DRAW_PROJECTILE_PATH_SEGMENTS_PER_INTERVAL,
	TEXT("Number of segments used to draw the Path for a Projectile."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<float> CsCVarDrawProjectilePathThickness(
	TEXT("draw.projectile.paththickness"),
	CS_CVAR_DRAW_PROJECTILE_PATH_THICKNESS,
	TEXT("Thickness of the Path to be drawn for a Projectile."),
	ECVF_SetByConsole
);

#pragma endregion Projectile

// Player
#pragma region

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

TAutoConsoleVariable<int32> CsCVarDrawPlayerCalcCameraTraceHitLocation(
	TEXT("draw.player.calccamera.tracehitlocation"),
	0,
	TEXT("Draw the Location traced out from the Player's Camera Location."),
	ECVF_SetByConsole
);

#pragma endregion Player

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

// Coroutine
#pragma region

TAutoConsoleVariable<int32> CsCVarLogCoroutineTransactions(
	TEXT("log.coroutine.transactions"),
	0,
	TEXT("Log Coroutine Scheduler Allocation and DeAllocation."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogCoroutineRunning(
	TEXT("log.coroutine.running"),
	0,
	TEXT("Log Coroutines currently running."),
	ECVF_SetByConsole
);

#pragma endregion Coroutine

// UI
#pragma region

	// Widget
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerWidgetTransactions(
	TEXT("log.manager.widget.transactions"),
	0,
	TEXT("Log Manager Widget Allocation and DeAllocation."),
	ECVF_SetByConsole
);

#pragma endregion Widget

#pragma endregion UI

// Item
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerItemTransactions(
	TEXT("log.manager.item.transactions"),
	0,
	TEXT("Log Manager Item Allocate and DeAllocate."),
	ECVF_SetByConsole
);

#pragma endregion Item

// Inventory
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerInventoryTransactions(
	TEXT("log.manager.inventory.transactions"),
	0,
	TEXT("Log Manager Inventory Add, Remove, Consume and Drop."),
	ECVF_SetByConsole
);

#pragma endregion Inventory

// Crafting
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerCraftingTransactions(
	TEXT("log.manager.crafting.transactions"),
	0,
	TEXT("Log Manager Crafting Begin, Craft, and Finish."),
	ECVF_SetByConsole
);

#pragma endregion Crafting