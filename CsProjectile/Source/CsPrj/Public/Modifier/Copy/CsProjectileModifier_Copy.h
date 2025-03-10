// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsMacro_Namespace.h"

// NCsPRojectile::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NModifier, IModifier)

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NCopy
		{
			struct CSPRJ_API ICopy : public ICsGetInterfaceMap
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

				virtual ~ICopy() {}

				virtual void Copy(const _::ModifierType* From) = 0;
			};
		}
	}
}