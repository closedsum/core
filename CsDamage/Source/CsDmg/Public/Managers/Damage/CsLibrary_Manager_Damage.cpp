// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/CsLibrary_Manager_Damage.h"

// Library
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"
	// Damage
#include "Value/CsLibrary_DamageValue.h"
#include "Range/CsLibrary_DamageRange.h"
#include "Modifier/CsLibrary_DamageModifier.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Damage/CsManager_Damage.h"
// Data
#include "Managers/Damage/Data/Types/CsData_GetDamageDataType.h"
// Damage
#include "Modifier/Copy/CsDamageModifier_Copy.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameState.h"
#endif // #if WITH_EDITOR

namespace NCsDamage
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NManager::FLibrary, GetSafe);
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

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetSafeAsObject(Context, WorldContext, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* WorldContext)
		{
			using namespace NCsDamage::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Damage* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
		{
			UObject* ContextRoot			  = GetContextRootChecked(Context, WorldContext);
			UCsManager_Damage* Manager_Damage = UCsManager_Damage::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Damage)
			return Manager_Damage;
		}

		UCsManager_Damage* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, WorldContext, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Damage* Manager_Damage = UCsManager_Damage::GetSafe(Context, ContextRoot, Log);

			if (!Manager_Damage)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Damage."), *Context));
			}
			return Manager_Damage;
		}

		UCsManager_Damage* FLibrary::GetSafe(const UObject* WorldContext)
		{
			using namespace NCsDamage::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, WorldContext, nullptr);
		}

		#pragma endregion Get
		
		// Event
		#pragma region

		#define EventResourceType NCsDamage::NEvent::FResource
		#define EventType NCsDamage::NEvent::IEvent

		void FLibrary::DeallocateEventChecked(const FString& Context, const UObject* WorldContext, EventResourceType* Event)
		{
			GetChecked(Context, WorldContext)->DeallocateEvent(Context, Event);
		}

		EventResourceType* FLibrary::CreateCopyOfEventChecked(const FString& Context, const UObject* WorldContext, const EventType* Event)
		{
			return GetChecked(Context, WorldContext)->CreateCopyOfEvent(Context, Event);
		}

		void FLibrary::CreateCopyOfEventChecked(const FString& Context, const UObject* WorldContext, const EventType* Event, EventResourceType*& OutEventContainer, EventType*& OutEvent)
		{
			OutEventContainer = CreateCopyOfEventChecked(Context, WorldContext, Event);
			OutEvent = OutEventContainer->Get();
		}

		#define GetDamageDataTypeDataType NCsData::IGetDamageDataType
		#define ProcessPayloadType NCsDamage::NData::NProcess::FPayload

		EventResourceType* FLibrary::CreateEventChecked(const FString& Context, const UObject* WorldContext, const ProcessPayloadType& ProcessPayload)
		{
			return GetChecked(Context, WorldContext)->CreateEvent(Context, ProcessPayload);
		}

		EventResourceType* FLibrary::CreateEventChecked(const FString& Context, const UObject* WorldContext, const GetDamageDataTypeDataType* GetDamageDataType, const ProcessPayloadType& ProcessPayload)
		{
			typedef NCsDamage::NData::IData DataType;

			DataType* Data = GetDataChecked(Context, WorldContext, GetDamageDataType);

			ProcessPayloadType* ProcessPayloadPtr = const_cast<ProcessPayloadType*>(&ProcessPayload);
			ProcessPayloadPtr->Data	 = Data;

			typedef NCsDamage::NData::FLibrary DataLibrary;
			typedef NCsDamage::NValue::IValue ValueType;
			typedef NCsDamage::NRange::IRange RangeType;

			ProcessPayloadPtr->Value = const_cast<ValueType*>(Data->GetValue());

			if (const RangeType* Range = DataLibrary::GetSafeRange(Context, Data, nullptr))
			{
				ProcessPayloadPtr->SetRange(const_cast<RangeType*>(Range));
			}

			return GetChecked(Context, WorldContext)->CreateEvent(Context, ProcessPayload);
		}

		#undef GetDamageDataTypeDataType
		#undef ProcessPayloadType

		void FLibrary::ProcessEventChecked(const FString& Context, const UObject* WorldContext, const EventType* Event)
		{
			GetChecked(Context, WorldContext)->ProcessDamageEvent(Event);
		}

		#undef EventResourceType
		#undef EventType

		#pragma endregion Event

		// Value
		#pragma region

		#define ValueResourceType NCsDamage::NValue::FResource
		#define ValueType NCsDamage::NValue::IValue

		void FLibrary::DeallocateValueChecked(const FString& Context, const UObject* WorldContext, const FECsDamageValue& Type, ValueResourceType* Value)
		{
			GetChecked(Context, WorldContext)->DeallocateValue(Context, Type, Value);
		}

		ValueResourceType* FLibrary::CreateCopyOfValueChecked(const FString& Context, const UObject* WorldContext, const ValueType* Value)
		{
			UCsManager_Damage* Manager_Damage = GetChecked(Context, WorldContext);

			typedef NCsDamage::NValue::FLibrary DamageValueLibrary;

			const FECsDamageValue& Type  = DamageValueLibrary::GetTypeChecked(Context, Value);
			ValueResourceType* Container = Manager_Damage->AllocateValue(Type);
			ValueType* Copy				 = Container->Get();

			typedef NCsDamage::NValue::FLibrary ValueLibrary;

			bool Success = ValueLibrary::CopyChecked(Context, Value, Copy);

			checkf(Success, TEXT("%s: Failed to create copy of Value."), *Context);

			return Container;
		}

		ValueResourceType* FLibrary::CreateCopyOfValueChecked(const FString& Context, const UObject* WorldContext, const ValueResourceType* Value)
		{
			CS_IS_PTR_NULL_CHECKED(Value)

			return CreateCopyOfValueChecked(Context, WorldContext, Value->Get());
		}

		#undef ValueResourceType
		#undef ValueType

		#pragma endregion Value

		// Range
		#pragma region

		#define RangeResourceType NCsDamage::NRange::FResource
		#define RangeType NCsDamage::NRange::IRange

		void FLibrary::DeallocateRangeChecked(const FString& Context, const UObject* WorldContext, RangeResourceType* Range)
		{
			GetChecked(Context, WorldContext)->DeallocateRange(Context, Range);
		}

		RangeResourceType* FLibrary::CreateCopyOfRangeChecked(const FString& Context, const UObject* WorldContext, const RangeType* Range)
		{
			UCsManager_Damage* Manager_Damage = GetChecked(Context, WorldContext);

			RangeResourceType* Container = Manager_Damage->AllocateRange();
			RangeType* Copy				 = Container->Get();

			typedef NCsDamage::NRange::FLibrary RangeLibrary;

			bool Success = RangeLibrary::CopyChecked(Context, Range, Copy);

			checkf(Success, TEXT("%s: Failed to create copy of Range."), *Context);

			return Container;
		}

		RangeResourceType* FLibrary::CreateCopyOfRangeChecked(const FString& Context, const UObject* WorldContext, const RangeResourceType* Range)
		{
			CS_IS_PTR_NULL_CHECKED(Range)

			return CreateCopyOfRangeChecked(Context, WorldContext, Range->Get());
		}

		#undef RangeResourceType
		#undef RangeType

		#pragma endregion Range

		// Modifier
		#pragma region

		#define ModifierResourceType NCsDamage::NModifier::FResource
		#define ModifierType NCsDamage::NModifier::IModifier
		#define AllocatedModifierType NCsDamage::NModifier::FAllocated
		
		void FLibrary::DeallocateModifierChecked(const FString& Context, const UObject* WorldContext, const FECsDamageModifier& Type, ModifierResourceType* Modifier)
		{
			GetChecked(Context, WorldContext)->DeallocateModifier(Context, Type, Modifier);
		}

		const FECsDamageModifier& FLibrary::GetModifierTypeChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier)
		{
			return GetChecked(Context, WorldContext)->GetModifierType(Context, Modifier);
		}

		ModifierResourceType* FLibrary::CreateCopyOfModifierChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier)
		{
			UCsManager_Damage* Manager_Damage = GetChecked(Context, WorldContext);

			typedef NCsDamage::NModifier::FLibrary DamageModifierLibrary;

			const FECsDamageModifier& Type  = DamageModifierLibrary::GetTypeChecked(Context, Modifier);
			ModifierResourceType* Container = Manager_Damage->AllocateModifier(Type);
			ModifierType* Copy				= Container->Get();

			typedef NCsDamage::NModifier::FLibrary ModifierLibrary;
			typedef NCsDamage::NModifier::NCopy::ICopy CopyType;

			CopyType* ICopy = ModifierLibrary::GetInterfaceChecked<CopyType>(Context, Copy);

			ICopy->Copy(Modifier);

			return Container;
		}

		ModifierResourceType* FLibrary::CreateCopyOfModifierChecked(const FString& Context, const UObject* WorldContext, const ModifierResourceType* Modifier)
		{
			CS_IS_PTR_NULL_CHECKED(Modifier)

			return CreateCopyOfModifierChecked(Context, WorldContext, Modifier->Get());
		}

		void FLibrary::CreateCopyOfModifiersChecked(const FString& Context, const UObject* WorldContext, const TArray<ModifierType*>& From, TArray<ModifierResourceType*>& To)
		{
			CS_IS_ARRAY_ANY_NULL_CHECKED(From, ModifierType)

			To.Reset(FMath::Max(To.Max(), From.Num()));

			for (const ModifierType* Modifier : From)
			{
				To.Add(CreateCopyOfModifierChecked(Context, WorldContext, Modifier));
			}
		}

		void FLibrary::CreateCopyOfModifiersChecked(const FString& Context, const UObject* WorldContext, const TArray<ModifierType*>& From, TArray<AllocatedModifierType>& To)
		{
			UObject* ContextRoot = GetContextRootChecked(Context, WorldContext);

			CS_IS_ARRAY_ANY_NULL_CHECKED(From, ModifierType)

			To.Reset(FMath::Max(To.Max(), From.Num()));

			for (const ModifierType* Modifier : From)
			{
				AllocatedModifierType& Allocated = To.AddDefaulted_GetRef();
				Allocated.Copy(ContextRoot, Modifier);
			}
		}

		void FLibrary::CreateCopyOfModifierChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier, ModifierResourceType*& OutContainer, FECsDamageModifier& OutType)
		{
			UCsManager_Damage* Manager_Damage = GetChecked(Context, WorldContext);

			typedef NCsDamage::NModifier::FLibrary DmgModifierLibrary;

			OutType				= DmgModifierLibrary::GetTypeChecked(Context, Modifier);
			OutContainer		= Manager_Damage->AllocateModifier(OutType);
			ModifierType* Copy	= OutContainer->Get();

			typedef NCsDamage::NModifier::FLibrary ModifierLibrary;
			typedef NCsDamage::NModifier::NCopy::ICopy CopyType;

			CopyType* ICopy = ModifierLibrary::GetInterfaceChecked<CopyType>(Context, Copy);

			ICopy->Copy(Modifier);
		}

