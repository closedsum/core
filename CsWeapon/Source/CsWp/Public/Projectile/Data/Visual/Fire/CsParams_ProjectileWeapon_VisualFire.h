// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Proxy.h"
#include "Managers/FX/CsTypes_FX.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsParams_ProjectileWeapon_VisualFire.generated.h"

// ProjectileWeaponFireVisualAttach
#pragma region

/**
* Describes how the Visual Fire FX should be attached to the Weapon.
*  Weapon is an object that implements the interface: ICsWeapon
*/
UENUM(BlueprintType)
enum class ECsProjectileWeaponFireVisualAttach : uint8
{
	None									UMETA(DisplayName = "None"),
	Owner									UMETA(DisplayName = "Owner"),
	Component								UMETA(DisplayName = "Component"),
	Custom									UMETA(DisplayName = "Custom"),
	ECsProjectileWeaponFireVisualAttach_MAX	UMETA(Hidden),
};

struct CSWP_API EMCsProjectileWeaponFireVisualAttach : public TCsEnumMap<ECsProjectileWeaponFireVisualAttach>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsProjectileWeaponFireVisualAttach, ECsProjectileWeaponFireVisualAttach)
};

namespace NCsProjectileWeaponFireVisualAttach
{
	typedef ECsProjectileWeaponFireVisualAttach Type;

	namespace Ref
	{
		extern CSWP_API const Type None;
		extern CSWP_API const Type Owner;
		extern CSWP_API const Type Component;
		extern CSWP_API const Type ECsProjectileWeaponFireVisualAttach_MAX;
	}

	extern CSWP_API const uint8 MAX;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NFire
		{
			namespace NVisual
			{
				/**
				* Describes how the Visual Fire FX should be attached to the weapon.
				*/
				enum class EAttach : uint8
				{
					None,
					Owner,
					Component,
					Custom,
					EAttach_MAX
				};

				struct CSWP_API EMAttach : public TCsEnumMap<EAttach>
				{
					CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMAttach, EAttach)
				};

				namespace NAttach
				{
					namespace Ref
					{
						typedef EAttach Type;

						extern CSWP_API const Type None;
						extern CSWP_API const Type Owner;
						extern CSWP_API const Type Component;
						extern CSWP_API const Type Custom;
						extern CSWP_API const Type EAttach_MAX;
					}
				}
			}
		}
	}
}

#pragma endregion ProjectileWeaponFireVisualAttach

// FCsProjectileWeapon_Fire_Visual_StartParams
#pragma region

// NCsWeapon::NProjectile::NFire::NVisual::NStart::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NProjectile, NFire, NVisual, NStart, FParams)

/**
* Describes any Visual information related to the Start of the Fire action for a Projectile Weapon.
*  Weapon is an object that implements the interface: ICsWeapon
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeapon_Fire_Visual_StartParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Which FX to spawn when the Fire action is executed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	FCsFX FX;

	/** How the FX should be attached. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	ECsProjectileWeaponFireVisualAttach Attach;

	FCsProjectileWeapon_Fire_Visual_StartParams() :
		FX(),
		Attach(ECsProjectileWeaponFireVisualAttach::Component)
	{
	}

#define ParamsType NCsWeapon::NProjectile::NFire::NVisual::NStart::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType
	
	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NFire
		{
			namespace NVisual
			{
				namespace NStart
				{
					/**
					* Describes any Visual information related to the Start of the Fire action for a Projectile Weapon.
					*  Weapon is an object that implements the interface: ICsWeapon
					*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
					*/
					struct CSWP_API FParams
					{
					private:

						using AttachType = NCsWeapon::NProjectile::NFire::NVisual::EAttach;

					private:

						/** Which FX to spawn when the Fire action is executed. */
						CS_DECLARE_MEMBER_WITH_PROXY(FX, FCsFX)
						/** How the FX should be attached. */
						CS_DECLARE_MEMBER_WITH_PROXY(Attach, AttachType)

					public:

						FParams() :
							CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(FX),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Attach, AttachType::None)
						{
							CS_CTOR_SET_MEMBER_PROXY(FX);
							CS_CTOR_SET_MEMBER_PROXY(Attach);
						}

					public:
						
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(FX, FCsFX)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Attach, AttachType)
						
						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
					};
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Fire_Visual_StartParams

// FCsProjectileWeapon_Fire_Visual_ShotParams
#pragma region

// NCsWeapon::NProjectile::NFire::NVisual::NShot::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NProjectile, NFire, NVisual, NShot, FParams)

