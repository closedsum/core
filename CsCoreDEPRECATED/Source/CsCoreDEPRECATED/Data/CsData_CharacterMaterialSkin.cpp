#include "Data/CsData_CharacterMaterialSkin.h"
#include "CsCoreDEPRECATED.h"

// Library
#include "Library/CsLibrary_Common.h"

#include "../Engine/Classes/Animation/SkeletalMeshActor.h"
#include "Materials/MaterialInstanceConstant.h"

UCsData_CharacterMaterialSkin::UCsData_CharacterMaterialSkin(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Skin
#pragma region

TArray<UMaterialInstanceConstant*>* UCsData_CharacterMaterialSkin::GetMaterials(const ECsViewType& ViewType, const bool& IsLow /*=false*/)
{
	return nullptr;
}

TArray<UMaterialInstanceConstant*>* UCsData_CharacterMaterialSkin::GetMaterials()
{
	return nullptr;
}

void UCsData_CharacterMaterialSkin::SetMaterials(USkeletalMeshComponent* InMesh, const ECsViewType& ViewType, const bool& IsLow /*=false*/)
{
	UCsLibrary_Common::SetMaterials(InMesh, *GetMaterials(ViewType, IsLow));
}

void UCsData_CharacterMaterialSkin::SetMaterials(ASkeletalMeshActor* InActor, const ECsViewType& ViewType, const bool& IsLow /*=false*/)
{
	SetMaterials(InActor->GetSkeletalMeshComponent(), ViewType, IsLow);
}

void UCsData_CharacterMaterialSkin::SetMaterials(UObject* InObject, const ECsViewType& ViewType, const bool& IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(InObject))
		SetMaterials(Mesh, ViewType, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetMaterials(Actor, ViewType, IsLow);
}

void UCsData_CharacterMaterialSkin::SetMaterials(USkeletalMeshComponent* InMesh)
{
	UCsLibrary_Common::SetMaterials(InMesh, *GetMaterials());
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