// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Engine.h"

// Loading
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerLoading;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarManagerLoadingAsyncOrder;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDisplayLoading;

#pragma endregion Loading

// Input
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputs;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputAll;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputActions;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputAxis;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputTrigger;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputLocations;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputRotations;

#pragma endregion Input

// OnBoard
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogPlayerStateOnBoard;

#pragma endregion OnBoard

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

// Interactive Actor
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInteractiveActorPhysicsStateChange;

#pragma endregion Interactive Actor

// Interactive AI Pawn
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInteractiveAIPawnPhysicsStateChange;

#pragma endregion Interactive AI Pawn

// Script
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogOverrideFunctions;

#pragma endregion
