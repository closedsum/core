// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Payload/Damage/CsPayload_Projectile_Damage.h"
#include "Reset/CsReset.h"

class UObject;
struct FCsInterfaceMap;

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NDamage
		{
			/**
			* 
			*/
			struct CSPRJ_API FImplSlice : public IDamage,
										  public ICsReset
			{
			public:

				static const FName Name;

			private:

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

			public:

				// IDamage

				TArray<FECsDamageData> DataTypes;

			public:

				FImplSlice();

			public:

				void SetInterfaceMap(FCsInterfaceMap* InInterfaceMap);

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

			#pragma endregion ICsGetInterfaceMap

			// IDamage
			#pragma region
			public:

				FORCEINLINE const TArray<FECsDamageData>& GetDamageDataTypes() const { return DataTypes; }

			#pragma endregion IDamage

			// ICsReset
			#pragma region
			public:

				void Reset();

			#pragma endregion ICsReset

			public:

				FORCEINLINE void CopyAndEmpty(TArray<FECsDamageData>& FromTypes)
				{
					DataTypes.Reset(FMath::Max(FromTypes.Num(), DataTypes.Max()));

					const int32 Count = FromTypes.Num();

					for (int32 I = Count - 1; I >= 0; --I)
					{
						const FECsDamageData& Type = FromTypes[I];

						DataTypes.Add(Type);
						FromTypes.RemoveAt(I, 1, false);
					}
				}

				FORCEINLINE static void Deconstruct(void* Ptr)
				{
					delete static_cast<NCsProjectile::NPayload::NDamage::FImplSlice*>(Ptr);
				}
			};
		}
	}
}