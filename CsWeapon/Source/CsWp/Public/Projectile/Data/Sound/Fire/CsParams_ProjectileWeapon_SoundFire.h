// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "CsMacro_Proxy.h"
#include "Projectile/Data/Sound/Fire/CsTypes_ProjectileWeapon_SoundFire.h"
// Log
#include "Utility/CsWpLog.h"

#include "CsParams_ProjectileWeapon_SoundFire.generated.h"

// FCsProjectileWeapon_Fire_Sound_StartParams
#pragma region

struct FCsProjectileWeapon_Fire_Sound_StartParams;

// ParamsType (NCsWeapon::NProjectile::NFire::NSound::NStart::FParams)
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NProjectile, NFire, NSound, NStart, FParams)

namespace NCsProjectileWeapon_Fire_Sound_StartParams
{
	using ThisType = FCsProjectileWeapon_Fire_Sound_StartParams;
	using ParamsType = NCsWeapon::NProjectile::NFire::NSound::NStart::FParams;

	// Separate implementation to allow for clearer use of aliases
	struct CSWP_API FImpl
	{
	public:

		static void CopyToParams(ThisType* This, ParamsType* Params);
		static void CopyToParamsAsValue(const ThisType* This, ParamsType* Params);
	};
}

// ParamsType (NCsWeapon::NProjectile::NFire::NSound::NStart::FParams)
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NProjectile, NFire, NSound, NStart, FParams)

/**
* Describes any Sound information related to the Start of the Fire action for a Projectile Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeapon_Fire_Sound_StartParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Which Sound to play when the Fire action is executed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	FCsSound Sound;

	/** How the Sound should be attached. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	ECsProjectileWeaponFireSoundAttach Attach;

	FCsProjectileWeapon_Fire_Sound_StartParams() :
		Sound(),
		Attach(ECsProjectileWeaponFireSoundAttach::Component)
	{
	}

	using ParamsType = NCsWeapon::NProjectile::NFire::NSound::NStart::FParams;
	using _Impl = NCsProjectileWeapon_Fire_Sound_StartParams::FImpl;

	FORCEINLINE void CopyToParams(ParamsType* Params)				{ _Impl::CopyToParams(this, Params); }
	FORCEINLINE void CopyToParamsAsValue(ParamsType* Params) const	{ _Impl::CopyToParamsAsValue(this, Params); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NFire
		{
			namespace NSound
			{
				namespace NStart
				{
					/**
					* Describes any Sound information related to the Start of the Fire action for a Projectile Weapon.
					*  Weapon is an object that implements the interface: ICsWeapon.
					*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
					*/
					struct CSWP_API FParams
					{
					private:

						using AttachType = NCsWeapon::NProjectile::NFire::NSound::EAttach;

					private:

						/** Which Sound to play when the Fire action is executed. */
						CS_DECLARE_MEMBER_WITH_PROXY(Sound, FCsSound)
						/** How the Sound should be attached. */
						CS_DECLARE_MEMBER_WITH_PROXY(Attach, AttachType)

					public:

						FParams() :
							CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Sound),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Attach, AttachType::Component)
						{
							CS_CTOR_SET_MEMBER_PROXY(Sound);
							CS_CTOR_SET_MEMBER_PROXY(Attach);
						}

						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Sound, FCsSound)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Attach, AttachType)

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
					};
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Fire_Sound_StartParams

// FCsProjectileWeapon_Fire_Sound_ShotParams
#pragma region

struct FCsProjectileWeapon_Fire_Sound_ShotParams;

// ParamsType (NCsWeapon::NProjectile::NFire::NSound::NShot::FParams)
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NProjectile, NFire, NSound, NShot, FParams)

namespace NCsProjectileWeapon_Fire_Sound_ShotParams
{
	using ThisType = FCsProjectileWeapon_Fire_Sound_ShotParams;
	using ParamsType = NCsWeapon::NProjectile::NFire::NSound::NShot::FParams;

	// Separate implementation to allow for clearer use of aliases
	struct CSWP_API FImpl
	{
	public:

		static void CopyToParams(ThisType* This, ParamsType* Params);
		static void CopyToParamsAsValue(const ThisType* This, ParamsType* Params);
	};
}

// ParamsType (NCsWeapon::NProjectile::NFire::NSound::NShot::FParams)
CS_FWD_DECLARE_STRUCT_NAMESPACE_5(NCsWeapon, NProjectile, NFire, NSound, NShot, FParams)

