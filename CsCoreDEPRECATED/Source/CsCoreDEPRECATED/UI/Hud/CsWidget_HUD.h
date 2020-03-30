// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/CsUserWidget.h"
#include "CsWidget_HUD.generated.h"

// Enums
#pragma region

namespace ECsWidgetHUDRoutine
{
	enum Type
	{
		ECsWidgetHUDRoutine_MAX = ECsUserWidgetRoutine::ECsUserWidgetRoutine_MAX,
	};
}

namespace ECsWidgetHUDRoutine
{
	typedef TCsProperty_Multi_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
	}

	FORCEINLINE const FString& ToString(const Type &EType)
	{
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		return Type::ECsWidgetHUDRoutine_MAX;
	}
}

#define ECS_WIDGET_HUD_ROUTINE_MAX (uint8)ECsWidgetHUDRoutine::ECsWidgetHUDRoutine_MAX
typedef ECsWidgetHUDRoutine::Type TCsWidgetHUDRoutine;

#pragma endregion Enums

UCLASS()
class CSCORE_API UCsWidget_HUD : public UCsUserWidget
{
	GENERATED_UCLASS_BODY()
};