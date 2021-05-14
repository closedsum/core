// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Event/CsDamageEventImpl.h"

// Library
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
#include "Library/CsLibrary_Valid.h"
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
			CS_IS_PTR_NULL_CHECKED(Data)

			CS_IS_PTR_NULL_CHECKED(DamageValue.GetValue())

			// Shape
			typedef NCsDamage::NData::FLibrary DamageDataLibrary;
			typedef NCsDamage::NData::NShape::IShape ShapeDataType;

			if (ShapeDataType* Shape = DamageDataLibrary::GetSafeInterfaceChecked<ShapeDataType>(Context, Data))
			{
				Damage = Shape->CalculateDamage(DamageValue.GetValue(), DamageRange.GetRange(), Origin.ImpactPoint, HitResult.ImpactPoint);
				return true;
			}
			// Point
			else
			{
				typedef NCsDamage::NValue::FLibrary ValueLibrary;
				typedef NCsDamage::NValue::NPoint::IPoint PointType;

				PointType* DamageValuePoint = ValueLibrary::GetInterfaceChecked<PointType>(Context, DamageValue.Value);
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