// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Managers/Pool/CsPooledObject.h"
#include "CsTdCreep.generated.h"

UINTERFACE(BlueprintType, MinimalApi, meta = (CannotImplementInterfaceInBlueprint))
class UCsTdCreep : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsTdCreep
{
	GENERATED_IINTERFACE_BODY()
		
public:
};

// FCsTdCreep
#pragma region

struct CSTD_API FCsTdCreep : public TCsInterfaceObject<ICsTdCreep>
{
private:

	typedef public TCsInterfaceObject<ICsTdCreep> Super;

public:

	static const FCsTdCreep Empty;

// Script
#pragma region
public:

#pragma endregion Script

public:

	FCsTdCreep() :
		Super()
	{
	}

	virtual ~FCsTdCreep() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void Reset() override
	{
		Super::Reset();
	}

#pragma endregion TCsInterfaceObject

	// ICsTdCreep
#pragma region
public:


#pragma endregion ICsTdCreep
};

#pragma endregion FCsTdCreep

// FCsTdCreepPooled
#pragma region

class ICsSpawnedObject;

struct CSTD_API FCsTdCreepPooled : public FCsPooledObject
{
private:

	typedef FCsPooledObject Super;

public:

	static const FCsTdCreep Empty;

protected:

	/** Reference to interface of type: ICsTdCreep. */
	ICsTdCreep* Creep;

	/** Does the Projectile implement a script interface of type: ICsTdCreep. */
	bool bScriptScript;

// Script
#pragma region
public:

#pragma endregion Script

public:

	FCsTdCreepPooled() :
		Super(),
		Creep(nullptr)
	{
	}

	virtual ~FCsTdCreepPooled() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void Reset() override
	{
		Super::Reset();

		Creep = nullptr;
	}

#pragma endregion TCsInterfaceObject

// ICsTdCreep
#pragma region
public:


#pragma endregion ICsTdCreep

	public:

	void SetPooledObject(const FCsPooledObject& PooledObject)
	{
		SetInterface(PooledObject.GetInterface());
		SetObject(PooledObject.GetObject());

		if (PooledObject.IsScript())
			SetScript();

		Script_GetCache_Impl = PooledObject.Script_GetCache_Impl;
		Script_Allocate_Impl = PooledObject.Script_Allocate_Impl;
		Script_Deallocate_Impl = PooledObject.Script_Deallocate_Impl;

		if (bScript)
		{
			UClass* Class = Object->GetClass();

			// GetCache
			checkf(Script_GetCache_Impl.IsBound(), TEXT("FCsTdCreepPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_GetCache_Impl Bound to any function."), *(Object->GetName()), *(Class->GetName()));
			// Allocate
			checkf(Script_Allocate_Impl.IsBound(), TEXT("FCsTdCreepPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Allocate_Impl Bound to any function."), *(Object->GetName()), *(Class->GetName()));
			// Deallocate
			checkf(Script_Deallocate_Impl.IsBound(), TEXT("FCsTdCreepPooled::SetPooledObject: Object: %s with Class: %s does NOT have Script_Deallocate_Impl Bound to any function."), *(Object->GetName()), *(Class->GetName()));
		}
	}

	void SetScriptCreep()
	{
		bScriptScript = true;
	}

	FORCEINLINE bool GetScriptCreep() const 
	{
		return bScriptScript;
	}

	FORCEINLINE ICsTdCreep* GetCreep() const
	{
		return Creep;
	}

	FORCEINLINE void SetCreep(ICsTdCreep* InCreep)
	{
		Creep = InCreep;
	}
};

#pragma endregion FCsTdCreepPooled