#pragma once
#include "Data/CsData.h"
#include "CsData_CharacterMaterialSkin.generated.h"

/* Current Order of Categories

01. Skin

*/

UCLASS(Abstract, hidecategories = (Object, Actor, Replication, Rendering, Input, "Actor Tick"))
class CSCORE_API ACsData_CharacterMaterialSkin : public ACsData
{
	GENERATED_UCLASS_BODY()

// Skin
#pragma region

	virtual TArray<class UMaterialInstanceConstant*>* GetMaterials(const TCsViewType &ViewType, const bool &IsLow = false);
	virtual TArray<class UMaterialInstanceConstant*>* GetMaterials(const bool &IsLow = false);

	virtual void SetMaterials(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const bool &IsLow = false);
	virtual void SetMaterials(class ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const bool &IsLow = false);

	UFUNCTION(BlueprintCallable, Category = "Character Material Skin")
	virtual void SetMaterials(UObject* InObject, const TEnumAsByte<ECsViewType::Type> &ViewType, const bool &IsLow = false);

	virtual void SetMaterials(USkeletalMeshComponent* InMesh, const bool &IsLow = false);
	virtual void SetMaterials(class ASkeletalMeshActor* InActor, const bool &IsLow = false);
	virtual void SetMaterials(UObject* InObject, const bool &IsLow = false);

#pragma endregion Skin
};