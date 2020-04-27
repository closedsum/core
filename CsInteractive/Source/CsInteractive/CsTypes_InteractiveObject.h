// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_InteractiveObject.generated.h"
#pragma once

class UObject;

struct CSINTERACTIVE_API ICsInteractiveObjectInfo
{
	virtual UObject* GetInstigator() = 0;

	virtual FVector GetLocation() = 0;
};

USTRUCT(BlueprintType)
struct CSINTERACTIVE_API FCsScriptInteractiveObjectInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
	TWeakObjectPtr<UObject> Instigator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cache")
	FVector Location;

	FCsScriptInteractiveObjectInfo()
	{
		Reset();
	}
	virtual ~FCsScriptInteractiveObjectInfo() {}

	virtual void Reset()
	{
		Instigator.Reset();
		Location = FVector::ZeroVector;
	}

	FORCEINLINE UObject* GetInstigator() { return Instigator.IsValid() ? Instigator.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetInstigator() { return Cast<T>(GetInstigator()); }
};