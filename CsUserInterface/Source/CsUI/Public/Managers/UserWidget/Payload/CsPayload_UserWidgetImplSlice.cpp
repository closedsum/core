// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/Payload/CsPayload_UserWidgetImplSlice.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsUserWidget::NPayload::FImplSlice::Name = FName("NCsUserWidget::NPayload::FImplSlice");;

namespace NCsUserWidget
{
	namespace NPayload
	{
		FImplSlice::FImplSlice() :
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

		void FImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
		{
			checkf(InInterfaceMap, TEXT("NCsUserWidget::NPayload::FImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));

			checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("NCsUserWidget::NPayload::FImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

			InterfaceMap = InInterfaceMap;

			InterfaceMap->Add<IPayload>(FImplSlice::Name, static_cast<IPayload*>(this));
		}

		// ICsReset
		#pragma region

		void FImplSlice::Reset()
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