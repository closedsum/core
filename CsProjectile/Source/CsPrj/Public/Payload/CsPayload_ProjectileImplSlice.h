// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Projectile
#include "Payload/CsPayload_Projectile.h"
// Reset
#include "Reset/CsReset.h"

class UObject;
struct FCsInterfaceMap;

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NImplSlice
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

				FECsProjectile Type;

				int32 Generation;

				FVector Direction;

				FVector Location;

			public:

				FImplSlice();
				~FImplSlice(){}

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

			#pragma endregion ICsGetInterfaceMap

			public:

				void SetInterfaceMap(FCsInterfaceMap* InInterfaceMap);

			// IPayload
			#pragma region
			public:

				FORCEINLINE const FECsProjectile& GetType() const { return Type; }
				FORCEINLINE const int32& GetGeneration() const { return Generation; }
				FORCEINLINE const FVector& GetDirection() const { return Direction; }
				FORCEINLINE const FVector& GetLocation() const { return Location; }

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
}