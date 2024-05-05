// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Achievement/CsTypes_Achievement.h"

#include "CsManager_Achievement_Delegates.generated.h"

USTRUCT()
struct CSPLATFORMSERVICES_API FCsManager_Achievement_Delegates_STUB
{
	GENERATED_USTRUCT_BODY()

	FCsManager_Achievement_Delegates_STUB()
	{
	}
};

// Script Passable
#pragma region
#pragma endregion Script Passable

/**
* QueryIds
*
* @param WasSuccessful
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerAchievement_OnQueryIds, bool, WasSuccessful);
/**
* QueryDescriptions
*
* @param WasSuccessful
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerAchievement_OnQueryDescriptions, bool, WasSuccessful);
/**
* Create
*
* @param WasSuccessful
* @param Achievement
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerAchievement_OnCreate, bool, WasSuccessful, const FECsAchievement&, Achievement);
/**
* Modify
*
* @param WasSuccessful
* @param Achievement
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerAchievement_OnModify, bool, WasSuccessful, const FECsAchievement&, Achievement);
/**
* Remove
*
* @param WasSuccessful
* @param Achievement
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerAchievement_OnRemove, bool, WasSuccessful, const FString&, Achievement);
/**
* RemoveAll
*
* @param WasSuccessful
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerAchievement_OnRemoveAll, bool, WasSuccessful);
/**
* Complete
*
* @param WasSuccessful
* @param Achievement
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCsManagerAchievement_OnComplete, bool, WasSuccessful, const FECsAchievement&, Achievement);
/**
* CompleteAll
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagerAchievement_OnCompleteAll);
/**
* Progress
*
* @param WasSuccessful
* @param Achievement
* @param Progress

*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsManagerAchievement_OnProgress, bool, WasSuccessful, const FECsAchievement&, Achievement, const float&, Progress);
/**
* Reset
*
* @param Achievement
* @param Progress
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCsManagerAchievement_OnReset, bool, WasSuccessful, const FECsAchievement&, Achievement, const float&, Progress);
/**
* ResetAll
*
* @param WasSuccessful
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerAchievement_OnResetAll, bool, WasSuccessful);

namespace NCsAchievement
{
	namespace NManager
	{
		/** Delegate type when finished Querying Achievement Ids. */
		DECLARE_MULTICAST_DELEGATE_OneParam(FOnQueryIds, bool);

		/** Delegate type when finished Querying Achievement Descriptions. */
		DECLARE_MULTICAST_DELEGATE_OneParam(FOnQueryDescriptions, bool);

		/**
		* Delegate type.
		*
		* @param WasSuccessful
		* @param Achievement
		*/
		DECLARE_MULTICAST_DELEGATE_TwoParams(FOnCreate, bool /*WasSuccessful*/, const ICsAchievement* /*Achievement*/);

		/**
		* Delegate type.
		*
		* @param WasSuccessful
		* @param Achievement
		*/
		DECLARE_MULTICAST_DELEGATE_TwoParams(FOnModify, bool /*WasSuccessful*/, const ICsAchievement* /*Achievement*/);

		/**
		* Delegate type.
		*
		* @param WasSuccessful
		* @param Achievement
		*/
		DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRemove, bool /*WasSuccessful*/, const FString& /*Achievement*/);

		/**
		* Delegate type.
		*
		* @param WasSuccessful
		*/
		DECLARE_MULTICAST_DELEGATE_OneParam(FOnRemoveAll, bool /*WasSuccessful*/);

		/** 
		* Delegate type when completing an Achievement
		*
		* @param WasSuccessful
		* @param Achievement
		*/
		DECLARE_MULTICAST_DELEGATE_TwoParams(FOnComplete, bool /*WasSuccessful*/, const ICsAchievement* /*Achievement*/);

		/** Delegate type when completing all achievement */
		DECLARE_MULTICAST_DELEGATE(FOnCompleteAll);

		/**
		* Delegate type when the progress of an Achievement has been reset to a value (default is 0).
		*
		* @param WasSuccessful
		* @param Achievement
		* @param Progress
		*/
		DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnReset, bool /*WasSuccessful*/, const ICsAchievement* /*Achievement*/, const float& /*Progress*/);

		/**
		* Delegate type when resetting all achievement
		*
		* @param WasSuccessful
		*/
		DECLARE_MULTICAST_DELEGATE_OneParam(FOnResetAll, bool /*WasSuccessful*/);

		/** Delegate type when the progress of an Achievement has been updated.
		*
		* @param WasSuccessful
		* @param Achievement
		* @param Progress
		*/
		DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnProgress, bool /*WasSuccessful*/, const ICsAchievement* /*Achievement*/, const float& /*Progress*/);
	}
}