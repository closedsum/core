// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "CsPIE_Delegates.h"

#include "CsPIE_Event.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSPIE_API UCsPIE_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSPIE_API ICsPIE_Event
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual FCsPIE_OnBegin& GetPIE_OnBegin_ScriptEvent() = 0;
	virtual FCsPIE_OnEnd& GetPIE_OnEnd_ScriptEvent() = 0;
	virtual FCsPIE_OnEnd_Last& GetPIE_OnEnd_Last_ScriptEvent() = 0;
	virtual FCsPIE_OnEnd_NextFrame& GetPIE_OnEnd_NextFrame_ScriptEvent() = 0;
	virtual FCsPIE_OnEndPlayMap& GetPIE_OnEndPlayMap_ScriptEvent() = 0;
};