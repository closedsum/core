// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Payload/Modifier/CsPayload_Projectile_Modifier.h"
#include "Reset/CsReset.h"
// Types
#include "CsMacro_Cached.h"
// Projectile
#include "Modifier/CsAllocated_ProjectileModifier.h"

class UObject;
struct FCsInterfaceMap;

// ModifierType (NCsProjectile::NModifier::IModifier)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NModifier, IModifier)

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_3(NCsProjectile, NPayload, NModifier, ImplSlice)

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

			private:
			
				using ThisType = NCsProjectile::NPayload::NModifier::FImplSlice;
				using ModifierType = NCsProjectile::NModifier::IModifier;
				using AllocatedModifierType = NCsProjectile::NModifier::FAllocated;

				CS_USING_CACHED_FUNCTION_NAME_NESTED_3(NCsProjectile, NPayload, NModifier, ImplSlice);

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
				void CopyAndEmptyFromModifiers(const UObject* WorldContext, TArray<ModifierType*>& FromModifiers);
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
					delete static_cast<ThisType*>(Ptr);
				}
			};
		}
	}
}