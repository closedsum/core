// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetCollisionHitCount.generated.h"

UINTERFACE(Blueprintable)
class CSTYPES_API UCsGetCollisionHitCount : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSTYPES_API ICsGetCollisionHitCount
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual int32 GetCollisionHitCount() const = 0;
};