// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData_Impl.h"
#include "Types/CsTypes_Interactive.h"
#include "CsData_Interactive.generated.h"

class UStaticMesh;
class USkeletalMesh;
class UStaticMeshComponent;
class USkeletalMeshComponent;
class UMaterialInstanceConstant;

UCLASS(Abstract)
class CSCORE_API UCsData_Interactive : public UCsData_Impl
{
	GENERATED_UCLASS_BODY()

// Stats
#pragma region
public:

	virtual const FECsInteractiveType& GetInteractiveType();

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
	virtual UStaticMesh* GetStaticMesh();
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	virtual USkeletalMesh* GetSkeletalMesh();

	virtual TArray<UMaterialInstanceConstant*>* GetMaterials();

	void SetMeshAndMaterials(UStaticMeshComponent* InMesh);
	void SetMeshAndMaterials(USkeletalMeshComponent* InMesh);

#pragma endregion Mesh

// Collision
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual const bool& UseWorldCollisionPreset();
	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual void SetWorldCollisionFromPreset(UPrimitiveComponent* InComponent);

	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual const float& GetInteractiveCollisionRadius();
	UFUNCTION(BlueprintCallable, Category = "Collision")
	virtual const float& GetInteractiveCollisionRadiusSq();

#pragma endregion Collision

// Movement
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual const bool& UsePhysicsPreset();
	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual void SetPhysicsFromPreset(UPrimitiveComponent* InComponent);
	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual const bool& SimulatePhysics();

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual void ToggleWorldCollisionAndPhysics(UPrimitiveComponent* InComponent, const bool& Toggle);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual const bool& UseSpawnPhysicsImpulse();
	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual void ApplySpawnPhysicsImpulse(UPrimitiveComponent* InComponent, const bool& bSeed = true);

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