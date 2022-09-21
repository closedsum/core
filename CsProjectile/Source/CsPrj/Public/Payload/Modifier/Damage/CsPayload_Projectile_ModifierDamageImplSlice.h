// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Payload/Modifier/Damage/CsPayload_Projectile_ModifierDamage.h"
#include "Reset/CsReset.h"
// Damage
#include "Modifier/CsAllocated_DamageModifier.h"

class UObject;
struct FCsInterfaceMap;

// NCsDamage::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, IModifier)

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NModifier
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

				#define DmgModifierType NCsDamage::NModifier::IModifier
				#define AllocatedDmgModifierType NCsDamage::NModifier::FAllocated

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

				public:

					// IDamage

					TArray<DmgModifierType*> Modifiers;

					TArray<AllocatedDmgModifierType> Modifiers_Internal;

				public:

					FImplSlice();

				public:

					void SetInterfaceMap(FCsInterfaceMap* InInterfaceMap);

				// ICsGetInterfaceMap
				#pragma region
				public:

					FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

				#pragma endregion ICsGetInterfaceMap

				public:

					void CopyFromModifiers(const UObject* WorldContext, const TArray<DmgModifierType*>& FromModifiers);
					void CopyFromModifiers(const UObject* WorldContext, const TArray<AllocatedDmgModifierType>& FromModifiers);

					FORCEINLINE void SetModifiers(const TArray<DmgModifierType*>& InModifiers)
					{
						Modifiers.Reset(FMath::Max(Modifiers.Max(), InModifiers.Num()));

						for (DmgModifierType* Modifier : InModifiers)
						{
							Modifiers.Add(Modifier);
						}
					}

					void TransferFromModifiers(TArray<AllocatedDmgModifierType>& FromModifiers);

				// IDamage
				#pragma region
				public:

					FORCEINLINE const TArray<DmgModifierType*>& GetDamageModifiers() const { return Modifiers; }

				#pragma endregion IDamage

				// ICsReset
				#pragma region
				public:

					void Reset();

				#pragma endregion ICsReset

				public:

					bool CopyFrom(const FImplSlice* From);

					FORCEINLINE static void Deconstruct(void* Ptr)
					{
						delete static_cast<NCsProjectile::NPayload::NModifier::NDamage::FImplSlice*>(Ptr);
					}

				#undef DmgModifierType
				#undef AllocatedDmgModifierType
				};
			}
		}
	}
}