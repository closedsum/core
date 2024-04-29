// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsAllocated_WeaponModifier.h"
#include "CsWp.h"

// Library
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
#include "Library/CsLibrary_Valid.h"
// Weapon
#include "Modifier/CsResource_WeaponModifier.h"

namespace NCsWeapon
{
	namespace NModifier
	{
		namespace NAllocated
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NModifier::FAllocated, Copy);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NModifier::FAllocated, Transfer);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NModifier::FAllocated, Reset);
				}
			}
		}

		FAllocated::~FAllocated()
		{
			Reset();
		}

		UObject* FAllocated::GetRoot() const { return Root.IsValid() ? Root.Get() : nullptr; }

		void FAllocated::Copy(UObject* InRoot, const IModifier* From)
		{
			using namespace NCsWeapon::NModifier::NAllocated::NCached;

			const FString& Context = Str::Copy;

			CS_IS_PTR_NULL_CHECKED(InRoot)

			CS_IS_PTR_NULL_CHECKED(From)

			typedef NCsWeapon::NManager::NModifier::FLibrary ModifierLibrary;

			Root	  = InRoot;
			Container = ModifierLibrary::CreateCopyOfChecked(Context, InRoot, From);
			Modifier  = Container->Get();
			Type	  = ModifierLibrary::GetTypeChecked(Context, InRoot, Modifier);
		}

		void FAllocated::Copy(const FAllocated& From)
		{
			using namespace NCsWeapon::NModifier::NAllocated::NCached;

			const FString& Context = Str::Copy;

			CS_IS_PTR_NULL_CHECKED(From.GetRoot())

			checkf(!Container, TEXT("%s: Container is already SET."), *Context);

			if (From.Container)
			{
				typedef NCsWeapon::NManager::NModifier::FLibrary ModifierLibrary;

				Root	  = From.GetRoot();
				Container = ModifierLibrary::CreateCopyOfChecked(Context, GetRoot(), From.Container);
				Modifier  = Container->Get();
				Type	  = From.Type;
			}
			else
			{
				Modifier = From.Modifier;
			}
		}

		void FAllocated::Transfer(FAllocated& To)
		{
			using namespace NCsWeapon::NModifier::NAllocated::NCached;

			const FString& Context = Str::Transfer;

			checkf(!To.Container, TEXT("%s: Container is already SET."), *Context);

			if (Container)
			{
				CS_IS_PTR_NULL_CHECKED(GetRoot())

				To.Root		  = GetRoot();
				To.Container  = Container;
				To.Modifier   = Modifier;
				To.Type		  = Type;
			}
			else
			{
				To.Modifier = Modifier;
			}
			Clear();
		}

		void FAllocated::Reset()
		{
			using namespace NCsWeapon::NModifier::NAllocated::NCached;

			const FString& Context = Str::Reset;

			if (Container)
			{
				CS_IS_PTR_NULL_CHECKED(GetRoot())

				typedef NCsWeapon::NManager::NModifier::FLibrary ModifierLibrary;

				ModifierLibrary::DeallocateChecked(Context, GetRoot(), Type, Container);
			}
			Clear();
		}
	}
}