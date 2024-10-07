// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_SeamlessTransition.generated.h"

// SeamlessTransitionState
#pragma region

/**
* Describes the State / Step of the Seamless Transition from an
* Origin Map to a Destination Map with a custom Transition Map.
*  Origin Map -> Transition Map -> Destination Map
* This flow is controlled by the Game Instance.
*/
UENUM(BlueprintType)
enum class ECsSeamlessTransitionState : uint8
{
	None										UMETA(DisplayName = "None"),
	/** Game State starts Transitioning Out for Seamless Transition to Transition Map. */
	GameState_TransitionOut						UMETA(DisplayName = "Game State: Transition Out"),
	/** Game State completes Transition Out for Seamless Transition to Transition Map. */
	GameState_TransitionOut_Complete			UMETA(DisplayName = "Game State: Transition Out Complete"),
	/** Start Seamless Transition to Destination Map. 
		The transition will "hold" on the Transition Map. */
	Load_TransitionMap							UMETA(DisplayName = "Load: Transition Map"),
	/** Transition Map has loaded. */
	Load_TransitionMap_Complete					UMETA(DisplayName = "Load: Transition Map Complete"),
	/** Game State start up has completed for Seamless Transition to Transition Map. */
	GameState_Startup_TransitionMap_Complete	UMETA(DisplayName = "Game State: Start up Transition Map Complete"),
	/** Destination Map has async loaded.
		NOTE: Destination Map is NOT necessarily "ready" to be the active World yet.
		NOTE: Transition to Destination Map is still "paused", bTransitionInProgress flag on
			  the SeamlessTravelHandler is set to FALSE. */
	AsyncLoad_DestinationMap_Complete			UMETA(DisplayName = "Async Load: Destination Map Complete"),
	/** Allow the transition to Destination Map.
		bTransitionInProgress flag on the SeamlessTravelHandler is set to TRUE. */
	EnableTransitionInProgress					UMETA(DisplayName = "Enable Transition in Progress"),
	/** Destination Map has loaded. */
	Load_DestinationMap_Complete				UMETA(DisplayName = "Load: Destination Map Complete"),
	/** Game State start up has completed for Seamless Transition to Transition Map. */
	GameState_Startup_DestinationMap_Complete	UMETA(DisplayName = "Game State: Start up Destination Map Complete"),
	ECsSeamlessTransitionState_MAX				UMETA(Hidden)
};

struct CSSEAMLESSTRANSITION_API EMCsSeamlessTransitionState : public TCsEnumMap<ECsSeamlessTransitionState>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSeamlessTransitionState, ECsSeamlessTransitionState)
};

namespace NCsSeamlessTransitionState
{
	typedef ECsSeamlessTransitionState Type;

	namespace Ref
	{
		extern CSSEAMLESSTRANSITION_API const Type None;
		extern CSSEAMLESSTRANSITION_API const Type GameState_TransitionOut;
		extern CSSEAMLESSTRANSITION_API const Type GameState_TransitionOut_Complete;
		extern CSSEAMLESSTRANSITION_API const Type Load_TransitionMap;
		extern CSSEAMLESSTRANSITION_API const Type Load_TransitionMap_Complete;
		extern CSSEAMLESSTRANSITION_API const Type GameState_Startup_TransitionMap_Complete;
		extern CSSEAMLESSTRANSITION_API const Type AsyncLoad_DestinationMap_Complete;
		extern CSSEAMLESSTRANSITION_API const Type EnableTransitionInProgress;
		extern CSSEAMLESSTRANSITION_API const Type Load_DestinationMap_Complete;
		extern CSSEAMLESSTRANSITION_API const Type GameState_Startup_DestinationMap_Complete;
		extern CSSEAMLESSTRANSITION_API const Type ECsSeamlessTransitionState_MAX;
	}
}

namespace NCsSeamlessTransition
{
	/**
	* Describes the State / Step of the Seamless Transition from an
	* Origin Map to a Destination Map with a custom Transition Map.
	*  Origin Map -> Transition Map -> Destination Map
	* This flow is controlled by the Game Instance.
	*/
	enum class EState : uint8
	{
		None,
		/** Game State starts Transitioning Out for Seamless Transition to Transition Map. */
		GameState_TransitionOut,
		/** Game State completes Transition Out for Seamless Transition to Transition Map. */
		GameState_TransitionOut_Complete,
		/** Start Seamless Transition to Destination Map. 
			The transition will "hold" on the Transition Map. */
		Load_TransitionMap,
		/** Transition Map has loaded. */
		Load_TransitionMap_Complete,
		/** Game State start up has completed for Seamless Transition to Transition Map. */
		GameState_Startup_TransitionMap_Complete,
		/** Destination Map has async loaded.
			NOTE: Destination Map is NOT necessarily "ready" to be the active World yet.
			NOTE: Transition to Destination Map is still "paused", bTransitionInProgress flag on
				  the SeamlessTravelHandler is set to FALSE. */
		AsyncLoad_DestinationMap_Complete,
		/** Allow the transition to Destination Map.
			bTransitionInProgress flag on the SeamlessTravelHandler is set to TRUE. */
		EnableTransitionInProgress,
		/** Destination Map has loaded. */
		Load_DestinationMap_Complete,
		/** Game State start up has completed for Seamless Transition to Transition Map. */
		GameState_Startup_DestinationMap_Complete,
		EState_MAX
	};

	struct CSSEAMLESSTRANSITION_API EMState : public TCsEnumMap<EState>
	{
		CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMState, EState)
	};

	namespace NState
	{
		typedef EState Type;

		namespace Ref
		{
			extern CSSEAMLESSTRANSITION_API const Type None;
			extern CSSEAMLESSTRANSITION_API const Type GameState_TransitionOut;
			extern CSSEAMLESSTRANSITION_API const Type GameState_TransitionOut_Complete;
			extern CSSEAMLESSTRANSITION_API const Type Load_TransitionMap;
			extern CSSEAMLESSTRANSITION_API const Type Load_TransitionMap_Complete;
			extern CSSEAMLESSTRANSITION_API const Type GameState_Startup_TransitionMap_Complete;
			extern CSSEAMLESSTRANSITION_API const Type AsyncLoad_DestinationMap_Complete;
			extern CSSEAMLESSTRANSITION_API const Type EnableTransitionInProgress;
			extern CSSEAMLESSTRANSITION_API const Type Load_DestinationMap_Complete;
			extern CSSEAMLESSTRANSITION_API const Type GameState_Startup_DestinationMap_Complete;
			extern CSSEAMLESSTRANSITION_API const Type EState_MAX;
		}
	}
}

using CsSeamlessTransitionStateType = NCsSeamlessTransition::EState;

#pragma endregion SeamlessTransitionState