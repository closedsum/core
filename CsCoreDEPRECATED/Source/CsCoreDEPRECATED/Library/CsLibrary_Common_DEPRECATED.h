// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "CsLibrary_Common_DEPRECATED.generated.h"

UCLASS()
class CSCOREDEPRECATED_API UCsLibrary_Common_DEPRECATED : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

// Editor Message
#pragma region

#if WITH_EDITOR

	static void DisplayNotificationInfo(const FString &InTextLiteral, const FString &InNamespace, const FString &InKey, const float &Duration);

#endif // #if WITH_EDITOR
	
#pragma endregion Editor Message
};