/**
* Describes any Visual information related to the Shots of the Fire action for a Projectile Weapon.
*  Weapon is an object that implements the interface: ICsWeapon
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeapon_Fire_Visual_ShotParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Whether to skip playing a sound for the FIRST Shot from a Fire action. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	bool bSkipFirst;

	/** Which FX to spawn when the Fire action is executed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	FCsFX FX;

	/** How the FX should be attached. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	ECsProjectileWeaponFireVisualAttach Attach;

	FCsProjectileWeapon_Fire_Visual_ShotParams() :
		bSkipFirst(true),
		FX(),
		Attach(ECsProjectileWeaponFireVisualAttach::Component)
	{
	}

#define ParamsType NCsWeapon::NProjectile::NFire::NVisual::NShot::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType
	
	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NFire
		{
			namespace NVisual
			{
				namespace NShot
				{
					/**
					* Describes any Visual information related to the Start of the Fire action for a Projectile Weapon.
					*  Weapon is an object that implements the interface: ICsWeapon
					*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
					*/
					struct CSWP_API FParams
					{
					private:

						using AttachType = NCsWeapon::NProjectile::NFire::NVisual::EAttach;

					private:

						/** Whether to skip playing a sound for the FIRST Shot from a Fire action. */
						CS_DECLARE_MEMBER_WITH_PROXY(bSkipFirst, bool)
						/** Which FX to spawn when the Fire action is executed. */
						CS_DECLARE_MEMBER_WITH_PROXY(FX, FCsFX)
						/** How the FX should be attached. */
						CS_DECLARE_MEMBER_WITH_PROXY(Attach, AttachType)

					public:

						FParams() :
							CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(bSkipFirst),
							CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(FX),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Attach, AttachType::None)
						{
							CS_CTOR_SET_MEMBER_PROXY(bSkipFirst);
							CS_CTOR_SET_MEMBER_PROXY(FX);
							CS_CTOR_SET_MEMBER_PROXY(Attach);
						}

					public:
						
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bSkipFirst, bool)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(FX, FCsFX)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Attach, AttachType)
						
						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
					};
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Fire_Visual_ShotParams

// FCsProjectileWeapon_Fire_VisualParams
#pragma region

// NCsWeapon::NProjectile::NFire::NVisual::FParams
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NProjectile, NFire, NVisual, FParams)

/**
* Describes any Visual information related to the Fire action for a Projectile Weapon.
*  Weapon is an object that implements the interface: ICsWeapon
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeapon_Fire_VisualParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Whether to use StartParams or not. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (ScriptName = "m_bStartParams", InlineEditConditionToggle))
	bool bStartParams;

	/** Describes any Visual information related to the Start of the Fire action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (ScriptName = "m_StartParams", EditCondition = "bStartParams"))
	FCsProjectileWeapon_Fire_Visual_StartParams StartParams;

	/** Whether to use ShotParams or not. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (ScriptName = "m_bShotParams", InlineEditConditionToggle))
	bool bShotParams;

	/** Describes any Visual information related to the Shots of the Fire action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (ScriptName = "m_ShotParams", EditCondition = "bShotParams"))
	FCsProjectileWeapon_Fire_Visual_ShotParams ShotParams;

	FCsProjectileWeapon_Fire_VisualParams() :
		bStartParams(false),
		StartParams(),
		bShotParams(false),
		ShotParams()
	{
	}

#define ParamsType NCsWeapon::NProjectile::NFire::NVisual::FParams
	void CopyToParams(ParamsType* Params);
	void CopyToParamsAsValue(ParamsType* Params) const;
#undef ParamsType
	
	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NFire
		{
			namespace NVisual
			{
				/**
				* Describes any Visual information related to the Fire action for a Projectile Weapon.
				*  Weapon is an object that implements the interface: ICsWeapon
				*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
				*/
				struct CSWP_API FParams
				{
				private:

					using StartParamsType = NCsWeapon::NProjectile::NFire::NVisual::NStart::FParams;
					using ShotParamsType = NCsWeapon::NProjectile::NFire::NVisual::NShot::FParams;

				private:
	
					/** Whether to use StartParams or not. */
					CS_DECLARE_MEMBER_WITH_PROXY(bStartParams, bool)
					/** Describes any FX information related to the Start of the Fire action */
					StartParamsType StartParams;
					/** Whether to use ShotParams or not. */
					CS_DECLARE_MEMBER_WITH_PROXY(bShotParams, bool)
					/** Describes any FX information related to the Shots of the Fire action */
					ShotParamsType ShotParams;

				public:

					FParams() :
						CS_CTOR_INIT_MEMBER_WITH_PROXY(bStartParams, false),
						StartParams(),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(bShotParams, false),
						ShotParams()
					{
						CS_CTOR_SET_MEMBER_PROXY(bStartParams);
						CS_CTOR_SET_MEMBER_PROXY(bShotParams);
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bStartParams, bool)
					FORCEINLINE const StartParamsType& GetStartParams() const { return StartParams; }
					FORCEINLINE StartParamsType* GetStartParamsPtr() { return &StartParams; }
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bShotParams, bool)
					FORCEINLINE const ShotParamsType& GetShotParams() const { return ShotParams; }
					FORCEINLINE ShotParamsType* GetShotParamsPtr() { return &ShotParams; }

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
				};
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Fire_VisualParams