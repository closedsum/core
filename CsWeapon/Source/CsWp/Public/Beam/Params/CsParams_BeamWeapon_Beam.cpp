// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Beam/Params/CsParams_BeamWeapon_Beam.h"

// Container
#include "Containers/CsInterfaceMap.h"
// Library
#include "Library/CsLibrary_Valid.h"

// BeamWeaponBeamLifeCycle
#pragma region

namespace NCsBeamWeaponBeamLifeCycle
{
	namespace Ref
	{
		typedef EMCsBeamWeaponBeamLifeCycle EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Self);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(AfterShot, "After Shot");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(AfterBeamsPerShot, "After Beams per Shot");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(AfterStopFire, "After Stop Fire");
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsBeamWeaponBeamLifeCycle_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsBeamWeaponBeamLifeCycle_MAX;
}

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NParams
		{
			namespace NBeam
			{
				namespace NLifeCycle
				{
					namespace Ref
					{
						typedef EMLifeCycle EnumMapType;

						CSWP_API CS_ADD_TO_ENUM_MAP(Self);
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(AfterShot, "After Shot");
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(AfterBeamsPerShot, "After Beams per Shot");
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(AfterStopFire, "After Stop Fire");
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ELifeCycle_MAX, "MAX");
					}
				}
			}
		}
	}
}

#pragma endregion BeamWeaponBeamLifeCycle

// BeamWeaponBeamLocation
#pragma region

namespace NCsBeamWeaponBeamLocation
{
	namespace Ref
	{
		typedef EMCsBeamWeaponBeamLocation EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Self);
		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
		CSWP_API CS_ADD_TO_ENUM_MAP(Socket);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Camera);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsBeamWeaponBeamLocation_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsBeamWeaponBeamLocation_MAX;
}

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NParams
		{
			namespace NBeam
			{
				namespace NLocation
				{
					namespace Ref
					{
						typedef EMLocation EnumMapType;

						CSWP_API CS_ADD_TO_ENUM_MAP(Self);
						CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
						CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
						CSWP_API CS_ADD_TO_ENUM_MAP(Socket);
						CSWP_API CS_ADD_TO_ENUM_MAP(Component);
						CSWP_API CS_ADD_TO_ENUM_MAP(Camera);
						CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ELocation_MAX, "MAX");
					}
				}
			}
		}
	}
}

#pragma endregion BeamWeaponBeamLocation

// FCsBeamWeaponBeamParamsLocationInfo
#pragma region

#define InfoType NCsWeapon::NBeam::NParams::NBeam::FLocationInfo

void FCsBeamWeaponBeamParamsLocationInfo::CopyToInfo(InfoType* Info)
{
	typedef NCsWeapon::NBeam::NParams::NBeam::ELocation LocationType;

	Info->SetType((LocationType*)&Type);
	Info->SetBoneOrSocket(&BoneOrSocket);
}

void FCsBeamWeaponBeamParamsLocationInfo::CopyToInfoAsValue(InfoType* Info) const
{
	typedef NCsWeapon::NBeam::NParams::NBeam::ELocation LocationType;

	Info->SetType((LocationType)Type);
	Info->SetBoneOrSocket(BoneOrSocket);
}

#undef InfoType

bool FCsBeamWeaponBeamParamsLocationInfo::IsValidChecked(const FString& Context) const
{
	check(EMCsBeamWeaponBeamLocation::Get().IsValidEnumChecked(Context, Type));
	return true;
}

bool FCsBeamWeaponBeamParamsLocationInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_ENUM_VALID(EMCsBeamWeaponBeamLocation, ECsBeamWeaponBeamLocation, Type)
	return true;
}

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NParams
		{
			namespace NBeam
			{
				bool FLocationInfo::IsValidChecked(const FString& Context) const
				{
					typedef NCsWeapon::NBeam::NParams::NBeam::EMLocation LocationMapType;

					check(LocationMapType::Get().IsValidEnumChecked(Context, GetType()));
					return true;
				}

				bool FLocationInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
				{
					typedef NCsWeapon::NBeam::NParams::NBeam::EMLocation LocationMapType;
					typedef NCsWeapon::NBeam::NParams::NBeam::ELocation LocationType;

					CS_IS_ENUM_VALID(LocationMapType, LocationType, GetType())
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsBeamWeaponBeamParamsLocationInfo

// BeamWeaponBeamDirection
#pragma region

namespace NCsBeamWeaponBeamDirection
{
	namespace Ref
	{
		typedef EMCsBeamWeaponBeamDirection EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Self);
		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
		CSWP_API CS_ADD_TO_ENUM_MAP(Socket);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Camera);
		CSWP_API CS_ADD_TO_ENUM_MAP(Trace);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsBeamWeaponBeamDirection_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsBeamWeaponBeamDirection_MAX;
}

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NParams
		{
			namespace NBeam
			{
				namespace NDirection
				{
					namespace Ref
					{
						typedef EMDirection EnumMapType;

						CSWP_API CS_ADD_TO_ENUM_MAP(Self);
						CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
						CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
						CSWP_API CS_ADD_TO_ENUM_MAP(Socket);
						CSWP_API CS_ADD_TO_ENUM_MAP(Component);
						CSWP_API CS_ADD_TO_ENUM_MAP(Camera);
						CSWP_API CS_ADD_TO_ENUM_MAP(Trace);
						CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
						CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDirection_MAX, "MAX");
					}
				}
			}
		}
	}
}

