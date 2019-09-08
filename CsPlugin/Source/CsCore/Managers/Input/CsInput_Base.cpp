// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsInput_Base.h"
#include "CsCore.h"

#if WITH_EDITOR
#include "Editor.h"
#endif // #if WITH_EDITOR

UCsInput_Base::UCsInput_Base(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
#if WITH_EDITOR
	FEditorDelegates::PrePIEEnded.AddUObject(this, &UCsInput_Base::OnPrePIEEnded);
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

void UCsInput_Base::OnPrePIEEnded(const bool bIsSimulating)
{
	RemoveFromRoot();
}

#endif // #if WITH_EDITOR