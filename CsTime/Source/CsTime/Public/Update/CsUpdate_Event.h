// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "Managers/Time/CsTypes_Time.h"

#include "CsUpdate_Event.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSTIME_API UCsUpdate_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsOnUpdate, const FCsDeltaTime&, DeltaTime);
// NOTE: For scripts (i.e. Python) that don't handle const ref properly
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsOnUpdate2, FCsDeltaTime, DeltaTime);

namespace NCsUpdate
{
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpcate, const FCsDeltaTime& /*DeltaTime*/);
}

class CSTIME_API ICsUpdate_Event
{
	GENERATED_IINTERFACE_BODY()

private:

	// Allow clearer names without name collisions
	struct _
	{
		using OnUpdateEventType = NCsUpdate::FOnUpcate;
	};

public:

	virtual _::OnUpdateEventType& GetUpdate_Event() = 0;

	virtual FCsOnUpdate& GetUpdate_ScriptEvent() = 0;

	virtual FCsOnUpdate2& GetUpdate2_ScriptEvent() = 0;
};