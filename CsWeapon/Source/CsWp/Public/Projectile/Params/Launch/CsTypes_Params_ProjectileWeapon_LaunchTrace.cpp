// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Launch/CsTypes_Params_ProjectileWeapon_LaunchTrace.h"

// Library
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
#include "Data/CsLibrary_Data_Weapon.h"
#include "Library/CsLibrary_Valid.h"
// Data
#include "Projectile/Data/CsData_ProjectileWeaponImplSlice.h"
// Params
#include "Projectile/Params/Launch/CsParams_ProjectileWeapon_LaunchTraceImpl.h"

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

#pragma endregion ProjectileWeaponLaunchTraceDirection

// FCsProjectileWeaponLaunchTraceParams
#pragma region

#define ParamsType NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FImpl

ParamsType* FCsProjectileWeaponLaunchTraceParams::AddSafeToSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
{
	ParamsType* Params = AddSafeToSlice_Internal(Context, WorldContext, Name, Log);

	if (!Params)
		return nullptr;

	CopyToParams(Params);
	return Params;
}

ParamsType* FCsProjectileWeaponLaunchTraceParams::AddSafeToSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	ParamsType* Params = AddSafeToSlice_Internal(Context, WorldContext, Name, Log);

	if (!Params)
		return nullptr;

	CopyToParamsAsValue(Params);
	return Params;
}

ParamsType* FCsProjectileWeaponLaunchTraceParams::AddSafeToSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
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

void FCsProjectileWeaponLaunchTraceParams::CopyToParams(ParamsType* Params)
{
	Params->SetLocationType(&LocationType);
	Params->SetDirectionType(&DirectionType);
	Params->SetDirectionRules(&DirectionRules);
	Params->SetTraceType(&TraceType);
	Params->SetTraceMethod(&TraceMethod);
	Params->SetTraceStartType(&TraceStartType);
	Params->SetTraceDirectionType(&TraceDirectionType);
	Params->SetTraceDistance(&TraceDistance);
}

void FCsProjectileWeaponLaunchTraceParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetLocationType(LocationType);
	Params->SetDirectionType(DirectionType);
	Params->SetDirectionRules(DirectionRules);
	Params->SetTraceType(TraceType);
	Params->SetTraceMethod(TraceMethod);
	Params->SetTraceStartType(TraceStartType);
	Params->SetTraceDirectionType(TraceDirectionType);
	Params->SetTraceDistance(TraceDistance);
}

#undef ParamsType

bool FCsProjectileWeaponLaunchTraceParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	if (DirectionRules == NCsRotationRules::None)
	{
		CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No DirectionRules set in Launchparams for Data."), *Context));
		return false;
	}

	CS_IS_FLOAT_GREATER_THAN(TraceDistance, 0.0f)
	return true;
}

#pragma endregion FCsProjectileWeaponLaunchTraceParams