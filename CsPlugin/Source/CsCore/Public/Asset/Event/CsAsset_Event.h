// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Interfaces
#include "UObject/Interface.h"
// Types
#include "Asset/Event/CsAsset_Event_Delegates.h"

#include "CsAsset_Event.generated.h"

UINTERFACE(Blueprintable)
class CSCORE_API UCsAsset_Event : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSCORE_API ICsAsset_Event
{
	GENERATED_IINTERFACE_BODY()

public:


	virtual NCsAsset::FOnOpenedInEditor& GetAsset_OpenedInEditor_Event() = 0;
	virtual NCsAsset::FOnUniqueOpenedInEditor& GetAsset_UniqueOpenedInEditor_Event() = 0;
	virtual NCsAsset::FOnRequest_Close& GetAssetEditor_OnRequest_Close_Event() = 0;
	virtual FCsAssetEditor_OnRequest_Close& GetAssetEditor_OnRequest_Close_ScriptEvent() = 0;
};