// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "UObject/Interface.h"

#include "CsWorldContext.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsWorldContext : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class UObject;

class CSCORE_API ICsWorldContext
{
	GENERATED_IINTERFACE_BODY()
	
public:

	virtual void SetWorldContext(UObject* InWorldContext) = 0;

	virtual const UObject* GetWorldContext() const = 0;
	virtual UObject* GetWorldContext() = 0;
};