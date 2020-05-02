// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerDigitalAgreement.generated.h"

class UCsManager_DigitalAgreement;

UINTERFACE(Blueprintable)
class CSONLINE_API UCsGetManagerDigitalAgreement : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSONLINE_API ICsGetManagerDigitalAgreement
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_DigitalAgreement* GetManager_DigitalAgreement() const = 0;

	virtual void SetManager_DigitalAgreement(UCsManager_DigitalAgreement* InManager) = 0;
};