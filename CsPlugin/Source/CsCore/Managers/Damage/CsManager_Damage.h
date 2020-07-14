// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UObject/Object.h"
#include "UniqueObject/CsTypes_UniqueObject.h"
#include "CsManager_Damage.generated.h"

class ICsGetManagerDamage;
class ICsDamageableObject;
struct ICsDamageEvent;

UCLASS()
class CSCORE_API UCsManager_Damage : public UObject
{
	GENERATED_UCLASS_BODY()

// Singleton
#pragma region
public:

	static UCsManager_Damage* Get(UObject* InRoot = nullptr);
	
	template<typename T>
	static T* Get(UObject* InRoot = nullptr)
	{
		return Cast<T>(Get(InRoot));
	}

	static bool IsValid(UObject* InRoot = nullptr);

	static void Init(UObject* InRoot, TSubclassOf<UCsManager_Damage> ManagerDamageClass, UObject* InOuter = nullptr);
	
	static void Shutdown(UObject* InRoot = nullptr);
	static bool HasShutdown(UObject* InRoot = nullptr);

#if WITH_EDITOR
protected:

	static ICsGetManagerDamage* Get_GetManagerDamage(UObject* InRoot);
	static ICsGetManagerDamage* GetSafe_GetManagerDamage(UObject* Object);

	static UCsManager_Damage* GetSafe(UObject* Object);

public:

	static UCsManager_Damage* GetFromWorldContextObject(const UObject* WorldContextObject);

#endif // #if WITH_EDITOR

protected:

	virtual void Initialize();
	virtual void CleanUp();

private:
	// Singleton data
	static UCsManager_Damage* s_Instance;
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

// Damageable Objects
#pragma region
protected:

	TMap<FCsUniqueObjectId, ICsDamageableObject*> DamageableObjectMap;

public:

	void Add(ICsDamageableObject* Object);

	void Remove(ICsDamageableObject* Object);

#pragma endregion Damageable Objects

public:

	void OnEvent(ICsDamageEvent* Event);
};