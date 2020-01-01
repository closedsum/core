// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Math.h"
#include "CsCore.h"

UCsLibrary_Math::UCsLibrary_Math(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

float UCsLibrary_Math::BytesToKilobytes(const int32& Bytes)
{
	return Bytes * FMath::Pow(10, -3);
}

float UCsLibrary_Math::BytesToMegabytes(const int32& Bytes)
{
	return Bytes * FMath::Pow(10, -6);
}

int32 UCsLibrary_Math::KilobytesToBytes(const float& Kilobytes)
{
	return Kilobytes * FMath::Pow(10, 3);
}