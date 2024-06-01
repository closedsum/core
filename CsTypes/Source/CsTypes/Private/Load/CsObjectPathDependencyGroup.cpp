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

		CSTYPES_API CS_ADD_TO_ENUM_MAP(Enum);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Texture);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Font);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(MaterialParameterCollection);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(MaterialFunction);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Material);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(MaterialInstance);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(StaticMesh);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Skeletal);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Sound);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(FX);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(AnimationAsset);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(BlendSpace);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(AnimComposite);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Blueprint);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Sequencer);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(DataTable);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Other);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsObjectPathDependencyGroup_MAX, "MAX");
	}

	CSTYPES_API const uint8 MAX = (uint8)Type::ECsObjectPathDependencyGroup_MAX;
}

#pragma endregion ObjectPathDependencyGroup