// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
#include "Payload/CsPayload_Weapon.h"

#pragma once

class UObject;
struct FCsInterfaceMap;

namespace NCsWeapon
{
	namespace NPayload
	{
		struct CSWP_API FImplPooled : public NCsPooledObject::NPayload::IPayload,
									  public NCsWeapon::NPayload::IPayload
		{
		private:

			FCsInterfaceMap* InterfaceMap;

			bool bAllocated;

		public:

			UObject* Instigator;

			UObject* Owner;

			UObject* Parent;

			FCsTime Time;

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

		// NCsWeapon::NPayload::IPayload
		#pragma region
		public:

		#pragma endregion NCsWeapon::NPayload::IPayload
		};
	}
}