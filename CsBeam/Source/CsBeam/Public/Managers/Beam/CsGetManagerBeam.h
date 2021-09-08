// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerBeam.generated.h"

class UCsManager_Beam;

UINTERFACE(Blueprintable)
class CSBEAM_API UCsGetManagerBeam : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSBEAM_API ICsGetManagerBeam
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_Beam* GetManager_Beam() const = 0;

	virtual void SetManager_Beam(UCsManager_Beam* InManager) = 0;
};