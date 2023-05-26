// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
// Play
#include "Play/Mode/CsPlayMode.h"

#include "CsGetPlayMode.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetPlayMode : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsGetPlayMode
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual const ECsPlayMode& GetPlayMode() const = 0;
};