// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/UserWidget/Payload/CsPayload_UserWidget.h"
#include "Reset/CsReset.h"

class UObject;
struct FCsInterfaceMap;

namespace NCsUserWidget
{
	namespace NPayload
	{
	#define PayloadType NCsUserWidget::NPayload::IPayload

		/**
		* Basic implementation of the interface: PayloadType (NCsUserWidget::NPayload::IPayload).
		*/
		struct CSUI_API FImplSlice final : public PayloadType,
										   public ICsReset
		{
		public:

			static const FName Name;

		#define AnimParamsType NCsUserWidget::NAnim::NPlay::FParams

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

		public:

			// PayloadType (NCsUserWidget::NPayload::IPayload)

			ESlateVisibility Visibility;

			bool bAddToViewport;

			float RenderScale;

			float LifeTime;

			NCsUserWidget::EPosition PositionType;

			FVector3f Position;

			NCsUserWidget::EPosition OffsetType;

			FVector3f Offset;

			int32 ZOrder;

			bool bAnimParams;

			AnimParamsType AnimParams;

		public:

			FImplSlice();

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

		public:

			void SetInterfaceMap(FCsInterfaceMap* InInterfaceMap);

		// PayloadType (NCsUserWidget::NPayload::IPayload)
		#pragma region
		public:

			FORCEINLINE const ESlateVisibility& GetVisibility() const { return Visibility; }
			FORCEINLINE const bool& ShouldAddToViewport() const { return bAddToViewport; }
			FORCEINLINE const float& GetRenderScale() const { return RenderScale; }
			FORCEINLINE const float& GetLifeTime() const { return LifeTime; }
			FORCEINLINE const NCsUserWidget::EPosition& GetPositionType() const { return PositionType; }
			FORCEINLINE const FVector3f& GetPosition() const { return Position; }
			FORCEINLINE const NCsUserWidget::EPosition& GetOffsetType() const { return OffsetType; }
			FORCEINLINE const FVector3f& GetOffset() const { return Offset; }
			FORCEINLINE const int32& GetZOrder() const { return ZOrder; }
			FORCEINLINE const bool& HasAnimParams() const { return bAnimParams; }
			FORCEINLINE const AnimParamsType& GetAnimParams() const { return AnimParams; }

		#pragma endregion PayloadType (NCsUserWidget::NPayload::IPayload)

		// ICsReset
		#pragma region
		public:

			void Reset();

		#pragma endregion ICsReset

		#undef AnimParamsType
		};

	#undef PayloadType
	}
}