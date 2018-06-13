// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_UI.h"

// WidgetActorType
EMCsWidgetActorType* EMCsWidgetActorType::Instance;

EMCsWidgetActorType& EMCsWidgetActorType::Get()
{
	if (!Instance)
		Instance = new EMCsWidgetActorType();
	return *Instance;
}

// WidgetType
EMCsWidgetType* EMCsWidgetType::Instance;

EMCsWidgetType& EMCsWidgetType::Get()
{
	if (!Instance)
		Instance = new EMCsWidgetType();
	return *Instance;
}

// SimpleWidgetType
EMCsSimpleWidgetType* EMCsSimpleWidgetType::Instance;

EMCsSimpleWidgetType& EMCsSimpleWidgetType::Get()
{
	if (!Instance)
		Instance = new EMCsSimpleWidgetType();
	return *Instance;
}

namespace ECsSimpleWidgetType
{
	namespace Ref
	{
		CSCORE_API const Type Text = EMCsSimpleWidgetType::Get().Add(Type::Text, TEXT("Text"));
		CSCORE_API const Type Float = EMCsSimpleWidgetType::Get().Add(Type::Float, TEXT("Float"));
		CSCORE_API const Type Button = EMCsSimpleWidgetType::Get().Add(Type::Button, TEXT("Button"));
		CSCORE_API const Type Bar = EMCsSimpleWidgetType::Get().Add(Type::Bar, TEXT("Bar"));
		CSCORE_API const Type ECsSimpleWidgetType_MAX = EMCsSimpleWidgetType::Get().Add(Type::ECsSimpleWidgetType_MAX, TEXT("ECsSimpleWidgetType_MAX"), TEXT("MAX"));
	}
}

// BuildState
EMCsButtonState* EMCsButtonState::Instance;

EMCsButtonState& EMCsButtonState::Get()
{
	if (!Instance)
		Instance = new EMCsButtonState();
	return *Instance;
}

namespace ECsButtonState
{
	namespace Ref
	{
		CSCORE_API const Type None = EMCsButtonState::Get().Add(Type::None, TEXT("None"));
		CSCORE_API const Type FirstHover = EMCsButtonState::Get().Add(Type::FirstHover, TEXT("FirstHover"), TEXT("First Hover"));
		CSCORE_API const Type Hover = EMCsButtonState::Get().Add(Type::Hover, TEXT("Hover"));
		CSCORE_API const Type FirstUnHover = EMCsButtonState::Get().Add(Type::FirstUnHover, TEXT("FirstUnHover"), TEXT("First UnHover"));
		CSCORE_API const Type FirstPressed = EMCsButtonState::Get().Add(Type::FirstPressed, TEXT("FirstPressed"), TEXT("First Pressed"));
		CSCORE_API const Type Pressed = EMCsButtonState::Get().Add(Type::Pressed, TEXT("Pressed"));
		CSCORE_API const Type FirstReleased = EMCsButtonState::Get().Add(Type::FirstReleased, TEXT("FirstReleased"), TEXT("First Released"));
		CSCORE_API const Type ECsButtonState_MAX = EMCsButtonState::Get().Add(Type::ECsButtonState_MAX, TEXT("ECsButtonState_MAX"), TEXT("MAX"));
	}
}