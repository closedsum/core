// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Game/Types/CsTypes_GameInstance_Transition.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_GameInstance_Transition)

// FCsGameInstance_TransitionParams
#pragma region 

bool FCsGameInstance_TransitionParams::IsValidChecked(const FString& Context) const
{
	typedef EMCsGameInstanceTransitionState StateMapType;

	CS_IS_ENUM_STRUCT_VALID_CHECKED(StateMapType, From)
	CS_IS_SOFT_OBJECT_PATH_VALID_CHECKED(FromMap)
	CS_IS_ENUM_STRUCT_VALID_CHECKED(StateMapType, To)
	CS_IS_SOFT_OBJECT_PATH_VALID_CHECKED(ToMap)
	return true;
}

bool FCsGameInstance_TransitionParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsSeamlessTransition::FLog::Warning*/) const
{
	typedef EMCsGameInstanceTransitionState StateMapType;
	typedef FECsGameInstanceTransitionState StateType;

	CS_IS_ENUM_STRUCT_VALID(StateMapType, StateType, From)
	CS_IS_SOFT_OBJECT_PATH_VALID(FromMap)
	CS_IS_ENUM_STRUCT_VALID(StateMapType, StateType, To)
	CS_IS_SOFT_OBJECT_PATH_VALID(ToMap)
	return true;
}

namespace NCsGameInstance
{
	namespace NTransition
	{
		bool FParams::IsValidChecked(const FString& Context) const
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(StateMapType, From)
			CS_IS_SOFT_OBJECT_PATH_VALID_CHECKED(FromMap)
			CS_IS_ENUM_STRUCT_VALID_CHECKED(StateMapType, To)
			CS_IS_SOFT_OBJECT_PATH_VALID_CHECKED(ToMap)
			return true;
		}

		bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsSeamlessTransition::FLog::Warning*/) const
		{
			CS_IS_ENUM_STRUCT_VALID(StateMapType, StateType, From)
			CS_IS_SOFT_OBJECT_PATH_VALID(FromMap)
			CS_IS_ENUM_STRUCT_VALID(StateMapType, StateType, To)
			CS_IS_SOFT_OBJECT_PATH_VALID(ToMap)
			return true;
		}
	}
}

#pragma endregion FCsGameInstance_TransitionParams

// GameInstanceTransitionUnpauseCondition
#pragma region

namespace NCsGameInstanceTransitionUnpauseCondition
{
	namespace Ref
	{
		typedef EMCsGameInstanceTransitionUnpauseCondition EnumMapType;

		CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(None);
		CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(Time);
		CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(Custom);
		CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsGameInstanceTransitionUnpauseCondition_MAX, "MAX");
	}
}

namespace NCsGameInstance
{
	namespace NTransition
	{
		namespace NUnpause
		{
			namespace NCondition
			{
				namespace Ref
				{
					typedef EMCondition EnumMapType;

					CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(None);
					CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(Time);
					CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP(Custom);
					CSSEAMLESSTRANSITION_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECondition_MAX, "MAX");
				}
			}
		}
	}
}

#pragma endregion GameInstanceTransitionUnpauseCondition
