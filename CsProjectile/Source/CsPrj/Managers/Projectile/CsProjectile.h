// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Managers/Pool/CsPooledObject.h"
#include "CsProjectile.generated.h"

UINTERFACE(Blueprintable)
class CSPRJ_API UCsProjectile : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class ICsData_Projectile;

class CSPRJ_API ICsProjectile
{
	GENERATED_IINTERFACE_BODY()

public:
	
	/**
	*
	*
	* return Data that implements the interface: ICsData_Projectile.
	*/
	virtual ICsData_Projectile* GetData() const = 0;

	/**
	*
	*
	* return Owner of the projectile.
	*/
	virtual UObject* GetOwner() const = 0;

	/**
	*
	*
	* return Instigator of the projectile.
	*/
	virtual UObject* GetInstigator() const = 0;
};

// FCsProjectilePooled
#pragma region

struct CSPRJ_API FCsProjectilePooled : public FCsPooledObject
{
private:

	typedef FCsPooledObject Super;

public:

	static const FCsProjectilePooled Empty;

protected:

	/** Reference to interface of type: ICsProjecitle. */
	ICsProjectile* Projectile;

	/** Does the Projectile implement a script interface of type: ICsProjectile. */
	bool bScriptProjectile;

// Script
#pragma region
public:

	/**
	* Delegate type for getting the Owner of a Projectile.
	*  The Projectile implements a script interface of type: ICsProjectile.
	*
	* @param Object		A Projectile of type: ICsProjectile.
	* return Owner		Owner of the Projectile.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(UObject* /*Owner*/, FScript_GetOwner, UObject* /*Object*/);

	/** Delegate for getting the Owner of a Projectile. 
		 The Projectile implements a script interface of type: ICsProjectile. */
	FScript_GetOwner Script_GetOwner_Impl;

	/**
	* Delegate type for getting the Instigator of a Projectile.
	*  The Projectile implements a script interface of type: ICsProjectile.
	*
	* @param Object			A Projectile of type: ICsProjectile.
	* return Instigator		Instigator of the Projectile.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(UObject* /*Instigator*/, FScript_GetInstigator, UObject* /*Object*/);

	/** Delegate for getting the Instigator of a Projectile. 
		 The Projectile implements a script interface of type: ICsProjectile. */
	FScript_GetInstigator Script_GetInstigator_Impl;

#pragma endregion Script

public:

	FCsProjectilePooled() :
		Super(),
		Projectile(nullptr),
		bScriptProjectile(false),
		Script_GetOwner_Impl(),
		Script_GetInstigator_Impl()
	{
	}

	virtual ~FCsProjectilePooled() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void SetInterface(ICsPooledObject* InInterface) override;

	virtual void SetObject(UObject* InObject) override;

	virtual void Reset() override
	{
		Super::Reset();

		Projectile = nullptr;
	}

#pragma endregion TCsInterfaceObject

// ICsProjectile
#pragma region
public:

	FORCEINLINE UObject* GetOwner() const 
	{
		if (bScript)
			return Script_GetOwner_Impl.Execute(Object);
		return Projectile->GetOwner();
	}

	FORCEINLINE UObject* GetInstigator() const
	{
		if (bScript)
			return Script_GetInstigator_Impl.Execute(Object);
		return Projectile->GetInstigator();
	}

#pragma endregion ICsProjectile

public:

	void SetPooledObject(const FCsPooledObject& PooledObject)
	{
		SetInterface(PooledObject.GetInterface());
		SetObject(PooledObject.GetObject());

		if (PooledObject.IsScript())
			SetScript();

		Script_GetCache_Impl = PooledObject.Script_GetCache_Impl;
		Script_Allocate_Impl = PooledObject.Script_Allocate_Impl;
		Script_Update_Impl = PooledObject.Script_Update_Impl;
		Script_Deallocate_Impl = PooledObject.Script_Deallocate_Impl;

		if (bScript)
		{
			UClass* Class = Object->GetClass();

			// GetCache
			checkf(Script_GetCache_Impl.IsBound(), TEXT("FCsProjectile::SetPooledObject: Object: %s with Class: %s does NOT have Script_GetCache_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
			// Allocate
			checkf(Script_Allocate_Impl.IsBound(), TEXT("FCsProjectile::SetPooledObject: Object: %s with Class: %s does NOT have Script_Allocate_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
			// Update
			checkf(Script_Update_Impl.IsBound(), TEXT("FCsProjectile::SetPooledObject: Object: %s with Class: %s does NOT have Script_Update_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
			// Deallocate
			checkf(Script_Deallocate_Impl.IsBound(), TEXT("FCsProjectile::SetPooledObject: Object: %s with Class: %s does NOT have Script_Deallocate_Impl bound to any function."), *(Object->GetName()), *(Class->GetName()));
		}
	}

	void SetScriptProjectile()
	{
		bScriptProjectile = true;
	}

	FORCEINLINE const bool& IsScriptProjectile() const 
	{
		return bScriptProjectile;
	}

	FORCEINLINE ICsProjectile* GetProjectile() const
	{
		return Projectile;
	}

	FORCEINLINE void SetProjectile(ICsProjectile* InProjectile)
	{
		Projectile = InProjectile;
	}
};

#pragma endregion FCsProjectilePooled