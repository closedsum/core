// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CoreMinimal.h"

#define CS_EMPTY 0
#define CS_FIRST 0
#define CS_SINGLETON 1

#define CS_INVALID_LOOK_UP_CODE 255
#define CS_INVALID_LOOK_UP_CODE_MAX 65535

#if !UE_BUILD_SHIPPING
#define CS_NON_SHIPPING_EXPR(__Expr) __Expr
#else
#define CS_NON_SHIPPING_EXPR(__Expr)
#endif // #if !UE_BUILD_SHIPPING

#if WITH_EDITOR
#define CS_EDITOR_EXPR(__Expr) __Expr
#else
#define CS_EDITOR_EXPR(__Expr)
#endif // #if WITH_EDITOR

#if !UE_BUILD_SHIPPING
#define CS_CONDITIONAL_LOG(__Str) if (Log) \
	Log(__Str);
#else
#define CS_CONDITIONAL_LOG(__Str)
#endif // #if !UE_BUILD_SHIPPING

#define CS_STRINGIFY(x) #x

#define CS_DEFINE_FUNCTION_NAME_AS_STRING(ClassName, FunctionName) const FString FunctionName = CS_STRINGIFY(ClassName::FunctionName) 

#if !UE_BUILD_SHIPPING
#define CS_DEFINE_CACHED_STRING(VariableName, StringValue) const FString VariableName = TEXT(StringValue)
#define CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ClassName, FunctionName) const FString FunctionName = CS_STRINGIFY(ClassName::FunctionName) 
#else
#define CS_DEFINE_CACHED_STRING(VariableName, StringValue) const FString VariableName = TEXT("")
#define CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(ClassName, FunctionName) const FString FunctionName = TEXT("")
#endif // #if !UE_BUILD_SHIPPING

#if !UE_BUILD_SHIPPING
#define CS_DEFINE_CACHED_NAME(VariableName, NameValue) const FName VariableName = FName(NameValue)
#define CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(ClassName, FunctionName) const FName FunctionName = FName(CS_STRINGIFY(ClassName::FunctionName))
#else
#define CS_DEFINE_CACHED_NAME(VariableName, NameValue) const FName VariableName = NAME_None
#define CS_DEFINE_CACHED_FUNCTION_NAME_AS_NAME(ClassName, FunctionName) const FName FunctionName = NAME_None
#endif // #if !UE_BUILD_SHIPPING

#define CS_SAFE_DELETE_PTR(__ptr) \
	if (__ptr) \
	{ \
		delete __ptr; \
		__ptr = nullptr; \
	}

#define CS_DECLARE_MEMBER_WITH_PROXY(__Member, __ValueType) \
	__ValueType __Member; \
	__ValueType* __Member##_Proxy;

#define CS_CTOR_INIT_MEMBER_WITH_PROXY(__Member, __Value) \
	__Member(__Value), \
	__Member##_Proxy(nullptr)

#define CS_CTOR_INIT_MEMBER_ARRAY_WITH_PROXY(__Member) \
	__Member(), \
	__Member##_Proxy(nullptr)

#define CS_CTOR_INIT_MEMBER_STRUCT_WITH_PROXY(__Member) \
	__Member(), \
	__Member##_Proxy(nullptr)

#define CS_CTOR_INIT_MEMBER_ENUM_STRUCT_WITH_PROXY(__Member) \
	__Member(), \
	__Member##_Proxy(nullptr)

#define CS_CTOR_SET_MEMBER_PROXY(__Member) __Member##_Proxy = &__Member

#define CS_RESET_MEMBER_WITH_PROXY(__Member, __Value) \
	__Member = __Value; \
	__Member##_Proxy = &__Member;

#define CS_RESET_MEMBER_ARRAY_WITH_PROXY(__Member) \
	__Member.Reset(__Member.Max()); \
	__Member##_Proxy = &__Member;

#define CS_RESET_MEMBER_SET_WITH_PROXY(__Member) \
	__Member.Reset(); \
	__Member##_Proxy = &__Member;

#define CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(__Member, __ValueType) \
	FORCEINLINE void Set##__Member(const __ValueType& __value) \
	{ \
		__Member = __value; \
		__Member##_Proxy = &__Member; \
	} \
	FORCEINLINE void Set##__Member(__ValueType* __value) { check(__value); __Member##_Proxy = __value; } \
	FORCEINLINE const __ValueType& Get##__Member() const { return *(__Member##_Proxy); } \
	FORCEINLINE __ValueType* Get##__Member##Ptr() const { return __Member##_Proxy; }

#define CS_DEFINE_SET_MEMBER_WITH_PROXY(__Member, __ValueType) \
	FORCEINLINE void Set##__Member(const __ValueType& __value) \
	{ \
		__Member = __value; \
		__Member##_Proxy = &__Member; \
	} \
	FORCEINLINE void Set##__Member(__ValueType* __value) \
	{ \
		check(__value); \
		__Member##_Proxy = __value; \
	}

