// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsCVars.h"
#include "CsCore.h"

// Loading
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerLoad(
	TEXT("log.manager.load"),
	0,
	TEXT("Log Manager Load"),
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

TAutoConsoleVariable<int32> CsCVarLogInputRaw(
	TEXT("log.input.raw"),
	0,
	TEXT("Log Input Raw"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputRawAction(
	TEXT("log.input.raw.action"),
	0,
	TEXT("Log Input Raw Action"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputRawAxis(
	TEXT("log.input.raw.axis"),
	0,
	TEXT("Log Input Raw Axis"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInput(
	TEXT("log.input"),
	0,
	TEXT("Log Input"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputAction(
	TEXT("log.input.action"),
	0,
	TEXT("Log Input Action"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputAxis(
	TEXT("log.input.axis"),
	0,
	TEXT("Log Input Axis"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputTrigger(
	TEXT("log.input.trigger"),
	0,
	TEXT("Log Input Trigger"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputLocation(
	TEXT("log.input.location"),
	0,
	TEXT("Log Input Locaton"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputRotation(
	TEXT("log.input.rotation"),
	0,
	TEXT("Log Input Rotation"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogInputGameEvent(
	TEXT("log.input.gameevent"),
	0,
	TEXT("Log Input Game Event"),
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

// GameState
#pragma region

TAutoConsoleVariable<int32> CsCVarLogGameStateOnBoard(
	TEXT("log.gamestate.onboard"),
	0,
	TEXT("Log GameState OnBoard"),
	ECVF_SetByConsole
);

#pragma endregion GameState

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

// Widget Actor
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorTransactions(
	TEXT("log.manager.widget.actor.transactions"),
	0,
	TEXT("Log Manager Widget Actor Allocation and DeAllocation."),
	ECVF_SetByConsole
);

#pragma endregion Widget Actor

// AI
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerAITransactions(
	TEXT("log.manager.ai.transactions"),
	0,
	TEXT("Log Manager A.I. Allocation and DeAllocation."),
	ECVF_SetByConsole
);

	// View
#pragma region

TAutoConsoleVariable<int32> CsCVarDrawAIViewTraceHitLocation(
	TEXT("draw.ai.view.tracehitlocation"),
	0,
	TEXT("Draw the Location traced out from the AI's View Location."),
	ECVF_SetByConsole
);

#pragma endregion View

	// Interactive AI Pawn
#pragma region

TAutoConsoleVariable<int32> CsCVarLogInteractiveAIPawnPhysicsStateChange(
	TEXT("log.interactive.aipawn.physicsstatechange"),
	0,
	TEXT("Log Interactive AI Pawn Physics State changes (Set and Clear)."),
	ECVF_SetByConsole
);

#pragma endregion Interactive AI Pawn

	// Behavior Tree
#pragma region

TAutoConsoleVariable<int32> CsCVarLogAIBTTasks(
	TEXT("log.ai.bt.tasks"),
	0,
	TEXT("Log A.I. Behavior Tree Tasks (Execute, Succeeded, and Abort)."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawAIBTMoveTo(
	TEXT("draw.ai.bt.moveto"),
	0,
	TEXT("Draw A.I. Behavior Tree MoveTo Task."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawAIBTRotateToFaceBBEntry(
	TEXT("draw.ai.bt.rotatetofacebbentry"),
	0,
	TEXT("Draw A.I. Behavior Tree RotateToFaceBBEntry Task."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawAIBTLookAtRotateToFace(
	TEXT("draw.ai.bt.lookatandrotatetoface"),
	0,
	TEXT("Draw A.I. Behavior Tree LookAtAndRotateToFace Task."),
	ECVF_SetByConsole
);

#pragma endregion Behavior Tree

#pragma endregion AI

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

TAutoConsoleVariable<int32> CsCVarDrawPlayerViewTraceHitLocation(
	TEXT("draw.player.view.tracehitlocation"),
	0,
	TEXT("Draw the Location traced out from the Player's Camera Location."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarPlayerSaveRebuild(
	TEXT("player.save.rebuild"),
	0,
	TEXT("Player Save Rebuild."),
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

TAutoConsoleVariable<int32> CsCVarManagerItemRebuild(
	TEXT("manager.item.rebuild"),
	0,
	TEXT("Manager Item Rebuild."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerItemTransactions(
	TEXT("log.manager.item.transactions"),
	0,
	TEXT("Log Manager Item Allocate and DeAllocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogManagerItemActionGetFail(
	TEXT("log.manager.item.action.get.fail"),
	0,
	TEXT("Log Manager Item GetItem(s) failed retrieval of item."),
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

// Collision
#pragma region

	// Trace
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerTraceTransactions(
	TEXT("log.manager.trace.transactions"),
	0,
	TEXT("Log Manager Trace Add and Complete."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawManagerTraceRequests(
	TEXT("draw.manager.trace.requests"),
	0,
	TEXT("Draw Manager Trace Requests. A Line from Start to End of the Trace Request"),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarDrawManagerTraceResponses(
	TEXT("draw.manager.trace.responses"),
	0,
	TEXT("Draw Manager Trace Responses. A Line from Start to End of the Trace Result / Response."),
	ECVF_SetByConsole
);


#pragma endregion Trace

#pragma endregion Collision

// Runnable
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerRunnableTransactions(
	TEXT("log.manager.runnable.transactions"),
	0,
	TEXT("Log Manager Runnable Add and Complete."),
	ECVF_SetByConsole
);

#pragma endregion Runnable

// Process
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerProcessTransactions(
	TEXT("log.manager.process.transactions"),
	0,
	TEXT("Log Manager Process Allocate and DeAllocate."),
	ECVF_SetByConsole
);

TAutoConsoleVariable<int32> CsCVarLogProcessIO(
	TEXT("log.process.io"),
	0,
	TEXT("Log Process Input / Ouput from Write / Read Pipes."),
	ECVF_SetByConsole
);

#pragma endregion Process

// Blockchain
#pragma region

TAutoConsoleVariable<int32> CsCVarBlockchainRebuild(
	TEXT("blockchain.rebuild"),
	0,
	TEXT("Rebuild Blockchain."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarLogBlockchainIO(
	TEXT("log.blockchain.io"),
	0,
	TEXT("Log All Blockchain Input / Output Messages."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarLogBlockchainIORunning(
	TEXT("log.blockchain.io.running"),
	0,
	TEXT("Log Running Blockchain Input / Output Messages."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarLogBlockchainIOConsole(
	TEXT("log.blockchain.io.console"),
	0,
	TEXT("Log Console Blockchain Input / Output Messages."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarShowBlockchainProcessWindow(
	TEXT("show.blockchain.processwindow"),
	0,
	TEXT("Show Blockchain Process Window."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarLogBlockchainProcessStart(
	TEXT("log.blockchain.process.start"),
	0,
	TEXT("Log Blockchain Process Starting."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarLogBlockchainCommandCompleted(
	TEXT("log.blockchain.command.completed"),
	0,
	TEXT("Log Blockchain Command Completed."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarLogBlockchainAccountCreated(
	TEXT("log.blockchain.account.created"),
	0,
	TEXT("Log Blockchain Account Created."),
	ECVF_SetByConsole | ECVF_SetByCode
);

	// Ethereum
#pragma region

TAutoConsoleVariable<int32> CsCVarLogBlockchainAccountLoad(
	TEXT("log.blockchain.account.load"),
	0,
	TEXT("Log Blockchain (Ethereum) when Accounts get loaded."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarLogBlockchainAccountSetup(
	TEXT("log.blockchain.account.setup"),
	0,
	TEXT("Log Blockchain (Ethereum) Account Setup."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarLogBlockchainBalance(
	TEXT("log.blockchain.balance"),
	0,
	TEXT("Log Blockchain (Ethereum) Balance."),
	ECVF_SetByConsole | ECVF_SetByCode
);

#pragma endregion Ethereum

#pragma endregion Blockchain

// Sense
#pragma region

TAutoConsoleVariable<int32> CsCVarDrawManagerSenseRadius(
	TEXT("draw.manager.sense.radius"),
	0,
	TEXT("Draw Manager Sense Radius."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarDrawManagerSenseAngle(
	TEXT("draw.manager.sense.angle"),
	0,
	TEXT("Draw Manager Sense Angle."),
	ECVF_SetByConsole | ECVF_SetByCode
);

TAutoConsoleVariable<int32> CsCVarLogManagerSenseSeesActorByDot(
	TEXT("log.manager.sense.sees.actor.bydot"),
	0,
	TEXT("Log Manager Sense bSeesActorByDot."),
	ECVF_SetByConsole | ECVF_SetByCode
);

#pragma endregion Sense

// Managers
#pragma region

	// Save
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerSaveTransactions(
	TEXT("log.manager.save.transactions"),
	0,
	TEXT("Log Manager Save Transactions."),
	ECVF_SetByConsole | ECVF_SetByCode
);

#pragma endregion Save

	// Achievement
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerAchievementTransactions(
	TEXT("log.manager.achievement.transactions"),
	0,
	TEXT("Log Manager Achievement Transactions."),
	ECVF_SetByConsole | ECVF_SetByCode
);

#pragma endregion Achievement

#pragma endregion Managers

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// Loading
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerLoading);
	// Input
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInputRaw);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInputRawAction);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInputRawAxis);

	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInput);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInputAction);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInputAxis);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInputTrigger);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInputLocation);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInputRotation);

	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInputGameEvent);
	// OnBoard
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogPlayerStateOnBoard);
	// GameState
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogGameStateOnBoard);
	// Json
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogJsonDataFilenames);
	// Interactive Actor
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInteractiveActorPhysicsStateChange);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerInteractiveActorTransactions);
	// Widget Actor
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerWidgetActorTransactions);
	// AI
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerAITransactions);
	// Interactive AI Pawn
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogInteractiveAIPawnPhysicsStateChange);
	// Behavior Tree
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogAIBTTasks);
	// Script
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogOverrideFunctions);
	// Sound
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerSoundTransactions);
	// FX
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerFxTransactions);
	// Projectile
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerProjectileTransactions);
	// Coroutine
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogCoroutineTransactions);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogCoroutineRunning);
	// UI

		// Widget
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerWidgetTransactions);
	// Item
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerItemTransactions);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerItemActionGetFail);
	// Inventory
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerInventoryTransactions);
	// Crafting
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerCraftingTransactions);
	// Collision

		// Trace
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerTraceTransactions);
	// Runnable
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerRunnableTransactions);
	// Process
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerProcessTransactions);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogProcessIO);
	// Blockchain
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogBlockchainIO);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogBlockchainIORunning);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogBlockchainIOConsole);
		// Process
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogBlockchainProcessStart);
		// Command
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogBlockchainCommandCompleted);
		// Account
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogBlockchainAccountCreated);
		// Ethereum
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogBlockchainAccountLoad);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogBlockchainAccountSetup);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogBlockchainBalance);
	// Sense
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerSenseSeesActorByDot);
	// Managers

		// Save
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerSaveTransactions);
		// Achievement
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerAchievementTransactions);
}

#pragma endregion CVarLog

// CVarLogMap
#pragma region

void FCsCVarLogMap::Resolve()
{
	for (TPair<FECsCVarLog, TCsAutoConsoleVariable_int32>& Pair : Map)
	{
		const FECsCVarLog& Key = Pair.Key;

		Map[Key].Resolve();
	}
}

void FCsCVarLogMap::Reset()
{
	for (TPair<FECsCVarLog, TCsAutoConsoleVariable_int32>& Pair : Map)
	{
		const FECsCVarLog& Key = Pair.Key;

		Map[Key].Set(DefaultValues[Key], ECVF_SetByConsole);
		DirtyMap[Key] = false;
	}
}

void FCsCVarLogMap::ResetDirty()
{
	for (TPair<FECsCVarLog, TCsAutoConsoleVariable_int32>& Pair : Map)
	{
		const FECsCVarLog& Key = Pair.Key;

		if (DirtyMap[Key])
			Map[Key].Set(DefaultValues[Key], ECVF_SetByConsole);
		DirtyMap[Key] = false;
	}
}

#pragma endregion CVarLogMap

// CVarToggleMap
#pragma region

void FCsCVarToggleMap::Resolve()
{
	for (TPair<FECsCVarToggle, TCsAutoConsoleVariable_int32>& Pair : Map)
	{
		const FECsCVarToggle& Key = Pair.Key;

		Map[Key].Resolve();
	}
}

void FCsCVarToggleMap::Reset()
{
	for (TPair<FECsCVarToggle, TCsAutoConsoleVariable_int32>& Pair : Map)
	{
		const FECsCVarToggle& Key = Pair.Key;

		Map[Key].Set(DefaultValues[Key], ECVF_SetByConsole);
		DirtyMap[Key] = false;
	}
}

void FCsCVarToggleMap::ResetDirty()
{
	for (TPair<FECsCVarToggle, TCsAutoConsoleVariable_int32>& Pair : Map)
	{
		const FECsCVarToggle& Key = Pair.Key;

		if (DirtyMap[Key])
			Map[Key].Set(DefaultValues[Key], ECVF_SetByConsole);
		DirtyMap[Key] = false;
	}
}

#pragma endregion CVarToggleMap

// CVarDrawsMap
#pragma region

void FCsCVarDrawMap::Resolve()
{
	for (TPair<FECsCVarDraw, TCsAutoConsoleVariable_int32>& Pair : Map)
	{
		const FECsCVarDraw& Key = Pair.Key;

		Map[Key].Resolve();
	}
}

void FCsCVarDrawMap::Reset()
{
	for (TPair<FECsCVarDraw, TCsAutoConsoleVariable_int32>& Pair : Map)
	{
		const FECsCVarDraw& Key = Pair.Key;

		Map[Key].Set(DefaultValues[Key], ECVF_SetByConsole);
		DirtyMap[Key] = false;
	}
}

void FCsCVarDrawMap::ResetDirty()
{
	for (TPair<FECsCVarDraw, TCsAutoConsoleVariable_int32>& Pair : Map)
	{
		const FECsCVarDraw& Key = Pair.Key;

		if (DirtyMap[Key])
			Map[Key].Set(DefaultValues[Key], ECVF_SetByConsole);
		DirtyMap[Key] = false;
	}
}

#pragma endregion CVarDrawsMap