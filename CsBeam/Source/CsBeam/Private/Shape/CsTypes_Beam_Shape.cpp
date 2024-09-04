// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Shape/CsTypes_Beam_Shape.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Beam_Shape)

// BeamShapeScale
#pragma region

namespace NCsBeamShapeScale
{
	namespace Ref
	{
		typedef EMCsBeamShapeScale EnumMapType;

		CSBEAM_API CS_ADD_TO_ENUM_MAP(Default);
		CSBEAM_API CS_ADD_TO_ENUM_MAP(Owner);
		CSBEAM_API CS_ADD_TO_ENUM_MAP_CUSTOM(OwnerAsScalar, "Owner as Scalar");
		CSBEAM_API CS_ADD_TO_ENUM_MAP(Collision);
		CSBEAM_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsBeamShapeScale_MAX, "MAX");
	}

	CSBEAM_API const uint8 MAX = (uint8)Type::ECsBeamShapeScale_MAX;
}

namespace NCsBeam
{
	namespace NShape
	{
		namespace NScale
		{
			namespace Ref
			{
				typedef EMScale EnumMapType;

				CSBEAM_API CS_ADD_TO_ENUM_MAP(Default);
				CSBEAM_API CS_ADD_TO_ENUM_MAP(Owner);
				CSBEAM_API CS_ADD_TO_ENUM_MAP_CUSTOM(OwnerAsScalar, "Owner as Scalar");
				CSBEAM_API CS_ADD_TO_ENUM_MAP(Collision);
				CSBEAM_API CS_ADD_TO_ENUM_MAP_CUSTOM(EScale_MAX, "MAX");
			}
		}
	}
}

#pragma endregion BeamShapeScale