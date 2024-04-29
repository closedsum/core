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