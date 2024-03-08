// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/Enum/CsEnumMap.h"
// Log
#include "Utility/CsBeamLog.h"

#include "CsBeam_CollisionShape.generated.h"

// BeamCollisionShapeScale
#pragma region

/**
* 
*/
UENUM(BlueprintType)
enum class ECsBeamShapeScale : uint8
{
	/** The scale is determined by Beam's shape data (NCsBeam::NData::NShape::IShape). */
	Default					UMETA(DisplayName = "Default"),
	/** The scale is determined by the Owner of the Beam. 
		Owner must implement the interface: ICsGetBeamScale. */
	Owner					UMETA(DisplayName = "Owner"),
	/** The scale is the product of a scalar from the Owner of the Beam
		and the Beam's shape data (NCsBeam::NData::NShape::IShape).
		Owner must implement the interface: ICsGetBeamScale. */
	OwnerAsScalar			UMETA(DisplayName = "Owner as Scalar"),
	/** The scale is determined by the collision's scale. 
		Look at NCsBeam::NCollision::NShape::FShape and NCsBeam::NCollision::NShape::EScale. */
	Collision				UMETA(DisplayName = "Collision"),
	ECsBeamShapeScale_MAX	UMETA(Hidden),
};

struct CSBEAM_API EMCsBeamShapeScale : public TCsEnumMap<ECsBeamShapeScale>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsBeamShapeScale, ECsBeamShapeScale)
};

namespace NCsBeamShapeScale
{
	typedef ECsBeamShapeScale Type;

	namespace Ref
	{
		extern CSBEAM_API const Type Default;
		extern CSBEAM_API const Type Owner;
		extern CSBEAM_API const Type OwnerAsScalar;
		extern CSBEAM_API const Type Collision;
		extern CSBEAM_API const Type ECsBeamShapeScale_MAX;
	}

	extern CSBEAM_API const uint8 MAX;
}

namespace NCsBeam
{
	namespace NShape
	{
		enum class EScale : uint8
		{
			/** The scale is determined by Beam's scale data (NCsBeam::NData::NScale::IScale). */
			Default,
			/** The scale is determined by the Owner of the Beam.
				Owner must implement the interface: ICsGetBeamScale. */
			Owner,
			/** The scale is the product of a scalar from the Owner of the Beam
`				and the Beam's scale data (NCsBeam::NData::NCollision::ICollision).
				Owner must implement the interface: ICsGetBeamScale. */
			OwnerAsScalar,
			/** The scale is determined by the collision's scale.
				Look at NCsBeam::NCollision::NShape::FShape and NCsBeam::NCollision::NShape::EScale. */
			Collision,
			EScale_MAX
		};

		struct CSBEAM_API EMScale : public TCsEnumMap<EScale>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMScale, EScale)
		};

		namespace NScale
		{
			typedef EScale Type;

			namespace Ref
			{
					
				extern CSBEAM_API const Type Default;
				extern CSBEAM_API const Type Owner;				
				extern CSBEAM_API const Type OwnerAsScalar;
				extern CSBEAM_API const Type Collision;
				extern CSBEAM_API const Type EScale_MAX;
			}
		}
	}
}

#pragma endregion BeamCollisionScale