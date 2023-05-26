// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/PlayerProfile/CsLibrary_Manager_PlayerProfile.h"
#include "CsPlatformServices.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/PlayerProfile/CsManager_PlayerProfile.h"
// Game
#include "Engine/GameInstance.h"

namespace NCsPlayer
{
	namespace NProfile
	{
		namespace NManager
		{
			namespace NLibrary
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsPlayer::NProfile::NManager::FLibrary, GetSafeContextRoot);
					}
				}
			}

			// ContextRoot
			#pragma region

			#if WITH_EDITOR

			UObject* FLibrary::GetContextRootChecked(const FString& Context, UObject* ContextObject)
			{
				typedef NCsGameInstance::FLibrary GameInstanceLibrary;

				return GameInstanceLibrary::GetChecked(Context, ContextObject);
			}

			UObject* FLibrary::GetSafeContextRoot(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) /*=&FCsPlatformServicesLog::Warning*/)
			{
				typedef NCsGameInstance::FLibrary GameInstanceLibrary;

				return GameInstanceLibrary::GetSafe(Context, ContextObject, Log);
			}

			UObject* FLibrary::GetSafeContextRoot(UObject* ContextObject)
			{
				using namespace NCsPlayer::NProfile::NManager::NLibrary::NCached;

				const FString& Context = Str::GetSafeContextRoot;

				return GetSafeContextRoot(Context, ContextObject, nullptr);
			}

			#endif // #if WITH_EDITOR

			#pragma endregion ContextRoot

			// Get
			#pragma region

			UCsManager_PlayerProfile* FLibrary::GetChecked(const FString& Context, UObject* ContextObject)
			{
				UObject* ContextRoot							= GetContextRootChecked(Context, ContextObject);
				UCsManager_PlayerProfile* Manager_PlayerProfile = UCsManager_PlayerProfile::Get(ContextRoot);

				CS_IS_PTR_NULL_CHECKED(Manager_PlayerProfile)
				return Manager_PlayerProfile;
			}

			UCsManager_PlayerProfile* FLibrary::GetSafe(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) /*= &FCsPlatformServicesLog::Warning*/)
			{
				UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

			#if WITH_EDITOR
				if (!ContextRoot)
					return nullptr;
			#endif // #if WITH_EDITOR

				UCsManager_PlayerProfile* Manager_PlayerProfile = UCsManager_PlayerProfile::Get(ContextRoot);

				if (!Manager_PlayerProfile)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_PlayerProfile."), *Context));
				}
				return Manager_PlayerProfile;
			}

			#pragma endregion Get

			void FLibrary::SetCurrentActiveProfileChecked(const FString& Context, UObject* ContextObject, const ECsPlayerProfile& ProfileType)
			{
				GetChecked(Context, ContextObject)->SetCurrentActiveProfile(ProfileType);
			}

			void FLibrary::SetSafeCurrentActiveProfile(const FString& Context, UObject* ContextObject, const ECsPlayerProfile& ProfileType, void(*Log)(const FString&) /*=&FCsPlatformServicesLog::Warning*/)
			{
				if (UCsManager_PlayerProfile* Manager_PlayerProfile = GetSafe(Context, ContextObject))
				{
					CS_IS_ENUM_VALID_EXIT(EMCsPlayerProfile, ECsPlayerProfile, ProfileType);

					Manager_PlayerProfile->SetCurrentActiveProfile(ProfileType);
				}
			}
		}
	}
}