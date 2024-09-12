// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/Text/CsTypes_UserWidget_Text.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_UserWidget_Text)

// FCsUserWidget_Text_OutlineSettings
#pragma region

#define SettingsType NCsUserWidget::NText::FOutline

void FCsUserWidget_Text_OutlineSettings::CopyToSettings(SettingsType* Settings)
{
	CS_COPY_TO_PROXY(Settings, Size);
	CS_COPY_TO_PROXY(Settings, bApplyOutlineToDropShadow);
	CS_COPY_TO_PROXY(Settings, Color);
}

void FCsUserWidget_Text_OutlineSettings::CopyToSettingsAsValue(SettingsType* Settings) const
{
	CS_COPY_TO_PROXY_AS_VALUE(Settings, Size);
	CS_COPY_TO_PROXY_AS_VALUE(Settings, bApplyOutlineToDropShadow);
	CS_COPY_TO_PROXY_AS_VALUE(Settings, Color);
}

#undef SettingsType

bool FCsUserWidget_Text_OutlineSettings::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsUserWidget_Text_OutlineSettings::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	return true;
}

namespace NCsUserWidget
{
	namespace NText
	{
		bool FOutline::IsValidChecked(const FString& Context) const
		{
			return true;
		}

		bool FOutline::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
		{
			return true;
		}
	}
}

#pragma endregion FCsUserWidget_Text_OutlineSettings

// FCsUserWidget_Text_ShadowSettings
#pragma region

#define SettingsType NCsUserWidget::NText::FShadow

void FCsUserWidget_Text_ShadowSettings::CopyToSettings(SettingsType* Settings)
{
	CS_COPY_TO_PROXY(Settings, Offset);
	CS_COPY_TO_PROXY(Settings, Color);
}

void FCsUserWidget_Text_ShadowSettings::CopyToSettingsAsValue(SettingsType* Settings) const
{
	CS_COPY_TO_PROXY_AS_VALUE(Settings, Offset);
	CS_COPY_TO_PROXY_AS_VALUE(Settings, Color);
}

#undef SettingsType

bool FCsUserWidget_Text_ShadowSettings::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsUserWidget_Text_ShadowSettings::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	return true;
}

namespace NCsUserWidget
{
	namespace NText
	{
		bool FShadow::IsValidChecked(const FString& Context) const
		{
			return true;
		}

		bool FShadow::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
		{
			return true;
		}
	}
}

#pragma endregion FCsUserWidget_Text_ShadowSettings