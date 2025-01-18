// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "Managers/Time/CsTypes_Time.h"

#include "CsUpdate_Override.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSTIME_API UCsUpdate_Override : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsOverride_UpdateImpl, const FCsDeltaTime&, DeltaTime);
// NOTE: For scripts (i.e. Python) that don't handle const ref properly
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsOverride_UpdateImpl2, FCsDeltaTime, DeltaTime);

class CSTIME_API ICsUpdate_Override
{
	GENERATED_IINTERFACE_BODY()
public:

	virtual void Set_Override_Update() = 0;

	virtual void Clear_Override_Update() = 0;

	virtual FCsOverride_UpdateImpl& GetOverride_UpdateImpl_ScriptEvent() = 0;

	virtual FCsOverride_UpdateImpl2& GetOverride_UpdateImpl2_ScriptEvent() = 0;
};