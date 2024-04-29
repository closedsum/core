// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "Types/CsTypes_Beam.h"
// Log
#include "Utility/CsBeamLog.h"

class UObject;
class UCsManager_Beam;

// NCsData::NManager::NHandler::TData
namespace NCsData {
	namespace NManager {
		namespace NHandler {
			template<typename InterfaceDataType, typename DataContainerType, typename DataInterfaceMapType>
			class TData;
		}
	}
}

// NCsBeam::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsBeam, NData, IData)
// NCsBeam::NData::FInterfaceMap
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsBeam, NData, FInterfaceMap)

namespace NCsBeam
{
	namespace NManager
	{
		struct CSBEAM_API FLibrary final
		{
		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Beam from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_Beam
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* WorldContext) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Beam from a WorldContext.
			*
			* @param Context		The calling context.
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				Context for UCsManager_Beam
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsBeam::FLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsBeam::FLog::Warning) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Beam from a WorldContext.
			*
			* @oaram WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Context for UCsManager_Beam
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
			* Get the reference to UCsManager_Beam from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_Beam.
			*/
			static UCsManager_Beam* GetChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get the reference to UCsManager_Beam from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				UCsManager_Beam.
			*/
			static UCsManager_Beam* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsBeam::FLog::Warning);

			/**
			* Safely get the reference to UCsManager_Beam from a WorldContext.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				UCsManager_Beam.
			*/
			static UCsManager_Beam* GetSafe(const UObject* WorldContext);

		#pragma endregion Get

		// Settings
		#pragma region
		public:

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Key
			* @param Value
			*/
			static void SetAndAddTypeMapKeyValueChecked(const FString& Context, const UObject* WorldContext, const FECsBeam& Key, const FECsBeam& Value);

			/**
			*
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Key
			* @param Value
			* @param Log			(optional)
			*/
			static void SafeSetAndAddTypeMapKeyValue(const FString& Context, const UObject* WorldContext, const FECsBeam& Key, const FECsBeam& Value, void(*Log)(const FString&) = &NCsBeam::FLog::Warning);

		#pragma endregion Settings

		// Data
		#pragma region
		public:

		#define DataType NCsBeam::NData::IData

		#define DataHandlerType NCsData::NManager::NHandler::TData
		#define DataInterfaceMapType NCsBeam::NData::FInterfaceMap

			/**
			* 
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			*/
			static DataHandlerType<DataType, FCsData_BeamPtr, DataInterfaceMapType>* GetSafeDataHandler(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) = &NCsBeam::FLog::Warning);

		#undef DataHandlerType
		#undef DataInterfaceMapType

			/**
			* Get the Data (implements interface: DataType (NCsBeam::NData::IData)) associated with Name of the weapon type.
			* "Checked" in regards to returning a valid pointer.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name			Name of the Weapon.
			* return				Data that implements the interface: DataType (NCsBeam::NData::IData).
			*/
			static DataType* GetDataChecked(const FString& Context, const UObject* WorldContext, const FName& Name);

			/**
			* Safely get the Data (implements interface: DataType (NCsBeam::NData::IData)) associated with Name of the weapon type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Name			Name of the Weapon.
			* @param Log			(optional)
			* return				Data that implements the interface: DataType (NCsBeam::NData::IData).
			*/
			static DataType* GetSafeData(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsBeam::FLog::Warning);

			/**
			* Get the Data (implements interface: DataType (NCsBeam::NData::IData)) associated with Type.
			* "Checked" in regards to returning a valid pointer.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			Weapon type.
			* return				Data that implements the interface: DataType (NCsBeam::NData::IData).
			*/
			static DataType* GetDataChecked(const FString& Context, const UObject* WorldContext, const FECsBeam& Type);

			/**
			* Get the Data (implements interface: DataType (NCsBeam::NData::IData)) associated with Type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type			Weapon type.
			* @param Log			(optional)
			* return				Data that implements the interface: DataType (NCsBeam::NData::IData).
			*/
			static DataType* GetSafeData(const FString& Context, const UObject* WorldContext, const FECsBeam& Type, void(*Log)(const FString&) = &NCsBeam::FLog::Warning);

		#undef DataType

		#pragma endregion Data
		};
	}
}