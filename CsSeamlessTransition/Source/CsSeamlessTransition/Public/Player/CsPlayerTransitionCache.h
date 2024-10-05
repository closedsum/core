// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/Input/GameEvent/CsGameEvent.h"

namespace NCsPlayer
{
	namespace NTransition
	{
		namespace NInput
		{
			struct CSSEAMLESSTRANSITION_API FCache
			{
			public:

				/** For now Assume only ONE Manager Input.
						ManagerInput0 (NCsGameEventCoordinatorGroup::ManagerInput0)
						Broadcast GameEvents during ControllerId 0's ManagerInput->PostProcessInput. */
				TArray<FCsGameEventInfo> Events;

				FCache() :
					Events()
				{
				}

				FORCEINLINE void Reset()
				{
					Events.Reset(Events.Max());
				}

				void Resolve(const FString& Context, const UObject* WorldContext);
			};
		}	
	}
}

using CsPlayerTransitionInputCacheType = NCsPlayer::NTransition::NInput::FCache;

namespace NCsPlayer
{
	namespace NTransition
	{
		struct CSSEAMLESSTRANSITION_API FCache
		{
		private:

			typedef NCsPlayer::NTransition::NInput::FCache InputCacheType;

		public:

			InputCacheType InputCache;

			FCache() :
				InputCache()
			{
			}

			FORCEINLINE void Reset()
			{
				InputCache.Reset();
			}

			FORCEINLINE void Resolve(const FString& Context, const UObject* WorldContext)
			{
				InputCache.Resolve(Context, WorldContext);
			}
		};
	}
}

using CsPlayerTransitionCacheType = NCsPlayer::NTransition::FCache;