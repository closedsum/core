// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Event/CsDamageEventImpl.h"

// Library
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
// Damage
#include "Managers/Damage/Data/CsData_Damage.h"
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"
#include "Managers/Damage/Value/Point/CsDamageValuePoint.h"

const FName NCsDamage::NEvent::FImpl::Name = FName("NCsDamage::NEvent::FImpl");;

namespace NCsDamage
{
	namespace NEvent
	{
		FImpl::FImpl() :
			InterfaceMap(),
			// IEvent
			Damage(0.0f),
			DamageValue(),
			DamageRange(),
			Data(nullptr),
			Instigator(nullptr),
			Causer(nullptr),
			HitType(),
			HitResult(),
			IgnoreObjects()
		{
			InterfaceMap.SetRootName(FImpl::Name);

			InterfaceMap.Add<IEvent>(static_cast<IEvent*>(this));
			InterfaceMap.Add<ICsReset>(static_cast<ICsReset*>(this));
		}

		void FImpl::CopyFrom(const FImpl* From)
		{
			Damage = From->Damage;

			checkf(From->DamageValue.GetValue(), TEXT("NCsDamage::NEvent::FImpl::CopyFrom: From->DamageValue.Value is NULL."));

			DamageValue.CopyFrom(&(From->DamageValue));

			if (From->DamageRange.GetRange())
				DamageRange.CopyFrom(&(From->DamageRange));

			Data = From->Data;
			Instigator = From->Instigator;
			Causer = From->Causer;
			HitType = From->HitType;
			Origin = From->Origin;
			HitResult = From->HitResult;

			IgnoreObjects.Reset(FMath::Max(IgnoreObjects.Max(), From->IgnoreObjects.Max()));

			for (UObject* O : From->IgnoreObjects)
			{
				IgnoreObjects.Add(O);
			}
		}

		bool FImpl::SetDamageChecked(const FString& Context)
		{
			checkf(Data, TEXT("%s: Data is NULL."), *Context);

			checkf(DamageValue.GetValue(), TEXT("%s: DamageValue.Value is NULL."), *Context);

			// Shape
			if (ICsData_DamageShape* Shape = FCsLibrary_Data_Damage::GetSafeInterfaceChecked<ICsData_DamageShape>(Context, Data))
			{
				Damage = Shape->CalculateDamage(DamageValue.GetValue(), DamageRange.GetRange(), Origin.ImpactPoint, HitResult.ImpactPoint);
				return true;
			}
			// Point
			else
			{
				typedef NCsDamage::NValue::NPoint::IPoint ValueType;

				ValueType* DamageValuePoint = FCsLibrary_DamageValue::GetInterfaceChecked<ValueType>(Context, DamageValue.Value);
				Damage						= DamageValuePoint->GetValue();
				return true;
			}
			return false;
		}

		// ICsReset
		#pragma region

		void FImpl::Reset()
		{
			Damage = 0.0f;
			DamageValue.Reset();
			DamageRange.Reset();
			Data = nullptr;
			Instigator = nullptr;
			Causer = nullptr;
			HitType = EMCsHitType::Get().GetMAX();
			HitResult.Reset(0.0f, false);
			IgnoreObjects.Reset(IgnoreObjects.Max());
		}

		#pragma endregion ICsReset
	}
}