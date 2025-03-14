// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Payload/CsPayload_Weapon.h"

class UObject;
struct FCsInterfaceMap;

namespace NCsWeapon
{
	namespace NPayload
	{
		namespace NImpl
		{
			using PooledPayloadType = NCsPooledObject::NPayload::IPayload;
			using PayloadType = NCsWeapon::NPayload::IPayload;

			struct CSWP_API FImpl : public PooledPayloadType,
									public PayloadType
			{
			public:

				static const FName Name;

			private:

				// ICsGetInterfaceMap
				FCsInterfaceMap* InterfaceMap;

				// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
				bool bAllocated;

			public:

				NCsPooledObject::EUpdate UpdateType;

				UObject* Instigator;

				UObject* Owner;

				UObject* Parent;

				FCsTime Time;

				uint32 PreserveChangesFromDefaultMask;

				// PayloadType (NCsWeapon::NPayload::IPayload)

				FECsWeapon Type;

				FECsUpdateGroup UpdateGroup;

				FTransform Transform;

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

			// PayloadType (NCsWeapon::NPayload::IPayload)
			#pragma region
			public:

				FORCEINLINE const FECsWeapon& GetType() const { return Type; }
				FORCEINLINE const FECsUpdateGroup& GetUpdateGroup() const { return UpdateGroup; }
				FORCEINLINE const FTransform& GetTransform() const { return Transform; }

			#pragma endregion PayloadType (NCsWeapon::NPayload::IPayload)
			};
		}
	}
}