// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Projectile.h"
#include "Modifier/CsProjectileModifierImpl.h"
#include "Params/OnHit/Spawn/Projectile/CsTypes_Projectile_OnHit_SpawnProjectile_Spread.h"
// Log
#include "Utility/CsPrjLog.h"

#include "CsParams_Projectile_OnHit_SpawnProjectile.generated.h"

// ProjectileOnHitSpawnProjectileDirection
#pragma region

/**
* Describes the movement direction of a Projectile spawned from 
* a Projectile OnHit.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
UENUM(BlueprintType)
enum class ECsProjectileOnHitSpawnProjectileDirection : uint8
{
	/** The current movement direction of the parent Projectile. */
	Parent											UMETA(DisplayName = "Parent"),
	/** The inverse (multiply by -1.0f) of the current movement direction 
		of the parent Projectile. */
	ParentInverse									UMETA(DisplayName = "Parent Inverse"),
	/** The direction to the closest "Target". */
	ClosestTarget									UMETA(DisplayName = "Closest Target"),
	ECsProjectileOnHitSpawnProjectileDirection_MAX	UMETA(Hidden),
};

struct CSPRJ_API EMCsProjectileOnHitSpawnProjectileDirection : public TCsEnumMap<ECsProjectileOnHitSpawnProjectileDirection>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileOnHitSpawnProjectileDirection, ECsProjectileOnHitSpawnProjectileDirection)
};

namespace NCsProjectileOnHitSpawnProjectileDirection
{
	typedef ECsProjectileOnHitSpawnProjectileDirection Type;

	namespace Ref
	{
		extern CSPRJ_API const Type Parent;
		extern CSPRJ_API const Type ParentInverse;
		extern CSPRJ_API const Type ClosestTarget;
		extern CSPRJ_API const Type ECsProjectileOnHitSpawnProjectileDirection_MAX;
	}
}

namespace NCsProjectile
{
	namespace NOnHit
	{
		namespace NSpawn
		{
			namespace NProjectile
			{
				/**
				* Describes the movement direction of a Projectile spawned from
				* a Projectile OnHit.
				*  Projectile is an object that implements the interface: ICsProjectile.
				*/
				enum class EDirection : uint8
				{
					/** The current movement direction of the parent Projectile. */
					Parent,
					/** The inverse (multiply by -1.0f) of the current movement direction
						of the parent Projectile. */
					ParentInverse,
						/** The direction to the closest "Target". */
					ClosestTarget,
					EDirection_MAX
				};

				struct CSPRJ_API EMDirection : public TCsEnumMap<EDirection>
				{
					CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMDirection, EDirection)
				};

				namespace NDirection
				{
					namespace Ref
					{
						typedef EDirection Type;

						extern CSPRJ_API const Type Parent;
						extern CSPRJ_API const Type ParentInverse;
						extern CSPRJ_API const Type ClosestTarget;
						extern CSPRJ_API const Type EDirection_MAX;
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileOnHitSpawnProjectileDirection

// FCsProjectile_OnHit_SpawnProjectile_DirectionParams
#pragma region

// NCsProjectile::NOnHit::NSpawn::NProjectile::NDirection::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsProjectile, NOnHit, NSpawn, NProjectile, NDirection, FParams)

USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectile_OnHit_SpawnProjectile_DirectionParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes the movement direction of a Projectile spawned from a Projectile OnHit. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit")
	ECsProjectileOnHitSpawnProjectileDirection Type;

