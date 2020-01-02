// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData_Impl.h"
#include "Types/CsTypes_View.h"
#include "CsData_WeaponMaterialSkin.generated.h"

class UMaterialInstanceConstant;
class USkeletalMeshComponent;
class ASkeletalMeshActor;

UCLASS(Abstract)
class CSCORE_API UCsData_WeaponMaterialSkin : public UCsData_Impl
{
	GENERATED_UCLASS_BODY()

// Skin
#pragma region

	virtual TArray<UMaterialInstanceConstant*>* GetMaterials(const ECsViewType& ViewType, const bool& IsLow = false);
	virtual TArray<UMaterialInstanceConstant*>* GetMaterials();

	virtual void SetMaterials(USkeletalMeshComponent* InMesh, const ECsViewType& ViewType, const bool& IsLow = false);
	virtual void SetMaterials(ASkeletalMeshActor* InActor, const ECsViewType& ViewType, const bool& IsLow = false);
	UFUNCTION(BlueprintCallable, Category = "Skin")
	virtual void SetMaterials(UObject* InObject, const ECsViewType& ViewType, const bool& IsLow = false);

	virtual void SetMaterials(USkeletalMeshComponent* InMesh);
	virtual void SetMaterials(ASkeletalMeshActor* InActor);
	virtual void SetMaterials(UObject* InObject);

#pragma endregion Skin
};