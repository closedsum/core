// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#define CS_DECLARE_ATTRIBUTE_PROPERTY_GETTER(__PropertyName) \
	static FGameplayAttribute Get##__PropertyName##Attribute();

#define CS_DEFINE_ATTRIBUTE_PROPERTY_GETTER(__ClassName, __PropertyName) \
	FGameplayAttribute __ClassName::Get##__PropertyName##Attribute() \
	{ \
		static FProperty* __Property = FindFieldChecked<FProperty>(__ClassName::StaticClass(), GET_MEMBER_NAME_CHECKED(__ClassName, __PropertyName)); \
		return __Property; \
	}

#define CS_ATTRIBUTE_VALUE_GETTER(__PropertyName) \
	FORCEINLINE float Get##__PropertyName() const \
	{ \
		return __PropertyName.GetCurrentValue(); \
	}

#define CS_DECLARE_ATTRIBUTE_VALUE_SETTER(__PropertyName) \
	void Set##__PropertyName(const float& __Value);

#define CS_DEFINE_ATTRIBUTE_VALUE_SETTER(__ClassName, __PropertyName) \
	void __ClassName::Set##__PropertyName(const float& __Value) \
	{ \
		UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponentChecked(); \
		\
		ASC->SetNumericAttributeBase(Get##__PropertyName##Attribute(), __Value); \
	}

#define CS_ATTRIBUTE_VALUE_INITTER(__PropertyName) \
	FORCEINLINE void Init##__PropertyName(const float& __Value) \
	{ \
		__PropertyName.SetBaseValue(__Value); \
		__PropertyName.SetCurrentValue(__Value); \
	}