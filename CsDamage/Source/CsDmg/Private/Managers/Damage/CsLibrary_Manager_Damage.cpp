// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Damage/CsLibrary_Manager_Damage.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"
	// Damage
#include "Value/CsLibrary_DamageValue.h"
#include "Range/CsLibrary_DamageRange.h"
#include "Modifier/CsLibrary_DamageModifier.h"
	// Common
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Damage/CsManager_Damage.h"
// Data
#include "Managers/Damage/Data/Types/CsData_GetDamageDataType.h"
#include "Managers/Damage/Data/Types/CsData_GetDamageDataTypes.h"
// Damage
#include "Modifier/Copy/CsDamageModifier_Copy.h"

#if WITH_EDITOR
// Library
	// Common
#include "Library/CsLibrary_World.h"
// Managers
#include "Singleton/CsGetManagerSingleton.h"
// Library
#include "Game/CsLibrary_GameState.h"
#endif // #if WITH_EDITOR

// Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME_NESTED_2(NCsDamage, NManager, Library)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsDamage::NManager::FLibrary, GetSafeContextRoot)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsDamage::NManager::FLibrary, GetSafe)
CS_END_CACHED_FUNCTION_NAME_NESTED_2

#pragma endregion Cached

namespace NCsDamage
{
	namespace NManager
	{
		using EventResourceType = NCsDamage::NEvent::FResource;
		using EventType = NCsDamage::NEvent::IEvent;
		using ProcessPayloadType = NCsDamage::NData::NProcess::FPayload;
		using ValueLibrary = NCsDamage::NValue::FLibrary;
		using ValueResourceType = NCsDamage::NValue::FResource;
		using ValueType = NCsDamage::NValue::IValue;
		using RangeResourceType = NCsDamage::NRange::FResource;
		using RangeType = NCsDamage::NRange::IRange;
		using DataType = NCsDamage::NData::IData;
		using DataInterfaceMapType = NCsDamage::NData::FInterfaceMap;
		using DataHandlerType = NCsData::NManager::NHandler::TData<DataType, FCsData_DamagePtr, DataInterfaceMapType>;
		using ModifierType = NCsDamage::NModifier::IModifier;

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

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
		{
			if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
			{
				if (const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST(WorldContext, UObject, ICsGetManagerSingleton))
				{
					return GetManagerSingleton->_getUObject();
				}
				return nullptr;
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

		UCsManager_Damage* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
		{
			UObject* ContextRoot			  = GetContextRootChecked(Context, WorldContext);
			UCsManager_Damage* Manager_Damage = UCsManager_Damage::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Damage)
			return Manager_Damage;
		}

		UCsManager_Damage* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
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
			CS_SET_CONTEXT_AS_FUNCTION_NAME(GetSafe);

			return GetSafe(Context, WorldContext, nullptr);
		}

		#pragma endregion Get
		
		// Event
		#pragma region

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

		EventResourceType* FLibrary::CreateEventChecked(const FString& Context, const UObject* WorldContext, const ProcessPayloadType& ProcessPayload)
		{
			return GetChecked(Context, WorldContext)->CreateEvent(Context, ProcessPayload);
		}

		EventResourceType* FLibrary::CreateEventChecked(const FString& Context, const UObject* WorldContext, const CsGetDamageDataTypeDataType* GetDamageDataType, const ProcessPayloadType& ProcessPayload)
		{
			DataType* Data = GetDataChecked(Context, WorldContext, GetDamageDataType);

			ProcessPayloadType* ProcessPayloadPtr = const_cast<ProcessPayloadType*>(&ProcessPayload);
			ProcessPayloadPtr->Type  = GetDamageDataType->GetDamageDataType();
			ProcessPayloadPtr->Data	 = Data;
			ProcessPayloadPtr->Value = const_cast<ValueType*>(Data->GetValue());

			if (const RangeType* Range = CsDamageDataLibrary::GetSafeRange(Context, Data, nullptr))
			{
				ProcessPayloadPtr->SetRange(const_cast<RangeType*>(Range));
			}

			return GetChecked(Context, WorldContext)->CreateEvent(Context, ProcessPayload);
		}

