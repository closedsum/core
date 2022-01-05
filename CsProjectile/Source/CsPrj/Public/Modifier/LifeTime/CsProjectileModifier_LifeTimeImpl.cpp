// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/LifeTime/CsProjectileModifier_LifeTimeImpl.h"

// Library
#include "Cache/CsLibrary_Cache_Projectile.h"
#include "Library/CsLibrary_Valid.h"
// Containers
#include "Containers/CsInterfaceMap.h"
// Pool
#include "Managers/Pool/Cache/CsCache_PooledObject.h"
// Projectile
#include "Managers/Projectile/CsProjectilePooledImpl.h"
#include "Managers/Projectile/CsProjectileMovementComponent.h"

const FName NCsProjectile::NModifier::NLifeTime::FImpl::Name = FName("NCsProjectile::NModifier::NLifeTime::FImpl");

namespace NCsProjectile
{
	namespace NModifier
	{
		namespace NLifeTime
		{
			namespace NImpl
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsProjectile::NModifier::NLifeTime::FImpl, Modify);
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

				InterfaceMap->Add<ModifierType>(static_cast<ModifierType*>(this));
				InterfaceMap->Add<PrjModifierType>(static_cast<PrjModifierType*>(this));
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
				using namespace NCsProjectile::NModifier::NLifeTime::NImpl::NCached;

				const FString& Context = Str::Modify;

				ACsProjectilePooledImpl* ProjectilePooled = CS_INTERFACE_TO_UOBJECT_CAST_CHECKED(Projectile, ICsProjectile, ACsProjectilePooledImpl);

				typedef NCsProjectile::NCache::FLibrary CacheLibrary;
				typedef NCsPooledObject::NCache::ICache CacheType;

				CacheType* Cache = ProjectilePooled->GetCache();
				float LifeTime	 = Cache->GetLifeTime();

				NCsModifier::NValue::NIntegral::NApplication::Modify(LifeTime, GetValue(), GetApplication());

				CacheLibrary::SetLifeTimeChecked(Context, Cache, LifeTime);
			}

			#pragma endregion PrjModifierType (NCsProjectile::NModifier::IModifier)

			void FImpl::CopyTo(FImpl* To) const
			{
				To->SetValue(GetValue());
				To->SetApplication(GetApplication());
			}

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