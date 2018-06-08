// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformAffinity.h"

#include "CsTypes_Runnable.generated.h"
#pragma once

UENUM(BlueprintType)
namespace ECsThreadPriority
{
	enum Type
	{
		TPri_Normal					UMETA(DisplayName = "Normal"),
		TPri_AboveNormal			UMETA(DisplayName = "Above Normal"),
		TPri_BelowNormal			UMETA(DisplayName = "Below Normal"),
		TPri_Highest				UMETA(DisplayName = "Highest"),
		TPri_Lowest					UMETA(DisplayName = "Lowest"),
		TPri_SlightlyBelowNormal	UMETA(DisplayName = "Slightly Below Normal"),
		TPri_TimeCritical			UMETA(DisplayName = "Time Critical"),
		ECsThreadPriority_MAX		UMETA(Hidden),
	};
}

namespace ECsThreadPriority
{
	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString TPri_Normal = TCsString(TEXT("TPri_Normal"), TEXT("tpri_normal"), TEXT("normal"));
		const TCsString TPri_AboveNormal = TCsString(TEXT("TPri_AboveNormal"), TEXT("tpri_abovenormal"), TEXT("above normal"));
		const TCsString TPri_BelowNormal = TCsString(TEXT("TPri_BelowNormal"), TEXT("tpri_belownormal"), TEXT("below normal"));
		const TCsString TPri_Highest = TCsString(TEXT("TPri_Highest"), TEXT("tpri_highest"), TEXT("highest"));
		const TCsString TPri_Lowest = TCsString(TEXT("TPri_Lowest"), TEXT("tpri_lowest"), TEXT("lowest"));
		const TCsString TPri_SlightlyBelowNormal = TCsString(TEXT("TPri_SlightlyBelowNormal"), TEXT("tpri_slightlybelownormal"), TEXT("slightly below normal"));
		const TCsString TPri_TimeCritical = TCsString(TEXT("TPri_TimeCritical"), TEXT("tpri_timecritical"), TEXT("time critical"));
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		if (EType == Type::TPri_Normal) { return Str::TPri_Normal.Value; }
		if (EType == Type::TPri_AboveNormal) { return Str::TPri_AboveNormal.Value; }
		if (EType == Type::TPri_BelowNormal) { return Str::TPri_BelowNormal.Value; }
		if (EType == Type::TPri_Highest) { return Str::TPri_Highest.Value; }
		if (EType == Type::TPri_Lowest) { return Str::TPri_Lowest.Value; }
		if (EType == Type::TPri_SlightlyBelowNormal) { return Str::TPri_SlightlyBelowNormal.Value; }
		if (EType == Type::TPri_TimeCritical) { return Str::TPri_TimeCritical.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::TPri_Normal) { return Type::TPri_Normal; }
		if (String == Str::TPri_AboveNormal) { return Type::TPri_AboveNormal; }
		if (String == Str::TPri_BelowNormal) { return Type::TPri_BelowNormal; }
		if (String == Str::TPri_Highest) { return Type::TPri_Highest; }
		if (String == Str::TPri_Lowest) { return Type::TPri_Lowest; }
		if (String == Str::TPri_SlightlyBelowNormal) { return Type::TPri_SlightlyBelowNormal; }
		if (String == Str::TPri_BelowNormal) { return Type::TPri_BelowNormal; }
		return Type::ECsThreadPriority_MAX;
	}

	FORCEINLINE Type ToType(const EThreadPriority &EType)
	{
		if (EType == EThreadPriority::TPri_Normal) { return Type::TPri_Normal; }
		if (EType == EThreadPriority::TPri_AboveNormal) { return Type::TPri_AboveNormal; }
		if (EType == EThreadPriority::TPri_BelowNormal) { return Type::TPri_BelowNormal; }
		if (EType == EThreadPriority::TPri_Highest) { return Type::TPri_Highest; }
		if (EType == EThreadPriority::TPri_Lowest) { return Type::TPri_Lowest; }
		if (EType == EThreadPriority::TPri_SlightlyBelowNormal) { return Type::TPri_SlightlyBelowNormal; }
		if (EType == EThreadPriority::TPri_TimeCritical) { return Type::TPri_TimeCritical; }
		return Type::ECsThreadPriority_MAX;
	}

	FORCEINLINE EThreadPriority ToBaseType(const Type &EType)
	{
		if (EType == Type::TPri_Normal) { return EThreadPriority::TPri_Normal; }
		if (EType == Type::TPri_AboveNormal) { return EThreadPriority::TPri_AboveNormal; }
		if (EType == Type::TPri_BelowNormal) { return EThreadPriority::TPri_BelowNormal; }
		if (EType == Type::TPri_Highest) { return EThreadPriority::TPri_Highest; }
		if (EType == Type::TPri_Lowest) { return EThreadPriority::TPri_Lowest; }
		if (EType == Type::TPri_SlightlyBelowNormal) { return EThreadPriority::TPri_SlightlyBelowNormal; }
		if (EType == Type::TPri_TimeCritical) { return EThreadPriority::TPri_TimeCritical; }
		return EThreadPriority::TPri_Lowest;
	}
}

struct FCsRunnablePayload
{
	bool IsAllocated;

	TWeakObjectPtr<class UObject> Owner;

	uint32 StackSize;
	EThreadPriority ThreadPriority;

	FCsRunnablePayload()
	{
		Reset();
	}
	~FCsRunnablePayload() {}

	void Reset()
	{
		IsAllocated = false;
		Owner.Reset();
		Owner = nullptr;
		StackSize = 0;
		ThreadPriority = EThreadPriority::TPri_Lowest;
	}

	class UObject* GetOwner() { return Owner.IsValid() ? Owner.Get() : nullptr; }
	template<typename T>
	T* GetOwner() { return Cast<T>(GetOwner()); }
};