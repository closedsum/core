// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/Modifier/CsPayload_Projectile_ModifierImplSlice.h"

// Library
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"
#include "Library/CsLibrary_Array.h"
#include "Library/CsLibrary_Valid.h"
// Container
#include "Containers/CsInterfaceMap.h"
// Projectile
#include "Modifier/CsResource_ProjectileModifier.h"

const FName NCsProjectile::NPayload::NModifier::FImplSlice::Name = FName("NCsProjectile::NPayload::NModifier::FImplSlice");;

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NModifier
		{
			namespace NImplSlice
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NPayload::NModifier::FImplSlice, CopyFromModifiers);
					}
				}
			}

			FImplSlice::FImplSlice() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				// IModifier
				Modifiers(),
				Modifiers_Internal()
			{
			}

			void FImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
			{
				checkf(InInterfaceMap, TEXT("NCsProjectile::NPayload::NModifier::FImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));

				checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("NCsProjectile::NPayload::NModifier::FImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

				InterfaceMap = InInterfaceMap;

				InterfaceMap->Add<IModifier>(FImplSlice::Name, static_cast<IModifier*>(this));
			}

			// ICsReset
			#pragma region

			void FImplSlice::Reset()
			{	
				Modifiers_Internal.Reset(Modifiers_Internal.Max());
				Modifiers.Reset(Modifiers.Max());
			}

			#pragma endregion ICsReset

			#define ModifierType NCsProjectile::NModifier::IModifier
			void FImplSlice::CopyFromModifiers(UObject* Root, const TArray<ModifierType*>& FromModifiers)
			{
				using namespace NCsProjectile::NPayload::NModifier::NImplSlice::NCached;

				const FString& Context = Str::CopyFromModifiers;

				CS_IS_PTR_NULL_CHECKED(Root)

				CS_IS_ARRAY_EMPTY_CHECKED(FromModifiers, ModifierType*)

				CS_IS_ARRAY_ANY_NULL_CHECKED(FromModifiers, ModifierType)

				checkf(Modifiers_Internal.Num() == CS_EMPTY, TEXT("%s: Modifiers_Internal is already populated."), *Context);

				typedef NCsArray::FLibrary ArrayLibrary;
				typedef NCsProjectile::NModifier::FAllocated AllocatedModifierType;

				ArrayLibrary::ResetChecked<ModifierType>(Context, Modifiers, FromModifiers.Num());
				ArrayLibrary::ResetChecked<AllocatedModifierType>(Context, Modifiers_Internal, FromModifiers.Num());
				
				for (ModifierType* Modifier : FromModifiers)
				{
					typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;

					AllocatedModifierType& Allocated = Modifiers_Internal.AddDefaulted_GetRef();

					Allocated.Root = Root;

					PrjManagerLibrary::CreateCopyOfModifierChecked(Context, Root, Modifier, Allocated.Container, Allocated.Type);
					
					Allocated.Modifier = Allocated.Container->Get();

					Modifiers.Add(Allocated.Modifier);
				}
			}
			#undef ModifierType
		}
	}
}