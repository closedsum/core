// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/UserWidget/Payload/CsPayload_UserWidget.h"
#include "Reset/CsReset.h"

#pragma once

class UObject;
struct FCsInterfaceMap;

namespace NCsUserWidget
{
	namespace NPayload
	{
		/**
		* Basic implementation of the interface: NCsUserWidget::NPayload::IPayload.
		*/
		struct CSUI_API FImplSlice : public IPayload,
									 public ICsReset
		{
		public:

			static const FName Name;

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

		public:

			// IPayload

			ESlateVisibility Visibility;

		public:

			FImplSlice();

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
			{
				return InterfaceMap;
			}

		#pragma endregion ICsGetInterfaceMap

		public:

			void SetInterfaceMap(FCsInterfaceMap* InInterfaceMap);

		// IPayload
		#pragma region
		public:

			FORCEINLINE const ESlateVisibility& GetVisibility() const
			{
				return Visibility;
			}

		#pragma endregion IPayload

		// ICsReset
		#pragma region
		public:

			void Reset();

		#pragma endregion ICsReset

		public:

			bool CopyFrom(const FImplSlice* From);
		};
	}
}