	/** NOTE: Only valid if Type == ECsProjectileOnHitSpawnProjectileDirection::ClosestTarget. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Radius;

	/** Whether to apply a Yaw (offset in degrees) to the movement direction of the Projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit", meta = (InlineEditConditionToggle))
	bool bYaw;

	/** The offset in degrees relative to the World Up vector to apply to the movement direction of the Projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit", meta = (editcondition = "bYaw", UIMin = "-90.0", ClampMin = "-90.0", UIMax = "90.0", ClampMax = "90.0"))
	float Yaw;

	/** Whether to apply a Pitch (offset in degrees) to the movement direction of the Projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit", meta = (InlineEditConditionToggle))
	bool bPitch;

	/** The offset in degrees relative to the Right vector with respect to the movement direction and
		World Up vector to apply to the movement direction of the Projectile. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit", meta = (editcondition = "bPitch", UIMin = "-90.0", ClampMin = "-90.0", UIMax = "90.0", ClampMax = "90.0"))
	float Pitch;

	FCsProjectile_OnHit_SpawnProjectile_DirectionParams() :
		Type(ECsProjectileOnHitSpawnProjectileDirection::Parent),
		Radius(0.0f),
		bYaw(false),
		Yaw(0.0f),
		bPitch(false),
		Pitch(0.0f)
	{
	}

#define ParamsType NCsProjectile::NOnHit::NSpawn::NProjectile::NDirection::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

namespace NCsProjectile
{
	namespace NOnHit
	{
		namespace NSpawn
		{
			namespace NProjectile
			{
				namespace NDirection
				{
					struct CSPRJ_API FParams
					{
					#define DirectionType NCsProjectile::NOnHit::NSpawn::NProjectile::EDirection

					private:

						CS_DECLARE_MEMBER_WITH_PROXY(Type, DirectionType)
						CS_DECLARE_MEMBER_WITH_PROXY(Radius, float)
						CS_DECLARE_MEMBER_WITH_PROXY(bYaw, bool)
						CS_DECLARE_MEMBER_WITH_PROXY(Yaw, float)
						CS_DECLARE_MEMBER_WITH_PROXY(bPitch, bool)
						CS_DECLARE_MEMBER_WITH_PROXY(Pitch, float)

					public:

						FParams() :
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Type, DirectionType::Parent),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Radius, 0.0f),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(bYaw, false),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Yaw, 0.0f),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(bPitch, false),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Pitch, 0.0f)
						{
							CS_CTOR_SET_MEMBER_PROXY(Type);
							CS_CTOR_SET_MEMBER_PROXY(Radius);
							CS_CTOR_SET_MEMBER_PROXY(bYaw);
							CS_CTOR_SET_MEMBER_PROXY(Yaw);
							CS_CTOR_SET_MEMBER_PROXY(bPitch);
							CS_CTOR_SET_MEMBER_PROXY(Pitch);
						}

						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Type, DirectionType)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Radius, float)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bYaw, bool)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Yaw, float)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bPitch, bool)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Pitch, float)

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

					#undef DirectionType
					};
				}
			}
		}
	}
}

#pragma endregion FCsProjectile_OnHit_SpawnProjectile_DirectionParams

// FCsProjectile_OnHit_SpawnProjectile_Spread_ShapeParams
#pragma region

// NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NShape::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_6(NCsProjectile, NOnHit, NSpawn, NProjectile, NSpread, NShape, FParams)

/**
* Describes any information related to Spread Shape for a Projectile spawn from
* another Projectile OnHit.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectile_OnHit_SpawnProjectile_Spread_ShapeParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Describes the Spread Shape. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit")
	ECsProjectileOnHitSpawnProjectileSpreadShape Shape;

	/** Describes the dimensions for the Shape.
		If Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Line: 
			Only Extents.X is used for the offset in Left and Right vectors from the
			movement direction of the parent Projectile
		if Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Rectangle:
			Only Extents.X and Extents.Y are used.
			Extents.X is the offset in Left and Right vectors from the
			movement direction of the parent Projectile .
			Extents.Y is the offset Up and Down from the World Up vector.
		if Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Circle:
			Only Extents.X and Extents.Y are used.
			Extents.X is the Inner Radius.
			Extents.Y is the Outer Radius.
			Only Extents.X and Extents.Y are used for the Radius around the
			movement direction of the parent Projectile.
			The Radius is represented by the Right vector with respect to the 
			movement direction of the parent Projectile and World Up vector.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit")
	FVector Extents;

	/** Describes the distribution of start locations within a Spread Shape. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit")
	ECsProjectileOnHitSpawnProjectileSpreadShapeDistribution Distribution;

	FCsProjectile_OnHit_SpawnProjectile_Spread_ShapeParams() :
		Shape(ECsProjectileOnHitSpawnProjectileSpreadShape::Line),
		Extents(0.0f),
		Distribution(ECsProjectileOnHitSpawnProjectileSpreadShapeDistribution::Random)
	{
	}

#define ParamsType NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NShape::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

namespace NCsProjectile
{
	namespace NOnHit
	{
		namespace NSpawn
		{
			namespace NProjectile
			{
				namespace NSpread
				{
					namespace NShape
					{
						/**
						* Describes any information related to Spread Shape for a Projectile spawn from
						* another Projectile OnHit.
						*  Projectile is an object that implements the interface: ICsProjectile.
						*/
						struct CSPRJ_API FParams
						{
						#define ShapeType NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::EShape
						#define DistributionType NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NShape::EDistribution

