// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.

#pragma once
#include "UObject/Object.h"

#include "CsManager_Menu.generated.h"

class ICsGetManagerMenu;

UCLASS(transient)
class CSUI_API UCsManager_Menu : public UObject
{
	GENERATED_UCLASS_BODY()
public:

// Singleton
#pragma region
public:

#if WITH_EDITOR
	static UCsManager_Menu* Get(UObject* InRoot = nullptr);
#else
	static UCsManager_Menu* Get(UObject* InRoot = nullptr);
#endif // #if WITH_EDITOR

	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_Menu> ManagerMenuClass, UObject* InOuter = nullptr);
	static void Shutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerMenu* Get_GetManagerMenu(UObject* InRoot);
	static ICsGetManagerMenu* GetSafe_GetManagerMenu(UObject* Object);

	static UCsManager_Menu* GetSafe(UObject* Object);

public:

	static UCsManager_Menu* GetFromWorldContextObject(const UObject* WorldContextObject);

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
};