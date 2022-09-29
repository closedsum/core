// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/Modifier/Damage/CsPayload_Projectile_ModifierDamageImplSlice.h"

// Library
#include "Managers/Damage/CsLibrary_Manager_Damage.h"
#include "Library/CsLibrary_Array.h"
#include "Library/CsLibrary_Valid.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Damage
#include "Modifier/CsResource_DamageModifier.h"

const FName NCsProjectile::NPayload::NModifier::NDamage::FImplSlice::Name = FName("NCsProjectile::NPayload::NModifier::NDamage::FImplSlice");;

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NModifier
		{
			namespace NDamage
			{
				namespace NImplSlice
				{
					namespace NCached
					{
						namespace Str
						{
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NPayload::NModifier::NDamage::FImplSlice, CopyFromModifiers);
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NPayload::NModifier::NDamage::FImplSlice, TransferFromModifiers);
						}
					}
				}

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
					checkf(InInterfaceMap, TEXT("NCsProjectile::NPayload::NModifier::NDamage::FImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));

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

				#define DmgModifierType NCsDamage::NModifier::IModifier
				#define AllocatedDmgModifierType NCsDamage::NModifier::FAllocated

				void FImplSlice::CopyFromModifiers(const UObject* WorldContext, const TArray<DmgModifierType*>& FromModifiers)
				{
					using namespace NCsProjectile::NPayload::NModifier::NDamage::NImplSlice::NCached;

					const FString& Context = Str::CopyFromModifiers;

					CS_IS_TARRAY_ANY_NULL_CHECKED(FromModifiers, DmgModifierType)

					checkf(Modifiers_Internal.Num() == CS_EMPTY, TEXT("%s: Modifiers_Internal is already populated."), *Context);

					typedef NCsArray::FLibrary ArrayLibrary;

					Modifiers.Reset(FMath::Max(Modifiers.Max(), FromModifiers.Num()));
					Modifiers_Internal.Reset(FMath::Max(Modifiers_Internal.Max(), FromModifiers.Num()));
				
					for (DmgModifierType* Modifier : FromModifiers)
					{
						typedef NCsDamage::NManager::FLibrary DmgManagerLibrary;

						AllocatedDmgModifierType& Allocated = Modifiers_Internal.AddDefaulted_GetRef();

						Allocated.Root = DmgManagerLibrary::GetContextRootChecked(Context, WorldContext);

						DmgManagerLibrary::CreateCopyOfModifierChecked(Context, WorldContext, Modifier, Allocated.Container, Allocated.Type);
					
						Allocated.Modifier = Allocated.Container->Get();

						Modifiers.Add(Allocated.Modifier);
					}
				}

				void FImplSlice::CopyFromModifiers(const UObject* WorldContext, const TArray<AllocatedDmgModifierType>& FromModifiers)
				{
					using namespace NCsProjectile::NPayload::NModifier::NDamage::NImplSlice::NCached;

					const FString& Context = Str::CopyFromModifiers;

					checkf(Modifiers_Internal.Num() == CS_EMPTY, TEXT("%s: Modifiers_Internal is already populated."), *Context);

					typedef NCsArray::FLibrary ArrayLibrary;

					Modifiers.Reset(FMath::Max(Modifiers.Max(), FromModifiers.Num()));
					Modifiers_Internal.Reset(FMath::Max(Modifiers_Internal.Max(), FromModifiers.Num()));

					for (const AllocatedDmgModifierType& From : FromModifiers)
					{
						AllocatedDmgModifierType& To = Modifiers_Internal.AddDefaulted_GetRef();

						To.Copy(From);
						Modifiers.Add(To.Modifier);
					}
				}

				void FImplSlice::TransferFromModifiers(TArray<AllocatedDmgModifierType>& FromModifiers)
				{
					using namespace NCsProjectile::NPayload::NModifier::NDamage::NImplSlice::NCached;

					const FString& Context = Str::TransferFromModifiers;

					checkf(Modifiers_Internal.Num() == CS_EMPTY, TEXT("%s: Modifiers_Internal is already populated."), *Context);

					typedef NCsArray::FLibrary ArrayLibrary;

					Modifiers.Reset(FMath::Max(Modifiers.Max(), FromModifiers.Num()));
					Modifiers_Internal.Reset(FMath::Max(Modifiers_Internal.Max(), FromModifiers.Num()));

					for (AllocatedDmgModifierType& From : FromModifiers)
					{
						AllocatedDmgModifierType& To = Modifiers_Internal.AddDefaulted_GetRef();

						From.Transfer(To);
						Modifiers.Add(To.Modifier);
					}
					FromModifiers.Reset(FromModifiers.Max());
				}

				#undef DmgModifierType
				#undef AllocatedDmgModifierType
			}
		}
	}
}