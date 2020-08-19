// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Event/CsDamageEventImpl.h"

// Library
#include "Managers/Damage/Expression/CsLibrary_DamageExpression.h"
#include "Managers/Damage/Value/CsLibrary_DamageValue.h"
// Damage
#include "Managers/Damage/Expression/CsDamageExpression.h"
#include "Managers/Damage/Shape/CsDamageShape.h"
#include "Managers/Damage/Value/Point/CsDamageValuePoint.h"

const FName FCsDamageEventImpl::Name = FName("FCsDamageEventImpl");;

FCsDamageEventImpl::FCsDamageEventImpl() :
	InterfaceMap(),
	// ICsDamageEvent
	Damage(0.0f),
	DamageValueContainer(nullptr),
	DamageValueType(),
	DamageValue(nullptr),
	DamageRangeContainer(nullptr),
	DamageRange(nullptr),
	Expression(nullptr),
	Instigator(nullptr),
	Causer(nullptr),
	HitType(),
	HitResult(),
	IgnoreObjects()
{
	InterfaceMap.SetRootName(FCsDamageEventImpl::Name);

	InterfaceMap.Add<ICsDamageEvent>(static_cast<ICsDamageEvent*>(this));
	InterfaceMap.Add<ICsReset>(static_cast<ICsReset*>(this));
}

void FCsDamageEventImpl::CopyFrom(const FCsDamageEventImpl* From)
{
	Damage = From->Damage;
	DamageValueType = From->DamageValueType;
	Expression = From->Expression;
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

bool FCsDamageEventImpl::SetDamageChecked(const FString& Context)
{
	checkf(Expression, TEXT("%s: Expression is NULL."), *Context);

	checkf(DamageValue, TEXT("%s: DamageValue is NULL."), *Context);

	// Shape
	if (ICsDamageShape* Shape = FCsLibrary_DamageExpression::GetSafeInterfaceChecked<ICsDamageShape>(Context, Expression))
	{
		Damage = Shape->CalculateDamage(DamageValue, DamageRange, Origin.ImpactPoint, HitResult.ImpactPoint);
		return true;
	}
	// Point
	else
	{
		ICsDamageValuePoint* DamageValuePoint = FCsLibrary_DamageValue::GetInterfaceChecked<ICsDamageValuePoint>(Context, DamageValue);
		Damage								  = DamageValuePoint->GetValue();
		return true;
	}
	return false;
}

// ICsReset
#pragma region

void FCsDamageEventImpl::Reset()
{
	Damage = 0.0f;
	DamageValueContainer = nullptr;
	DamageValueType = EMCsDamageValue::Get().GetMAX();
	DamageValue = nullptr;
	DamageRangeContainer = nullptr;
	DamageRange = nullptr;
	Expression = nullptr;
	Instigator = nullptr;
	Causer = nullptr;
	HitType = EMCsHitType::Get().GetMAX();
	HitResult.Reset(0.0f, false);
	IgnoreObjects.Reset(IgnoreObjects.Max());
}

#pragma endregion ICsReset