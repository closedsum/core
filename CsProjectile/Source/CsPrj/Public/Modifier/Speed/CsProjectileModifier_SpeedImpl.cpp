// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/Speed/CsProjectileModifier_SpeedImpl.h"

// Library
//#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
// Containers
#include "Containers/CsInterfaceMap.h"

const FName NCsProjectile::NModifier::NSpeed::FImpl::Name = FName("NCsProjectile::NModifier::NSpeed::FImpl");

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NSpeed
		{
			namespace NCached
			{
				namespace Str
				{
					//CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NModifier::NSpeed::FImpl, Modify);
				}
			}

			FImpl::FImpl() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				Val(0.0f)
			{
				InterfaceMap = new FCsInterfaceMap();

				InterfaceMap->SetRoot<FImpl>(this);

				typedef NCsProjectile::NModifier::IModifier PrjModifierType;

				InterfaceMap->Add<PrjModifierType>(static_cast<PrjModifierType*>(this));
			}
				
			FImpl::~FImpl()
			{
				// ICsGetInterfaceMap
				delete InterfaceMap;
			}

			void FImpl::CopyTo(FImpl* To) const
			{
				To->Val = Val;
				//To->Application = Application;
			}
		}
	}
}