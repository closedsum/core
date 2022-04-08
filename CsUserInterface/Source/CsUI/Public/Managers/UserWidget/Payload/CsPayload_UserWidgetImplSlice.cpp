// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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
			Position(FVector2D::ZeroVector),
			ZOrder(0)
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
			Position = FVector2D::ZeroVector;
			ZOrder = 0;
		}

		#pragma endregion ICsReset
	}
}