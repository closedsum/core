// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Coordinators/StatusEffect/CsLibrary_Coordinator_StatusEffect.h"

// Types
#include "CsMacro_Misc.h"
// Coordinators
#include "Coordinators/StatusEffect/CsCoordinator_StatusEffect.h"
// Library
#include "Data/CsLibrary_Data_StatusEffect.h"
#include "Library/CsLibrary_Valid.h"
// StatusEffect
#include "CsAllocated_StatusEffect.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameState.h"
#endif // #if WITH_EDITOR

namespace NCsStatusEffect
{
	namespace NCoordinator
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStatusEffect::NCoordinator::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStatusEffect::NCoordinator::FLibrary, GetSafe);
				}
			}
		}

		// Print
		#pragma region

		FString FLibrary::PrintObjectWithClass(const UCsCoordinator_StatusEffect* Coordinator)
		{
			return FString::Printf(TEXT("%s: with Class: %s"), *(Coordinator->GetName()), *(Coordinator->GetClass()->GetName()));
		}

		#pragma endregion Print

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* WorldContext)
		{
			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetAsObjectChecked(Context, WorldContext);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsStatusEffect::FLog::Warning*/)
		{
			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetSafeAsObject(Context, WorldContext, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* WorldContext)
		{
			using namespace NCsStatusEffect::NCoordinator::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsCoordinator_StatusEffect* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
		{
			UObject* ContextRoot								  = GetContextRootChecked(Context, WorldContext);
			UCsCoordinator_StatusEffect* Coordinator_StatusEffect = UCsCoordinator_StatusEffect::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Coordinator_StatusEffect)
			return Coordinator_StatusEffect;
		}

		UCsCoordinator_StatusEffect* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsStatusEffect::FLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, WorldContext, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsCoordinator_StatusEffect* Coordinator_StatusEffect = UCsCoordinator_StatusEffect::GetSafe(Context, ContextRoot, Log);

			if (!Coordinator_StatusEffect)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Coordinator_StatusEffect."), *Context));
			}
			return Coordinator_StatusEffect;
		}

		UCsCoordinator_StatusEffect* FLibrary::GetSafe(const UObject* WorldContext)
		{
			using namespace NCsStatusEffect::NCoordinator::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, WorldContext, nullptr);
		}

		#pragma endregion Get

		// Data
		#pragma region

		#define DataType NCsStatusEffect::NData::IData

		#define DataHandlerType NCsData::NManager::NHandler::TData
		#define DataInterfaceMapType NCsStatusEffect::NData::FInterfaceMap
		DataHandlerType<DataType, FCsData_StatusEffectPtr, DataInterfaceMapType>* FLibrary::GetSafeDataHandler(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
		#undef DataHandlerType
		#undef DataInterfaceMapType

			if (UCsCoordinator_StatusEffect* Coordinator_StatusEffect = GetSafe(Context, WorldContext, Log))
			{
				return Coordinator_StatusEffect->GetDataHandler();
			}
			return nullptr;
		}

		DataType* FLibrary::GetDataChecked(const FString& Context, const UObject* WorldContext, const FName& Name)
		{
			DataType* Data = GetChecked(Context, WorldContext)->GetDataChecked(Context, Name);

			typedef NCsStatusEffect::NData::FLibrary SeDataLibrary;

			check(SeDataLibrary::IsValidChecked(Context, Data));

			return Data;
		}

		DataType* FLibrary::GetSafeData(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsCoordinator_StatusEffect* Coordinator_StatusEffect = GetSafe(Context, WorldContext, Log))
			{
				DataType* Data = Coordinator_StatusEffect->GetSafeData(Context, Name);

				typedef NCsStatusEffect::NData::FLibrary SeDataLibrary;

				if (!SeDataLibrary::IsValid(Context, Data, Log))
					return nullptr;
				return Data;
			}
			return nullptr;
		}

		DataType* FLibrary::GetDataChecked(const FString& Context, const UObject* WorldContext, const FECsStatusEffect& Type)
		{
			DataType* Data = GetChecked(Context, WorldContext)->GetDataChecked(Context, Type);

			typedef NCsStatusEffect::NData::FLibrary SeDataLibrary;

			check(SeDataLibrary::IsValidChecked(Context, Data));

			return Data;
		}

		DataType* FLibrary::GetSafeData(const FString& Context, const UObject* WorldContext, const FECsStatusEffect& Type, void(*Log)(const FString&) /*=&FCLog::Warning*/)
		{
			if (UCsCoordinator_StatusEffect* Coordinator_StatusEffect = GetSafe(Context, WorldContext, Log))
			{
				DataType* Data = Coordinator_StatusEffect->GetSafeData(Context, Type);

				typedef NCsStatusEffect::NData::FLibrary SeDataLibrary;

				if (!SeDataLibrary::IsValid(Context, Data, Log))
					return nullptr;
				return Data;
			}
			return nullptr;
		}

		#define ProcessPayloadType NCsStatusEffect::NData::NProcess::FPayload
		void FLibrary::ProcessDataChecked(const FString& Context, const UObject* WorldContext, const ProcessPayloadType& ProcessPayload)
		{
		#undef ProcessPayloadType
			GetChecked(Context, WorldContext)->ProcessDataChecked(Context, ProcessPayload);
		}

		void FLibrary::ProcessDataChecked(const FString& Context, const UObject* WorldContext, const FECsStatusEffect& Type, DataType* Data, UObject* Instigator, UObject* Causer, UObject* Receiver)
		{
			GetChecked(Context, WorldContext)->ProcessDataChecked(Context, Type, Data, Instigator, Causer, Receiver);
		}

		void FLibrary::ProcessDataChecked(const FString& Context, const UObject* WorldContext, const FECsStatusEffect& Type, UObject* Instigator, UObject* Causer, UObject* Receiver)
		{
			GetChecked(Context, WorldContext)->ProcessDataChecked(Context, Type, Instigator, Causer, Receiver);
		}

		#undef DataType

		#pragma endregion Data

		// StatusEffect
		#pragma region

		#define SeResourceType NCsStatusEffect::FResource
		#define StatusEffectType NCsStatusEffect::IStatusEffect
		
		SeResourceType* FLibrary::AllocateStatusEffectChecked(const FString& Context, const UObject* WorldContext, const FECsStatusEffectImpl& Type)
		{
			return GetChecked(Context, WorldContext)->AllocateStatusEffect(Type);
		}

		void FLibrary::DeallocateStatusEffectChecked(const FString& Context, const UObject* WorldContext, const FECsStatusEffectImpl& Type, SeResourceType* StatusEffect)
		{
			GetChecked(Context, WorldContext)->DeallocateStatusEffect(Context, Type, StatusEffect);
		}

		const FECsStatusEffectImpl& FLibrary::GetStatusEffectImplTypeChecked(const FString& Context, const UObject* WorldContext, const StatusEffectType* StatusEffect)
		{
			return GetChecked(Context, WorldContext)->GetStatusEffectImplType(Context, StatusEffect);
		}

		SeResourceType* FLibrary::CreateCopyOfStatusEffectChecked(const FString& Context, const UObject* WorldContext, const StatusEffectType* StatusEffect, FECsStatusEffectImpl& OutType)
		{
			return GetChecked(Context, WorldContext)->CreateCopyOfStatusEffect(Context, StatusEffect, OutType);
		}

		SeResourceType* FLibrary::CreateCopyOfStatusEffectChecked(const FString& Context, const UObject* WorldContext, const StatusEffectType* StatusEffect)
		{
			return GetChecked(Context, WorldContext)->CreateCopyOfStatusEffect(Context, StatusEffect);
		}

		SeResourceType* FLibrary::CreateCopyOfStatusEffectChecked(const FString& Context, const UObject* WorldContext, const SeResourceType* StatusEffect)
		{
			return GetChecked(Context, WorldContext)->CreateCopyOfStatusEffect(Context, StatusEffect);
		}

		#define SeAllocatedType NCsStatusEffect::FAllocated
		void FLibrary::CreateCopyOfStatusEffectChecked(const FString& Context, const UObject* WorldContext, const StatusEffectType* StatusEffect, SeAllocatedType*& OutAllocated)
		{
		#undef SeAllocatedType

			FECsStatusEffectImpl ImplType;
			SeResourceType* Container = GetChecked(Context, WorldContext)->CreateCopyOfStatusEffect(Context, StatusEffect, ImplType);
			StatusEffectType* Se	  = Container->Get();

			OutAllocated->Root		   = const_cast<UObject*>(WorldContext);
			OutAllocated->Type		   = Se->GetStatusEffectType();
			OutAllocated->Container	   = Container;
			OutAllocated->StatusEffect = Se;
			OutAllocated->ImplType	   = ImplType;
		}

#		undef SeResourceType
		#undef StatusEffectType

		#pragma endregion Modifier

		namespace NEvent
		{
			#define EventResourceType NCsStatusEffect::NEvent::FResource

			EventResourceType* FLibrary::AllocateChecked(const FString& Context, const UObject* WorldContext, const FECsStatusEffectEvent& Type)
			{
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsStatusEffectEvent, Type)

				return GetCoordinatorChecked(Context, WorldContext)->AllocateEvent(Type);
			}

			void FLibrary::DeallocateChecked(const FString& Context, const UObject* WorldContext, EventResourceType* Event, const FECsStatusEffectEvent& Type)
			{
				GetCoordinatorChecked(Context, WorldContext)->DeallocateEvent(Context, Event, Type);
			}

			void FLibrary::DeallocateChecked(const FString& Context, const UObject* WorldContext, EventResourceType* Event)
			{
				GetCoordinatorChecked(Context, WorldContext)->DeallocateEvent(Context, Event);	
			}

			#undef EventResourceType
		}
	}
}