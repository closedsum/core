#include "Data/CsData_CharacterMeshSkin.h"
#include "CsCore.h"
#include "../Engine/Classes/Animation/SkeletalMeshActor.h"

ACsData_CharacterMeshSkin::ACsData_CharacterMeshSkin(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ACsData_CharacterMeshSkin::SetMesh(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType){}

void ACsData_CharacterMeshSkin::SetMesh(ASkeletalMeshActor* InActor, const TCsViewType &ViewType)
{
	SetMesh(InActor->GetSkeletalMeshComponent(), ViewType);
}

void ACsData_CharacterMeshSkin::SetMesh(UObject* InObject, const TEnumAsByte<ECsViewType::Type> &ViewType)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(InObject))
		SetMesh(Mesh, ViewType);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetMesh(Actor, ViewType);
}