// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes.h"

// Level
#pragma region

	// LevelState
CS_DEFINE_ENUM_MAP_BODY(EMCsLevelState)

namespace NCsLevelState
{
	namespace Ref
	{
		CSCORE_API const Type None = EMCsLevelState::Get().Add(Type::None, TEXT("None"));
		CSCORE_API const Type Loaded = EMCsLevelState::Get().Add(Type::Loaded, TEXT("Loaded"));
		CSCORE_API const Type BeginTransition = EMCsLevelState::Get().Add(Type::BeginTransition, TEXT("BeginTransition"), TEXT("Begin Transition"));
		CSCORE_API const Type InTransition = EMCsLevelState::Get().Add(Type::InTransition, TEXT("InTransition"), TEXT("In Transition"));
		CSCORE_API const Type ECsLevelState_MAX = EMCsLevelState::Get().Add(Type::ECsLevelState_MAX, TEXT("ECsLevelState_MAX"), TEXT("MAX"));
	}
}

#pragma endregion Level

// Transform
#pragma region

	// Axes
CS_DEFINE_ENUM_FLAG_MAP_BODY(EMCsAxes)

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
CS_DEFINE_ENUM_MAP_BODY(EMCsAxes_Editor)

namespace NCsAxes_Editor
{
	namespace Ref
	{
		CSCORE_API const Type X = EMCsAxes_Editor::Get().Add(Type::X, TEXT("X"));
		CSCORE_API const Type Y = EMCsAxes_Editor::Get().Add(Type::Y, TEXT("Y"));
		CSCORE_API const Type Z = EMCsAxes_Editor::Get().Add(Type::Z, TEXT("Z"));
		CSCORE_API const Type ECsAxes_Editor_MAX = EMCsAxes_Editor::Get().Add(Type::ECsAxes_Editor_MAX, TEXT("ECsAxes_Editor_MAX"), TEXT("MAX"));
	}
}

	// TransformMember
CS_DEFINE_ENUM_MAP_BODY(EMCsTransformMember)

namespace NCsTransformMember
{
	namespace Ref
	{
		CSCORE_API const Type Location = EMCsTransformMember::Get().Add(Type::Location, TEXT("Location"));
		CSCORE_API const Type Rotation = EMCsTransformMember::Get().Add(Type::Rotation, TEXT("Rotation"));
		CSCORE_API const Type Scale = EMCsTransformMember::Get().Add(Type::Scale, TEXT("Scale"));
		CSCORE_API const Type ECsTransformMember_MAX = EMCsTransformMember::Get().Add(Type::ECsTransformMember_MAX, TEXT("ECsTransformMember_MAX"), TEXT("MAX"));
	}
}

#pragma endregion Transform

// Surface
#pragma region

	// SurfaceType
CS_DEFINE_ENUM_STRUCT_MAP_BODY(EMCsSurfaceType)

#pragma endregion Surface

// Physics
#pragma region

	// PhysicsImpulseType
CS_DEFINE_ENUM_MAP_BODY(EMCsPhysicsImpulseType)

namespace NCsPhysicsImpulseType
{
	namespace Ref
	{
		CSCORE_API const Type AddForce = EMCsPhysicsImpulseType::Get().Add(Type::AddForce, TEXT("AddForce"), TEXT("Add Force"));
		CSCORE_API const Type AddForceAtPosition = EMCsPhysicsImpulseType::Get().Add(Type::AddForceAtPosition, TEXT("AddForceAtPosition"), TEXT("Add Force at Position"));
		CSCORE_API const Type AddTorque = EMCsPhysicsImpulseType::Get().Add(Type::AddTorque, TEXT("AddTorque"), TEXT("Add Torque"));
		CSCORE_API const Type AddAngularImpulse = EMCsPhysicsImpulseType::Get().Add(Type::AddAngularImpulse, TEXT("AddAngularImpulse"), TEXT("Add Angular Impulse"));
		CSCORE_API const Type AddImpulse = EMCsPhysicsImpulseType::Get().Add(Type::AddImpulse, TEXT("AddImpulse"), TEXT("Add Impulse"));
		CSCORE_API const Type AddImpulseAtPosition = EMCsPhysicsImpulseType::Get().Add(Type::AddImpulseAtPosition, TEXT("AddImpulseAtPosition"), TEXT("Add Impulse at Position"));
		CSCORE_API const Type ECsPhysicsImpulseType_MAX = EMCsPhysicsImpulseType::Get().Add(Type::ECsPhysicsImpulseType_MAX, TEXT("ECsPhysicsImpulseType_MAX"), TEXT("MAX"));
	}
}

