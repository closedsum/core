// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Templates/SubclassOf.h"

#include "CsManager_Menu.generated.h"

class ICsGetManagerMenu;

UCLASS(transient, BlueprintType, Blueprintable, Meta = (ShowWorldContextPin))
class CSMENU_API UCsManager_Menu : public UObject
{
	GENERATED_UCLASS_BODY()
public:

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Menu* Get(UObject* InRoot = nullptr);
#else
	FORCEINLINE static UCsManager_Menu* Get(UObject* InRoot = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

#if WITH_EDITOR
	static UCsManager_Menu* GetSafe(const FString& Context, UObject* InRoot, void(*Log)(const FString&) = nullptr);
#else
	FORCEINLINE static UCsManager_Menu* GetSafe(const FString& Context, UObject* InRoot, void(*Log)(const FString&) = nullptr)
	{
		return s_bShutdown ? nullptr : s_Instance;
	}
#endif // #if WITH_EDITOR

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_Menu> ManagerMenuClass, UObject* InOuter = nullptr);
	static void Init(UObject* InRoot, UObject* InOuter = nullptr);
	static void Shutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerMenu* Get_GetManagerMenu(UObject* InRoot);
	static ICsGetManagerMenu* GetSafe_GetManagerMenu(const FString& Context, UObject* InRoot, void(*Log)(const FString&) = nullptr);

#endif // #if WITH_EDITOR

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_Menu* s_Instance;
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

public:

	void Update(const float& DeltaSeconds);
};