// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/CsSettings_Manager_UserWidget.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Settings
#include "Settings/CsUserInterfaceSettings.h"

bool FCsSettings_Manager_UserWidget_PoolParams::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUserWidgetPooledClass, Class)
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUserWidget, Widget)
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(PoolSize, 4)
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(PayloadSize, 4)
	return true;
}

bool FCsSettings_Manager_UserWidget_PoolParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsUserWidgetPooledClass, FECsUserWidgetPooledClass, Class)
	CS_IS_ENUM_STRUCT_VALID(EMCsUserWidget, FECsUserWidget, Widget)
	CS_IS_INT_GREATER_THAN_OR_EQUAL(PoolSize, 4)
	CS_IS_INT_GREATER_THAN_OR_EQUAL(PayloadSize, 4)
	return true;
}

// FCsSettings_Manager_UserWidget
#pragma region

const FCsSettings_Manager_UserWidget& FCsSettings_Manager_UserWidget::Get()
{
	return GetMutableDefault<UCsUserInterfaceSettings>()->Manager_UserWidget;
}

bool FCsSettings_Manager_UserWidget::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_STRUCT_SET_VALID_CHECKED(EMCsUserWidgetPayload, FECsUserWidgetPayload, PayloadTypes)
	CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUserWidgetPooled, DefaultType)

	for (const TPair<FECsUserWidgetPooled, FCsSettings_Manager_UserWidget_PoolParams>& Pair : PoolParams)
	{
		CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsUserWidgetPooled, Pair.Key)
		CS_IS_VALID_CHECKED(Pair.Value);
	}
	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(SetPositionInViewports_PoolSize, 4)
	return true;
}

bool FCsSettings_Manager_UserWidget::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_SET_VALID(EMCsUserWidgetPayload, FECsUserWidgetPayload, PayloadTypes)
	CS_IS_ENUM_STRUCT_VALID(EMCsUserWidgetPooled, FECsUserWidgetPooled, DefaultType)

	for (const TPair<FECsUserWidgetPooled, FCsSettings_Manager_UserWidget_PoolParams>& Pair : PoolParams)
	{
		CS_IS_ENUM_STRUCT_VALID(EMCsUserWidgetPooled, FECsUserWidgetPooled, Pair.Key)
		CS_IS_VALID(Pair.Value)
	}
	CS_IS_INT_GREATER_THAN_OR_EQUAL(SetPositionInViewports_PoolSize, 4)
	return true;
}

#pragma endregion FCsSettings_Manager_UserWidget