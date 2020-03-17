#pragma once
#include "Data/CsData_Impl.h"
#include "Types/CsTypes_View.h"
#include "CsData_CharacterMaterialSkin.generated.h"

/* Current Order of Categories

01. Skin

*/

class UMaterialInstanceConstant;

UCLASS(Abstract)
class CSCORE_API UCsData_CharacterMaterialSkin : public UCsData_Impl
{
	GENERATED_UCLASS_BODY()

// Skin
#pragma region

	virtual TArray<UMaterialInstanceConstant*>* GetMaterials(const ECsViewType& ViewType, const bool& IsLow = false);
	virtual TArray<UMaterialInstanceConstant*>* GetMaterials();

	virtual void SetMaterials(USkeletalMeshComponent* InMesh, const ECsViewType& ViewType, const bool& IsLow = false);
	virtual void SetMaterials(class ASkeletalMeshActor* InActor, const ECsViewType& ViewType, const bool& IsLow = false);

	UFUNCTION(BlueprintCallable, Category = "Character Material Skin")
	virtual void SetMaterials(UObject* InObject, const ECsViewType& ViewType, const bool& IsLow = false);

	virtual void SetMaterials(USkeletalMeshComponent* InMesh);
	virtual void SetMaterials(class ASkeletalMeshActor* InActor);
	virtual void SetMaterials(UObject* InObject);

#pragma endregion Skin
};