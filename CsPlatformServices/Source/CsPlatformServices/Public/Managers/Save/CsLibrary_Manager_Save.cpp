// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Save/CsLibrary_Manager_Save.h"
#include "CsPlatformServices.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/Save/CsManager_Save.h"

namespace NCsSave
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSave::NManager::FLibrary, GetSafeContextRoot);
					CSPLATFORMSERVICES_API CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSave::NManager::FLibrary, GetSafe);
				}
			}
		}

		// ContextRoot
		#pragma region

	#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
		{
			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsGameInstance::FLibrary GameInstanceLibrary;

			return GameInstanceLibrary::GetSafeAsObject(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* ContextObject)
		{
			using namespace NCsSave::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Save* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* ContextRoot		  = GetContextRootChecked(Context, ContextObject);
			UCsManager_Save* Manager_Save = UCsManager_Save::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Save)
			return Manager_Save;
		}

		UCsManager_Save* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*= &FCsLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Save* Manager_Save = UCsManager_Save::Get(ContextRoot);

			if (!Manager_Save)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Save."), *Context));
			}
			return Manager_Save;
		}

		UCsManager_Save* FLibrary::GetSafe(const UObject* ContextObject)
		{
			using namespace NCsSave::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get

		// FileName
		#pragma region

		void FLibrary::SetCurrentSaveChecked(const FString& Context, const UObject* ContextObject, const ECsSave& Save)
		{
			UCsManager_Save* Manager_Save = GetChecked(Context, ContextObject);
			
			check(EMCsSave::Get().IsValidEnumChecked(Context, Save));

			Manager_Save->SetCurrentSave(Save);
		}

		void FLibrary::SetSafeCurrentSave(const FString& Context, const UObject* ContextObject, const ECsSave& Save, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Save* Manager_Save = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_ENUM_VALID_EXIT(EMCsSave, ECsSave, Save)

				Manager_Save->SetCurrentSave(Save);
			}
		}

		#pragma endregion FileName

		// Enumerate
		#pragma region

		void FLibrary::EnumerateChecked(const FString& Context, const UObject* ContextObject)
		{
			GetChecked(Context, ContextObject)->Enumerate();
		}

		void FLibrary::SafeEnumerate(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Save* Manager_Save = GetSafe(Context, ContextObject, Log))
			{
				Manager_Save->Enumerate();
			}
		}

		#pragma endregion Enumerate

		// Read
		#pragma region
		
		void FLibrary::ReadChecked(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save)
		{
			GetChecked(Context, ContextObject)->Read(Profile, Save);
		}

		void FLibrary::SafeRead(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Save* Manager_Save = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_ENUM_VALID_EXIT(EMCsPlayerProfile, ECsPlayerProfile, Profile)

				CS_IS_ENUM_VALID_EXIT(EMCsSave, ECsSave, Save)

				Manager_Save->Read(Profile, Save);
			}
		}

		void FLibrary::ReadAllChecked(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile)
		{
			GetChecked(Context, ContextObject)->ReadAll(Profile);
		}

		void FLibrary::SafeReadAll(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Save* Manager_Save = GetSafe(Context, ContextObject, Log))
			{
				Manager_Save->ReadAll(Profile);
			}
		}

		#pragma endregion Read

		// Write
		#pragma region

		void FLibrary::WriteChecked(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save)
		{
			GetChecked(Context, ContextObject)->Write(Profile, Save);
		}

		void FLibrary::SafeWrite(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Save* Manager_Save = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_ENUM_VALID_EXIT(EMCsPlayerProfile, ECsPlayerProfile, Profile)

				CS_IS_ENUM_VALID_EXIT(EMCsSave, ECsSave, Save)

				Manager_Save->Write(Profile, Save);
			}
		}

		void FLibrary::WriteAllChecked(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile)
		{
			GetChecked(Context, ContextObject)->WriteAll(Profile);
		}

		void FLibrary::SafeWriteAll(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Save* Manager_Save = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_ENUM_VALID_EXIT(EMCsPlayerProfile, ECsPlayerProfile, Profile)

				Manager_Save->WriteAll(Profile);
			}
		}

		#pragma endregion Write

		// Delete
		#pragma region

		void FLibrary::DeleteChecked(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save)
		{
			GetChecked(Context, ContextObject)->Delete(Profile, Save);
		}

		void FLibrary::SafeDelete(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Save* Manager_Save = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_ENUM_VALID_EXIT(EMCsPlayerProfile, ECsPlayerProfile, Profile)

				CS_IS_ENUM_VALID_EXIT(EMCsSave, ECsSave, Save)

				Manager_Save->Delete(Profile, Save);
			}
		}

		void FLibrary::DeleteAllChecked(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile)
		{
			GetChecked(Context, ContextObject)->DeleteAll(Profile);
		}

		void FLibrary::SafeDeleteAll(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Save* Manager_Save = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_ENUM_VALID_EXIT(EMCsPlayerProfile, ECsPlayerProfile, Profile)

				Manager_Save->DeleteAll(Profile);
			}
		}

		void FLibrary::DeleteAllContentChecked(const FString& Context, const UObject* ContextObject)
		{
			GetChecked(Context, ContextObject)->DeleteAllContent();
		}

		void FLibrary::SafeDeleteAllContent(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			if (UCsManager_Save* Manager_Save = GetSafe(Context, ContextObject, Log))
			{
				Manager_Save->DeleteAllContent();
			}
		}

		#pragma endregion Delete
	}
}