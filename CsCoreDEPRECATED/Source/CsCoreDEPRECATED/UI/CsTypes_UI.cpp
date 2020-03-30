// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/CsTypes_UI.h"

// SimpleWidgetType
#pragma region

namespace NCsSimpleWidgetType
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSimpleWidgetType, Text);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSimpleWidgetType, Float);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSimpleWidgetType, Button);
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsSimpleWidgetType, Bar);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsSimpleWidgetType, ECsSimpleWidgetType_MAX, "MAX");
	}
}

#pragma endregion SimpleWidgetType

// HorizTextAligment
#pragma region

namespace ECsHorizTextAligment
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMHorizTextAligment, EHTA_Left, "Left");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMHorizTextAligment, EHTA_Center, "Center");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMHorizTextAligment, EHTA_Right, "Right");
	}
}

#pragma endregion HorizTextAligment

// VerticalTextAligment
#pragma region

namespace ECsVerticalTextAligment
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMVerticalTextAligment, EVRTA_TextTop, "Text Top");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMVerticalTextAligment, EVRTA_TextCenter, "Text Center");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMVerticalTextAligment, EVRTA_TextBottom, "Text Bottom");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMVerticalTextAligment, EVRTA_QuadTop, "Quad Top");
	}
}

#pragma endregion VerticalTextAligment

// ButtonState
#pragma region

namespace NCsButtonState
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsButtonState, None);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsButtonState, FirstHover, "First Hover");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsButtonState, Hover);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsButtonState, FirstUnHover, "First UnHover");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsButtonState, FirstPressed, "First Pressed");
		CSCORE_API CS_ADD_TO_ENUM_MAP(EMCsButtonState, Pressed);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsButtonState, FirstReleased, "First Released");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsButtonState, ECsButtonState_MAX, "MAX");
	}
}

#pragma endregion ButtonState