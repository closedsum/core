// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsAllocated_ProjectileModifier.h"

// Types
#include "CsMacro_Misc.h"
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

		#define USING_NS_CACHED using namespace NCsProjectile::NModifier::NAllocated::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsProjectile::NModifier::NAllocated::NCached; \
			const FString& Context = Str::__FunctionName
		#define PrjManagerLibrary NCsProjectile::NManager::FLibrary
		#define PrjModifierLibrary NCsProjectile::NManager::NModifier::FLibrary

		FAllocated::~FAllocated()
		{
			Reset();
		}

		UObject* FAllocated::GetRoot() const { return Root.IsValid() ? Root.Get() : nullptr; }

		void FAllocated::Copy(const UObject* WorldContext, const IModifier* From)
		{
			SET_CONTEXT(Copy);

			CS_IS_PTR_NULL_CHECKED(From)

			Root	  = PrjManagerLibrary::GetContextRootChecked(Context, WorldContext);
			Container = PrjModifierLibrary::CreateCopyOfChecked(Context, WorldContext, From);
			Modifier  = Container->Get();
			Type	  = PrjModifierLibrary::GetTypeChecked(Context, WorldContext, Modifier);
		}

		void FAllocated::Copy(const FAllocated& From)
		{
			SET_CONTEXT(Copy);

			CS_IS_PTR_NULL_CHECKED(From.GetRoot())

			checkf(!Container, TEXT("%s: Container is already SET."), *Context);

			if (From.Container)
			{
				Root	  = From.GetRoot();
				Container = PrjModifierLibrary::CreateCopyOfChecked(Context, GetRoot(), From.Container);
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
			SET_CONTEXT(Transfer);

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
			SET_CONTEXT(Reset);

			if (Container)
			{
				CS_IS_PTR_NULL_CHECKED(GetRoot())

				PrjModifierLibrary::DeallocateChecked(Context, GetRoot(), Type, Container);
			}
			Clear();
		}

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef PrjManagerLibrary
		#undef PrjModifierLibrary
	}
}