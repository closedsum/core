// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"

// Library
#include "Data/CsLibrary_Data_Weapon.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Weapon/CsManager_Weapon.h"
// Weapon
#include "CsWeapon.h"
#include "Payload/CsPayload_WeaponImpl.h"

#if WITH_EDITOR
// Library
	// Common
#include "Game/CsLibrary_GameState.h"
#include "Library/CsLibrary_World.h"
// Managers
#include "Singleton/CsGetManagerSingleton.h"
#endif // #if WITH_EDITOR

// NCsWeapon::NManager::FLibrary
//	Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME_NESTED_2(NCsWeapon, NManager, Library)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsWeapon::NManager::FLibrary, GetSafeContextRoot)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsWeapon::NManager::FLibrary, GetSafe)
CS_END_CACHED_FUNCTION_NAME_NESTED_2

#pragma endregion Cached

namespace NCsWeapon
{
	namespace NManager
	{
		using LogClassType = NCsWeapon::FLog;

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		using DataType = NCsWeapon::NData::IData;
		using DataInterfaceMapType = NCsWeapon::NData::FInterfaceMap;
		using DataHandlerType = NCsData::NManager::NHandler::TData<DataType, FCsData_WeaponPtr, DataInterfaceMapType>;
		using PayloadType = NCsWeapon::NPayload::IPayload;
		using PayloadImplType = NCsWeapon::NPayload::FImpl;

		// Print
		#pragma region

		FString FLibrary::PrintObjectWithClass(const UCsManager_Weapon* Manager)
		{
			return FString::Printf(TEXT("%s: with Class: %s"), *(Manager->GetName()), *(Manager->GetClass()->GetName()));
		}

		#pragma endregion Print

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* WorldContext)
		{
			if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
			{
				const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST_CHECKED(WorldContext, UObject, ICsGetManagerSingleton);

				return GetManagerSingleton->_getUObject();
			}
			return CsGameStateLibrary::GetAsObjectChecked(Context, WorldContext);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
			{
				if (const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST(WorldContext, UObject, ICsGetManagerSingleton))
				{
					return GetManagerSingleton->_getUObject();
				}
			}
			return CsGameStateLibrary::GetSafeAsObject(Context, WorldContext, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* WorldContext)
		{
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetSafeContextRoot);

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

		UCsManager_Weapon* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
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
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetSafe);

			return GetSafe(Context, WorldContext, nullptr);
		}

		#pragma endregion Get

		// Payload
		#pragma region

		PayloadType* FLibrary::AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type)
		{
			return GetChecked(Context, WorldContext)->AllocatePayload(Type);
		}

		PayloadImplType* FLibrary::AllocatePayloadImplChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type)
		{
			return GetChecked(Context, WorldContext)->AllocatePayload<PayloadImplType>(Type);
		}

		#pragma endregion Payload

		// Spawn
		#pragma region
	
		const FCsWeaponPooled* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, UObject* Owner, const FECsWeapon& Type)
		{
			PayloadImplType* Payload = AllocatePayloadImplChecked(Context, WorldContext, Type);

			Payload->Owner = Owner;
			Payload->Type  = Type;

			return GetChecked(Context, WorldContext)->Spawn(Type, Payload);
		}

		const FCsWeaponPooled* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, PayloadType* Payload)
		{
			return GetChecked(Context, WorldContext)->Spawn(Type, Payload);
		}

		#pragma endregion Spawn

		// Destroy
		#pragma region
		
		bool FLibrary::DestroyChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, ICsWeapon* Weapon)
		{
			return GetChecked(Context, WorldContext)->Destroy(Type, Weapon);
		}

		bool FLibrary::DestroyChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, FCsWeaponPooled* Weapon)
		{
			return GetChecked(Context, WorldContext)->Destroy(Type, Weapon->GetWeapon());
		}

		#pragma endregion Destroy

		// Class
		#pragma region

		FCsWeaponClass* FLibrary::GetWeaponChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type)
		{
			return GetChecked(Context, WorldContext)->GetWeaponChecked(Context, Type);
		}

		FCsWeaponClass* FLibrary::GetSafeWeapon(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
				return Manager_Weapon->GetSafeWeapon(Context, Type);
			return nullptr;
		}

		FCsWeaponClass* FLibrary::GetWeaponChecked(const FString& Context, const UObject* WorldContext, const FECsWeaponClass& Type)
		{
			return GetChecked(Context, WorldContext)->GetWeaponChecked(Context, Type);
		}

		FCsWeaponClass* FLibrary::GetSafeWeapon(const FString& Context, const UObject* WorldContext, const FECsWeaponClass& Type, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
				return Manager_Weapon->GetSafeWeapon(Context, Type);
			return nullptr;
		}

		UClass* FLibrary::GetClassChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type)
		{
			return GetWeaponChecked(Context, WorldContext, Type)->GetClassChecked(Context);
		}

		UClass* FLibrary::GetSafeClass(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
			{
				FCsWeaponClass* Weapon = Manager_Weapon->GetSafeWeapon(Context, Type);

				return Weapon->GetClass();
			}
			return nullptr;
		}

		UClass* FLibrary::GetSafeClass(const FString& Context, const UObject* WorldContext, const FECsWeaponClass& Type, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
			{
				FCsWeaponClass* Weapon = Manager_Weapon->GetSafeWeapon(Context, Type);

				return Weapon->GetClass();
			}
			return nullptr;
		}

		bool FLibrary::SafeAddClass(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, UObject* Class, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
				return Manager_Weapon->SafeAddClass(Context, Type, Class);
			return false;
		}

		bool FLibrary::SafeAddClass(const FString& Context, const UObject* WorldContext, const FECsWeaponClass& Type, UObject* Class, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
				return Manager_Weapon->SafeAddClass(Context, Type, Class);
			return false;
		}

		#pragma endregion Class

		// Data
		#pragma region

		DataHandlerType* FLibrary::GetSafeDataHandler(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
				return Manager_Weapon->GetDataHandler();
			return nullptr;
		}

		DataType* FLibrary::GetDataChecked(const FString& Context, const UObject* WorldContext, const FName& Name)
		{
			return GetChecked(Context, WorldContext)->GetDataChecked(Context, Name);
		}

		DataType* FLibrary::GetSafeData(const FString& Context, const UObject* WorldContext, const FName& Name, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
				return Manager_Weapon->GetSafeData(Context, Name);
			return nullptr;
		}

		DataType* FLibrary::GetDataChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type)
		{
			return GetChecked(Context, WorldContext)->GetDataChecked(Context, Type);
		}

		DataType* FLibrary::GetSafeData(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
				return Manager_Weapon->GetSafeData(Context, Type);
			return nullptr;
		}

		#pragma endregion Data
	}
}

