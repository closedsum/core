// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsCVars_Core.h"

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

// Inventory
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerInventoryTransactions(
	TEXT("log.manager.inventory.transactions"),
	0,
	TEXT("Log Manager Inventory Add, Remove, Consume and Drop."),
	ECVF_SetByConsole
);

#pragma endregion Inventory

// Runnable
#pragma region

TAutoConsoleVariable<int32> CsCVarLogManagerRunnableTransactions(
	TEXT("log.manager.runnable.transactions"),
	0,
	TEXT("Log Manager Runnable Add and Complete."),
	ECVF_SetByConsole
);

#pragma endregion Runnable

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

// CVarLog
#pragma region

namespace NCsCVarLog
{
	// GameState
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogGameStateOnBoard);
	// Json
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogJsonDataFilenames);
	// FX
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogManagerFxTransactions);
	// Runnable
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogManagerRunnableTransactions);
	// Sense
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogManagerSenseSeesActorByDot);
	// Managers

	// Level
	CSCORE_API CS_CREATE_ENUM_STRUCT(LogLevelPayloadPopulate);

	namespace Map
	{
		// Managers

			// Data
		//CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerDataLoad, CsCVarLogManagerDataLoad);

			// Collectible
		//CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerCollectibleTransactions, CsCVarLogManagerCollectibleTransactions);
			// Level
		//CSCORE_API CS_ADD_TO_CVAR_MAP(LogManagerLevelTransactions, CsCVarLogManagerLevelTransactions);

		// Level
		CSCORE_API CS_ADD_TO_CVAR_MAP(LogLevelPayloadPopulate, CsCVarLogLevelPayloadPopulate);
	}
}

#pragma endregion CVarLog