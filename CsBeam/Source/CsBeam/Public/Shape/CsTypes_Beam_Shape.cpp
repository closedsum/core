// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Shape/CsTypes_Beam_Shape.h"

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