						private:

							/** Describes the Spread Shape. */
							CS_DECLARE_MEMBER_WITH_PROXY(Shape, ShapeType)
							/** Describes the dimensions for the Shape.
								If Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Line:
									Only Extents.X is used for the offset in Left and Right vectors from the
									movement direction of the parent Projectile
								if Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Rectangle:
									Only Extents.X and Extents.Y are used.
									Extents.X is the offset in Left and Right vectors from the
									movement direction of the parent Projectile .
									Extents.Y is the offset Up and Down from the World Up vector.
								if Shape == ECsProjectileOnHitSpawnProjectileSpreadShape::Circle:
									Only Extents.X and Extents.Y are used.
									Extents.X is the Inner Radius.
									Extents.Y is the Outer Radius.
									Only Extents.X and Extents.Y are used for the Radius around the
									movement direction of the parent Projectile.
									The Radius is represented by the Right vector with respect to the
									movement direction of the parent Projectile and World Up vector.
							*/
							CS_DECLARE_MEMBER_WITH_PROXY(Extents, FVector)
							/** Describes the distribution of start locations within a Spread Shape. */
							CS_DECLARE_MEMBER_WITH_PROXY(Distribution, DistributionType)

						public:

							FParams() :
								CS_CTOR_INIT_MEMBER_WITH_PROXY(Shape, ShapeType::Line),
								CS_CTOR_INIT_MEMBER_WITH_PROXY(Extents, 0.0f),
								CS_CTOR_INIT_MEMBER_WITH_PROXY(Distribution, DistributionType::Random)
							{
								CS_CTOR_SET_MEMBER_PROXY(Shape);
								CS_CTOR_SET_MEMBER_PROXY(Extents);
								CS_CTOR_SET_MEMBER_PROXY(Distribution);
							}

							CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Shape, ShapeType)
							CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Extents, FVector)
							CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Distribution, DistributionType)

							bool IsValidChecked(const FString& Context) const;
							bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

					
							FORCEINLINE bool ShouldPrecalculate() const { return NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NShape::NDistribution::ShouldPrecalculate(GetDistribution()); }
							/*
							FORCEINLINE void SetAnglesChecked(const FString& Context, const int32& Count, TArray<float>& OutAngles) const
							{
								NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::FLibrary::SetAnglesChecked(Context, Count, GetAngleType(), GetAngle(), GetDistribution(), OutAngles);
							}
							*/
							FORCEINLINE FVector GetRandomOffsetChecked(const FString& Context) const
							{
								return NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::FLibrary::GetRandomOffsetChecked(Context, GetShape(), GetExtents(), GetDistribution());
							}

						#undef ShapeType
						#undef DistributionType
						};
					}
				}
			}
		}
	}
}

#pragma endregion FCsProjectile_OnHit_SpawnProjectile_Spread_ShapeParams

// FCsProjectile_OnHit_SpawnProjectile_Spread_AngleParams
#pragma region

// NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NAngle::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_6(NCsProjectile, NOnHit, NSpawn, NProjectile, NSpread, NAngle, FParams)

USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectile_OnHit_SpawnProjectile_Spread_AngleParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit")
	ECsProjectileOnHitSpawnProjectileSpreadAngle AngleType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit", meta = (UIMin = "0.0", ClampMin = "0.0", UIMax = "180.0", ClampMax = "180.0"))
	float Angle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit")
	ECsProjectileOnHitSpawnProjectileSpreadAngleDistribution Distribution;

	FCsProjectile_OnHit_SpawnProjectile_Spread_AngleParams() :
		AngleType(ECsProjectileOnHitSpawnProjectileSpreadAngle::DivideByCount),
		Angle(0.0f),
		Distribution(ECsProjectileOnHitSpawnProjectileSpreadAngleDistribution::Shuffle)
	{
	}

#define ParamsType NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NAngle::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

namespace NCsProjectile
{
	namespace NOnHit
	{
		namespace NSpawn
		{
			namespace NProjectile
			{
				namespace NSpread
				{
					namespace NAngle
					{
						/**
						* Describes any information related to spread along an angle axis for a Projectile spawned
						* from another Projectile OnHit.
						*  Projectile is an object that implements the interface: ICsProjectile.
						*/
						struct CSPRJ_API FParams
						{
						#define SpreadAngleType NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::EAngle
						#define DistributionType NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NAngle::EDistribution

						private:

							CS_DECLARE_MEMBER_WITH_PROXY(AngleType, SpreadAngleType)
							CS_DECLARE_MEMBER_WITH_PROXY(Angle, float)
							CS_DECLARE_MEMBER_WITH_PROXY(Distribution, DistributionType)

						public:

							FParams() :
								CS_CTOR_INIT_MEMBER_WITH_PROXY(AngleType, SpreadAngleType::DivideByCount),
								CS_CTOR_INIT_MEMBER_WITH_PROXY(Angle, 0.0f),
								CS_CTOR_INIT_MEMBER_WITH_PROXY(Distribution, DistributionType::Shuffle)
							{
								CS_CTOR_SET_MEMBER_PROXY(AngleType);
								CS_CTOR_SET_MEMBER_PROXY(Angle);
								CS_CTOR_SET_MEMBER_PROXY(Distribution);
							}

							CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(AngleType, SpreadAngleType)
							CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Angle, float)
							CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Distribution, DistributionType)

							bool IsValidChecked(const FString& Context) const;
							bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

							FORCEINLINE bool ShouldPrecalculate() const { return NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NAngle::NDistribution::ShouldPrecalculate(GetDistribution()); }

							FORCEINLINE void SetAnglesChecked(const FString& Context, const int32& Count, TArray<float>& OutAngles) const
							{
								NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::FLibrary::SetAnglesChecked(Context, Count, GetAngleType(), GetAngle(), GetDistribution(), OutAngles);
							}

							FORCEINLINE float GetRandomAngleChecked(const FString& Context) const
							{
								return NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::FLibrary::GetRandomAngleChecked(Context, GetAngleType(), GetAngle(), GetDistribution());
							}

						#undef SpreadAngleType
						#undef DistributionType
						};
					}
				}
			}
		}
	}
}

#pragma endregion FCsProjectile_OnHit_SpawnProjectile_Spread_AngleParams

// FCsProjectile_OnHit_SpawnProjectile_SpreadParams
#pragma region

// NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsProjectile, NOnHit, NSpawn, NProjectile, NSpread, FParams)

USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectile_OnHit_SpawnProjectile_SpreadParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit", meta = (InlineEditConditionToggle))
	bool bShape;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit", meta = (editcondition = "bShape"))
	FCsProjectile_OnHit_SpawnProjectile_Spread_ShapeParams ShapeParams;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit", meta = (InlineEditConditionToggle))
	bool bYaw;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit", meta = (editcondition = "bYaw"))
	FCsProjectile_OnHit_SpawnProjectile_Spread_AngleParams YawParams;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit", meta = (InlineEditConditionToggle))
	bool bPitch;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit", meta = (editcondition = "bPitch"))
	FCsProjectile_OnHit_SpawnProjectile_Spread_AngleParams PitchParams;

	FCsProjectile_OnHit_SpawnProjectile_SpreadParams() :
		bShape(false),
		ShapeParams(),
		bYaw(true),
		YawParams(),
		bPitch(false),
		PitchParams()
	{
	}

