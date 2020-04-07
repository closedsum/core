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

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerLoad;
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

// Coroutine
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogCoroutineTransactions;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogCoroutineRunning;

#pragma endregion Coroutine

// Inventory
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerInventoryTransactions;

#pragma endregion Inventory

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

// Sense
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawManagerSenseRadius;
extern CSCORE_API TAutoConsoleVariable<int32> CsCVarDrawManagerSenseAngle;

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogManagerSenseSeesActorByDot;

#pragma endregion Sense

// Managers
#pragma region

#pragma endregion Managers

// Level
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogLevelPayloadPopulate;

#pragma endregion Level

// Payload
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogPayloadPopulate;

#pragma endregion Payload

// Data
#pragma region

extern CSCORE_API TAutoConsoleVariable<int32> CsCVarLogDataEntryPopulate;

#pragma endregion Data

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

#define CS_DECLARE_ADD_TO_CVAR_MAP(EnumStruct) const Type __##EnumStruct
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
	// GameState
	extern CSCORE_API const Type LogGameStateOnBoard;
	// Json
	extern CSCORE_API const Type LogJsonDataFilenames;
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
	// Collision

		// Trace
	extern CSCORE_API const Type LogManagerTraceTransactions;
	// Runnable
	extern CSCORE_API const Type LogManagerRunnableTransactions;
	// Process
	extern CSCORE_API const Type LogManagerProcessTransactions;
	extern CSCORE_API const Type LogProcessIO;
	// Sense
	extern CSCORE_API const Type LogManagerSenseSeesActorByDot;
	// Managers

	// Level
	extern CSCORE_API const Type LogLevelPayloadPopulate;
	// Payload
	extern CSCORE_API const Type LogPayloadPopulate;
	// Data
	extern CSCORE_API const Type LogDataEntryPopulate;

	namespace Map
	{
		// Managers

			// Load
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerLoad);
			// Trace
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerTraceTransactions);
			// Task
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerTaskTransactions);
			// Runnable
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerRunnableTransactions);
			// Data
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerDataLoad);
			// Projectile
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerProjectileTransactions);

			// Collectible
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerCollectibleTransactions);
			// Level
		//extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogManagerLevelTransactions);

		// Level
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogLevelPayloadPopulate);
		// Payload
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogPayloadPopulate);
		// Data
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogDataEntryPopulate);
	}
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