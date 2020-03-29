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

// AI
#pragma region

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

#pragma endregion Managers

// Level
#pragma region

TAutoConsoleVariable<int32> CsCVarLogLevelPayloadPopulate(
	TEXT("log.level.payload.populate"),
	1,
	TEXT("Log Level Payload Populate."),
	ECVF_SetByConsole
);

#pragma endregion Level

// Payload
#pragma region

TAutoConsoleVariable<int32> CsCVarLogPayloadPopulate(
	TEXT("log.payload.populate"),
	1,
	TEXT("Log Payload Populate."),
	ECVF_SetByConsole
);

#pragma endregion Payload

// Data
#pragma region

TAutoConsoleVariable<int32> CsCVarLogDataEntryPopulate(
	TEXT("log.data.entry.populate"),
	1,
	TEXT("Log Data Entry Populate."),
	ECVF_SetByConsole
);

#pragma endregion Data

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

	// GameState
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogGameStateOnBoard);
	// Json
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogJsonDataFilenames);
	// AI
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerAITransactions);
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
	// Collision

		// Trace
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerTraceTransactions);
	// Runnable
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerRunnableTransactions);
	// Process
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerProcessTransactions);
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogProcessIO);
	// Sense
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogManagerSenseSeesActorByDot);
	// Managers

	// Level
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogLevelPayloadPopulate);
	// Payload
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogPayloadPopulate);
	// Data
	CSCORE_API CS_CREATE_ENUM_STRUCT(EMCsCVarLog, LogDataEntryPopulate);

	namespace Map
	{
		// Managers

			// Load
		//CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerLoad, CsCVarLogManagerLoad);
			// Data
		//CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerDataLoad, CsCVarLogManagerDataLoad);
			// Projectile
		//CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerProjectileTransactions, CsCVarLogManagerProjectileTransactions);

			// Collectible
		//CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerCollectibleTransactions, CsCVarLogManagerCollectibleTransactions);
			// Level
		//CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogManagerLevelTransactions, CsCVarLogManagerLevelTransactions);

		// Level
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogLevelPayloadPopulate, CsCVarLogLevelPayloadPopulate);
		// Payload
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogPayloadPopulate, CsCVarLogPayloadPopulate);
		// Data
		CSCORE_API CS_ADD_TO_CVAR_MAP(FCsCVarLogMap, LogDataEntryPopulate, CsCVarLogDataEntryPopulate);
	}
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