#pragma endregion BeamWeaponBeamDirection

// FCsBeamWeaponBeamParamsDirectionInfo
#pragma region

#define InfoType NCsWeapon::NBeam::NParams::NBeam::FDirectionInfo

void FCsBeamWeaponBeamParamsDirectionInfo::CopyToInfo(InfoType* Info)
{
	typedef NCsWeapon::NBeam::NParams::NBeam::EDirection DirectionType;

	Info->SetType((DirectionType*)&Type);
	Info->SetBoneOrSocket(&BoneOrSocket);
	Info->SetRules(&Rules);
}

void FCsBeamWeaponBeamParamsDirectionInfo::CopyToInfoAsValue(InfoType* Info) const
{
	typedef NCsWeapon::NBeam::NParams::NBeam::EDirection DirectionType;

	Info->SetType((DirectionType)Type);
	Info->SetBoneOrSocket(BoneOrSocket);
	Info->SetRules(Rules);
}

#undef InfoType

bool FCsBeamWeaponBeamParamsDirectionInfo::IsValidChecked(const FString& Context) const
{
	// Check Type is Valid
	check(EMCsBeamWeaponBeamDirection::Get().IsValidEnumChecked(Context, Type));
	// BoneOrSocket is Valid
	if (Type == ECsBeamWeaponBeamDirection::Bone ||
		Type == ECsBeamWeaponBeamDirection::Socket)
	{
		CS_IS_NAME_NONE_CHECKED(BoneOrSocket)

		checkf(Rules != 0, TEXT("%s Rules should != 0 for Type: %s."), *Context, EMCsBeamWeaponBeamDirection::Get().ToChar(Type));
	}
	return true;
}

