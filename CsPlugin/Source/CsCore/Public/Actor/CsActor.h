// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsActor.generated.h"

// FCsActor
#pragma region

class AActor;
class UClass;

USTRUCT(BlueprintType)
struct CSCORE_API FCsActor
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CsCore|Load")
	TSoftClassPtr<AActor> Actor;

	UPROPERTY()
	int32 Load_Flags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Load")
	AActor* Actor_Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Load")
	UClass* Actor_Class;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsCore|Load")
	TSubclassOf<AActor> Actor_SubclassOf;

	FCsActor() :
		Actor(nullptr),
		Load_Flags(0),
		Actor_Internal(nullptr),
		Actor_Class(nullptr),
		Actor_SubclassOf(nullptr)
	{
	}

	FORCEINLINE AActor* Get() const { return Actor_Internal; }
	
	template<typename T>
	FORCEINLINE T* Get() const { return Cast<T>(Get()); }

	FORCEINLINE UClass* GetClass() const { return Actor_Class; }

	template<typename T>
	FORCEINLINE T* GetClass() const { return Cast<T>(GetClass()); }

	FORCEINLINE TSubclassOf<AActor> GetSubclassOf() const { return Actor_SubclassOf; }
};

#pragma endregion FCsActor