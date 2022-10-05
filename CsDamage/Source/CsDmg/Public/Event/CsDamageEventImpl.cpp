// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsDamageEventImpl.h"

// Library
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"
#include "Event/CsLibrary_DamageEvent.h"
#include "Value/CsLibrary_DamageValue.h"
#include "Library/CsLibrary_Valid.h"
// Damage
#include "Managers/Damage/Data/CsData_Damage.h"
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"
#include "Value/Point/CsDamageValuePoint.h"

const FName NCsDamage::NEvent::FImpl::Name = FName("NCsDamage::NEvent::FImpl");;

namespace NCsDamage
{
	namespace NEvent
	{
		namespace NImpl
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsDamage::NEvent::FImpl, Copy);
				}
			}
		}

		FImpl::FImpl() :
			InterfaceMap(),
			// IEvent
			Damage(0.0f),
			DamageValue(),
			DamageRange(),
			Data(nullptr),
			Instigator(nullptr),
			Causer(nullptr),
			DamageDirection(0.0f),
			HitType(),
			Origin(),
			HitResult(),
			IgnoreObjects(),
			ModifierMask(0)
		{
			InterfaceMap.SetRoot<FImpl>(this);

			typedef NCsDamage::NEvent::NCopy::ICopy CopyType;

			InterfaceMap.Add<IEvent>(static_cast<IEvent*>(this));
			InterfaceMap.Add<CopyType>(static_cast<CopyType*>(this));
			InterfaceMap.Add<ICsReset>(static_cast<ICsReset*>(this));
		}

		// CopyType (NCsDamage::NEvent::NCopy::ICopy)
		#pragma region

		void FImpl::Copy(const IEvent* From)
		{
			using namespace NCsDamage::NEvent::NImpl::NCached;

			const FString& Context = Str::Copy;

			typedef NCsDamage::NEvent::FLibrary EventLibrary;

			const FImpl* FromImpl = EventLibrary::PureStaticCastChecked<FImpl>(Context, From);

			Damage = FromImpl->Damage;

			checkf(FromImpl->DamageValue.GetValue(), TEXT("%s: From->DamageValue.Value is NULL."), *Context);

			DamageValue.CopyFrom(&(FromImpl->DamageValue));

			if (FromImpl->DamageRange.GetRange())
				DamageRange.CopyFrom(&(FromImpl->DamageRange));

			Data		= FromImpl->Data;
			Instigator  = FromImpl->Instigator;
			Causer		= FromImpl->Causer;
			DamageDirection = FromImpl->DamageDirection;
			HitType		= FromImpl->HitType;
			Origin		= FromImpl->Origin;
			HitResult	= FromImpl->HitResult;
			ModifierMask = FromImpl->ModifierMask;

			IgnoreObjects.Reset(FMath::Max(IgnoreObjects.Max(), FromImpl->IgnoreObjects.Max()));

			for (UObject* O : FromImpl->IgnoreObjects)
			{
				IgnoreObjects.Add(O);
			}
		}

		#pragma endregion CopyType (NCsDamage::NEvent::NCopy::ICopy)

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

				PointType* DamageValuePoint = ValueLibrary::GetInterfaceChecked<PointType>(Context, DamageValue.GetValue());
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
			DamageDirection = FVector::ZeroVector;
			HitType = EMCsHitType::Get().GetMAX();
			Origin.Reset(0.0f, false);
			HitResult.Reset(0.0f, false);
			IgnoreObjects.Reset(IgnoreObjects.Max());
			ModifierMask = 0;
		}

		#pragma endregion ICsReset
	}
}