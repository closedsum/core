// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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
#include "Managers/Singleton/CsGetManagerSingleton.h"
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
			typedef NCsWorld::FLibrary WorldLibrary;

			if (WorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
			{
				const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST_CHECKED(WorldContext, UObject, ICsGetManagerSingleton);

				return GetManagerSingleton->_getUObject();
			}

			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetAsObjectChecked(Context, WorldContext);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			if (WorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
			{
				if (const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST(WorldContext, UObject, ICsGetManagerSingleton))
				{
					return GetManagerSingleton->_getUObject();
				}
			}

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

		// Payload
		#pragma region

		#define PayloadType NCsWeapon::NPayload::IPayload
		#define PayloadImplType NCsWeapon::NPayload::FImpl

		PayloadType* FLibrary::AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type)
		{
			return GetChecked(Context, WorldContext)->AllocatePayload(Type);
		}

		PayloadImplType* FLibrary::AllocatePayloadImplChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type)
		{
			return GetChecked(Context, WorldContext)->AllocatePayload<PayloadImplType>(Type);
		}

		#undef PayloadType
		#undef PayloadImplType

		#pragma endregion Payload

		// Spawn
		#pragma region
	
		const FCsWeaponPooled* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, UObject* Owner, const FECsWeapon& Type)
		{
			typedef NCsWeapon::NPayload::FImpl PayloadImplType;

			PayloadImplType* Payload = AllocatePayloadImplChecked(Context, WorldContext, Type);

			Payload->Owner = Owner;
			Payload->Type  = Type;

			return GetChecked(Context, WorldContext)->Spawn(Type, Payload);
		}

		#define PayloadType NCsWeapon::NPayload::IPayload
		const FCsWeaponPooled* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, PayloadType* Payload)
		{
		#undef PayloadType

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

		FCsWeaponClass* FLibrary::GetSafeWeapon(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
			{
				return Manager_Weapon->GetSafeWeapon(Context, Type);
			}
			return nullptr;
		}

		FCsWeaponClass* FLibrary::GetWeaponChecked(const FString& Context, const UObject* WorldContext, const FECsWeaponClass& Type)
		{
			return GetChecked(Context, WorldContext)->GetWeaponChecked(Context, Type);
		}

		FCsWeaponClass* FLibrary::GetSafeWeapon(const FString& Context, const UObject* WorldContext, const FECsWeaponClass& Type, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
			{
				return Manager_Weapon->GetSafeWeapon(Context, Type);
			}
			return nullptr;
		}

		UClass* FLibrary::GetClassChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type)
		{
			return GetWeaponChecked(Context, WorldContext, Type)->GetClassChecked(Context);
		}

		UClass* FLibrary::GetSafeClass(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
			{
				FCsWeaponClass* Weapon = Manager_Weapon->GetSafeWeapon(Context, Type);

				return Weapon->GetClass();
			}
			return nullptr;
		}

		UClass* FLibrary::GetSafeClass(const FString& Context, const UObject* WorldContext, const FECsWeaponClass& Type, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
			{
				FCsWeaponClass* Weapon = Manager_Weapon->GetSafeWeapon(Context, Type);

				return Weapon->GetClass();
			}
			return nullptr;
		}

		bool FLibrary::SafeAddClass(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, UObject* Class, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
			{
				return Manager_Weapon->SafeAddClass(Context, Type, Class);
			}
			return false;
		}

		bool FLibrary::SafeAddClass(const FString& Context, const UObject* WorldContext, const FECsWeaponClass& Type, UObject* Class, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
			{
				return Manager_Weapon->SafeAddClass(Context, Type, Class);
			}
			return false;
		}

		#pragma endregion Class

		// Data
		#pragma region

		#define DataType NCsWeapon::NData::IData

		#define DataHandlerType NCsData::NManager::NHandler::TData
		#define DataInterfaceMapType NCsWeapon::NData::FInterfaceMap
		DataHandlerType<DataType, FCsData_WeaponPtr, DataInterfaceMapType>* FLibrary::GetSafeDataHandler(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
		#undef DataHandlerType
		#undef DataInterfaceMapType

			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
			{
				return Manager_Weapon->GetDataHandler();
			}
			return nullptr;
		}

		DataType* FLibrary::GetDataChecked(const FString& Context, const UObject* WorldContext, const FName& Name)
		{
			return GetChecked(Context, WorldContext)->GetDataChecked(Context, Name);
		}

		DataType* FLibrary::GetSafeData(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
			{
				return Manager_Weapon->GetSafeData(Context, Name);
			}
			return nullptr;
		}

		DataType* FLibrary::GetDataChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type)
		{
			return GetChecked(Context, WorldContext)->GetDataChecked(Context, Type);
		}

		DataType* FLibrary::GetSafeData(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
		{
			if (UCsManager_Weapon* Manager_Weapon = GetSafe(Context, WorldContext, Log))
			{
				return Manager_Weapon->GetSafeData(Context, Type);
			}
			return nullptr;
		}

		#undef DataType

		#pragma endregion Data

		namespace NModifier
		{
			#define ModifierResourceType NCsWeapon::NModifier::FResource
			#define ModifierType NCsWeapon::NModifier::IModifier
		
			ModifierResourceType* FLibrary::AllocateChecked(const FString& Context, const UObject* WorldContext, const FECsWeaponModifier& Type)
			{
				typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;

				return WeaponManagerLibrary::GetChecked(Context, WorldContext)->AllocateModifier(Type);
			}

			void FLibrary::DeallocateChecked(const FString& Context, const UObject* WorldContext, const FECsWeaponModifier& Type, ModifierResourceType* Modifier)
			{
				typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;

				WeaponManagerLibrary::GetChecked(Context, WorldContext)->DeallocateModifier(Context, Type, Modifier);
			}

			const FECsWeaponModifier& FLibrary::GetTypeChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier)
			{
				typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;

				return WeaponManagerLibrary::GetChecked(Context, WorldContext)->GetModifierType(Context, Modifier);
			}

			ModifierResourceType* FLibrary::CreateCopyOfChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier)
			{
				typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;

				return WeaponManagerLibrary::GetChecked(Context, WorldContext)->CreateCopyOfModifier(Context, Modifier);
			}

			ModifierResourceType* FLibrary::CreateCopyOfChecked(const FString& Context, const UObject* WorldContext, const ModifierResourceType* Modifier)
			{
				typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;

				return WeaponManagerLibrary::GetChecked(Context, WorldContext)->CreateCopyOfModifier(Context, Modifier);
			}

			#undef ModifierResourceType
			#undef ModifierType
		}

		namespace NSpread
		{
			namespace NVariables
			{
				#define SpreadVariablesResourceType NCsWeapon::NProjectile::NSpread::NVariables::FResource

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

				#undef SpreadVariablesResourceType
			}
		}
	}
}