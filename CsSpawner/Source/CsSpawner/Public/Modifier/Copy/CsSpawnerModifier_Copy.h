// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsMacro_Namespace.h"

// NCsSpawner::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSpawner, NModifier, IModifier)

namespace NCsSpawner
{
	namespace NModifier
	{
		namespace NCopy
		{
			struct CSSPAWNER_API ICopy : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			#define CsSpawnerModifierType NCsSpawner::NModifier::IModifier

			public:

				virtual ~ICopy() {}

				virtual void Copy(const CsSpawnerModifierType* From) = 0;

			#undef CsSpawnerModifierType 
			};
		}
	}
}