#define CS_DEFINE_SET_GET_MEMBER_PTR_WITH_PROXY(__Member, __ValueType) \
	FORCEINLINE void Set##__Member(__ValueType* __value) \
	{ \
		__Member = __value; \
		__Member##_Proxy = &__Member; \
	} \
	FORCEINLINE void Set##__Member(__ValueType** __value) \
	{ \
		check(__value); \
		__Member##_Proxy = __value; \
	} \
	FORCEINLINE __ValueType* Get##__Member() const { return *(__Member##_Proxy); }

#define CS_COPY_TO_PROXY(__Proxy, __Member) __Proxy->Set##__Member(&__Member)
#define CS_COPY_TO_PROXY_AS_VALUE(__Proxy, __Member) __Proxy->Set##__Member(__Member)
#define CS_COPY_PTR_TO_PROXY(__Proxy, __Member) __Proxy->Set##__Member(__Member.GetPtr())
#define CS_COPY_PTR_TO_PROXY_AS_VALUE(__Proxy, __Member) __Proxy->Set##__Member(__Member.Get())
#define CS_COPY_CLASS_PTR_TO_PROXY(__Proxy, __Member) __Proxy->Set##__Member(__Member.GetClassPtr())
#define CS_COPY_CLASS_PTR_TO_PROXY_AS_VALUE(__Proxy, __Member) __Proxy->Set##__Member(__Member.GetClass())
#define CS_COPY_INFO_TO_PROXY_PTR(__Proxy, __Member) __Member.CopyToInfo(__Proxy->Get##__Member##Ptr())
#define CS_COPY_INFO_TO_PROXY_PTR_AS_VALUE(__Proxy, __Member) __Member.CopyToInfoAsValue(__Proxy->Get##__Member##Ptr())
#define CS_COPY_PARAMS_TO_PROXY_PTR(__Proxy, __Member) __Member.CopyToParams(__Proxy->Get##__Member##Ptr())
#define CS_COPY_PARAMS_TO_PROXY_PTR_AS_VALUE(__Proxy, __Member) __Member.CopyToParamsAsValue(__Proxy->Get##__Member##Ptr())
#define CS_COPY_SETTINGS_TO_PROXY_PTR(__Proxy, __Member) __Member.CopyToSettings(__Proxy->Get##__Member##Ptr())
#define CS_COPY_SETTINGS_TO_PROXY_PTR_AS_VALUE(__Proxy, __Member) __Member.CopyToSettingsAsValue(__Proxy->Get##__Member##Ptr())
#define CS_COPY_TYPE_TO_PROXY(__Proxy, __Member, __Type) __Proxy->Set##__Member((__Type*)&__Member)
#define CS_COPY_TYPE_TO_PROXY_AS_VALUE(__Proxy, __Member, __Type) __Proxy->Set##__Member((__Type)__Member)

#define CS_COPY_PROXY_TO_PROXY_AS_VALUE(__Proxy, __Member) Set##__Member(__Proxy.Get##__Member())
#define CS_COPY_CUSTOM_PROXY_TO_PROXY_PTR_AS_VALUE(__Proxy, __Member) Get##__Member##Ptr()->Copy(__Proxy.Get##__Member())

#define CS_DEFINE_IS_PROXY_PTR_DEFAULT_CHECKED(__Member) \
	FORCEINLINE bool IsProxyPtrDefault_##__Member##_Checked(const FString& Context) const \
	{ \
		static const FString __temp__str__ = #__Member; \
		static const FString __temp__str__proxy__ = CS_STRINGIFY(__Member##_Proxy); \
		checkf(__Member##_Proxy == &__Member, TEXT("%s: %s does NOT reference %s."), *Context, *__temp__str__proxy__, *__temp__str__); \
		return true; \
	}

// Assume const FString& Context has been defined
#define CS_IS_PROXY_PTR_DEFAULT_CHECKED(__Member) check(IsProxyPtrDefault_##__Member##_Checked(Context))

#define CS_ADD_TO_DYNAMIC_MULITCAST_DELEGATE(__Context, __Owner, __MulticastDelegate, __Delegate, __Log) \
	if (__Delegate.IsBound()) \
	{ \
		if (!__Owner->__MulticastDelegate.Contains(__Delegate)) \
		{ \
			__Owner->__MulticastDelegate.Add(__Delegate); \
		} \
		else \
		{ \
			static const FString __temp__str__ = #__MulticastDelegate; \
			UE_LOG(__Log, Warning, TEXT("%s: Delegate has already been added to %s."), *__Context, *__temp__str__); \
		} \
	} \
	else \
	{ \
		UE_LOG(__Log, Warning, TEXT("%s: Delegate is NOT bound to anything."), *__Context); \
	}