// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Settings/CsWeaponSettings.h"
#include "CsWp.h"

UCsWeaponSettings::UCsWeaponSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

#if WITH_EDITOR

void UCsWeaponSettings::PostEditChangeProperty(FPropertyChangedEvent& e)
{
	FName PropertyName = (e.Property != NULL) ? e.Property->GetFName() : NAME_None;

	Super::PostEditChangeProperty(e);
}

#endif // #if WITH_EDITOR