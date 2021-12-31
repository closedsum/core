// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Modifier/CsProjectileModifier.h"
#include "Reset/CsReset.h"
// Types
#include "Modifier/Speed/CsTypes_ProjectileModifier_Speed.h"
// Log
#include "Utility/CsPrjLog.h"

class ICsProjectile;

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NSpeed
		{
		#define PrjModifierType NCsProjectile::NModifier::IModifier

			struct CSPRJ_API FImpl : public PrjModifierType,
									 public ICsReset
			{
			public:

				static const FName Name;

			#define ApplicationType NCsProjectile::NModifier::NSpeed::EApplication

			private:

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

			public:

				float Val;

				ApplicationType Application;

			public:
						
				FImpl();
				~FImpl();

				FORCEINLINE UObject* _getUObject() const { return nullptr; }

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

			#pragma endregion ICsGetInterfaceMap

			// PrjModifierType (NCsProjectile::NModifier::IModifier)
			#pragma region
			public:

				void Modify(ICsProjectile* Projectile);

			#pragma endregion PrjModifierType (NCsProjectile::NModifier::IModifier)

			// ICsReset
			#pragma region
			public:

				FORCEINLINE void Reset()
				{
					Val = 0.0f;
					Application = ApplicationType::EApplication_MAX;
				}

			#pragma endregion ICsReset

			public:

				void CopyTo(FImpl* To) const;

				bool IsValidChecked(const FString& Context) const;
				bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning) const;

			#undef ApplicationType
			};

		#undef PrjModifierType
		}
	}
}