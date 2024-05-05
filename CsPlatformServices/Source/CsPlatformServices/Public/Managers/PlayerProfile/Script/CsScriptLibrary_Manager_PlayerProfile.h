// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/PlayerProfile/CsTypes_PlayerProfile.h"

#include "CsScriptLibrary_Manager_PlayerProfile.generated.h"

UCLASS()
class CSPLATFORMSERVICES_API UCsScriptLibrary_Manager_PlayerProfile : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	/**
	* Set current active profile. 
	* Active profile is used by the Manager_Save to determine which Save (slot) to save to.
	*
	* @param Context				The calling context.
	* @param WorldContextObject		Object that contains a reference to a World (GetWorld() is Valid).
	* @param ProfileType			Profile to set as the active profile.
	* return
	*/
	UFUNCTION(BlueprintCallable, Category = "CsPlatformServices|Library|Manager|Player Profile", meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext, AutoCreateRefTerm = "ProfileType"))
	static bool SetCurrentActiveProfile(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& ProfileType);
};