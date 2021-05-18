// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_ProjectileImplSlice.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Data
#include "Data/CsData_ProjectileEmuSlice.h"

#define SliceType NCsProjectile::NData::FImplSlice

void FCsData_ProjectileImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetLifeTime(&LifeTime);
	Slice->SetInitialSpeed(&InitialSpeed);
	Slice->SetMaxSpeed(&MaxSpeed);
	Slice->SetGravityScale(&GravityScale);
}

void FCsData_ProjectileImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetLifeTime(LifeTime);
	Slice->SetInitialSpeed(InitialSpeed);
	Slice->SetMaxSpeed(MaxSpeed);
	Slice->SetGravityScale(GravityScale);
}

#undef SliceType

bool FCsData_ProjectileImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
{
	CS_IS_FLOAT_GREATER_THAN(LifeTime, 0.0f)

	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(InitialSpeed, 0.0f)

	CS_IS_INT_GREATER_THAN(MaxSpeed, 0.0f)

	CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(GravityScale, 0.0f)

	return true;
}