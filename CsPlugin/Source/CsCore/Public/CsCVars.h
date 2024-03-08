// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine.h"
#include "Types/Enum/CsEnum_uint32.h"
#include "Types/Enum/CsEnumStructMap.h"
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
	TMulticastDelegate<void(const ValueType&)> OnChange_Event;

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

struct TCsAutoConsoleVariable_bool : public TCsAutoConsoleVariable<bool>
{
private:
	typedef TCsAutoConsoleVariable<bool> Super;

public:

	TCsAutoConsoleVariable_bool() : Super()
	{
		GetValue = &IConsoleVariable::GetBool;
		SetValue = &IConsoleVariable::Set;

		Value = false;
		Last_Value = false;
	}
	~TCsAutoConsoleVariable_bool() {}
};

struct CSCORE_API ICsCVarMap
{
	virtual void Resolve() = 0;
	virtual void Reset() = 0;
	virtual void ResetDirty() = 0;
};

#define CS_DECLARE_ADD_TO_CVAR_MAP(EnumStruct) const Type __##EnumStruct
// Assume typedef "EnumType" Type and typedef "CVarMapType" CVarMapType
#define CS_ADD_TO_CVAR_MAP(EnumStruct, CVar) const Type __##EnumStruct = CVarMapType::Get().Add(EnumStruct, &CVar);

// CVarLog
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsCVarLog : public FECsEnum_uint32
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT32_BODY(FECsCVarLog)
};

CS_DEFINE_ENUM_UINT32_GET_TYPE_HASH(FECsCVarLog)

struct CSCORE_API EMCsCVarLog final : public TCsEnumStructMap<FECsCVarLog, uint32>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsCVarLog, FECsCVarLog, uint32)
};

	// FCsCVarLogMap
#pragma region

struct CSCORE_API FCsCVarLogMap : public ICsCVarMap
{
protected:
	FCsCVarLogMap() :
		Map(),
		DefaultValues(),
		DirtyMap(),
		Num(0)
	{
	}
	FCsCVarLogMap(const FCsCVarLogMap &) = delete;
	FCsCVarLogMap(FCsCVarLogMap &&) = delete;
public:
	virtual ~FCsCVarLogMap() {}
private:
	TArray<TCsAutoConsoleVariable_int32> Map;
	TArray<int32> DefaultValues;
	TArray<bool> DirtyMap;
	int32 Num;
public:
	static FCsCVarLogMap& Get()
	{
		static FCsCVarLogMap Instance;
		return Instance;
	}

public:

	FORCEINLINE const FECsCVarLog& Add(const FECsCVarLog& Log, TAutoConsoleVariable<int32>* CVar)
	{
		const int32 Index = Log.GetValue();

		for (int32 I = Num - 1; I < Index; ++I)
		{
			Map.AddDefaulted();
			DefaultValues.AddDefaulted();
			DirtyMap.AddDefaulted();
			++Num;
		}

		Map[Index].Init(CVar);
		DefaultValues[Index] = GetValue(Log);
		DirtyMap[Index] = false;
		return Log;
	}

	FORCEINLINE int32 GetValue(const FECsCVarLog& Log)
	{
		return Map[Log.GetValue()].Get();
	}

	FORCEINLINE bool IsShowing(const FECsCVarLog& Log)
	{
		return Map[Log.GetValue()].Get() == CS_CVAR_SHOW_LOG;
	}

	FORCEINLINE bool IsHiding(const FECsCVarLog& Log)
	{
		return Map[Log.GetValue()].Get() == CS_CVAR_HIDE_LOG;
	}

	FORCEINLINE void Show(const FECsCVarLog& Log, bool MarkDirty = false)
	{
		Map[Log.GetValue()].Set(CS_CVAR_SHOW_LOG, ECVF_SetByConsole);

		if (MarkDirty)
			DirtyMap[Log.GetValue()] = true;
	}

