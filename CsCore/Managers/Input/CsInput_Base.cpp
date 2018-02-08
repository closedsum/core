// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsInput_Base.h"
#include "CsCore.h"

UCsInput_Base::UCsInput_Base(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
#if WITH_EDITOR
	FEditorDelegates::PrePIEEnded.AddUObject(this, &UCsInput_Base::OnPrePIEEnded);
#endif // #if WITH_EDITOR
}

#if WITH_EDITOR

void UCsInput_Base::OnPrePIEEnded(const bool IsSimulating)
{
	RemoveFromRoot();
}

#endif // #if WITH_EDITOR