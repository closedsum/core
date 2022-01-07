// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/Speed/CsProjectileModifier_MaxSpeedImpl.h"

// Library
#include "Modifier/CsLibrary_ProjectileModifier.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"
// Projectile
#include "Managers/Projectile/CsProjectilePooledImpl.h"
#include "Managers/Projectile/CsProjectileMovementComponent.h"

const FName NCsProjectile::NModifier::NSpeed::NMax::FImpl::Name = FName("NCsProjectile::NModifier::NSpeed::NMax::FImpl");

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NSpeed
		{
			namespace NMax
			{
				namespace NImpl
				{
					namespace NCached
					{
						namespace Str
						{
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NModifier::NSpeed::NMax::FImpl, Modify);
							CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NModifier::NSpeed::NMax::FImpl, Copy);
						}
					}
				}

				FImpl::FImpl() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0.0f),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Application, NCsModifier::NValue::NIntegral::EApplication::Multiply)
				{
					InterfaceMap = new FCsInterfaceMap();

					InterfaceMap->SetRoot<FImpl>(this);

					typedef NCsModifier::IModifier ModifierType;
					typedef NCsProjectile::NModifier::IModifier PrjModifierType;
					typedef NCsProjectile::NModifier::NCopy::ICopy CopyType;

					InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
					InterfaceMap->Add<PrjModifierType>(static_cast<PrjModifierType*>(this));
					InterfaceMap->Add<ICsGetProjectileModifierType>(static_cast<ICsGetProjectileModifierType*>(this));
					InterfaceMap->Add<CopyType>(static_cast<CopyType*>(this));
					InterfaceMap->Add<ICsReset>(static_cast<ICsReset*>(this));

					CS_CTOR_SET_MEMBER_PROXY(Value);
					CS_CTOR_SET_MEMBER_PROXY(Application);
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
					using namespace NCsProjectile::NModifier::NSpeed::NMax::NImpl::NCached;

					const FString& Context = Str::Modify;

					ACsProjectilePooledImpl* ProjectilePooled		  = CS_INTERFACE_TO_UOBJECT_CAST_CHECKED(Projectile, ICsProjectile, ACsProjectilePooledImpl);
					UCsProjectileMovementComponent* MovementComponent = ProjectilePooled->MovementComponent;

					float& MaxSpeed = MovementComponent->MaxSpeed;

					NCsModifier::NValue::NIntegral::NApplication::Modify(MaxSpeed, GetValue(), GetApplication());
				}

				#pragma endregion PrjModifierType (NCsProjectile::NModifier::IModifier)

				#define PrjModifierType NCsProjectile::NModifier::IModifier
				void FImpl::Copy(const PrjModifierType* From)
				{
				#undef PrjModifierType

					using namespace NCsProjectile::NModifier::NSpeed::NMax::NImpl::NCached;

					const FString& Context = Str::Copy;

					typedef NCsProjectile::NModifier::FLibrary PrjModifierLibrary;

					const FImpl* FromImpl = PrjModifierLibrary::PureStaticCastChecked<FImpl>(Context, From);

					SetValue(FromImpl->GetValue());
					SetApplication(FromImpl->GetApplication());
				}

				#pragma endregion CopyType (NCsProjectile::NModifier::NCopy::ICopy)

				bool FImpl::IsValidChecked(const FString& Context) const
				{
					CS_IS_FLOAT_GREATER_THAN_CHECKED(GetValue(), 0.0f)

					typedef NCsModifier::NValue::NIntegral::EMApplication ApplicationMapType;

					CS_IS_ENUM_VALID_CHECKED(ApplicationMapType, GetApplication())
					return true;
				}

				bool FImpl::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
				{
					CS_IS_FLOAT_GREATER_THAN(GetValue(), 0.0f)

					typedef NCsModifier::NValue::NIntegral::EMApplication ApplicationMapType;
					typedef NCsModifier::NValue::NIntegral::EApplication ApplicationType;

					CS_IS_ENUM_VALID(ApplicationMapType, ApplicationType, GetApplication())
					return true;
				}
			}
		}
	}
}