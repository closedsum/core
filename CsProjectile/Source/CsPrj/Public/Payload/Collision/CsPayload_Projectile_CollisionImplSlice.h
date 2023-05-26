// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Payload/Collision/CsPayload_Projectile_Collision.h"
#include "Reset/CsReset.h"

class UObject;
struct FCsInterfaceMap;

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NCollision
		{
			/**
			* 
			*/
			struct CSPRJ_API FImplSlice : public ICollision,
										  public ICsReset
			{
			public:

				static const FName Name;

			private:

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

			public:

				TArray<AActor*> IgnoreActorsOnHit;

				TArray<UPrimitiveComponent*> IgnoreComponentsOnHit;

			public:

				FImplSlice();

			public:

				void SetInterfaceMap(FCsInterfaceMap* InInterfaceMap);

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

			#pragma endregion ICsGetInterfaceMap

			// ICollision
			#pragma region
			public:

				FORCEINLINE const TArray<AActor*>& GetIgnoreActorsOnHit() const { return IgnoreActorsOnHit; }
				FORCEINLINE const TArray<UPrimitiveComponent*>& GetIgnoreComponentsOnHit() const { return IgnoreComponentsOnHit; }

			#pragma endregion ICollision

			// ICsReset
			#pragma region
			public:

				void Reset();

			#pragma endregion ICsReset

			public:

				FORCEINLINE static void Deconstruct(void* Ptr)
				{
					delete static_cast<NCsProjectile::NPayload::NCollision::FImplSlice*>(Ptr);
				}
			};
		}
	}
}