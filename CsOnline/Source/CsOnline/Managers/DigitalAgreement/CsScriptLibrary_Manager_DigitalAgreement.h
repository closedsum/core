// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#pragma once

#include "UObject/Object.h"
// Types
#include "Managers/DigitalAgreement/CsTypes_DigitalAgreement.h"
#include "CsScriptLibrary_Manager_DigitalAgreement.generated.h"

// Delegates
#pragma region

/**
* OnAccept
*/
DECLARE_DYNAMIC_DELEGATE_OneParam(FCsScriptLibraryManagerDigitalAgreement_OnAccept, const ECsDigitalAgreement&, DigitalAgreement);
/**
* OnDoNotAccept
*/
DECLARE_DYNAMIC_DELEGATE_OneParam(FCsScriptLibraryManagerDigitalAgreement_OnDoNotAccept, const ECsDigitalAgreement&, DigitalAgreement);

#pragma endregion Delegates

UCLASS()
class CSONLINE_API UCsScriptLibrary_Manager_DigitalAgreement : public UObject
{
	GENERATED_UCLASS_BODY()

public:


	/**
	* Checks Digital Agreements are enabled.
	*
	* @param WorldContextObject
	* @param DigitalAgreement
	*/
	UFUNCTION(BlueprintPure, Category = "Script|Library|Manager|Digital Agreement", meta = (WorldContext = "WorldContextObject"))
	static bool AreEnabled(const UObject* WorldContextObject);

	/**
	* Reset any stored information about any Digital Agreement to default values.
	*
	* @param WorldContextObject
	*/
	UFUNCTION(BlueprintCallable, Category = "Script|Library|Manager|Digital Agreement", meta = (WorldContext = "WorldContextObject"))
	static void ResetAll(const UObject* WorldContextObject);

// Accept
#pragma region

	/**
	* Accept the specified Digital Agreement.
	*
	* @param WorldContextObject
	* @param DigitalAgreement
	*/
	UFUNCTION(BlueprintCallable, Category = "Script|Library|Manager|Digital Agreement", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "DigitalAgreement"))
	static void Accept(const UObject* WorldContextObject, const ECsDigitalAgreement& DigitalAgreement);

private:

	static void Accept_Internal(const FString& Context, const UObject* WorldContextObject, const ECsDigitalAgreement& DigitalAgreement);

public:

	/**
	* Bind to the event OnAccept
	* OnAccept is fired when the specified Digital Agreement
	* has been Accepted.
	*
	* @param WorldContextObject
	* @param DigitalAgreement
	* @param Event / Delegate
	*/
	UFUNCTION(BlueprintCallable, Category = "Script|Library|Manager|Digital Agreement", meta = (DisplayName = "BindToEvent: OnAccept", WorldContext = "WorldContextObject"))
	static void BindToEvent_OnAccept(const UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsScriptLibraryManagerDigitalAgreement_OnAccept Delegate);

private:

	static void BindToEvent_OnAccept_Internal(const FString& Context, const UObject* WorldContextObject, const FCsScriptLibraryManagerDigitalAgreement_OnAccept& Delegate);

public:

	/**
	* Checks whether the specified Digital Agreement has been accepted.
	*
	* @param WorldContextObject
	* @param DigitalAgreement
	*/
	UFUNCTION(BlueprintPure, Category = "Script|Library|Manager|Digital Agreement", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "DigitalAgreement"))
	static bool HasBeenAccepted(const UObject* WorldContextObject, const ECsDigitalAgreement& DigitalAgreement);

#pragma endregion Accept

// Do Not Accept
#pragma region

	/**
	* Do Not Accept the specified Digital Agreement.
	*
	* @param WorldContextObject
	*/
	UFUNCTION(BlueprintCallable, Category = "Script|Library|Manager|Digital Agreement", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "DigitalAgreement"))
	static void DoNotAccept(const UObject* WorldContextObject, const ECsDigitalAgreement& DigitalAgreement);

private:

	static void DoNotAccept_Internal(const FString& Context, const UObject* WorldContextObject, const ECsDigitalAgreement& DigitalAgreement);

public:

	/**
	* Bind to the event OnDoNotAccept
	* OnDoNotAccept is fired when the specified Digital Agreement
	* has NOT been accepted.
	*
	* @param WorldContextObject
	* @param Event / Delegate
	*/
	UFUNCTION(BlueprintCallable, Category = "Script|Library|Manager|Digital Agreement", meta = (DisplayName = "BindToEvent: OnDoNotAccept", WorldContext = "WorldContextObject"))
	static void BindToEvent_OnDoNotAccept(const UObject* WorldContextObject, UPARAM(DisplayName = "Event") FCsScriptLibraryManagerDigitalAgreement_OnDoNotAccept Delegate);

private:

	static void BindToEvent_OnDoNotAccept_Internal(const FString& Context, const UObject* WorldContextObject, const FCsScriptLibraryManagerDigitalAgreement_OnDoNotAccept& Delegate);

#pragma endregion Do Not Accept
};