// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Projectile/Params/Launch/CsTypes_Params_ProjectileWeapon_Launch.h"
#include "Managers/Trace/CsTypes_Trace.h"
#include "Types/CsTypes_Math.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsTypes_Params_ProjectileWeapon_LaunchTrace.generated.h"

// ProjectileWeaponLaunchTraceStart
#pragma region

/**
* Describes how the start of a trace should be chosen.
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponLaunchTraceStart : uint8
{
	/** The launch location (the result from ILaunch::GetLocationType()) is used. */
	LaunchLocation							UMETA(DisplayName = "Launch Location"),
	/** Owner's Location. If the Owner is of type: AActor, then it will
		be GetActorLocation(). */
	Owner									UMETA(DisplayName = "Owner"),
	/** If there is a Skeletal Mesh that acts as the root object for the Weapon,
		use the Bone's location. */
	Bone									UMETA(DisplayName = "Bone"),
	/** SceneComponent's Location. The Component is marked as the Launch Component Transform. */
	Component								UMETA(DisplayName = "Component"),
	/** Owner's Camera's Location. */
	Camera									UMETA(DisplayName = "Camera"),
	Custom									UMETA(DisplayName = "Custom"),
	ECsProjectileWeaponLaunchTraceStart_MAX	UMETA(Hidden), 
};

struct CSWP_API EMCsProjectileWeaponLaunchTraceStart : public TCsEnumMap<ECsProjectileWeaponLaunchTraceStart>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileWeaponLaunchTraceStart, ECsProjectileWeaponLaunchTraceStart)
};

namespace NCsProjectileWeaponLaunchTraceStart
{
	typedef ECsProjectileWeaponLaunchTraceStart Type;

	namespace Ref
	{
		extern CSWP_API const Type LaunchLocation;
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Bone;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type Camera;
		extern CSWP_API const Type Custom;
		extern CSWP_API const Type ECsProjectileWeaponLaunchTraceStart_MAX;
	}

	extern CSWP_API const uint8 MAX;
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
					/**
					* Describes how the start of a trace should be chosen.
					*/
					enum class EStart : uint8 
					{
						/** The launch location (the result from ILaunch::GetLocationType()) is used. 
							See NCsWeapon::NCsProjectile::NParams::NLaunch::ELocation. */
						LaunchLocation,
						/** Owner's Location. If the Owner is of type: AActor, then it will
							be GetActorLocation(). */
						Owner,
						/** If there is a Skeletal Mesh that acts as the root object for the Weapon,
							use the Bone's location. */
						Bone,
						/** SceneComponent's Location. The Component is marked as the Launch Component Transform. */
						Component,
						/** Owner's Camera's Location. */
						Camera,
						Custom,
						EStart_MAX
					};

					struct CSWP_API EMStart : public TCsEnumMap<EStart>
					{
						CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMStart, EStart)
					};

					namespace NStart
					{
						typedef EStart Type;

						namespace Ref
						{
							extern CSWP_API const Type LaunchLocation;
							extern CSWP_API const Type Owner;
							extern CSWP_API const Type Bone;
							extern CSWP_API const Type Component;
							extern CSWP_API const Type Camera;
							extern CSWP_API const Type Custom;
							extern CSWP_API const Type EStart_MAX;
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

/**
* Describes how the direction (end) of a trace should be chosen. The normalized
* direction is used to project outward GetTraceDistance() from the start of the
* trace.
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponLaunchTraceDirection : uint8
{
	/** Owner's Rotation (forward). If the Owner is of type: AActor, then use
		get the Owner's forward vector. */
	Owner										UMETA(DisplayName = "Owner"),
	/** If there is a Skeletal Mesh that acts as the root object for the Weapon,
		then use the Bone's rotation (to normalized vector). */
	Bone										UMETA(DisplayName = "Bone"),
	/** SceneComponent's Rotation. The Component is marked as the Launch Component Transform. */
	Component									UMETA(DisplayName = "Component"),
	/** Owner's Camera's Rotation (forward). */
	Camera										UMETA(DisplayName = "Camera"),
	Custom										UMETA(DisplayName = "Custom"),
	ECsProjectileWeaponLaunchTraceDirection_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsProjectileWeaponLaunchTraceDirection : public TCsEnumMap<ECsProjectileWeaponLaunchTraceDirection>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileWeaponLaunchTraceDirection, ECsProjectileWeaponLaunchTraceDirection)
};

