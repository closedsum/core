// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Input/CsTypes_Input.h"
#include "CsCore.h"

// Settings
#include "Settings/CsDeveloperSettings.h"
#include "GameFramework/InputSettings.h"

// InputDevice
#pragma region

namespace NCsInputDevice
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputDevice, MouseAndKeyboard, "Mouse and Keyboard");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputDevice, Gamepad);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputDevice, MotionController, "Motion Controller");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputDevice, ECsInputDevice_MAX, "MAX");
	}
}

#pragma endregion InputDevice

// InputType
#pragma region

namespace NCsInputType
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputType, Action);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputType, Axis);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputType, Trigger);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputType, Location);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputType, Rotation);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputType, ECsInputType_MAX, "MAX");
	}
}

#pragma endregion InputType

// InputEvent
#pragma region

namespace NCsInputEvent
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputEvent, FirstPressed, "First Pressed");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputEvent, Pressed);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputEvent, FirstReleased, "First Released");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputEvent, Released);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputEvent, FirstMoved, "First Moved");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputEvent, Moved);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputEvent, FirstStationary, "First Stationary");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputEvent, Stationary);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputEvent, ECsInputEvent_MAX, "MAX");
	}
}

#pragma endregion InputEvent

// InputValue
#pragma region

namespace NCsInputValue
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputValue, Void);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputValue, Float);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputValue, Vector);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsInputValue, Rotator);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsInputValue, ECsInputValue_MAX, "MAX");
	}
}

#pragma endregion InputValue

// InputActionMap
#pragma region

namespace NCsInputActionMap
{
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		if (UCsDeveloperSettings* Settings = GetMutableDefault<UCsDeveloperSettings>())
		{
#if WITH_EDITOR
			EMCsInputActionMap::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

			const TArray<FCsSettings_Enum>& Enums = Settings->GetSettingsEnum<FECsInputActionMap>();
			const FString EnumSettingsPath		  = Settings->GetSettingsEnumPath<FECsInputActionMap>();

			if (Enums.Num() > CS_EMPTY)
			{
				for (const FCsSettings_Enum& Enum : Enums)
				{
					const FString& Name		   = Enum.Name;
					const FString& DisplayName = Enum.DisplayName;

					if (Name.IsEmpty())
					{
						UE_LOG(LogCs, Warning, TEXT("%s: Empty Enum listed in %s."), *Context, *EnumSettingsPath);
						return;
					}

					checkf(!EMCsInputActionMap::Get().IsValidEnum(Name), TEXT("%s: InputActionMap (Name): %s already exists (declared in native)."), *Context, *Name);

					if (!Enum.DisplayName.IsEmpty())
					{
						checkf(!EMCsInputActionMap::Get().IsValidEnumByDisplayName(DisplayName), TEXT("%s: InputActionMap (DisplayName): %s already exists (declared in native)."), *Context, *DisplayName);

						EMCsInputActionMap::Get().Create(Name, DisplayName, true);
					}
					else
					{
						EMCsInputActionMap::Get().Create(Name, true);
					}
				}
			}
			else
			{
				UE_LOG(LogCs, Warning, TEXT("%s: Enum Setting @ %s is empty."), *Context, *EnumSettingsPath);
			}
		}
	}
}

#pragma endregion InputActionMap

// InputAction
#pragma region

namespace NCsInputAction
{
	void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot)
	{
		if (UInputSettings* Settings = GetMutableDefault<UInputSettings>())
		{
#if WITH_EDITOR
			EMCsInputAction::Get().ClearUserDefinedEnums();
#endif // #if WITH_EDITOR

			// Add ActionMappings
			for (const FInputActionKeyMapping& Mapping : Settings->GetActionMappings())
			{
				const FName& Name = Mapping.ActionName;

				EMCsInputAction::Get().Create(Name.ToString(), true);
			}
			// Add AxisMappings
			for (const FInputAxisKeyMapping& Mapping : Settings->GetAxisMappings())
			{
				const FName& Name = Mapping.AxisName;

				EMCsInputAction::Get().Create(Name.ToString(), true);
			}
		}
	}
}

#pragma endregion InputAction

// ControllerHand
#pragma region

namespace NCsControllerHand
{
	namespace Ref
	{
		CSCORE_API const Type Left = EMCsControllerHand::Get().Add(Type::Left, TEXT("Left"));
		CSCORE_API const Type Right = EMCsControllerHand::Get().Add(Type::Right, TEXT("Right"));
		CSCORE_API const Type ECsControllerHand_MAX = EMCsControllerHand::Get().Add(Type::ECsControllerHand_MAX, TEXT("ECsControllerHand_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsControllerHand_MAX;
}

#pragma endregion ControllerHand