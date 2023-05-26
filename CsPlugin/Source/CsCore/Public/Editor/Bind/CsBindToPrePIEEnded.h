// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"

#include "CsBindToPrePIEEnded.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsBindToPrePIEEnded : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsBindToPrePIEEnded
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void BindToPrePIEEnded(UObject* Object) = 0;
};