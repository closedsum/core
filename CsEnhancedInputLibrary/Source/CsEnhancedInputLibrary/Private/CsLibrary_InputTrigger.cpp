// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsLibrary_InputTrigger.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Input
#include "InputTriggers.h"

namespace NCsInput
{
	namespace NEnhanced
	{
		namespace NInputTrigger
		{
			bool FLibrary::IsPressedOrReleasedChecked(const FString& Context, const UInputTrigger* InputTrigger)
			{
				CS_IS_PENDING_KILL_CHECKED(InputTrigger)

				if (Cast<UInputTriggerPressed>(InputTrigger))
					return true;
				if (Cast<UInputTriggerReleased>(InputTrigger))
					return true;
				checkf(0, TEXT("%s: InputTrigger: %s is NOT of type: Pressed or Released."), *Context, *(InputTrigger->GetName()));
				return false;
			}

			bool FLibrary::IsPressedOrReleased(const FString& Context, const UInputTrigger* InputTrigger)
			{
				CS_IS_PENDING_KILL_CHECKED(InputTrigger)

				if (Cast<UInputTriggerPressed>(InputTrigger))
					return true;
				if (Cast<UInputTriggerReleased>(InputTrigger))
					return true;
				return false;
			}

			bool FLibrary::IsPressedOrReleasedOrDown(const FString& Context, const UInputTrigger* InputTrigger)
			{
				CS_IS_PENDING_KILL_CHECKED(InputTrigger)

				if (Cast<UInputTriggerPressed>(InputTrigger))
					return true;
				if (Cast<UInputTriggerReleased>(InputTrigger))
					return true;
				if (Cast<UInputTriggerDown>(InputTrigger))
					return true;
				return false;
			}

			bool FLibrary::IsPressed(const FString& Context, const UInputTrigger* InputTrigger)
			{
				CS_IS_PENDING_KILL_CHECKED(InputTrigger)
				return Cast<UInputTriggerPressed>(InputTrigger) != nullptr;
			}

			bool FLibrary::IsReleased(const FString& Context, const UInputTrigger* InputTrigger)
			{
				CS_IS_PENDING_KILL_CHECKED(InputTrigger)
				return Cast<UInputTriggerReleased>(InputTrigger) != nullptr;
			}

			bool FLibrary::HasPressedOrReleasedChecked(const FString& Context, const TArray<TObjectPtr<UInputTrigger>>& Triggers)
			{
				CS_IS_TARRAY_EMPTY_CHECKED(Triggers, TObjectPtr<UInputTrigger>)
				CS_IS_TARRAY_ANY_PENDING_KILL_CHECKED(Triggers, UInputTrigger)

				for (const TObjectPtr<UInputTrigger>& Trigger : Triggers)
				{
					if (IsPressedOrReleased(Context, Trigger.Get()))
						return true;
				}
				checkf(0, TEXT("%s: Triggers does NOT contain a type of: Pressed or Released."), *Context);
				return false;
			}

			bool FLibrary::HasPressedOrReleased(const FString& Context, const TArray<TObjectPtr<UInputTrigger>>& Triggers)
			{
				CS_IS_TARRAY_EMPTY_CHECKED(Triggers, TObjectPtr<UInputTrigger>)
				CS_IS_TARRAY_ANY_PENDING_KILL_CHECKED(Triggers, UInputTrigger)

				for (const TObjectPtr<UInputTrigger>& Trigger : Triggers)
				{
					if (IsPressedOrReleased(Context, Trigger.Get()))
						return true;
				}
				return false;
			}

			bool FLibrary::HasPressedOrReleasedOrDownChecked(const FString& Context, const TArray<TObjectPtr<UInputTrigger>>& Triggers)
			{
				CS_IS_TARRAY_EMPTY_CHECKED(Triggers, TObjectPtr<UInputTrigger>)
				CS_IS_TARRAY_ANY_PENDING_KILL_CHECKED(Triggers, UInputTrigger)

				for (const TObjectPtr<UInputTrigger>& Trigger : Triggers)
				{
					if (IsPressedOrReleasedOrDown(Context, Trigger.Get()))
						return true;
				}
				checkf(0, TEXT("%s: Triggers does NOT contain a type of: Pressed or Released or Down."), *Context);
				return false;
			}

			bool FLibrary::HasPressedOrReleasedOrDown(const FString& Context, const TArray<TObjectPtr<UInputTrigger>>& Triggers)
			{
				CS_IS_TARRAY_EMPTY_CHECKED(Triggers, TObjectPtr<UInputTrigger>)
				CS_IS_TARRAY_ANY_PENDING_KILL_CHECKED(Triggers, UInputTrigger)

				for (const TObjectPtr<UInputTrigger>& Trigger : Triggers)
				{
					if (IsPressedOrReleasedOrDown(Context, Trigger.Get()))
						return true;
				}
				return false;
			}

			bool FLibrary::HasPressed(const FString& Context, const TArray<TObjectPtr<UInputTrigger>>& Triggers)
			{
				CS_IS_TARRAY_EMPTY_CHECKED(Triggers, TObjectPtr<UInputTrigger>)
				CS_IS_TARRAY_ANY_PENDING_KILL_CHECKED(Triggers, UInputTrigger)

				for (const TObjectPtr<UInputTrigger>& Trigger : Triggers)
				{
					if (IsPressed(Context, Trigger.Get()))
						return true;
				}
				return false;
			}

			bool FLibrary::HasReleased(const FString& Context, const TArray<TObjectPtr<UInputTrigger>>& Triggers)
			{
				CS_IS_TARRAY_EMPTY_CHECKED(Triggers, TObjectPtr<UInputTrigger>)
				CS_IS_TARRAY_ANY_PENDING_KILL_CHECKED(Triggers, UInputTrigger)

				for (const TObjectPtr<UInputTrigger>& Trigger : Triggers)
				{
					if (IsReleased(Context, Trigger.Get()))
						return true;
				}
				return false;
			}
		}
	}
}