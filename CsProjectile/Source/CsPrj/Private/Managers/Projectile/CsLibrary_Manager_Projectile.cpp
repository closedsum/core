// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Projectile/CsLibrary_Manager_Projectile.h"

// Types
#include "CsMacro_Misc.h"
// Managers
#include "Managers/Projectile/CsManager_Projectile.h"
// Library
#include "Data/CsLibrary_Data_Projectile.h"
#include "Modifier/CsLibrary_ProjectileModifier.h"
#include "Library/CsLibrary_Valid.h"
// Projectile
#include "Payload/CsPayload_Projectile.h"
#include "Modifier/Copy/CsProjectileModifier_Copy.h"

#if WITH_EDITOR
// Library
	// Common
#include "Game/CsLibrary_GameState.h"
#include "Library/CsLibrary_World.h"
// Managers
#include "Singleton/CsGetManagerSingleton.h"
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

		using DataType = NCsProjectile::NData::IData;
		using DataInterfaceMapType = NCsProjectile::NData::FInterfaceMap;
		using DataHandlerType = NCsData::NManager::NHandler::TData<DataType, FCsData_ProjectilePtr, DataInterfaceMapType>;	
		using PayloadType = NCsProjectile::NPayload::IPayload;

		// Print
		#pragma region

		FString FLibrary::PrintObjectWithClass(const UCsManager_Projectile* Manager)
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

			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetAsObjectChecked(Context, WorldContext);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
			{
				if (const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST(WorldContext, UObject, ICsGetManagerSingleton))
				{
					return GetManagerSingleton->_getUObject();
				}
				return nullptr;
			}

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

		const TArray<TArray<FECsProjectile>>& FLibrary::GetTypeMapToArrayChecked(const FString& Context, const UObject* WorldContext)
		{
			return GetChecked(Context, WorldContext)->GetTypeMapToArray();
		}

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

		void FLibrary::AddPoolParamsChecked(const FString& Context, const UObject* WorldContext, const FECsProjectile& Type, const FCsSettings_Manager_Projectile_PoolParams& PoolParams)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectile, Type);

			CS_IS_VALID_CHECKED(PoolParams);

			UCsManager_Projectile* Manager_Projectile = GetChecked(Context, WorldContext);

			// Get Class
			const FECsProjectileClass& ClassType = PoolParams.Class;
			FCsProjectilePooled* Projectile		 = Manager_Projectile->GetProjectileChecked(Context, ClassType);

			check(Projectile->GetClassChecked(Context));

			Manager_Projectile->AddPoolParams(Type, PoolParams);
		}

		bool FLibrary::SafeAddPoolParams(const FString& Context, const UObject* WorldContext, const FECsProjectile& Type, const FCsSettings_Manager_Projectile_PoolParams& PoolParams, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			CS_IS_ENUM_STRUCT_VALID(EMCsProjectile, FECsProjectile, Type)

			CS_IS_VALID(PoolParams)

			if (UCsManager_Projectile* Manager_Projectile = GetSafe(Context, WorldContext, Log))
			{
				// Get Class
				const FECsProjectileClass& ClassType = PoolParams.Class;
				FCsProjectilePooled* Projectile		 = Manager_Projectile->GetSafeProjectile(Context, ClassType);

				if (!Projectile)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Projectile class from ClassType: %s."), *Context, ClassType.ToChar()));
					return false;
				}

				UClass* Class = Projectile->GetClass();

				if (!Class)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get class for Type: %s ClassType: %s."), *Context, Type.ToChar(), ClassType.ToChar()));
					return false;
				}
				Manager_Projectile->AddPoolParams(Type, PoolParams);
				return true;
			}
			return false;
		}

		#pragma endregion Settings

		// Pool
		#pragma region
		
		bool FLibrary::SafeHasPool(const FString& Context, const UObject* WorldContext, const FECsProjectile& Type, void(*Log)(const FString&) /*=&FCLog::Warning*/)
		{
			if (UCsManager_Projectile* Manager_Projectile = GetSafe(Context, WorldContext, Log))
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsProjectile, FECsProjectile, Type)

				return Manager_Projectile->HasPool(Type);
			}
			return false;
		}

		bool FLibrary::GetSafePool(const FString& Context, const UObject* WorldContext, const FECsProjectile& Type, TArray<UObject*>& OutPool, void(*Log)(const FString&) /*=&FCLog::Warning*/)
		{
			if (UCsManager_Projectile* Manager_Projectile = GetSafe(Context, WorldContext, Log))
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsProjectile, FECsProjectile, Type)

				if (Manager_Projectile->HasPool(Type))
				{
					const TArray<FCsProjectilePooled*>& Pool = Manager_Projectile->GetPool(Type);

					OutPool.Reset(Pool.Num());

					for (const FCsProjectilePooled* Projectile : Pool)
					{
						OutPool.Add(Projectile->GetSafeObject());
					}
					return true;
				}

				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No Pool of Type: %s exists."), *Context, Type.ToChar()));
				return false;
			}
			return false;
		}

		#pragma endregion Pool

		// Allocate / Deallocate
		#pragma region
		
		void FLibrary::QueueDeallocateAllChecked(const FString& Context, const UObject* WorldContext)
		{
			GetChecked(Context, WorldContext)->QueueDeallocateAll();
		}

		bool FLibrary::SafeQueueDeallocateAll(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			if (UCsManager_Projectile* Manager_Projectile = GetSafe(Context, WorldContext))
			{
				Manager_Projectile->QueueDeallocateAll();
				return true;
			}
			return false;
		}

		#pragma endregion Allocate / Deallocate

		// Payload
		#pragma region

		PayloadType* FLibrary::AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, const FECsProjectile& Type)
		{
			return GetChecked(Context, WorldContext)->AllocatePayload(Type);
		}

		PayloadType* FLibrary::SafeAllocatePayload(const FString& Context, const UObject* WorldContext, const FECsProjectile& Type, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			if (UCsManager_Projectile* Manager_Projectile = GetSafe(Context, WorldContext, Log))
			{
				CS_IS_ENUM_STRUCT_VALID_RET_NULL(EMCsProjectile, FECsProjectile, Type)

				return Manager_Projectile->AllocatePayload(Type);
			}
			return nullptr;
		}

		#pragma endregion Payload

		// Spawn
		#pragma region

		const FCsProjectilePooled* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, PayloadType* Payload)
		{
			return GetChecked(Context, WorldContext)->Spawn(Payload->GetType(), Payload);
		}

		#pragma endregion Spawn

		// Data
		#pragma region

		DataHandlerType* FLibrary::GetSafeDataHandler(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			if (UCsManager_Projectile* Manager_Projectile = GetSafe(Context, WorldContext, Log))
			{
				return Manager_Projectile->GetDataHandler();
			}
			return nullptr;
		}

		DataType* FLibrary::GetDataChecked(const FString& Context, const UObject* WorldContext, const FName& Name)
		{
			return GetChecked(Context, WorldContext)->GetDataChecked(Context, Name);
		}

		DataType* FLibrary::GetSafeData(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			if (UCsManager_Projectile* Manager_Projectile = GetSafe(Context, WorldContext, Log))
			{
				return Manager_Projectile->GetSafeData(Context, Name);
			}
			return nullptr;
		}

		DataType* FLibrary::GetDataChecked(const FString& Context, const UObject* WorldContext, const FECsProjectile& Type)
		{
			return GetChecked(Context, WorldContext)->GetDataChecked(Context, Type);
		}

		DataType* FLibrary::GetSafeData(const FString& Context, const UObject* WorldContext, const FECsProjectile& Type, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			if (UCsManager_Projectile* Manager_Projectile = GetSafe(Context, WorldContext, Log))
			{
				return Manager_Projectile->GetSafeData(Context, Type);
			}
			return nullptr;
		}

		UObject* FLibrary::GetSafeDataAsObject(const FString& Context, const UObject* WorldContext, const FECsProjectile& Type, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			if (UCsManager_Projectile* Manager_Projectile = GetSafe(Context, WorldContext, Log))
			{
				if (DataType* Data = Manager_Projectile->GetSafeData(Context, Type))
				{
					if (UObject* O = Data->_getUObject())
					{
						return O;
					}
					else
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get UObject for %s associated with Type: %s"), *Context, *CsPrjDataLibrary::PrintDataAndClass(Data), Type.ToChar()));
					}
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Data associated with Type: %s"), *Context, Type.ToChar()));
				}
			}
			return nullptr;
		}

		#undef DataType

		#pragma endregion Data

		namespace NModifier
		{
			using ModifierResourceType = NCsProjectile::NModifier::NResource::FResource;
			using ModifierType = NCsProjectile::NModifier::IModifier;
			using AllocatedModifierType = NCsProjectile::NModifier::FAllocated;
		
			ModifierResourceType* FLibrary::AllocateChecked(const FString& Context, const UObject* WorldContext, const FECsProjectileModifier& Type)
			{
				return CsPrjManagerLibrary::GetChecked(Context, WorldContext)->AllocateModifier(Type);
			}

			void FLibrary::DeallocateChecked(const FString& Context, const UObject* WorldContext, const FECsProjectileModifier& Type, ModifierResourceType* Modifier)
			{
				CsPrjManagerLibrary::GetChecked(Context, WorldContext)->DeallocateModifier(Context, Type, Modifier);
			}

			const FECsProjectileModifier& FLibrary::GetTypeChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier)
			{
				return CsPrjManagerLibrary::GetChecked(Context, WorldContext)->GetModifierType(Context, Modifier);
			}

			ModifierResourceType* FLibrary::CreateCopyOfChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier)
			{
				UCsManager_Projectile* Manager_Projectile = CsPrjManagerLibrary::GetChecked(Context, WorldContext);

				const FECsProjectileModifier& Type  = CsProjectileModifierLibrary::GetTypeChecked(Context, Modifier);
				ModifierResourceType* Container		= Manager_Projectile->AllocateModifier(Type);
				ModifierType* Copy					= Container->Get();

				typedef NCsProjectile::NModifier::NCopy::ICopy CopyType;

				CopyType* ICopy = CsProjectileModifierLibrary::GetInterfaceChecked<CopyType>(Context, Copy);

				ICopy->Copy(Modifier);

				return Container;
			}

			ModifierResourceType* FLibrary::CreateCopyOfChecked(const FString& Context, const UObject* WorldContext, const ModifierResourceType* Modifier)
			{
				CS_IS_PTR_NULL_CHECKED(Modifier)

				return CreateCopyOfChecked(Context, WorldContext, Modifier->Get());
			}

			void FLibrary::CreateCopyOfChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier, ModifierResourceType*& OutContainer, FECsProjectileModifier& OutType)
			{
				UCsManager_Projectile* Manager_Projectile = CsPrjManagerLibrary::GetChecked(Context, WorldContext);

				OutType				= CsProjectileModifierLibrary::GetTypeChecked(Context, Modifier);
				OutContainer		= Manager_Projectile->AllocateModifier(OutType);
				ModifierType* Copy	= OutContainer->Get();

				typedef NCsProjectile::NModifier::NCopy::ICopy CopyType;

				CopyType* ICopy = CsProjectileModifierLibrary::GetInterfaceChecked<CopyType>(Context, Copy);

				ICopy->Copy(Modifier);
			}

			void FLibrary::CopyChecked(const FString& Context, const UObject* WorldContext, const TArray<ModifierType*>& From, TArray<ModifierResourceType*>& To)
			{
				CS_IS_TARRAY_ANY_NULL_CHECKED(From, ModifierType)

				To.Reset(FMath::Max(To.Max(), From.Num()));

				for (const ModifierType* Modifier : From)
				{
					To.Add(CreateCopyOfChecked(Context, WorldContext, Modifier));
				}
			}

			void FLibrary::CopyChecked(const FString& Context, const UObject* WorldContext, const TArray<ModifierType*>& From, TArray<AllocatedModifierType>& To)
			{
				UObject* ContextRoot = CsPrjManagerLibrary::GetContextRootChecked(Context, WorldContext);

				CS_IS_TARRAY_ANY_NULL_CHECKED(From, ModifierType)

				To.Reset(FMath::Max(To.Max(), From.Num()));

				for (const ModifierType* Modifier : From)
				{
					AllocatedModifierType& Allocated = To.AddDefaulted_GetRef();
					Allocated.Copy(ContextRoot, Modifier);
				}
			}

			void FLibrary::CopyAndEmptyChecked(const FString& Context, const UObject* WorldContext, TArray<ModifierType*>& From, TArray<AllocatedModifierType>& To)
			{
				UObject* ContextRoot = CsPrjManagerLibrary::GetContextRootChecked(Context, WorldContext);

				CS_IS_TARRAY_ANY_NULL_CHECKED(From, ModifierType)

				To.Reset(FMath::Max(To.Max(), From.Num()));

				const int32 Count = From.Num();

				for (int32 I = Count - 1; I >= 0; --I)
				{
					const ModifierType* Modifier = From[I];

					AllocatedModifierType& Allocated = To.AddDefaulted_GetRef();
					Allocated.Copy(ContextRoot, Modifier);

					From.RemoveAt(I, 1, false);
				}
			}

			void FLibrary::AddChecked(const FString& Context, const UObject* WorldContext, const TArray<ModifierType*>& From, TArray<AllocatedModifierType>& To)
			{
				UObject* ContextRoot = CsPrjManagerLibrary::GetContextRootChecked(Context, WorldContext);

				CS_IS_TARRAY_ANY_NULL_CHECKED(From, ModifierType)

				const int32 FromCount = From.Num();
				const int32 ToCount	  = To.Num();
				const int32 Total	  = FromCount + ToCount;

				if (To.Max() >= Total)
				{
					for (int32 I = ToCount; I < Total; ++I)
					{
						AllocatedModifierType& Allocated = To.AddDefaulted_GetRef();
						Allocated.Copy(ContextRoot, From[I - ToCount]);
					}
				}
				else
				{
					static TArray<AllocatedModifierType> Temp;

					Temp.Reset(FMath::Max(Temp.Max(), ToCount));
					Temp.AddDefaulted(ToCount);

					for (int32 I = 0; I < ToCount; ++I)
					{
						Temp[I].Copy(To[I]);
					}

					To.Reset(Total);
					To.AddDefaulted(Total);

					for (int32 I = 0; I < Total; ++I)
					{
						if (I < ToCount)
						{
							Temp[I].Transfer(To[I]);
						}
						else
						{
							To[I].Copy(ContextRoot, From[I - ToCount]);
						}
					}
					Temp.Reset(Temp.Max());
				}
			}
		}
	}
}

