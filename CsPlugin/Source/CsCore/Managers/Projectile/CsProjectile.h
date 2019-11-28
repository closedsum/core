// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Managers/Pool/CsPooledObject.h"
#include "CsProjectile.generated.h"

UINTERFACE(Blueprintable)
class UCsProjectile : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

//class ICsData_Projectile;

class ICsProjectile
{
	GENERATED_IINTERFACE_BODY()

public:
	
	/**
	*
	*
	* return Data that implements the interface: ICsData_Projectile.
	*/
	//virtual ICsData_Projectile* GetData()  = 0;

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

// FCsProjectile
#pragma region

struct CSCORE_API FCsProjectile : FCsPooledObject
{
private:

	typedef FCsPooledObject Super;

public:

	static const FCsProjectile Empty;

protected:

	ICsProjectile* Projectile;

// Script
#pragma region
public:

	/**
	*
	*/
	DECLARE_DELEGATE_RetVal_OneParam(UObject* /*Owner*/, FScript_GetOwner, UObject* /*Object*/);

	FScript_GetOwner Script_GetOwner_Impl;

	/**
	*
	*/
	DECLARE_DELEGATE_RetVal_OneParam(UObject* /*Instigator*/, FScript_GetInstigator, UObject* /*Object*/);

	FScript_GetInstigator Script_GetInstigator_Impl;

#pragma endregion Script

public:

	FCsProjectile() :
		Super(),
		Projectile(nullptr)
	{
	}

	virtual ~FCsProjectile() {}

// TCsInterfaceObject
#pragma region
public:

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

	FORCEINLINE ICsProjectile* GetProjectile() const
	{
		return Projectile;
	}

	FORCEINLINE void SetProjectile(ICsProjectile* InProjectile)
	{
		Projectile = InProjectile;
	}
};

#pragma endregion FCsProjectile