// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Beam/CsLibrary_Manager_Beam.h"

// Types
#include "Types/CsTypes_Macro.h"
// Managers
#include "Managers/Beam/CsManager_Beam.h"
// Library
#include "Data/CsLibrary_Data_Beam.h"
#include "Library/CsLibrary_Valid.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameState.h"
#endif // #if WITH_EDITOR

namespace NCsBeam
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsBeam::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsBeam::NManager::FLibrary, GetSafe);
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

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/)
		{
			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetSafeAsObject(Context, WorldContext, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* WorldContext)
		{
			using namespace NCsBeam::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Beam* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
		{
			UObject* ContextRoot					  = GetContextRootChecked(Context, WorldContext);
			UCsManager_Beam* Manager_Beam = UCsManager_Beam::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Beam)
			return Manager_Beam;
		}

		UCsManager_Beam* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, WorldContext, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Beam* Manager_Beam = UCsManager_Beam::Get(ContextRoot);

			if (!Manager_Beam)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Beam."), *Context));
			}
			return Manager_Beam;
		}

		UCsManager_Beam* FLibrary::GetSafe(const UObject* WorldContext)
		{
			using namespace NCsBeam::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, WorldContext, nullptr);
		}

		#pragma endregion Get

		// Settings
		#pragma region

		void FLibrary::SetAndAddTypeMapKeyValueChecked(const FString& Context, const UObject* WorldContext, const FECsBeam& Key, const FECsBeam& Value)
		{
			check(EMCsBeam::Get().IsValidEnumChecked(Context, Key));

			check(EMCsBeam::Get().IsValidEnumChecked(Context, Value));

			GetChecked(Context, WorldContext)->SetAndAddTypeMapKeyValue(Key, Value);
		}

		void FLibrary::SafeSetAndAddTypeMapKeyValue(const FString& Context, const UObject* WorldContext, const FECsBeam& Key, const FECsBeam& Value, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/)
		{
			CS_IS_ENUM_STRUCT_VALID_EXIT(EMCsBeam, FECsBeam, Key)

			CS_IS_ENUM_STRUCT_VALID_EXIT(EMCsBeam, FECsBeam, Value)

			if (UCsManager_Beam* Manager_Beam = GetSafe(Context, WorldContext, Log))
			{
				Manager_Beam->SetAndAddTypeMapKeyValue(Key, Value);
			}
		}

		#pragma endregion Settings

		// Data
		#pragma region

		#define DataType NCsBeam::NData::IData

		#define DataHandlerType NCsData::NManager::NHandler::TData
		#define DataInterfaceMapType NCsBeam::NData::FInterfaceMap
		DataHandlerType<DataType, FCsData_BeamPtr, DataInterfaceMapType>* FLibrary::GetSafeDataHandler(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/)
		{
		#undef DataHandlerType
		#undef DataInterfaceMapType

			if (UCsManager_Beam* Manager_Beam = GetSafe(Context, WorldContext, Log))
			{
				return Manager_Beam->GetDataHandler();
			}
			return nullptr;
		}

		DataType* FLibrary::GetDataChecked(const FString& Context, const UObject* WorldContext, const FName& Name)
		{
			DataType* Data = GetChecked(Context, WorldContext)->GetDataChecked(Context, Name);

			typedef NCsBeam::NData::FLibrary BeamDataLibrary;

			check(BeamDataLibrary::IsValidChecked(Context, Data));

			return Data;
		}

		DataType* FLibrary::GetSafeData(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/)
		{
			if (UCsManager_Beam* Manager_Beam = GetSafe(Context, WorldContext, Log))
			{
				DataType* Data = Manager_Beam->GetSafeData(Context, Name);

				typedef NCsBeam::NData::FLibrary BeamDataLibrary;

				if (!BeamDataLibrary::IsValid(Context, Data, Log))
					return nullptr;
				return Data;
			}
			return nullptr;
		}

		DataType* FLibrary::GetDataChecked(const FString& Context, const UObject* WorldContext, const FECsBeam& Type)
		{
			DataType* Data = GetChecked(Context, WorldContext)->GetDataChecked(Context, Type);

			typedef NCsBeam::NData::FLibrary BeamDataLibrary;

			check(BeamDataLibrary::IsValidChecked(Context, Data));

			return Data;
		}

		DataType* FLibrary::GetSafeData(const FString& Context, const UObject* WorldContext, const FECsBeam& Type, void(*Log)(const FString&) /*=&NCsBeam::FLog::Warning*/)
		{
			if (UCsManager_Beam* Manager_Beam = GetSafe(Context, WorldContext, Log))
			{
				DataType* Data = Manager_Beam->GetSafeData(Context, Type);

				typedef NCsBeam::NData::FLibrary BeamDataLibrary;

				if (!BeamDataLibrary::IsValid(Context, Data, Log))
					return nullptr;
				return Data;
			}
			return nullptr;
		}

		#undef DataType

		#pragma endregion Data
	}
}