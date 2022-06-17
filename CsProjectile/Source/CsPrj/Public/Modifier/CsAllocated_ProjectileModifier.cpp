// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsAllocated_ProjectileModifier.h"
#include "CsPrj.h"

// Library
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"
#include "Library/CsLibrary_Valid.h"
// Projectile
#include "Modifier/CsResource_ProjectileModifier.h"

namespace NCsProjectile 
{
	namespace NModifier
	{
		namespace NAllocated
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NModifier::FAllocated, Copy);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NModifier::FAllocated, Transfer);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NModifier::FAllocated, Reset);
				}
			}
		}

		FAllocated::~FAllocated()
		{
			Reset();
		}

		UObject* FAllocated::GetRoot() const { return Root.IsValid() ? Root.Get() : nullptr; }

		void FAllocated::Copy(const UObject* WorldContext, const IModifier* From)
		{
			using namespace NCsProjectile::NModifier::NAllocated::NCached;

			const FString& Context = Str::Copy;

			CS_IS_PTR_NULL_CHECKED(From)

			typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;

			Root	  = PrjManagerLibrary::GetContextRootChecked(Context, WorldContext);
			Container = PrjManagerLibrary::CreateCopyOfModifierChecked(Context, WorldContext, From);
			Modifier  = Container->Get();
			Type	  = PrjManagerLibrary::GetModifierTypeChecked(Context, WorldContext, Modifier);
		}

		void FAllocated::Copy(const FAllocated& From)
		{
			using namespace NCsProjectile::NModifier::NAllocated::NCached;

			const FString& Context = Str::Copy;

			CS_IS_PTR_NULL_CHECKED(From.GetRoot())

			checkf(!Container, TEXT("%s: Container is already SET."), *Context);

			if (From.Container)
			{
				typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;

				Root	  = From.GetRoot();
				Container = PrjManagerLibrary::CreateCopyOfModifierChecked(Context, GetRoot(), From.Container);
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
			using namespace NCsProjectile::NModifier::NAllocated::NCached;

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
			using namespace NCsProjectile::NModifier::NAllocated::NCached;

			const FString& Context = Str::Reset;

			if (Container)
			{
				CS_IS_PTR_NULL_CHECKED(GetRoot())

				typedef NCsProjectile::NManager::FLibrary PrjManagerLibrary;

				PrjManagerLibrary::DeallocateModifierChecked(Context, GetRoot(), Type, Container);
			}
			Clear();
		}
	}
}