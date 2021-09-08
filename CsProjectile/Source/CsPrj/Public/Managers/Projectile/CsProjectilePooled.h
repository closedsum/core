// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "Managers/Pool/CsPooledObject.h"

class ICsProjectile;

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

	FCsProjectilePooled();

	virtual ~FCsProjectilePooled() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void SetInterface(ICsPooledObject* InInterface) override;

	virtual void SetObject(UObject* InObject) override;

	virtual void Reset() override;

#pragma endregion TCsInterfaceObject

// ICsProjectile
#pragma region
public:

	UObject* GetOwner() const;

	UObject* GetInstigator() const;

#pragma endregion ICsProjectile

public:

	void SetPooledObject(const FCsPooledObject& PooledObject);

	FORCEINLINE void SetScriptProjectile()
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