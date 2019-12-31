#include "Data/CsData_CharacterMaterialSkin.h"
#include "CsCore.h"
#include "Common/CsCommon.h"

#include "../Engine/Classes/Animation/SkeletalMeshActor.h"
#include "Materials/MaterialInstanceConstant.h"

UCsData_CharacterMaterialSkin::UCsData_CharacterMaterialSkin(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Skin
#pragma region

TArray<UMaterialInstanceConstant*>* UCsData_CharacterMaterialSkin::GetMaterials(const TCsViewType& ViewType, const bool& IsLow /*=false*/)
{
	return nullptr;
}

TArray<UMaterialInstanceConstant*>* UCsData_CharacterMaterialSkin::GetMaterials()
{
	return nullptr;
}

void UCsData_CharacterMaterialSkin::SetMaterials(USkeletalMeshComponent* InMesh, const TCsViewType& ViewType, const bool& IsLow /*=false*/)
{
	UCsCommon::SetMaterials(InMesh, *GetMaterials(ViewType, IsLow));
}

void UCsData_CharacterMaterialSkin::SetMaterials(ASkeletalMeshActor* InActor, const TCsViewType& ViewType, const bool& IsLow /*=false*/)
{
	SetMaterials(InActor->GetSkeletalMeshComponent(), ViewType, IsLow);
}

void UCsData_CharacterMaterialSkin::SetMaterials(UObject* InObject, const TEnumAsByte<ECsViewType::Type>& ViewType, const bool& IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(InObject))
		SetMaterials(Mesh, (TCsViewType)ViewType, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetMaterials(Actor, (TCsViewType)ViewType, IsLow);
}

void UCsData_CharacterMaterialSkin::SetMaterials(USkeletalMeshComponent* InMesh)
{
	UCsCommon::SetMaterials(InMesh, *GetMaterials());
}

void UCsData_CharacterMaterialSkin::SetMaterials(ASkeletalMeshActor* InActor)
{
	SetMaterials(InActor->GetSkeletalMeshComponent());
}

void UCsData_CharacterMaterialSkin::SetMaterials(UObject* InObject)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(InObject))
		SetMaterials(Mesh);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetMaterials(Actor);
}

#pragma endregion Skin