// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Value/Types/CsTypes_DamageValue.h"
#include "Managers/Damage/Data/Types/CsTypes_Data_Damage.h"
// Damage
#include "Modifier/CsAllocated_DamageModifier.h"
#include "Process/Payload/CsProcessDamageDataPayload.h"
// Log
#include "Utility/CsDmgLog.h"

class UObject;
class UCsManager_Damage;

// NCsDamage::NEvent::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NEvent, FResource)
// NCsDamage::NEvent::IEvent
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NEvent, IEvent)

// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)
// NCsData::IGetDamageDataType
CS_FWD_DECLARE_STRUCT_NAMESPACE_1(NCsData, IGetDamageDataType)
// NCsData::IGetDamageDataTypes
CS_FWD_DECLARE_STRUCT_NAMESPACE_1(NCsData, IGetDamageDataTypes)

// NCsDamage::NValue::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, FResource)
// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)
// NCsDamage::NRange::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NRange, FResource)

// NCsDamage::NRange::IRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NRange, IRange)
// NCsDamage::NModifier::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, FResource)
// NCsDamage::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, IModifier)

// NCsData::NManager::NHandler::TData
namespace NCsData {
	namespace NManager {
		namespace NHandler {
			template<typename InterfaceDataType, typename DataContainerType, typename DataInterfaceMapType>
			class TData;
		}
	}
}

// NCsDamage::NData::FInterfaceMap
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, FInterfaceMap)

namespace NCsDamage
{
	namespace NManager
	{
		struct CSDMG_API FLibrary final
		{
		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Damage from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_Damage
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Damage from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				Context for UCsManager_Damage
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsDamage::FLog::Warning) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Damage from a WorldContext.
			*
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_Damage
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
			* Get the reference to UCsManager_Damage from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_Damage.
			*/
			static UCsManager_Damage* GetChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get the reference to UCsManager_Damage from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				UCsManager_Damage.
			*/
			static UCsManager_Damage* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);

			/**
			* Safely get the reference to UCsManager_Damage from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_Damage.
			*/
			static UCsManager_Damage* GetSafe(const UObject* WorldContext);

		#pragma endregion Get

		// Event
		#pragma region
		public:

		#define EventResourceType NCsDamage::NEvent::FResource
		#define EventType NCsDamage::NEvent::IEvent

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Event
			*/
			static void DeallocateEventChecked(const FString& Context, const UObject* WorldContext, EventResourceType* Event);

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Event
			* return
			*/
			static EventResourceType* CreateCopyOfEventChecked(const FString& Context, const UObject* WorldContext, const EventType* Event);

			/**
			*
			*
			* @param Context			The calling context.
			* @param WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
			* @param OutEventContainer
			* @param OutEvent
			*/
			static void CreateCopyOfEventChecked(const FString& Context, const UObject* WorldContext, const EventType* Event, EventResourceType*& OutEventContainer, EventType*& OutEvent);

		#define GetDamageDataTypeDataType NCsData::IGetDamageDataType
		#define ProcessPayloadType NCsDamage::NData::NProcess::FPayload

			/**
			*
			*
			* @param Context			The calling context.
			* @param WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
			* @param Data
			* @param Instigator
			* @param Causer
			* @param HitResult
			*/
			static EventResourceType* CreateEventChecked(const FString& Context, const UObject* WorldContext, const ProcessPayloadType& ProcessPayload);

			/**
			*
			*
			* @param Context			The calling context.
			* @param WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
			* @param Data
			* @param Instigator
			* @param Causer
			* @param HitResult
			*/
			static EventResourceType* CreateEventChecked(const FString& Context, const UObject* WorldContext, const GetDamageDataTypeDataType* GetDamageDataType, const ProcessPayloadType& ProcessPayload);

		#undef GetDamageDataTypeDataType
		#undef ProcessPayloadType

			static void ProcessEventChecked(const FString& Context, const UObject* WorldContext, const EventType* Event);

		#undef EventResourceType
		#undef EventType

		#pragma endregion Event

		// Value
		#pragma region
		public:

		#define ValueResourceType NCsDamage::NValue::FResource
		#define ValueType NCsDamage::NValue::IValue

		/**
		*
		*
		* @param Type
		* @param Value
		*/
		static void DeallocateValueChecked(const FString& Context, const UObject* WorldContext, const FECsDamageValue& Type, ValueResourceType* Value);