	FORCEINLINE void Hide(const FECsCVarLog& Log, bool MarkDirty = false)
	{
		Map[Log.GetValue()].Set(CS_CVAR_HIDE_LOG, ECVF_SetByConsole);

		if (MarkDirty)
			DirtyMap[Log.GetValue()] = true;
	}

	void Resolve();
	void Reset();
	void ResetDirty();
};

#pragma endregion FCsCVarLogMap

namespace NCsCVarLog
{
	typedef FECsCVarLog Type;
	typedef EMCsCVarLog EnumMapType;

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
	// Payload
	extern CSCORE_API const Type LogPayloadPopulate;
	// Data
	extern CSCORE_API const Type LogDataEntryPopulate;

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
		// Payload
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogPayloadPopulate);
		// Data
		extern CSCORE_API CS_DECLARE_ADD_TO_CVAR_MAP(LogDataEntryPopulate);
	}
}

#define CS_CVAR_LOG_IS_SHOWING(__Log) FCsCVarLogMap::Get().IsShowing(NCsCVarLog::__Log)

#pragma endregion CVarLog

// CVarToggle
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsCVarToggle : public FECsEnum_uint32
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT32_BODY(FECsCVarToggle)
};

CS_DEFINE_ENUM_UINT32_GET_TYPE_HASH(FECsCVarToggle)

struct CSCORE_API EMCsCVarToggle final : public TCsEnumStructMap<FECsCVarToggle, uint32>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsCVarToggle, FECsCVarToggle, uint32)
};

	// FCsCVarToggleMap
#pragma region

struct CSCORE_API FCsCVarToggleMap : public ICsCVarMap
{
protected:
	FCsCVarToggleMap() :
		Map(),
		DefaultValues(),
		DirtyMap(),
		Num(0)
	{
	}
	FCsCVarToggleMap(const FCsCVarToggleMap &) = delete;
	FCsCVarToggleMap(FCsCVarToggleMap &&) = delete;
public:
	virtual ~FCsCVarToggleMap() {}
private:
	TArray<TCsAutoConsoleVariable_bool> Map;
	TArray<bool> DefaultValues;
	TArray<bool> DirtyMap;
	int32 Num;
public:
	static FCsCVarToggleMap& Get()
	{
		static FCsCVarToggleMap Instance;
		return Instance;
	}

public:

	FORCEINLINE const FECsCVarToggle& Add(const FECsCVarToggle& Toggle, TAutoConsoleVariable<bool>* CVar)
	{
		const int32 Index = Toggle.GetValue();

		for (int32 I = Num - 1; I < Index; ++I)
		{
			Map.AddDefaulted();
			DefaultValues.AddDefaulted();
			DirtyMap.AddDefaulted();
			++Num;
		}

		Map[Index].Init(CVar);
		DefaultValues[Index] = GetValue(Toggle);
		DirtyMap[Index] = false;
		return Toggle;
	}

	FORCEINLINE bool GetValue(const FECsCVarToggle& Toggle)
	{
		return Map[Toggle.GetValue()].Get() != CS_CVAR_DISABLED;
	}

	FORCEINLINE bool IsEnabled(const FECsCVarToggle& Toggle)
	{
		return Map[Toggle.GetValue()].Get() == CS_CVAR_ENABLED;
	}

	FORCEINLINE bool IsDisabled(const FECsCVarToggle& Toggle)
	{
		return Map[Toggle.GetValue()].Get() == CS_CVAR_DISABLED;
	}

	FORCEINLINE void Enable(const FECsCVarToggle& Toggle, bool MarkDirty = false)
	{
		Map[Toggle.GetValue()].Set(CS_CVAR_ENABLED, ECVF_SetByConsole);

		if (MarkDirty)
			DirtyMap[Toggle.GetValue()] = true;
	}

