// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Payload/Modifier/Damage/CsPayload_Projectile_ModifierDamage.h"
#include "Reset/CsReset.h"
// Types
#include "CsMacro_Cached.h"
// Damage
#include "Modifier/CsAllocated_DamageModifier.h"

class UObject;
struct FCsInterfaceMap;

// ModifierType (NCsDamage::NModifier::IModifier)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, IModifier)

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_4(NCsProjectile, NPayload, NModifier, NDamage, FImplSlice)

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

				private:

					CS_USING_CACHED_FUNCTION_NAME_NESTED_4(NCsProjectile, NPayload, NModifier, NDamage, FImplSlice);

					using ThisType = NCsProjectile::NPayload::NModifier::NDamage::FImplSlice;
					using ModifierType = NCsDamage::NModifier::IModifier;
					using AllocatedModifierType = NCsDamage::NModifier::FAllocated;

				private:

					// ICsGetInterfaceMap

					FCsInterfaceMap* InterfaceMap;

				public:

					// IDamage

					TArray<ModifierType*> Modifiers;

					TArray<AllocatedModifierType> Modifiers_Internal;

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

					void CopyFromModifiers(const UObject* WorldContext, const TArray<ModifierType*>& FromModifiers);
					void CopyAndEmptyFromModifiers(const UObject* WorldContext, TArray<ModifierType*>& FromModifiers);
					void CopyFromModifiers(const UObject* WorldContext, const TArray<AllocatedModifierType>& FromModifiers);

					void AddAndEmptyFromModifiers(TArray<ModifierType*>& FromModifiers);

					FORCEINLINE void SetModifiers(const TArray<ModifierType*>& InModifiers)
					{
						Modifiers.Reset(FMath::Max(Modifiers.Max(), InModifiers.Num()));

						for (ModifierType* Modifier : InModifiers)
						{
							Modifiers.Add(Modifier);
						}
					}

					void TransferFromModifiers(TArray<AllocatedModifierType>& FromModifiers);

				// IDamage
				#pragma region
				public:

					FORCEINLINE const TArray<ModifierType*>& GetDamageModifiers() const { return Modifiers; }

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
						delete static_cast<ThisType*>(Ptr);
					}
				};
			}
		}
	}
}