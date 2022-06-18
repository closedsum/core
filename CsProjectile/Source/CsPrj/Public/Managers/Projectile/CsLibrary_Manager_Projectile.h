// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/Projectile/CsSettings_Manager_Projectile.h"
#include "Modifier/Types/CsTypes_ProjectileModifier.h"
// Coroutine
#include "Coroutine/CsRoutineHandle"
// Projectile
#include "Modifier/CsAllocated_ProjectileModifier.h"
// Log
#include "Utility/CsPrjLog.h"

class UObject;
class UCsManager_Projectile;

// NCsData::NManager::NHandler::TData
namespace NCsData {
	namespace NManager {
		namespace NHandler {
			template<typename InterfaceDataType, typename DataContainerType, typename DataInterfaceMapType>
			class TData;
		}
	}
}

// NCsProjectile::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NData, IData)
// NCsProjectile::NPayload::IPayload
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NPayload, IPayload)
// NCsProjectile::NData::FInterfaceMap
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NData, FInterfaceMap)

struct FCsProjectilePooled;

// NCsProjectile::NOnHit::NSpawn::NProjectile::NVariables::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsProjectile, NOnHit, NSpawn, NProjectile, NVariables, FResource)
// NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NVariables::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_6(NCsProjectile, NOnHit, NSpawn, NProjectile, NSpread, NVariables, FResource)

namespace NCsProjectile
{
	namespace NManager
	{
		struct CSPRJ_API FLibrary final
		{
		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Projectile from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_Projectile
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Projectile from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				Context for UCsManager_Projectile
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Projectile from a WorldContext.
			*
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_Projectile
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
			* Get the reference to UCsManager_Projectile from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_Projectile.
			*/
			static UCsManager_Projectile* GetChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get the reference to UCsManager_Projectile from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				UCsManager_Projectile.
			*/
			static UCsManager_Projectile* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

			/**
			* Safely get the reference to UCsManager_Projectile from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_Projectile.
			*/
			static UCsManager_Projectile* GetSafe(const UObject* WorldContext);

		#pragma endregion Get

