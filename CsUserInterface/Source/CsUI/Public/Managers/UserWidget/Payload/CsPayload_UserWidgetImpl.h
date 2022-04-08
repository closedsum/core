// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Managers/UserWidget/Payload/CsPayload_UserWidget.h"

class UObject;
struct FCsInterfaceMap;

namespace NCsUserWidget
{
	namespace NPayload
	{
	#define PooledPayloadType NCsPooledObject::NPayload::IPayload
	#define WidgetPayloadType NCsUserWidget::NPayload::IPayload

		/**
		*/
		struct CSUI_API FImpl final : public PooledPayloadType,
									  public WidgetPayloadType
		{
		public:

			static const FName Name;

		private:

			FCsInterfaceMap* InterfaceMap;

			bool bAllocated;

		public:

			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)

			NCsPooledObject::EUpdate UpdateType;

			UObject* Instigator;

			UObject* Owner;

			UObject* Parent;
	
			FCsTime Time;

			uint32  PreserveChangesFromDefaultMask;

			// WidgetPayloadType (NCsUserWidget::NPayload::IPayload)

			ESlateVisibility Visibility;

			bool bAddToViewport;

			float RenderScale;

			float LifeTime;

			FVector2D Position;

			int32 ZOrder;

		public:

			FImpl();
			~FImpl();

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

		#pragma endregion ICsGetInterfaceMap

		// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
		#pragma region
		public:

			FORCEINLINE const bool& IsAllocated() const { return bAllocated; }
			FORCEINLINE const NCsPooledObject::EUpdate& GetUpdateType() const { return UpdateType; }
			FORCEINLINE UObject* GetInstigator() const { return Instigator; }
			FORCEINLINE UObject* GetOwner() const { return Owner; }
			FORCEINLINE UObject* GetParent() const { return Parent; }
			FORCEINLINE const FCsTime& GetTime() const { return Time; }
			FORCEINLINE void Allocate() { bAllocated = true; }

			void Reset();

			FORCEINLINE const uint32& GetPreserveChangesFromDefaultMask() const { return PreserveChangesFromDefaultMask; }

		#pragma endregion PooledPayloadType (NCsPooledObject::NPayload::IPayload)

		public:

			template<typename T>
			FORCEINLINE T* GetInstigator() const { return Cast<T>(GetInstigator()); }

			template<typename T>
			FORCEINLINE T* GetOwner() const { return Cast<T>(GetOwner()); }

			template<typename T>
			FORCEINLINE T* GetParent() const { return Cast<T>(GetParent()); }

		// WidgetPayloadType (NCsUserWidget::NPayload::IPayload)
		#pragma region
		public:

			FORCEINLINE const ESlateVisibility& GetVisibility() const { return Visibility; }
			FORCEINLINE const bool& ShouldAddToViewport() const { return bAddToViewport; }
			FORCEINLINE const float& GetRenderScale() const { return RenderScale; }
			FORCEINLINE const float& GetLifeTime() const { return LifeTime; }
			FORCEINLINE const FVector2D& GetPosition() const { return Position; }
			FORCEINLINE const int32& GetZOrder() const { return ZOrder;
			}

		#pragma endregion WidgetPayloadType (NCsUserWidget::NPayload::IPayload)
		};

	#undef PooledPayloadType
	#undef WidgetPayloadType
	}
}