// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Payload/Modifier/CsPayload_Projectile_Modifier.h"
#include "Reset/CsReset.h"
// Projectile
#include "Modifier/CsAllocated_ProjectileModifier.h"

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
			/**
			* 
			*/
			struct CSPRJ_API FImplSlice : public IModifier,
										  public ICsReset
			{
			public:

				static const FName Name;

			#define ModifierType NCsProjectile::NModifier::IModifier
			#define AllocatedModifierType NCsProjectile::NModifier::FAllocated

			private:

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

			public:

				// IModifier

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

				void CopyFromModifiers(const UObject* WorldContext, const TArray<ModifierType*>& FromModifiers);
				void CopyFromModifiers(const UObject* WorldContext, const TArray<AllocatedModifierType>& FromModifiers);

				FORCEINLINE void SetModifiers(const TArray<ModifierType*>& InModifiers)
				{
					Modifiers.Reset(FMath::Max(Modifiers.Max(), InModifiers.Num()));

					for (ModifierType* Modifier : InModifiers)
					{
						Modifiers.Add(Modifier);
					}
				}

				void TransferFromModifiers(TArray<AllocatedModifierType>& FromModifiers);

			// IModifier
			#pragma region
			public:

				FORCEINLINE const TArray<ModifierType*>& GetModifiers() const { return Modifiers; }

			#pragma endregion IModifier

			// ICsReset
			#pragma region
			public:

				void Reset();

			#pragma endregion ICsReset

			public:

				FORCEINLINE static void Deconstruct(void* Ptr)
				{
					delete static_cast<NCsProjectile::NPayload::NModifier::FImplSlice*>(Ptr);
				}

			#undef ModifierType
			#undef AllocatedModifierType
			};
		}
	}
}