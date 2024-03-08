// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/ProgressBar/CsUserWidget_ProgressBarInfo.h"

// Library
#include "Library/CsLibrary_Valid.h"

#define InfoType NCsUserWidget::NProgressBar::FInfo

void FCsUserWidget_ProgressBarInfo::CopyToInfo(InfoType* Info)
{
	CS_COPY_TO_PROXY(Info, FillColorAndOpacity);
}

void FCsUserWidget_ProgressBarInfo::CopyToInfoAsValue(InfoType* Info) const
{
	CS_COPY_TO_PROXY_AS_VALUE(Info, FillColorAndOpacity);
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
