// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Components/CsSkeletalMeshComponent.h"
#include "CsCoreDEPRECATED.h"

UCsSkeletalMeshComponent::UCsSkeletalMeshComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

#if WITH_EDITOR

void UCsSkeletalMeshComponent::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	Super::PostEditChangeProperty(e);
}

void UCsSkeletalMeshComponent::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& e)
{
	Super::PostEditChangeChainProperty(e);
}

#endif // #if WITH_EDITOR