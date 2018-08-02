// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "GameFramework/Actor.h"
#include "Types/CsTypes_Damage.h"
#include "CsManager_Damage.generated.h"

#define CS_DAMAGE_EVENT_POOL_SIZE 255
#define CS_DAMAGE_RESULT_POOL_SIZE 255

UCLASS()
class CSCORE_API ACsManager_Damage : public AActor
{
	GENERATED_UCLASS_BODY()

protected:

	static TWeakObjectPtr<UObject> MyOwner;

	static UObject* GetMyOwner();
	template<typename T>
	static T* GetMyOwner()
	{
		return Cast<T>(GetMyOwner());
	}

public:

	static void Init(UObject* InOwner);
	static ACsManager_Damage* Get(UWorld* InWorld);

// Event
#pragma region

	FCsDamageEvent EventPool[CS_DAMAGE_EVENT_POOL_SIZE];

	uint8 EventPoolIndex;

	virtual FCsDamageEvent* AllocateEvent();

#pragma endregion Event

// Result
#pragma region

	FCsDamageResult ResultPool[CS_DAMAGE_RESULT_POOL_SIZE];

	uint8 ResultPoolIndex;

	virtual FCsDamageResult* AllocateResult();

#pragma endregion Result
};