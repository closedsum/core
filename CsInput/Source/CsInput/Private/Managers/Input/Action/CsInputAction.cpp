// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Input/Action/CsInputAction.h"

// Settings
#include "GameFramework/InputSettings.h"
// Input
#include "GameFramework/PlayerInput.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsInputAction)

namespace NCsInputAction
{
	// Mouse
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__MousePositionXY__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__MouseLeftButton__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__MouseRightButton__);
	// Touch
		// Action
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__Touch_0__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__Touch_1__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__Touch_2__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__Touch_3__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__Touch_4__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__Touch_5__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__Touch_6__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__Touch_7__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__Touch_8__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__Touch_9__);
		// Location
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__TouchPositionXY_0__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__TouchPositionXY_1__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__TouchPositionXY_2__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__TouchPositionXY_3__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__TouchPositionXY_4__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__TouchPositionXY_5__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__TouchPositionXY_6__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__TouchPositionXY_7__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__TouchPositionXY_8__);
	CSINPUT_API CS_CREATE_ENUM_STRUCT(Default__TouchPositionXY_9__);

	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		if (UInputSettings* Settings = GetMutableDefault<UInputSettings>())
		{
			EMCsInputAction::Get().ClearUserDefinedEnums();

			// Add ActionMappings
			for (const FInputActionKeyMapping& Mapping : Settings->GetActionMappings())
			{
				const FName& Name = Mapping.ActionName;

				if (!EMCsInputAction::Get().IsValidEnum(Name))
					EMCsInputAction::Get().Create(Name.ToString(), true);
			}
			// Add AxisMappings
			for (const FInputAxisKeyMapping& Mapping : Settings->GetAxisMappings())
			{
				const FName& Name = Mapping.AxisName;

				if (!EMCsInputAction::Get().IsValidEnum(Name))
					EMCsInputAction::Get().Create(Name.ToString(), true);
			}
		}
	}
}