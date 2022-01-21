// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Play/Mode/CsPlayMode.h"

namespace NCsPlayMode
{
	namespace Ref
	{
		typedef EMCsPlayMode EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(InViewPort, "In ViewPort");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(InEditorFloating, "In Editor ViewPort");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(InMobilePreview, "In Mobile Preview");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(InTargetedMobilePreview, "In Targeted Mobile Preview");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(InVulkanPreview, "In Vulkan Preview");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(InNewProcess, "In New Process");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(InVR, "In VR");
		CSCORE_API CS_ADD_TO_ENUM_MAP(Simulate);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Count);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(InMobilePreviewEditorViewport, "In Mobile Preview Editor Viewport");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(InMobilePreviewEditorFloating, "In Mobile Preview Editor Floating");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsPlayMode_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsPlayMode_MAX;
}