// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/CsManager.h"
#include "Types/CsTypes_Pool.h"
#include "CsManager_Decal.generated.h"

#define CS_DECAL_POOL_SIZE 64

USTRUCT(BlueprintType)
struct FCsDecalCache : public FCsPooledObjectCache
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	uint8 PoolIndex;

	UPROPERTY()
	float TimeAllocated;

	UPROPERTY()
	class ADecalActor* DecalActor;

	FCsDecalCache() :
		PoolIndex(0),
		TimeAllocated(0.0f),
		DecalActor(nullptr)
	{
	}

	~FCsDecalCache(){}
};

UCLASS()
class CSCORE_API ACsManager_Decal : public AActor
{
	GENERATED_UCLASS_BODY()

		/*
	virtual void Shutdown() override;

	void OnTick(const float &DeltaSeconds);

	virtual void Destroyed() override;
	virtual void CreatePool(const int32 &Size);
	*/
	static ACsManager_Decal* Get(UWorld* InWorld);

	/*
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pool")
	TArray<FCsDecalCache> Pool;

	TArray<FCsDecalCache> ActiveDecals;

	FCsDecalCache Allocate();

	virtual void DeAllocate(const int32 &Index) override;
	virtual void DeAllocateAll() override;
	*/
};