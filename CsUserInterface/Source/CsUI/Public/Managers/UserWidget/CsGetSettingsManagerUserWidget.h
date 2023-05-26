// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "UObject/Interface.h"
// Types
#include "Managers/UserWidget/CsSettings_Manager_UserWidget.h"

#include "CsGetSettingsManagerUserWidget.generated.h"

UINTERFACE(Blueprintable)
class CSUI_API UCsGetSettingsManagerUserWidget : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSUI_API ICsGetSettingsManagerUserWidget
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*/
	virtual const FCsSettings_Manager_UserWidget& GetSettingsManagerUserWidget() const = 0;
};