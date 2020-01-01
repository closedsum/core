// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
#include "CsLibrary_Math.generated.h"

UCLASS()
class CSCORE_API UCsLibrary_Math : public UObject
{
	GENERATED_UCLASS_BODY()

	static float BytesToKilobytes(const int32& Bytes);

	static float BytesToMegabytes(const int32& Bytes);

	static int32 KilobytesToBytes(const float& Kilobytes);
};