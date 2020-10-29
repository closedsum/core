// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Trace/Data/Params/CsTypes_Params_TraceWeapon_Trace.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Trace/Data/Params/CsLibrary_Params_TraceWeapon_Trace.h"
// Params
#include "Trace/Data/Params/CsParams_TraceWeapon_TraceShape.h"

// TraceWeaponTraceLocation
#pragma region

namespace NCsTraceWeaponTraceLocation
{
	namespace Ref
	{
		typedef EMCsTraceWeaponTraceLocation EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Self);
		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
		CSWP_API CS_ADD_TO_ENUM_MAP(Socket);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Camera);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTraceWeaponTraceLocation_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsTraceWeaponTraceLocation_MAX;
}

#pragma endregion TraceWeaponTraceLocation

// TraceWeaponTraceDirection
#pragma region

namespace NCsTraceWeaponTraceDirection
{
	namespace Ref
	{
		typedef EMCsTraceWeaponTraceDirection EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Self);
		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
		CSWP_API CS_ADD_TO_ENUM_MAP(Socket);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Camera);
		CSWP_API CS_ADD_TO_ENUM_MAP(Trace);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTraceWeaponTraceDirection_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsTraceWeaponTraceDirection_MAX;
}

#pragma endregion TraceWeaponTraceDirection

// TraceWeaponTraceShape
#pragma region

namespace NCsTraceWeaponTraceShape
{
	namespace Ref
	{
		typedef EMCsTraceWeaponTraceShape EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Line);
		CSWP_API CS_ADD_TO_ENUM_MAP(Box);
		CSWP_API CS_ADD_TO_ENUM_MAP(Sphere);
		CSWP_API CS_ADD_TO_ENUM_MAP(Capsule);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTraceWeaponTraceShape_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsTraceWeaponTraceShape_MAX;
}

#pragma endregion TraceWeaponTraceShape

// FCsTraceWeaponLineTraceParams
#pragma region

#define EmuType NCsWeapon::NTrace::NParams::NTrace::FLineEmu
void FCsTraceWeaponLineTraceParams::CopyParams(EmuType* Emu)
{
#undef EmuType

	using namespace NCsWeapon::NTrace::NParams::NTrace;

	Emu->LocationInfo.SetType((ELocation*)&LocationInfo.Type);
	Emu->LocationInfo.SetBoneOrSocket(&LocationInfo.BoneOrSocket);
	Emu->DirectionInfo.SetType((EDirection*)&DirectionInfo.Type);
	Emu->DirectionInfo.SetBoneOrSocket(&DirectionInfo.BoneOrSocket);
	Emu->DirectionInfo.SetRules(&DirectionInfo.Rules);
	Emu->SetObjectTypes(ObjectTypes);
	Emu->SetDistance(&Distance);
}

#pragma endregion FCsTraceWeaponLineTraceParams

// FCsTraceWeaponBoxTraceParams
#pragma region

#define EmuType NCsWeapon::NTrace::NParams::NTrace::FBoxEmu
void FCsTraceWeaponBoxTraceParams::CopyParams(EmuType* Emu)
{
#undef EmuType

	using namespace NCsWeapon::NTrace::NParams::NTrace;

	Emu->LocationInfo.SetType((ELocation*)&LocationInfo.Type);
	Emu->LocationInfo.SetBoneOrSocket(&LocationInfo.BoneOrSocket);
	Emu->DirectionInfo.SetType((EDirection*)&DirectionInfo.Type);
	Emu->DirectionInfo.SetBoneOrSocket(&DirectionInfo.BoneOrSocket);
	Emu->DirectionInfo.SetRules(&DirectionInfo.Rules);
	Emu->SetObjectTypes(ObjectTypes);
	Emu->SetShape(&Shape);
	Emu->SetDistance(&Distance);
}

#pragma endregion FCsTraceWeaponBoxTraceParams

// FCsTraceWeaponSphereTraceParams
#pragma region

#define EmuType NCsWeapon::NTrace::NParams::NTrace::FSphereEmu
void FCsTraceWeaponSphereTraceParams::CopyParams(EmuType* Emu)
{
#undef EmuType

	using namespace NCsWeapon::NTrace::NParams::NTrace;

	Emu->LocationInfo.SetType((ELocation*)&LocationInfo.Type);
	Emu->LocationInfo.SetBoneOrSocket(&LocationInfo.BoneOrSocket);
	Emu->DirectionInfo.SetType((EDirection*)&DirectionInfo.Type);
	Emu->DirectionInfo.SetBoneOrSocket(&DirectionInfo.BoneOrSocket);
	Emu->DirectionInfo.SetRules(&DirectionInfo.Rules);
	Emu->SetObjectTypes(ObjectTypes);
	Emu->SetShape(&Shape);
	Emu->SetDistance(&Distance);
}

