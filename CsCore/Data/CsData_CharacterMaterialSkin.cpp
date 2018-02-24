#include "Data/CsData_CharacterMaterialSkin.h"
#include "CsCore.h"
#include "Common/CsCommon.h"

#include "../Engine/Classes/Animation/SkeletalMeshActor.h"

ACsData_CharacterMaterialSkin::ACsData_CharacterMaterialSkin(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Skin
#pragma region

TArray<class UMaterialInstanceConstant*>* ACsData_CharacterMaterialSkin::GetMaterials(const TCsViewType &ViewType, const bool &IsLow /*=false*/)
{
	return nullptr;
}

void ACsData_CharacterMaterialSkin::SetMaterials(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const bool &IsLow /*=false*/)
{
	UCsCommon::SetMaterials(InMesh, *GetMaterials(ViewType, IsLow));
}

void ACsData_CharacterMaterialSkin::SetMaterials(ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const bool &IsLow /*=false*/)
{
	SetMaterials(InActor->GetSkeletalMeshComponent(), ViewType, IsLow);
}

void ACsData_CharacterMaterialSkin::SetMaterials(UObject* InObject, const TEnumAsByte<ECsViewType::Type> &ViewType, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(InObject))
		SetMaterials(Mesh, ViewType, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetMaterials(Actor, ViewType, IsLow);
}

#pragma endregion Skin