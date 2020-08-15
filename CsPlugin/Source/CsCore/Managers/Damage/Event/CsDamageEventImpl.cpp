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
	Expression(nullptr),
	Instigator(nullptr),
	Causer(nullptr),
	HitType(),
	HitResult(),
	IgnoreObjects()
{
	InterfaceMap.SetRootName(FCsDamageEventImpl::Name);

	InterfaceMap.Add<ICsDamageEvent>(static_cast<ICsDamageEvent*>(this));
}

void FCsDamageEventImpl::CopyFrom(const FCsDamageEventImpl* From)
{
	Damage = From->Damage;
	DamageValueContainer = From->DamageValueContainer;
	DamageValueType = From->DamageValueType;
	DamageValue = From->DamageValue;
	Expression = From->Expression;
	Instigator = From->Instigator;
	Causer = From->Causer;
	HitType = From->HitType;
	Origin = From->Origin;
	HitResult = From->HitResult;
	// TODO: Handle TArray copy
	IgnoreObjects = From->IgnoreObjects;
}

void FCsDamageEventImpl::SetDamageChecked(const FString& Context)
{
	checkf(Expression, TEXT("%s: Expression is NULL."), *Context);

	checkf(DamageValue, TEXT("%s: DamageValue is NULL."), *Context);

	// Shape
	if (ICsDamageShape* Shape = FCsLibrary_DamageExpression::GetSafeInterfaceChecked<ICsDamageShape>(Context, Expression))
	{
		Damage = Shape->CalculateDamage(DamageValue, Origin.ImpactPoint, HitResult.ImpactPoint);
	}
	// Point
	else
	{
		ICsDamageValuePoint* DamageValuePoint = FCsLibrary_DamageValue::GetInterfaceChecked<ICsDamageValuePoint>(Context, DamageValue);
		Damage								  = DamageValuePoint->GetValue();
	}
}

void FCsDamageEventImpl::Reset()
{
	Damage = 0.0f;
	DamageValueContainer = nullptr;
	DamageValueType = EMCsDamageValue::Get().GetMAX();
	DamageValue = nullptr;
	Expression = nullptr;
	Instigator = nullptr;
	Causer = nullptr;
	HitType = EMCsHitType::Get().GetMAX();
	HitResult.Reset(0.0f, false);
	IgnoreObjects.Reset(IgnoreObjects.Max());
}