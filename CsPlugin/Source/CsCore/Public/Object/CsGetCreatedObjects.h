// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "UObject/Interface.h"
// Types
#include "Object/CsTypes_Object.h"

#include "CsGetCreatedObjects.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetCreatedObjects : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetCreatedObjects
{
	GENERATED_IINTERFACE_BODY()

public:

#define CreatedObjectsType NCsObject::NCreate::FCreated

	virtual CreatedObjectsType* GetCreatedObjects() = 0;

#undef CreatedObjectsType
};