namespace NCsProjectileWeaponLaunchTraceDirection
{
	typedef ECsProjectileWeaponLaunchTraceDirection Type;

	namespace Ref
	{
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Bone;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type Camera;
		extern CSWP_API const Type Custom;
		extern CSWP_API const Type ECsProjectileWeaponLaunchTraceDirection_MAX;
	}

	extern CSWP_API const uint8 MAX;
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
					/**
					* Describes how the direction (end) of a trace should be chosen. The normalized
					* direction is used to project outward GetTraceDistance() from the start of the 
					* trace.
					*/
					enum class EDirection : uint8
					{
						/** Owner's Rotation (forward). If the Owner is of type: AActor, then use 
							get the Owner's forward vector. */
						Owner,
						/** If there is a Skeletal Mesh that acts as the root object for the Weapon,
							then use the Bone's rotation (to normalized vector). */
						Bone,
						/** SceneComponent's Rotation. The Component is marked as the Launch Component Transform. */
						Component,
						/** Owner's Camera's Rotation (forward). */
						Camera,
						Custom,
						EDirection_MAX
					};

					struct CSWP_API EMDirection : public TCsEnumMap<EDirection>
					{
						CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMDirection, EDirection)
					};

					namespace NDirection
					{
						typedef EDirection Type;

						namespace Ref
						{
							extern CSWP_API const Type Owner;
							extern CSWP_API const Type Bone;
							extern CSWP_API const Type Component;
							extern CSWP_API const Type Camera;
							extern CSWP_API const Type Custom;
							extern CSWP_API const Type EDirection_MAX;
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

struct FCsProjectileWeapon_Launch_TraceParams;

// ParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FParams)
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NProjectile, NParams, NLaunch, NTrace, FParams)

namespace NCsProjectileWeapon_Launch_TraceParams
{
	using ThisType = FCsProjectileWeapon_Launch_TraceParams;
	using ParamsType = NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FParams;

	// Separate implementation to allow for clearer use of aliases
	struct CSWP_API FImpl
	{
	public:

		static void CopyToParams(ThisType* This, ParamsType* Params);
		static void CopyToParamsAsValue(const ThisType* This, ParamsType* Params);
	};
}

// ParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FParams)
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NProjectile, NParams, NLaunch, NTrace, FParams)

/**
* Describes any Trace information related to Launching a Projectile using a Trace from a Projectile Weapon.
* The trace may determine the Location and/or Direction with which to Launch the Projectile.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeapon_Launch_TraceParams
{
	GENERATED_USTRUCT_BODY()

private:

	using StartMapType = EMCsProjectileWeaponLaunchTraceStart;
	using StartType = ECsProjectileWeaponLaunchTraceStart;
	using DirectionMapType = EMCsProjectileWeaponLaunchTraceDirection;
	using DirectionType = ECsProjectileWeaponLaunchTraceDirection;

public:

	/** Describes what type of Trace to perform. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	ECsTraceType Type;

	/** Describes how (number) the Trace is performed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	ECsTraceMethod Method;

	/** Describes how the start of a trace should be chosen. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	ECsProjectileWeaponLaunchTraceStart Start;

	/** Describes how the direction (end) of a trace should be chosen. The normalized
		direction is used to project outward GetTraceDistance() from the start of the
		trace. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	ECsProjectileWeaponLaunchTraceDirection Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float Distance;

	FCsProjectileWeapon_Launch_TraceParams() :
		Type(ECsTraceType::Line),
		Method(ECsTraceMethod::Single),
		Start(ECsProjectileWeaponLaunchTraceStart::LaunchLocation),
		Direction(ECsProjectileWeaponLaunchTraceDirection::Owner),
		Distance(1000.0f)
	{
	}

	using ParamsType = NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FParams;
	using _Impl = NCsProjectileWeapon_Launch_TraceParams::FImpl;

	FORCEINLINE void CopyToParams(ParamsType* Params)				{ _Impl::CopyToParams(this, Params); }
	FORCEINLINE void CopyToParamsAsValue(ParamsType* Params) const	{ _Impl::CopyToParamsAsValue(this, Params); }

public:

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

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
					/**
					* Describes any Trace information related to Launching a Projectile using a Trace from a Projectile Weapon.
					* The trace may determine the Location and/or Direction with which to Launch the Projectile.
					*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
					*  Projectile is an object that implements the interface: ICsProjectile.
					*/
					struct CSWP_API FParams
					{
					private:

						using StartType = NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EStart;
						using DirectionType = NCsWeapon::NProjectile::NParams::NLaunch::NTrace::EDirection;

					private:

						/** Describes what type of Trace to perform. */
						CS_DECLARE_MEMBER_WITH_PROXY(Type, ECsTraceType)
						/** Describes how (number) the Trace is performed. */
						CS_DECLARE_MEMBER_WITH_PROXY(Method, ECsTraceMethod)
						/** Describes how the start of a trace should be chosen. */
						CS_DECLARE_MEMBER_WITH_PROXY(Start, StartType)
						/** Describes how the direction (end) of a trace should be chosen. The normalized
							direction is used to project outward GetTraceDistance() from the start of the
							trace. */
						CS_DECLARE_MEMBER_WITH_PROXY(Direction, DirectionType)
						CS_DECLARE_MEMBER_WITH_PROXY(Distance, float)
						

					public:

						FParams() :
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Type, ECsTraceType::Line),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Method, ECsTraceMethod::Single),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Start, StartType::LaunchLocation),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Direction, DirectionType::Owner),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Distance, 1000.0f)
						{
							CS_CTOR_SET_MEMBER_PROXY(Type);
							CS_CTOR_SET_MEMBER_PROXY(Method);
							CS_CTOR_SET_MEMBER_PROXY(Start);
							CS_CTOR_SET_MEMBER_PROXY(Direction);
							CS_CTOR_SET_MEMBER_PROXY(Distance);
						}

						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, ECsTraceType)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Method, ECsTraceMethod)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Start, StartType)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Direction, DirectionType)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Distance, float)
					
						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
					};
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Launch_TraceParams

