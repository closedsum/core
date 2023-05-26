// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/Sound/Fire/CsParams_ProjectileWeapon_SoundFire.h"

// Library
#include "Library/CsLibrary_Valid.h"

// FCsProjectileWeapon_Fire_Sound_StartParams
#pragma region

#define ParamsType NCsWeapon::NProjectile::NFire::NSound::NStart::FParams

void FCsProjectileWeapon_Fire_Sound_StartParams::CopyToParams(ParamsType* Params)
{
	Params->SetSound(&Sound);

	typedef NCsWeapon::NProjectile::NFire::NSound::EAttach AttachType;
	
	Params->SetAttachType((AttachType*)(&Attach));
}

void FCsProjectileWeapon_Fire_Sound_StartParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetSound(Sound);

	typedef NCsWeapon::NProjectile::NFire::NSound::EAttach AttachType;

	Params->SetAttachType((AttachType)(Attach));
}

#undef ParamsType

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
					bool FParams::IsValidChecked(const FString& Context) const
					{
						CS_IS_VALID_CHECKED(GetSound());

						typedef NCsWeapon::NProjectile::NFire::NSound::EMAttach _AttachMapType;

						CS_IS_ENUM_VALID_CHECKED(_AttachMapType, GetAttachType())
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						CS_IS_VALID(GetSound())

						typedef NCsWeapon::NProjectile::NFire::NSound::EMAttach _AttachMapType;
						typedef NCsWeapon::NProjectile::NFire::NSound::EAttach _AttachType;

						CS_IS_ENUM_VALID(_AttachMapType, _AttachType, GetAttachType())
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

#define ParamsType NCsWeapon::NProjectile::NFire::NSound::NShot::FParams

void FCsProjectileWeapon_Fire_Sound_ShotParams::CopyToParams(ParamsType* Params)
{
	Params->SetbSkipFirst(&bSkipFirst);
	Params->SetSound(&Sound);

	typedef NCsWeapon::NProjectile::NFire::NSound::EAttach AttachType;
	
	Params->SetAttachType((AttachType*)(&Attach));
}

void FCsProjectileWeapon_Fire_Sound_ShotParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetbSkipFirst(bSkipFirst);
	Params->SetSound(Sound);

	typedef NCsWeapon::NProjectile::NFire::NSound::EAttach AttachType;

	Params->SetAttachType((AttachType)(Attach));
}

#undef ParamsType

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
					bool FParams::IsValidChecked(const FString& Context) const
					{
						CS_IS_VALID_CHECKED(GetSound());

						typedef NCsWeapon::NProjectile::NFire::NSound::EMAttach _AttachMapType;

						CS_IS_ENUM_VALID_CHECKED(_AttachMapType, GetAttachType())
						return true;
					}

					bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						CS_IS_VALID(GetSound())

						typedef NCsWeapon::NProjectile::NFire::NSound::EMAttach _AttachMapType;
						typedef NCsWeapon::NProjectile::NFire::NSound::EAttach _AttachType;

						CS_IS_ENUM_VALID(_AttachMapType, _AttachType, GetAttachType())
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

#define ParamsType NCsWeapon::NProjectile::NFire::NSound::FParams

void FCsProjectileWeapon_Fire_SoundParams::CopyToParams(ParamsType* Params)
{
	Params->SetbStartParams(&bStartParams);
	StartParams.CopyToParams(Params->GetStartParamsPtr());
	Params->SetbShotParams(&bShotParams);
	ShotParams.CopyToParams(Params->GetShotParamsPtr());
}

void FCsProjectileWeapon_Fire_SoundParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetbStartParams(bStartParams);
	StartParams.CopyToParamsAsValue(Params->GetStartParamsPtr());
	Params->SetbShotParams(bShotParams);
	ShotParams.CopyToParamsAsValue(Params->GetShotParamsPtr());
}

#undef ParamsType

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