// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/CsSettings_Manager_UserWidget.h"

// Settings
#include "Settings/CsUserInterfaceSettings.h"

// FCsSettings_Manager_UserWidget
#pragma region

const FCsSettings_Manager_UserWidget& FCsSettings_Manager_UserWidget::Get()
{
	return GetMutableDefault<UCsUserInterfaceSettings>()->Manager_UserWidget;
}

#pragma endregion FCsSettings_Manager_UserWidget