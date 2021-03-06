// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Payload/CsPayload_Projectile.h"

#pragma once

class UObject;
struct FCsInterfaceMap;

namespace NCsProjectile
{
	namespace NPayload
	{
	#define PooledPayloadType NCsPooledObject::NPayload::IPayload
	#define ProjectilePayloadType NCsProjectile::NPayload::IPayload

		/**
		* Basic implementation of the interfaces: 
		*  PooledPayloadType (NCsPooledObject::NPayload::IPayload)
		*  ProjectilePayloadType (NCsProjectile::NPayload::IPayload)
		*/
		struct CSPRJ_API FImplPooled : public PooledPayloadType,
									   public ProjectilePayloadType
		{
		public:

			static const FName Name;

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)

			bool bAllocated;

		public:

			UObject* Instigator;

			UObject* Owner;

			UObject* Parent;
	
			FCsTime Time;

			uint32 PreserveChangesFromDefaultMask;

			// ProjectilePayloadType (NCsProjectile::NPayload::IPayload)

			FVector Direction;

			FVector Location;

		public:

			FImplPooled();
			~FImplPooled();

		// ICsGetInterfaceMap
		#pragma region
		public:

			FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
			{
				return InterfaceMap;
			}

		#pragma endregion ICsGetInterfaceMap

		// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
		#pragma region
		public:

			FORCEINLINE const bool& IsAllocated() const { return bAllocated; }
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

		// ProjectilePayloadType (NCsProjectile::NPayload::IPayload)
		#pragma region
		public:

			FORCEINLINE const FVector& GetDirection() const { return Direction; }
			FORCEINLINE const FVector& GetLocation() const { return Location; }

		#pragma endregion ProjectilePayloadType (NCsProjectile::NPayload::IPayload)
		};

	#undef PooledPayloadType
	#undef ProjectilePayloadType
	}
}