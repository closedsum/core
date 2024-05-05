// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/Modifier/Damage/CsPayload_Projectile_ModifierDamageImplSlice.h"

// Types
#include "CsMacro_Misc.h"
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
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NPayload::NModifier::NDamage::FImplSlice, SetInterfaceMap);
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NPayload::NModifier::NDamage::FImplSlice, CopyFromModifiers);
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NPayload::NModifier::NDamage::FImplSlice, CopyAndEmptyFromModifiers);
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NPayload::NModifier::NDamage::FImplSlice, TransferFromModifiers);
						}
					}
				}

				#define USING_NS_CACHED using namespace NCsProjectile::NPayload::NModifier::NDamage::NImplSlice::NCached;
				#define SET_CONTEXT(__FunctionName) using namespace NCsProjectile::NPayload::NModifier::NDamage::NImplSlice::NCached; \
					const FString& Context = Str::__FunctionName
				#define ArrayLibrary NCsArray::FLibrary
				#define DmgManagerLibrary NCsDamage::NManager::FLibrary
				#define DmgModifierLibrary NCsDamage::NManager::NModifier::FLibrary

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
					SET_CONTEXT(SetInterfaceMap);

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

				#define DmgModifierType NCsDamage::NModifier::IModifier
				#define AllocatedDmgModifierType NCsDamage::NModifier::FAllocated

				void FImplSlice::CopyFromModifiers(const UObject* WorldContext, const TArray<DmgModifierType*>& FromModifiers)
				{
					SET_CONTEXT(CopyFromModifiers);

					CS_IS_TARRAY_ANY_NULL_CHECKED(FromModifiers, DmgModifierType)

					checkf(Modifiers_Internal.Num() == CS_EMPTY, TEXT("%s: Modifiers_Internal is already populated."), *Context);

					Modifiers.Reset(FMath::Max(Modifiers.Max(), FromModifiers.Num()));
					Modifiers_Internal.Reset(FMath::Max(Modifiers_Internal.Max(), FromModifiers.Num()));
				
					for (DmgModifierType* Modifier : FromModifiers)
					{
						AllocatedDmgModifierType& Allocated = Modifiers_Internal.AddDefaulted_GetRef();

						Allocated.Root = DmgManagerLibrary::GetContextRootChecked(Context, WorldContext);

						DmgModifierLibrary::CopyChecked(Context, WorldContext, Modifier, Allocated.Container, Allocated.Type);
					
						Allocated.Modifier = Allocated.Container->Get();

						Modifiers.Add(Allocated.Modifier);
					}
				}

				void FImplSlice::CopyAndEmptyFromModifiers(const UObject* WorldContext, TArray<DmgModifierType*>& FromModifiers)
				{
					SET_CONTEXT(CopyAndEmptyFromModifiers);

					CS_IS_TARRAY_ANY_NULL_CHECKED(FromModifiers, DmgModifierType)

					checkf(Modifiers_Internal.Num() == CS_EMPTY, TEXT("%s: Modifiers_Internal is already populated."), *Context);

					const int32 Count = FromModifiers.Num();

					Modifiers.Reset(FMath::Max(Modifiers.Max(), Count));
					Modifiers_Internal.Reset(FMath::Max(Modifiers_Internal.Max(), Count));
				
					for (int32 I = Count - 1; I >= 0; --I)
					{
						DmgModifierType* Modifier			= FromModifiers[I];
						AllocatedDmgModifierType& Allocated = Modifiers_Internal.AddDefaulted_GetRef();

						Allocated.Root = DmgManagerLibrary::GetContextRootChecked(Context, WorldContext);

						DmgModifierLibrary::CopyChecked(Context, WorldContext, Modifier, Allocated.Container, Allocated.Type);
					
						Allocated.Modifier = Allocated.Container->Get();

						Modifiers.Add(Allocated.Modifier);

						FromModifiers.RemoveAt(I, 1, false);
					}
				}

				void FImplSlice::CopyFromModifiers(const UObject* WorldContext, const TArray<AllocatedDmgModifierType>& FromModifiers)
				{
					SET_CONTEXT(CopyFromModifiers);

					checkf(Modifiers_Internal.Num() == CS_EMPTY, TEXT("%s: Modifiers_Internal is already populated."), *Context);

					Modifiers.Reset(FMath::Max(Modifiers.Max(), FromModifiers.Num()));
					Modifiers_Internal.Reset(FMath::Max(Modifiers_Internal.Max(), FromModifiers.Num()));

					for (const AllocatedDmgModifierType& From : FromModifiers)
					{
						AllocatedDmgModifierType& To = Modifiers_Internal.AddDefaulted_GetRef();

						To.Copy(From);
						Modifiers.Add(To.Modifier);
					}
				}

				void FImplSlice::AddAndEmptyFromModifiers(TArray<DmgModifierType*>& FromModifiers)
				{
					const int32 Count = FromModifiers.Num();

					for (int32 I = Count - 1; I >= 0; --I)
					{
						DmgModifierType* Modifier = FromModifiers[I];

						Modifiers.Add(Modifier);
						FromModifiers.RemoveAt(I, 1, false);
					}
				}

				void FImplSlice::TransferFromModifiers(TArray<AllocatedDmgModifierType>& FromModifiers)
				{
					SET_CONTEXT(TransferFromModifiers);

					checkf(Modifiers_Internal.Num() == CS_EMPTY, TEXT("%s: Modifiers_Internal is already populated."), *Context);

					Modifiers.Reset(FMath::Max(Modifiers.Max(), FromModifiers.Num()));
					Modifiers_Internal.Reset(FMath::Max(Modifiers_Internal.Max(), FromModifiers.Num()));

					const int32 Count = FromModifiers.Num();

					for (int32 I = Count - 1; I >= 0; --I)
					{
						AllocatedDmgModifierType& From = FromModifiers[I];
						AllocatedDmgModifierType& To   = Modifiers_Internal.AddDefaulted_GetRef();

						From.Transfer(To);
						Modifiers.Add(To.Modifier);

						FromModifiers.RemoveAt(I, 1, false);
					}
				}

				#undef DmgModifierType
				#undef AllocatedDmgModifierType

				#undef USING_NS_CACHED
				#undef SET_CONTEXT
				#undef ArrayLibrary
				#undef DmgManagerLibrary
				#undef DmgModifierLibrary
			}
		}
	}
}