#pragma endregion FCsTraceWeaponSphereTraceParams

// FCsTraceWeaponTraceParams
#pragma region

namespace NCsTraceWeaponTraceParams
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(FCsTraceWeaponTraceParams, ConstructAndCopyParams);
		}
	}
}

#define ParamsType NCsWeapon::NTrace::NParams::NTrace::ITrace
ParamsType* FCsTraceWeaponTraceParams::ConstructAndCopyParams()
{
	using namespace NCsTraceWeaponTraceParams::NCached;

	const FString& Context = Str::ConstructAndCopyParams;

	using namespace NCsWeapon::NTrace::NParams::NTrace;

	// Line
	if (Shape == ECsTraceWeaponTraceShape::Line)
	{
		FLineEmu* Emu = new FLineEmu();

		Emu->LocationInfo.SetType((ELocation*)&LocationInfo.Type);
		Emu->LocationInfo.SetBoneOrSocket(&LocationInfo.BoneOrSocket);
		Emu->DirectionInfo.SetType((EDirection*)&DirectionInfo.Type);
		Emu->DirectionInfo.SetBoneOrSocket(&DirectionInfo.BoneOrSocket);
		Emu->DirectionInfo.SetRules(&DirectionInfo.Rules);
		Emu->SetObjectTypes(ObjectTypes);
		Emu->SetDistance(&Distance);
		return Emu;
	}
	// Box
	if (Shape == ECsTraceWeaponTraceShape::Box)
	{
		FBoxEmu* Emu = new FBoxEmu();

		Emu->LocationInfo.SetType((ELocation*)&LocationInfo.Type);
		Emu->LocationInfo.SetBoneOrSocket(&LocationInfo.BoneOrSocket);
		Emu->DirectionInfo.SetType((EDirection*)&DirectionInfo.Type);
		Emu->DirectionInfo.SetBoneOrSocket(&DirectionInfo.BoneOrSocket);
		Emu->DirectionInfo.SetRules(&DirectionInfo.Rules);
		Emu->SetObjectTypes(ObjectTypes);
		Emu->SetShape(&BoxShape);
		Emu->SetDistance(&Distance);
		return Emu;
	}
	// Sphere
	if (Shape == ECsTraceWeaponTraceShape::Sphere)
	{
		FSphereEmu* Emu = new FSphereEmu();

		Emu->LocationInfo.SetType((ELocation*)&LocationInfo.Type);
		Emu->LocationInfo.SetBoneOrSocket(&LocationInfo.BoneOrSocket);
		Emu->DirectionInfo.SetType((EDirection*)&DirectionInfo.Type);
		Emu->DirectionInfo.SetBoneOrSocket(&DirectionInfo.BoneOrSocket);
		Emu->DirectionInfo.SetRules(&DirectionInfo.Rules);
		Emu->SetObjectTypes(ObjectTypes);
		Emu->SetShape(&SphereShape);
		Emu->SetDistance(&Distance);
		return Emu;
	}
	// Capsule
	if (Shape == ECsTraceWeaponTraceShape::Capsule)
	{
		FCapsuleEmu* Emu = new FCapsuleEmu();

		Emu->LocationInfo.SetType((ELocation*)&LocationInfo.Type);
		Emu->LocationInfo.SetBoneOrSocket(&LocationInfo.BoneOrSocket);
		Emu->DirectionInfo.SetType((EDirection*)&DirectionInfo.Type);
		Emu->DirectionInfo.SetBoneOrSocket(&DirectionInfo.BoneOrSocket);
		Emu->DirectionInfo.SetRules(&DirectionInfo.Rules);
		Emu->SetObjectTypes(ObjectTypes);
		Emu->SetShape(&CapsuleShape);
		Emu->SetDistance(&Distance);
		return Emu;
	}

	checkf(0, TEXT("%s: Failed to construct Params from Shape: %s."), *Context, EMCsTraceWeaponTraceShape::Get().ToChar(Shape));
	return nullptr;
}
#undef ParamsType

#pragma endregion FCsTraceWeaponTraceParams