// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsMacro_Namespace.h"

// ModifierType (NCsProjectile::NModifier::IModifier)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NModifier, IModifier)

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NModifier
		{
			/**
			*/
			struct CSPRJ_API IModifier : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			private:

				// Allow clearer names without name collisions
				struct _
				{
					using ModifierType = NCsProjectile::NModifier::IModifier;
				};

			public:

				virtual ~IModifier(){}

				virtual const TArray<_::ModifierType*>& GetModifiers() const = 0;
			};
		}
	}
}