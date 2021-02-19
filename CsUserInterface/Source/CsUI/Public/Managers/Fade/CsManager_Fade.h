// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#pragma once
#include "UObject/Object.h"
// Types
#include "Coroutine/CsTypes_Coroutine.h"
#include "Managers/Fade/CsTypes_Fade.h"

#include "CsManager_Fade.generated.h"

class ICsGetManagerFade;
struct FCsRoutine;
class UCsUserWidget_Fade;

UCLASS(transient)
class CSUI_API UCsManager_Fade : public UObject
{
	GENERATED_UCLASS_BODY()
public:

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Fade* Get(UObject* InRoot = nullptr);
#else
	static UCsManager_Fade* Get(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_Fade> ManagerMenuClass, UObject* InOuter = nullptr);
	static void Shutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerFade* Get_GetManagerFade(UObject* InRoot);
	static ICsGetManagerFade* GetSafe_GetManagerFade(UObject* Object);

	static UCsManager_Fade* GetSafe(UObject* Object);

public:

	static UCsManager_Fade* GetFromWorldContextObject(const UObject* WorldContextObject);

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
	char Fade_Internal(FCsRoutine* R);

	FCsRoutineHandle FadeHandle;

	void StopFade();
	void ClearFade();

#undef ParamsType
};