// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Settings/CsProjectileSettings.h"
#include "CsPrj.h"

#include "Managers/Projectile/CsProjectile.h"

UCsProjectileSettings::UCsProjectileSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

#if WITH_EDITOR

void UCsProjectileSettings::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	/*
	if (PropertyName == GET_MEMBER_NAME_CHECKED(UCsProjectileSettings, ProjectileDataEmulatedInterfaces))
	{
		UClass* Class = UCsProjectile::StaticClass();
		FSoftClassPath ClassPath(Class);

		UClass* Class2 = FindObject<UClass>(nullptr, *(ClassPath.ToString()));

		if (Class)
		{
			UE_LOG(LogCsPrj, Warning, TEXT("Class"));
		}
	}
	*/

	Super::PostEditChangeProperty(e);
}

#endif // #if WITH_EDITOR