		void FLibrary::ProcessEventChecked(const FString& Context, const UObject* WorldContext, const EventType* Event)
		{
			GetChecked(Context, WorldContext)->ProcessDamageEvent(Event);
		}

		#pragma endregion Event

		// Value
		#pragma region	

		void FLibrary::DeallocateValueChecked(const FString& Context, const UObject* WorldContext, const FECsDamageValue& Type, ValueResourceType* Value)
		{
			GetChecked(Context, WorldContext)->DeallocateValue(Context, Type, Value);
		}

		ValueResourceType* FLibrary::CreateCopyOfValueChecked(const FString& Context, const UObject* WorldContext, const ValueType* Value)
		{
			UCsManager_Damage* Manager_Damage = GetChecked(Context, WorldContext);

			const FECsDamageValue& Type  = ValueLibrary::GetTypeChecked(Context, Value);
			ValueResourceType* Container = Manager_Damage->AllocateValue(Type);
			ValueType* Copy				 = Container->Get();

			bool Success = ValueLibrary::CopyChecked(Context, Value, Copy);

			checkf(Success, TEXT("%s: Failed to create copy of Value."), *Context);
			return Container;
		}

		ValueResourceType* FLibrary::CreateCopyOfValueChecked(const FString& Context, const UObject* WorldContext, const ValueResourceType* Value)
		{
			CS_IS_PTR_NULL_CHECKED(Value)

			return CreateCopyOfValueChecked(Context, WorldContext, Value->Get());
		}

		#pragma endregion Value

		// Range
		#pragma region

		void FLibrary::DeallocateRangeChecked(const FString& Context, const UObject* WorldContext, RangeResourceType* Range)
		{
			GetChecked(Context, WorldContext)->DeallocateRange(Context, Range);
		}

		RangeResourceType* FLibrary::CreateCopyOfRangeChecked(const FString& Context, const UObject* WorldContext, const RangeType* Range)
		{
			UCsManager_Damage* Manager_Damage = GetChecked(Context, WorldContext);

			RangeResourceType* Container = Manager_Damage->AllocateRange();
			RangeType* Copy				 = Container->Get();

			bool Success = CsDamageRangeLibrary::CopyChecked(Context, Range, Copy);

			checkf(Success, TEXT("%s: Failed to create copy of Range."), *Context);

			return Container;
		}

		RangeResourceType* FLibrary::CreateCopyOfRangeChecked(const FString& Context, const UObject* WorldContext, const RangeResourceType* Range)
		{
			CS_IS_PTR_NULL_CHECKED(Range)

			return CreateCopyOfRangeChecked(Context, WorldContext, Range->Get());
		}

		#pragma endregion Range

		// Modifier
		#pragma region

		#pragma endregion Modifier

		// Data
		#pragma region

		const FECsDamageData& FLibrary::GetDataTypeChecked(const FString& Context, const UObject* WorldContext, const DataType* Data)
		{
			return GetChecked(Context, WorldContext)->GetDataTypeChecked(Context, Data);
		}

		DataType* FLibrary::GetDataChecked(const FString& Context, const UObject* WorldContext, const FECsDamageData& Type)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageData, Type)

