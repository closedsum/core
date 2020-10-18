// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Trace/Data/Params/CsTypes_Params_TraceWeapon_Trace.h"

#include "Trace/Data/Params/CsParams_TraceWeapon_TraceShape.h"

// TraceWeaponTraceLocation
#pragma region

namespace NCsTraceWeaponTraceLocation
{
	namespace Ref
	{
		typedef EMCsTraceWeaponTraceLocation EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
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

		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Camera);
		CSWP_API CS_ADD_TO_ENUM_MAP(Trace);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsTraceWeaponTraceDirection_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsTraceWeaponTraceDirection_MAX;
}

#pragma endregion TraceWeaponTraceDirection

// FCsTraceWeaponLineTraceParams
#pragma region

#define EmuType NCsWeapon::NTrace::NParams::NTrace::FLineEmu
void FCsTraceWeaponLineTraceParams::CopyParams(EmuType* Emu)
{
#undef EmuType

	using namespace NCsWeapon::NTrace::NParams::NTrace;

	Emu->SetLocationType((ELocation*)&Location);
	Emu->SetDirectionType((EDirection*)&Direction);
	Emu->SetDirectionRules(&DirectionRules);
	Emu->SetObjectType(ObjectType);
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

	Emu->SetLocationType((ELocation*)&Location);
	Emu->SetDirectionType((EDirection*)&Direction);
	Emu->SetDirectionRules(&DirectionRules);
	Emu->SetObjectType(ObjectType);
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

	Emu->SetLocationType((ELocation*)&Location);
	Emu->SetDirectionType((EDirection*)&Direction);
	Emu->SetDirectionRules(&DirectionRules);
	Emu->SetObjectType(ObjectType);
	Emu->SetShape(&Shape);
	Emu->SetDistance(&Distance);
}

#pragma endregion FCsTraceWeaponSphereTraceParams