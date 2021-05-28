// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"

// Types
#include "Types/CsTypes_Macro.h"
// Managers
#include "Managers/Weapon/CsManager_Weapon.h"
// Library
#include "Library/CsLibrary_Valid.h"
#include "Data/CsLibrary_Data_Weapon.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameState.h"
#endif // #if WITH_EDITOR

namespace NCsWeapon
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWeapon::NManager::FLibrary, GetSafe);
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
			using namespace NCsWeapon::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Weapon* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
		{
			UObject* ContextRoot			  = GetContextRootChecked(Context, WorldContext);
			UCsManager_Weapon* Manager_Weapon = UCsManager_Weapon::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Weapon)
			return Manager_Weapon;
		}

		UCsManager_Weapon* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, WorldContext, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Weapon* Manager_Weapon = UCsManager_Weapon::Get(ContextRoot);

			if (!Manager_Weapon)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Weapon."), *Context));
			}
			return Manager_Weapon;
		}

		UCsManager_Weapon* FLibrary::GetSafe(const UObject* WorldContext)
		{
			using namespace NCsWeapon::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, WorldContext, nullptr);
		}

		#pragma endregion Get

		// Class
		#pragma region

		FCsWeapon* FLibrary::GetWeaponChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type)
		{
			return GetChecked(Context, WorldContext)->GetWeaponChecked(Context, Type);
		}

		FCsWeapon* FLibrary::GetSafeWeapon(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
			{
				return Manager_Weapon->GetSafeWeapon(Context, Type);
			}
			return nullptr;
		}

		FCsWeapon* FLibrary::GetWeaponChecked(const FString& Context, const UObject* WorldContext, const FECsWeaponClass& Type)
		{
			return GetChecked(Context, WorldContext)->GetWeaponChecked(Context, Type);
		}

		FCsWeapon* FLibrary::GetSafeWeapon(const FString& Context, const UObject* WorldContext, const FECsWeaponClass& Type, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
			{
				return Manager_Weapon->GetSafeWeapon(Context, Type);
			}
			return nullptr;
		}

		#pragma endregion Class

		// Data
		#pragma region

		#define DataType NCsWeapon::NData::IData

		DataType* FLibrary::GetDataChecked(const FString& Context, const UObject* WorldContext, const FName& Name)
		{
			DataType* Data = GetChecked(Context, WorldContext)->GetDataChecked(Context, Name);

			typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

			check(WeaponDataLibrary::IsValidChecked(Context, Data));

			return Data;
		}

		DataType* FLibrary::GetSafeData(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
			{
				DataType* Data = Manager_Weapon->GetSafeData(Context, Name);

				typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

				if (!WeaponDataLibrary::IsValid(Context, Data, Log))
					return nullptr;
				return Data;
			}
			return nullptr;
		}

		DataType* FLibrary::GetDataChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type)
		{
			DataType* Data = GetChecked(Context, WorldContext)->GetDataChecked(Context, Type);

			typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

			check(WeaponDataLibrary::IsValidChecked(Context, Data));

			return Data;
		}

		DataType* FLibrary::GetSafeData(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
			{
				DataType* Data = Manager_Weapon->GetSafeData(Context, Type);

				typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;

				if (!WeaponDataLibrary::IsValid(Context, Data, Log))
					return nullptr;
				return Data;
			}
			return nullptr;
		}

		#undef DataType

		#pragma endregion Data
	}
}