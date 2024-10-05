// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/CsLibrary_GameInstance_SeamlessTransition.h"

// Library
#include "Game/CsLibrary_GameInstance.h"
#include "Library/CsLibrary_Valid.h"
// Player
#include "Player/CsPlayerTransitionCache.h"
// Game
#include "Game/CsGameInstance_SeamlessTransition.h"

namespace NCsGameInstance
{
	namespace NSeamlessTransition
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Name
				{
					const FName traveled = FName("traveled");
				}
			}
		}

		#define USING_NS_CACHED using namespace NCGameInstance::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCGameInstance::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName
		#define LogLevel void(*Log)(const FString&) /*=&NCsSeamlessTransition::FLog::Warning*/

		// Interface
		#pragma region

		ICsGameInstance_SeamlessTransition* FLibrary::GetInterfaceChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* GameInstance = CsGameInstanceLibrary::GetAsObjectChecked(Context, ContextObject);

			return CS_INTERFACE_CAST_CHECKED(GameInstance, UObject, ICsGameInstance_SeamlessTransition);
		}
		
		ICsGameInstance_SeamlessTransition* FLibrary::GetSafeInterface(const FString& Context, const UObject* ContextObject, LogLevel)
		{
			if (UObject* GameInstance = CsGameInstanceLibrary::GetSafeAsObject(Context, ContextObject, Log))
				return CS_INTERFACE_CAST(GameInstance, UObject, ICsGameInstance_SeamlessTransition);
			return nullptr;
		}

		#pragma endregion Interface

		// Transition
		#pragma region

		bool FLibrary::HasPerformedTransitionChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetInterfaceChecked(Context, ContextObject)->GetHasPerformedTransition();
		}

		void FLibrary::PerformTransitionChecked(const FString& Context, const UObject* ContextObject, const TransitionParamsType& Params)
		{
			GetInterfaceChecked(Context, ContextObject)->PerformTransition(Params);
		}

		bool FLibrary::SafePerformTransition(const FString& Context, const UObject* ContextObject, const TransitionParamsType& Params, LogLevel)
		{
			if (ICsGameInstance_SeamlessTransition* Interface = GetSafeInterface(Context, ContextObject))
			{
				CS_IS_VALID(Params)

				Interface->PerformTransition(Params);
			}
			return false;
		}

		CsPlayerTransitionCacheType* FLibrary::GetPlayerTransitionCacheChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetInterfaceChecked(Context, ContextObject)->GetPlayerTransitionCache();
		}

		CsPlayerTransitionCacheType* FLibrary::GetSafePlayerTransitionCache(const FString& Context, const UObject* ContextObject, LogLevel)
		{
			if (ICsGameInstance_SeamlessTransition* Interface = GetSafeInterface(Context, ContextObject, Log))
				return Interface->GetPlayerTransitionCache();
			return nullptr;
		}

		#pragma endregion Transition

		// Seamless Transition
		#pragma region

		bool FLibrary::IsSeamlessTransitionActiveChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetInterfaceChecked(Context, ContextObject)->IsSeamlessTransitionActive();
		}

		void FLibrary::SeamlessTransition_EnableTransitionInProgressChecked(const FString& Context, const UObject* ContextObject)
		{
			GetInterfaceChecked(Context, ContextObject)->SeamlessTransition_EnableTransitionInProgress();
		}

		const StateType& FLibrary::GetSeamlessTransitionStateChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetInterfaceChecked(Context, ContextObject)->GetSeamlessTransitionState();
		}

		bool FLibrary::SeamlessTransition_IsLoad_TransitionMap_CompleteChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetInterfaceChecked(Context, ContextObject)->GetSeamlessTransitionState() == StateType::Load_TransitionMap_Complete;
		}

		#pragma endregion Seamless Transition

		// Player
		#pragma region
	
		const FName& FLibrary::GetPlayerPawnTraveledTag(const FString& Context, const UObject* ContextObject) 
		{ 
			return GetInterfaceChecked(Context, ContextObject)->GetPlayerPawnTraveledTag();
		}

		void FLibrary::SetPlayerPawnTraveledChecked(const FString& Context, const UObject* ContextObject, const bool& bTraveled)
		{
			GetInterfaceChecked(Context, ContextObject)->SetPlayerPawnTraveled(bTraveled);
		}

		bool FLibrary::HasPlayerPawnTraveledChecked(const FString& Context, const UObject* ContextObject)
		{
			return GetInterfaceChecked(Context, ContextObject)->HasPlayerPawnTraveled();
		}

		bool FLibrary::SafeHasPlayerPawnTraveled(const FString& Context, const UObject* ContextObject, LogLevel)
		{
			if (ICsGameInstance_SeamlessTransition* Interface = GetSafeInterface(Context, ContextObject, Log))
				return Interface->HasPlayerPawnTraveled();
			return false;
		}

		#pragma endregion Player

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef LogLevel
	}
}