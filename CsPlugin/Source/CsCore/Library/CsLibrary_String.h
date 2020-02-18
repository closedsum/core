// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Object.h"
#include "CsLibrary_String.generated.h"

UCLASS()
class CSCORE_API UCsLibrary_String : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	// Stream
#pragma region

	static FString Stream_GetString(const TCHAR*& Str, bool IsLowerCase);
	static FName Stream_GetName(const TCHAR*& Str);
	static bool Stream_GetBool(const TCHAR*& Str);
	static int32 Stream_GetBoolAsInt(const TCHAR*& Str);
	static int32 Stream_GetInt(const TCHAR*& Str);
	static float Stream_GetFloat(const TCHAR*& Str);

#pragma endregion Stream
};