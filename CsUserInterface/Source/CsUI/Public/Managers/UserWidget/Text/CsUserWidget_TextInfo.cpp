// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/Text/CsUserWidget_TextInfo.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsUserWidget_TextInfo)

#define InfoType NCsUserWidget::NText::FInfo

void FCsUserWidget_TextInfo::CopyToInfo(InfoType* Info)
{
	CS_COPY_TO_PROXY(Info, Text);
	CS_COPY_PTR_TO_PROXY(Info, Font);
	CS_COPY_TO_PROXY(Info, bMaterial);
	CS_COPY_PTR_TO_PROXY(Info, Material);
	CS_COPY_TO_PROXY(Info, Size);
	CS_COPY_TO_PROXY(Info, RenderScale);
	CS_COPY_TO_PROXY_AS_VALUE(Info, Justification);
	CS_COPY_TO_PROXY(Info, ZOrder);
	CS_COPY_TO_PROXY(Info, Color);
	CS_COPY_SETTINGS_TO_PROXY_PTR(Info, OutlineSettings);
	CS_COPY_SETTINGS_TO_PROXY_PTR(Info, ShadowSettings);
	CS_COPY_TO_PROXY(Info, bAnimParams);
	CS_COPY_PARAMS_TO_PROXY_PTR(Info, AnimParams);
}

void FCsUserWidget_TextInfo::CopyToInfoAsValue(InfoType* Info) const
{
	CS_COPY_TO_PROXY_AS_VALUE(Info, Text);
	CS_COPY_PTR_TO_PROXY_AS_VALUE(Info, Font);
	CS_COPY_TO_PROXY_AS_VALUE(Info, bMaterial);
	CS_COPY_PTR_TO_PROXY_AS_VALUE(Info, Material);
	CS_COPY_TO_PROXY_AS_VALUE(Info, Size);
	CS_COPY_TO_PROXY_AS_VALUE(Info, RenderScale);
	CS_COPY_TO_PROXY_AS_VALUE(Info, Justification);
	CS_COPY_TO_PROXY_AS_VALUE(Info, ZOrder);
	CS_COPY_TO_PROXY_AS_VALUE(Info, Color);
	CS_COPY_SETTINGS_TO_PROXY_PTR_AS_VALUE(Info, OutlineSettings);
	CS_COPY_SETTINGS_TO_PROXY_PTR_AS_VALUE(Info, ShadowSettings);
	CS_COPY_TO_PROXY_AS_VALUE(Info, bAnimParams);
	CS_COPY_PARAMS_TO_PROXY_PTR_AS_VALUE(Info, AnimParams);
}

#undef InfoType

bool FCsUserWidget_TextInfo::IsValidChecked(const FString& Context) const
{
	CS_IS_STRING_EMPTY_CHECKED(Text)
	CS_IS_VALID_CHECKED(Font);

	if (bMaterial)
	{
		CS_IS_VALID_CHECKED(Material);
	}

	CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(Size, 1)
	CS_IS_INT_LESS_THAN_OR_EQUAL_CHECKED(Size, 1000)
	CS_IS_FLOAT_GREATER_THAN_CHECKED(RenderScale, 0.0f)
	CS_IS_VALID_CHECKED(OutlineSettings);
	CS_IS_VALID_CHECKED(ShadowSettings);
	
	if (bAnimParams)
	{
		CS_IS_VALID_CHECKED(AnimParams);
	}
	return true;
}

bool FCsUserWidget_TextInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
{
	CS_IS_STRING_EMPTY(Text)
	CS_IS_VALID(Font)

	if (bMaterial)
	{
		CS_IS_VALID(Material);
	}

	CS_IS_INT_GREATER_THAN_OR_EQUAL(Size, 1)
	CS_IS_INT_LESS_THAN_OR_EQUAL(Size, 1000)
	CS_IS_FLOAT_GREATER_THAN(RenderScale, 0.0f)
	CS_IS_VALID(OutlineSettings)
	CS_IS_VALID(ShadowSettings)

	if (bAnimParams)
	{
		CS_IS_VALID(AnimParams)
	}
	return true;
}

namespace NCsUserWidget
{
	namespace NText
	{
		bool FInfo::IsValidChecked(const FString& Context) const
		{
			CS_IS_STRING_EMPTY_CHECKED(GetText())
			CS_IS_PTR_NULL_CHECKED(GetFont())

			if (GetbMaterial())
			{
				CS_IS_PTR_NULL_CHECKED(GetMaterial())
			}

			CS_IS_INT_GREATER_THAN_OR_EQUAL_CHECKED(GetSize(), 1)
			CS_IS_INT_LESS_THAN_OR_EQUAL_CHECKED(GetSize(), 1000)
			CS_IS_FLOAT_GREATER_THAN_CHECKED(GetRenderScale(), 0.0f)
			CS_IS_VALID_CHECKED(GetOutlineSettings());
			CS_IS_VALID_CHECKED(GetShadowSettings());

			if (GetbAnimParams())
			{
				CS_IS_VALID_CHECKED(GetAnimParams());
			}
			return true;
		}

		bool FInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/) const
		{
			CS_IS_STRING_EMPTY(GetText())
			CS_IS_PTR_NULL(GetFont())

			if (GetbMaterial())
			{
				CS_IS_PTR_NULL(GetMaterial())
			}

			CS_IS_INT_GREATER_THAN_OR_EQUAL(GetSize(), 1)
			CS_IS_INT_LESS_THAN_OR_EQUAL(GetSize(), 1000)
			CS_IS_FLOAT_GREATER_THAN(GetRenderScale(), 0.0f)
			CS_IS_VALID(GetOutlineSettings())
			CS_IS_VALID(GetShadowSettings())

			if (GetbAnimParams())
			{
				CS_IS_VALID(GetAnimParams())
			}
			return true;
		}
	}
}
