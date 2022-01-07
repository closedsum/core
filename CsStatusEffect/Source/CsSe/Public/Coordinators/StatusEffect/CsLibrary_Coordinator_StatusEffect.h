// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsTypes_StatusEffect.h"
// Log
#include "Utility/CsSeLog.h"

class UObject;
class UCsCoordinator_StatusEffect;

// NCsPooledObject::NManager::NHandler::TData
namespace NCsPooledObject {
	namespace NManager {
		namespace NHandler {
			template<typename InterfaceDataType, typename DataContainerType, typename DataInterfaceMapType>
			class TData;
		}
	}
}

// NCsStatusEffect::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NData, IData)
// NCsStatusEffect::NData::FInterfaceMap
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStatusEffect, NData, FInterfaceMap)

namespace NCsStatusEffect
{
	namespace NCoordinator
	{
		struct CSSE_API FLibrary final
		{
		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsCoordinator_StatusEffect from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsCoordinator_StatusEffect
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsCoordinator_StatusEffect from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				Context for UCsCoordinator_StatusEffect
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsCoordinator_StatusEffect from a WorldContext.
			*
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsCoordinator_StatusEffect
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
			* Get the reference to UCsCoordinator_StatusEffect from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsCoordinator_StatusEffect.
			*/
			static UCsCoordinator_StatusEffect* GetChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get the reference to UCsCoordinator_StatusEffect from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				UCsCoordinator_StatusEffect.
			*/
			static UCsCoordinator_StatusEffect* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning);

			/**
			* Safely get the reference to UCsCoordinator_StatusEffect from a WorldContext.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsCoordinator_StatusEffect.
			*/
			static UCsCoordinator_StatusEffect* GetSafe(const UObject* WorldContext);

		#pragma endregion Get

		// Data
		#pragma region
		public:

		#define DataType NCsStatusEffect::NData::IData

		#define DataHandlerType NCsPooledObject::NManager::NHandler::TData
		#define DataInterfaceMapType NCsStatusEffect::NData::FInterfaceMap

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			*/
			static DataHandlerType<DataType, FCsData_StatusEffectPtr, DataInterfaceMapType>* GetSafeDataHandler(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning);

		#undef DataHandlerType
		#undef DataInterfaceMapType

			/**
			* Get the Data (implements interface: DataType (NCsStatusEffect::NData::IData)) associated with Name of the Status Effect type.
			* "Checked" in regards to returning a valid pointer.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name			Name of the Status Effect.
			* return				Data that implements the interface: DataType (NCsStatusEffect::NData::IData).
			*/
			static DataType* GetDataChecked(const FString& Context, const UObject* WorldContext, const FName& Name);

			/**
			* Safely get the Data (implements interface: DataType (NCsStatusEffect::NData::IData)) associated with Name of the Status Effect type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name			Name of the Status Effect.
			* @param Log			(optional)
			* return				Data that implements the interface: DataType (NCsStatusEffect::NData::IData).
			*/
			static DataType* GetSafeData(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning);

			/**
			* Get the Data (implements interface: DataType (NCsStatusEffect::NData::IData)) associated with Type.
			* "Checked" in regards to returning a valid pointer.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			Status Effect type.
			* return				Data that implements the interface: DataType (NCsStatusEffect::NData::IData).
			*/
			static DataType* GetDataChecked(const FString& Context, const UObject* WorldContext, const FECsStatusEffect& Type);

			/**
			* Get the Data (implements interface: DataType (NCsStatusEffect::NData::IData)) associated with Type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			Status Effect type.
			* @param Log			(optional)
			* return				Data that implements the interface: DataType (NCsStatusEffect::NData::IData).
			*/
			static DataType* GetSafeData(const FString& Context, const UObject* WorldContext, const FECsStatusEffect& Type, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning);

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			Status Effect type.
			* @param Instigator
			* @param Causer
			* @param Receiver
			*/
			static void ProcessDataChecked(const FString& Context, const UObject* WorldContext, const FECsStatusEffect& Type, UObject* Instigator, UObject* Causer, UObject* Receiver);

		#undef DataType

		#pragma endregion Data
		};
	}
}