// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Engine.h"

#define CS_CVAR_SHOW_LOG 1
#define CS_CVAR_HIDE_LOG 0
#define CS_CVAR_DRAW 1
#define CS_CVAR_DISPLAY 1
#define CS_CVAR_SHOW 1
#define CS_CVAR_HIDE 0
#define CS_CVAR_VALID 1

// Loading
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerLoading;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarManagerLoadingAsyncOrder;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDisplayLoading;

#pragma endregion Loading

// Input
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputRaw;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputRawAction;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputRawAxis;

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInput;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputAction;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputAxis;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputTrigger;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputLocation;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputRotation;

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInputGameEvent;

#pragma endregion Input

// OnBoard
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogPlayerStateOnBoard;

#pragma endregion OnBoard

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

// Interactive Actor
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInteractiveActorPhysicsStateChange;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerInteractiveActorTransactions;

#pragma endregion Interactive Actor

// Widget Actor
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerWidgetActorTransactions;

#pragma endregion Widget Actor

// AI
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerAITransactions;

	// View
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawAIViewTraceHitLocation;

#pragma endregion View

	// Interactive AI Pawn
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogInteractiveAIPawnPhysicsStateChange;

#pragma endregion Interactive AI Pawn

	// Behavior Tree
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogAIBTTasks;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawAIBTMoveTo;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawAIBTRotateToFaceBBEntry;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawAIBTLookAtAndRotateToFace;

#pragma endregion Behavior Tree

#pragma endregion AI

// Script
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogOverrideFunctions;

#pragma endregion Script

// Sound
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSoundTransactions;

#pragma endregion Sound

// FX
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerFxTransactions;

#pragma endregion FX

// Weapon
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawWeaponFireProjectile;

#pragma endregion Weapon

// Projectile
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerProjectileTransactions;

#define CS_CVAR_DRAW_PROJECTILE_IMPACT_NORMAL_LENGTH 100.0f
#define CS_CVAR_DRAW_PROJECTILE_IMPACT_NORMAL_THICKNESS 2.0f
#define CS_CVAR_DRAW_PROJECTILE_IMPACT_NORMAL_DURATION 0.25f

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawProjectileImpactNormal;
extern CSCORE_API TAutoConsoleVariable<float> CsCVarDrawProjectileImpactNormalLength;
extern CSCORE_API TAutoConsoleVariable<float> CsCVarDrawProjectileImpactNormalThickness;
extern CSCORE_API TAutoConsoleVariable<float> CsCVarDrawProjectileImpactNormalDuration;

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawProjectileCollision;

#define CS_CVAR_DRAW_PROJECTILE_PATH_INTERVAL 0.5f
#define CS_CVAR_DRAW_PROJECTILE_PATH_SEGMENTS_PER_INTERVAL 16
#define CS_CVAR_DRAW_PROJECTILE_PATH_THICKNESS 1.0f

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawProjectilePath;
extern CSCORE_API TAutoConsoleVariable<float> CsCVarDrawProjectilePathInterval;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawProjectilePathSegmentsPerInterval;
extern CSCORE_API TAutoConsoleVariable<float> CsCVarDrawProjectilePathThickness;

#pragma endregion Projectile

// Player
#pragma region

	// View
#pragma region

#define CS_CVAR_DRAW_PLAYER_VIEW_FORWARD_LENGTH 100.0f
#define CS_CVAR_DRAW_PLAYER_VIEW_FORWARD_THICKNESS 2.0f
#define CS_CVAR_DRAW_PLAYER_VIEW_RIGHT_LENGTH 100.0f
#define CS_CVAR_DRAW_PLAYER_VIEW_RIGHT_THICKNESS 2.0f

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawPlayerViewForward;
extern CSCORE_API TAutoConsoleVariable<float> CsCVarDrawPlayerViewForwardLength;
extern CSCORE_API TAutoConsoleVariable<float> CsCVarDrawPlayerViewForwardThickness;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawPlayerViewRight;
extern CSCORE_API TAutoConsoleVariable<float> CsCVarDrawPlayerViewRightLength;
extern CSCORE_API TAutoConsoleVariable<float> CsCVarDrawPlayerViewRightThickness;

#pragma endregion View

	// Pawn
#pragma region

#define CS_CVAR_DRAW_PLAYER_PAWN_FORWARD_LENGTH 100.0f
#define CS_CVAR_DRAW_PLAYER_PAWN_FORWARD_THICKNESS 2.0f
#define CS_CVAR_DRAW_PLAYER_PAWN_RIGHT_LENGTH 100.0f
#define CS_CVAR_DRAW_PLAYER_PAWN_RIGHT_THICKNESS 2.0f

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawPlayerPawnForward;
extern CSCORE_API TAutoConsoleVariable<float> CsCVarDrawPlayerPawnForwardLength;
extern CSCORE_API TAutoConsoleVariable<float> CsCVarDrawPlayerPawnForwardThickness;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawPlayerPawnRight;
extern CSCORE_API TAutoConsoleVariable<float> CsCVarDrawPlayerPawnRightLength;
extern CSCORE_API TAutoConsoleVariable<float> CsCVarDrawPlayerPawnRightThickness;

