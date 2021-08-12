// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"

#include "CsGetCollisionHitCount.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetCollisionHitCount : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetCollisionHitCount
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual int32 GetCollisionHitCount() const = 0;
};