namespace NCsProjectile
{
	namespace NManager
	{
		namespace NVariables
		{
			using VariablesPayloadType = NCsProjectile::NVariables::NAllocate::FPayload;
			using VariablesType = NCsProjectile::NVariables::FVariables;

			VariablesType* FLibrary::AllocateChecked(const FString& Context, const UObject* WorldContext, const VariablesPayloadType& Payload)
			{
				return CsPrjManagerLibrary::GetChecked(Context, WorldContext)->AllocateVariablesChecked(Context, Payload);
			}

			void FLibrary::DeallocateChecked(const FString& Context, const UObject* WorldContext, VariablesType* Variables)
			{
				CsPrjManagerLibrary::GetChecked(Context, WorldContext)->DeallocateVariablesChecked(Context, Variables);
			}
			
			bool FLibrary::SafeDeallocate(const FString& Context, const UObject* WorldContext, VariablesType* Variables, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
			{
				CS_IS_PTR_NULL(Variables)

				if (UCsManager_Projectile* Manager_Projectile = CsPrjManagerLibrary::GetSafe(Context, WorldContext, Log))
				{
					Manager_Projectile->DeallocateVariablesChecked(Context, Variables);
					return true;
				}
				return false;
			}
		}
	}
}

namespace NCsProjectile
{
	namespace NManager
	{
		namespace NSearch
		{
			using BoundsWorldType = NCsGrid::NUniform::FGrid;