/**
* Describes any Sound information related to the Shots of the Fire action for a Projectile Weapon.
*  Weapon is an object that implements the interface: ICsWeapon.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeapon_Fire_Sound_ShotParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Whether to skip playing a sound for the FIRST Shot from a Fire action. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	bool bSkipFirst;

	/** Which Sound to play when the Fire action is executed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	FCsSound Sound;

	/** How the Sound should be attached. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile")
	ECsProjectileWeaponFireSoundAttach Attach;

	FCsProjectileWeapon_Fire_Sound_ShotParams() :
		bSkipFirst(true),
		Sound(),
		Attach(ECsProjectileWeaponFireSoundAttach::Component)
	{
	}

	using ParamsType = NCsWeapon::NProjectile::NFire::NSound::NShot::FParams;
	using _Impl = NCsProjectileWeapon_Fire_Sound_ShotParams::FImpl;

	FORCEINLINE void CopyToParams(ParamsType* Params)				{ _Impl::CopyToParams(this, Params); }
	FORCEINLINE void CopyToParamsAsValue(ParamsType* Params) const	{ _Impl::CopyToParamsAsValue(this, Params); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NFire
		{
			namespace NSound
			{
				namespace NShot
				{
					/**
					* Describes any Sound information related to the Shots of the Fire action for a Projectile Weapon.
					*  Weapon is an object that implements the interface: ICsWeapon.
					*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
					*/
					struct CSWP_API FParams
					{
					private:

						using AttachType = NCsWeapon::NProjectile::NFire::NSound::EAttach;

					private:

						/** Whether to skip playing a sound for the FIRST Shot from a Fire action. */
						CS_DECLARE_MEMBER_WITH_PROXY(bSkipFirst, bool)
						/** Which Sound to play when the Fire action is executed. */
						CS_DECLARE_MEMBER_WITH_PROXY(Sound, FCsSound)
						/** How the Sound should be attached. */
						CS_DECLARE_MEMBER_WITH_PROXY(Attach, AttachType)

					public:

						FParams() :
							CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(bSkipFirst),
							CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(Sound),
							CS_CTOR_INIT_MEMBER_WITH_PROXY(Attach, AttachType::Component)
						{
							CS_CTOR_SET_MEMBER_PROXY(bSkipFirst);
							CS_CTOR_SET_MEMBER_PROXY(Sound);
							CS_CTOR_SET_MEMBER_PROXY(Attach);
						}

						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bSkipFirst, bool)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Sound, FCsSound)
						CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Attach, AttachType)

						bool IsValidChecked(const FString& Context) const;
						bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
					};
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Fire_Sound_ShotParams

// FCsProjectileWeapon_Fire_SoundParams
#pragma region

struct FCsProjectileWeapon_Fire_SoundParams;

// ParamsType (NCsWeapon::NProjectile::NFire::NSound::FParams)
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NProjectile, NFire, NSound, FParams)

namespace NCsProjectileWeapon_Fire_SoundParams
{
	using ThisType = FCsProjectileWeapon_Fire_SoundParams;
	using ParamsType = NCsWeapon::NProjectile::NFire::NSound::FParams;

	// Separate implementation to allow for clearer use of aliases
	struct CSWP_API FImpl
	{
	public:

		static void CopyToParams(ThisType* This, ParamsType* Params);
		static void CopyToParamsAsValue(const ThisType* This, ParamsType* Params);
	};
}

// ParamsType (NCsWeapon::NProjectile::NFire::NSound::FParams)
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NProjectile, NFire, NSound, FParams)

/**
* Describes any Sound information related to the Fire action for a Projectile Weapon.
*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
*/
USTRUCT(BlueprintType)
struct CSWP_API FCsProjectileWeapon_Fire_SoundParams
{
	GENERATED_USTRUCT_BODY()

public:

	/** Whether to use StartParams or not. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (ScriptName = "m_bStartParams", InlineEditConditionToggle))
	bool bStartParams;

	/** Describes any Sound information related to the Start of the Fire action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (ScriptName = "m_StartParams", EditCondition = "bStartParams"))
	FCsProjectileWeapon_Fire_Sound_StartParams StartParams;

	/** Whether to use ShotParams or not. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (ScriptName = "m_bShotParams", InlineEditConditionToggle))
	bool bShotParams;

	/** Describes any Sound information related to the Shots of the Fire action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsWp|Weapon|Projectile", meta = (ScriptName = "m_ShotParams", EditCondition = "bShotParams"))
	FCsProjectileWeapon_Fire_Sound_ShotParams ShotParams;

	FCsProjectileWeapon_Fire_SoundParams() :
		bStartParams(false),
		StartParams(),
		bShotParams(false),
		ShotParams()
	{
	}

	using ParamsType = NCsWeapon::NProjectile::NFire::NSound::FParams;
	using _Impl = NCsProjectileWeapon_Fire_SoundParams::FImpl;

	FORCEINLINE void CopyToParams(ParamsType* Params)				{ _Impl::CopyToParams(this, Params); }
	FORCEINLINE void CopyToParamsAsValue(ParamsType* Params) const	{ _Impl::CopyToParamsAsValue(this, Params); }

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning) const;
};

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NFire
		{
			namespace NSound
			{
				/**
				* Describes any Sound information related to the Fire action for a Projectile Weapon.
				*  Projectile Weapon is an object that implements the interface: ICsProjectileWeapon.
				*/
				struct CSWP_API FParams
				{
				private:

					using StartParamsType = NCsWeapon::NProjectile::NFire::NSound::NStart::FParams;
					using ShotParamsType = NCsWeapon::NProjectile::NFire::NSound::NShot::FParams;

				private:
	
					/** Whether to use StartParams or not. */
					CS_DECLARE_MEMBER_WITH_PROXY(bStartParams, bool)
					/** Describes any Sound information related to the Start of the Fire action */
					StartParamsType StartParams;
					/** Whether to use ShotParams or not. */
					CS_DECLARE_MEMBER_WITH_PROXY(bShotParams, bool)
					/** Describes any Sound information related to the Shots of the Fire action */
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

#pragma endregion FCsProjectileWeapon_Fire_SoundParams