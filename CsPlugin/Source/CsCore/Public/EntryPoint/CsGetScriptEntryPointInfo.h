// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
// Types
#include "EntryPoint/CsTypes_ScriptEntryPointInfo.h"

#include "CsGetScriptEntryPointInfo.generated.h"

UINTERFACE(BlueprintType)
class CSCORE_API UCsGetScriptEntryPointInfo : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetScriptEntryPointInfo
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*
	* return
	*/
	virtual const FCsScriptEntryPointInfo& GetScriptEntryPointInfo() const = 0;
};