// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Projectile.h"
// Container
#include "Containers/CsGetInterfaceMap.h"

namespace NCsProjectile
{
	namespace NPayload
	{
		/**
		*/
		struct CSPRJ_API IPayload : public ICsGetInterfaceMap
		{
		public:

			static const FName Name;

		public:

			virtual ~IPayload(){}

			virtual const FECsProjectile& GetType() const = 0;

			virtual const int32& GetGeneration() const = 0;

			virtual const FVector& GetDirection() const = 0;

			virtual const FVector& GetLocation() const = 0;
		};
	}
}

using CsProjectilePayloadType = NCsProjectile::NPayload::IPayload;

// WIP Trait

namespace NCsProjectile
{
	namespace NPayload
	{
		struct CSPRJ_API RPayload final
		{
		public:

			static const FName Name;

		private:

			void* Root;

			const FECsProjectile&(*__GetType)(const void*);
			const FVector&(*__GetDirection)(const void*);
			const FVector&(*__GetLocation)(const void*);

		public:

			RPayload() :
				Root(nullptr),
				__GetType(nullptr),
				__GetDirection(nullptr),
				__GetLocation(nullptr)
			{
			}

			FORCEINLINE void Set__GetType(const FECsProjectile& (*Fn)(const void*)) { __GetType = Fn; }
			FORCEINLINE void Set__GetDirection(const FVector& (*Fn)(const void*)) { __GetDirection = Fn; }
			FORCEINLINE void Set__GetLocation(const FVector& (*Fn)(const void*)) { __GetLocation = Fn; }

			FORCEINLINE const FECsProjectile& GetType() const { check(Root); check(__GetType); return __GetType(Root); }

			FORCEINLINE const FVector& GetDirection() const { check(Root); check(__GetDirection); return __GetDirection(Root); }

			FORCEINLINE const FVector& GetLocation() const { check(Root); check(__GetLocation); return __GetLocation(Root); }
		};

		template<typename T>
		struct CSPRJ_API TCheck
		{
		private:

			const FECsProjectile&(T::*GetType)() const;
			const FVector&(T::*GetDirection)() const;
			const FVector&(T::*GetLocation)() const;

		public:

			TCheck()
			{
				GetType = &T::GetType;
				GetDirection = &T::GetDirection;
				GetLocation = &T::GetLocation;
			}
		};
	}
}