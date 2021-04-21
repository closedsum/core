// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "CsGetManagerPlayerProfile.generated.h"

class UCsManager_PlayerProfile;

UINTERFACE(Blueprintable)
class UCsGetManagerPlayerProfile : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsGetManagerPlayerProfile
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual UCsManager_PlayerProfile* GetManager_PlayerProfile() const = 0;

	virtual void SetManager_PlayerProfile(UCsManager_PlayerProfile* InManager) = 0;
};