// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"

// Types
#include "Types/CsTypes_Macro.h"
// Managers
#include "Managers/Projectile/CsManager_Projectile.h"
// Library
#include "Data/CsLibrary_Data_Projectile.h"
#include "Modifier/CsLibrary_ProjectileModifier.h"
#include "Library/CsLibrary_Valid.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameState.h"
#endif // #if WITH_EDITOR

namespace NCsProjectile
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NManager::FLibrary, GetSafe);
				}
			}
		}

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* WorldContext)
		{
			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetAsObjectChecked(Context, WorldContext);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetSafeAsObject(Context, WorldContext, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* WorldContext)
		{
			using namespace NCsProjectile::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Projectile* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
		{
			UObject* ContextRoot					  = GetContextRootChecked(Context, WorldContext);
			UCsManager_Projectile* Manager_Projectile = UCsManager_Projectile::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Projectile)
			return Manager_Projectile;
		}

		UCsManager_Projectile* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, WorldContext, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Projectile* Manager_Projectile = UCsManager_Projectile::Get(ContextRoot);

			if (!Manager_Projectile)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Projectile."), *Context));
			}
			return Manager_Projectile;
		}

		UCsManager_Projectile* FLibrary::GetSafe(const UObject* WorldContext)
		{
			using namespace NCsProjectile::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, WorldContext, nullptr);
		}

		#pragma endregion Get

		// Settings
		#pragma region

		void FLibrary::SetAndAddTypeMapKeyValueChecked(const FString& Context, const UObject* WorldContext, const FECsProjectile& Key, const FECsProjectile& Value)
		{
			check(EMCsProjectile::Get().IsValidEnumChecked(Context, Key));

			check(EMCsProjectile::Get().IsValidEnumChecked(Context, Value));

			GetChecked(Context, WorldContext)->SetAndAddTypeMapKeyValue(Key, Value);
		}

		void FLibrary::SafeSetAndAddTypeMapKeyValue(const FString& Context, const UObject* WorldContext, const FECsProjectile& Key, const FECsProjectile& Value, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			CS_IS_ENUM_STRUCT_VALID_EXIT(EMCsProjectile, FECsProjectile, Key)

			CS_IS_ENUM_STRUCT_VALID_EXIT(EMCsProjectile, FECsProjectile, Value)

			if (UCsManager_Projectile* Manager_Projectile = GetSafe(Context, WorldContext, Log))
			{
				Manager_Projectile->SetAndAddTypeMapKeyValue(Key, Value);
			}
		}

		#pragma endregion Settings

		// Data
		#pragma region

		#define DataType NCsProjectile::NData::IData

		#define DataHandlerType NCsPooledObject::NManager::NHandler::TData
		#define DataInterfaceMapType NCsProjectile::NData::FInterfaceMap
		DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>* FLibrary::GetSafeDataHandler(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
		#undef DataHandlerType
		#undef DataInterfaceMapType

			if (UCsManager_Projectile* Manager_Projectile = GetSafe(Context, WorldContext, Log))
			{
				return Manager_Projectile->GetDataHandler();
			}
			return nullptr;
		}

		DataType* FLibrary::GetDataChecked(const FString& Context, const UObject* WorldContext, const FName& Name)
		{
			DataType* Data = GetChecked(Context, WorldContext)->GetDataChecked(Context, Name);

			typedef NCsProjectile::NData::FLibrary PrjDataLibrary;

			check(PrjDataLibrary::IsValidChecked(Context, Data));

			return Data;
		}

		DataType* FLibrary::GetSafeData(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			if (UCsManager_Projectile* Manager_Projectile = GetSafe(Context, WorldContext, Log))
			{
				DataType* Data = Manager_Projectile->GetSafeData(Context, Name);

				typedef NCsProjectile::NData::FLibrary PrjDataLibrary;

				if (!PrjDataLibrary::IsValid(Context, Data, Log))
					return nullptr;
				return Data;
			}
			return nullptr;
		}

		DataType* FLibrary::GetDataChecked(const FString& Context, const UObject* WorldContext, const FECsProjectile& Type)
		{
			DataType* Data = GetChecked(Context, WorldContext)->GetDataChecked(Context, Type);

			typedef NCsProjectile::NData::FLibrary PrjDataLibrary;

			check(PrjDataLibrary::IsValidChecked(Context, Data));

			return Data;
		}

		DataType* FLibrary::GetSafeData(const FString& Context, const UObject* WorldContext, const FECsProjectile& Type, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			if (UCsManager_Projectile* Manager_Projectile = GetSafe(Context, WorldContext, Log))
			{
				DataType* Data = Manager_Projectile->GetSafeData(Context, Type);

				typedef NCsProjectile::NData::FLibrary PrjDataLibrary;

				if (!PrjDataLibrary::IsValid(Context, Data, Log))
					return nullptr;
				return Data;
			}
			return nullptr;
		}

		#undef DataType

		#pragma endregion Data

		// Modifier
		#pragma region

		#define ModifierResourceType NCsProjectile::NModifier::FResource
		#define ModifierType NCsProjectile::NModifier::IModifier
		#define AllocatedModifierType NCsProjectile::NModifier::FAllocated
		
		void FLibrary::DeallocateModifierChecked(const FString& Context, const UObject* WorldContext, const FECsProjectileModifier& Type, ModifierResourceType* Modifier)
		{
			GetChecked(Context, WorldContext)->DeallocateModifier(Context, Type, Modifier);
		}

		const FECsProjectileModifier& FLibrary::GetModifierTypeChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier)
		{
			return GetChecked(Context, WorldContext)->GetModifierType(Context, Modifier);
		}

		ModifierResourceType* FLibrary::CreateCopyOfModifierChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier)
		{
			UCsManager_Projectile* Manager_Projectile = GetChecked(Context, WorldContext);

			typedef NCsProjectile::NModifier::FLibrary PrjModifierLibrary;

			const FECsProjectileModifier& Type  = PrjModifierLibrary::GetTypeChecked(Context, Modifier);
			ModifierResourceType* Container		= Manager_Projectile->AllocateModifier(Type);
			ModifierType* Copy					= Container->Get();

			typedef NCsProjectile::NModifier::FLibrary ModifierLibrary;

			bool Success = ModifierLibrary::CopyChecked(Context, Modifier, Copy);

			checkf(Success, TEXT("%s: Failed to create copy of Event."), *Context);

			return Container;
		}

		ModifierResourceType* FLibrary::CreateCopyOfModifierChecked(const FString& Context, const UObject* WorldContext, const ModifierResourceType* Modifier)
		{
			CS_IS_PTR_NULL_CHECKED(Modifier)

			return CreateCopyOfModifierChecked(Context, WorldContext, Modifier->Get());
		}

		void FLibrary::CreateCopyOfModifierChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier, ModifierResourceType*& OutContainer, FECsProjectileModifier& OutType)
		{
			UCsManager_Projectile* Manager_Projectile = GetChecked(Context, WorldContext);

			typedef NCsProjectile::NModifier::FLibrary PrjModifierLibrary;

			OutType				= PrjModifierLibrary::GetTypeChecked(Context, Modifier);
			OutContainer		= Manager_Projectile->AllocateModifier(OutType);
			ModifierType* Copy	= OutContainer->Get();

			typedef NCsProjectile::NModifier::FLibrary ModifierLibrary;

			bool Success = ModifierLibrary::CopyChecked(Context, Modifier, Copy);

			checkf(Success, TEXT("%s: Failed to create copy of Event."), *Context);
		}

		void FLibrary::CreateCopyOfModifiersChecked(const FString& Context, const UObject* WorldContext, const TArray<ModifierType*>& From, TArray<ModifierResourceType*>& To)
		{
			To.Reset(FMath::Max(To.Max(), From.Num()));

			for (const ModifierType* Modifier : From)
			{
				To.Add(CreateCopyOfModifierChecked(Context, WorldContext, Modifier));
			}
		}

		void FLibrary::CreateCopyOfModifiersChecked(const FString& Context, const UObject* WorldContext, const TArray<ModifierType*>& From, TArray<AllocatedModifierType>& To)
		{
			UObject* ContextRoot = GetContextRootChecked(Context, WorldContext);

			To.Reset(FMath::Max(To.Max(), From.Num()));

			for (const ModifierType* Modifier : From)
			{
				AllocatedModifierType& Allocated = To.AddDefaulted_GetRef();
				Allocated.CopyFrom(ContextRoot, Modifier);
			}
		}

#		undef ModifierResourceType
		#undef ModifierType
		#undef AllocatedModifierType

		#pragma endregion Modifier
	}
}