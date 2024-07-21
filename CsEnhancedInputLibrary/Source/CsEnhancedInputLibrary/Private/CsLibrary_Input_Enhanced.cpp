// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsLibrary_Input_Enhanced.h"

// Library
#include "Player/CsLibrary_Player.h"
#include "Library/CsLibrary_Valid.h"
// Input
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
// Player
#include "Engine/LocalPlayer.h"

namespace NCsInput
{
	namespace NEnhanced
	{
		bool FLibrary::IsValidMappingChecked(const FString& Context, const UInputMappingContext* MappingContext)
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

		namespace NFirst
		{
			#define FirstLocalPlayerLibrary NCsPlayer::NLocal::NFirst::FLibrary

			UEnhancedInputLocalPlayerSubsystem* FLibrary::GetSubsystemChecked(const FString& Context, const UObject* WorldContext)
			{
				const ULocalPlayer* LocalPlayer				  = FirstLocalPlayerLibrary::GetChecked(Context, WorldContext);
				UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

				CS_IS_PENDING_KILL_CHECKED(Subsystem)
				return Subsystem;
			}

			#undef FirstLocalPlayerLibrary
		}
	}
}