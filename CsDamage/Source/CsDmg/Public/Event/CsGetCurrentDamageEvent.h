// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
#include "Containers/CsInterfaceObject.h"
// Types
#include "Types/CsTypes_Macro.h"

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