	FORCEINLINE void Disable(const FECsCVarToggle& Toggle, bool MarkDirty = false)
	{
		Map[Toggle.GetValue()].Set(CS_CVAR_DISABLED, ECVF_SetByConsole);

		if (MarkDirty)
			DirtyMap[Toggle.GetValue()] = true;
	}

	void Resolve();
	void Reset();
	void ResetDirty();
};

#pragma endregion FCsCVarToggleMap

namespace NCsCVarToggle
{
	typedef FECsCVarToggle Type;
	typedef EMCsCVarToggle EnumMapType;

	namespace Ref
	{
	}

	namespace Map
	{
		typedef FCsCVarToggleMap CVarMapType;
	}
}

#define CS_CVAR_TOGGLE_IS_ENABLED(__Toggle) FCsCVarToggleMap::Get().IsEnabled(NCsCVarToggle::__Toggle)
#define CS_CVAR_TOGGLE_IS_DISABLED(__Toggle) FCsCVarToggleMap::Get().IsDisabled(NCsCVarToggle::__Toggle)

#pragma endregion CVarToggle

// CVarDraw
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsCVarDraw : public FECsEnum_uint32
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT32_BODY(FECsCVarDraw)
};

CS_DEFINE_ENUM_UINT32_GET_TYPE_HASH(FECsCVarDraw)

struct CSCORE_API EMCsCVarDraw final : public TCsEnumStructMap<FECsCVarDraw, uint32>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsCVarDraw, FECsCVarDraw, uint32)
};

	// FCsCVarDrawMap
#pragma region

struct CSCORE_API FCsCVarDrawMap : ICsCVarMap
{
protected:
	FCsCVarDrawMap() :
		Map(),
		DefaultValues(),
		DirtyMap(),
		Num(0)
	{
	}
	FCsCVarDrawMap(const FCsCVarDrawMap &) = delete;
	FCsCVarDrawMap(FCsCVarDrawMap &&) = delete;
public:
	virtual ~FCsCVarDrawMap() {}
private:
	TArray<TCsAutoConsoleVariable_int32> Map;
	TArray<int32> DefaultValues;
	TArray<bool> DirtyMap;
	int32 Num;
public:
	static FCsCVarDrawMap& Get()
	{
		static FCsCVarDrawMap Instance;
		return Instance;
	}

public:

	FORCEINLINE const FECsCVarDraw& Add(const FECsCVarDraw& Draw, TAutoConsoleVariable<int32>* CVar)
	{
		const int32 Index = Draw.GetValue();

		for (int32 I = Num - 1; I < Index; ++I)
		{
			Map.AddDefaulted();
			DefaultValues.AddDefaulted();
			DirtyMap.AddDefaulted();
			++Num;
		}

		Map[Index].Init(CVar);
		DefaultValues[Index] = GetValue(Draw);
		DirtyMap[Index] = false;
		return Draw;
	}

	FORCEINLINE int32 GetValue(const FECsCVarDraw& Draw)
	{
		return Map[Draw.GetValue()].Get();
	}

	FORCEINLINE bool IsDrawing(const FECsCVarDraw& Draw)
	{
		return Map[Draw.GetValue()].Get() == CS_CVAR_DRAW;
	}

	FORCEINLINE bool IsHiding(const FECsCVarDraw& Draw)
	{
		return Map[Draw.GetValue()].Get() == CS_CVAR_HIDE;
	}

	FORCEINLINE void Draw(const FECsCVarDraw& Draw, bool MarkDirty = false)
	{
		Map[Draw.GetValue()].Set(CS_CVAR_DRAW, ECVF_SetByConsole);

		if (MarkDirty)
			DirtyMap[Draw.GetValue()] = true;
	}

	FORCEINLINE void Hide(const FECsCVarDraw& Draw, bool MarkDirty = false)
	{
		Map[Draw.GetValue()].Set(CS_CVAR_HIDE, ECVF_SetByConsole);

		if (MarkDirty)
			DirtyMap[Draw.GetValue()] = true;
	}

