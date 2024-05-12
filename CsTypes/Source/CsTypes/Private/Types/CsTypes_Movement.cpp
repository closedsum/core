// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_Movement.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Movement)

// Mover
#pragma region

namespace NCsMover
{
	namespace Ref
	{
		typedef EMCsMover EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP(Actor);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Component);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsMover_MAX, "MAX");
	}
}

namespace NCsMovement
{
	namespace NMover
	{
		namespace Ref
		{
			typedef EMMover EnumMapType;

			CSTYPES_API CS_ADD_TO_ENUM_MAP(Actor);
			CSTYPES_API CS_ADD_TO_ENUM_MAP(Component);
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMover_MAX, "MAX");
		}
	}
}

#pragma endregion Mover

// MoveDestination
#pragma region

namespace NCsMoveDestination
{
	namespace Ref
	{
		typedef EMCsMoveDestination EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP(Location);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Actor);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Component);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Bone);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsMoveDestination_MAX, "MAX");
	}
}

namespace NCsMovement
{
	namespace NDestination
	{
		namespace Ref
		{
			typedef EMDestination EnumMapType;

			CSTYPES_API CS_ADD_TO_ENUM_MAP(Location);
			CSTYPES_API CS_ADD_TO_ENUM_MAP(Actor);
			CSTYPES_API CS_ADD_TO_ENUM_MAP(Component);
			CSTYPES_API CS_ADD_TO_ENUM_MAP(Bone);
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDestination_MAX, "MAX");
		}
	}
}

#pragma endregion MoveDestination

// SpeedFormat
#pragma region

namespace NCsSpeedFormat
{
	namespace Ref
	{
		typedef EMCsSpeedFormat EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(UUpS, "Unreal Units per Second");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(MpH, "Miles per Hour");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(KpH, "Kilometers per Hour");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpeedFormat_MAX, "MAX");
	}
}

namespace NCsSpeed
{
	namespace NFormat
	{
		typedef EMFormat EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(UUpS, "Unreal Units per Second");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(MpH, "Miles per Hour");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(KpH, "Kilometers per Hour");
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EFormat_MAX, "MAX");
	}
}

#pragma endregion SpeedFormat

// FCsSpeed
#pragma region

#if WITH_EDITOR

void FCsSpeed::OnPostEditChange(const FName& PropertyName)
{
	// UUpS
	if (PropertyName == FName("UUpS"))
		FromUUpS();
	// MpH
	else
	if (PropertyName == FName("MpH"))
		FromMpH();
	// KpH
	else
	if (PropertyName == FName("KpH"))
		FromKpH();
}

#endif // #if WITH_EDITOR

#pragma endregion FCsSpeed

// FCsAcceleration
#pragma region

#if WITH_EDITOR

void FCsAcceleration::OnPostEditChange(const FName& PropertyName)
{
	// UUpSS
	if (PropertyName == FName("UUpSS"))
		FromUUpSS();
	// MpHS
	else
	if (PropertyName == FName("MpHS"))
		FromMpHS();
	// KpHS
	else
	if (PropertyName == FName("KpHS"))
		FromKpHS();
}

#endif // #if WITH_EDITOR

#pragma endregion FCsAcceleration

// SpeedInterpMethod
#pragma region

namespace NCsSpeedInterpMethod
{
	namespace Ref
	{
		typedef EMCsSpeedInterpMethod EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP(Acceleration);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Easing);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Curve);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpeedInterpMethod_MAX, "MAX");
	}
}

namespace NCsSpeed
{
	namespace NInterp
	{
		namespace NMethod
		{
			typedef EMMethod EnumMapType;

			CSTYPES_API CS_ADD_TO_ENUM_MAP(Acceleration);
			CSTYPES_API CS_ADD_TO_ENUM_MAP(Easing);
			CSTYPES_API CS_ADD_TO_ENUM_MAP(Curve);
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EMethod_MAX, "MAX");
		}
	}
}

#pragma endregion SpeedInterpMethod

// SpeedInterpDirection
#pragma region

namespace NCsSpeedInterpDirection
{
	namespace Ref
	{
		typedef EMCsSpeedInterpDirection EnumMapType;

		CSTYPES_API CS_ADD_TO_ENUM_MAP(Increasing);
		CSTYPES_API CS_ADD_TO_ENUM_MAP(Decreasing);
		CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsSpeedInterpDirection_MAX, "MAX");
	}
}

namespace NCsSpeed
{
	namespace NInterp
	{
		namespace NDirection
		{
			typedef EMDirection EnumMapType;

			CSTYPES_API CS_ADD_TO_ENUM_MAP(Increasing);
			CSTYPES_API CS_ADD_TO_ENUM_MAP(Decreasing);
			CSTYPES_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDirection_MAX, "MAX");
		}
	}
}

#pragma endregion SpeedInterpDirection
