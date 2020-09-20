// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumMap.h"
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

typedef ECsThreadPriority::Type TCsThreadPriority;

struct CSCORE_API EMCsThreadPriority : public TCsEnumMap<ECsThreadPriority::Type>
{
protected:
	EMCsThreadPriority() {}
	EMCsThreadPriority(const EMCsThreadPriority &) = delete;
	EMCsThreadPriority(EMCsThreadPriority &&) = delete;
public:
	~EMCsThreadPriority() {}
private:
	static EMCsThreadPriority* Instance;

public:
	static EMCsThreadPriority& Get();
};

namespace ECsThreadPriority
{
	namespace Ref
	{
		extern CSCORE_API const Type TPri_Normal;
		extern CSCORE_API const Type TPri_AboveNormal;
		extern CSCORE_API const Type TPri_BelowNormal;
		extern CSCORE_API const Type TPri_Highest;
		extern CSCORE_API const Type TPri_Lowest;
		extern CSCORE_API const Type TPri_SlightlyBelowNormal;
		extern CSCORE_API const Type TPri_TimeCritical;
		extern CSCORE_API const Type ECsThreadPriority_MAX;
	}

	FORCEINLINE const Type& ToType(const EThreadPriority &EType)
	{
		if (EType == EThreadPriority::TPri_Normal) { return Ref::TPri_Normal; }
		if (EType == EThreadPriority::TPri_AboveNormal) { return Ref::TPri_AboveNormal; }
		if (EType == EThreadPriority::TPri_BelowNormal) { return Ref::TPri_BelowNormal; }
		if (EType == EThreadPriority::TPri_Highest) { return Ref::TPri_Highest; }
		if (EType == EThreadPriority::TPri_Lowest) { return Ref::TPri_Lowest; }
		if (EType == EThreadPriority::TPri_SlightlyBelowNormal) { return Ref::TPri_SlightlyBelowNormal; }
		if (EType == EThreadPriority::TPri_TimeCritical) { return Ref::TPri_TimeCritical; }
		return Ref::ECsThreadPriority_MAX;
	}

	FORCEINLINE EThreadPriority ToBaseType(const Type &EType)
	{
		if (EType == Ref::TPri_Normal) { return EThreadPriority::TPri_Normal; }
		if (EType == Ref::TPri_AboveNormal) { return EThreadPriority::TPri_AboveNormal; }
		if (EType == Ref::TPri_BelowNormal) { return EThreadPriority::TPri_BelowNormal; }
		if (EType == Ref::TPri_Highest) { return EThreadPriority::TPri_Highest; }
		if (EType == Ref::TPri_Lowest) { return EThreadPriority::TPri_Lowest; }
		if (EType == Ref::TPri_SlightlyBelowNormal) { return EThreadPriority::TPri_SlightlyBelowNormal; }
		if (EType == Ref::TPri_TimeCritical) { return EThreadPriority::TPri_TimeCritical; }
		return EThreadPriority::TPri_Lowest;
	}
}

struct FCsRunnablePayload
{
	bool bAllocated;

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
		bAllocated = false;
		Owner.Reset();
		Owner = nullptr;
		StackSize = 0;
		ThreadPriority = EThreadPriority::TPri_Lowest;
	}

	class UObject* GetOwner() { return Owner.IsValid() ? Owner.Get() : nullptr; }
	template<typename T>
	T* GetOwner() { return Cast<T>(GetOwner()); }
};