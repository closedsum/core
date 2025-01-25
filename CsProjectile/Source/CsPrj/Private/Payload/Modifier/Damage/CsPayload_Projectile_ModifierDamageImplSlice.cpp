// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/Modifier/Damage/CsPayload_Projectile_ModifierDamageImplSlice.h"

// Types
#include "CsMacro_Interface.h"
#include "CsMacro_Misc.h"
// Library
#include "Managers/Damage/CsLibrary_Manager_Damage.h"
#include "Library/CsLibrary_Array.h"
#include "Library/CsLibrary_Valid.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Modifier/CsResource_DamageModifier.h"

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsProjectile::NPayload::NModifier::NDamage::FImplSlice);

// Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME_NESTED_4(NCsProjectile, NPayload, NModifier, NDamage, FImplSlice)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsProjectile::NPayload::NModifier::NDamage::FImplSlice, SetInterfaceMap)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsProjectile::NPayload::NModifier::NDamage::FImplSlice, CopyFromModifiers)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsProjectile::NPayload::NModifier::NDamage::FImplSlice, CopyAndEmptyFromModifiers)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsProjectile::NPayload::NModifier::NDamage::FImplSlice, TransferFromModifiers)
CS_END_CACHED_FUNCTION_NAME_NESTED_4

#pragma endregion Cached


namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NModifier
		{
			namespace NDamage
			{
				using ModifierLibrary = NCsDamage::NManager::NModifier::FLibrary;
				using ModifierType = NCsDamage::NModifier::IModifier;
				using AllocatedModifierType = NCsDamage::NModifier::FAllocated;

				FImplSlice::FImplSlice() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// IDamage
					Modifiers(),
					Modifiers_Internal()
				{
				}

				void FImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
				{
					CS_SET_CONTEXT_AS_FUNCTION_NAME(SetInterfaceMap);

					CS_IS_PTR_NULL_CHECKED(InInterfaceMap)

					checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("NCsProjectile::NPayload::NModifier::NDamage::FImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

					InterfaceMap = InInterfaceMap;

					InterfaceMap->Add<IDamage>(FImplSlice::Name, static_cast<IDamage*>(this));
				}

				// ICsReset
				#pragma region

				void FImplSlice::Reset()
				{	
					Modifiers_Internal.Reset(Modifiers_Internal.Max());
					Modifiers.Reset(Modifiers.Max());
				}

				#pragma endregion ICsReset

				void FImplSlice::CopyFromModifiers(const UObject* WorldContext, const TArray<ModifierType*>& FromModifiers)
				{
					CS_SET_CONTEXT_AS_FUNCTION_NAME(CopyFromModifiers);

					CS_IS_TARRAY_ANY_NULL_CHECKED(FromModifiers, ModifierType)

					checkf(Modifiers_Internal.Num() == CS_EMPTY, TEXT("%s: Modifiers_Internal is already populated."), *Context);

					Modifiers.Reset(FMath::Max(Modifiers.Max(), FromModifiers.Num()));
					Modifiers_Internal.Reset(FMath::Max(Modifiers_Internal.Max(), FromModifiers.Num()));
				
					for (ModifierType* Modifier : FromModifiers)
					{
						AllocatedModifierType& Allocated = Modifiers_Internal.AddDefaulted_GetRef();
						Allocated.Root					 = CsDamageManagerLibrary::GetContextRootChecked(Context, WorldContext);

						ModifierLibrary::CopyChecked(Context, WorldContext, Modifier, Allocated.Container, Allocated.Type);
					
						Allocated.Modifier = Allocated.Container->Get();

						Modifiers.Add(Allocated.Modifier);
					}
				}

				void FImplSlice::CopyAndEmptyFromModifiers(const UObject* WorldContext, TArray<ModifierType*>& FromModifiers)
				{
					CS_SET_CONTEXT_AS_FUNCTION_NAME(CopyAndEmptyFromModifiers);

					CS_IS_TARRAY_ANY_NULL_CHECKED(FromModifiers, ModifierType)

					checkf(Modifiers_Internal.Num() == CS_EMPTY, TEXT("%s: Modifiers_Internal is already populated."), *Context);

					const int32 Count = FromModifiers.Num();

					Modifiers.Reset(FMath::Max(Modifiers.Max(), Count));
					Modifiers_Internal.Reset(FMath::Max(Modifiers_Internal.Max(), Count));
				
					for (int32 I = Count - 1; I >= 0; --I)
					{
						ModifierType* Modifier			 = FromModifiers[I];
						AllocatedModifierType& Allocated = Modifiers_Internal.AddDefaulted_GetRef();
						Allocated.Root					 = CsDamageManagerLibrary::GetContextRootChecked(Context, WorldContext);

						ModifierLibrary::CopyChecked(Context, WorldContext, Modifier, Allocated.Container, Allocated.Type);

						Allocated.Modifier = Allocated.Container->Get();

						Modifiers.Add(Allocated.Modifier);

						FromModifiers.RemoveAt(I, 1, false);
					}
				}

				void FImplSlice::CopyFromModifiers(const UObject* WorldContext, const TArray<AllocatedModifierType>& FromModifiers)
				{
					CS_SET_CONTEXT_AS_FUNCTION_NAME(CopyFromModifiers);

					checkf(Modifiers_Internal.Num() == CS_EMPTY, TEXT("%s: Modifiers_Internal is already populated."), *Context);

					Modifiers.Reset(FMath::Max(Modifiers.Max(), FromModifiers.Num()));
					Modifiers_Internal.Reset(FMath::Max(Modifiers_Internal.Max(), FromModifiers.Num()));

					for (const AllocatedModifierType& From : FromModifiers)
					{
						AllocatedModifierType& To = Modifiers_Internal.AddDefaulted_GetRef();

						To.Copy(From);
						Modifiers.Add(To.Modifier);
					}
				}

				void FImplSlice::AddAndEmptyFromModifiers(TArray<ModifierType*>& FromModifiers)
				{
					const int32 Count = FromModifiers.Num();

					for (int32 I = Count - 1; I >= 0; --I)
					{
						ModifierType* Modifier = FromModifiers[I];

						Modifiers.Add(Modifier);
						FromModifiers.RemoveAt(I, 1, false);
					}
				}

				void FImplSlice::TransferFromModifiers(TArray<AllocatedModifierType>& FromModifiers)
				{
					CS_SET_CONTEXT_AS_FUNCTION_NAME(TransferFromModifiers);

					checkf(Modifiers_Internal.Num() == CS_EMPTY, TEXT("%s: Modifiers_Internal is already populated."), *Context);

					Modifiers.Reset(FMath::Max(Modifiers.Max(), FromModifiers.Num()));
					Modifiers_Internal.Reset(FMath::Max(Modifiers_Internal.Max(), FromModifiers.Num()));

					const int32 Count = FromModifiers.Num();

					for (int32 I = Count - 1; I >= 0; --I)
					{
						AllocatedModifierType& From = FromModifiers[I];
						AllocatedModifierType& To   = Modifiers_Internal.AddDefaulted_GetRef();

						From.Transfer(To);
						Modifiers.Add(To.Modifier);

						FromModifiers.RemoveAt(I, 1, false);
					}
				}
			}
		}
	}
}