	void Resolve();
	void Reset();
	void ResetDirty();
};

#pragma endregion FCsCVarDrawMap

namespace NCsCVarDraw
{
	typedef FECsCVarDraw Type;
	typedef EMCsCVarDraw EnumMapType;

	namespace Map
	{
		typedef FCsCVarDrawMap CVarMapType;
	}
}

#define CS_CVAR_DRAW_IS_DRAWING(__Draw) FCsCVarDrawMap::Get().IsDrawing(NCsCVarDraw::__Draw)

#pragma endregion CVarDraw

// ScopedGroup
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsScopedGroup : public FECsEnum_uint32
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT32_BODY(FECsScopedGroup)
};

CS_DEFINE_ENUM_UINT32_GET_TYPE_HASH(FECsScopedGroup)

struct CSCORE_API EMCsScopedGroup final : public TCsEnumStructMap<FECsScopedGroup, uint32>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsScopedGroup, FECsScopedGroup, uint32)
};

	// FCsScopedGroupMap
#pragma region

struct CSCORE_API FCsScopedGroupMap : public ICsCVarMap
{
protected:
	FCsScopedGroupMap() :
		Map(),
		DefaultValues(),
		DirtyMap(),
		Num(0)
	{
	}
	FCsScopedGroupMap(const FCsScopedGroupMap &) = delete;
	FCsScopedGroupMap(FCsScopedGroupMap &&) = delete;
public:
	virtual ~FCsScopedGroupMap() {}
private:
	TArray<TCsAutoConsoleVariable_int32> Map;
	TArray<int32> DefaultValues;
	TArray<bool> DirtyMap;
	int32 Num;
public:
	static FCsScopedGroupMap& Get()
	{
		static FCsScopedGroupMap Instance;
		return Instance;
	}

public:

	FORCEINLINE const FECsScopedGroup& Add(const FECsScopedGroup& Log, TAutoConsoleVariable<int32>* CVar)
	{
		const int32 Index = Log.GetValue();

		for (int32 I = Num - 1; I < Index; ++I)
		{
			Map.AddDefaulted();
			DefaultValues.AddDefaulted();
			DirtyMap.AddDefaulted();
			++Num;
		}

		Map[Index].Init(CVar);
		DefaultValues[Index] = GetValue(Log);
		DirtyMap[Index] = false;
		return Log;
	}

	FORCEINLINE int32 GetValue(const FECsScopedGroup& Log)
	{
		return Map[Log.GetValue()].Get();
	}

	FORCEINLINE bool IsShowing(const FECsScopedGroup& Log)
	{
		return Map[Log.GetValue()].Get() == CS_CVAR_SHOW_LOG;
	}

	FORCEINLINE bool IsHiding(const FECsScopedGroup& Log)
	{
		return Map[Log.GetValue()].Get() == CS_CVAR_HIDE_LOG;
	}

	FORCEINLINE void Show(const FECsScopedGroup& Log, bool MarkDirty = false)
	{
		Map[Log.GetValue()].Set(CS_CVAR_SHOW_LOG, ECVF_SetByConsole);

		if (MarkDirty)
			DirtyMap[Log.GetValue()] = true;
	}

	FORCEINLINE void Hide(const FECsScopedGroup& Log, bool MarkDirty = false)
	{
		Map[Log.GetValue()].Set(CS_CVAR_HIDE_LOG, ECVF_SetByConsole);

		if (MarkDirty)
			DirtyMap[Log.GetValue()] = true;
	}

	void Resolve();
	void Reset();
	void ResetDirty();
};

#pragma endregion FCsScopedGroupMap

namespace NCsScopedGroup
{
	typedef FECsScopedGroup Type;
	typedef EMCsScopedGroup EnumMapType;

	namespace Map
	{
		typedef FCsScopedGroupMap CVarMapType;
	}
}

#pragma endregion ScopedGroup