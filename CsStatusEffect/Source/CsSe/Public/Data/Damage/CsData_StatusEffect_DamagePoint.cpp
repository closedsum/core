// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Damage/CsData_StatusEffect_DamagePoint.h"
#include "CsSe.h"

// Containers
#include "Containers/CsInterfaceMap.h"
// Library
#include "Library/Load/CsLibrary_Load.h"
// Damage
#include "Managers/Damage/Data/CsData_DamagePointProxy.h"

// FPointProxy
#pragma region

const FName NCsStatusEffect::NData::NDamage::FPointProxy::Name = FName("NCsStatusEffect::NData::NDamage::FPointProxy");

namespace NCsStatusEffect
{
	namespace NData
	{
		namespace NDamage
		{
			FPointProxy::FPointProxy() :
				Outer(nullptr),
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				// StatusEffectDataType (NCsStatusEffect::NData::IData)
				TriggerCondition(nullptr),
				TriggerFrequencyParams(nullptr),
				TransferFrequencyParams(nullptr),
				Children(nullptr),
				// StatusEffectDamageDataType (NCsStatusEffect::NData::NDamage::IDamage)
				DamageData(nullptr)
			{
				InterfaceMap = new FCsInterfaceMap();

				InterfaceMap->SetRoot<FPointProxy>(this);

				typedef NCsData::IData DataType;
				typedef NCsStatusEffect::NData::IData StatusEffectDataType;
				typedef NCsStatusEffect::NData::NDamage::IDamage StatusEffectDamageDataType;

				InterfaceMap->Add<DataType>(static_cast<DataType*>(this));
				InterfaceMap->Add<StatusEffectDataType>(static_cast<StatusEffectDataType*>(this));
				InterfaceMap->Add<StatusEffectDamageDataType>(static_cast<StatusEffectDamageDataType*>(this));
			}

			FPointProxy::~FPointProxy()
			{
				delete InterfaceMap;
			}
		}
	}
}

#pragma endregion FPointProxy

const FName UCsData_StatusEffect_DamagePoint::Name = FName("UCsData_StatusEffect_DamagePoint");

UCsData_StatusEffect_DamagePoint::UCsData_StatusEffect_DamagePoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// UObject Interface
#pragma region

void UCsData_StatusEffect_DamagePoint::PostLoad()
{
	Super::PostLoad();

	if (this == GetClass()->GetDefaultObject<UCsData_StatusEffect_DamagePoint>())
	{
		Init();
		bLoaded = false;
	}
}

void UCsData_StatusEffect_DamagePoint::BeginDestroy()
{
	Super::BeginDestroy();

	// ICsGetInterfaceMap
	if (InterfaceMap)
	{
		delete InterfaceMap;
		InterfaceMap = nullptr;
	}
	// ICsStatusEffect_Damage
	if (DamagePointProxy)
	{
		typedef NCsDamage::NData::NPoint::FProxy PointDataProxyType;

		PointDataProxyType* Proxy = static_cast<PointDataProxyType*>(DamagePointProxy);
		delete Proxy;
		DamagePointProxy = nullptr;
	}
	if (DataProxy)
	{
		delete DataProxy;
		DataProxy = nullptr;
	}
}

#pragma endregion UObject Interface

void UCsData_StatusEffect_DamagePoint::Init()
{
	// ICsGetInterfaceMap
	if (!InterfaceMap)
	{
		// Setup InterfaceMap
		InterfaceMap = new FCsInterfaceMap();

		InterfaceMap->SetRoot<UCsData_StatusEffect_DamagePoint>(this);

		InterfaceMap->Add<ICsData>(Cast<ICsData>(this));
		InterfaceMap->Add<ICsData_StatusEffect>(Cast<ICsData_StatusEffect>(this));
		InterfaceMap->Add<ICsData_StatusEffect_Damage>(Cast<ICsData_StatusEffect_Damage>(this));
	}
	// ICsStatusEffect_Damage
	if (!DamagePointProxy)
	{
		typedef NCsDamage::NData::NPoint::FProxy PointDataProxyType;

		DamagePointProxy = new PointDataProxyType();
		DamagePoint.SetData(static_cast<PointDataProxyType*>(DamagePointProxy));
	}
	if (!DataProxy)
	{
		typedef NCsStatusEffect::NData::NDamage::FPointProxy DataProxyType;

		DataProxy = new DataProxyType();

		DataProxyType* Proxy = (DataProxyType*)DataProxy;
		Proxy->SetOuter(this);
		// // NCsStatusEffect::NData::IData
		//Proxy->SetTriggerCondition(this);
		//Proxy->SetTriggerFrequencyParams(this);
		//Proxy->SetTransferFrequencyParams(this);
		//Proxy->SetChildren(this);
		// NCsStatusEffect::NData::NDamage::IDamage
		//Proxy->SetDamageData();
	}
}

// ICsData
#pragma region

bool UCsData_StatusEffect_DamagePoint::IsValid(const int32& LoadFlags)
{
	return true;
}

void UCsData_StatusEffect_DamagePoint::Load(const int32& LoadFlags)
{
	UCsLibrary_Load::LoadStruct(this, GetClass(), LoadFlags, NCsLoadCodes::All);

#if WITH_EDITOR
	Init();
#endif // #if WITH_EDITOR

	bLoaded = true;
}

void UCsData_StatusEffect_DamagePoint::Unload()
{

}

bool UCsData_StatusEffect_DamagePoint::IsLoaded() const
{
	return bLoaded;
}

#pragma endregion ICsData