namespace NCsWeapon
{
	namespace NManager
	{
		namespace NModifier
		{
			using ModifierResourceType = NCsWeapon::NModifier::NResource::FResource;
			using ModifierType = NCsWeapon::NModifier::IModifier;
		
			ModifierResourceType* FLibrary::AllocateChecked(const FString& Context, const UObject* WorldContext, const FECsWeaponModifier& Type)
			{
				return CsWeaponManagerLibrary::GetChecked(Context, WorldContext)->AllocateModifier(Type);
			}

			void FLibrary::DeallocateChecked(const FString& Context, const UObject* WorldContext, const FECsWeaponModifier& Type, ModifierResourceType* Modifier)
			{
				CsWeaponManagerLibrary::GetChecked(Context, WorldContext)->DeallocateModifier(Context, Type, Modifier);
			}

			const FECsWeaponModifier& FLibrary::GetTypeChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier)
			{
				return CsWeaponManagerLibrary::GetChecked(Context, WorldContext)->GetModifierType(Context, Modifier);
			}

			ModifierResourceType* FLibrary::CreateCopyOfChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier)
			{
				return CsWeaponManagerLibrary::GetChecked(Context, WorldContext)->CreateCopyOfModifier(Context, Modifier);
			}

			ModifierResourceType* FLibrary::CreateCopyOfChecked(const FString& Context, const UObject* WorldContext, const ModifierResourceType* Modifier)
			{
				return CsWeaponManagerLibrary::GetChecked(Context, WorldContext)->CreateCopyOfModifier(Context, Modifier);
			}
		}
	}
}

namespace NCsWeapon
{
	namespace NManager
	{
		namespace NSpread
		{
			namespace NVariables
			{
				using SpreadVariablesResourceType = NCsWeapon::NProjectile::NSpread::NVariables::FResource;

				SpreadVariablesResourceType* FLibrary::Allocate(const FString& Context, const UObject* WorldContext)
				{
					typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;

					return WeaponManagerLibrary::GetChecked(Context, WorldContext)->AllocateSpreadVariables();
				}

				void FLibrary::Deallocate(const FString& Context, const UObject* WorldContext, SpreadVariablesResourceType* Resource)
				{
					typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;

					WeaponManagerLibrary::GetChecked(Context, WorldContext)->DeallocateSpreadVariables(Resource);
				}

				void FLibrary::Deallocate(const FString& Context, const UObject* WorldContext, const int32& Index)
				{
					typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;

					WeaponManagerLibrary::GetChecked(Context, WorldContext)->DeallocateSpreadVariables(Index);
				}
			}
		}
	}
}