			return GetChecked(Context, WorldContext)->GetDataChecked(Context, Type.GetFName());
		}

		DataType* FLibrary::GetDataChecked(const FString& Context, const UObject* WorldContext, const CsGetDamageDataTypeDataType* GetDamageDataType)
		{
			CS_IS_PTR_NULL_CHECKED(GetDamageDataType)

			const FECsDamageData& DamageDataType = GetDamageDataType->GetDamageDataType();

			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsDamageData, DamageDataType)

			return GetChecked(Context, WorldContext)->GetDataChecked(Context, DamageDataType.GetFName());
		}

		DataType* FLibrary::GetSafeData(const FString& Context, const UObject* WorldContext, const CsGetDamageDataTypeDataType* GetDamageDataType, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
		{
			CS_IS_PTR_NULL_RET_NULL(GetDamageDataType)

			const FECsDamageData& DamageDataType = GetDamageDataType->GetDamageDataType();

			CS_IS_ENUM_STRUCT_VALID_RET_NULL(EMCsDamageData, FECsDamageData, DamageDataType)

			if (UCsManager_Damage* Manager_Damage = GetSafe(Context, WorldContext, Log))
			{
				return Manager_Damage->GetSafeData(Context, DamageDataType.GetFName(), Log);
			}
			return nullptr;
		}

		void FLibrary::GetDatasChecked(const FString& Context, const UObject* WorldContext, const TArray<FECsDamageData>& DamageDataTypes, TArray<DataType*>& OutDatas)
		{
			OutDatas.Reset(FMath::Max(OutDatas.Max(), DamageDataTypes.Num()));

			CS_IS_ENUM_STRUCT_ARRAY_VALID_CHECKED(EMCsDamageData, FECsDamageData, DamageDataTypes)

			UCsManager_Damage* Manager_Damage = GetChecked(Context, WorldContext);

			for (const FECsDamageData& Type : DamageDataTypes)
			{
				DataType* Data = Manager_Damage->GetDataChecked(Context, Type.GetFName());

				OutDatas.Add(Data);
			}
		}

		void FLibrary::GetDatasChecked(const FString& Context, const UObject* WorldContext, const CsGetDamageDataTypeDataTypes* GetDamageDataTypes, TArray<DataType*>& OutDatas)
		{
			CS_IS_PTR_NULL_CHECKED(GetDamageDataTypes)

			const TArray<FECsDamageData>& DamageDataTypes = GetDamageDataTypes->GetDamageDataTypes();

			GetDatasChecked(Context, WorldContext, DamageDataTypes, OutDatas);
		}

		bool FLibrary::GetSafeDatas(const FString& Context, const UObject* WorldContext, const CsGetDamageDataTypeDataTypes* GetDamageDataTypes, TArray<DataType*>& OutDatas, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
		{
			CS_IS_PTR_NULL(GetDamageDataTypes)

			const TArray<FECsDamageData>& DamageDataTypes = GetDamageDataTypes->GetDamageDataTypes();

			CS_IS_ENUM_STRUCT_ARRAY_VALID(EMCsDamageData, FECsDamageData, DamageDataTypes)

			if (UCsManager_Damage* Manager_Damage = GetSafe(Context, WorldContext, Log))
			{
				for (const FECsDamageData& Type : DamageDataTypes)
				{
					if (DataType* Data = Manager_Damage->GetSafeData(Context, Type.GetFName(), Log))
					{
						OutDatas.Add(Data);
					}
				}
				return true;
			}
			return false;
		}

		UObject* FLibrary::GetSafeDataAsObject(const FString& Context, const UObject* WorldContext, const FECsDamageData& Type, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
		{
			if (UCsManager_Damage* Manager_Damage = GetSafe(Context, WorldContext, Log))
			{
				if (DataType* Data = Manager_Damage->GetSafeData(Context, Type, Log))
				{
					if (UObject* O = Data->_getUObject())
					{
						return O;
					}
					else
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get UObject for %s associated with Name: %s"), *Context, *CsDamageDataLibrary::PrintDataAndClass(Data), Type.ToChar()));
					}
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Data associated with Name: %s"), *Context, Type.ToChar()));
				}
			}
			return nullptr;
		}

		UObject* FLibrary::GetSafeDataAsObject(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
		{
			if (UCsManager_Damage* Manager_Damage = GetSafe(Context, WorldContext, Log))
			{
				if (DataType* Data = Manager_Damage->GetSafeData(Context, Name, Log))
				{
					if (UObject* O = Data->_getUObject())
					{
						return O;
					}
					else
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get UObject for %s associated with Name: %s"), *Context, *CsDamageDataLibrary::PrintDataAndClass(Data), *(Name.ToString())));
					}
				}
				else
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Data associated with Name: %s"), *Context, *(Name.ToString())));
				}
			}
			return nullptr;
		}

		void FLibrary::AddDatasChecked(const FString& Context, const UObject* WorldContext, const TArray<FECsDamageData>& DamageDataTypes, TArray<DataType*>& OutDatas)
		{
			CS_IS_ENUM_STRUCT_ARRAY_VALID_CHECKED(EMCsDamageData, FECsDamageData, DamageDataTypes)

			UCsManager_Damage* Manager_Damage = GetChecked(Context, WorldContext);

			for (const FECsDamageData& Type : DamageDataTypes)
			{
				DataType* Data = Manager_Damage->GetDataChecked(Context, Type.GetFName());

				OutDatas.Add(Data);
			}
		}

		DataHandlerType* FLibrary::GetSafeDataHandler(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
		{
			if (UCsManager_Damage* Manager_Damage = GetSafe(Context, WorldContext, Log))
			{
				return Manager_Damage->GetDataHandler();
			}
			return nullptr;
		}
	
		void FLibrary::ProcessDataChecked(const FString& Context, const UObject* WorldContext, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierType*>& Modifiers)
		{
			GetChecked(Context, WorldContext)->ProcessData(Context, Data, Type, Instigator, Causer, HitResult, Modifiers);
		}

		void FLibrary::ProcessDataChecked(const FString& Context, const UObject* WorldContext, const FECsDamageData& Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult)
		{
			DataType* DataPtr = GetChecked(Context, WorldContext)->GetDataChecked(Context, Data.GetFName());

			GetChecked(Context, WorldContext)->ProcessData(Context, DataPtr, Data, Instigator, Causer, HitResult);
		}

		bool FLibrary::SafeProcessData(const FString& Context, const UObject* WorldContext, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierType*>& Modifiers, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
		{
			CS_IS_PTR_NULL(Data)
			CS_IS_ENUM_STRUCT_VALID(EMCsDamageData, FECsDamageData, Type)

			if (UCsManager_Damage* Manager_Damage = GetSafe(Context, WorldContext, Log))
			{
				if (!CsDamageDataLibrary::IsValid(Context, Data))
					return false;

				CS_IS_TARRAY_ANY_NULL(Modifiers, ModifierType)

				Manager_Damage->ProcessData(Context, Data, Type, Instigator, Causer, HitResult, Modifiers);
				return true;
			}
			return false;
		}

		bool FLibrary::SafeProcessData(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, void(*Log)(const FString&) /*=&NCsDamage::FLog::Warning*/)
		{
			if (UCsManager_Damage* Manager_Damage = GetSafe(Context, WorldContext, Log))
			{
				DataType* Data = Manager_Damage->GetSafeData(Context, DataName, Log);

				if (!CsDamageDataLibrary::IsValid(Context, Data))
					return false;

				const FECsDamageData& Type = EMCsDamageData::Get().GetEnum(DataName);

				CS_IS_ENUM_STRUCT_VALID(EMCsDamageData, FECsDamageData, Type)

				TArray<ModifierType*> Modifiers;
				Manager_Damage->ProcessData(Context, Data, Type, Instigator, Causer, HitResult, Modifiers);
				return true;
			}
			return false;
		}

		void FLibrary::ProcessDataChecked(const FString& Context, const UObject* WorldContext, const ValueType* Value, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierType*>& Modifiers)
		{
			GetChecked(Context, WorldContext)->ProcessData(Context, Value, Data, Type, Instigator, Causer, HitResult, Modifiers);
		}

		void FLibrary::ProcessDataChecked(const FString& Context, const UObject* WorldContext, const ValueType* Value, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult)
		{
			GetChecked(Context, WorldContext)->ProcessData(Context, Value, Data, Type, Instigator, Causer, HitResult);
		}

		void FLibrary::ProcessDataChecked(const FString& Context, const UObject* WorldContext, const ValueType* Value, const RangeType* Range, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierType*>& Modifiers)
		{
			GetChecked(Context, WorldContext)->ProcessData(Context, Value, Range, Data, Type, Instigator, Causer, HitResult, Modifiers);
		}

		void FLibrary::ProcessDataChecked(const FString& Context, const UObject* WorldContext, const ValueType* Value, const RangeType* Range, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult)
		{
			GetChecked(Context, WorldContext)->ProcessData(Context, Value, Range, Data, Type, Instigator, Causer, HitResult);
		}

		void FLibrary::ProcessDataChecked(const FString& Context, const UObject* WorldContext, const ProcessPayloadType& ProcessPayload)
		{
			GetChecked(Context, WorldContext)->ProcessData(Context, ProcessPayload);
		}

		#pragma endregion Data
	}
}

namespace NCsDamage
{
	namespace NManager
	{
		namespace NModifier
		{
			using ModifierResourceType = NCsDamage::NModifier::FResource;
			using ModifierType = NCsDamage::NModifier::IModifier;
			using AllocatedModifierType = NCsDamage::NModifier::FAllocated;
			using CopyType = NCsDamage::NModifier::NCopy::ICopy;
		
			void FLibrary::DeallocateChecked(const FString& Context, const UObject* WorldContext, const FECsDamageModifier& Type, ModifierResourceType* Modifier)
			{
				CsDamageManagerLibrary::GetChecked(Context, WorldContext)->DeallocateModifier(Context, Type, Modifier);
			}

			const FECsDamageModifier& FLibrary::GetTypeChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier)
			{
				return CsDamageManagerLibrary::GetChecked(Context, WorldContext)->GetModifierType(Context, Modifier);
			}

			ModifierResourceType* FLibrary::CopyChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier)
			{
				UCsManager_Damage* Manager_Damage = CsDamageManagerLibrary::GetChecked(Context, WorldContext);

				const FECsDamageModifier& Type  = CsDamageModifierLibrary::GetTypeChecked(Context, Modifier);
				ModifierResourceType* Container = Manager_Damage->AllocateModifier(Type);
				ModifierType* Copy				= Container->Get();

				CopyType* ICopy = CsDamageModifierLibrary::GetInterfaceChecked<CopyType>(Context, Copy);

				ICopy->Copy(Modifier);
				return Container;
			}

			ModifierResourceType* FLibrary::CopyChecked(const FString& Context, const UObject* WorldContext, const ModifierResourceType* Modifier)
			{
				CS_IS_PTR_NULL_CHECKED(Modifier)

				return CopyChecked(Context, WorldContext, Modifier->Get());
			}

			void FLibrary::CopyChecked(const FString& Context, const UObject* WorldContext, const TArray<ModifierType*>& From, TArray<ModifierResourceType*>& To)
			{
				CS_IS_TARRAY_ANY_NULL_CHECKED(From, ModifierType)

				To.Reset(FMath::Max(To.Max(), From.Num()));

				for (const ModifierType* Modifier : From)
				{
					To.Add(CopyChecked(Context, WorldContext, Modifier));
				}
			}

			void FLibrary::CopyChecked(const FString& Context, const UObject* WorldContext, const TArray<ModifierType*>& From, TArray<AllocatedModifierType>& To)
			{
				UObject* ContextRoot = CsDamageManagerLibrary::GetContextRootChecked(Context, WorldContext);

				CS_IS_TARRAY_ANY_NULL_CHECKED(From, ModifierType)

				To.Reset(FMath::Max(To.Max(), From.Num()));

				for (const ModifierType* Modifier : From)
				{
					AllocatedModifierType& Allocated = To.AddDefaulted_GetRef();
					Allocated.Copy(ContextRoot, Modifier);
				}
			}

			void FLibrary::CopyChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier, ModifierResourceType*& OutContainer, FECsDamageModifier& OutType)
			{
				UCsManager_Damage* Manager_Damage = CsDamageManagerLibrary::GetChecked(Context, WorldContext);

				OutType				= CsDamageModifierLibrary::GetTypeChecked(Context, Modifier);
				OutContainer		= Manager_Damage->AllocateModifier(OutType);
				ModifierType* Copy	= OutContainer->Get();

				CopyType* ICopy = CsDamageModifierLibrary::GetInterfaceChecked<CopyType>(Context, Copy);

				ICopy->Copy(Modifier);
			}
		}
	}
}