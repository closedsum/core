// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "UObject/Interface.h"

#include "CsAnimation_Event.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsAnimation_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class UAnimInstance;

// Anim
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsAnimationEvent_OnInit, UAnimInstance*, AnimInstance);

class CSCORE_API ICsAnimation_Event
{
	GENERATED_IINTERFACE_BODY()

public:

// Init
public:

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnInit, const UAnimInstance* /*AnimInstance*/);

	virtual FOnInit& GetOnInit_Event() = 0;
	virtual FCsAnimationEvent_OnInit& GetOnInit_ScriptEvent() = 0;
};