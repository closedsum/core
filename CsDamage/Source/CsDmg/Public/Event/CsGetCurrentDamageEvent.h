// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
#include "Containers/CsInterfaceObject.h"
// Types
#include "Macro/CsMacro_Namespace.h"

#include "CsGetCurrentDamageEvent.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSDMG_API UCsGetCurrentDamageEvent : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

// NCsDamage::NEvent::IEvent
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NEvent, IEvent)

/**
*/
class CSDMG_API ICsGetCurrentDamageEvent
{
	GENERATED_IINTERFACE_BODY()

#define EventType NCsDamage::NEvent::IEvent

public:

	virtual const EventType* GetCurrentDamageEvent() const = 0;

#undef EventType
};