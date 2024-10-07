// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_SeamlessTransition.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_SeamlessTransition)

// SeamlessTransitionState
#pragma region

namespace NCsSeamlessTransitionState
{
	namespace Ref
	{
		typedef EMCsSeamlessTransitionState EnumMapType;

		CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(None);
		CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(GameState_TransitionOut);
		CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(GameState_TransitionOut_Complete);
		CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(Load_TransitionMap);
		CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(Load_TransitionMap_Complete);
		CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(GameState_Startup_TransitionMap_Complete);
		CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(AsyncLoad_DestinationMap_Complete);
		CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(EnableTransitionInProgress);
		CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(Load_DestinationMap_Complete);
		CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(GameState_Startup_DestinationMap_Complete);
		CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSeamlessTransitionState_MAX, "MAX");
	}
}

namespace NCsSeamlessTransition
{
	namespace NState
	{
		namespace Ref
		{
			typedef EMState EnumMapType;

			CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(None);
			CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(GameState_TransitionOut);
			CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(GameState_TransitionOut_Complete);
			CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(Load_TransitionMap);
			CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(Load_TransitionMap_Complete);
			CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(GameState_Startup_TransitionMap_Complete);
			CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(AsyncLoad_DestinationMap_Complete);
			CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(EnableTransitionInProgress);
			CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(Load_DestinationMap_Complete);
			CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(GameState_Startup_DestinationMap_Complete);
			CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP_CUSTOM(EState_MAX, "MAX");
		}
	}
}

#pragma endregion SeamlessTransitionState