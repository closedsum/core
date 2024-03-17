// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "UObject/Interface.h"
#include "Containers/CsInterfaceObject.h"
// Types
#include "Macro/CsMacro_Namespace.h"
#include "Managers/Time/CsTypes_Time.h"

#include "CsProjectileWeapon.generated.h"

UINTERFACE(BlueprintType)
class CSWP_API UCsProjectileWeapon : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
*/
class CSWP_API ICsProjectileWeapon
{
	GENERATED_IINTERFACE_BODY()

public:

	/**
	*
	*/
	virtual void StartFire() = 0;
	
	/** 
	*
	*/
	virtual void StopFire() = 0;
};

// FCsProjectileWeapon
#pragma region

class ICsWeapon;
class ICsUpdate;

// NCsWeapon::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NData, IData)

struct CSWP_API FCsProjectileWeapon : public TCsInterfaceObject<ICsProjectileWeapon>
{
private:

	typedef TCsInterfaceObject<ICsProjectileWeapon> Super;

#define DataType NCsWeapon::NData::IData

public:

	static const FCsProjectileWeapon Empty;

protected:

	/** Reference to interface of type: ICsWeapon. */
	ICsWeapon* Weapon;

	/** Does the object implement a script interface of type: ICsWeapon. */
	bool bScriptWeapon;

	/** Reference to interface of type: ICsUpdate. */
	ICsUpdate* _Update;

	/** Does the object implement a script interface of type: ICsUpdate. */
	bool bScriptUpdate;

// Script
#pragma region
public:

	// ICsWeapon
#pragma region

	/**
	* Delegate type for getting the Data associated with a Weapon.
	*  The Weapon implements a script interface of type: ICsWeapon.
	*
	* @param Object		An object of type: ICsWeapon.
	* return Data		The cache associated with the Pooled Object.
	*/
	DECLARE_DELEGATE_RetVal_OneParam(DataType* /*Data*/, FScript_GetData, UObject* /*Object*/);

	/** Delegate for getting the Data associated with a Weapon. 
		 The Weapon implements a script interface of type: ICsWeapon. */
	FScript_GetData Script_GetData_Impl;

#pragma endregion ICsWeapon

	// ICsProjectileWeapon
#pragma region
public:

	/**
	* Delegate type for start firing a Weapon.
	*  The Weapon implements a script interface of type: ICsProjectileWeapon.
	*
	* @param Object		An object of type: ICsProjectileWeapon.
	*/
	DECLARE_DELEGATE_OneParam(FScript_StartFire, UObject* /*Object*/);

	/** Delegate for start firing a Weapon.
		 The Weapon implements a script interface of type: ICsProjectileWeapon. */
	FScript_StartFire Script_StartFire_Impl;

	/**
	* Delegate type for stop firing a Weapon.
	*  The Weapon implements a script interface of type: ICsProjectileWeapon.
	*
	* @param Object		An object of type: ICsProjectileWeapon.
	*/
	DECLARE_DELEGATE_OneParam(FScript_StopFire, UObject* /*Object*/);

	/** Delegate for start firing a Weapon.
		 The Weapon implements a script interface of type: ICsProjectileWeapon. */
	FScript_StopFire Script_StopFire_Impl;

#pragma endregion ICsProjectileWeapon

	// ICsUpdate
#pragma region
public:

	/**
	* Delegate type for updating an object.
	*   The object implements a script interface of type: ICsUpdate.
	*
	* @param Object		A Pooled Object of type: ICsUpdate.
	* @param DeltaTime
	*/
	DECLARE_DELEGATE_TwoParams(FScript_Update, UObject* /*Object*/, const FCsDeltaTime& /*DeltaTime*/);

	/** Delegate for updating a Pooled Object. */
	FScript_Update Script_Update_Impl;

#pragma endregion ICsUpdate

#pragma endregion Script

public:

	FCsProjectileWeapon() :
		Super(),
		Weapon(nullptr),
		bScriptWeapon(false),
		_Update(nullptr),
		bScriptUpdate(false),
		Script_GetData_Impl(),
		Script_StartFire_Impl(),
		Script_StopFire_Impl(),
		Script_Update_Impl()
	{
	}

	virtual ~FCsProjectileWeapon() {}

	FORCEINLINE bool operator==(const FCsProjectileWeapon& B) const
	{
		return Interface == B.Interface &&
			   WeakObject == B.WeakObject &&
			   Object == B.Object &&
			   bObject == B.bObject &&
			   bScript == B.bScript &&
			   Weapon == B.Weapon &&
			   bScriptWeapon == B.bScriptWeapon &&
			   _Update == B._Update &&
			   bScriptUpdate == B.bScriptUpdate;
	}

	FORCEINLINE bool operator!=(const FCsProjectileWeapon& B) const
	{
		return !(*this == B);
	}

// TCsInterfaceObject
#pragma region
public:

	virtual void SetInterface(ICsProjectileWeapon* InInterface) override;

	virtual void SetObject(UObject* InObject) override;

	virtual void Reset() override;

#pragma endregion TCsInterfaceObject

// ICsWeapon
#pragma region

#pragma endregion ICsWeapon

public:

	FORCEINLINE void SetScriptWeapon()
	{
		bScriptWeapon = true;
	}

	FORCEINLINE const bool& IsScriptWeapon() const
	{
		return bScriptWeapon;
	}

	FORCEINLINE void SetWeapon(ICsWeapon* InWeapon)
	{
		Weapon = InWeapon;
	}

	FORCEINLINE ICsWeapon* GetWeapon() const
	{
		return Weapon;
	}

// ICsProjectileWeapon
#pragma region

	FORCEINLINE void StartFire()
	{
		if (bScript)
			Script_StartFire_Impl.Execute(Object);
		else
			Interface->StartFire();
	}

	FORCEINLINE void StopFire()
	{
		if (bScript)
			Script_StopFire_Impl.Execute(Object);
		else
			Interface->StopFire();
	}

#pragma endregion ICsProjectileWeapon

// ICsUpdate
#pragma region
public:

	void Update(const FCsDeltaTime& DeltaTime);

#pragma endregion ICsUpdate

public:

	FORCEINLINE void SetScriptUpdate()
	{
		bScriptUpdate = true;
	}

	FORCEINLINE const bool& IsScriptUpdate() const
	{
		return bScriptUpdate;
	}

	FORCEINLINE void SetUpdate(ICsUpdate* InUpdate)
	{
		_Update = InUpdate;
	}

	FORCEINLINE ICsUpdate* GetUpdate() const 
	{
		return _Update;
	}

#undef DataType
};

#pragma endregion FCsProjectileWeapon