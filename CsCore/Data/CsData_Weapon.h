// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes_Weapon.h"
#include "CsData_Weapon.generated.h"

UCLASS(Abstract, hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Weapon : public ACsData
{
	GENERATED_UCLASS_BODY()

// Stats
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual const FName& GetItemShortCode();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	virtual const bool& UseInventory();

#pragma endregion Stats

// Mesh
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "Mesh")
	virtual const bool& UseMesh();

	virtual USkeletalMesh* GetMesh(const TCsViewType &ViewType, const bool &IsLow = false);
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	virtual USkeletalMesh* GetMesh(const TEnumAsByte<ECsViewType::Type> &ViewType, const bool &IsLow = false);
	virtual USkeletalMesh* GetMesh();

	virtual void SetMesh(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const bool &IsLow = false);
	virtual void SetMesh(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const bool &IsLow = false);
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	virtual void SetMesh(UObject* InObject, const TEnumAsByte<ECsViewType::Type> &ViewType, const bool &IsLow = false);

	virtual void SetMesh(USkeletalMeshComponent* InMesh);
	virtual void SetMesh(class ASkeletalMeshActor* InActor);
	virtual void SetMesh(UObject* InObject);

	virtual void GetDefaultMaterials(TArray<class UMaterialInstanceConstant*> &OutMaterials, const TCsViewType &ViewType, const bool &IsLow = false);
	virtual void GetDefaultMaterials(TArray<class UMaterialInstanceConstant*> &OutMaterials);

#pragma endregion Mesh

// Anims
#pragma region
public:

	virtual void SetAnimBlueprint(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const bool &IsLow = false);
	virtual void SetAnimBlueprint(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const bool &IsLow = false);
	UFUNCTION(BlueprintCallable, Category = Animation)
	virtual void SetAnimBlueprint(class UObject* InActor, const TEnumAsByte<ECsViewType::Type> &ViewType, const bool &IsLow = false);

	virtual void SetAnimBlueprint(USkeletalMeshComponent* InMesh);
	virtual void SetAnimBlueprint(class ASkeletalMeshActor* InActor);
	virtual void SetAnimBlueprint(class UObject* InActor);

#pragma endregion Anims
};