#define ParamsType NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

namespace NCsProjectile
{
	namespace NOnHit
	{
		namespace NSpawn
		{
			namespace NProjectile
			{
				namespace NSpread
				{
					/**
					* Describes any information related to spread for a Projectile spawned from
					* another Projectile OnHit.
					*  Projectile is an object that implements the interface: ICsProjectile.
					*/
					struct CSPRJ_API FParams
					{
					#define ShapeParamsType NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NShape::FParams
					#define AngleParamsType NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::NAngle::FParams

					private:

						CS_DECLARE_MEMBER_WITH_PROXY(bShape, bool)
						CS_DECLARE_MEMBER_WITH_PROXY(bYaw, bool)
						CS_DECLARE_MEMBER_WITH_PROXY(bPitch, bool)

					public:

						ShapeParamsType ShapeParams;

						AngleParamsType YawParams;
						AngleParamsType PitchParams;

						FParams() :
							CS_CTOR_INIT_MEMBER_WITH_PROXY(bYaw, true),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(bPitch, false),
							YawParams(),
							PitchParams()
						{
							CS_CTOR_SET_MEMBER_PROXY(bYaw);
							CS_CTOR_SET_MEMBER_PROXY(bPitch);
						}

						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bShape, bool)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bYaw, bool)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bPitch, bool)
						FORCEINLINE const ShapeParamsType& GetShapeParams() const { return ShapeParams; }
						FORCEINLINE ShapeParamsType* GetShapeParamsPtr() { return &ShapeParams; }
						FORCEINLINE const AngleParamsType& GetYawParams() const { return YawParams; }
						FORCEINLINE AngleParamsType* GetYawParamsPtr() { return &YawParams; }
						FORCEINLINE const AngleParamsType& GetPitchParams() const { return PitchParams; }
						FORCEINLINE AngleParamsType* GetPitchParamsPtr() { return &PitchParams; }

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

					#undef ShapeParamsType
					#undef AngleParamsType
					};
				}
			}
		}
	}
}

#pragma endregion FCsProjectile_OnHit_SpawnProjectile_SpreadParams

// FCsProjectile_OnHit_SpawnProjectileParams
#pragma region

// NCsProjectile::NOnHit::NSpawn::FProjectile::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsProjectile, NOnHit, NSpawn, NProjectile, FParams)

/**
* Describing spawning Projectiles after a Projectile collides with another object.
*  Projectile is an object that implements the interface: ICsProjectile.
*/
USTRUCT(BlueprintType)
struct CSPRJ_API FCsProjectile_OnHit_SpawnProjectileParams
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit")
	FCsDataNoPropertyView_ECsProjectile Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit", meta = (UIMin = "1", ClampMin = "1"))
	int32 ProjectilesPerSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float TimeBetweenProjectilesPerSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit", meta = (InlineEditConditionToggle))
	bool bUntilGenerationCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit", meta = (editcondition = "bUntilGenerationCount", UIMin = "1", ClampMin = "1"))
	int32 GenerationCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit")
	FCsProjectile_OnHit_SpawnProjectile_DirectionParams DirectionParams;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit", meta = (InlineEditConditionToggle))
	bool bSpreadParams;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit", meta = (editcondition = "bSpreadParams"))
	FCsProjectile_OnHit_SpawnProjectile_SpreadParams SpreadParams;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit")
	bool bInheritModifiers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit")
	FCsProjectileModifier_CreateInfo CreateModifiers;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPrj|OnHit")
	FCsProjectileModifierInfo Modifiers;

	FCsProjectile_OnHit_SpawnProjectileParams() :
		Projectile(),
		ProjectilesPerSpawn(1),
		TimeBetweenProjectilesPerSpawn(0.0f),
		bUntilGenerationCount(false),
		GenerationCount(1),
		DirectionParams(),
		bSpreadParams(false),
		SpreadParams(),
		bInheritModifiers(false),
		CreateModifiers(),
		Modifiers()
	{
	}

