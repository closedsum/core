// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Engine.h"
#include "Types/CsTypes_Primitive.h"
#include "CsCVars.generated.h"

#define CS_CVAR_SHOW_LOG 1
#define CS_CVAR_HIDE_LOG 0
#define CS_CVAR_DRAW 1
#define CS_CVAR_DISPLAY 1
#define CS_CVAR_SHOW 1
#define CS_CVAR_HIDE 0
#define CS_CVAR_VALID 1
#define CS_CVAR_ENABLED 1
#define CS_CVAR_DISABLED 0

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

struct ICsAutoConsoleVariable
{
	virtual void UpdateIsDirty() = 0;
	virtual void Clear() = 0;
	virtual bool HasChanged() = 0;
	virtual void Resolve() = 0;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FCsAutoConsoleVariable_int32_OnChange, const int32&);

template<typename ValueType>
struct TCsAutoConsoleVariable : public ICsAutoConsoleVariable
{
protected:
	TAutoConsoleVariable<ValueType>* CVar;
	ValueType(IConsoleVariable::*GetValue)() const;
	void(IConsoleVariable::*SetValue)(ValueType, EConsoleVariableFlags);
public:
	ValueType Value;
	ValueType Last_Value;
protected:
	bool bDirty;
public:
	TMulticastDelegate<void, const ValueType&> OnChange_Event;

public:
	TCsAutoConsoleVariable()
	{
		bDirty = false;
		OnChange_Event.Clear();
	}
	virtual ~TCsAutoConsoleVariable() {}

	void Init(TAutoConsoleVariable<ValueType>* InCVar)
	{
		CVar = InCVar;

		IConsoleVariable* Var = (*CVar).AsVariable();
		Value				  = ((*Var).*(GetValue))();
		Last_Value			  = Value;
	}

	FORCEINLINE ValueType Get()
	{
		IConsoleVariable* Var = (*CVar).AsVariable();
		return ((*Var).*(GetValue))();
	}

	void Set(const ValueType& InValue, const EConsoleVariableFlags& SetBy = ECVF_SetByCode)
	{
		IConsoleVariable* Var = (*CVar).AsVariable();
		((*Var).*(SetValue))(InValue, SetBy);

		Value = InValue;

		UpdateIsDirty();
	}

protected:

	FORCEINLINE void UpdateIsDirty()
	{
		bDirty	   = Value != Last_Value;
		Last_Value = Value;

		if (bDirty)
			OnChange_Event.Broadcast(Value);
	}

public:

	FORCEINLINE void Clear()
	{
		bDirty = false;
	}

	FORCEINLINE bool HasChanged() { return bDirty; }

	FORCEINLINE void Resolve()
	{
		UpdateIsDirty();
		Clear();
	}
};

struct TCsAutoConsoleVariable_int32 : public TCsAutoConsoleVariable<int32>
{
private:
	typedef TCsAutoConsoleVariable<int32> Super;

public:

	TCsAutoConsoleVariable_int32() : Super()
	{
		GetValue = &IConsoleVariable::GetInt;
		SetValue = &IConsoleVariable::Set;

		Value = 0;
		Last_Value = 0;
	}
	~TCsAutoConsoleVariable_int32() {}
};

struct CSCORE_API ICsCVarMap
{
	virtual void Resolve() = 0;
	virtual void Reset() = 0;
	virtual void ResetDirty() = 0;
};

#define CS_ADD_TO_CVAR_MAP(CVarMap, EnumStruct, CVar) const Type __##EnumStruct = CVarMap::Get().Add(EnumStruct, &CVar);

// CVarLog
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsCVarLog : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsCVarLog)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsCVarLog)

struct CSCORE_API EMCsCVarLog final : public TCsEnumStructMap<FECsCVarLog, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsCVarLog, FECsCVarLog, uint8)
};

namespace NCsCVarLog
{
	typedef FECsCVarLog Type;

	// Loading
	extern CSCORE_API const Type LogManagerLoading;
	// Input
	extern CSCORE_API const Type LogInputRaw;
	extern CSCORE_API const Type LogInputRawAction;
	extern CSCORE_API const Type LogInputRawAxis;

	extern CSCORE_API const Type LogInput;
	extern CSCORE_API const Type LogInputAction;
	extern CSCORE_API const Type LogInputAxis;
	extern CSCORE_API const Type LogInputTrigger;
	extern CSCORE_API const Type LogInputLocation;
	extern CSCORE_API const Type LogInputRotation;

