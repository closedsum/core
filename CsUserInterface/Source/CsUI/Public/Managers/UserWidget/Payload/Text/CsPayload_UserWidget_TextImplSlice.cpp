// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/Payload/Text/CsPayload_UserWidget_TextImplSlice.h"

// Types
#include "CsMacro_Interface.h"
// Container
#include "Containers/CsInterfaceMap.h"

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsUserWidget::NPayload::NText::NImpl::NSlice::FSlice);

namespace NCsUserWidget
{
	namespace NPayload
	{
		namespace NText
		{
			namespace NImpl
			{
				namespace NSlice
				{
					FSlice::FSlice() :
						// ICsGetInterfaceMap
						InterfaceMap(nullptr),
						// PayloadType (NCsUserWidget::NPayload::NText::IText)
						Text(),
						Color(),
						OutlineSettings(),
						ShadowSettings()
					{
					}

					void FSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
					{
						checkf(InInterfaceMap, TEXT("NCsUserWidget::NPayload::NText::NImpl::NSlice::FSlice::SetInterfaceMap: InInterfaceMap is NULL."));
						checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("NCsUserWidget::NPayload::NText::NImpl::NSlice::FSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

						InterfaceMap = InInterfaceMap;

						InterfaceMap->Add<PayloadType>(FSlice::Name, static_cast<PayloadType*>(this));
					}

					// ICsReset
					#pragma region

					void FSlice::Reset()
					{
						// PayloadType (NCsUserWidget::NPayload::NText::IText)
						//Text
						Color = FLinearColor::White;
						//OutlineSettings.Reset();
						//ShadowSettings.Reset();
					}

					#pragma endregion ICsReset
				}
			}
		}
	}
}