			BoundsWorldType* FLibrary::GetBoundsWorldChecked(const FString& Context, const UObject* WorldContext)
			{
				return CsPrjManagerLibrary::GetChecked(Context, WorldContext)->GetBoundsWorld();
			}
		}
	}
}

namespace NCsProjectile
{
	namespace NManager
	{
		namespace NOnHit
		{
			namespace NSpawn
			{
				namespace NProjectile
				{
					using VariablesResourceType = NCsProjectile::NOnHit::NSpawn::NProjectile::NVariables::FResource;

					VariablesResourceType* FLibrary::AllocateChecked(const FString& Context, const UObject* WorldContext)
					{
						return CsPrjManagerLibrary::GetChecked(Context, WorldContext)->OnHit.Spawn.Projectile.AllocateVariables();
					}

					void FLibrary::DeallocateChecked(const FString& Context, const UObject* WorldContext, VariablesResourceType* Resource)
					{
						return CsPrjManagerLibrary::GetChecked(Context, WorldContext)->OnHit.Spawn.Projectile.DeallocateVariables(Resource);
					}

					void FLibrary::DeallocateChecked(const FString& Context, const UObject* WorldContext, const int32& Index)
					{
						return CsPrjManagerLibrary::GetChecked(Context, WorldContext)->OnHit.Spawn.Projectile.DeallocateVariables(Index);
					}