	extern CSCORE_API const Type LogInputGameEvent;
	// OnBoard
	extern CSCORE_API const Type LogPlayerStateOnBoard;
	// GameState
	extern CSCORE_API const Type LogGameStateOnBoard;
	// Json
	extern CSCORE_API const Type LogJsonDataFilenames;
	// Interactive Actor
	extern CSCORE_API const Type LogInteractiveActorPhysicsStateChange;
	extern CSCORE_API const Type LogManagerInteractiveActorTransactions;
	// Widget Actor
	extern CSCORE_API const Type LogManagerWidgetActorTransactions;
	// AI
	extern CSCORE_API const Type LogManagerAITransactions;
	// Interactive AI Pawn
	extern CSCORE_API const Type LogInteractiveAIPawnPhysicsStateChange;
	// Behavior Tree
	extern CSCORE_API const Type LogAIBTTasks;
	// Script
	extern CSCORE_API const Type LogOverrideFunctions;
	// Sound
	extern CSCORE_API const Type LogManagerSoundTransactions;
	// FX
	extern CSCORE_API const Type LogManagerFxTransactions;
	// Projectile
	extern CSCORE_API const Type LogManagerProjectileTransactions;
	// Coroutine
	extern CSCORE_API const Type LogCoroutineTransactions;
	extern CSCORE_API const Type LogCoroutineRunning;
	// UI

		// Widget
	extern CSCORE_API const Type LogManagerWidgetTransactions;
	// Item
	extern CSCORE_API const Type LogManagerItemTransactions;
	extern CSCORE_API const Type LogManagerItemActionGetFail;
	// Inventory
	extern CSCORE_API const Type LogManagerInventoryTransactions;
	// Crafting
	extern CSCORE_API const Type LogManagerCraftingTransactions;
	// Collision

		// Trace
	extern CSCORE_API const Type LogManagerTraceTransactions;
	// Runnable
	extern CSCORE_API const Type LogManagerRunnableTransactions;
	// Process
	extern CSCORE_API const Type LogManagerProcessTransactions;
	extern CSCORE_API const Type LogProcessIO;
	// Blockchain
	extern CSCORE_API const Type LogBlockchainIO;
	extern CSCORE_API const Type LogBlockchainIORunning;
	extern CSCORE_API const Type LogBlockchainIOConsole;
		// Process
	extern CSCORE_API const Type LogBlockchainProcessStart;
		// Command
	extern CSCORE_API const Type LogBlockchainCommandCompleted;
		// Account
	extern CSCORE_API const Type LogBlockchainAccountCreated;
		// Ethereum
	extern CSCORE_API const Type LogBlockchainAccountLoad;
	extern CSCORE_API const Type LogBlockchainAccountSetup;
	extern CSCORE_API const Type LogBlockchainBalance;
	// Sense
	extern CSCORE_API const Type LogManagerSenseSeesActorByDot;
}

#pragma endregion CVarLog

// CVarLogMap
#pragma region

struct CSCORE_API FCsCVarLogMap : public ICsCVarMap
{
protected:
	FCsCVarLogMap() {}
	FCsCVarLogMap(const FCsCVarLogMap &) = delete;
	FCsCVarLogMap(FCsCVarLogMap &&) = delete;
public:
	virtual ~FCsCVarLogMap() {}
private:
	TMap<FECsCVarLog, TCsAutoConsoleVariable_int32> Map;
	TMap<FECsCVarLog, int32> DefaultValues;
	TMap<FECsCVarLog, bool> DirtyMap;

public:
	static FCsCVarLogMap& Get()
	{
		static FCsCVarLogMap Instance;
		return Instance;
	}

public:

	FORCEINLINE const FECsCVarLog& Add(const FECsCVarLog& Log, TAutoConsoleVariable<int32>* CVar)
	{
		Map.Add(Log);
		Map[Log].Init(CVar);
		DefaultValues.Add(Log, GetValue(Log));
		DirtyMap.Add(Log, false);
		return Log;
	}

	FORCEINLINE int32 GetValue(const FECsCVarLog& Log)
	{
		return Map[Log].Get();
	}

	FORCEINLINE bool IsShowing(const FECsCVarLog& Log)
	{
		return Map[Log].Get() == CS_CVAR_SHOW_LOG;
	}

	FORCEINLINE bool IsHiding(const FECsCVarLog& Log)
	{
		return Map[Log].Get() == CS_CVAR_HIDE_LOG;
	}

	FORCEINLINE void Show(const FECsCVarLog& Log, bool MarkDirty = false)
	{
		Map[Log].Set(CS_CVAR_SHOW_LOG, ECVF_SetByConsole);

		if (MarkDirty)
			DirtyMap[Log] = true;
	}

	FORCEINLINE void Hide(const FECsCVarLog& Log, bool MarkDirty = false)
	{
		Map[Log].Set(CS_CVAR_HIDE_LOG, ECVF_SetByConsole);

		if (MarkDirty)
			DirtyMap[Log] = true;
	}

	void Resolve();
	void Reset();
	void ResetDirty();
};

#pragma endregion CVarLogMap

// CVarToggle
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsCVarToggle : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsCVarToggle)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsCVarToggle)

struct CSCORE_API EMCsCVarToggle final : public TCsEnumStructMap<FECsCVarToggle, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsCVarToggle, FECsCVarToggle, uint8)
};

namespace NCsCVarToggle
{
	typedef FECsCVarToggle Type;

	namespace Ref
	{
	}

	namespace Map
	{
	}
}

#pragma endregion CVarToggle

// CVarToggleMap
#pragma region

