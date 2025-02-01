// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "Coordinators/GameplayTag/CsCoordinator_GameplayTag_Delegates.h"

#include "CsOnProcessGameplayTagEvent_Override.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSGAMEPLAYTAGS_API UCsOnProcessGameplayTagEvent_Override : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSGAMEPLAYTAGS_API ICsOnProcessGameplayTagEvent_Override
{
	GENERATED_IINTERFACE_BODY()
public:

	virtual void Set_Override_OnProcessGameplayTagEvent() = 0;

	virtual void Clear_Override_OnProcessGameplayTagEvent() = 0;

	virtual FCsOverride_OnProcessGameplayTagEventImpl& GetOverride_OnProcessGameplayTagEventImpl_ScriptEvent() = 0;

	virtual FCsOverride_OnProcessGameplayTagEventImpl2& GetOverride_OnProcessGameplayTagEventImpl2_ScriptEvent() = 0;
};