		/**
		*
		*
		* @param Context	The calling context.
		* @param Value
		* return
		*/
		static ValueResourceType* CreateCopyOfValueChecked(const FString& Context, const UObject* WorldContext, const ValueType* Value);

		/**
		*
		*
		* @param Context	The calling context.
		* @param Value
		* return
		*/
		static ValueResourceType* CreateCopyOfValueChecked(const FString& Context, const UObject* WorldContext, const ValueResourceType* Value);

		#undef ValueResourceType
		#undef ValueType

		#pragma endregion Value

		// Range
		#pragma region
		public:

		#define RangeResourceType NCsDamage::NRange::FResource
		#define RangeType NCsDamage::NRange::IRange

		static void DeallocateRangeChecked(const FString& Context, const UObject* WorldContext, RangeResourceType* Range);

		static RangeResourceType* CreateCopyOfRangeChecked(const FString& Context, const UObject* WorldContext, const RangeType* Range);

		static RangeResourceType* CreateCopyOfRangeChecked(const FString& Context, const UObject* WorldContext, const RangeResourceType* Range);

		#undef RangeResourceType
		#undef RangeType

		#pragma endregion Range

		// Data
		#pragma region
		public:

		#define DataType NCsDamage::NData::IData

			static const FECsDamageData& GetDataTypeChecked(const FString& Context, const UObject* WorldContext, const DataType* Data);

			/**
			* Get the Data, Object that implements the interface: DataType (NCsDamage::NData::IData),
			* associated with the Type.
			*
			* @param Context			The calling context.
			* @oaram WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* return					Object which implements the interface: DataType (NCsDamage::NData::IData).
			*/
			static DataType* GetDataChecked(const FString& Context, const UObject* WorldContext, const FECsDamageData& Type);

		#define GetDamageDataTypeDataType NCsData::IGetDamageDataType

			/**
			* Get the Data, Object that implements the interface: DataType (NCsDamage::NData::IData), 
			* associated with the result of GetDamageDataType->GetDamageDataType (FECsDamageData).
			* 
			* @param Context			The calling context.
			* @oaram WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
			* @param GetDamageDataType
			* return					Object which implements the interface: DataType (NCsDamage::NData::IData).
			*/
			static DataType* GetDataChecked(const FString& Context, const UObject* WorldContext, const GetDamageDataTypeDataType* GetDamageDataType);

			/**
			* Safely get the Data, Object that implements the interface: DataType (NCsDamage::NData::IData),
			* associated with the result of GetDamageDataType->GetDamageDataType (FECsDamageData).
			*
			* @param Context			The calling context.
			* @oaram WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
			* @param GetDamageDataType
			* @param Log				(optional)
			* return					Object which implements the interface: DataType (NCsDamage::NData::IData).
			*/
			static DataType* GetSafeData(const FString& Context, const UObject* WorldContext, const GetDamageDataTypeDataType* GetDamageDataType, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);

		#undef GetDamageDataTypeDataType

		#define GetDamageDataTypeDataTypes NCsData::IGetDamageDataTypes

			/**
			* Get the Datas, Objects that implements the interface: DataType (NCsDamage::NData::IData),
			* associated with the associated Types.
			*
			* @param Context			The calling context.
			* @oaram WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
			* @param DamageDataTypes
			* @param OutDatas			(out) Objects which implements the interface: DataType (NCsDamage::NData::IData).
			*/
			static void GetDatasChecked(const FString& Context, const UObject* WorldContext, const TArray<FECsDamageData>& DamageDataTypes, TArray<DataType*>& OutDatas);

			/**
			* Get the Datas, Objects that implements the interface: DataType (NCsDamage::NData::IData), 
			* associated with the result of GetDamageDataTypes->GetDamageDataTypes (TArray<FECsDamageData>).
			* 
			* @param Context			The calling context.
			* @oaram WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
			* @param GetDamageDataTypes
			* @param OutDatas			(out) Objects which implements the interface: DataType (NCsDamage::NData::IData).
			*/
			static void GetDatasChecked(const FString& Context, const UObject* WorldContext, const GetDamageDataTypeDataTypes* GetDamageDataTypes, TArray<DataType*>& OutDatas);

