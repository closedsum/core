// Copyright 2018 Respawn Entertainment, Inc. All rights reserved.

#pragma once

#include "UObject/Object.h"
// Types
#include "Managers/PlayerProfile/CsTypes_PlayerProfile.h"

#include "CsScriptLibrary_Manager_PlayerProfile.generated.h"

// Delegates
#pragma region

#pragma endregion Delegates


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
	*/
	UFUNCTION(BlueprintCallable, Category = "CsCore|Library|Manager|Player Profile", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "ProfileType"))
	static void SetCurrentActiveProfile(const FString& Context, UObject* WorldContextObject, const ECsPlayerProfile& ProfileType);
};