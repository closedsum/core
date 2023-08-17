// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Interface.h"
// Types
#include "Script/CsTypes_ScriptInfo.h"

#include "CsGetScriptInfo.generated.h"

UINTERFACE(BlueprintType)
class CSCORE_API UCsGetScriptInfo : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetScriptInfo
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*
	* return
	*/
	virtual const FCsScriptInfo& GetScriptInfo() const = 0;
};