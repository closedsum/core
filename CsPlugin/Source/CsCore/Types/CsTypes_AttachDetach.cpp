// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_AttachDetach.h"

// AttachmentTransformRules
#pragma region

namespace NCsAttachmentTransformRules
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAttachmentTransformRules, KeepRelativeTransform, "Keep Relative Transform");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAttachmentTransformRules, KeepWorldTransform, "Keep World Transform");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAttachmentTransformRules, SnapToTargetNotIncludingScale, "Snap to Target Not Including Scale");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAttachmentTransformRules, SnapToTargetIncludingScale, "Snap to Target Including Scale");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsAttachmentTransformRules, ECsAttachmentTransformRules_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsAttachmentTransformRules_MAX;
}

#pragma endregion AttachmentTransformRules

// DetachmentTransformRules
#pragma region

namespace NCsDetachmentTransformRules
{
	namespace Ref
	{
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsDetachmentTransformRules, KeepRelativeTransform, "Keep Relative Transform");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsDetachmentTransformRules, KeepWorldTransform, "Keep World Transform");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMCsDetachmentTransformRules, ECsDetachmentTransformRules_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsDetachmentTransformRules_MAX;
}

#pragma endregion DetachmentTransformRules