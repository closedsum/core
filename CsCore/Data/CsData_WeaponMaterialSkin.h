// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData.h"
#include "Types/CsTypes_View.h"
#include "CsData_WeaponMaterialSkin.generated.h"

UCLASS(hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_WeaponMaterialSkin : public ACsData
{
	GENERATED_UCLASS_BODY()

// Skin
#pragma region

	virtual TArray<class UMaterialInstanceConstant*>* GetMaterials(const TCsViewType &ViewType, const bool &IsLow = false);

	virtual void SetMaterials(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const bool &IsLow = false);
	virtual void SetMaterials(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const bool &IsLow = false);
	UFUNCTION(BlueprintCallable, Category = "Skin")
	virtual void SetMaterials(UObject* InObject, const TEnumAsByte<ECsViewType::Type> &ViewType, const bool &IsLow = false);

#pragma endregion Skin
};