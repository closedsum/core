// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interface
#include "Containers/CsGetInterfaceMap.h"

/**
*/
struct CSCORE_API ICsIsValid : public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsIsValid(){}

	virtual bool IsValidChecked(const FString& Context) = 0;

	virtual bool IsValid(const FString& Context, void(*Log)(const FString&) = nullptr) = 0;
};