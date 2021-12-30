// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interfaces
#include "Modifier/CsProjectileModifier.h"

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

			private:

				// ICsGetInterfaceMap

				FCsInterfaceMap* InterfaceMap;

			public:

				float Val;

				//ApplicationType Application;

			public:
						
				FImpl();
				~FImpl();

				FORCEINLINE UObject* _getUObject() const { return nullptr; }

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

			#pragma endregion ICsGetInterfaceMap

			public:

				void CopyTo(FImpl* To) const;
			};

		#undef PrjModifierType
		}
	}
}