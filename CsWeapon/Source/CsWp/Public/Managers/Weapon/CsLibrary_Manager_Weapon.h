// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "Types/CsTypes_Weapon.h"
#include "Modifier/Types/CsTypes_WeaponModifier.h"
// Log
#include "Utility/CsWpLog.h"

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

// NCsWeapon::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)
// NCsWeapon::NData::FInterfaceMap
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, FInterfaceMap)

// NCsWeapon::NModifier::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NModifier, FResource)
// NCsWeapon::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NModifier, IModifier)

// NCsWeapon::NProjectile::NSpread::NVariables::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NProjectile, NSpread, NVariables, FResource)

namespace NCsWeapon
{
	namespace NManager
	{
		struct CSWP_API FLibrary final
		{
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
			static UCsManager_Weapon* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

			/**
			* Safely get the reference to UCsManager_Weapon from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				UCsManager_Weapon.
			*/
			template<typename T>
			static T* GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning)
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

		#define PayloadType NCsWeapon::NPayload::IPayload
		#define PayloadImplType NCsWeapon::NPayload::FImpl

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

		#undef PayloadType
		#undef PayloadImplType

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

		#define PayloadType NCsWeapon::NPayload::IPayload

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

		#undef PayloadType

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
			static FCsWeaponClass* GetSafeWeapon(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

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
			static FCsWeaponClass* GetSafeWeapon(const FString& Context, const UObject* WorldContext, const FECsWeaponClass& Type, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);

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
		};

		namespace NModifier
		{
			struct CSWP_API FLibrary final
			{
			public:

			#define ModifierResourceType NCsWeapon::NModifier::FResource
			#define ModifierType NCsWeapon::NModifier::IModifier
		
				static ModifierResourceType* AllocateChecked(const FString& Context, const UObject* WorldContext, const FECsWeaponModifier& Type);

				static void DeallocateChecked(const FString& Context, const UObject* WorldContext, const FECsWeaponModifier& Type, ModifierResourceType* Modifier);

				static const FECsWeaponModifier& GetTypeChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier);

				static ModifierResourceType* CreateCopyOfChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier);

				static ModifierResourceType* CreateCopyOfChecked(const FString& Context, const UObject* WorldContext, const ModifierResourceType* Modifier);

			#undef ModifierResourceType
			#undef ModifierType
			};
		}

		namespace NSpread
		{
			namespace NVariables
			{
				struct CSWP_API FLibrary final
				{
				public:

				#define SpreadVariablesResourceType NCsWeapon::NProjectile::NSpread::NVariables::FResource

					static SpreadVariablesResourceType* Allocate(const FString& Context, const UObject* WorldContext);

					static void Deallocate(const FString& Context, const UObject* WorldContext, SpreadVariablesResourceType* Resource);

					static void Deallocate(const FString& Context, const UObject* WorldContext, const int32& Index);

				#undef SpreadVariablesResourceType
				};
			}
		}
	}
}