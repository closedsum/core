// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_Projectile.h"
#include "Reset/CsReset.h"

#pragma once

class UObject;
struct FCsInterfaceMap;

namespace NCsProjectile
{
	namespace NPayload
	{
		/**
		* Basic implementation of the interface: NCsProjectile::NPayload::IPayload.
		*/
		struct CSPRJ_API FImplSlice : public IPayload,
									  public ICsReset
		{
		public:

			static const FName Name;

		private:

			// ICsGetInterfaceMap

			FCsInterfaceMap* InterfaceMap;

		public:

			// ICsPayload_Projectile

			FVector Direction;

			FVector Location;
		public:

			FImplSlice();
			~FImplSlice(){}

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

			FORCEINLINE const FVector& GetDirection() const
			{
				return Direction;
			}

			FORCEINLINE const FVector& GetLocation() const
			{
				return Location;
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