#pragma endregion Physics

// VR
#pragma region

	// HMDDeviceType
CS_DEFINE_ENUM_MAP_BODY(EMCsHMDDeviceType)

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
}

#pragma endregion VR

// Gestures
#pragma region

	// GestureDevice
CS_DEFINE_ENUM_MAP_BODY(EMCsGestureDevice)

namespace NCsGestureDevice
{
	namespace Ref
	{
		CSCORE_API const Type Mouse = EMCsGestureDevice::Get().Add(Type::Mouse, TEXT("Mouse"));
		CSCORE_API const Type MotionController = EMCsGestureDevice::Get().Add(Type::MotionController, TEXT("Motion Controller"));
		CSCORE_API const Type ECsGestureDevice_MAX = EMCsGestureDevice::Get().Add(Type::ECsGestureDevice_MAX, TEXT("ECsGestureDevice_MAX"), TEXT("MAX"));
	}
}

	// GestureType
CS_DEFINE_ENUM_MAP_BODY(EMCsGestureType)

#pragma endregion Gestures

// Motion Controller
#pragma region

	// ControllerHand
CS_DEFINE_ENUM_MAP_BODY(EMCsControllerHand)

namespace NCsControllerHand
{
	namespace Ref
	{
		CSCORE_API const Type Left = EMCsControllerHand::Get().Add(Type::Left, TEXT("Left"));
		CSCORE_API const Type Right = EMCsControllerHand::Get().Add(Type::Right, TEXT("Right"));
	}
}

#pragma endregion Motion Controller

// Collision
#pragma region

	// CollisionEnabled
CS_DEFINE_ENUM_MAP_BODY(EMCollisionEnabled)

namespace ECollisionEnabled
{
	namespace Ref
	{
		CSCORE_API const Type NoCollision = EMCollisionEnabled::Get().Add(Type::NoCollision, TEXT("NoCollision"));
		CSCORE_API const Type QueryOnly = EMCollisionEnabled::Get().Add(Type::QueryOnly, TEXT("QueryOnly"));
		CSCORE_API const Type PhysicsOnly = EMCollisionEnabled::Get().Add(Type::PhysicsOnly, TEXT("PhysicsOnly"));
		CSCORE_API const Type QueryAndPhysics = EMCollisionEnabled::Get().Add(Type::QueryAndPhysics, TEXT("QueryAndPhysics"));
	}
}

	// CollisionChannel
CS_DEFINE_ENUM_MAP_BODY(EMCsCollisionChannel)