			/**
			* Safely, get the Datas, Objects that implements the interface: DataType (NCsDamage::NData::IData),
			* associated with the result of GetDamageDataTypes->GetDamageDataTypes (TArray<FECsDamageData>).
			*
			* @param Context			The calling context.
			* @oaram WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
			* @param GetDamageDataTypes
			* @param OutDatas			(out) Objects which implements the interface: DataType (NCsDamage::NData::IData).
			* @param Log				(optional)
			* return
			*/
			static bool GetSafeDatas(const FString& Context, const UObject* WorldContext, const GetDamageDataTypeDataTypes* GetDamageDataTypes, TArray<DataType*>& OutDatas, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);

		#undef GetDamageDataTypeDataTypes
			
			/**
			* Get the Data as a UObject (implements interface: DataType (ICsData_Damage)) associated with Type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name			Name of the Damage type.
			* @param Log			(optional)
			* return				Data that implements the interface: DataType (ICsData_Damage).
			*/
			static UObject* GetSafeDataAsObject(const FString& Context, const UObject* WorldContext, const FECsDamageData& Type, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);

			/**
			* Get the Data as a UObject (implements interface: DataType (ICsData_Damage)) associated with Type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name			Name of the Damage type.
			* @param Log			(optional)
			* return				Data that implements the interface: DataType (ICsData_Damage).
			*/
			static UObject* GetSafeDataAsObject(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);

			/**
			* Add the Datas, Objects that implements the interface: DataType (NCsDamage::NData::IData),
			* associated with the result of GetDamageDataTypes->GetDamageDataTypes (TArray<FECsDamageData>).
			*
			* @param Context			The calling context.
			* @oaram WorldContext		Object that contains a reference to a World (GetWorld() is Valid).
			* @param GetDamageDataTypes
			* @param OutDatas			(out) Objects which implements the interface: DataType (NCsDamage::NData::IData).
			*/
			static void AddDatasChecked(const FString& Context, const UObject* WorldContext, const TArray<FECsDamageData>& DamageDataTypes, TArray<DataType*>& OutDatas);

		#define DataHandlerType NCsData::NManager::NHandler::TData
		#define DataInterfaceMapType NCsDamage::NData::FInterfaceMap

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			*/
			static DataHandlerType<DataType, FCsData_DamagePtr, DataInterfaceMapType>* GetSafeDataHandler(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);

		#undef DataHandlerType
		#undef DataInterfaceMapType

		#define ModifierType NCsDamage::NModifier::IModifier
		#define ValueType NCsDamage::NValue::IValue
		#define RangeType NCsDamage::NRange::IRange

			/**
			* Process, create a Damage Event, and broadcast the Event with Data, Instigator, Causer, HitResult, and Modifiers
			*  Modifiers are applied to the Value and/or Range after the Event is created.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Data			Object that implements the interface: DataType (NCsDamage::NData::IData).
			* @param Instigator
			* @param Causer
			* @param HitResult
			* @param Modifiers
			*/
			static void ProcessDataChecked(const FString& Context, const UObject* WorldContext, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierType*>& Modifiers);

			/**
			* Process, create a Damage Event (NCsDamage::NEvent::IEvent), and broadcast the Event
			* with Damage Data (NCsDamage::NData::IData) associated with type: Data, Instigator, Causer, and HitResult.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Value			Object that implements the interface: ValueType (NCsDamage::NValue::IValue).
			* @param Data			Type associated with object that implements the interface: DataType (NCsDamage::NData::IData).
			* @param Instigator
			* @param Causer
			* @param HitResult
			*/
			static void ProcessDataChecked(const FString& Context, const UObject* WorldContext, const FECsDamageData& Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult);

			/**
			* Process, create a Damage Event (NCsDamage::NEvent::IEvent), and broadcast the Event
			* with Data, Instigator, Causer, HitResult, and Modifiers
			*  Modifiers are applied to the Value and/or Range after the Event is created.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Data			Object that implements the interface: DataType (NCsDamage::NData::IData).
			* @param Instigator
			* @param Causer
			* @param HitResult
			* @param Modifiers
			* @param Log			(optional)
			* return				Whether the Damage Event was created or not.
			*/
			static bool SafeProcessData(const FString& Context, const UObject* WorldContext, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierType*>& Modifiers, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);

