// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_ActorComponent.h"

// Library
#include "Library/CsLibrary_Name.h"
#include "Library/CsLibrary_Valid.h"
// Component
#include "Components/ActorComponent.h"

using LogClassType = NCsCore::NLibrary::FLog;

namespace NCsActorComponent
{
	CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

	void FLibrary::GetChecked(const FString& Context, const TSet<UActorComponent*>& Components, const TArray<FName>& Tags, TArray<UActorComponent*>& OutComponents)
	{
		CS_IS_TSET_EMPTY_CHECKED(Components, UActorComponent*)
		CS_IS_TSET_ANY_PENDING_KILL_CHECKED(Components, UActorComponent)
		CS_IS_TARRAY_EMPTY_CHECKED(Tags, FName)
		CS_IS_TARRAY_ANY_NONE_CHECKED(Tags)

		OutComponents.Reset(OutComponents.Max());

		for (UActorComponent* Component : Components)
		{
			if (CsNameLibrary::Contains(Component->ComponentTags, Tags))
				OutComponents.Add(Component);
		}
	}

	bool FLibrary::GetSafe(const FString& Context, const TSet<UActorComponent*>& Components, const TArray<FName>& Tags, TArray<UActorComponent*>& OutComponents, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		CS_IS_TSET_EMPTY(Components, UActorComponent*)
		CS_IS_TSET_ANY_PENDING_KILL(Components, UActorComponent)
		CS_IS_TARRAY_EMPTY(Tags, FName)
		CS_IS_TARRAY_ANY_NONE(Tags)

		OutComponents.Reset(OutComponents.Max());

		for (UActorComponent* Component : Components)
		{
			if (CsNameLibrary::Contains(Component->ComponentTags, Tags))
				OutComponents.Add(Component);
		}
		return !OutComponents.IsEmpty();
	}
}