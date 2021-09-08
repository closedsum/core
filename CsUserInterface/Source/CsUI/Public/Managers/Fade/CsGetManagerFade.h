// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerFade.generated.h"

class UCsManager_Fade;

UINTERFACE(Blueprintable)
class CSUI_API UCsGetManagerFade : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSUI_API ICsGetManagerFade
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Fade* GetManager_Fade() const = 0;

	virtual void SetManager_Fade(UCsManager_Fade* InManager) = 0;
};