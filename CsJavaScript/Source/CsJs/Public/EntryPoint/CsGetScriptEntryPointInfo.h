// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"
// Types
#include "EntryPoint/CsTypes_ScriptEntryPointInfo.h"

#include "CsGetScriptEntryPointInfo.generated.h"

UINTERFACE(BlueprintType)
class CSJS_API UCsGetScriptEntryPointInfo : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSJS_API ICsGetScriptEntryPointInfo
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