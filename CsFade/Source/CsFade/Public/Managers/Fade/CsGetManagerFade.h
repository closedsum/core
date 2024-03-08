// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Interface.h"

#include "CsGetManagerFade.generated.h"

class UCsManager_Fade;

UINTERFACE(Blueprintable)
class CSFADE_API UCsGetManagerFade : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSFADE_API ICsGetManagerFade
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Fade* GetManager_Fade() const = 0;

	virtual void SetManager_Fade(UCsManager_Fade* InManager) = 0;
};