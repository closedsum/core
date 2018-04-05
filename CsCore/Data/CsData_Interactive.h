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
public:

	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual const float& GetWarmUpTime();
	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual const float& GetLifeTime();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual const FVector& GetScale();

#pragma endregion Stats

// Mesh
#pragma region
public:

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
public:

	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual const bool& UseCollisionPreset();
	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual void SetCollisionFromPreset(UPrimitiveComponent* InComponent);
	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual const float& GetCollisionRadius();
	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual const float& GetCollisionRadiusSq();

#pragma endregion Collision

// Movement
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual const bool& UsePhysicsPreset();
	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual void SetPhysicsFromPreset(UPrimitiveComponent* InComponent);

	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual const bool& UseSpawnPhysicsImpulse();
	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual void ApplySpawnPhysicsImpulse(UPrimitiveComponent* InComponent);

#pragma endregion Movement

// UI
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual const bool& OnSpawnSpawnWidget();
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual const FString& GetDisplayName();
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void GetScreenSpaceOffset(FIntPoint &OutPoint);

#pragma endregion UI
};