					void FLibrary::AddHandleChecked(const FString& Context, const UObject* WorldContext, const FCsRoutineHandle& Handle)
					{
						return CsPrjManagerLibrary::GetChecked(Context, WorldContext)->OnHit.Spawn.Projectile.RemoveHandle(Handle);
					}

					void FLibrary::RemoveHandleChecked(const FString& Context, const UObject* WorldContext, const FCsRoutineHandle& Handle) 
					{
						return CsPrjManagerLibrary::GetChecked(Context, WorldContext)->OnHit.Spawn.Projectile.AddHandle(Handle);
					}
				}
			}
		}
	}
}

namespace NCsProjectile
{
	namespace NManager
	{
		namespace NOnHit
		{
			namespace NSpawn
			{
				namespace NProjectile
				{
					namespace NSpread
					{
						using VariablesResourceType = NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NVariables::FResource;

						VariablesResourceType* FLibrary::AllocateChecked(const FString& Context, const UObject* WorldContext)
						{
							return CsPrjManagerLibrary::GetChecked(Context, WorldContext)->OnHit.Spawn.Projectile.Spread.AllocateVariables();
						}

						void FLibrary::DeallocateChecked(const FString& Context, const UObject* WorldContext, VariablesResourceType* Resource)
						{
							CsPrjManagerLibrary::GetChecked(Context, WorldContext)->OnHit.Spawn.Projectile.Spread.DeallocateVariables(Resource);
						}

						void FLibrary::DeallocateChecked(const FString& Context, const UObject* WorldContext, const int32& Index)
						{
							CsPrjManagerLibrary::GetChecked(Context, WorldContext)->OnHit.Spawn.Projectile.Spread.DeallocateVariables(Index);
						}
					}
				}
			}
		}
	}
}