		// Settings
		#pragma region
		public:

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return
			*/
			static const TArray<TArray<FECsProjectile>>& GetTypeMapToArrayChecked(const FString& Context, const UObject* WorldContext);


			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Key
			* @param Value
			*/
			static void SetAndAddTypeMapKeyValueChecked(const FString& Context, const UObject* WorldContext, const FECsProjectile& Key, const FECsProjectile& Value);

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Key
			* @param Value
			* @param Log			(optional)
			*/
			static void SafeSetAndAddTypeMapKeyValue(const FString& Context, const UObject* WorldContext, const FECsProjectile& Key, const FECsProjectile& Value, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

			/**
			* Add and create a pool in Manager_Character with the specified PoolParams.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* @param PoolParams
			*/
			static void AddPoolParamsChecked(const FString& Context, const UObject* WorldContext, const FECsProjectile& Type, const FCsSettings_Manager_Projectile_PoolParams& PoolParams);

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* @param PoolParams
			*/
			static bool SafeAddPoolParams(const FString& Context, const UObject* WorldContext, const FECsProjectile& Type, const FCsSettings_Manager_Projectile_PoolParams& PoolParams, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

		#pragma endregion Settings

		// Pool
		#pragma region
		public:

			/**
			* Safely determine whether a pool as been created for the appropriate Type.
			*
			* @oaran Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			Type of pool.
			* @param Log			(optional)
			* return				Whether the pool of Type has been created.
			*/
			static bool SafeHasPool(const FString& Context, const UObject* WorldContext, const FECsProjectile& Type, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

			/**
			* Get the pool for the appropriate Type.
			*  Pool is an array of containers holding references to objects that
			*  implement the interface: ICsProjectile.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			Type of pool to get.
			* @param OutPool		(out)
			* @param Log			(optional)
			* return				
			*/
			static bool GetSafePool(const FString& Context, const UObject* WorldContext, const FECsProjectile& Type, TArray<UObject*>& OutPool, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

		#pragma endregion Pool

		// Payload
		#pragma region
		public:

		#define PayloadType NCsProjectile::NPayload::IPayload

			/*
			* Allocate a Payload (used to Spawn a Projectile from Manager_Projectile).
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* return				Payload
			*/
			static PayloadType* AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, const FECsProjectile& Type);

			/*
			* Safely allocate a Payload (used to Spawn a Projectile from Manager_Projectile).
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* @param Log			(optional)
			* return				Payload
			*/
			static PayloadType* SafeAllocatePayload(const FString& Context, const UObject* WorldContext, const FECsProjectile& Type, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

		#undef PayloadType

		#pragma endregion Payload

		// Spawn
		#pragma region
		public:

		#define PayloadType NCsProjectile::NPayload::IPayload

			/**
			* Spawn a Projectile with the given Payload.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Payload
			* @param Log			(optional)
			* return
			*/
			static const FCsProjectilePooled* SpawnChecked(const FString& Context, const UObject* WorldContext, PayloadType* Payload);

		#undef PayloadType

		#pragma endregion Spawn

		// Data
		#pragma region
		public:

		#define DataType NCsProjectile::NData::IData

		#define DataHandlerType NCsData::NManager::NHandler::TData
		#define DataInterfaceMapType NCsProjectile::NData::FInterfaceMap

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			*/
			static DataHandlerType<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>* GetSafeDataHandler(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

		#undef DataHandlerType
		#undef DataInterfaceMapType

			/**
			* Get the Data (implements interface: DataType (NCsProjectile::NData::IData)) associated with Name of the weapon type.
			* "Checked" in regards to returning a valid pointer.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name			Name of the Weapon.
			* return				Data that implements the interface: DataType (NCsProjectile::NData::IData).
			*/
			static DataType* GetDataChecked(const FString& Context, const UObject* WorldContext, const FName& Name);

			/**
			* Safely get the Data (implements interface: DataType (NCsProjectile::NData::IData)) associated with Name of the weapon type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name			Name of the Weapon.
			* @param Log			(optional)
			* return				Data that implements the interface: DataType (NCsProjectile::NData::IData).
			*/
			static DataType* GetSafeData(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

			/**
			* Get the Data (implements interface: DataType (NCsProjectile::NData::IData)) associated with Type.
			* "Checked" in regards to returning a valid pointer.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			Weapon type.
			* return				Data that implements the interface: DataType (NCsProjectile::NData::IData).
			*/
			static DataType* GetDataChecked(const FString& Context, const UObject* WorldContext, const FECsProjectile& Type);

			/**
			* Get the Data (implements interface: DataType (NCsProjectile::NData::IData)) associated with Type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			Weapon type.
			* @param Log			(optional)
			* return				Data that implements the interface: DataType (NCsProjectile::NData::IData).
			*/
			static DataType* GetSafeData(const FString& Context, const UObject* WorldContext, const FECsProjectile& Type, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

		#undef DataType

		#pragma endregion Data

		// Modifier
		#pragma region
		public:
		
		#define ModifierResourceType NCsProjectile::NModifier::FResource
		#define ModifierType NCsProjectile::NModifier::IModifier
		#define AllocatedModifierType NCsProjectile::NModifier::FAllocated
		
			static ModifierResourceType* AllocateModifierChecked(const FString& Context, const UObject* WorldContext, const FECsProjectileModifier& Type);

			static void DeallocateModifierChecked(const FString& Context, const UObject* WorldContext, const FECsProjectileModifier& Type, ModifierResourceType* Modifier);

			static const FECsProjectileModifier& GetModifierTypeChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier);

			static ModifierResourceType* CreateCopyOfModifierChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier);

			static ModifierResourceType* CreateCopyOfModifierChecked(const FString& Context, const UObject* WorldContext, const ModifierResourceType* Modifier);

			static void CreateCopyOfModifierChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier, ModifierResourceType*& OutContainer, FECsProjectileModifier& OutType);

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param From
			* @param To
			*/
			static void CreateCopyOfModifiersChecked(const FString& Context, const UObject* WorldContext, const TArray<ModifierType*>& From, TArray<ModifierResourceType*>& To);

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param From
			* @param To
			*/
			static void CreateCopyOfModifiersChecked(const FString& Context, const UObject* WorldContext, const TArray<ModifierType*>& From, TArray<AllocatedModifierType>& To);

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param From
			* @param To
			*/
			static void CreateCopyOfAndAddModifiersChecked(const FString& Context, const UObject* WorldContext, const TArray<ModifierType*>& From, TArray<AllocatedModifierType>& To);

		#undef ModifierResourceType
		#undef ModifierType
		#undef AllocatedModifierType

		#pragma endregion Modifier
		};

		namespace NOnHit
		{
			namespace NSpawn
			{
				namespace NProjectile
				{
					struct CSPRJ_API FLibrary final
					{
					public:

					#define VariablesResourceType NCsProjectile::NOnHit::NSpawn::NProjectile::NVariables::FResource

						static VariablesResourceType* AllocateVariablesChecked(const FString& Context, const UObject* WorldContext);

						static void DeallocateVariablesChecked(const FString& Context, const UObject* WorldContext, VariablesResourceType* Resource);
						static void DeallocateVariablesChecked(const FString& Context, const UObject* WorldContext, const int32& Index);

					#undef VariablesResourceType

						static void AddHandleChecked(const FString& Context, const UObject* WorldContext, const FCsRoutineHandle& Handle);
						
						static void RemoveHandleChecked(const FString& Context, const UObject* WorldContext, const FCsRoutineHandle& Handle);
					};

					namespace NSpread
					{
						struct CSPRJ_API FLibrary final
						{
						public:

						#define VariablesResourceType NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NVariables::FResource

							static VariablesResourceType* AllocateVariablesChecked(const FString& Context, const UObject* WorldContext);

							static void DeallocateVariablesChecked(const FString& Context, const UObject* WorldContext, VariablesResourceType* Resource);
							static void DeallocateVariablesChecked(const FString& Context, const UObject* WorldContext, const int32& Index);

						#undef VariablesResourceType
						};
					}
				}
			}
		}
	}
}