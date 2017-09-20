// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Components/CsPoseableMeshComponent.h"
#include "CsCore.h"
#include "CsTypes.h"
#include "CsCommon.h"

UCsPoseableMeshComponent::UCsPoseableMeshComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

#if WITH_EDITOR

void UCsPoseableMeshComponent::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	if (UCsCommon::IsPlayInEditor(GetWorld()))
	{
		if (PropertyName == GET_MEMBER_NAME_CHECKED(USkinnedMeshComponent, SkeletalMesh))
		{
			if (SkeletalMesh != Last_SkeletalMesh)
			{

			}
			Last_SkeletalMesh = SkeletalMesh;
		}
	}
	Super::PostEditChangeProperty(e);
}

void UCsPoseableMeshComponent::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& e)
{
	Super::PostEditChangeChainProperty(e);
}

#endif // #if WITH_EDITOR