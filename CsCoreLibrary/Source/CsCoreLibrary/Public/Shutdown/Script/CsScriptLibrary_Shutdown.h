// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"

#include "CsScriptLibrary_Shutdown.generated.h"

UCLASS()
class CSCORELIBRARY_API UCsScriptLibrary_Shutdown : public UObject
{ 
	GENERATED_UCLASS_BODY() 

// Shutdown
#pragma region
public:

	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|ICsShutdown", meta = (AutoCreateRefTerm = "Context"))
	static bool HasShutdown(const FString& Context, UObject* Object);

	UFUNCTION(BlueprintCallable, Category = "CsCoreLibrary|ICsShutdown")
	static bool HasShutdown_NoLog(UObject* Object);

#pragma endregion Shutdown
};