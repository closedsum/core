// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/DigitalAgreement/CsTypes_DigitalAgreement.h"
#include "CsManager_DigitalAgreement.generated.h"

// Delegates
#pragma region

/**
* OnAccept
*
* @param DigitalAgreement
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerDigitalAgreement_OnAccept, const ECsDigitalAgreement&, DigitalAgreement);
/**
* OnDoNotAccept
*
* @param DigitalAgreement
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCsManagerDigitalAgreement_OnDoNotAccept, const ECsDigitalAgreement&, DigitalAgreement);

#pragma endregion Delegates

class ICsGetManagerDigitalAgreement;
class FCsConsoleCommand_DigitalAgreement;
struct FCsRoutine;

/**
* 
*/
UCLASS(transient)
class CSONLINE_API UCsManager_DigitalAgreement : public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
public:

	static UCsManager_DigitalAgreement* Get(UObject* InRoot = nullptr);

	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static bool IsValid(UObject* InRoot = nullptr);
	static void Init(UObject* InRoot);
	static void Shutdown(UObject* InRoot = nullptr);
	static void SafeShutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerDigitalAgreement* Get_GetManagerDigitalAgreement(UObject* InRoot);
	static ICsGetManagerDigitalAgreement* GetSafe_GetManagerDigitalAgreement(UObject* Object);

	static UCsManager_DigitalAgreement* GetSafe(UObject* Object);

public:

	static UCsManager_DigitalAgreement* GetFromWorldContextObject(const UObject* WorldContextObject);

	template<typename T>
	static T* GetFromWorldContextObject(const UObject* WorldContextObject)
	{
		return Cast<T>(GetFromWorldContextObject(WorldContextObject));
	}

#endif // #if WITH_EDITOR

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_DigitalAgreement* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
protected:

	UObject * MyRoot;

	void SetMyRoot(UObject* InRoot);

public:

	FORCEINLINE UObject* GetMyRoot()
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton

public:

	bool AreEnabled();

// Query
#pragma region
public:

	void Query();

protected:

	char Query_Internal(FCsRoutine* R);

#pragma endregion Query

// Console Command
#pragma region
protected:

	FCsConsoleCommand_DigitalAgreement* ConsoleCommand;

public:

	FORCEINLINE FCsConsoleCommand_DigitalAgreement* const GetConsoleCommand()
	{
		return ConsoleCommand;
	}

#pragma endregion Console Command

protected:

	TArray<FCsDigitalAgreementState> States;

// Reset
#pragma region
public:

	/**
	*
	*
	* @param DigitalAgreement
	*/
	void Reset(const ECsDigitalAgreement& DigitalAgreement);

	/**
	*
	*
	* @param DigitalAgreement
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnReset, const ECsDigitalAgreement& /*DigitalAgreement*/);

	/** */
	FOnReset OnReset_Event;

	void ResetAll();

	/**
	*
	*/
	DECLARE_MULTICAST_DELEGATE(FOnResetAll);

	/** */
	FOnResetAll OnResetAll_Event;

#pragma endregion Reset

// Accept
#pragma region
public:

	/**
	*
	* 
	* @param DigitalAgreement
	*/
	void Accept(const ECsDigitalAgreement& DigitalAgreement);

	/**
	*
	*
	* @param DigitalAgreement
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnAccept, const ECsDigitalAgreement& /*DigitalAgreement*/);

	/** */
	FOnAccept OnAccept_Event;
	/** */
	FCsManagerDigitalAgreement_OnAccept OnAccept_ScriptEvent;

	bool HasBeenAccepted(const ECsDigitalAgreement& DigitalAgreement);

#pragma endregion Accept

// Do Not Accept
#pragma region
public:

	/**
	*
	*
	* @param DigitalAgreement
	*/
	void DoNotAccept(const ECsDigitalAgreement& DigitalAgreement);

	/**
	*
	*
	* @param DigitalAgreement
	*/
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDoNotAccept, const ECsDigitalAgreement& /*DigitalAgreement*/);

	/** */
	FOnDoNotAccept OnDoNotAccept_Event;
	/** */
	FCsManagerDigitalAgreement_OnDoNotAccept OnDoNotAccept_ScriptEvent;

#pragma endregion Do Not Accept
};