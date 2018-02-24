// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "CsData_Interactive.generated.h"

UCLASS(Abstract, hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Interactive : public ACsData
{
	GENERATED_UCLASS_BODY()

// Stats
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual float GetWarmUpTime();
	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual float GetLifeTime();

#pragma endregion Stats

// Mesh
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	virtual class UStaticMesh* GetStaticMesh();
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	virtual class USkeletalMesh* GetSkeletalMesh();

	virtual TArray<class UMaterialInstanceConstant*>* GetMaterials();

	void SetMeshAndMaterials(UStaticMeshComponent* InMesh);
	void SetMeshAndMaterials(USkeletalMeshComponent* InMesh);

#pragma endregion Mesh

// Collision
#pragma region

	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual float GetCollisionRadius();
	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual float GetCollisionRadiusSq();

#pragma endregion Collision

// UI
#pragma region
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool OnSpawnSpawnWidget();
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual FString GetDisplayName();
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void GetScreenSpaceOffset(FIntPoint &OutPoint);

#pragma endregion UI
};