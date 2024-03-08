// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes.h"

// Level
#pragma region

	// LevelState
#pragma region

namespace NCsLevelState
{
	namespace Ref
	{
		typedef EMCsLevelState EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP(None);
		CSCORE_API CS_ADD_TO_ENUM_MAP(Loaded);
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(BeginTransition, "Begin Transition");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(InTransition, "In Transition");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsLevelState_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsLevelState_MAX;
}

#pragma endregion NCsLevelState

#pragma endregion Level

// Transform
#pragma region

	// Axes
namespace NCsAxes
{
	namespace Ref
	{
		CSCORE_API const Type X = EMCsAxes::Get().Add(Type::X, TEXT("X"));
		CSCORE_API const Type Y = EMCsAxes::Get().Add(Type::Y, TEXT("Y"));
		CSCORE_API const Type Z = EMCsAxes::Get().Add(Type::Z, TEXT("Z"));
	}
}

	// Axes_Editor
#pragma region

namespace NCsAxes_Editor
{
	namespace Ref
	{
		CSCORE_API const Type X = EMCsAxes_Editor::Get().Add(Type::X, TEXT("X"));
		CSCORE_API const Type Y = EMCsAxes_Editor::Get().Add(Type::Y, TEXT("Y"));
		CSCORE_API const Type Z = EMCsAxes_Editor::Get().Add(Type::Z, TEXT("Z"));
		CSCORE_API const Type ECsAxes_Editor_MAX = EMCsAxes_Editor::Get().Add(Type::ECsAxes_Editor_MAX, TEXT("ECsAxes_Editor_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsAxes_Editor_MAX;
}

#pragma endregion Axes_Editor

	// TransformMember
#pragma region

namespace NCsTransformMember
{
	namespace Ref
	{
		CSCORE_API const Type Location = EMCsTransformMember::Get().Add(Type::Location, TEXT("Location"));
		CSCORE_API const Type Rotation = EMCsTransformMember::Get().Add(Type::Rotation, TEXT("Rotation"));
		CSCORE_API const Type Scale = EMCsTransformMember::Get().Add(Type::Scale, TEXT("Scale"));
		CSCORE_API const Type ECsTransformMember_MAX = EMCsTransformMember::Get().Add(Type::ECsTransformMember_MAX, TEXT("ECsTransformMember_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsTransformMember_MAX;
}

#pragma endregion TransformMember

#pragma endregion Transform

// Surface
#pragma region

	// SurfaceType
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsSurfaceType)

#pragma endregion Surface

// VR
#pragma region

	// HMDDeviceType
#pragma region

namespace NCsHMDDeviceType
{
	namespace Ref
	{
		CSCORE_API const Type DT_OculusRift = EMCsHMDDeviceType::Get().Add(Type::DT_OculusRift, TEXT("DT_OculusRift"), TEXT("Oculus Rift"));
		CSCORE_API const Type DT_Morpheus = EMCsHMDDeviceType::Get().Add(Type::DT_Morpheus, TEXT("DT_Morpheus"), TEXT("PS VR"));
		CSCORE_API const Type DT_ES2GenericStereoMesh = EMCsHMDDeviceType::Get().Add(Type::DT_ES2GenericStereoMesh, TEXT("DT_ES2GenericStereoMesh"), TEXT("ES2 Generic"));
		CSCORE_API const Type DT_SteamVR = EMCsHMDDeviceType::Get().Add(Type::DT_SteamVR, TEXT("DT_SteamVR"), TEXT("Vive"));
		CSCORE_API const Type DT_GearVR = EMCsHMDDeviceType::Get().Add(Type::DT_GearVR, TEXT("DT_GearVR"), TEXT("Gear VR"));
		CSCORE_API const Type DT_GoogleVR = EMCsHMDDeviceType::Get().Add(Type::DT_GoogleVR, TEXT("DT_GoogleVR"), TEXT("Google VR"));
		CSCORE_API const Type ECsHMDDeviceType_MAX = EMCsHMDDeviceType::Get().Add(Type::ECsHMDDeviceType_MAX, TEXT("ECsHMDDeviceType_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsHMDDeviceType_MAX;
}

#pragma endregion HMDDeviceType

#pragma endregion VR

// Color
#pragma region

	// LinearColor
#pragma region

namespace NCsLinearColor
{
	namespace Ref
	{
		typedef EMCsLinearColor EnumMapType;

		CSCORE_API const Type White = EMCsLinearColor::Get().Add(Type::White, TEXT("White"));
		CSCORE_API const Type Gray = EMCsLinearColor::Get().Add(Type::Gray, TEXT("Gray"));
		CSCORE_API const Type Black = EMCsLinearColor::Get().Add(Type::Black, TEXT("Black"));
		CSCORE_API const Type Transparent = EMCsLinearColor::Get().Add(Type::Transparent, TEXT("Transparent"));
		CSCORE_API const Type Red = EMCsLinearColor::Get().Add(Type::Red, TEXT("Red"));
		CSCORE_API const Type Green = EMCsLinearColor::Get().Add(Type::Green, TEXT("Green"));
		CSCORE_API const Type Blue = EMCsLinearColor::Get().Add(Type::Blue, TEXT("Blue"));
		CSCORE_API const Type Yellow = EMCsLinearColor::Get().Add(Type::Yellow, TEXT("Yellow"));
		CSCORE_API const Type ECsLinearColor_MAX = EMCsLinearColor::Get().Add(Type::ECsLinearColor_MAX, TEXT("ECsLinearColor_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsLinearColor_MAX;
}

#pragma endregion LinearColor

	// Color
#pragma region

namespace NCsColor
{
	namespace Ref
	{
		CSCORE_API const Type White = EMCsColor::Get().Add(Type::White, TEXT("White"));
		CSCORE_API const Type Black = EMCsColor::Get().Add(Type::Black, TEXT("Black"));
		CSCORE_API const Type Transparent = EMCsColor::Get().Add(Type::Transparent, TEXT("Transparent"));
		CSCORE_API const Type Red = EMCsColor::Get().Add(Type::Red, TEXT("Red"));
		CSCORE_API const Type Green = EMCsColor::Get().Add(Type::Green, TEXT("Green"));
		CSCORE_API const Type Blue = EMCsColor::Get().Add(Type::Blue, TEXT("Blue"));
		CSCORE_API const Type Yellow = EMCsColor::Get().Add(Type::Yellow, TEXT("Yellow"));
		CSCORE_API const Type Cyan = EMCsColor::Get().Add(Type::Cyan, TEXT("Cyan"));
		CSCORE_API const Type Magenta = EMCsColor::Get().Add(Type::Magenta, TEXT("Magenta"));
		CSCORE_API const Type Orange = EMCsColor::Get().Add(Type::Orange, TEXT("Orange"));
		CSCORE_API const Type Purple = EMCsColor::Get().Add(Type::Purple, TEXT("Purple"));
		CSCORE_API const Type Turquoise = EMCsColor::Get().Add(Type::Turquoise, TEXT("Turquoise"));
		CSCORE_API const Type Silver = EMCsColor::Get().Add(Type::Silver, TEXT("Silver"));
		CSCORE_API const Type Emerald = EMCsColor::Get().Add(Type::Emerald, TEXT("Emerald"));
		CSCORE_API const Type ECsColor_MAX = EMCsColor::Get().Add(Type::ECsColor_MAX, TEXT("ECsColor_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsColor_MAX;
}

#pragma endregion Color

#pragma endregion Color