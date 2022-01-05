// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsLibrary_WeaponModifier.h"
#include "CsWp.h"

// Library
#include "Library/CsLibrary_Valid.h"

namespace NCsWeapon
{
	namespace NModifier
	{
		#define ModifierType NCsWeapon::NModifier::IModifier

		bool FLibrary::IsValidChecked(const FString& Context, const ModifierType* Modifier)
		{
			CS_IS_PTR_NULL_CHECKED(Modifier)

			return true;
		}

		bool FLibrary::IsValid(const FString& Context, const ModifierType* Modifier, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
		{
			CS_IS_PTR_NULL(Modifier)

			return true;
		}

		const FECsWeaponModifier& FLibrary::GetTypeChecked(const FString& Context, const ModifierType* Modifier)
		{
			CS_IS_PTR_NULL_CHECKED(Modifier)

			checkf(0, TEXT("%s: Failed to determine type (FECsWeaponModifier) for Value."), *Context);
			return EMCsWeaponModifier::Get().GetMAX();
		}

		bool FLibrary::CopyChecked(const FString& Context, const ModifierType* From, ModifierType* To)
		{
			CS_IS_PTR_NULL_CHECKED(From)

			CS_IS_PTR_NULL_CHECKED(To)

			return false;
		}

		#undef ModifierType
	}
}