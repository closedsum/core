// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Event/CsDamageEventImpl.h"

// Types
#include "CsMacro_Misc.h"
#include "CsMacro_Interface.h"
// Library
#include "Managers/Damage/Data/CsLibrary_Data_Damage.h"
	// Damage
#include "Event/CsLibrary_DamageEvent.h"
#include "Value/CsLibrary_DamageValue.h"
	// Common
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Damage
#include "Managers/Damage/Data/CsData_Damage.h"
#include "Managers/Damage/Data/Shape/CsData_DamageShape.h"
#include "Value/Point/CsDamageValuePoint.h"

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsDamage::NEvent::NImpl::FImpl);

// Cached
#pragma region

CS_START_CACHED_FUNCTION_NAME_NESTED_3(NCsDamage, NEvent, NImpl, Impl)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsDamage::NEvent::NImpl, Copy)
CS_END_CACHED_FUNCTION_NAME_NESTED_3

#pragma endregion Cached

namespace NCsDamage
{
	namespace NEvent
	{
		namespace NImpl
		{
			FImpl::FImpl() :
				InterfaceMap(),
				// IEvent
				Damage(0.0f),
				DamageValue(),
				DamageRange(),
				Type(),
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

				InterfaceMap.Add<IEvent>(static_cast<EventType*>(this));
				InterfaceMap.Add<CopyType>(static_cast<CopyType*>(this));
				InterfaceMap.Add<ICsReset>(static_cast<ICsReset*>(this));
			}

			using ShapeDataType = NCsDamage::NData::NShape::IShape;
			using ValueLibrary = NCsDamage::NValue::FLibrary;
			using PointType = NCsDamage::NValue::NPoint::IPoint;

			// CopyType (NCsDamage::NEvent::NCopy::ICopy)
			#pragma region

			void FImpl::Copy(const IEvent* From)
			{
				CS_SET_CONTEXT_AS_FUNCTION_NAME(Copy);

				const FImpl* FromImpl = CsDamageEventLibrary::PureStaticCastChecked<FImpl>(Context, From);

				Damage = FromImpl->Damage;

				checkf(FromImpl->DamageValue.GetValue(), TEXT("%s: From->DamageValue.Value is NULL."), *Context);

				DamageValue.CopyFrom(&(FromImpl->DamageValue));

				if (FromImpl->DamageRange.GetRange())
					DamageRange.CopyFrom(&(FromImpl->DamageRange));

				Type		= FromImpl->Type;
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
				if (ShapeDataType* Shape = CsDamageDataLibrary::GetSafeInterfaceChecked<ShapeDataType>(Context, Data))
				{
					Damage = Shape->CalculateDamage(DamageValue.GetValue(), DamageRange.GetRange(), CsMathLibrary::Convert(Origin.ImpactPoint), CsMathLibrary::Convert(HitResult.ImpactPoint));
					return true;
				}
				// Point
				else
				{
					PointType* DamageValuePoint = ValueLibrary::GetInterfaceChecked<PointType>(Context, DamageValue.GetValue());
					Damage						= DamageValuePoint->GetValue();
					return true;
				}
			}

			// ICsReset
			#pragma region

			void FImpl::Reset()
			{
				Damage = 0.0f;
				DamageValue.Reset();
				DamageRange.Reset();
				Type = EMCsDamageData::Get().GetMAX();
				Data = nullptr;
				Instigator = nullptr;
				Causer = nullptr;
				DamageDirection = FVector3f::ZeroVector;
				HitType = EMCsHitType::Get().GetMAX();
				Origin.Reset(0.0f, false);
				HitResult.Reset(0.0f, false);
				IgnoreObjects.Reset(IgnoreObjects.Max());
				ModifierMask = 0;
			}

			#pragma endregion ICsReset
		}
	}
}