// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Result/CsDamageResultImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsDamage::NResult::FImpl::Name = FName("NCsDamage::NResult::FImpl");;

namespace NCsDamage
{
	namespace NResult
	{
		FImpl::FImpl() :
			InterfaceMap(nullptr),
			// IResult
			Damage(0.0f),
			Instigator(nullptr),
			Causer(nullptr),
			Victim(nullptr),
			DamageType(),
			HitType(),
			bImpulse(false),
			HitResult()
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			InterfaceMap->Add<IResult>(static_cast<IResult*>(this));
		}

		FImpl::~FImpl()
		{
			delete InterfaceMap;
		}

		void FImpl::Reset()
		{
			Damage = 0.0f;
			Instigator = nullptr;
			Causer = nullptr;
			Victim = nullptr;
			DamageType = EMCsDamageType::Get().GetMAX();
			HitType = EMCsHitType::Get().GetMAX();
			bImpulse = false;
			HitResult.Reset(0.0f, false);
		}
	}
}