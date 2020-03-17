#include "Data/CsData_CharacterMeshSkin.h"
#include "CsCoreDEPRECATED.h"

#include "../Engine/Classes/Animation/SkeletalMeshActor.h"

UCsData_CharacterMeshSkin::UCsData_CharacterMeshSkin(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsData_CharacterMeshSkin::SetMesh(USkeletalMeshComponent* InMesh, const ECsViewType& ViewType, const bool& IsLow /*=false*/){}

void UCsData_CharacterMeshSkin::SetMesh(ASkeletalMeshActor* InActor, const ECsViewType& ViewType, const bool& IsLow /*=false*/)
{
	SetMesh(InActor->GetSkeletalMeshComponent(), ViewType, IsLow);
}

void UCsData_CharacterMeshSkin::SetMesh(UObject* InObject, const ECsViewType& ViewType, const bool& IsLow /*=false*/)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		SetMesh(InMesh, ViewType, IsLow);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetMesh(Actor, ViewType, IsLow);
}

void UCsData_CharacterMeshSkin::SetMesh(USkeletalMeshComponent* InMesh) {}

void UCsData_CharacterMeshSkin::SetMesh(ASkeletalMeshActor* InActor)
{
	SetMesh(InActor->GetSkeletalMeshComponent());
}

void UCsData_CharacterMeshSkin::SetMesh(UObject* InObject)
{
	// Skeletal Mesh Component
	if (USkeletalMeshComponent* InMesh = Cast<USkeletalMeshComponent>(InObject))
		SetMesh(InMesh);
	// Skeletal Mesh Actor
	if (ASkeletalMeshActor* Actor = Cast<ASkeletalMeshActor>(InObject))
		SetMesh(Actor);
}