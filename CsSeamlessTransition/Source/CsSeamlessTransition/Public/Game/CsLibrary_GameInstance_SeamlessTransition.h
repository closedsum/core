// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Namespace.h"
#include "Game/Types/CsTypes_GameInstance_Transition.h"
#include "CsTypes_SeamlessTransition.h"
// Log
#include "Utility/CsSeamlessTransitionLog.h"

class ICsGameInstance_SeamlessTransition;
class UObject;

// CsPlayerTransitionCacheType (NCsPlayer::NTransition::FCache)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsPlayer, NTransition, FCache)

namespace NCsGameInstance
{
	namespace NSeamlessTransition
	{
		using TransitionParamsType = NCsGameInstance::NTransition::FParams;
		using StateType = NCsSeamlessTransition::EState;

		struct CSSEAMLESSTRANSITION_API FLibrary final
		{
		#define LogLevel void(*Log)(const FString&) = &NCsSeamlessTransition::FLog::Warning

		// Interface
		#pragma region
		public:

			static ICsGameInstance_SeamlessTransition* GetInterfaceChecked(const FString& Context, const UObject* ContextObject);
			
			static ICsGameInstance_SeamlessTransition* GetSafeInterface(const FString& Context, const UObject* ContextObject, LogLevel);

		#pragma endregion Interface

		// Transition
		#pragma region
		public:

			static bool HasPerformedTransitionChecked(const FString& Context, const UObject* ContextObject);

			static void PerformTransitionChecked(const FString& Context, const UObject* ContextObject, const TransitionParamsType& Params);
			static void PerformTransitionChecked(const FString& Context, const UObject* ContextObject, const FCsGameInstance_TransitionParams& Params)
			{
				PerformTransitionChecked(Context, ContextObject, TransitionParamsType::Make(Params));
			}

			static bool SafePerformTransition(const FString& Context, const UObject* ContextObject, const TransitionParamsType& Params, LogLevel);
			FORCEINLINE static bool SafePerformTransition(const FString& Context, const UObject* ContextObject, const FCsGameInstance_TransitionParams& Params, LogLevel)
			{
				return SafePerformTransition(Context, ContextObject, TransitionParamsType::Make(Params), Log);
			}

		#define CsPlayerTransitionCacheType NCsPlayer::NTransition::FCache 

			static CsPlayerTransitionCacheType* GetPlayerTransitionCacheChecked(const FString& Context, const UObject* ContextObject);
			static CsPlayerTransitionCacheType* GetSafePlayerTransitionCache(const FString& Context, const UObject* ContextObject, LogLevel);

		#undef CsPlayerTransitionCacheType

		#pragma endregion Transition

		// Seamless Transition
		#pragma region
		public:

			static bool IsSeamlessTransitionActiveChecked(const FString& Context, const UObject* ContextObject);

			static void SeamlessTransition_EnableTransitionInProgressChecked(const FString& Context, const UObject* ContextObject);

			static const StateType& GetSeamlessTransitionStateChecked(const FString& Context, const UObject* ContextObject);

			static bool SeamlessTransition_IsLoad_TransitionMap_CompleteChecked(const FString& Context, const UObject* ContextObject);

		#pragma endregion Seamless Transition

		// Player
		#pragma region
		public:

			static const FName& GetPlayerPawnTraveledTag(const FString& Context, const UObject* ContextObject);

			static void SetPlayerPawnTraveledChecked(const FString& Context, const UObject* ContextObject, const bool& bTraveled);

			static bool HasPlayerPawnTraveledChecked(const FString& Context, const UObject* ContextObject);

			static bool SafeHasPlayerPawnTraveled(const FString& Context, const UObject* ContextObject, LogLevel);
			FORCEINLINE static bool SafeHasPlayerPawnTraveled(const FString& Context, const UObject* ContextObject, bool& OutSuccess, LogLevel)
			{
				OutSuccess = SafeHasPlayerPawnTraveled(Context, ContextObject);
				return OutSuccess;
			}

		#pragma endregion Player

		#undef LogLevel
		};
	}
}