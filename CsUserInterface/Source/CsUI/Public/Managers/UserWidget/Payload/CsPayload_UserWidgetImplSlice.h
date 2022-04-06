// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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
		struct CSUI_API FImplSlice : public PayloadType,
									 public ICsReset
		{
		public:

			static const FName Name;

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

		public:

			// PayloadType (NCsUserWidget::NPayload::IPayload)

			ESlateVisibility Visibility;

			bool bAddToViewport;

			float RenderScale;

			float LifeTime;

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

		#pragma endregion PayloadType (NCsUserWidget::NPayload::IPayload)

		// ICsReset
		#pragma region
		public:

			void Reset();

		#pragma endregion ICsReset
		};

	#undef PayloadType
	}
}