#		undef ModifierResourceType
		#undef ModifierType
		#undef AllocatedModifierType

		#pragma endregion Modifier

		// Data
		#pragma region

		#define DataType NCsDamage::NData::IData

		#define GetDamageDataTypeDataType NCsData::IGetDamageDataType
		DataType* FLibrary::GetDataChecked(const FString& Context, const UObject* WorldContext, const GetDamageDataTypeDataType* GetDamageDataType)
		{
		#undef GetDamageDataTypeDataType

			CS_IS_PTR_NULL_CHECKED(GetDamageDataType)

			const FECsDamageData& DamageDataType = GetDamageDataType->GetDamageDataType();

			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageData, DamageDataType)

			return GetChecked(Context, WorldContext)->GetDataChecked(Context, DamageDataType.GetFName());
		}

		#define DataHandlerType NCsData::NManager::NHandler::TData
		#define DataInterfaceMapType NCsDamage::NData::FInterfaceMap
		DataHandlerType<DataType, FCsData_DamagePtr, DataInterfaceMapType>* FLibrary::GetSafeDataHandler(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
		#undef DataHandlerType
		#undef DataInterfaceMapType

			if (UCsManager_Damage* Manager_Damage = GetSafe(Context, WorldContext, Log))
			{
				return Manager_Damage->GetDataHandler();
			}
			return nullptr;
		}
	
		#define ModifierType NCsDamage::NModifier::IModifier
		#define ValueType NCsDamage::NValue::IValue
		#define RangeType NCsDamage::NRange::IRange

		void FLibrary::ProcessDataChecked(const FString& Context, const UObject* WorldContext, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierType*>& Modifiers)
		{
			GetChecked(Context, WorldContext)->ProcessData(Context, Data, Instigator, Causer, HitResult, Modifiers);
		}

		void FLibrary::ProcessDataChecked(const FString& Context, const UObject* WorldContext, const FECsDamageData& Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult)
		{
			DataType* DataPtr = GetChecked(Context, WorldContext)->GetDataChecked(Context, Data.GetFName());

			GetChecked(Context, WorldContext)->ProcessData(Context, DataPtr, Instigator, Causer, HitResult);
		}

		bool FLibrary::SafeProcessData(const FString& Context, const UObject* WorldContext, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierType*>& Modifiers, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Damage* Manager_Damage = GetSafe(Context, WorldContext, Log))
			{
				typedef NCsDamage::NData::FLibrary DamageDataLibrary;

				if (!DamageDataLibrary::IsValid(Context, Data))
					return false;

				CS_IS_ARRAY_ANY_NULL(Modifiers, ModifierType)

				Manager_Damage->ProcessData(Context, Data, Instigator, Causer, HitResult, Modifiers);
				return true;
			}
			return false;
		}

		bool FLibrary::SafeProcessData(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Damage* Manager_Damage = GetSafe(Context, WorldContext, Log))
			{
				DataType* Data = Manager_Damage->GetSafeData(Context, DataName, Log);

				typedef NCsDamage::NData::FLibrary DamageDataLibrary;

				if (!DamageDataLibrary::IsValid(Context, Data))
					return false;

				TArray<ModifierType*> Modifiers;
				Manager_Damage->ProcessData(Context, Data, Instigator, Causer, HitResult, Modifiers);
				return true;
			}
			return false;
		}

		void FLibrary::ProcessDataChecked(const FString& Context, const UObject* WorldContext, const ValueType* Value, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierType*>& Modifiers)
		{
			GetChecked(Context, WorldContext)->ProcessData(Context, Value, Data, Instigator, Causer, HitResult, Modifiers);
		}

		void FLibrary::ProcessDataChecked(const FString& Context, const UObject* WorldContext, const ValueType* Value, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult)
		{
			GetChecked(Context, WorldContext)->ProcessData(Context, Value, Data, Instigator, Causer, HitResult);
		}

		void FLibrary::ProcessDataChecked(const FString& Context, const UObject* WorldContext, const ValueType* Value, const RangeType* Range, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierType*>& Modifiers)
		{
			GetChecked(Context, WorldContext)->ProcessData(Context, Value, Range, Data, Instigator, Causer, HitResult, Modifiers);
		}

		void FLibrary::ProcessDataChecked(const FString& Context, const UObject* WorldContext, const ValueType* Value, const RangeType* Range, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult)
		{
			GetChecked(Context, WorldContext)->ProcessData(Context, Value, Range, Data, Instigator, Causer, HitResult);
		}

		#define ProcessPayloadType NCsDamage::NData::NProcess::FPayload
		
		void FLibrary::ProcessDataChecked(const FString& Context, const UObject* WorldContext, const ProcessPayloadType& ProcessPayload)
		{
			GetChecked(Context, WorldContext)->ProcessData(Context, ProcessPayload);
		}

		#undef ProcessPayloadType

		#undef ModifierType
		#undef ValueType
		#undef RangeType

		#undef DataType

		#pragma endregion Data
	}
}