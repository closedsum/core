// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class ICsData_ProjectileWeapon;

struct CSWP_API FCsLibrary_Data_ProjectileWeapon
{
	/**
	*
	*
	* @param Context
	* @param Data
	* return
	*/
	static bool IsValidChecked(const FString& Context, ICsData_ProjectileWeapon* Data);
};