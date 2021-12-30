// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/Speed/CsProjectileModifier_SpeedImpl.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"
// Projectile
#include "Managers/Projectile/CsProjectilePooledImpl.h"
#include "Managers/Projectile/CsProjectileMovementComponent.h"

const FName NCsProjectile::NModifier::NSpeed::FImpl::Name = FName("NCsProjectile::NModifier::NSpeed::FImpl");

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NSpeed
		{
			namespace NImpl
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NModifier::NSpeed::FImpl, Modify);
					}
				}
			}

			FImpl::FImpl() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				Val(0.0f),
				Application(NCsProjectile::NModifier::NSpeed::EApplication::Multiply)
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

			// PrjModifierType (NCsProjectile::NModifier::IModifier)
			#pragma region

			void FImpl::Modify(ICsProjectile* Projectile)
			{
				using namespace NCsProjectile::NModifier::NSpeed::NImpl::NCached;

				const FString& Context = Str::Modify;

				ACsProjectilePooledImpl* ProjectilePooled		  = CS_INTERFACE_TO_UOBJECT_CAST_CHECKED(Projectile, ICsProjectile, ACsProjectilePooledImpl);
				UCsProjectileMovementComponent* MovementComponent = ProjectilePooled->MovementComponent;

				float& InitialSpeed = MovementComponent->InitialSpeed;

				NCsProjectile::NModifier::NSpeed::NApplication::Modify(InitialSpeed, Val, Application);
			}

			#pragma endregion PrjModifierType (NCsProjectile::NModifier::IModifier)

			void FImpl::CopyTo(FImpl* To) const
			{
				To->Val = Val;
				To->Application = Application;
			}
		}
	}
}