struct CSCORE_API FCsCVarToggleMap : public ICsCVarMap
{
protected:
	FCsCVarToggleMap() {}
	FCsCVarToggleMap(const FCsCVarToggleMap &) = delete;
	FCsCVarToggleMap(FCsCVarToggleMap &&) = delete;
public:
	virtual ~FCsCVarToggleMap() {}
private:
	TMap<FECsCVarToggle, TCsAutoConsoleVariable_int32> Map;
	TMap<FECsCVarToggle, int32> DefaultValues;
	TMap<FECsCVarToggle, bool> DirtyMap;

public:
	static FCsCVarToggleMap& Get()
	{
		static FCsCVarToggleMap Instance;
		return Instance;
	}

public:

	FORCEINLINE const FECsCVarToggle& Add(const FECsCVarToggle& Toggle, TAutoConsoleVariable<int32>* CVar)
	{
		Map.Add(Toggle);
		Map[Toggle].Init(CVar);
		DefaultValues.Add(Toggle, GetValue(Toggle));
		DirtyMap.Add(Toggle, false);
		return Toggle;
	}

	FORCEINLINE bool GetValue(const FECsCVarToggle& Toggle)
	{
		return Map[Toggle].Get() != CS_CVAR_DISABLED;
	}

	FORCEINLINE bool IsEnabled(const FECsCVarToggle& Toggle)
	{
		return Map[Toggle].Get() == CS_CVAR_ENABLED;
	}

	FORCEINLINE bool IsDisabled(const FECsCVarToggle& Toggle)
	{
		return Map[Toggle].Get() == CS_CVAR_DISABLED;
	}

	FORCEINLINE void Enable(const FECsCVarToggle& Toggle, bool MarkDirty = false)
	{
		Map[Toggle].Set(CS_CVAR_ENABLED, ECVF_SetByConsole);

		if (MarkDirty)
			DirtyMap[Toggle] = true;
	}

	FORCEINLINE void Disable(const FECsCVarToggle& Toggle, bool MarkDirty = false)
	{
		Map[Toggle].Set(CS_CVAR_DISABLED, ECVF_SetByConsole);

		if (MarkDirty)
			DirtyMap[Toggle] = true;
	}

	void Resolve();
	void Reset();
	void ResetDirty();
};

#pragma endregion CVarToggleMap

// CVarDraw
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsCVarDraw : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsCVarDraw)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsCVarDraw)

struct CSCORE_API EMCsCVarDraw final : public TCsEnumStructMap<FECsCVarDraw, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsCVarDraw, FECsCVarDraw, uint8)
};

namespace NCsCVarDraw
{
	typedef FECsCVarDraw Type;

	namespace Ref
	{
		// Trace
		extern CSCORE_API const Type DrawManagerTraceRequests;
		extern CSCORE_API const Type DrawManagerTraceResponses;
	}

	namespace Map
	{
		// Trace
		extern CSCORE_API const Type DrawManagerTraceRequests;
		extern CSCORE_API const Type DrawManagerTraceResponses;
	}
}

#pragma endregion CVarDraw

// CVarDrawMap
#pragma region

struct CSCORE_API FCsCVarDrawMap : ICsCVarMap
{
protected:
	FCsCVarDrawMap() {}
	FCsCVarDrawMap(const FCsCVarDrawMap &) = delete;
	FCsCVarDrawMap(FCsCVarDrawMap &&) = delete;
public:
	virtual ~FCsCVarDrawMap() {}
private:
	TMap<FECsCVarDraw, TCsAutoConsoleVariable_int32> Map;
	TMap<FECsCVarDraw, int32> DefaultValues;
	TMap<FECsCVarDraw, bool> DirtyMap;

public:
	static FCsCVarDrawMap& Get()
	{
		static FCsCVarDrawMap Instance;
		return Instance;
	}

public:

	FORCEINLINE const FECsCVarDraw& Add(const FECsCVarDraw& Draw, TAutoConsoleVariable<int32>* CVar)
	{
		Map.Add(Draw);
		Map[Draw].Init(CVar);
		DefaultValues.Add(Draw, GetValue(Draw));
		DirtyMap.Add(Draw, false);
		return Draw;
	}

	FORCEINLINE int32 GetValue(const FECsCVarDraw& Draw)
	{
		return Map[Draw].Get();
	}

	FORCEINLINE bool IsDrawing(const FECsCVarDraw& Draw)
	{
		return Map[Draw].Get() == CS_CVAR_DRAW;
	}

	FORCEINLINE bool IsHiding(const FECsCVarDraw& Draw)
	{
		return Map[Draw].Get() == CS_CVAR_HIDE;
	}

	FORCEINLINE void Draw(const FECsCVarDraw& Draw, bool MarkDirty = false)
	{
		Map[Draw].Set(CS_CVAR_DRAW, ECVF_SetByConsole);

		if (MarkDirty)
			DirtyMap[Draw] = true;
	}

	FORCEINLINE void Hide(const FECsCVarDraw& Draw, bool MarkDirty = false)
	{
		Map[Draw].Set(CS_CVAR_HIDE, ECVF_SetByConsole);

		if (MarkDirty)
			DirtyMap[Draw] = true;
	}

	void Resolve();
	void Reset();
	void ResetDirty();
};

#pragma endregion CVarDrawMap