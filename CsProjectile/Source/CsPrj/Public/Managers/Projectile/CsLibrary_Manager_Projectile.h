// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/Projectile/CsSettings_Manager_Projectile.h"
#include "Modifier/Types/CsTypes_ProjectileModifier.h"
// Coroutine
#include "Coroutine/CsRoutineHandle.h"
// Projectile
#include "Variables/CsProjectile_Variables.h"
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

// NCsGrid::NUnfiorm::FGrid
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsGrid, NUniform, FGrid)

namespace NCsProjectile
{
	namespace NManager
	{
		struct CSPRJ_API FLibrary final
		{
		private:
			
			using DataType = NCsProjectile::NData::IData;
			using DataInterfaceMapType = NCsProjectile::NData::FInterfaceMap;
			using DataHandlerType = NCsData::NManager::NHandler::TData<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>;
			using PayloadType = NCsProjectile::NPayload::IPayload;

		// Print
		#pragma region
		public:

			static FString PrintObjectWithClass(const UCsManager_Projectile* Manager);

		#pragma endregion Print

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
			* Get the reference to UCsManager_Projectile from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_Projectile.
			*/
			template<typename T>
			static T* GetChecked(const FString& Context, const UObject* ContextObject)
			{
				UCsManager_Projectile* O = GetChecked(Context, ContextObject);
				T* Other				 = Cast<T>(O);

				checkf(Other, TEXT("%s: %s is NOT of type: %s."), *Context, *PrintObjectWithClass(O), *(T::StaticClass()->GetName()));
				return Other;
			}

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
			* @param Log			(optional)
			* return				UCsManager_Projectile.
			*/
			template<typename T>
			static T* GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning)
			{
				UCsManager_Projectile* O = GetSafe(Context, ContextObject, Log);

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

		// Allocate / Deallocate
		#pragma region
		public:

			static void QueueDeallocateAllChecked(const FString& Context, const UObject* WorldContext);

			static bool SafeQueueDeallocateAll(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

		#pragma endregion Allocate / Deallocate

		// Payload
		#pragma region
		public:

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

		#pragma endregion Payload

		// Spawn
		#pragma region
		public:

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

		#pragma endregion Spawn

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
			static DataHandlerType* GetSafeDataHandler(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

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

			/**
			* Get the Data as a UObject (implements interface: DataType (ICsData_Projectile)) associated with Type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			Weapon type.
			* @param Log			(optional)
			* return				Data that implements the interface: DataType (ICsData_Projectile).
			*/
			static UObject* GetSafeDataAsObject(const FString& Context, const UObject* WorldContext, const FECsProjectile& Type, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);

		#pragma endregion Data
		};

		namespace NModifier
		{
			struct CSPRJ_API FLibrary final
			{
			private:

				using ModifierResourceType = NCsProjectile::NModifier::NResource::FResource;
				using ModifierType = NCsProjectile::NModifier::IModifier;
				using AllocatedModifierType = NCsProjectile::NModifier::FAllocated;

			public:
		
				static ModifierResourceType* AllocateChecked(const FString& Context, const UObject* WorldContext, const FECsProjectileModifier& Type);

				static void DeallocateChecked(const FString& Context, const UObject* WorldContext, const FECsProjectileModifier& Type, ModifierResourceType* Modifier);

				static const FECsProjectileModifier& GetTypeChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier);

				static ModifierResourceType* CreateCopyOfChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier);

				static ModifierResourceType* CreateCopyOfChecked(const FString& Context, const UObject* WorldContext, const ModifierResourceType* Modifier);

				static void CreateCopyOfChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier, ModifierResourceType*& OutContainer, FECsProjectileModifier& OutType);

				/**
				* 
				* 
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param From
				* @param To
				*/
				static void CopyChecked(const FString& Context, const UObject* WorldContext, const TArray<ModifierType*>& From, TArray<ModifierResourceType*>& To);

				/**
				*
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param From
				* @param To
				*/
				static void CopyChecked(const FString& Context, const UObject* WorldContext, const TArray<ModifierType*>& From, TArray<AllocatedModifierType>& To);

				/**
				*
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param From
				* @param To
				*/
				static void CopyAndEmptyChecked(const FString& Context, const UObject* WorldContext, TArray<ModifierType*>& From, TArray<AllocatedModifierType>& To);

				/**
				*
				*
				* @param Context		The calling context.
				* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
				* @param From
				* @param To
				*/
				static void AddChecked(const FString& Context, const UObject* WorldContext, const TArray<ModifierType*>& From, TArray<AllocatedModifierType>& To);
			};
		}

		namespace NVariables
		{
			struct CSPRJ_API FLibrary final
			{
			private:

				using VariablesPayloadType = NCsProjectile::NVariables::NAllocate::FPayload;
				using VariablesType = NCsProjectile::NVariables::FVariables;

			public:

				static VariablesType* AllocateChecked(const FString& Context, const UObject* WorldContext, const VariablesPayloadType& Payload);

				static void DeallocateChecked(const FString& Context, const UObject* WorldContext, VariablesType* Variables);

				static bool SafeDeallocate(const FString& Context, const UObject* WorldContext, VariablesType* Variables, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);
			};
		}

		namespace NSearch
		{
			struct CSPRJ_API FLibrary final
			{
			private:

				using BoundsWorldType = NCsGrid::NUniform::FGrid;

			public:
	
				static BoundsWorldType* GetBoundsWorldChecked(const FString& Context, const UObject* WorldContext);
			};
		}

		namespace NOnHit
		{
			namespace NSpawn
			{
				namespace NProjectile
				{
					struct CSPRJ_API FLibrary final
					{
					private:

						using VariablesResourceType = NCsProjectile::NOnHit::NSpawn::NProjectile::NVariables::FResource;

					public:

						static VariablesResourceType* AllocateChecked(const FString& Context, const UObject* WorldContext);

						static void DeallocateChecked(const FString& Context, const UObject* WorldContext, VariablesResourceType* Resource);
						static void DeallocateChecked(const FString& Context, const UObject* WorldContext, const int32& Index);

						static void AddHandleChecked(const FString& Context, const UObject* WorldContext, const FCsRoutineHandle& Handle);
						
						static void RemoveHandleChecked(const FString& Context, const UObject* WorldContext, const FCsRoutineHandle& Handle);
					};

					namespace NSpread
					{
						struct CSPRJ_API FLibrary final
						{
						private:

							using VariablesResourceType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NVariables::FResource;

						public:

							static VariablesResourceType* AllocateChecked(const FString& Context, const UObject* WorldContext);

							static void DeallocateChecked(const FString& Context, const UObject* WorldContext, VariablesResourceType* Resource);
							static void DeallocateChecked(const FString& Context, const UObject* WorldContext, const int32& Index);
						};
					}
				}
			}
		}
	}
}

using CsProjectileManagerLibrary = NCsProjectile::NManager::FLibrary;
using CsPrjManagerLibrary = NCsProjectile::NManager::FLibrary;