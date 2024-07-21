// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsLibrary_InputMappingContext.h"

// Library
#include "CsLibrary_InputTrigger.h"
#include "Library/CsLibrary_Valid.h"
// Input
#include "InputMappingContext.h"
#include "InputAction.h"

namespace NCsInput
{
	namespace NEnhanced
	{
		namespace NInputMappingContext
		{
			#define InputTriggerLibrary NCsInput::NEnhanced::NInputTrigger::FLibrary

			bool FLibrary::IsValidChecked(const FString& Context, const UInputMappingContext* MappingContext)
			{
				CS_IS_PENDING_KILL_CHECKED(MappingContext)

				const TArray<FEnhancedActionKeyMapping>& Mappings = MappingContext->GetMappings();

				CS_IS_TARRAY_EMPTY_CHECKED(Mappings, FEnhancedActionKeyMapping)

				for (const FEnhancedActionKeyMapping& Mapping : Mappings)
				{
					CS_IS_OBJECT_PTR_NULL_CHECKED(Mapping.Action, UInputAction)
				}
				return true;
			}

			bool FLibrary::HasPressedOrReleasedChecked(const FString& Context, const UInputMappingContext* MappingContext, const UInputAction* InputAction)
			{
				CS_IS_PENDING_KILL_CHECKED(MappingContext)

				const TArray<FEnhancedActionKeyMapping>& Mappings = MappingContext->GetMappings();

				CS_IS_TARRAY_EMPTY_CHECKED(Mappings, FEnhancedActionKeyMapping)

				bool ActionFound = false;

				for (const FEnhancedActionKeyMapping& Mapping : Mappings)
				{
					if (Mapping.Action == InputAction)
					{
						ActionFound = true;
						
						if (InputTriggerLibrary::HasPressedOrReleased(Context, Mapping.Triggers))
							return true;
					}
				}
				checkf(ActionFound, TEXT("%s: Failed to find InputAction: %s in MappingContext: %s."), *Context, *(InputAction->GetName()), *(MappingContext->GetName()));
				checkf(0, TEXT("%s: InputAction: %s does NOT InputTrigger Pressed or Released."), *Context, *(InputAction->GetName()));
				return false;
			}

			bool FLibrary::HasPressedOrReleasedOrDownChecked(const FString& Context, const UInputMappingContext* MappingContext, const UInputAction* InputAction)
			{
				CS_IS_PENDING_KILL_CHECKED(MappingContext)

				const TArray<FEnhancedActionKeyMapping>& Mappings = MappingContext->GetMappings();

				CS_IS_TARRAY_EMPTY_CHECKED(Mappings, FEnhancedActionKeyMapping)

				bool ActionFound = false;

				for (const FEnhancedActionKeyMapping& Mapping : Mappings)
				{
					if (Mapping.Action == InputAction)
					{
						ActionFound = true;
						
						if (InputTriggerLibrary::HasPressedOrReleasedOrDown(Context, Mapping.Triggers))
							return true;
					}
				}
				checkf(ActionFound, TEXT("%s: Failed to find InputAction: %s in MappingContext: %s."), *Context, *(InputAction->GetName()), *(MappingContext->GetName()));
				checkf(0, TEXT("%s: InputAction: %s does NOT InputTrigger Pressed or Released Or Down."), *Context, *(InputAction->GetName()));
				return false;
			}

			bool FLibrary::HasPressed(const FString& Context, const UInputMappingContext* MappingContext, const UInputAction* InputAction)
			{
				CS_IS_PENDING_KILL_CHECKED(MappingContext)

				const TArray<FEnhancedActionKeyMapping>& Mappings = MappingContext->GetMappings();

				CS_IS_TARRAY_EMPTY_CHECKED(Mappings, FEnhancedActionKeyMapping)

				bool ActionFound = false;

				for (const FEnhancedActionKeyMapping& Mapping : Mappings)
				{
					if (Mapping.Action == InputAction)
					{
						ActionFound = true;
						
						if (InputTriggerLibrary::HasPressed(Context, Mapping.Triggers))
							return true;
					}
				}
				checkf(ActionFound, TEXT("%s: Failed to find InputAction: %s in MappingContext: %s."), *Context, *(InputAction->GetName()), *(MappingContext->GetName()));
				return false;
			}

			bool FLibrary::HasReleased(const FString& Context, const UInputMappingContext* MappingContext, const UInputAction* InputAction)
			{
				CS_IS_PENDING_KILL_CHECKED(MappingContext)

				const TArray<FEnhancedActionKeyMapping>& Mappings = MappingContext->GetMappings();

				CS_IS_TARRAY_EMPTY_CHECKED(Mappings, FEnhancedActionKeyMapping)

				bool ActionFound = false;

				for (const FEnhancedActionKeyMapping& Mapping : Mappings)
				{
					if (Mapping.Action == InputAction)
					{
						ActionFound = true;
						
						if (InputTriggerLibrary::HasReleased(Context, Mapping.Triggers))
							return true;
					}
				}
				checkf(ActionFound, TEXT("%s: Failed to find InputAction: %s in MappingContext: %s."), *Context, *(InputAction->GetName()), *(MappingContext->GetName()));
				return false;
			}

			#undef InputActinoLibrary
		}
	}
}