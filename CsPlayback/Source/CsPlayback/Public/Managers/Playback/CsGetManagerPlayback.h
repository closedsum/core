// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerPlayback.generated.h"

class UCsManager_Playback;

UINTERFACE(Blueprintable)
class CSPLAYBACK_API UCsGetManagerPlayback : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSPLAYBACK_API ICsGetManagerPlayback
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Playback* GetManager_Playback() const = 0;

	virtual void SetManager_Playback(UCsManager_Playback* InManager) = 0;
};