// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/CsTypes_UI.h"

// SimpleWidgetType
#pragma region

namespace NCsSimpleWidgetType
{
	namespace Ref
	{
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP(EMCsSimpleWidgetType, Text);
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP(EMCsSimpleWidgetType, Float);
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP(EMCsSimpleWidgetType, Button);
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP(EMCsSimpleWidgetType, Bar);
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSimpleWidgetType, ECsSimpleWidgetType_MAX, "MAX");
	}
}

#pragma endregion SimpleWidgetType

// HorizTextAligment
#pragma region

namespace ECsHorizTextAligment
{
	namespace Ref
	{
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMHorizTextAligment, EHTA_Left, "Left");
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMHorizTextAligment, EHTA_Center, "Center");
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMHorizTextAligment, EHTA_Right, "Right");
	}
}

#pragma endregion HorizTextAligment

// VerticalTextAligment
#pragma region

namespace ECsVerticalTextAligment
{
	namespace Ref
	{
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMVerticalTextAligment, EVRTA_TextTop, "Text Top");
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMVerticalTextAligment, EVRTA_TextCenter, "Text Center");
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMVerticalTextAligment, EVRTA_TextBottom, "Text Bottom");
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMVerticalTextAligment, EVRTA_QuadTop, "Quad Top");
	}
}

#pragma endregion VerticalTextAligment

// ButtonState
#pragma region

namespace NCsButtonState
{
	namespace Ref
	{
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP(EMCsButtonState, None);
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsButtonState, FirstHover, "First Hover");
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP(EMCsButtonState, Hover);
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsButtonState, FirstUnHover, "First UnHover");
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsButtonState, FirstPressed, "First Pressed");
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP(EMCsButtonState, Pressed);
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsButtonState, FirstReleased, "First Released");
		CSCOREDEPRECATED_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsButtonState, ECsButtonState_MAX, "MAX");
	}
}

#pragma endregion ButtonState