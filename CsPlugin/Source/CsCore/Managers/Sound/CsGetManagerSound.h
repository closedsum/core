// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerSound.generated.h"

class UCsManager_Sound;

UINTERFACE(Blueprintable)
class CSCORE_API UCsGetManagerSound : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/*
*/
class CSCORE_API ICsGetManagerSound
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Sound* GetManager_Sound() const = 0;

	virtual void SetManager_Sound(UCsManager_Sound* InManager) = 0;
};