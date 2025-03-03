// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/Sound/Fire/CsParams_ProjectileWeapon_SoundFire.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsParams_ProjectileWeapon_SoundFire)

// FCsProjectileWeapon_Fire_Sound_StartParams
#pragma region

namespace NCsProjectileWeapon_Fire_Sound_StartParams
{
	using AttachType = NCsWeapon::NProjectile::NFire::NSound::EAttach;

	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY(Params, Sound);
		CS_THIS_COPY_TYPE_TO_PROXY(Params, Attach, AttachType);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Sound);
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, Attach, AttachType);
	}
}

bool FCsProjectileWeapon_Fire_Sound_StartParams::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Sound);
	CS_IS_ENUM_VALID_CHECKED(EMCsProjectileWeaponFireSoundAttach, Attach)
	return true;
}

bool FCsProjectileWeapon_Fire_Sound_StartParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_VALID(Sound)	
	CS_IS_ENUM_VALID(EMCsProjectileWeaponFireSoundAttach, ECsProjectileWeaponFireSoundAttach, Attach)
	return true;
}

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
					using AttachMapType = NCsWeapon::NProjectile::NFire::NSound::EMAttach;

					bool FParams::IsValidChecked(const FString& Context) const
					{
						CS_IS_VALID_CHECKED(GetSound());
						CS_IS_ENUM_VALID_CHECKED(AttachMapType, GetAttach())
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						CS_IS_VALID(GetSound())
						CS_IS_ENUM_VALID(AttachMapType, AttachType, GetAttach())
						return true;
					}
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Fire_Sound_StartParams

// FCsProjectileWeapon_Fire_Sound_ShotParams
#pragma region

namespace NCsProjectileWeapon_Fire_Sound_ShotParams
{
	using AttachType = NCsWeapon::NProjectile::NFire::NSound::EAttach;

	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY(Params, bSkipFirst);
		CS_THIS_COPY_TO_PROXY(Params, Sound);
		CS_THIS_COPY_TYPE_TO_PROXY(Params, Attach, AttachType);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bSkipFirst);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, Sound);
		CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(Params, Attach, AttachType);
	}
}

bool FCsProjectileWeapon_Fire_Sound_ShotParams::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Sound);
	CS_IS_ENUM_VALID_CHECKED(EMCsProjectileWeaponFireSoundAttach, Attach)
	return true;
}

bool FCsProjectileWeapon_Fire_Sound_ShotParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	CS_IS_VALID(Sound)
	CS_IS_ENUM_VALID(EMCsProjectileWeaponFireSoundAttach, ECsProjectileWeaponFireSoundAttach, Attach)
	return true;
}

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
					using AttachMapType = NCsWeapon::NProjectile::NFire::NSound::EMAttach;

					bool FParams::IsValidChecked(const FString& Context) const
					{
						CS_IS_VALID_CHECKED(GetSound());
						CS_IS_ENUM_VALID_CHECKED(AttachMapType, GetAttach())
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						CS_IS_VALID(GetSound())
						CS_IS_ENUM_VALID(AttachMapType, AttachType, GetAttach())
						return true;
					}
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Fire_Start_SoundParams

// FCsProjectileWeapon_Fire_SoundParams
#pragma region

namespace NCsProjectileWeapon_Fire_SoundParams
{
	void FImpl::CopyToParams(ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY(Params, bStartParams);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR(Params, StartParams);
		CS_THIS_COPY_TO_PROXY(Params, bShotParams);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR(Params, ShotParams);
	}

	void FImpl::CopyToParamsAsValue(const ThisType* This, ParamsType* Params)
	{
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bStartParams);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR_AS_VALUE(Params, StartParams);
		CS_THIS_COPY_TO_PROXY_AS_VALUE(Params, bShotParams);
		CS_THIS_COPY_PARAMS_TO_PROXY_PTR_AS_VALUE(Params, ShotParams);
	}
}

bool FCsProjectileWeapon_Fire_SoundParams::IsValidChecked(const FString& Context) const
{
	if (bStartParams)
	{
		CS_IS_VALID_CHECKED(StartParams);
	}

	if (bShotParams)
	{
		CS_IS_VALID_CHECKED(ShotParams);
	}
	return true;
}

bool FCsProjectileWeapon_Fire_SoundParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	if (bStartParams)
	{
		CS_IS_VALID(StartParams)
	}
	
	if (bShotParams)
	{
		CS_IS_VALID(ShotParams)
	}
	return true;
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NFire
		{
			namespace NSound
			{
				bool FParams::IsValidChecked(const FString& Context) const
				{
					if (GetbStartParams())
					{
						CS_IS_VALID_CHECKED(GetStartParams());
					}

					if (GetbShotParams())
					{
						CS_IS_VALID_CHECKED(GetShotParams());
					}
					return true;
				}

				bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
				{
					if (GetbStartParams())
					{
						CS_IS_VALID(GetStartParams())
					}

					if (GetbShotParams())
					{
						CS_IS_VALID(GetShotParams())
					}
					return true;
				}
			}
		}
	}
}

#pragma endregion FCsProjectileWeapon_Fire_SoundParams