// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"

#include "CsActor.generated.h"

// FCsActor
#pragma region

class AActor;
class UClass;

USTRUCT(BlueprintType)
struct CSTYPES_API FCsActor
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "CsTypes|Actor")
	TSoftClassPtr<AActor> Actor;

	UPROPERTY()
	int32 Actor_LoadFlags;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsTypes|Actor")
	AActor* Actor_Internal;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsTypes|Actor")
	UClass* Actor_Class;

	UPROPERTY(Transient, BlueprintReadOnly, Category = "CsTypes|Actor")
	TSubclassOf<AActor> Actor_SubclassOf;

	FCsActor() :
		Actor(nullptr),
		Actor_LoadFlags(0),
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