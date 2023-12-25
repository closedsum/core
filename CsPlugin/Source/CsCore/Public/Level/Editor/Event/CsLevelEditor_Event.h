// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "UObject/Interface.h"

#include "CsLevelEditor_Event.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsLevelEditor_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsLevelEditor_OnActorSelectionChanged, const TArray<UObject*>&, NewSelection, bool, bForceRefresh);

class CSCORE_API ICsLevelEditor_Event
{
	GENERATED_IINTERFACE_BODY()

public:

	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnActorSelectionChanged, const TArray<UObject*>& /*NewSelection*/, bool /*bForceRefresh*/);

	virtual FOnActorSelectionChanged& GetOnActorSelectionChanged_Event() = 0;

	virtual FCsLevelEditor_OnActorSelectionChanged& GetOnActorSelectionChanged_ScriptEvent() = 0;
};