#define ParamsType NCsProjectile::NOnHit::NSpawn::NProjectile::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;
};

namespace NCsProjectile
{
	namespace NOnHit
	{
		namespace NSpawn
		{
			namespace NProjectile
			{
				/**
				* Describing spawning Projectiles after a Projectile collides with another object.
				*  Projectile is an object that implements the interface: ICsProjectile.
				*/
				struct CSPRJ_API FParams
				{
				#define DirectionParamsType NCsProjectile::NOnHit::NSpawn::NProjectile::NDirection::FParams
				#define SpreadParamsType NCsProjectile::NOnHit::NSpawn::NProjectile::NSpread::FParams
				#define CreateModifierInfoType NCsProjectile::NModifier::NCreate::FInfo
				#define ModifierInfoType NCsProjectile::NModifier::FInfo

				private:

					CS_DECLARE_MEMBER_WITH_PROXY(Projectile, FECsProjectile)
					CS_DECLARE_MEMBER_WITH_PROXY(ProjectilesPerSpawn, int32)
					CS_DECLARE_MEMBER_WITH_PROXY(TimeBetweenProjectilesPerSpawn, float)
					CS_DECLARE_MEMBER_WITH_PROXY(bUntilGenerationCount, bool)
					CS_DECLARE_MEMBER_WITH_PROXY(GenerationCount, int32)

				public:

					DirectionParamsType DirectionParams;

				private:

					CS_DECLARE_MEMBER_WITH_PROXY(bSpreadParams, bool)

				public:

					SpreadParamsType SpreadParams;

				private:

					CS_DECLARE_MEMBER_WITH_PROXY(bInheritModifiers, bool)

				public:

					CreateModifierInfoType CreateModifiers;
				
					ModifierInfoType Modifiers;

				public:

					FParams() :
						CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Projectile),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(ProjectilesPerSpawn, 1),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(TimeBetweenProjectilesPerSpawn, 0.0f),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(bUntilGenerationCount, false),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(GenerationCount, 1),
						DirectionParams(),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(bSpreadParams, false),
						SpreadParams(),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(bInheritModifiers, false),
						CreateModifiers(),
						Modifiers()
					{
						CS_CTOR_SET_MEMBER_PROXY(Projectile);
						CS_CTOR_SET_MEMBER_PROXY(ProjectilesPerSpawn);
						CS_CTOR_SET_MEMBER_PROXY(TimeBetweenProjectilesPerSpawn);
						CS_CTOR_SET_MEMBER_PROXY(bUntilGenerationCount);
						CS_CTOR_SET_MEMBER_PROXY(GenerationCount);
						CS_CTOR_SET_MEMBER_PROXY(bSpreadParams);
						CS_CTOR_SET_MEMBER_PROXY(bInheritModifiers);
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Projectile, FECsProjectile)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(ProjectilesPerSpawn, int32)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(TimeBetweenProjectilesPerSpawn, float)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bUntilGenerationCount, bool)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(GenerationCount, int32)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bSpreadParams, bool)

					FORCEINLINE const DirectionParamsType& GetDirectionParams() const { return DirectionParams; }
					FORCEINLINE DirectionParamsType* GetDirectionParamsPtr() { return &DirectionParams; }
					FORCEINLINE const SpreadParamsType& GetSpreadParams() const { return SpreadParams; }
					FORCEINLINE SpreadParamsType* GetSpreadParamsPtr() { return &SpreadParams; }

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bInheritModifiers, bool)

					FORCEINLINE const CreateModifierInfoType* GetCreateModifiersPtr() const { return &CreateModifiers; }
					FORCEINLINE CreateModifierInfoType* GetCreateModifiersPtr() { return &CreateModifiers; }
					FORCEINLINE ModifierInfoType* GetModifiersPtr() { return &Modifiers; }

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

				#undef DirectionParamsType
				#undef SpreadParamsType
				#undef CreateModifierInfoType
				#undef ModifierInfoType
				};
			}
		}
	}
}

#pragma endregion FCsProjectile_OnHit_SpawnProjectileParams