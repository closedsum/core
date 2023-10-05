// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/Payload/Text/CsPayload_UserWidget_TextImplSlice.h"

// Container
#include "Containers/CsInterfaceMap.h"

const FName NCsUserWidget::NPayload::NText::FImplSlice::Name = FName("NCsUserWidget::NPayload::NText::FImplSlice");;

namespace NCsUserWidget
{
	namespace NPayload
	{
		namespace NText
		{
			FImplSlice::FImplSlice() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				// PayloadType (NCsUserWidget::NPayload::NText::IText)
				Text(),
				Color(),
				OutlineSettings(),
				ShadowSettings()
			{
			}

			void FImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
			{
				checkf(InInterfaceMap, TEXT("NCsUserWidget::NPayload::NText::FImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));

				checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("NCsUserWidget::NPayload::NText::FImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

				InterfaceMap = InInterfaceMap;

				InterfaceMap->Add<IText>(FImplSlice::Name, static_cast<IText*>(this));
			}

			// ICsReset
			#pragma region

			void FImplSlice::Reset()
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