// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

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

// Assume there is a pointer to a member named This
#define CS_THIS_COPY_TO_PROXY(__Proxy, __Member) __Proxy->Set##__Member(&(This->__Member))
#define CS_THIS_COPY_TO_PROXY_AS_VALUE(__Proxy, __Member) __Proxy->Set##__Member(This->__Member)
#define CS_THIS_COPY_PTR_TO_PROXY(__Proxy, __Member) __Proxy->Set##__Member(This->__Member.GetPtr())
#define CS_THIS_COPY_PTR_TO_PROXY_AS_VALUE(__Proxy, __Member) __Proxy->Set##__Member(This->__Member.Get())
#define CS_THIS_COPY_CLASS_PTR_TO_PROXY(__Proxy, __Member) __Proxy->Set##__Member(This->__Member.GetClassPtr())
#define CS_THIS_COPY_CLASS_PTR_TO_PROXY_AS_VALUE(__Proxy, __Member) __Proxy->Set##__Member(This->__Member.GetClass())
#define CS_THIS_COPY_INFO_TO_PROXY_PTR(__Proxy, __Member) This->__Member.CopyToInfo(__Proxy->Get##__Member##Ptr())
#define CS_THIS_COPY_INFO_TO_PROXY_PTR_AS_VALUE(__Proxy, __Member) This->__Member.CopyToInfoAsValue(__Proxy->Get##__Member##Ptr())
#define CS_THIS_COPY_PARAMS_TO_PROXY_PTR(__Proxy, __Member) This->__Member.CopyToParams(__Proxy->Get##__Member##Ptr())
#define CS_THIS_COPY_PARAMS_TO_PROXY_PTR_AS_VALUE(__Proxy, __Member) This->__Member.CopyToParamsAsValue(__Proxy->Get##__Member##Ptr())
#define CS_THIS_COPY_SETTINGS_TO_PROXY_PTR(__Proxy, __Member) This->__Member.CopyToSettings(__Proxy->Get##__Member##Ptr())
#define CS_THIS_COPY_SETTINGS_TO_PROXY_PTR_AS_VALUE(__Proxy, __Member) This->__Member.CopyToSettingsAsValue(__Proxy->Get##__Member##Ptr())
#define CS_THIS_COPY_TYPE_TO_PROXY(__Proxy, __Member, __Type) __Proxy->Set##__Member((__Type*)&(This->__Member))
#define CS_THIS_COPY_TYPE_TO_PROXY_AS_VALUE(__Proxy, __Member, __Type) __Proxy->Set##__Member((__Type)This->__Member)

#define CS_THIS_COPY_PROXY_TO_PROXY_AS_VALUE(__Proxy, __Member) This->Set##__Member(__Proxy.Get##__Member())
#define CS_THIS_COPY_CUSTOM_PROXY_TO_PROXY_PTR_AS_VALUE(__Proxy, __Member) This->Get##__Member##Ptr()->Copy(__Proxy.Get##__Member())

#define CS_PROXY_STRINGIFY(x) #x

#define CS_DEFINE_IS_PROXY_PTR_DEFAULT_CHECKED(__Member) \
	FORCEINLINE bool IsProxyPtrDefault_##__Member##_Checked(const FString& Context) const \
	{ \
		static const FString __temp__str__ = #__Member; \
		static const FString __temp__str__proxy__ = CS_PROXY_STRINGIFY(__Member##_Proxy); \
		checkf(__Member##_Proxy == &__Member, TEXT("%s: %s does NOT reference %s."), *Context, *__temp__str__proxy__, *__temp__str__); \
		return true; \
	}

// Assume const FString& Context has been defined
#define CS_IS_PROXY_PTR_DEFAULT_CHECKED(__Member) check(IsProxyPtrDefault_##__Member##_Checked(Context))