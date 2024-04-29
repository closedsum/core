// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interface
#include "Containers/CsGetInterfaceMap.h"

#include "CsIsValid.generated.h"


UINTERFACE(Blueprintable)
class CSVALID_API UCsIsValid : public UCsGetInterfaceMap
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSVALID_API ICsIsValid : public ICsGetInterfaceMap
{
	GENERATED_IINTERFACE_BODY()

public:

	static const FName Name;

public:

	virtual bool IsValidChecked(const FString& Context) const = 0;

	virtual bool IsValid(const FString& Context, void(*Log)(const FString&) = nullptr) const = 0;
};