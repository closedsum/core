// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/ProgressBar/CsUserWidget_ProgressBarInfo.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsUserWidget_ProgressBarInfo)

namespace NCsUserWidget_ProgressBarInfo
{
	void FImpl::CopyToInfo(ThisType* This, InfoType* Info)
	{
		CS_THIS_COPY_TO_PROXY(Info, FillColorAndOpacity);
	}

	void FImpl::CopyToInfoAsValue(const ThisType* This, InfoType* Info)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Info, FillColorAndOpacity);
	}
}

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