namespace ECsCollisionChannel
{
	namespace Ref
	{
		CSCORE_API const ECollisionChannel ECC_WorldStatic = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_WorldStatic, TEXT("ECC_WorldStatic"), TEXT("World Static"));
		CSCORE_API const ECollisionChannel ECC_WorldDynamic = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_WorldDynamic, TEXT("ECC_WorldDynamic"), TEXT("World Dynamic"));
		CSCORE_API const ECollisionChannel ECC_Pawn = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_Pawn, TEXT("ECC_Pawn"), TEXT("Pawn"));
		CSCORE_API const ECollisionChannel ECC_Visibility = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_Visibility, TEXT("ECC_Visibility"), TEXT("Visibility"));
		CSCORE_API const ECollisionChannel ECC_Camera = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_Camera, TEXT("ECC_Camera"), TEXT("Camera"));
		CSCORE_API const ECollisionChannel ECC_PhysicsBody = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_PhysicsBody, TEXT("ECC_PhysicsBody"), TEXT("Physics Body"));
		CSCORE_API const ECollisionChannel ECC_Vehicle = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_Vehicle, TEXT("ECC_Vehicle"), TEXT("Vehicle"));
		CSCORE_API const ECollisionChannel ECC_Destructible = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_Destructible, TEXT("ECC_Destructible"), TEXT("Destructible"));

		CSCORE_API const ECollisionChannel ECC_EngineTraceChannel1 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_EngineTraceChannel1, TEXT("ECC_EngineTraceChannel1"), TEXT("EngineTraceChannel 1"));
		CSCORE_API const ECollisionChannel ECC_EngineTraceChannel2 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_EngineTraceChannel2, TEXT("ECC_EngineTraceChannel2"), TEXT("EngineTraceChannel 2"));
		CSCORE_API const ECollisionChannel ECC_EngineTraceChannel3 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_EngineTraceChannel3, TEXT("ECC_EngineTraceChannel3"), TEXT("EngineTraceChannel 3"));
		CSCORE_API const ECollisionChannel ECC_EngineTraceChannel4 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_EngineTraceChannel4, TEXT("ECC_EngineTraceChannel4"), TEXT("EngineTraceChannel 4"));
		CSCORE_API const ECollisionChannel ECC_EngineTraceChannel5 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_EngineTraceChannel5, TEXT("ECC_EngineTraceChannel5"), TEXT("EngineTraceChannel 5"));
		CSCORE_API const ECollisionChannel ECC_EngineTraceChannel6 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_EngineTraceChannel6, TEXT("ECC_EngineTraceChannel6"), TEXT("EngineTraceChannel 6"));

		CSCORE_API const ECollisionChannel ECC_GameTraceChannel1 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_GameTraceChannel1, TEXT("ECC_GameTraceChannel1"), TEXT("GameTraceChannel 1"));
		CSCORE_API const ECollisionChannel ECC_GameTraceChannel2 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_GameTraceChannel2, TEXT("ECC_GameTraceChannel2"), TEXT("GameTraceChannel 2"));
		CSCORE_API const ECollisionChannel ECC_GameTraceChannel3 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_GameTraceChannel3, TEXT("ECC_GameTraceChannel3"), TEXT("GameTraceChannel 3"));
		CSCORE_API const ECollisionChannel ECC_GameTraceChannel4 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_GameTraceChannel4, TEXT("ECC_GameTraceChannel4"), TEXT("GameTraceChannel 4"));
		CSCORE_API const ECollisionChannel ECC_GameTraceChannel5 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_GameTraceChannel5, TEXT("ECC_GameTraceChannel5"), TEXT("GameTraceChannel 5"));
		CSCORE_API const ECollisionChannel ECC_GameTraceChannel6 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_GameTraceChannel6, TEXT("ECC_GameTraceChannel6"), TEXT("GameTraceChannel 6"));
		CSCORE_API const ECollisionChannel ECC_GameTraceChannel7 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_GameTraceChannel7, TEXT("ECC_GameTraceChannel7"), TEXT("GameTraceChannel 7"));
		CSCORE_API const ECollisionChannel ECC_GameTraceChannel8 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_GameTraceChannel8, TEXT("ECC_GameTraceChannel8"), TEXT("GameTraceChannel 8"));
		CSCORE_API const ECollisionChannel ECC_GameTraceChannel9 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_GameTraceChannel9, TEXT("ECC_GameTraceChannel9"), TEXT("GameTraceChannel 9"));
		CSCORE_API const ECollisionChannel ECC_GameTraceChannel10 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_GameTraceChannel10, TEXT("ECC_GameTraceChannel10"), TEXT("GameTraceChannel 10"));
		CSCORE_API const ECollisionChannel ECC_GameTraceChannel11 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_GameTraceChannel11, TEXT("ECC_GameTraceChannel11"), TEXT("GameTraceChannel 11"));
		CSCORE_API const ECollisionChannel ECC_GameTraceChannel12 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_GameTraceChannel12, TEXT("ECC_GameTraceChannel12"), TEXT("GameTraceChannel 12"));
		CSCORE_API const ECollisionChannel ECC_GameTraceChannel13 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_GameTraceChannel13, TEXT("ECC_GameTraceChannel13"), TEXT("GameTraceChannel 13"));
		CSCORE_API const ECollisionChannel ECC_GameTraceChannel14 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_GameTraceChannel14, TEXT("ECC_GameTraceChannel14"), TEXT("GameTraceChannel 14"));
		CSCORE_API const ECollisionChannel ECC_GameTraceChannel15 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_GameTraceChannel15, TEXT("ECC_GameTraceChannel15"), TEXT("GameTraceChannel 15"));
		CSCORE_API const ECollisionChannel ECC_GameTraceChannel16 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_GameTraceChannel16, TEXT("ECC_GameTraceChannel16"), TEXT("GameTraceChannel 16"));
		CSCORE_API const ECollisionChannel ECC_GameTraceChannel17 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_GameTraceChannel17, TEXT("ECC_GameTraceChannel17"), TEXT("GameTraceChannel 17"));
		CSCORE_API const ECollisionChannel ECC_GameTraceChannel18 = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_GameTraceChannel18, TEXT("ECC_GameTraceChannel18"), TEXT("GameTraceChannel 18"));

		CSCORE_API const ECollisionChannel ECC_MAX = EMCsCollisionChannel::Get().Add(ECollisionChannel::ECC_MAX, TEXT("ECC_MAX"), TEXT("MAX"));
	}
}

	// CollisionResponse
