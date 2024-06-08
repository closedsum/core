// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Engine/DeveloperSettings.h"
// Types
#include "Settings/CsTypes_Settings_Enum.h"
// Input
#include "Managers/Input/CsTypes_InputSystem.h"
#include "Managers/Input/CsTypes_Input.h"
#include "Managers/Input/CsSettings_Input.h"
#include "Managers/Input/Enhanced/CsSettings_Input_Enhanced.h"
#include "Managers/Input/CsSettings_Manager_Input.h"

#include "CsInputSettings.generated.h"

// Cached
#pragma region

namespace NCsInputSettings
{
	namespace NCached
	{
		namespace Str
		{
			extern CSINPUT_API const FString InputActionMap;
			extern CSINPUT_API const FString GameEvent;
		}
	}
}

#pragma endregion Cached

UCLASS(config = Game, defaultconfig, meta = (DisplayName = "CsInput Settings"))
class CSINPUT_API UCsInputSettings : public UDeveloperSettings
{
	GENERATED_UCLASS_BODY()

// UOjbect Interface
#pragma region
public:

#if WITH_EDITOR

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;

	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& e) override;

#endif // #if WITH_EDITOR

#pragma endregion UOjbect Interface

// Enum
#pragma region
public:

	template<typename EnumType>
	const TArray<FCsSettings_Enum>& GetSettingsEnum() const;

	template<typename EnumType>
	const FString& GetSettingsEnumPath() const;

#pragma endregion Enum

// Input
#pragma region
public:

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input")
	ECsInputSystem InputSystem;

	// InputActionMap

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (DisplayName = "ECsInputActionMap", EditCondition = "InputSystem==ECsInputSystem::Default", MultiLine = true))
	FString ECsInputActionMap;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (DisplayName = "ECsInputActionMap: Internal", EditCondition = "InputSystem==ECsInputSystem::Default", TitleProperty = "Name"))
	TArray<FCsSettings_Enum> ECsInputActionMap_Internal;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsInputActionMap>() const { return ECsInputActionMap_Internal; }
	template<>
	const FString& GetSettingsEnumPath<FECsInputActionMap>() const { return NCsInputSettings::NCached::Str::InputActionMap; }

	// Game Event

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (DisplayName = "ECsGameEvent", EditCondition = "InputSystem==ECsInputSystem::Default", MultiLine = true))
	FString ECsGameEvent;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (DisplayName = "ECsGameEvent: Internal", EditCondition = "InputSystem==ECsInputSystem::Default", TitleProperty = "Name"))
	TArray<FCsSettings_Enum> ECsGameEvent_Internal;

	template<>
	const TArray<FCsSettings_Enum>& GetSettingsEnum<FECsGameEvent>() const { return ECsGameEvent_Internal; }
	template<>
	const FString& GetSettingsEnumPath<FECsGameEvent>() const { return NCsInputSettings::NCached::Str::GameEvent; }

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (EditCondition = "InputSystem==ECsInputSystem::Default", EditConditionHides))
	FCsSettings_Input Input;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (EditCondition = "InputSystem==ECsInputSystem::Enhanced", EditConditionHides))
	FCsSettings_Input_Enhanced EnhancedInput;

	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Settings|Input", meta = (DisplayName = "Manager Input"))
	FCsSettings_Manager_Input Manager_Input;

#pragma endregion Input
};