// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Enhanced/CsEnhancedInputListener.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsEnhancedInputListener)

UCsEnhancedInputListener::UCsEnhancedInputListener(const FObjectInitializer& ObjectInitializer) : 
	Super(ObjectInitializer),
	ActionIndex(INDEX_NONE),
	OnAction_Event()
{
}

void UCsEnhancedInputListener::Init(const int32& Index)
{
	ActionIndex	= Index;
}

void UCsEnhancedInputListener::OnAction(const FInputActionInstance& ActionInstance)
{
	OnAction_Event.Execute(ActionIndex, ActionInstance);
}