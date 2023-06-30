// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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

	typedef NCsWeapon::NProjectile::NParams::NLaunch::EDirection LaunchDirectionType;
	typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EStart LaunchTraceStartType;
	typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EDirection LaunchTraceDirectionType;

	Params->SetDirectionType((LaunchDirectionType*)(&DirectionType));
	Params->SetDirectionOffset(&DirectionOffset);
	Params->SetbInvertDirection(&bInvertDirection);
	Params->SetDirectionRules(&DirectionRules);
	Params->SetTraceType(&TraceType);
	Params->SetTraceMethod(&TraceMethod);
	Params->SetTraceStartType((LaunchTraceStartType*)(&TraceStartType));
	Params->SetTraceDirectionType((LaunchTraceDirectionType*)(&TraceDirectionType));
	Params->SetTraceDistance(&TraceDistance);
}

void FCsProjectileWeapon_LaunchTraceParams::CopyToParamsAsValue(ParamsType* Params) const
{
	LocationParams.CopyToParamsAsValue(Params->GetLocationParamsPtr());

	typedef NCsWeapon::NProjectile::NParams::NLaunch::EDirection LaunchDirectionType;
	typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EStart LaunchTraceStartType;
	typedef NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EDirection LaunchTraceDirectionType;

	Params->SetDirectionType((LaunchDirectionType)DirectionType);
	Params->SetDirectionOffset(DirectionOffset);
	Params->SetbInvertDirection(bInvertDirection);
	Params->SetDirectionRules(DirectionRules);
	Params->SetTraceType(TraceType);
	Params->SetTraceMethod(TraceMethod);
	Params->SetTraceStartType((LaunchTraceStartType)TraceStartType);
	Params->SetTraceDirectionType((LaunchTraceDirectionType)TraceDirectionType);
	Params->SetTraceDistance(TraceDistance);
}

#undef ParamsType

bool FCsProjectileWeapon_LaunchTraceParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_VALID(LocationParams)

	typedef EMCsProjectileWeaponLaunchDirection LaunchDirectionMapType;
	typedef ECsProjectileWeaponLaunchDirection LaunchDirectionType;

	CS_IS_ENUM_VALID(LaunchDirectionMapType, LaunchDirectionType, DirectionType)

	if (DirectionRules == NCsRotationRules::None)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No Rules set for DirectionType. DirectionRules == 0."), *Context));
		return false;
	}

	typedef EMCsProjectileWeaponLaunchTraceStart LaunchTraceStartMapType;
	typedef ECsProjectileWeaponLaunchTraceStart LaunchTraceStartType;
	typedef EMCsProjectileWeaponLaunchTraceDirection LaunchTraceDirectionMapType;
	typedef ECsProjectileWeaponLaunchTraceDirection LaunchTraceDirectionType;

	CS_IS_ENUM_VALID(LaunchTraceStartMapType, LaunchTraceStartType, TraceStartType)
	CS_IS_ENUM_VALID(LaunchTraceDirectionMapType, LaunchTraceDirectionType, TraceDirectionType)
	CS_IS_FLOAT_GREATER_THAN(TraceDistance, 0.0f)
	return true;
}

#pragma endregion FCsProjectileWeapon_LaunchTraceParams