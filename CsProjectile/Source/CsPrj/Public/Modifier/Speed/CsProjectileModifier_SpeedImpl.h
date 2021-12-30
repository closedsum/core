// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Modifier/CsProjectileModifier.h"
// Types
#include "Modifier/Speed/CsTypes_ProjectileModifier_Speed.h"

class ICsProjectile;

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NSpeed
		{
		#define PrjModifierType NCsProjectile::NModifier::IModifier

			struct CSPRJ_API FImpl : public PrjModifierType
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

			public:

				void CopyTo(FImpl* To) const;

			#undef ApplicationType
			};

		#undef PrjModifierType
		}
	}
}