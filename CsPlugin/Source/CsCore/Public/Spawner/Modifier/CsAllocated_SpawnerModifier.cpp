// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Modifier/CsAllocated_SpawnerModifier.h"
#include "CsCore.h"

// Library
#include "Managers/Spawner/CsLibrary_Manager_Spawner.h"
#include "Library/CsLibrary_Valid.h"
// Spawner
#include "Spawner/Modifier/CsResource_SpawnerModifier.h"

namespace NCsSpawner
{
	namespace NModifier
	{
		namespace NAllocated
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSpawner::NModifier::FAllocated, Copy);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSpawner::NModifier::FAllocated, Transfer);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSpawner::NModifier::FAllocated, Reset);
				}
			}
		}

		FAllocated::~FAllocated()
		{
			Reset();
		}

		UObject* FAllocated::GetRoot() const { return Root.IsValid() ? Root.Get() : nullptr; }

		#define ModifierType NCsSpawner::NModifier::IModifier
		void FAllocated::Copy(UObject* InRoot, const ModifierType* From)
		{
		#undef ModifierType

			using namespace NCsSpawner::NModifier::NAllocated::NCached;

			const FString& Context = Str::Copy;

			CS_IS_PTR_NULL_CHECKED(InRoot)

			CS_IS_PTR_NULL_CHECKED(From)

			typedef NCsSpawner::NManager::NModifier::FLibrary ModifierLibrary;

			Root	  = InRoot;
			Container = ModifierLibrary::CreateCopyOfChecked(Context, InRoot, From);
			Modifier  = Container->Get();
			Type	  = ModifierLibrary::GetTypeChecked(Context, InRoot, Modifier);
		}

		void FAllocated::Copy(const FAllocated& From)
		{
			using namespace NCsSpawner::NModifier::NAllocated::NCached;

			const FString& Context = Str::Copy;

			CS_IS_PTR_NULL_CHECKED(From.GetRoot())

			checkf(!Container, TEXT("%s: Container is already SET."), *Context);

			if (From.Container)
			{
				typedef NCsSpawner::NManager::NModifier::FLibrary ModifierLibrary;

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
			using namespace NCsSpawner::NModifier::NAllocated::NCached;

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
			using namespace NCsSpawner::NModifier::NAllocated::NCached;

			const FString& Context = Str::Reset;

			if (Container)
			{
				CS_IS_PTR_NULL_CHECKED(GetRoot())

				typedef NCsSpawner::NManager::NModifier::FLibrary ModifierLibrary;

				ModifierLibrary::DeallocateChecked(Context, GetRoot(), Type, Container);
			}
			Clear();
		}
	}
}