// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "CsMacro_Log.h"
#include "CsMacro_Cached.h"
#include "Types/CsTypes_Weapon.h"
#include "Modifier/Types/CsTypes_WeaponModifier.h"

class UObject;
class UCsManager_Weapon;
struct FCsWeaponPooled;

// NCsWeapon::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NPayload, IPayload)
// NCsWeapon::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NPayload, FImpl)

struct FCsWeapon;
class ICsWeapon;
struct FCsWeaponClass;
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

// DataType (NCsWeapon::NData::IData)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)
// DataInterfaceMapType (NCsWeapon::NData::FInterfaceMap)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, FInterfaceMap)

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_2(NCsWeapon, NManager, Library)

namespace NCsWeapon
{
	namespace NManager
	{
		struct CSWP_API FLibrary final
		{
		private:

			CS_DECLARE_STATIC_LOG_LEVEL

			CS_USING_CACHED_FUNCTION_NAME_NESTED_2(NCsWeapon, NManager, Library);

			using DataType = NCsWeapon::NData::IData;
			using DataInterfaceMapType = NCsWeapon::NData::FInterfaceMap;
			using DataHandlerType = NCsData::NManager::NHandler::TData<DataType, FCsData_WeaponPtr, DataInterfaceMapType>;
			using PayloadType = NCsWeapon::NPayload::IPayload;
			using PayloadImplType = NCsWeapon::NPayload::FImpl;

		// Print
		#pragma region
		public:

			static FString PrintObjectWithClass(const UCsManager_Weapon* Manager);

		#pragma endregion Print

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
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL) { return nullptr; }
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
			* Get the reference to UCsManager_Weapon from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_Weapon.
			*/
			template<typename T>
			static T* GetChecked(const FString& Context, const UObject* ContextObject)
			{
				UCsManager_Weapon* O = GetChecked(Context, ContextObject);
				T* Other			 = Cast<T>(O);

				checkf(Other, TEXT("%s: %s is NOT of type: %s."), *Context, *PrintObjectWithClass(O), *(T::StaticClass()->GetName()));
				return Other;
			}

			/**
			* Safely get the reference to UCsManager_Weapon from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				UCsManager_Weapon.
			*/
			static UCsManager_Weapon* GetSafe(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			/**
			* Safely get the reference to UCsManager_Weapon from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				UCsManager_Weapon.
			*/
			template<typename T>
			static T* GetSafe(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL)
			{
				UCsManager_Weapon* O = GetSafe(Context, ContextObject, Log);

				if (!O)
					return nullptr;

				T* Other = Cast<T>(O);

				if (!Other)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: %s is NOT of type: %s."), *Context, *PrintObjectWithClass(O), *(T::StaticClass()->GetName())));
				}
				return Other;
			}

			/**
			* Safely get the reference to UCsManager_Weapon from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_Weapon.
			*/
			static UCsManager_Weapon* GetSafe(const UObject* WorldContext);

		#pragma endregion Get

		// Payload
		#pragma region
		public:

			/*
			* Allocate a Payload (used to Spawn an Weapon from Manager_Weapon).
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* return				Payload
			*/
			static PayloadType* AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type);

			/*
			* Allocate a Payload (used to Spawn an Weapon from Manager_Weapon).
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* return				Payload
			*/
			static PayloadImplType* AllocatePayloadImplChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type);

		#pragma endregion Payload

		// Spawn
		#pragma region
		public:

			/**
			* Spawn an Weapon, object that implements the interface: ICsWeapon, and pass the Owner and Type.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Owner
			* @param Type
			* return
			*/
			static const FCsWeaponPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, UObject* Owner, const FECsWeapon& Type);

			/**
			* Spawn an Weapon, object that implements the interface: ICsWeapon, and pass the Owner and Type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* @param Payload
			* return
			*/
			static const FCsWeaponPooled* SpawnChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, PayloadType* Payload);

		#pragma endregion Spawn

		// Destroy
		#pragma region
		public:

		/**
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Type
		* @param Weapon
		* return
		*/
		static bool DestroyChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, ICsWeapon* Weapon);

		/**
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Type
		* @param Weapon
		* return
		*/
		static bool DestroyChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, FCsWeaponPooled* Weapon);

		#pragma endregion Destroy

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
			static FCsWeaponClass* GetWeaponChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type);

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
			static FCsWeaponClass* GetSafeWeapon(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

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
			static FCsWeaponClass* GetWeaponChecked(const FString& Context, const UObject* WorldContext, const FECsWeaponClass& Type);

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
			static FCsWeaponClass* GetSafeWeapon(const FString& Context, const UObject* WorldContext, const FECsWeaponClass& Type, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

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
			static UClass* GetSafeClass(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			/**
			* Safely get the Class associated with WeaponClass of Type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* @param Log			(optional)
			* return				UClass associated with Type.
			*/
			static UClass* GetSafeClass(const FString& Context, const UObject* WorldContext, const FECsWeaponClass& Type, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

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
			static bool SafeAddClass(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, UObject* Class, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

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
			static bool SafeAddClass(const FString& Context, const UObject* WorldContext, const FECsWeaponClass& Type, UObject* Class, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		#pragma endregion Class

		// Data
		#pragma region
		public:

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			*/
			static DataHandlerType* GetSafeDataHandler(const FString& Context, const UObject* WorldContext, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

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
			static DataType* GetSafeData(const FString& Context, const UObject* WorldContext, const FName& Name, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

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
			static DataType* GetSafeData(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		#pragma endregion Data
		};
	}
}

using CsWeaponManagerLibrary = NCsWeapon::NManager::FLibrary;

// ModifierResourceType (NCsWeapon::NModifier::NResource::FResource)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsWeapon, NModifier, NResource, FResource)
// ModifierType (NCsWeapon::NModifier::IModifier)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NModifier, IModifier)

namespace NCsWeapon
{
	namespace NManager
	{
		namespace NModifier
		{
			struct CSWP_API FLibrary final
			{
			private:

				using ModifierResourceType = NCsWeapon::NModifier::NResource::FResource;
				using ModifierType = NCsWeapon::NModifier::IModifier;

			public:
		
				static ModifierResourceType* AllocateChecked(const FString& Context, const UObject* WorldContext, const FECsWeaponModifier& Type);

				static void DeallocateChecked(const FString& Context, const UObject* WorldContext, const FECsWeaponModifier& Type, ModifierResourceType* Modifier);

				static const FECsWeaponModifier& GetTypeChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier);

				static ModifierResourceType* CreateCopyOfChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier);

				static ModifierResourceType* CreateCopyOfChecked(const FString& Context, const UObject* WorldContext, const ModifierResourceType* Modifier);
			};
		}
	}
}

// SpreadVariablesResourceType (NCsWeapon::NProjectile::NSpread::NVariables::FResource)
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NProjectile, NSpread, NVariables, FResource)

namespace NCsWeapon
{
	namespace NManager
	{
		namespace NSpread
		{
			namespace NVariables
			{
				struct CSWP_API FLibrary final
				{
				private:

					using SpreadVariablesResourceType = NCsWeapon::NProjectile::NSpread::NVariables::FResource;

				public:

					static SpreadVariablesResourceType* Allocate(const FString& Context, const UObject* WorldContext);

					static void Deallocate(const FString& Context, const UObject* WorldContext, SpreadVariablesResourceType* Resource);

					static void Deallocate(const FString& Context, const UObject* WorldContext, const int32& Index);
				};
			}
		}
	}
}