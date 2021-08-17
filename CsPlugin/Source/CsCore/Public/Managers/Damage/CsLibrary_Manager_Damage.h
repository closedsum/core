// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Managers/Damage/Value/CsTypes_DamageValue.h"
#include "Managers/Damage/Data/CsTypes_Data_Damage.h"
// Damage
#include "Managers/Damage/Modifier/CsAllocated_DamageModifier.h"
// Log
#include "Utility/CsLog.h"

#pragma once

class UObject;
class UCsManager_Damage;

// NCsDamage::NEvent::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NEvent, FResource)
// NCsDamage::NEvent::IEvent
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NEvent, IEvent)
// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)
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

// NCsPooledObject::NManager::NHandler::TData
namespace NCsPooledObject {
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
		struct CSCORE_API FLibrary final
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
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning) { return nullptr; }
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
			static UCsManager_Damage* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

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

		// Modifier
		#pragma region
		public:

		#define ModifierResourceType NCsDamage::NModifier::FResource
		#define ModifierType NCsDamage::NModifier::IModifier
		#define AllocatedModifierType NCsDamage::NModifier::FAllocated
		
			static void DeallocateModifierChecked(const FString& Context, const UObject* WorldContext, const FECsDamageModifier& Type, ModifierResourceType* Modifier);

			static const FECsDamageModifier& GetModifierTypeChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier);

			static ModifierResourceType* CreateCopyOfModifierChecked(const FString& Context, const UObject* WorldContext, const ModifierType* Modifier);

			static ModifierResourceType* CreateCopyOfModifierChecked(const FString& Context, const UObject* WorldContext,  const ModifierResourceType* Modifier);

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

		#undef ModifierResourceType
		#undef ModifierType
		#undef AllocatedModifierType

		#pragma endregion Modifier

		// Data
		#pragma region
		public:

		#define DataType NCsDamage::NData::IData

		#define DataHandlerType NCsPooledObject::NManager::NHandler::TData
		#define DataInterfaceMapType NCsDamage::NData::FInterfaceMap

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			*/
			static DataHandlerType<DataType, FCsData_DamagePtr, DataInterfaceMapType>* GetSafeDataHandler(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &FCsLog::Warning);

		#undef DataHandlerType
		#undef DataInterfaceMapType

		#define ModifierResourceType NCsDamage::NModifier::FResource
		#define ValueType NCsDamage::NValue::IValue

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Data
			* @param Instigator
			* @param Causer
			* @param HitResult
			* @param Modifiers
			*/
			static void ProcessDataChecked(const FString& Context, const UObject* WorldContext, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierResourceType*>& Modifiers);

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Data
			* @param Instigator
			* @param Causer
			* @param HitResult
			* @param Modifiers
			* @param Log			(optional)
			* return
			*/
			static bool SafeProcessData(const FString& Context, const UObject* WorldContext, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierResourceType*>& Modifiers, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param DataName
			* @param Instigator
			* @param Causer
			* @param HitResult
			* @param Log			(optional)
			* return
			*/
			static bool SafeProcessData(const FString& Context, const UObject* WorldContext, const FName& DataName, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Value
			* @param Data
			* @param Instigator
			* @param Causer
			* @param HitResult
			*/
			static void ProcessDataChecked(const FString& Context, const UObject* WorldContext, const ValueType* Value, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult, const TArray<ModifierResourceType*>& Modifiers);

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Value
			* @param Data
			* @param Instigator
			* @param Causer
			* @param HitResult
			*/
			static void ProcessDataChecked(const FString& Context, const UObject* WorldContext, const ValueType* Value, DataType* Data, UObject* Instigator, UObject* Causer, const FHitResult& HitResult);

		#undef ModifierResourceType
		#undef ValueType

		#undef DataType

		#pragma endregion Data
		};
	}
}