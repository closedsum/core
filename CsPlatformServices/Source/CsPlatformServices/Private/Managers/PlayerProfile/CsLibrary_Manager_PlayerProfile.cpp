// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/PlayerProfile/CsLibrary_Manager_PlayerProfile.h"
#include "CsPlatformServices.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/PlayerProfile/CsManager_PlayerProfile.h"

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

			#define USING_NS_CACHED using namespace NCsPlayer::NProfile::NManager::NLibrary::NCached;
			#define SET_CONTEXT(__FunctionName) using namespace NCsPlayer::NProfile::NManager::NLibrary::NCached; \
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

			UCsManager_PlayerProfile* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
			{
			#if UE_BUILD_SHIPPING
				return UCsManager_PlayerProfile::Get(nullptr);
			#else
				UObject* ContextRoot							= GetContextRootChecked(Context, ContextObject);
				UCsManager_PlayerProfile* Manager_PlayerProfile = UCsManager_PlayerProfile::Get(ContextRoot);

				CS_IS_PTR_NULL_CHECKED(Manager_PlayerProfile)
				return Manager_PlayerProfile;
			#endif // #if UE_BUILD_SHIPPING
			}

			UCsManager_PlayerProfile* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*= &NCsPlatformServices::FLog::Warning*/)
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

			void FLibrary::SetCurrentActiveProfileChecked(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& ProfileType)
			{
				GetChecked(Context, ContextObject)->SetCurrentActiveProfile(ProfileType);
			}

			bool FLibrary::SetSafeCurrentActiveProfile(const FString& Context, const UObject* ContextObject, const ECsPlayerProfile& ProfileType, void(*Log)(const FString&) /*=&NCsPlatformServices::FLog::Warning*/)
			{
				if (UCsManager_PlayerProfile* Manager_PlayerProfile = GetSafe(Context, ContextObject))
				{
					CS_IS_ENUM_VALID(EMCsPlayerProfile, ECsPlayerProfile, ProfileType);

					Manager_PlayerProfile->SetCurrentActiveProfile(ProfileType);
					return true;
				}
				return false;
			}

			#undef USING_NS_CACHED
			#undef SET_CONTEXT
		}
	}
}