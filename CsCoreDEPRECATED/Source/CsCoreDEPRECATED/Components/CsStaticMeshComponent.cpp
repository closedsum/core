// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Components/CsStaticMeshComponent.h"
#include "CsCoreDEPRECATED.h"

UCsStaticMeshComponent::UCsStaticMeshComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

#if WITH_EDITOR

void UCsStaticMeshComponent::PostEditChangeProperty(struct FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	Super::PostEditChangeProperty(e);
}

void UCsStaticMeshComponent::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& e)
{
	Super::PostEditChangeChainProperty(e);
}

#endif // #if WITH_EDITOR