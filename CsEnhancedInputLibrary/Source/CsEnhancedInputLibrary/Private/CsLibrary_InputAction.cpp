// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsLibrary_InputAction.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Input
#include "InputAction.h"
#include "InputTriggers.h"

namespace NCsInput
{
	namespace NEnhanced
	{
		namespace NInputAction
		{
			bool FLibrary::IsBool(const FString& Context, const UInputAction* InputAction)
			{
				CS_IS_PENDING_KILL_CHECKED(InputAction)
				return InputAction->ValueType == EInputActionValueType::Boolean;
			}

			bool FLibrary::HasPressedOrReleasedChecked(const FString& Context, const UInputAction* InputAction)
			{
				CS_IS_PENDING_KILL_CHECKED(InputAction)
				CS_IS_TARRAY_EMPTY_CHECKED(InputAction->Triggers, TObjectPtr<UInputTrigger>)
				CS_IS_TARRAY_ANY_PENDING_KILL_CHECKED(InputAction->Triggers, UInputTrigger)

				for (const TObjectPtr<UInputTrigger>& Trigger : InputAction->Triggers)
				{
					if (Cast<UInputTriggerPressed>(Trigger.Get()))
						return true;
					if (Cast<UInputTriggerReleased>(Trigger.Get()))
						return true;
				}
				checkf(0, TEXT("%s: InputAction: %s does NOT have the Trigger: Pressed or Released."), *Context, *(InputAction->GetName()));
				return false;
			}
		}
	}
}