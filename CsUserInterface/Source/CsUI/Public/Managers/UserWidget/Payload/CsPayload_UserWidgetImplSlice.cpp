// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/Payload/CsPayload_UserWidgetImplSlice.h"

// Types
#include "CsMacro_Interface.h"
// Container
#include "Containers/CsInterfaceMap.h"

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsUserWidget::NPayload::NImpl::NSlice::FSlice);

namespace NCsUserWidget
{
	namespace NPayload
	{
		namespace NImpl
		{
			namespace NSlice
			{
				FSlice::FSlice() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// PayloadType (NCsUserWidget::NPayload::IPayload)
					Visibility(ESlateVisibility::SelfHitTestInvisible),
					bAddToViewport(false),
					RenderScale(1.0f),
					LifeTime(0.0f),
					PositionType(NCsUserWidget::EPosition::Screen),
					Position(FVector3f::ZeroVector),
					OffsetType(NCsUserWidget::EPosition::Screen),
					Offset(FVector3f::ZeroVector),
					ZOrder(0),
					bAnimParams(false),
					AnimParams()
				{
				}

				void FSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
				{
					checkf(InInterfaceMap, TEXT("NCsUserWidget::NPayload::NImpl::NSlice::FSlice::SetInterfaceMap: InInterfaceMap is NULL."));
					checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("NCsUserWidget::NPayload::NImpl::NSlice::FSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

					InterfaceMap = InInterfaceMap;

					InterfaceMap->Add<PayloadType>(FSlice::Name, static_cast<PayloadType*>(this));
				}

				// ICsReset
				#pragma region

				void FSlice::Reset()
				{
					// PayloadType (NCsUserWidget::NPayload::IPayload)
					Visibility = ESlateVisibility::SelfHitTestInvisible;
					bAddToViewport = false;
					RenderScale = 1.0f;
					LifeTime = 0.0f;
					PositionType = NCsUserWidget::EPosition::Screen;
					Position = FVector3f::ZeroVector;
					OffsetType = NCsUserWidget::EPosition::Screen;
					Offset = FVector3f::ZeroVector;
					ZOrder = 0;
					bAnimParams = false;
					AnimParams.Reset();
				}

				#pragma endregion ICsReset
			}
		}
	}
}