#pragma endregion Pawn

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawPlayerViewTraceHitLocation;

	// Save
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarPlayerSaveRebuild;

#pragma endregion Save

#pragma endregion Player

// Local Player
#pragma region

	// Weapon
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawLocalPlayerWeaponFireProjectile;

#pragma endregion Weapon

	// Projectile
#pragma region

#define CS_CVAR_DRAW_LOCAL_PLAYER_PROJECTILE_PATH_INTERVAL 0.5f
#define CS_CVAR_DRAW_LOCAL_PLAYER_PROJECTILE_PATH_SEGMENTS_PER_INTERVAL 16
#define CS_CVAR_DRAW_LOCAL_PLAYER_PROJECTILE_PATH_THICKNESS 1.0f

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawLocalPlayerProjectilePath;
extern CSCORE_API TAutoConsoleVariable<float> CsCVarDrawLocalPlayerProjectilePathInterval;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawLocalPlayerProjectilePathSegmentsPerInterval;
extern CSCORE_API TAutoConsoleVariable<float> CsCVarDrawLocalPlayerProjectilePathThickness;

#pragma endregion Projectile

#pragma endregion Local Player

// Coroutine
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogCoroutineTransactions;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogCoroutineRunning;

#pragma endregion Coroutine

// UI
#pragma region

	// Widget
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerWidgetTransactions;

#pragma endregion Widget

#pragma endregion UI

// Item
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarManagerItemRebuild;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerItemTransactions;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerItemActionGetFail;

#pragma endregion Item

// Inventory
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerInventoryTransactions;

#pragma endregion Inventory

// Crafting
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerCraftingTransactions;

#pragma endregion Crafting

// Collision
#pragma region

	// Trace
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerTraceTransactions;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawManagerTraceRequests;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawManagerTraceResponses;

#pragma endregion Trace

#pragma endregion Collision

// Runnable
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerRunnableTransactions;

#pragma endregion Runnable

// Process
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerProcessTransactions;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogProcessIO;

#pragma endregion Process

// Blockchain
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarBlockchainRebuild;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogBlockchainIO;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogBlockchainIORunning;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogBlockchainIOConsole;
//Process
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarShowBlockchainProcessWindow;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogBlockchainProcessStart;
// Command
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogBlockchainCommandCompleted;
// Account
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogBlockchainAccountCreated;

	// Ethereum
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogBlockchainAccountLoad;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogBlockchainAccountSetup;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogBlockchainBalance;

#pragma endregion Ethereum

#pragma endregion Blockchain

// Sense
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawManagerSenseRadius;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawManagerSenseAngle;

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSenseSeesActorByDot;

#pragma endregion Sense

// CVarLog
#pragma region

UENUM(BlueprintType)
enum class ECsCVarLog : uint8
{
	// Loading
	LogManagerLoading								UMETA(DisplayName = "Log Manager Loading"),

	// Input
	LogInputRaw										UMETA(DisplayName = "Log Input Raw"),
	LogInputRawAction								UMETA(DisplayName = "Log Input Raw Action"),
	LogInputRawAxis									UMETA(DisplayName = "Log Input Raw Axis"),

	LogInput										UMETA(DisplayName = "Log Input"),
	LogInputAction									UMETA(DisplayName = "Log Input Action"),
	LogInputAxis									UMETA(DisplayName = "Log Input Axis"),
	LogInputTrigger									UMETA(DisplayName = "Log Input Trigger"),
	LogInputLocation								UMETA(DisplayName = "Log Input Location"),
	LogInputRotation								UMETA(DisplayName = "Log Input Rotation"),

	LogInputGameEvent								UMETA(DisplayName = "Log Input Game Event"),

	// OnBoard
	LogPlayerStateOnBoard							UMETA(DisplayName = "Log PlayerState OnBoard"),

	// GameState
	LogGameStateOnBoard								UMETA(DisplayName = "Log GameState OnBoard"),

	// Json
	LogJsonDataFilenames							UMETA(DisplayName = "Log Json Data Filenames"),

	// Interactive Actor
	LogInteractiveActorPhysicsStateChange			UMETA(DisplayName = "Log Interactive Actor Physics State Change"),
	LogManagerInteractiveActorTransactions			UMETA(DisplayName = "Log Manager Interactive Actor Transactions"),

	// Widget Actor
	LogManagerWidgetActorTransactions				UMETA(DisplayName = "Log Manager Widget Actor Transactions"),

	// AI
	LogManagerAITransactions						UMETA(DisplayName = "Log Manager AI Transactions"),

		// Interactive AI Pawn
	LogInteractiveAIPawnPhysicsStateChange			UMETA(DisplayName = "Log Interactive AI Pawn Physics State Change"),

		// Behavior Tree
	LogAIBTTasks									UMETA(DisplayName = "Log AI BT Tasks"),

	// Script
	LogOverrideFunctions							UMETA(DisplayName = "Log Override Functions"),

	// Sound
	LogManagerSoundTransactions						UMETA(DisplayName = "Log Manager Sound Transactions"),

