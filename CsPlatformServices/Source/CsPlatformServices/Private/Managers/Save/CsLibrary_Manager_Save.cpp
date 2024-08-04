// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Save/CsLibrary_Manager_Save.h"
#include "CsPlatformServices.h"

// Types
#include "CsMacro_Misc.h"
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

		#define USING_NS_CACHED using namespace NCsSave::NManager::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsSave::NManager::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* ContextObject)
		{
			return CsGameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&NCsPlatformServices::FLog::Warning*/)
		{
			return CsGameInstanceLibrary::GetSafeAsObject(Context, ContextObject, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* ContextObject)
		{
			SET_CONTEXT(GetSafeContextRoot);

			return GetSafeContextRoot(Context, ContextObject, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Save* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
		#if UE_BUILD_SHIPPING
			return UCsManager_Save::Get(nullptr);
		#else
			UObject* ContextRoot		  = GetContextRootChecked(Context, ContextObject);
			UCsManager_Save* Manager_Save = UCsManager_Save::Get(ContextRoot);

			CS_IS_PENDING_KILL_CHECKED(Manager_Save)
			return Manager_Save;
		#endif // #if UE_BUILD_SHIPPING
		}

		UCsManager_Save* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*= &NCsPlatformServices::FLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Save* Manager_Save = UCsManager_Save::Get(ContextRoot);

			if (!IsValid(Manager_Save))
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Save."), *Context));
				return nullptr;
			}
			return Manager_Save;
		}

		UCsManager_Save* FLibrary::GetSafe(const UObject* ContextObject)
		{
			SET_CONTEXT(GetSafe);

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get

		// FileName
		#pragma region

		void FLibrary::SetCurrentSaveChecked(const FString& Context, const UObject* ContextObject, const ECsSave& Save)
		{
			CS_IS_ENUM_VALID_CHECKED(EMCsSave, Save)

			GetChecked(Context, ContextObject)->SetCurrentSave(Save);
		}

		bool FLibrary::SetSafeCurrentSave(const FString& Context, const UObject* ContextObject, const ECsSave& Save, void(*Log)(const FString&) /*=&NCsPlatformServices::FLog::Warning*/)
		{
			if (UCsManager_Save* Manager_Save = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_ENUM_VALID(EMCsSave, ECsSave, Save)

				Manager_Save->SetCurrentSave(Save);
				return true;
			}
			return false;
		}

		#pragma endregion FileName

		// Enumerate
		#pragma region

		void FLibrary::EnumerateChecked(const FString& Context, const UObject* ContextObject)
		{
			GetChecked(Context, ContextObject)->Enumerate();
		}

		bool FLibrary::SafeEnumerate(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&NCsPlatformServices::FLog::Warning*/)
		{
			if (UCsManager_Save* Manager_Save = GetSafe(Context, ContextObject, Log))
			{
				Manager_Save->Enumerate();
				return true;
			}
			return false;
		}

		#pragma endregion Enumerate

		// Read
		#pragma region
		
		void FLibrary::ReadChecked(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save)
		{
			GetChecked(Context, ContextObject)->Read(Profile, Save);
		}

		bool FLibrary::SafeRead(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save, void(*Log)(const FString&) /*=&NCsPlatformServices::FLog::Warning*/)
		{
			if (UCsManager_Save* Manager_Save = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_ENUM_VALID(EMCsPlayerProfile, ECsPlayerProfile, Profile)
				CS_IS_ENUM_VALID(EMCsSave, ECsSave, Save)

				Manager_Save->Read(Profile, Save);
				return true;
			}
			return false;
		}

		void FLibrary::ReadAllChecked(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile)
		{
			GetChecked(Context, ContextObject)->ReadAll(Profile);
		}

		bool FLibrary::SafeReadAll(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, void(*Log)(const FString&) /*=&NCsPlatformServices::FLog::Warning*/)
		{
			if (UCsManager_Save* Manager_Save = GetSafe(Context, ContextObject, Log))
			{
				Manager_Save->ReadAll(Profile);
				return true;
			}
			return false;
		}

		#pragma endregion Read

		// Write
		#pragma region

		void FLibrary::WriteChecked(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save)
		{
			GetChecked(Context, ContextObject)->Write(Profile, Save);
		}

		bool FLibrary::SafeWrite(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save, void(*Log)(const FString&) /*=&NCsPlatformServices::FLog::Warning*/)
		{
			if (UCsManager_Save* Manager_Save = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_ENUM_VALID(EMCsPlayerProfile, ECsPlayerProfile, Profile)
				CS_IS_ENUM_VALID(EMCsSave, ECsSave, Save)

				Manager_Save->Write(Profile, Save);
				return true;
			}
			return false;
		}

		void FLibrary::WriteAllChecked(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile)
		{
			GetChecked(Context, ContextObject)->WriteAll(Profile);
		}

		bool FLibrary::SafeWriteAll(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, void(*Log)(const FString&) /*=&NCsPlatformServices::FLog::Warning*/)
		{
			if (UCsManager_Save* Manager_Save = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_ENUM_VALID(EMCsPlayerProfile, ECsPlayerProfile, Profile)

				Manager_Save->WriteAll(Profile);
				return true;
			}
			return false;
		}

		#pragma endregion Write

		// Delete
		#pragma region

		void FLibrary::DeleteChecked(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save)
		{
			GetChecked(Context, ContextObject)->Delete(Profile, Save);
		}

		bool FLibrary::SafeDelete(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, const ECsSave& Save, void(*Log)(const FString&) /*=&NCsPlatformServices::FLog::Warning*/)
		{
			if (UCsManager_Save* Manager_Save = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_ENUM_VALID(EMCsPlayerProfile, ECsPlayerProfile, Profile)
				CS_IS_ENUM_VALID(EMCsSave, ECsSave, Save)

				Manager_Save->Delete(Profile, Save);
				return true;
			}
			return false;
		}

		void FLibrary::DeleteAllChecked(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile)
		{
			GetChecked(Context, ContextObject)->DeleteAll(Profile);
		}

		bool FLibrary::SafeDeleteAll(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& Profile, void(*Log)(const FString&) /*=&NCsPlatformServices::FLog::Warning*/)
		{
			if (UCsManager_Save* Manager_Save = GetSafe(Context, ContextObject, Log))
			{
				CS_IS_ENUM_VALID(EMCsPlayerProfile, ECsPlayerProfile, Profile)

				Manager_Save->DeleteAll(Profile);
				return true;
			}
			return false;
		}

		void FLibrary::DeleteAllContentChecked(const FString& Context, const UObject* ContextObject)
		{
			GetChecked(Context, ContextObject)->DeleteAllContent();
		}

		bool FLibrary::SafeDeleteAllContent(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*=&NCsPlatformServices::FLog::Warning*/)
		{
			if (UCsManager_Save* Manager_Save = GetSafe(Context, ContextObject, Log))
			{
				Manager_Save->DeleteAllContent();
				return true;
			}
			return false;
		}

		#pragma endregion Delete

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}