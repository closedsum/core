// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Managers/UserWidget/Payload/CsPayload_UserWidget.h"

#pragma once

class UObject;
struct FCsInterfaceMap;

namespace NCsUserWidget
{
	namespace NPayload
	{
		/**
		*/
		struct CSUI_API FImpl final : public NCsPooledObject::NPayload::IPayload,
									  public NCsUserWidget::NPayload::IPayload
		{
		public:

			static const FName Name;

		private:

			FCsInterfaceMap* InterfaceMap;

			bool bAllocated;

		public:

			// NCsPooledObject::NPayload::IPayload

			UObject* Instigator;

			UObject* Owner;

			UObject* Parent;
	
			FCsTime Time;

			// NCsUserWidget::NPayload::IPayload

			ESlateVisibility Visibility;

		public:

			FImpl();
			~FImpl();

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
			{
				return InterfaceMap;
			}

		#pragma endregion ICsGetInterfaceMap

		// NCsPooledObject::NPayload::IPayload
		#pragma region
		public:

			FORCEINLINE const bool& IsAllocated() const
			{
				return bAllocated;
			}

			FORCEINLINE UObject* GetInstigator() const
			{
				return Instigator;
			}

			FORCEINLINE UObject* GetOwner() const
			{
				return Owner;
			}

			FORCEINLINE UObject* GetParent() const
			{
				return Parent;
			}

			FORCEINLINE const FCsTime& GetTime() const
			{
				return Time;
			}

			FORCEINLINE void Allocate()
			{
				bAllocated = true;
			}

			void Reset();

		#pragma endregion NCsPooledObject::NPayload::IPayload

		public:

			template<typename T>
			FORCEINLINE T* GetInstigator() const
			{
				return Cast<T>(GetInstigator());
			}

			template<typename T>
			FORCEINLINE T* GetOwner() const
			{
				return Cast<T>(GetOwner());
			}

			template<typename T>
			FORCEINLINE T* GetParent() const
			{
				return Cast<T>(GetParent());
			}

		// NCsUserWidget::NPayload::IPayload
		#pragma region
		public:

			FORCEINLINE const ESlateVisibility& GetVisibility() const
			{
				return Visibility;
			}

		#pragma endregion NCsUserWidget::NPayload::IPayload
		};
	}
}