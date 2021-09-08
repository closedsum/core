// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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

#define ImplType NCsWeapon::NTrace::NParams::NTrace::FLineImpl
void FCsTraceWeaponLineTraceParams::CopyParams(ImplType* Impl)
{
#undef ImplType

	using namespace NCsWeapon::NTrace::NParams::NTrace;

	Impl->LocationInfo.SetType((ELocation*)&LocationInfo.Type);
	Impl->LocationInfo.SetBoneOrSocket(&LocationInfo.BoneOrSocket);
	Impl->DirectionInfo.SetType((EDirection*)&DirectionInfo.Type);
	Impl->DirectionInfo.SetBoneOrSocket(&DirectionInfo.BoneOrSocket);
	Impl->DirectionInfo.SetRules(&DirectionInfo.Rules);
	Impl->SetObjectTypes(ObjectTypes);
	Impl->SetDistance(&Distance);
}

#pragma endregion FCsTraceWeaponLineTraceParams

// FCsTraceWeaponBoxTraceParams
#pragma region

#define ImplType NCsWeapon::NTrace::NParams::NTrace::FBoxImpl
void FCsTraceWeaponBoxTraceParams::CopyParams(ImplType* Impl)
{
#undef ImplType

	using namespace NCsWeapon::NTrace::NParams::NTrace;

	Impl->LocationInfo.SetType((ELocation*)&LocationInfo.Type);
	Impl->LocationInfo.SetBoneOrSocket(&LocationInfo.BoneOrSocket);
	Impl->DirectionInfo.SetType((EDirection*)&DirectionInfo.Type);
	Impl->DirectionInfo.SetBoneOrSocket(&DirectionInfo.BoneOrSocket);
	Impl->DirectionInfo.SetRules(&DirectionInfo.Rules);
	Impl->SetObjectTypes(ObjectTypes);
	Impl->SetShape(&Shape);
	Impl->SetDistance(&Distance);
}

#pragma endregion FCsTraceWeaponBoxTraceParams

// FCsTraceWeaponSphereTraceParams
#pragma region

#define ImplType NCsWeapon::NTrace::NParams::NTrace::FSphereImpl
void FCsTraceWeaponSphereTraceParams::CopyParams(ImplType* Impl)
{
#undef ImplType

	using namespace NCsWeapon::NTrace::NParams::NTrace;

	Impl->LocationInfo.SetType((ELocation*)&LocationInfo.Type);
	Impl->LocationInfo.SetBoneOrSocket(&LocationInfo.BoneOrSocket);
	Impl->DirectionInfo.SetType((EDirection*)&DirectionInfo.Type);
	Impl->DirectionInfo.SetBoneOrSocket(&DirectionInfo.BoneOrSocket);
	Impl->DirectionInfo.SetRules(&DirectionInfo.Rules);
	Impl->SetObjectTypes(ObjectTypes);
	Impl->SetShape(&Shape);
	Impl->SetDistance(&Distance);
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
		FLineImpl* Impl = new FLineImpl();

		Impl->LocationInfo.SetType((ELocation*)&LocationInfo.Type);
		Impl->LocationInfo.SetBoneOrSocket(&LocationInfo.BoneOrSocket);
		Impl->DirectionInfo.SetType((EDirection*)&DirectionInfo.Type);
		Impl->DirectionInfo.SetBoneOrSocket(&DirectionInfo.BoneOrSocket);
		Impl->DirectionInfo.SetRules(&DirectionInfo.Rules);
		Impl->SetObjectTypes(ObjectTypes);
		Impl->SetDistance(&Distance);
		return Impl;
	}
	// Box
	if (Shape == ECsTraceWeaponTraceShape::Box)
	{
		FBoxImpl* Impl = new FBoxImpl();

		Impl->LocationInfo.SetType((ELocation*)&LocationInfo.Type);
		Impl->LocationInfo.SetBoneOrSocket(&LocationInfo.BoneOrSocket);
		Impl->DirectionInfo.SetType((EDirection*)&DirectionInfo.Type);
		Impl->DirectionInfo.SetBoneOrSocket(&DirectionInfo.BoneOrSocket);
		Impl->DirectionInfo.SetRules(&DirectionInfo.Rules);
		Impl->SetObjectTypes(ObjectTypes);
		Impl->SetShape(&BoxShape);
		Impl->SetDistance(&Distance);
		return Impl;
	}
	// Sphere
	if (Shape == ECsTraceWeaponTraceShape::Sphere)
	{
		FSphereImpl* Impl = new FSphereImpl();

		Impl->LocationInfo.SetType((ELocation*)&LocationInfo.Type);
		Impl->LocationInfo.SetBoneOrSocket(&LocationInfo.BoneOrSocket);
		Impl->DirectionInfo.SetType((EDirection*)&DirectionInfo.Type);
		Impl->DirectionInfo.SetBoneOrSocket(&DirectionInfo.BoneOrSocket);
		Impl->DirectionInfo.SetRules(&DirectionInfo.Rules);
		Impl->SetObjectTypes(ObjectTypes);
		Impl->SetShape(&SphereShape);
		Impl->SetDistance(&Distance);
		return Impl;
	}
	// Capsule
	if (Shape == ECsTraceWeaponTraceShape::Capsule)
	{
		FCapsuleImpl* Impl = new FCapsuleImpl();

		Impl->LocationInfo.SetType((ELocation*)&LocationInfo.Type);
		Impl->LocationInfo.SetBoneOrSocket(&LocationInfo.BoneOrSocket);
		Impl->DirectionInfo.SetType((EDirection*)&DirectionInfo.Type);
		Impl->DirectionInfo.SetBoneOrSocket(&DirectionInfo.BoneOrSocket);
		Impl->DirectionInfo.SetRules(&DirectionInfo.Rules);
		Impl->SetObjectTypes(ObjectTypes);
		Impl->SetShape(&CapsuleShape);
		Impl->SetDistance(&Distance);
		return Impl;
	}

	checkf(0, TEXT("%s: Failed to construct Params from Shape: %s."), *Context, EMCsTraceWeaponTraceShape::Get().ToChar(Shape));
	return nullptr;
}
#undef ParamsType

#pragma endregion FCsTraceWeaponTraceParams