			/**
			* Safely process, create a Damage Event (NCsDamage::NEvent::IEvent), and broadcast the Event
			* with Data (NCsDamage::NData::IData) associated with DataName, Instigator, Causer, and HitResult.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param DataName		Name associated with Data that implements the interface: DataType (NCsDamage::NData::IData).
			* @param Instigator
			* @param Causer
			* @param HitResult
			* @param Log			(optional)
			* return				Whether the Damage Event was created or not.
			*/
			static bool SafeProcessData(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, void(*Log)(const FString&) = &NCsDamage::FLog::Warning);

			/**
			* Process, create a Damage Event (NCsDamage::NEvent::IEvent), and broadcast the Event 
			* with Data, Value, Instigator, Causer, HitResult, and Modifiers
			*  Modifiers are applied to the Value and/or Range after the Event is created.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Value			Object that implements the interface: ValueType (NCsDamage::NValue::IValue).
			* @param Data			Object that implements the interface: DataType (NCsDamage::NData::IData).
			* @param Instigator
			* @param Causer
			* @param HitResult
			*/
			static void ProcessDataChecked(const FString& Context, const UObject* WorldContext, const ValueType* Value, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierType*>& Modifiers);

			/**
			* Process, create a Damage Event, and broadcast the Event with Data, Value, Instigator, Causer, and HitResult
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Value			Object that implements the interface: ValueType (NCsDamage::NValue::IValue).
			* @param Data			Object that implements the interface: DataType (NCsDamage::NData::IData).
			* @param Instigator
			* @param Causer
			* @param HitResult
			*/
			static void ProcessDataChecked(const FString& Context, const UObject* WorldContext, const ValueType* Value, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult);

			/**
			* Process, create a Damage Event, and broadcast the Event with Data, Value, Range, Instigator, Causer, HitResult, and Modifiers
			*  Modifiers are applied to the Value and/or Range after the Event is created.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Value			Object that implements the interface: ValueType (NCsDamage::NValue::IValue).
			* @param Range			Object that implements the interface: RangeType (NCsDamage::NRange::IRange).
			* @param Data			Object that implements the interface: DataType (NCsDamage::NData::IData).
			* @param Instigator
			* @param Causer
			* @param HitResult
			* @param Modifiers
			*/
			static void ProcessDataChecked(const FString& Context, const UObject* WorldContext, const ValueType* Value, const RangeType* Range, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierType*>& Modifiers);

			/**
			* Process, create a Damage Event, and broadcast the Event with Data, Value, Instigator, Causer, and HitResult
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Value			Object that implements the interface: ValueType (NCsDamage::NValue::IValue).
			* @param Range			Object that implements the interface: RangeType (NCsDamage::NRange::IRange).
			* @param Data			Object that implements the interface: DataType (NCsDamage::NData::IData).
			* @param Instigator
			* @param Causer
			* @param HitResult
			*/
			static void ProcessDataChecked(const FString& Context, const UObject* WorldContext, const ValueType* Value, const RangeType* Range, DataType* Data, const FECsDamageData& Type, UObject* Instigator, UObject* Causer, const FHitResult& HitResult);

		#define ProcessPayloadType NCsDamage::NData::NProcess::FPayload

			/**
			* Process, create a Damage Event, and broadcast the Event with Data, Value, Instigator, Causer, and HitResult
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param ProcessPayload
			*/
			static void ProcessDataChecked(const FString& Context, const UObject* WorldContext, const ProcessPayloadType& ProcessPayload);

		#undef ProcessPayloadType

		#undef ModifierType
		#undef ValueType
		#undef RangeType

		#undef DataType

		#pragma endregion Data
		};

		namespace NModifier
		{
			struct CSDMG_API FLibrary final
			{
			public:

			#define ModifierResourceType NCsDamage::NModifier::FResource
			#define ModifierType NCsDamage::NModifier::IModifier
			#define AllocatedModifierType NCsDamage::NModifier::FAllocated
		
				static void DeallocateChecked(const FString& Context, const UObject* WorldContext, const FECsDamageModifier& Type, ModifierResourceType* Modifier);

				static const FECsDamageModifier& GetTypeChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier);

				static ModifierResourceType* CopyChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier);

				static ModifierResourceType* CopyChecked(const FString& Context, const UObject* WorldContext,  const ModifierResourceType* Modifier);

				static void CopyChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier, ModifierResourceType*& OutContainer, FECsDamageModifier& OutType);

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

			#undef ModifierResourceType
			#undef ModifierType
			#undef AllocatedModifierType
			};
		}
	}
}