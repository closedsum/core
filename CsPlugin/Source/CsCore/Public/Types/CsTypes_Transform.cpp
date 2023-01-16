// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Transform.h"

// Transform
#pragma region

namespace NCsTransform
{
	namespace Ref
	{
		typedef EMCsTransform EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Translation);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Rotation);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Scale);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTransform_MAX, "MAX");
	}
}

#pragma endregion Transform

// TransformSpace
#pragma region

namespace NCsTransformSpace
{
	namespace Ref
	{
		typedef EMCsTransformSpace EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Relative);
		CSCORE_API CS_ADD_TO_ENUM_MAP(World);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTransformSpace_MAX, "MAX");
	}
}

#pragma endregion TransformSpace