// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Weapon.h"
#include "Types/CsTypes_Projectile.h"
// Log
#include "Utility/CsWpLog.h"

namespace NCsWeapon
{
	namespace NProjectile
	{
		/**
		*/
		struct CSWP_API FLibrary
		{
		public:

			/**
			* Get the Projectile type associated with Weapon of Type.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* return				Projectile type associated with Type (weapon).
			*/
			static const FECsProjectile& GetProjectileTypeChecked(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type);

			/**
			* Safely get the Projectile type associated with Weapon of Type.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Type
			* @param Log			(optional)
			* return				Projectile type associated with Type (weapon).
			*/
			static const FECsProjectile& GetSafeProjectileType(const FString& Context, const UObject* WorldContext, const FECsWeapon& Type, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);
		};
	}
}