bool FCsBeamWeaponBeamParamsDirectionInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	// Check Type is Valid
	CS_IS_ENUM_VALID(EMCsBeamWeaponBeamDirection, ECsBeamWeaponBeamDirection, Type)
	// BoneOrSocket is Valid
	if (Type == ECsBeamWeaponBeamDirection::Bone ||
		Type == ECsBeamWeaponBeamDirection::Socket)
	{
		CS_IS_NAME_NONE(BoneOrSocket)

		if (Rules == 0)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s Rules should != 0 for Type: %s."), *Context, EMCsBeamWeaponBeamDirection::Get().ToChar(Type)));
			return false;
		}
	}
	return true;
}

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NParams
		{
			namespace NBeam
			{
				bool FDirectionInfo::IsValidChecked(const FString& Context) const
				{
					typedef NCsWeapon::NBeam::NParams::NBeam::EMDirection DirectionMapType;
					typedef NCsWeapon::NBeam::NParams::NBeam::EDirection DirectionType;

					// Check Type is Valid
					check(DirectionMapType::Get().IsValidEnumChecked(Context, GetType()));
					// BoneOrSocket is Valid
					if (GetType() == DirectionType::Bone ||
						GetType() == DirectionType::Socket)
					{
						CS_IS_NAME_NONE_CHECKED(GetBoneOrSocket())

						checkf(GetRules() != 0, TEXT("%s GetRules() should != 0 for GetType(): %s."), *Context, DirectionMapType::Get().ToChar(GetType()));
					}
					return true;
				}

				bool FDirectionInfo::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
				{
					typedef NCsWeapon::NBeam::NParams::NBeam::EMDirection DirectionMapType;
					typedef NCsWeapon::NBeam::NParams::NBeam::EDirection DirectionType;

					// Check Type is Valid
					CS_IS_ENUM_VALID(DirectionMapType, DirectionType, GetType())
					// BoneOrSocket is Valid
					if (GetType() == DirectionType::Bone ||
						GetType() == DirectionType::Socket)
					{
						CS_IS_NAME_NONE(GetBoneOrSocket())

						if (GetRules() == 0)
						{
							CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s GetRules() should != 0 for GetType(): %s."), *Context, DirectionMapType::Get().ToChar(GetType())));
							return false;
						}
					}
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsBeamWeaponBeamParamsDirectionInfo

const FName NCsWeapon::NBeam::NParams::NBeam::IBeam::Name = FName("NCsWeapon::NBeam::NParams::NBeam::IBeam");

// FCsBeamWeaponBeamParams
#pragma region

#define ParamsType NCsWeapon::NBeam::NParams::NBeam::FImpl

void FCsBeamWeaponBeamParams::CopyToParams(ParamsType* Params)
{
	typedef NCsWeapon::NBeam::NParams::NBeam::ELifeCycle LifeCycleType;

	Params->SetIsAttached(&bAttached);
	Params->SetAttachRules(AttachRules.ToRule());
	Params->SetLifeCycle((LifeCycleType*)&LifeCycle);
	LocationInfo.CopyToInfo(Params->GetLocationInfoPtr());
	DirectionInfo.CopyToInfo(Params->GetDirectionInfoPtr());
}

#undef ParamsType

bool FCsBeamWeaponBeamParams::IsValidChecked(const FString& Context) const
{
	typedef EMCsBeamWeaponBeamLifeCycle LifeCycleMapType;

	// Check LifeCycle is Valid
	check(LifeCycleMapType::Get().IsValidEnumChecked(Context, LifeCycle));
	// Check LocationInfo is Valid
	CS_IS_VALID_CHECKED(LocationInfo);
	// Check DirectionInfo is Valid
	CS_IS_VALID_CHECKED(DirectionInfo);
	return true;
}

bool FCsBeamWeaponBeamParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	typedef EMCsBeamWeaponBeamLifeCycle LifeCycleMapType;
	typedef ECsBeamWeaponBeamLifeCycle LifeCycleType;

	// Check LifeCycle is Valid
	CS_IS_ENUM_VALID(LifeCycleMapType, LifeCycleType, LifeCycle)
	// Check LocationInfo is Valid
	CS_IS_VALID(LocationInfo)
	// Check DirectionInfo is Valid
	CS_IS_VALID(DirectionInfo)
	return true;
}

const FName NCsWeapon::NBeam::NParams::NBeam::FImpl::Name = FName("NCsWeapon::NBeam::NParams::NBeam::FImpl");

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NParams
		{
			namespace NBeam
			{
				FImpl::FImpl() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// BeamParamsType (NCsWeapon::NBeam::NParams::NBeam::IBeam)
					CS_CTOR_INIT_MEMBER_WITH_PROXY(bAttached, true),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(AttachRules, FAttachmentTransformRules::SnapToTargetNotIncludingScale),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(LifeCycle, NCsWeapon::NBeam::NParams::NBeam::ELifeCycle::AfterStopFire),
					LocationInfo(),
					DirectionInfo()
				{
					// ICsGetInterfaceMap
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FImpl>(this);

					typedef NCsWeapon::NBeam::NParams::NBeam::IBeam BeamParamsType;

					InterfaceMap->Add<BeamParamsType>(static_cast<BeamParamsType*>(this));

					CS_CTOR_SET_MEMBER_PROXY(bAttached);
					CS_CTOR_SET_MEMBER_PROXY(AttachRules);
					CS_CTOR_SET_MEMBER_PROXY(LifeCycle);
				}

				FImpl::~FImpl()
				{
					delete InterfaceMap;
				}

				bool FImpl::IsValidChecked(const FString& Context) const
				{
					typedef NCsWeapon::NBeam::NParams::NBeam::EMLifeCycle LifeCycleMapType;

					// Check LifeCycle is Valid
					check(LifeCycleMapType::Get().IsValidEnumChecked(Context, GetLifeCycle()));
					// Check LocationInfo is Valid
					CS_IS_VALID_CHECKED(LocationInfo);
					// Check DirectionInfo is Valid
					CS_IS_VALID_CHECKED(DirectionInfo);
					return true;
				}

				bool FImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
				{
					typedef NCsWeapon::NBeam::NParams::NBeam::EMLifeCycle LifeCycleMapType;
					typedef NCsWeapon::NBeam::NParams::NBeam::ELifeCycle LifeCycleType;

					// Check LifeCycle is Valid
					CS_IS_ENUM_VALID(LifeCycleMapType, LifeCycleType, GetLifeCycle())
					// Check LocationInfo is Valid
					CS_IS_VALID(LocationInfo)
					// Check DirectionInfo is Valid
					CS_IS_VALID(DirectionInfo)
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsBeamWeaponBeamParams