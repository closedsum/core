// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
#include "CsTypes_Javascript.h"
#include "CsManager_Javascript.generated.h"

// Delegates
#pragma region

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCsManagerJavascript_OnShutdown);

#pragma endregion Delegates

class ICsGetManagerJavascript;
struct FCsRoutine;

UCLASS()
class CSJS_API UCsManager_Javascript : public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
public:

	static UCsManager_Javascript* Get(UObject* InRoot = nullptr);
	
	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static bool IsValid(UObject* InRoot = nullptr);

	static void Init(UObject* InRoot);

	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

	UPROPERTY(BlueprintAssignable)
	FCsManagerJavascript_OnShutdown OnShutdown_ScriptEvent;

#if WITH_EDITOR
protected:

	static ICsGetManagerJavascript* Get_GetManagerJavascript(UObject* InRoot);
	static ICsGetManagerJavascript* GetSafe_GetManagerJavascript(UObject* Object);

	static UCsManager_Javascript* GetSafe(UObject* Object);

public:

	static UCsManager_Javascript* GetFromWorldContextObject(const UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_Javascript* s_Instance;
	static bool s_bShutdown;

	// Root
#pragma region
protected:

	UObject* MyRoot;

	void SetMyRoot(UObject* InRoot);

public:

	FORCEINLINE UObject* GetMyRoot()
	{
		return MyRoot;
	}

#pragma endregion Root

#pragma endregion Singleton

// Entry Point
#pragma region
private:

	UPROPERTY(Transient)
	FCsJavascriptFileObjects GameInstanceEntryPoint;

	void SetupAndRunGameInstanceEntryPoint();
	char SetupAndRunGameInstanceEntryPoint_Internal(FCsRoutine* R);

public:

	void RunGameInstanceEntryPoint();

private:

	UPROPERTY(Transient)
	FCsJavascriptFileObjects GameStateEntryPoint;

public:

	void SetupAndRunGameStateEntryPoint();

private:

	char SetupAndRunGameStateEntryPoint_Internal(FCsRoutine* R);

public:

	void RunGameStateEntryPoint();

#pragma endregion Entry Point
};