CS_DEFINE_ENUM_MAP_BODY(EMCollisionResponse)

namespace ECsCollisionResponse
{
	namespace Ref
	{
		extern CSCORE_API const ECollisionResponse ECR_Ignore = EMCollisionResponse::Get().Add(ECollisionResponse::ECR_Ignore, TEXT("ECR_Ignore"), TEXT("Ignore"));
		extern CSCORE_API const ECollisionResponse ECR_Overlap = EMCollisionResponse::Get().Add(ECollisionResponse::ECR_Overlap, TEXT("ECR_Overlap"), TEXT("Overlap"));
		extern CSCORE_API const ECollisionResponse ECR_Block = EMCollisionResponse::Get().Add(ECollisionResponse::ECR_Block, TEXT("ECR_Block"), TEXT("Block"));
		extern CSCORE_API const ECollisionResponse ECR_MAX = EMCollisionResponse::Get().Add(ECollisionResponse::ECR_MAX, TEXT("ECR_MAX"), TEXT("MAX"));
	}
}

#pragma endregion Collision

// Color
#pragma region

	// LinearColor
CS_DEFINE_ENUM_MAP_BODY(EMCsLinearColor)

namespace NCsLinearColor
{
	namespace Ref
	{
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
}

	// Color
CS_DEFINE_ENUM_MAP_BODY(EMCsColor)

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
}

#pragma endregion Color

// AttachmentTransformRules
CS_DEFINE_ENUM_MAP_BODY(EMCsAttachmentTransformRules)

namespace NCsAttachmentTransformRules
{
	namespace Ref
	{
		CSCORE_API const Type KeepRelativeTransform = EMCsAttachmentTransformRules::Get().Add(Type::KeepRelativeTransform, TEXT("KeepRelativeTransform"));
		CSCORE_API const Type KeepWorldTransform = EMCsAttachmentTransformRules::Get().Add(Type::KeepWorldTransform, TEXT("KeepWorldTransform"));
		CSCORE_API const Type SnapToTargetNotIncludingScale = EMCsAttachmentTransformRules::Get().Add(Type::SnapToTargetNotIncludingScale, TEXT("SnapToTargetNotIncludingScale"));
		CSCORE_API const Type SnapToTargetIncludingScale = EMCsAttachmentTransformRules::Get().Add(Type::SnapToTargetIncludingScale, TEXT("SnapToTargetIncludingScale"));
		CSCORE_API const Type ECsAttachmentTransformRules_MAX = EMCsAttachmentTransformRules::Get().Add(Type::ECsAttachmentTransformRules_MAX, TEXT("ECsAttachmentTransformRules_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsAttachmentTransformRules_MAX;
}

// DetachmentTransformRules
CS_DEFINE_ENUM_MAP_BODY(EMCsDetachmentTransformRules)

namespace NCsDetachmentTransformRules
{
	namespace Ref
	{
		CSCORE_API const Type KeepRelativeTransform = EMCsDetachmentTransformRules::Get().Add(Type::KeepRelativeTransform, TEXT("KeepRelativeTransform"));
		CSCORE_API const Type KeepWorldTransform = EMCsDetachmentTransformRules::Get().Add(Type::KeepWorldTransform, TEXT("KeepWorldTransform"));
		CSCORE_API const Type ECsDetachmentTransformRules_MAX = EMCsDetachmentTransformRules::Get().Add(Type::ECsDetachmentTransformRules_MAX, TEXT("ECsDetachmentTransformRules_MAX"), TEXT("MAX"));
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsDetachmentTransformRules_MAX;
}