// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Managers/Creep/CsTdTypes_Creep.h"
#include "Managers/Pool/CsPooledObject.h"
#include "CsTdCreep.generated.h"

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class CSTD_API UCsTdCreep : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class CSTD_API ICsTdCreep
{
	GENERATED_IINTERFACE_BODY()

	virtual void Stub() = 0;

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

	static const FCsTdCreepPooled Empty;

protected:

	/** Reference to interface of type: ICsTdCreep. */
	ICsTdCreep* Creep;

	/** Does the Creep implement a script interface of type: ICsTdCreep. */
	bool bScriptCreep;

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

	virtual void SetInterface(ICsPooledObject* InInterface) override;

	virtual void SetObject(UObject* InObject) override;

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
		bScriptCreep = true;
	}

	FORCEINLINE bool GetScriptCreep() const 
	{
		return bScriptCreep;
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