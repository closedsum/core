// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Coroutine/CsTypes_Coroutine.h"
#include "Managers/Fade/CsTypes_Fade.h"
#include "Managers/Fade/CsManager_Fade_Delegates.h"

#include "CsManager_Fade.generated.h"

class ICsGetManagerFade;
struct FCsRoutine;
class UCsUserWidget_Fade;

UCLASS(transient, BlueprintType, Blueprintable, Meta = (ShowWorldContextPin))
class CSUI_API UCsManager_Fade : public UObject
{
	GENERATED_UCLASS_BODY()
public:

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Fade* Get(const UObject* InRoot = nullptr);
#else
	FORCEINLINE static UCsManager_Fade* Get(const UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	template<typename T>
	FORCEINLINE static T* Get(const UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

#if WITH_EDITOR
	static UCsManager_Fade* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);
#else
	FORCEINLINE static UCsManager_Fade* GetSafe(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_Fade> ManagerMenuClass, UObject* InOuter = nullptr);
	static void Init(UObject* InRoot, UObject* InOuter = nullptr);
	static void Shutdown(const UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerFade* Get_GetManagerFade(const UObject* InRoot);
	static ICsGetManagerFade* GetSafe_GetManagerFade(const FString& Context, const UObject* InRoot, void(*Log)(const FString&) = nullptr);

#endif // #if WITH_EDITOR

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_Fade* s_Instance;
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

	UPROPERTY()
	UCsUserWidget_Fade* FadeWidget;

	void CreateFadeWidget();

#define ParamsType NCsFade::FParams

	void Fade(const ParamsType& Params);
private:
	char Fade_Internal(FCsRoutine* R);

	FCsRoutineHandle FadeHandle;

public:

	void SafeFade(const ParamsType& Params);

#define OnCompleteEventType NCsFade::NManager::NFade::FOnComplete

	OnCompleteEventType OnFadeComplete_Event;

	FORCEINLINE OnCompleteEventType& GetOnFadeComplete_Event() { return OnFadeComplete_Event; }

#undef OnCompleteEventType

	UPROPERTY(BlueprintAssignable)
	FCsManagerFade_OnFadeComplete OnFadeComplete_ScriptEvent;

private:

	bool bFadeComplete;

public:

	FORCEINLINE bool IsFadeComplete() const { return bFadeComplete; }

	FORCEINLINE bool IsFadeActive() const { return !bFadeComplete && FadeHandle.IsValid(); }

	void StopFade();
	void ClearFade();

#undef ParamsType
};