// FCsProjectileWeapon_LaunchTraceParams (TODO: DEPRECATE)
#pragma region

struct FCsProjectileWeapon_LaunchTraceParams;

// ParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::NImpl::FImpl)
CS_FWD_DECLARE_STRUCT_NAMESPACE_6(NCsWeapon, NProjectile, NParams, NLaunch, NTrace, NImpl, FImpl)

namespace NCsProjectileWeapon_LaunchTraceParams
{
	using ThisType = FCsProjectileWeapon_LaunchTraceParams;
	using ParamsType = NCsWeapon::NProjectile::NParams::NLaunch::NTrace::NImpl::FImpl;

	// Separate implementation to allow for clearer use of aliases
	struct CSWP_API FImpl
	{
	public:

		static ParamsType* AddSafeToSlice(const FString& Context, ThisType* This, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);
		static ParamsType* AddSafeToSliceAsValue(const FString& Context, const ThisType* This, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);
		static ParamsType* AddSafeToSlice_Internal(const FString& Context, const ThisType* This, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);
		static void CopyToParams(ThisType* This, ParamsType* Params);
		static void CopyToParamsAsValue(const ThisType* This, ParamsType* Params);
	};
}

// ParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NTrace::NImpl::FImpl)
CS_FWD_DECLARE_STRUCT_NAMESPACE_6(NCsWeapon, NProjectile, NParams, NLaunch, NTrace, NImpl, FImpl)

