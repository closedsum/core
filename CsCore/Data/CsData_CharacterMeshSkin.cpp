#include "Data/CsData_CharacterMeshSkin.h"
#include "CsCore.h"
#include "../Engine/Classes/Animation/SkeletalMeshActor.h"

ACsData_CharacterMeshSkin::ACsData_CharacterMeshSkin(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ACsData_CharacterMeshSkin::SetMesh(USkeletalMeshComponent* InMesh, const TCsViewType &ViewType, const bool &IsLow /*=false*/){}

void ACsData_CharacterMeshSkin::SetMesh(ASkeletalMeshActor* InActor, const TCsViewType &ViewType, const bool &IsLow /*=false*/)
{
	SetMesh(InActor->GetSkeletalMeshComponent(), ViewType, IsLow);
}

void ACsData_CharacterMeshSkin::SetMesh(UObject* InObject, const TEnumAsByte<ECsViewType::Type> &ViewType, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		SetMesh(InMesh, ViewType, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetMesh(Actor, ViewType, IsLow);
}

void ACsData_CharacterMeshSkin::SetMesh(USkeletalMeshComponent* InMesh, const bool &IsLow /*=false*/) {}

void ACsData_CharacterMeshSkin::SetMesh(ASkeletalMeshActor* InActor, const bool &IsLow /*=false*/)
{
	SetMesh(InActor->GetSkeletalMeshComponent(), IsLow);
}

void ACsData_CharacterMeshSkin::SetMesh(UObject* InObject, const bool &IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		SetMesh(InMesh, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetMesh(Actor, IsLow);
}