// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/Modifier/CsPayload_Projectile_ModifierImplSlice.h"

// Library
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"
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
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NPayload::NModifier::FImplSlice, CopyAndEmptyFromModifiers);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NPayload::NModifier::FImplSlice, TransferFromModifiers);
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
			#define AllocatedModifierType NCsProjectile::NModifier::FAllocated

			void FImplSlice::CopyFromModifiers(const UObject* WorldContext, const TArray<ModifierType*>& FromModifiers)
			{
				using namespace NCsProjectile::NPayload::NModifier::NImplSlice::NCached;

				const FString& Context = Str::CopyFromModifiers;

				CS_IS_TARRAY_ANY_NULL_CHECKED(FromModifiers, ModifierType)

				checkf(Modifiers_Internal.Num() == CS_EMPTY, TEXT("%s: Modifiers_Internal is already populated."), *Context);

				typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;
				typedef NCsProjectile::NManager::NModifier::FLibrary PrjModifierLibrary;

				Modifiers.Reset(FMath::Max(Modifiers.Max(), FromModifiers.Num()));
				Modifiers_Internal.Reset(FMath::Max(Modifiers_Internal.Max(), FromModifiers.Num()));
				
				for (ModifierType* Modifier : FromModifiers)
				{
					AllocatedModifierType& Allocated = Modifiers_Internal.AddDefaulted_GetRef();

					Allocated.Root = PrjManagerLibrary::GetContextRootChecked(Context, WorldContext);

					PrjModifierLibrary::CreateCopyOfChecked(Context, WorldContext, Modifier, Allocated.Container, Allocated.Type);
					
					Allocated.Modifier = Allocated.Container->Get();

					Modifiers.Add(Allocated.Modifier);
				}
			}

			void FImplSlice::CopyAndEmptyFromModifiers(const UObject* WorldContext, TArray<ModifierType*>& FromModifiers)
			{
				using namespace NCsProjectile::NPayload::NModifier::NImplSlice::NCached;

				const FString& Context = Str::CopyAndEmptyFromModifiers;

				CS_IS_TARRAY_ANY_NULL_CHECKED(FromModifiers, ModifierType)

				checkf(Modifiers_Internal.Num() == CS_EMPTY, TEXT("%s: Modifiers_Internal is already populated."), *Context);

				typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;
				typedef NCsProjectile::NManager::NModifier::FLibrary PrjModifierLibrary;

				const int32 Count = FromModifiers.Num();

				Modifiers.Reset(FMath::Max(Modifiers.Max(), Count));
				Modifiers_Internal.Reset(FMath::Max(Modifiers_Internal.Max(), Count));
				
				for (int32 I = Count - 1; I >= 0; --I)
				{
					ModifierType* Modifier			 = FromModifiers[I];
					AllocatedModifierType& Allocated = Modifiers_Internal.AddDefaulted_GetRef();

					Allocated.Root = PrjManagerLibrary::GetContextRootChecked(Context, WorldContext);

					PrjModifierLibrary::CreateCopyOfChecked(Context, WorldContext, Modifier, Allocated.Container, Allocated.Type);
					
					Allocated.Modifier = Allocated.Container->Get();

					Modifiers.Add(Allocated.Modifier);

					FromModifiers.RemoveAt(I, 1, false);
				}
			}

			void FImplSlice::CopyFromModifiers(const UObject* WorldContext, const TArray<AllocatedModifierType>& FromModifiers)
			{
				using namespace NCsProjectile::NPayload::NModifier::NImplSlice::NCached;

				const FString& Context = Str::CopyFromModifiers;

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

			void FImplSlice::TransferFromModifiers(TArray<AllocatedModifierType>& FromModifiers)
			{
				using namespace NCsProjectile::NPayload::NModifier::NImplSlice::NCached;

				const FString& Context = Str::TransferFromModifiers;

				checkf(Modifiers_Internal.Num() == CS_EMPTY, TEXT("%s: Modifiers_Internal is already populated."), *Context);

				Modifiers.Reset(FMath::Max(Modifiers.Max(), FromModifiers.Num()));
				Modifiers_Internal.Reset(FMath::Max(Modifiers_Internal.Max(), FromModifiers.Num()));

				const int32 Count = FromModifiers.Num();

				for (int32 I = Count - 1; I >= 0; --I)
				{
					AllocatedModifierType& From = FromModifiers[I];
					AllocatedModifierType& To	= Modifiers_Internal.AddDefaulted_GetRef();

					From.Transfer(To);
					Modifiers.Add(To.Modifier);

					FromModifiers.RemoveAt(I, 1, false);
				}
			}

			#undef ModifierType
			#undef AllocatedModifierType
		}
	}
}