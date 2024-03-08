// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/Image/CsUserWidget_ImageInfo.h"

// Library
#include "Library/CsLibrary_Valid.h"

#define InfoType NCsUserWidget::NImage::FInfo

void FCsUserWidget_ImageInfo::CopyToInfo(InfoType* Info)
{
	CS_COPY_PTR_TO_PROXY(Info, Image);
	CS_COPY_TO_PROXY(Info, RenderScale);
	CS_COPY_TO_PROXY(Info, ZOrder);
}

void FCsUserWidget_ImageInfo::CopyToInfoAsValue(InfoType* Info) const
{
	CS_COPY_PTR_TO_PROXY_AS_VALUE(Info, Image);
	CS_COPY_TO_PROXY_AS_VALUE(Info, RenderScale);
	CS_COPY_TO_PROXY_AS_VALUE(Info, ZOrder);
}

#undef InfoType

bool FCsUserWidget_ImageInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Image);
	CS_IS_FLOAT_GREATER_THAN_CHECKED(RenderScale, 0.0f)
	return true;
}

bool FCsUserWidget_ImageInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	CS_IS_VALID(Image)
	CS_IS_FLOAT_GREATER_THAN(RenderScale, 0.0f)
	return true;
}

namespace NCsUserWidget
{
	namespace NImage
	{
		bool FInfo::IsValidChecked(const FString& Context) const
		{
			CS_IS_PTR_NULL_CHECKED(GetImage())
			CS_IS_FLOAT_GREATER_THAN_CHECKED(GetRenderScale(), 0.0f)
			return true;
		}

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
		{
			CS_IS_PTR_NULL(GetImage())
			CS_IS_FLOAT_GREATER_THAN(GetRenderScale(), 0.0f)
			return true;
		}
	}
}
