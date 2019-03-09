// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_UI.h"

// WidgetActorType
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsWidgetActorType)

// WidgetType
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsWidgetType)

// SimpleWidgetType
CS_DEFINE_ENUM_MAP_BODY(EMCsSimpleWidgetType)

namespace NCsSimpleWidgetType
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

// HorizTextAligment
CS_DEFINE_ENUM_MAP_BODY(EMHorizTextAligment)

namespace ECsHorizTextAligment
{
	namespace Ref
	{
		CSCORE_API const Type EHTA_Left = EMHorizTextAligment::Get().Add(Type::EHTA_Left, TEXT("EHTA_Left"), TEXT("Left"));
		CSCORE_API const Type EHTA_Center = EMHorizTextAligment::Get().Add(Type::EHTA_Center, TEXT("EHTA_Center"), TEXT("Center"));
		CSCORE_API const Type EHTA_Right = EMHorizTextAligment::Get().Add(Type::EHTA_Right, TEXT("EHTA_Right"), TEXT("Right"));
	}
}

// VerticalTextAligment
CS_DEFINE_ENUM_MAP_BODY(EMVerticalTextAligment)

namespace ECsVerticalTextAligment
{
	namespace Ref
	{
		CSCORE_API const Type EVRTA_TextTop = EMVerticalTextAligment::Get().Add(Type::EVRTA_TextTop, TEXT("EVRTA_TextTop"), TEXT("Text Top"));
		CSCORE_API const Type EVRTA_TextCenter = EMVerticalTextAligment::Get().Add(Type::EVRTA_TextCenter, TEXT("EVRTA_TextCenter"), TEXT("Text Center"));
		CSCORE_API const Type EVRTA_TextBottom = EMVerticalTextAligment::Get().Add(Type::EVRTA_TextBottom, TEXT("EVRTA_TextBottom"), TEXT("Text Bottom"));
		CSCORE_API const Type EVRTA_QuadTop = EMVerticalTextAligment::Get().Add(Type::EVRTA_QuadTop, TEXT("EVRTA_QuadTop"), TEXT("Quad Top"));
	}
}

// ButtonState
CS_DEFINE_ENUM_MAP_BODY(EMCsButtonState)

namespace NCsButtonState
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