// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/ProgressBar/CsUserWidget_ProgressBarInfo.h"

// Library
#include "Library/CsLibrary_Valid.h"

#define InfoType NCsUserWidget::NProgressBar::FInfo

void FCsUserWidget_ProgressBarInfo::CopyToInfo(InfoType* Info)
{
	Info->SetFillColorAndOpacity(&FillColorAndOpacity);
}

void FCsUserWidget_ProgressBarInfo::CopyToInfoAsValue(InfoType* Info) const
{
	Info->SetFillColorAndOpacity(FillColorAndOpacity);
}

#undef InfoType

bool FCsUserWidget_ProgressBarInfo::IsValidChecked(const FString& Context) const
{
	return true;
}

bool FCsUserWidget_ProgressBarInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	return true;
}

namespace NCsUserWidget
{
	namespace NProgressBar
	{
		bool FInfo::IsValidChecked(const FString& Context) const
		{
			return true;
		}

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
		{
			return true;
		}
	}
}
