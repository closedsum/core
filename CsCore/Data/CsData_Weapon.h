// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes_Weapon.h"
#include "CsData_Weapon.generated.h"

UCLASS(Abstract, hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_Weapon : public ACsData
{
	GENERATED_UCLASS_BODY()

// Mesh
#pragma region

	virtual USkeletalMesh* GetMesh(const TCsViewType &ViewType, const bool &IsLow = false);
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

	CS_DECLARE_WEAPON_ANIM

	virtual void SetAnimBlueprint(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const bool &IsLow = false);
	virtual void SetAnimBlueprint(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const bool &IsLow = false);
	UFUNCTION(BlueprintCallable, Category = Animation)
	virtual void SetAnimBlueprint(class UObject* InActor, const TEnumAsByte<ECsViewType::Type> &ViewType, const bool &IsLow = false);

	virtual void SetAnimBlueprint(USkeletalMeshComponent* InMesh);
	virtual void SetAnimBlueprint(class ASkeletalMeshActor* InActor);
	virtual void SetAnimBlueprint(class UObject* InActor);

#pragma endregion Anims
};