/**
* Describes any information related to Launching a Projectile using a Trace from a Projectile Weapon.
* The trace may determine the Location and/or Direction with which to Launch the Projectile.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeapon_LaunchTraceParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes any Location information related to Launching a Projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	FCsProjectileWeapon_Launch_LocationParams LocationParams;

	/** Describes any Direction information related to Launching a Projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	FCsProjectileWeapon_Launch_DirectionParams DirectionParams;

	/** Describes any Trace information related to Launching a Projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	FCsProjectileWeapon_Launch_TraceParams TraceParams;

	FCsProjectileWeapon_LaunchTraceParams() :
		LocationParams(),
		DirectionParams(),
		TraceParams()
	{
	}

	using ParamsType = NCsWeapon::NProjectile::NParams::NLaunch::NTrace::NImpl::FImpl;
	using _Impl = NCsProjectileWeapon_LaunchTraceParams::FImpl;

	ParamsType* AddSafeToSlice(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning)				{ return _Impl::AddSafeToSlice(Context, this, WorldContext, Name, Log); }
	ParamsType* AddSafeToSliceAsValue(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const	{ return _Impl::AddSafeToSliceAsValue(Context, this, WorldContext, Name, Log); }
private:
	ParamsType* AddSafeToSlice_Internal(const FString& Context, const UObject* WorldContext, const FName& Name, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const { return _Impl::AddSafeToSlice_Internal(Context, this, WorldContext, Name, Log); }
public:
	FORCEINLINE void CopyToParams(ParamsType* Params)				{ _Impl::CopyToParams(this, Params); }
	FORCEINLINE void CopyToParamsAsValue(ParamsType* Params) const	{ _Impl::CopyToParamsAsValue(this, Params); }

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

#pragma endregion FCsProjectileWeapon_LaunchTraceParams

// FCsProjectileWeapon_Launch_WithTraceParams
#pragma region

struct FCsProjectileWeapon_Launch_WithTraceParams;

// ParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NWithTrace::FParams)
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NProjectile, NParams, NLaunch, NWithTrace, FParams)

namespace NCsProjectileWeapon_Launch_WithTraceParams
{
	using ThisType = FCsProjectileWeapon_Launch_WithTraceParams;
	using ParamsType = NCsWeapon::NProjectile::NParams::NLaunch::NWithTrace::FParams;

	// Separate implementation to allow for clearer use of aliases
	struct CSWP_API FImpl
	{
	public:

		static void CopyToParams(ThisType* This, ParamsType* Params);
		static void CopyToParamsAsValue(const ThisType* This, ParamsType* Params);
	};
}

// ParamsType (NCsWeapon::NProjectile::NParams::NLaunch::NWithTrace::FParams)
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NProjectile, NParams, NLaunch, NWithTrace, FParams)

/**
* Describes any information related to Launching a Projectile from a Projectile Weapon.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeapon_Launch_WithTraceParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes any Location information related to Launching a Projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	FCsProjectileWeapon_Launch_LocationParams LocationParams;

	/** Describes any Direction information related to Launching a Projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	FCsProjectileWeapon_Launch_DirectionParams DirectionParams;

	/** Describes any Trace information related to Launching a Projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Projectile")
	FCsProjectileWeapon_Launch_TraceParams TraceParams;

	FCsProjectileWeapon_Launch_WithTraceParams() :
		LocationParams(),
		DirectionParams(),
		TraceParams()
	{
	}

	using ParamsType = NCsWeapon::NProjectile::NParams::NLaunch::NWithTrace::FParams;
	using _Impl = NCsProjectileWeapon_Launch_WithTraceParams::FImpl;

	FORCEINLINE void CopyToParams(ParamsType* Params)				{ _Impl::CopyToParams(this, Params); }
	FORCEINLINE void CopyToParamsAsValue(ParamsType* Params) const	{ _Impl::CopyToParamsAsValue(this, Params); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

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
					/**
					* Describes any information related to Launching a Projectile from a Projectile Weapon.
					*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
					*  Projectile is an object that implements the interface: ICsProjectile.
					*/
					struct CSWP_API FParams
					{
						using LocationParamsType = NCsWeapon::NProjectile::NParams::NLaunch::NLocation::FParams;
						using DirectionParamsType = NCsWeapon::NProjectile::NParams::NLaunch::NDirection::FParams;
						using TraceParamsType = NCsWeapon::NProjectile::NParams::NLaunch::NTrace::FParams;

					private:

						/** Describes any Location information related to Launching a Projectile. */
						LocationParamsType LocationParams;
						/** Describes any Direction information related to Launching a Projectile. */
						DirectionParamsType DirectionParams;
						/** Describes any Trace information related to Launching a Projectile. */
						TraceParamsType TraceParams;

					public:

						FParams() :
							LocationParams(),
							DirectionParams(),
							TraceParams()
						{
						}

						FORCEINLINE const LocationParamsType& GetLocationParams() const { return LocationParams; }
						FORCEINLINE LocationParamsType* GetLocationParamsPtr() { return &LocationParams; }
						FORCEINLINE const DirectionParamsType& GetDirectionParams() const { return DirectionParams; }
						FORCEINLINE DirectionParamsType* GetDirectionParamsPtr() { return &DirectionParams; }
						FORCEINLINE const TraceParamsType& GetTraceParams() const { return TraceParams; }
						FORCEINLINE TraceParamsType* GetTraceParamsPtr() { return &TraceParams; }
					
						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
					};
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Launch_WithTraceParams