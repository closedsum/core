// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Load/CsObjectPathDependencyGroup.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsObjectPathDependencyGroup)

// ObjectPathDependencyGroup
#pragma region

namespace NCsObjectPathDependencyGroup
{
	namespace Ref
	{
		typedef EMCsObjectPathDependencyGroup EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(Enum);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Texture);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Font);
		CSCORE_API CS_ADD_TO_ENUM_MAP(MaterialParameterCollection);
		CSCORE_API CS_ADD_TO_ENUM_MAP(MaterialFunction);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Material);
		CSCORE_API CS_ADD_TO_ENUM_MAP(MaterialInstance);
		CSCORE_API CS_ADD_TO_ENUM_MAP(StaticMesh);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Skeletal);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Sound);
		CSCORE_API CS_ADD_TO_ENUM_MAP(FX);
		CSCORE_API CS_ADD_TO_ENUM_MAP(AnimationAsset);
		CSCORE_API CS_ADD_TO_ENUM_MAP(BlendSpace);
		CSCORE_API CS_ADD_TO_ENUM_MAP(AnimComposite);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Blueprint);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Sequencer);
		CSCORE_API CS_ADD_TO_ENUM_MAP(DataTable);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Other);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsObjectPathDependencyGroup_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsObjectPathDependencyGroup_MAX;
}

#pragma endregion ObjectPathDependencyGroup