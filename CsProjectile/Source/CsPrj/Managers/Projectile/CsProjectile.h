// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsInterfaceObject.h"
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
	* The Data the projectile is currently using.
	*
	* return Data that implements the interface: ICsData_Projectile.
	*/
	virtual ICsData_Projectile* GetData() const = 0;

	/**
	* The object that "owns" the projectile.
	*
	* return Owner of the projectile.
	*/
	virtual UObject* GetOwner() const = 0;

	/**
	* The object that started the process of launching / activating the projectile.
	*
	* return Instigator of the projectile.
	*/
	virtual UObject* GetInstigator() const = 0;
};


// FCsProjectile
#pragma region

class ICsData_Projectile;

struct CSPRJ_API FCsProjectile : public TCsInterfaceObject<ICsProjectile>
{
private:

	typedef TCsInterfaceObject<ICsProjectile> Super;

public:

	static const FCsProjectile Empty;

	// Script
#pragma region

public:

	/**
	* Delegate type for
	*
	* @param Object		Object->GetClass() that implements the interface: ICsProjectile.
	* return			.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(ICsData_Projectile* /*Data*/, FScript_GetData, UObject* /*Object*/);

	/** Delegate type for . 
		 The Data implements a script interface of type: ICsWeapon and the UClass
		 associated with the Object have ImplementsInterface(UCsProjectile::StaticClass()) == true. */
	FScript_GetData Script_GetData_Impl;
	
	/**
	* Delegate type for 
	*
	* @param Object		Object->GetClass() that implements the interface: ICsData.
	* return
	*/
	DECLARE_DELEGATE_RetVal_OneParam(UObject* /*Owner*/, FScript_GetOwner, UObject* /*Object*/);

	/** Delegate type for  */
	FScript_GetOwner Script_GetOwner_Impl;

	/**
	* Delegate type for
	*
	* @param Object		Object->GetClass() that implements the interface: ICsData.
	* return
	*/
	DECLARE_DELEGATE_RetVal_OneParam(UObject* /*Owner*/, FScript_GetInstigator, UObject* /*Object*/);

	/** Delegate type for  */
	FScript_GetInstigator Script_GetInstigator_Impl;

#pragma endregion Script

public:

	FCsProjectile() :
		Super(),
		Script_GetData_Impl(),
		Script_GetOwner_Impl(),
		Script_GetInstigator_Impl()
	{
	}

	virtual ~FCsProjectile() {}

// TCsInterfaceObject
#pragma region
public:

	virtual void SetObject(UObject* InObject) override;

#pragma endregion TCsInterfaceObject

// TCsInterfaceObject
#pragma region
public:

	virtual void Reset() override
	{
		Super::Reset();

		Script_GetData_Impl.Unbind();
		Script_GetOwner_Impl.Unbind();
		Script_GetInstigator_Impl.Unbind();
	}

#pragma endregion TCsInterfaceObject

// ICsProjectile
#pragma region
public:

	ICsData_Projectile* GetData();

	UObject* GetOwner();

	UObject* GetInstigator();

#pragma endregion ICsProjectile
};

#pragma endregion FCsProjectile