	// FX
	LogManagerFxTransactions						UMETA(DisplayName = "Log Manager FX Transactions"),

	// Projectile
	LogManagerProjectileTransactions				UMETA(DisplayName = "Log Manager Projectile Transactions"),

	// Coroutine
	LogCoroutineTransactions						UMETA(DisplayName = "Log Coroutine Transactions"),
	LogCoroutineRunning								UMETA(DisplayName = "Log Coroutine Running"),

	// UI

		// Widget
	LogManagerWidgetTransactions					UMETA(DisplayName = "Log Manager Widget Transactions"),

	// Item
	LogManagerItemTransactions						UMETA(DisplayName = "Log Manager Item Transactions"),
	LogManagerItemActionGetFail						UMETA(DisplayName = "Log Manager Item Action Get Fail"),

	// Inventory
	LogManagerInventoryTransactions					UMETA(DisplayName = "Log Manager Inventory Transactions"),

	// Crafting
	LogManagerCraftingTransactions					UMETA(DisplayName = "Log Manager Crafting Transactions"),

	// Collision

		// Trace
	LogManagerTraceTransactions						UMETA(DisplayName = "Log Manager Trace Transactions"),

	// Runnable
	LogManagerRunnableTransactions					UMETA(DisplayName = "Log Manager Runnable Transactions"),

	// Process
	LogManagerProcessTransactions					UMETA(DisplayName = "Log Manager Process Transactions"),
	LogProcessIO									UMETA(DisplayName = "Log Process IO"),

	// Blockchain
	LogBlockchainIO									UMETA(DisplayName = "Log Blockchain IO"),
	LogBlockchainIORunning							UMETA(DisplayName = "Log Blockchain IO Running"),
	LogBlockchainIOConsole							UMETA(DisplayName = "Log Blockchain IO Console"),
		// Process
	LogBlockchainProcessStart						UMETA(DisplayName = "Log Blockchain Process Start"),
		// Command
	LogBlockchainCommandCompleted					UMETA(DisplayName = "Log Blockchain Command Completed"),
		// Account
	LogBlockchainAccountCreated						UMETA(DisplayName = "Log Blockchain Account Created"),

	// Ethereum
	LogBlockchainAccountLoad						UMETA(DisplayName = "Log Blockchain Account Load"),
	LogBlockchainAccountSetup						UMETA(DisplayName = "Log Blockchain Account Setup"),
	LogBlockchainBalance							UMETA(DisplayName = "Log Blockchain Balance"),

	// Sense
	LogManagerSenseSeesActorByDot					UMETA(DisplayName = "Log Manager Sense Sees Actor by Dot"),

	ECsCVarLog_MAX									UMETA(Hidden),
};

struct CSCORE_API EMCsCVarLog : public TCsEnumMap<ECsCVarLog>
{
	CS_DECLARE_ENUM_MAP_BODY(EMCsCVarLog)
};

namespace NCsCVarLog
{
	namespace Ref
	{
		typedef ECsCVarLog Type;

		//extern CSCORE_API const Type FirstPressed;
		//extern CSCORE_API const Type ECsInputEvent_MAX;
	}
}

#pragma endregion CVarLog

struct CSCORE_API FCsCVarLogMap
{
protected:
	FCsCVarLogMap() {}
	FCsCVarLogMap(const FCsCVarLogMap &) = delete;
	FCsCVarLogMap(FCsCVarLogMap &&) = delete;
public:
	~FCsCVarLogMap() {}
private:
	static FCsCVarLogMap* Instance;
		
	TMap<ECsCVarLog, TAutoConsoleVariable<int32>*> Map;
	TMap<ECsCVarLog, int32> DefaultValues;
	TMap<ECsCVarLog, bool> DirtyValues;

public:
	static FCsCVarLogMap& Get();

private:
	void Init();

public:

	void Reset();
	void ResetDirty();

	FORCEINLINE int32 GetValue(const ECsCVarLog& Log)
	{
		return 0;
	}

	FORCEINLINE void SetValue(const ECsCVarLog& Log, const int32& Value)
	{
		(*Map[Log])->Set(Value, ECVF_SetByConsole);
	}

	FORCEINLINE bool IsShowing(const ECsCVarLog& Log)
	{
		return (*Map[Log])->GetInt() == CS_CVAR_SHOW_LOG;
	}

	FORCEINLINE bool IsHiding(const ECsCVarLog& Log)
	{
		return (*Map[Log])->GetInt() == CS_CVAR_HIDE_LOG;
	}

	FORCEINLINE void Show(const ECsCVarLog& Log, const bool& MarkDirty = false)
	{
		(*Map[Log])->Set(CS_CVAR_SHOW_LOG, ECVF_SetByConsole);

		if (MarkDirty)
			DirtyValues[Log] = true;
	}

	FORCEINLINE void Hide(const ECsCVarLog& Log, const bool& MarkDirty = false)
	{
		(*Map[Log])->Set(CS_CVAR_HIDE_LOG, ECVF_SetByConsole);

		if (MarkDirty)
			DirtyValues[Log] = true;
	}
};