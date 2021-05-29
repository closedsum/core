// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"

// Types
#include "Types/CsTypes_Macro.h"
// Managers
#include "Managers/Projectile/CsManager_Projectile.h"
// Library
#include "Data/CsLibrary_Data_Projectile.h"
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

		// Data
		#pragma region

		#define DataType NCsProjectile::NData::IData

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
	}
}