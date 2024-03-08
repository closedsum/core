// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Containers
#include "Containers/CsInterfaceObject.h"

class ICsWeapon;
class ICsPooledObject;

struct CSWP_API FCsWeaponClass : public TCsInterfaceObject<ICsWeapon>
{
private:

	typedef TCsInterfaceObject<ICsWeapon> Super;

public:

	static const FCsWeaponClass Empty;

public:

	FCsWeaponClass();

	virtual ~FCsWeaponClass() {}

	FORCEINLINE bool operator==(const FCsWeaponClass& B) const
	{
		return Interface == B.Interface &&
			   WeakObject == B.WeakObject &&
			   Object == B.Object &&
			   bObject == B.bObject &&
			   bScript == B.bScript;
	}

	FORCEINLINE bool operator!=(const FCsWeaponClass& B) const
	{
		return !(*this == B);
	}

// TCsInterfaceObject
#pragma region
public:

	virtual void SetInterface(ICsWeapon* InInterface) override;

	virtual void SetObject(UObject* InObject) override;

#pragma endregion TCsInterfaceObject
};