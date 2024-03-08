// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Launch/Trace/CsTypes_Params_ProjectileWeapon_LaunchTrace.h"

// Library
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
#include "Data/CsLibrary_Data_Weapon.h"
#include "Library/CsLibrary_Valid.h"
// Data
#include "Projectile/Data/CsData_ProjectileWeaponImplSlice.h"
// Params
#include "Projectile/Params/Launch/Trace/CsParams_ProjectileWeapon_LaunchTraceImpl.h"

// ProjectileWeaponLaunchTraceStart
#pragma region

namespace NCsProjectileWeaponLaunchTraceStart
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponLaunchTraceStart EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(LaunchLocation, "Launch Location");
		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Camera);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponLaunchTraceStart_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsProjectileWeaponLaunchTraceStart_MAX;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
				namespace NTrace
				{
					namespace NStart
					{
						namespace Ref
						{
							typedef EMStart EnumMapType;

							CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(LaunchLocation, "Launch Location");
							CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
							CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
							CSWP_API CS_ADD_TO_ENUM_MAP(Component);
							CSWP_API CS_ADD_TO_ENUM_MAP(Camera);
							CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
							CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(EStart_MAX, "MAX");
						}
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponLaunchTraceStart

// ProjectileWeaponLaunchTraceDirection
#pragma region

namespace NCsProjectileWeaponLaunchTraceDirection
{
	namespace Ref
	{
		typedef EMCsProjectileWeaponLaunchTraceDirection EnumMapType;

		CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
		CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
		CSWP_API CS_ADD_TO_ENUM_MAP(Component);
		CSWP_API CS_ADD_TO_ENUM_MAP(Camera);
		CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
		CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsProjectileWeaponLaunchTraceDirection_MAX, "MAX");
	}

	CSWP_API const uint8 MAX = (uint8)Type::ECsProjectileWeaponLaunchTraceDirection_MAX;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
				namespace NTrace
				{
					namespace NDirection
					{
						namespace Ref
						{
							typedef EMDirection EnumMapType;

							CSWP_API CS_ADD_TO_ENUM_MAP(Owner);
							CSWP_API CS_ADD_TO_ENUM_MAP(Bone);
							CSWP_API CS_ADD_TO_ENUM_MAP(Component);
							CSWP_API CS_ADD_TO_ENUM_MAP(Camera);
							CSWP_API CS_ADD_TO_ENUM_MAP(Custom);
							CSWP_API CS_ADD_TO_ENUM_MAP_CUSTOM(EDirection_MAX, "MAX");
						}
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponLaunchTraceDirection

// FCsProjectileWeapon_Launch_TraceParams
#pragma region

#define ParamsType NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FParams

void FCsProjectileWeapon_Launch_TraceParams::CopyToParams(ParamsType* Params)
{
	typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EStart StartType;
	typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EDirection DirectionType;

	Params->SetType(&Type);
	Params->SetMethod(&Method);
	Params->SetStart((StartType*)(&Start));
	Params->SetDirection((DirectionType*)(&Direction));
	Params->SetDistance(&Distance);
}

void FCsProjectileWeapon_Launch_TraceParams::CopyToParamsAsValue(ParamsType* Params) const
{
	typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EStart StartType;
	typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EDirection DirectionType;

	Params->SetType(Type);
	Params->SetMethod(Method);
	Params->SetStart((StartType)Start);
	Params->SetDirection((DirectionType)Direction);
	Params->SetDistance(Distance);
}

#undef ParamsType

bool FCsProjectileWeapon_Launch_TraceParams::IsValidChecked(const FString& Context) const
{
	typedef EMCsProjectileWeaponLaunchTraceStart StartMapType;
	typedef EMCsProjectileWeaponLaunchTraceDirection DirectionMapType;

	CS_IS_ENUM_VALID_CHECKED(StartMapType, Start)
	CS_IS_ENUM_VALID_CHECKED(DirectionMapType, Direction)
	CS_IS_FLOAT_GREATER_THAN_CHECKED(Distance, 0.0f)
	return true;
}

bool FCsProjectileWeapon_Launch_TraceParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	typedef EMCsProjectileWeaponLaunchTraceStart StartMapType;
	typedef ECsProjectileWeaponLaunchTraceStart StartType;
	typedef EMCsProjectileWeaponLaunchTraceDirection DirectionMapType;
	typedef ECsProjectileWeaponLaunchTraceDirection DirectionType;

	CS_IS_ENUM_VALID(StartMapType, StartType, Start)
	CS_IS_ENUM_VALID(DirectionMapType, DirectionType, Direction)
	CS_IS_FLOAT_GREATER_THAN(Distance, 0.0f)
	return true;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
				namespace NTrace
				{
					bool FParams::IsValidChecked(const FString& Context) const
					{
						typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EMStart StartMapType;
						typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EMDirection DirectionMapType;

						CS_IS_ENUM_VALID_CHECKED(StartMapType, GetStart())
						CS_IS_ENUM_VALID_CHECKED(DirectionMapType, GetDirection())
						CS_IS_FLOAT_GREATER_THAN_CHECKED(GetDistance(), 0.0f)
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EMStart StartMapType;
						typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EStart StartType;
						typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EMDirection DirectionMapType;
						typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EDirection DirectionType;

						CS_IS_ENUM_VALID(StartMapType, StartType, GetStart())
						CS_IS_ENUM_VALID(DirectionMapType, DirectionType, GetDirection())
						CS_IS_FLOAT_GREATER_THAN(GetDistance(), 0.0f)
						return true;
					}
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Launch_TraceParams

// FCsProjectileWeapon_LaunchTraceParams
#pragma region

#define ParamsType NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FImpl

ParamsType* FCsProjectileWeapon_LaunchTraceParams::AddSafeToSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
{
	ParamsType* Params = AddSafeToSlice_Internal(Context, WorldContext, Name, Log);

	if (!Params)
		return nullptr;

	CopyToParams(Params);
	return Params;
}

ParamsType* FCsProjectileWeapon_LaunchTraceParams::AddSafeToSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	ParamsType* Params = AddSafeToSlice_Internal(Context, WorldContext, Name, Log);

	if (!Params)
		return nullptr;

	CopyToParamsAsValue(Params);
	return Params;
}

ParamsType* FCsProjectileWeapon_LaunchTraceParams::AddSafeToSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	if (!IsValid(Context, Log))
		return nullptr;

	typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;
	typedef NCsWeapon::NData::IData WeaponDataType;

	WeaponDataType* Data = WeaponManagerLibrary::GetSafeData(Context, WorldContext, Name, Log);

	if (!Data)
		return nullptr;

	typedef NCsWeapon::NData::FLibrary WeaponDataLibrary;
	typedef NCsWeapon::NProjectile::NData::IData PrjWeaponDataType;

	PrjWeaponDataType* PrjWeaponData = WeaponDataLibrary::GetSafeInterfaceChecked<PrjWeaponDataType>(Context, Data);

	if (!PrjWeaponData)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data: %s does NOT implement the interface: %s."), *Context, *(Name.ToString()), *(PrjWeaponDataType::Name.ToString())));
		return nullptr;
	}

	typedef NCsWeapon::NProjectile::NData::FImplSlice PrjWeaponDataImplType;

	PrjWeaponDataImplType* PrjWeaponDataImpl = NCsInterfaceMap::SafeStaticCastChecked<PrjWeaponDataImplType, PrjWeaponDataType>(Context, PrjWeaponData);

	if (!PrjWeaponDataImpl)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Data: %s does NOT contain the slice: %s."), *Context, *(Name.ToString()), *(PrjWeaponDataImplType::Name.ToString())));
		return nullptr;
	}

	ParamsType* Params = PrjWeaponDataImpl->ConstructLaunchParams<ParamsType>();

	return Params;
}

void FCsProjectileWeapon_LaunchTraceParams::CopyToParams(ParamsType* Params)
{
	LocationParams.CopyToParams(Params->GetLocationParamsPtr());
	DirectionParams.CopyToParams(Params->GetDirectionParamsPtr());
	TraceParams.CopyToParams(Params->GetTraceParamsPtr());
}

void FCsProjectileWeapon_LaunchTraceParams::CopyToParamsAsValue(ParamsType* Params) const
{
	LocationParams.CopyToParamsAsValue(Params->GetLocationParamsPtr());
	DirectionParams.CopyToParamsAsValue(Params->GetDirectionParamsPtr());
	TraceParams.CopyToParamsAsValue(Params->GetTraceParamsPtr());
}

#undef ParamsType

bool FCsProjectileWeapon_LaunchTraceParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_VALID(LocationParams)
	CS_IS_VALID(DirectionParams)
	CS_IS_VALID(TraceParams)
	return true;
}

