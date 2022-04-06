// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Text/CsTypes_UserWidget_Text.h"

// Library
#include "Library/CsLibrary_Valid.h"

// FCsUI_UserWidget_Text_OutlineSettings
#pragma region


#define SettingsType NCsUserWidget::NText::FOutline

void FCsUI_UserWidget_Text_OutlineSettings::CopyToSettings(SettingsType* Settings)
{
	Settings->SetSize(&Size);
	Settings->SetbApplyOutlineToDropShadow(&bApplyOutlineToDropShadow);
	Settings->SetColor(&Color);
}

void FCsUI_UserWidget_Text_OutlineSettings::CopyToSettingsAsValue(SettingsType* Settings) const
{
	Settings->SetSize(Size);
	Settings->SetbApplyOutlineToDropShadow(bApplyOutlineToDropShadow);
	Settings->SetColor(Color);
}

#undef SettingsType

bool FCsUI_UserWidget_Text_OutlineSettings::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsUI_UserWidget_Text_OutlineSettings::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
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

#pragma endregion FCDamage_Text_OutlineSettings

// FCDamage_Text_ShadowSettings
#pragma region


#define SettingsType NCsUserWidget::NText::FShadow

void FCsUI_UserWidget_Text_ShadowSettings::CopyToSettings(SettingsType* Settings)
{
	Settings->SetOffset(&Offset);
	Settings->SetColor(&Color);
}

void FCsUI_UserWidget_Text_ShadowSettings::CopyToSettingsAsValue(SettingsType* Settings) const
{
	Settings->SetOffset(Offset);
	Settings->SetColor(Color);
}

#undef SettingsType

bool FCsUI_UserWidget_Text_ShadowSettings::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsUI_UserWidget_Text_ShadowSettings::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
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

#pragma endregion FCsUI_UserWidget_Text_ShadowSettings