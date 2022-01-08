// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Weapon.h"
#include "Modifier/Types/CsTypes_WeaponModifier.h"
// Log
#include "Utility/CsWpLog.h"

class UObject;
class UCsManager_Weapon;
struct FCsWeapon;
class UClass;

// NCsData::NManager::NHandler::TData
namespace NCsData {
	namespace NManager {
		namespace NHandler {
			template<typename InterfaceDataType, typename DataContainerType, typename DataInterfaceMapType>
			class TData;
		}
	}
}

// NCsWeapon::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)
// NCsWeapon::NData::FInterfaceMap
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, FInterfaceMap)

// NCsWeapon::NModifier::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NModifier, FResource)
// NCsWeapon::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NModifier, IModifier)

namespace NCsWeapon
{
	namespace NManager
	{
		struct CSWP_API FLibrary final
		{
		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Weapon from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_Weapon
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Weapon from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				Context for UCsManager_Weapon
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Weapon from a WorldContext.
			*
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_Weapon
			*/
			static UObject* GetSafeContextRoot(const UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region
		public:

			/**
			* Get the reference to UCsManager_Weapon from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_Weapon.
			*/
			static UCsManager_Weapon* GetChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get the reference to UCsManager_Weapon from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				UCsManager_Weapon.
			*/
			static UCsManager_Weapon* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

			/**
			* Safely get the reference to UCsManager_Weapon from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_Weapon.
			*/
			static UCsManager_Weapon* GetSafe(const UObject* WorldContext);

		#pragma endregion Get

		// Class
		#pragma region
		public:

			/**
			* Get the Weapon container (Interface (ICsWeapon), UObject, and / or UClass) associated
			* with the weapon Type.
			* "Checked" in regards to returning a valid pointer.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			Type of the weapon.
			* return				Weapon container (Interface (ICsWeapon), UObject, and / or UClass).
			*/
			static FCsWeapon* GetWeaponChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type);

			/**
			* Safely get the Weapon container (Interface (ICsWeapon), UObject, and / or UClass) associated
			* with the weapon Type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			Type of the weapon.
			* @param Log			(optional)
			* return				Weapon container (Interface (ICsWeapon), UObject, and / or UClass).
			*/
			static FCsWeapon* GetSafeWeapon(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

			/**
			* Get the Weapon container (Interface (ICsWeapon), UObject, and / or UClass) associated
			* with the weapon class Type.
			* "Checked" in regards to returning a valid pointer.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			Class type of the weapon.
			* return				Weapon container (Interface (ICsWeapon), UObject, and / or UClass).
			*/
			static FCsWeapon* GetWeaponChecked(const FString& Context, const UObject* WorldContext, const FECsWeaponClass& Type);

			/**
			* Safely get the Weapon container (Interface (ICsWeapon), UObject, and / or UClass) associated
			* with the weapon class Type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			Class type of the weapon.
			* @param Log			(optional)
			* return				Weapon container (Interface (ICsWeapon), UObject, and / or UClass).
			*/
			static FCsWeapon* GetSafeWeapon(const FString& Context, const UObject* WorldContext, const FECsWeaponClass& Type, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

			/**
			* Get the Class associated with Weapon of Type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* return				UClass associated with Type.
			*/
			static UClass* GetClassChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type);

			/**
			* Safely get the Class associated with Weapon of Type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* @param Log			(optional)
			* return				UClass associated with Type.
			*/
			static UClass* GetSafeClass(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

			/**
			* Safely get the Class associated with WeaponClass of Type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* @param Log			(optional)
			* return				UClass associated with Type.
			*/
			static UClass* GetSafeClass(const FString& Context, const UObject* WorldContext, const FECsWeaponClass& Type, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

			/**
			* Safely add the Class for Type to Manager_Weapon's ClassHandler.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* @param Class
			* @param Log			(optional)
			* return				Whether the Class was successfully added for Type.
			*/
			static bool SafeAddClass(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, UObject* Class, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

			/**
			* Safely add the Class for Class Type to Manager_Weapon's ClassHandler.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* @param Class
			* @param Log			(optional)
			* return				Whether the Class was successfully added for Class Type.
			*/
			static bool SafeAddClass(const FString& Context, const UObject* WorldContext, const FECsWeaponClass& Type, UObject* Class, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

		#pragma endregion Class

		// Data
		#pragma region
		public:

		#define DataType NCsWeapon::NData::IData

		#define DataHandlerType NCsData::NManager::NHandler::TData
		#define DataInterfaceMapType NCsWeapon::NData::FInterfaceMap

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			*/
			static DataHandlerType<DataType, FCsData_WeaponPtr, DataInterfaceMapType>* GetSafeDataHandler(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

		#undef DataHandlerType
		#undef DataInterfaceMapType

			/**
			* Get the Data (implements interface: NCsWeapon::NData::IData) associated with Name of the weapon type.
			* "Checked" in regards to returning a valid pointer.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name			Name of the Weapon.
			* return				Data that implements the interface: NCsWeapon::NData::IData.
			*/
			static DataType* GetDataChecked(const FString& Context, const UObject* WorldContext, const FName& Name);

			/**
			* Safely get the Data (implements interface: NCsWeapon::NData::IData) associated with Name of the weapon type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name			Name of the Weapon.
			* @param Log			(optional)
			* return				Data that implements the interface: NCsWeapon::NData::IData.
			*/
			static DataType* GetSafeData(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

			/**
			* Get the Data (implements interface: NCsWeapon::NData::IData) associated with Type.
			* "Checked" in regards to returning a valid pointer.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			Weapon type.
			* return				Data that implements the interface: NCsWeapon::NData::IData.
			*/
			static DataType* GetDataChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type);

			/**
			* Get the Data (implements interface: NCsWeapon::NData::IData) associated with Type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			Weapon type.
			* @param Log			(optional)
			* return				Data that implements the interface: NCsWeapon::NData::IData.
			*/
			static DataType* GetSafeData(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

		#undef DataType

		#pragma endregion Data

		// Modifier
		#pragma region
		public:
		
		#define ModifierResourceType NCsWeapon::NModifier::FResource
		#define ModifierType NCsWeapon::NModifier::IModifier
		
			static ModifierResourceType* AllocateModifierChecked(const FString& Context, const UObject* WorldContext, const FECsWeaponModifier& Type);

			static void DeallocateModifierChecked(const FString& Context, const UObject* WorldContext, const FECsWeaponModifier& Type, ModifierResourceType* Modifier);

			static const FECsWeaponModifier& GetModifierTypeChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier);

			static ModifierResourceType* CreateCopyOfModifierChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier);

			static ModifierResourceType* CreateCopyOfModifierChecked(const FString& Context, const UObject* WorldContext, const ModifierResourceType* Modifier);

		#undef ModifierResourceType
		#undef ModifierType

		#pragma endregion Modifier
		};
	}
}