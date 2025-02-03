// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Params/Launch/Trace/CsTypes_Params_ProjectileWeapon_LaunchTrace.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Managers/Weapon/CsLibrary_Manager_Weapon.h"
#include "Data/CsLibrary_Data_Weapon.h"
#include "Library/CsLibrary_Valid.h"
// Data
#include "Projectile/Data/CsData_ProjectileWeaponImplSlice.h"
// Params
#include "Projectile/Params/Launch/Trace/CsParams_ProjectileWeapon_LaunchTraceImpl.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsTypes_Params_ProjectileWeapon_LaunchTrace)

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

namespace NCsProjectileWeapon_Launch_TraceParams
{
	using StartType = NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EStart;
	using DirectionType = NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EDirection;

	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY(Params, Type);
		CS_THIS_COPY_TO_PROXY(Params, Method);
		CS_THIS_COPY_TYPE_TO_PROXY(Params, Start, StartType);
		CS_THIS_COPY_TYPE_TO_PROXY(Params, Direction, DirectionType);
		CS_THIS_COPY_TO_PROXY(Params, Distance);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Type);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Method);
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, Start, StartType);
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, Direction, DirectionType);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Distance);
	}
}

bool FCsProjectileWeapon_Launch_TraceParams::IsValidChecked(const FString& Context) const
{
	CS_IS_ENUM_VALID_CHECKED(StartMapType, Start)
	CS_IS_ENUM_VALID_CHECKED(DirectionMapType, Direction)
	CS_IS_FLOAT_GREATER_THAN_CHECKED(Distance, 0.0f)
	return true;
}

bool FCsProjectileWeapon_Launch_TraceParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
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
					using StartMapType = NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EMStart;
					using DirectionMapType = NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EMDirection;

					bool FParams::IsValidChecked(const FString& Context) const
					{
						CS_IS_ENUM_VALID_CHECKED(StartMapType, GetStart())
						CS_IS_ENUM_VALID_CHECKED(DirectionMapType, GetDirection())
						CS_IS_FLOAT_GREATER_THAN_CHECKED(GetDistance(), 0.0f)
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
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

namespace NCsProjectileWeapon_LaunchTraceParams
{
	ParamsType* FImpl::AddSafeToSlice(const FString& Context, ThisType* This, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) 
	{
		ParamsType* Params = AddSafeToSlice_Internal(Context, This, WorldContext, Name, Log);

		if (!Params)
			return nullptr;

		CopyToParams(Params);
		return Params;
	}

	ParamsType* FImpl::AddSafeToSliceAsValue(const FString& Context, const ThisType* This, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
	{
		ParamsType* Params = AddSafeToSlice_Internal(Context, This, WorldContext, Name, Log);

		if (!Params)
			return nullptr;

		CopyToParamsAsValue(This, Params);
		return Params;
	}

	ParamsType* FImpl::AddSafeToSlice_Internal(const FString& Context, const ThisType* This, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
	{
		if (!This->IsValid(Context, Log))
		return nullptr;

		typedef NCsWeapon::NManager::FLibrary WeaponManagerLibrary;
		typedef NCsWeapon::NData::IData WeaponDataType;

		WeaponDataType* Data = WeaponManagerLibrary::GetSafeData(Context, WorldContext, Name, Log);

		if (!Data)
			return nullptr;

		typedef NCsWeapon::NProjectile::NData::IData PrjWeaponDataType;

		PrjWeaponDataType* PrjWeaponData = CsWeaponDataLibrary::GetSafeInterfaceChecked<PrjWeaponDataType>(Context, Data);

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

	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		This->LocationParams.CopyToParams(Params->GetLocationParamsPtr());
		This->DirectionParams.CopyToParams(Params->GetDirectionParamsPtr());
		This->TraceParams.CopyToParams(Params->GetTraceParamsPtr());
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		This->LocationParams.CopyToParamsAsValue(Params->GetLocationParamsPtr());
		This->DirectionParams.CopyToParamsAsValue(Params->GetDirectionParamsPtr());
		This->TraceParams.CopyToParamsAsValue(Params->GetTraceParamsPtr());
	}
}

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

namespace NCsProjectileWeapon_Launch_WithTraceParams
{
	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR(Params, LocationParams);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR(Params, DirectionParams);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR(Params, TraceParams);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR_AS_VALUE(Params, LocationParams);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR_AS_VALUE(Params, DirectionParams);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR_AS_VALUE(Params, TraceParams);
	}
}

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