#pragma endregion FCsProjectileWeapon_LaunchTraceParams

// FCsProjectileWeapon_Launch_WithTraceParams
#pragma region

#define ParamsType NCsWeapon::NProjectile::NParams::NLaunch::NWithTrace::FParams

void FCsProjectileWeapon_Launch_WithTraceParams::CopyToParams(ParamsType* Params)
{
	LocationParams.CopyToParams(Params->GetLocationParamsPtr());
	DirectionParams.CopyToParams(Params->GetDirectionParamsPtr());
	TraceParams.CopyToParams(Params->GetTraceParamsPtr());
}

void FCsProjectileWeapon_Launch_WithTraceParams::CopyToParamsAsValue(ParamsType* Params) const
{
	LocationParams.CopyToParamsAsValue(Params->GetLocationParamsPtr());
	DirectionParams.CopyToParamsAsValue(Params->GetDirectionParamsPtr());
	TraceParams.CopyToParamsAsValue(Params->GetTraceParamsPtr());
}

#undef ParamsType

bool FCsProjectileWeapon_Launch_WithTraceParams::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(LocationParams);
	CS_IS_VALID_CHECKED(DirectionParams);
	CS_IS_VALID_CHECKED(TraceParams);
	return true;
}

bool FCsProjectileWeapon_Launch_WithTraceParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_VALID(LocationParams)
	CS_IS_VALID(DirectionParams)
	CS_IS_VALID(TraceParams)
	return true;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NParams
		{
			namespace NLaunch
			{
				namespace NWithTrace
				{
					bool FParams::IsValidChecked(const FString& Context) const
					{
						CS_IS_VALID_CHECKED(GetLocationParams());
						CS_IS_VALID_CHECKED(GetDirectionParams());
						CS_IS_VALID_CHECKED(GetTraceParams());
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						CS_IS_VALID(GetLocationParams())
						CS_IS_VALID(GetDirectionParams())
						CS_IS_VALID(GetTraceParams())
						return true;
					}
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Launch_WithTraceParams