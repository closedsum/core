// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetBlockchain.generated.h"

class UCsBlockchain;

UINTERFACE(Blueprintable)
class UCsGetBlockchain : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsGetBlockchain
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsBlockchain* GetBlockchain() = 0;

	virtual void SetBlockchain(UCsBlockchain* InBlockchain) = 0;
};