// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Managers/WidgetActor/Payload/CsPayload_WidgetActor.h"
#include "Managers/WidgetActor/Payload/CsPayload_WidgetActorUserWidget.h"
// Types
#include "Managers/UserWidget/CsTypes_UserWidget.h"

class UObject;
struct FCsInterfaceMap;
class UUserWidget;

// NCsUserWidget::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsUserWidget, NPayload, IPayload)

namespace NCsWidgetActor
{
	namespace NPayload
	{
		namespace NImpl
		{
			using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
			using WidgetPayloadType = NCsWidgetActor::NPayload::IPayload;
			using UserWidgetType = NCsWidgetActor::NPayload::IUserWidget;

			/**
			*/
			struct CSUI_API FImpl final : public PooledPayloadType,
										  public WidgetPayloadType,
										  public UserWidgetType
			{
			public:

				static const FName Name;

			private:

				using UserWidgetPayloadType = NCsUserWidget::NPayload::IPayload;

				FCsInterfaceMap* InterfaceMap;

				bool bAllocated;

			public:

				// PooledPayloadType (NCsPooledObject::NPayload::IPayload)

				NCsPooledObject::EUpdate UpdateType;

				UObject* Instigator;

				UObject* Owner;

				UObject* Parent;
	
				FCsTime Time;

				uint32 PreserveChangesFromDefaultMask;

				// WidgetPayloadType (NCsWidgetActor::NPayload::IPayload)

				UUserWidget* UserWidget;

				ECsWidgetActorDeallocateMethod DeallocateMethod;

				float LifeTime;
	
				FAttachmentTransformRules AttachmentTransformRules;

				FName Bone;

				int32 TransformRules;

				FTransform3f Transform;

				// UserWidgetType (NCsWidgetActor::NPayload::IUserWidget)

				FECsUserWidgetPooled UserWidgetPooledType;

				UserWidgetPayloadType* UserWidgetPayload;

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

			// WidgetPayloadType (NCsWidgetActor::NPayload::IPayload)
			#pragma region
			public:

				FORCEINLINE UUserWidget* GetUserWidget() const { return UserWidget; }
				FORCEINLINE const ECsWidgetActorDeallocateMethod& GetDeallocateMethod() const { return DeallocateMethod; }
				FORCEINLINE const float& GetLifeTime() const { return LifeTime; }
				FORCEINLINE const FAttachmentTransformRules& GetAttachmentTransformRule() const { return AttachmentTransformRules; }
				FORCEINLINE const FName& GetBone() const { return Bone; }
				FORCEINLINE const int32& GetTransformRules() const { return TransformRules; }
				FORCEINLINE const FTransform3f& GetTransform() const { return Transform; }

			#pragma endregion WidgetPayloadType (NCsWidgetActor::NPayload::IPayload)

			// UserWidgetType (NCsWidgetActor::NPayload::IUserWidget)
			#pragma region
			public:

				FORCEINLINE const FECsUserWidgetPooled& GetUserWidgetPooledType() const { return UserWidgetPooledType; }
				FORCEINLINE UserWidgetPayloadType* GetUserWidgetPayload() const { return UserWidgetPayload; }

			#pragma endregion UserWidgetType (NCsWidgetActor::NPayload::IUserWidget)
			};
		}
	}
}