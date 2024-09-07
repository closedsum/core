// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsCVars.h"

// GameState
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogGameStateOnBoard;

#pragma endregion GameState

// Json
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogJsonDataFilenames;

#pragma endregion Json

// Motion Controller
#pragma region

extern CSCORE_API TAutoConsoleVariable<float> CsCVarMotionControllerTraceFrequencey;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawMotionControllerTrace;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawMotionControllerMaxTouchSenseRange;

#pragma endregion Motion Controller

// Pooled Actor
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawPooledActorRootLocation;

#pragma endregion Pooled Actor

// AI
#pragma region

	// View
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawAIViewTraceHitLocation;

#pragma endregion View

	// Interactive AI Pawn
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInteractiveAIPawnPhysicsStateChange;

#pragma endregion Interactive AI Pawn

#pragma endregion AI


// Inventory
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerInventoryTransactions;

#pragma endregion Inventory

// Runnable
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerRunnableTransactions;

#pragma endregion Runnable

// Sense
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawManagerSenseRadius;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawManagerSenseAngle;

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSenseSeesActorByDot;

#pragma endregion Sense

// Level
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogLevelPayloadPopulate;

#pragma endregion Level

namespace NCsCVarLog
{
	// GameState
	extern CSCORE_API const Type LogGameStateOnBoard;
	// Json
	extern CSCORE_API const Type LogJsonDataFilenames;
	// Script
	extern CSCORE_API const Type LogOverrideFunctions;
	// FX
	extern CSCORE_API const Type LogManagerFxTransactions;
	// Runnable
	extern CSCORE_API const Type LogManagerRunnableTransactions;
	// Sense
	extern CSCORE_API const Type LogManagerSenseSeesActorByDot;
	// Managers

	// Level
	extern CSCORE_API const Type LogLevelPayloadPopulate;

	namespace Map
	{
		typedef FCsCVarLogMap CVarMapType;

		// Script
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogOverrideFunctions);
		// Managers

			// Task
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerTaskTransactions);
			// Runnable
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerRunnableTransactions);
			// Data
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerDataLoad);

			// Collectible
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerCollectibleTransactions);
			// Level
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerLevelTransactions);

		// Level
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogLevelPayloadPopulate);
	}
}