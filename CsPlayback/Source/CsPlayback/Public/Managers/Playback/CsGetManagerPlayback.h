// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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