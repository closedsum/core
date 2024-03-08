// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_ActorComponent.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Name.h"
#include "Library/CsLibrary_Valid.h"
// Component
#include "Components/ActorComponent.h"

namespace NCsActorComponent
{
	#define NameLibrary NCsName::FLibrary

	void FLibrary::GetChecked(const FString& Context, const TSet<UActorComponent*>& Components, const TArray<FName>& Tags, TArray<UActorComponent*>& OutComponents)
	{
		// CS_IS_TSET_EMPTY_CHECKED(Components, )
		checkf(Components.Num() > CS_EMPTY, TEXT("%s: Components is EMPTY."), *Context);
		// CS_IS_TSET_ANY_NULL_CHECKED

		for (UActorComponent* Component : Components)
		{
			checkf(IsValid(Component), TEXT("%s: An element in Components is NULL or Pending Kill."), *Context);
		}

		CS_IS_TARRAY_EMPTY_CHECKED(Tags, FName)
		CS_IS_TARRAY_ANY_NONE_CHECKED(Tags)

		OutComponents.Reset(OutComponents.Max());

		for (UActorComponent* Component : Components)
		{
			if (NameLibrary::Contains(Component->ComponentTags, Tags))
				OutComponents.Add(Component);
		}
	}

	bool FLibrary::GetSafe(const FString& Context, const TSet<UActorComponent*>& Components, const TArray<FName>& Tags, TArray<UActorComponent*>& OutComponents, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		if (Components.Num() == CS_EMPTY)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Components is EMPTY."), *Context));
			return false;
		}

		for (UActorComponent* Component : Components)
		{
			if (!IsValid(Component))
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: An element in Components is NULL or Pending Kill."), *Context));
				return false;
			}
		}
		CS_IS_TARRAY_EMPTY(Tags, FName)
		CS_IS_TARRAY_ANY_NONE(Tags)

		OutComponents.Reset(OutComponents.Max());

		for (UActorComponent* Component : Components)
		{
			if (NameLibrary::Contains(Component->ComponentTags, Tags))
				OutComponents.Add(Component);
		}
		return OutComponents.Num() > CS_EMPTY;
	}

	#undef NameLibrary
}