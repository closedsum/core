// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Misc/Build.h"

#define CS_FWD_DECLARE_CACHED_FUNCTION_NAME(__ClassName) namespace N##__ClassName { \
	namespace NCached { \
		namespace NFunction { \
			namespace NName { \
				struct FInfo; } } } }
#define CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_1(__Ns1, __ClassName) namespace __Ns1 { \
	namespace N##__ClassName { \
		namespace NCached { \
			namespace NFunction { \
				namespace NName { \
					struct FInfo; } } } } }
#define CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_2(__Ns1, __Ns2, __ClassName) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace N##__ClassName { \
			namespace NCached { \
				namespace NFunction { \
					namespace NName { \
						struct FInfo; } } } } } }
#define CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_3(__Ns1, __Ns2, __Ns3, __ClassName) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace N##__ClassName { \
				namespace NCached { \
					namespace NFunction { \
						namespace NName { \
							struct FInfo; } } } } } } }
#define CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_4(__Ns1, __Ns2, __Ns3, __Ns4, __ClassName) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace N##__ClassName { \
					namespace NCached { \
						namespace NFunction { \
							namespace NName { \
								struct FInfo; } } } } } } } }
#define CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_5(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __ClassName) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					namespace N##__ClassName { \
						namespace NCached { \
							namespace NFunction { \
								namespace NName { \
									struct FInfo; } } } } } } } } }
#define CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_6(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __ClassName) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					namespace __Ns6 { \
						namespace N##__ClassName { \
							namespace NCached { \
								namespace NFunction { \
									namespace NName { \
										struct FInfo; } } } } } } } } } }
#define CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_7(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __Ns7, __ClassName) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					namespace __Ns6 { \
						namespace __Ns7 { \
							namespace N##__ClassName { \
								namespace NCached { \
									namespace NFunction { \
										namespace NName { \
											struct FInfo; } } } } } } } } } } }
#define CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_8(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __Ns7, __Ns8, __ClassName) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					namespace __Ns6 { \
						namespace __Ns7 { \
							namespace __Ns8 { \
								namespace N##__ClassName { \
									namespace NCached { \
										namespace NFunction { \
											namespace NName { \
												struct FInfo; } } } } } } } } } } }
#define CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_9(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __Ns7, __Ns8, __Ns9, __ClassName) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					namespace __Ns6 { \
						namespace __Ns7 { \
							namespace __Ns8 { \
								namespace __Ns9 { \
									namespace N##__ClassName { \
										namespace NCached { \
											namespace NFunction { \
												namespace NName { \
													struct FInfo; } } } } } } } } } } } }

#define CS_USING_CACHED_FUNCTION_NAME(__ClassName) using _CachedFunctionNameType = N##__ClassName::NCached::NFunction::NName::FInfo
#define CS_USING_CACHED_FUNCTION_NAME_NESTED_1(__Ns1, __ClassName) using _CachedFunctionNameType = __Ns1::N##__ClassName::NCached::NFunction::NName::FInfo
#define CS_USING_CACHED_FUNCTION_NAME_NESTED_2(__Ns1, __Ns2, __ClassName) using _CachedFunctionNameType = __Ns1::__Ns2::N##__ClassName::NCached::NFunction::NName::FInfo
#define CS_USING_CACHED_FUNCTION_NAME_NESTED_3(__Ns1, __Ns2, __Ns3, __ClassName) using _CachedFunctionNameType = __Ns1::__Ns2::__Ns3::N##__ClassName::NCached::NFunction::NName::FInfo
#define CS_USING_CACHED_FUNCTION_NAME_NESTED_4(__Ns1, __Ns2, __Ns3, __Ns4, __ClassName) using _CachedFunctionNameType = __Ns1::__Ns2::__Ns3::__Ns4::N##__ClassName::NCached::NFunction::NName::FInfo
#define CS_USING_CACHED_FUNCTION_NAME_NESTED_5(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __ClassName) using _CachedFunctionNameType = __Ns1::__Ns2::__Ns3::__Ns4::__Ns5::N##__ClassName::NCached::NFunction::NName::FInfo
#define CS_USING_CACHED_FUNCTION_NAME_NESTED_6(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __ClassName) using _CachedFunctionNameType = __Ns1::__Ns2::__Ns3::__Ns4::__Ns5::__Ns6::N##__ClassName::NCached::NFunction::NName::FInfo
#define CS_USING_CACHED_FUNCTION_NAME_NESTED_7(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __Ns7, __ClassName) using _CachedFunctionNameType = __Ns1::__Ns2::__Ns3::__Ns4::__Ns5::__Ns6::__Ns7::N##__ClassName::NCached::NFunction::NName::FInfo
#define CS_USING_CACHED_FUNCTION_NAME_NESTED_8(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __Ns7, __Ns8, __ClassName) using _CachedFunctionNameType = __Ns1::__Ns2::__Ns3::__Ns4::__Ns5::__Ns6::__Ns7::__Ns8::N##__ClassName::NCached::NFunction::NName::FInfo
#define CS_USING_CACHED_FUNCTION_NAME_NESTED_9(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __Ns7, __Ns8, __Ns9, __ClassName) using _CachedFunctionNameType = __Ns1::__Ns2::__Ns3::__Ns4::__Ns5::__Ns6::__Ns7::__Ns8::__Ns9::N##__ClassName::NCached::NFunction::NName::FInfo

#define CS_START_CACHED_FUNCTION_NAME(__ClassName) namespace N##__ClassName { \
	namespace NCached { \
		namespace NFunction { \
			namespace NName { \
				struct FInfo \
				{ \
					public:
#define CS_END_CACHED_FUNCTION_NAME }; } } } }
#define CS_START_CACHED_FUNCTION_NAME_NESTED_1(__Ns1, __ClassName) namespace __Ns1 { \
	namespace N##__ClassName { \
		namespace NCached { \
			namespace NFunction { \
				namespace NName { \
					struct FInfo \
					{ \
						public:
#define CS_END_CACHED_FUNCTION_NAME_NESTED_1 }; } } } } }
#define CS_START_CACHED_FUNCTION_NAME_NESTED_2(__Ns1, __Ns2, __ClassName) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace N##__ClassName { \
			namespace NCached { \
				namespace NFunction { \
					namespace NName { \
						struct FInfo \
						{ \
							public:
#define CS_END_CACHED_FUNCTION_NAME_NESTED_2 }; } } } } } }
#define CS_START_CACHED_FUNCTION_NAME_NESTED_3(__Ns1, __Ns2, __Ns3, __ClassName) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace N##__ClassName { \
				namespace NCached { \
					namespace NFunction { \
						namespace NName { \
							struct FInfo \
							{ \
								public:
#define CS_END_CACHED_FUNCTION_NAME_NESTED_3 }; } } } } } } }
#define CS_START_CACHED_FUNCTION_NAME_NESTED_4(__Ns1, __Ns2, __Ns3, __Ns4, __ClassName) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace N##__ClassName { \
					namespace NCached { \
						namespace NFunction { \
							namespace NName { \
								struct FInfo \
								{ \
									public:
#define CS_END_CACHED_FUNCTION_NAME_NESTED_4 }; } } } } } } } }
#define CS_START_CACHED_FUNCTION_NAME_NESTED_5(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __ClassName) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					namespace N##__ClassName { \
						namespace NCached { \
							namespace NFunction { \
								namespace NName { \
									struct FInfo \
									{ \
										public:
#define CS_END_CACHED_FUNCTION_NAME_NESTED_5 }; } } } } } } } } }
#define CS_START_CACHED_FUNCTION_NAME_NESTED_6(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __ClassName) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					namespace __Ns6 { \
						namespace N##__ClassName { \
							namespace NCached { \
								namespace NFunction { \
									namespace NName { \
										struct FInfo \
										{ \
											public:
#define CS_END_CACHED_FUNCTION_NAME_NESTED_6 }; } } } } } } } } } }
#define CS_START_CACHED_FUNCTION_NAME_NESTED_7(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __Ns7, __ClassName) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					namespace __Ns6 { \
						namespace __Ns7 { \
							namespace N##__ClassName { \
								namespace NCached { \
									namespace NFunction { \
										namespace NName { \
											struct FInfo \
											{ \
												public:
#define CS_END_CACHED_FUNCTION_NAME_NESTED_7 }; } } } } } } } } } } }
#define CS_START_CACHED_FUNCTION_NAME_NESTED_8(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __Ns7, __Ns8, __ClassName) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					namespace __Ns6 { \
						namespace __Ns7 { \
							namespace __Ns8 { \
								namespace N##__ClassName { \
									namespace NCached { \
										namespace NFunction { \
											namespace NName { \
												struct FInfo \
												{ \
													public:
#define CS_END_CACHED_FUNCTION_NAME_NESTED_8 }; } } } } } } } } } } } }
#define CS_START_CACHED_FUNCTION_NAME_NESTED_9(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __Ns7, __Ns8, __Ns9, __ClassName) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					namespace __Ns6 { \
						namespace __Ns7 { \
							namespace __Ns8 { \
								namespace __Ns9 { \
									namespace N##__ClassName { \
										namespace NCached { \
											namespace NFunction { \
												namespace NName { \
													struct FInfo \
													{ \
														public:
#define CS_END_CACHED_FUNCTION_NAME_NESTED_9 }; } } } } } } } } } } } }

#define CS_MACRO_CACHED_STRINGIFY(x) #x

#if !UE_BUILD_SHIPPING
#define CS_DEFINE_CACHED_FUNCTION_NAME(__ClassName, __FunctionName) static const FString& Get_STRING_##__FunctionName() \
	{ \
		static FString Name = CS_MACRO_CACHED_STRINGIFY(__ClassName::__FunctionName); \
		return Name; \
	} \
	static const FName& Get_NAME_##__FunctionName() \
	{ \
		static FName Name = CS_MACRO_CACHED_STRINGIFY(__ClassName::__FunctionName); \
		return Name; \
	}
#else
#define CS_DEFINE_CACHED_FUNCTION_NAME(__ClassName, __FunctionName) static const FString& Get_STRING_##__FunctionName() \
	{ \
		static FString Name = TEXT(""); \
		return Name; \
	} \
	static const FName& Get_NAME_##__FunctionName() \
	{ \
		static FName Name = NAME_None; \
		return Name; \
	}
#endif // #if !UE_BUILD_SHIPPING 

#define CS_SET_CONTEXT_AS_FUNCTION_NAME(__FunctionName) const FString& Context = _CachedFunctionNameType::Get_STRING_##__FunctionName()
#define CS_SET_CTXT_AS_FUNCTION_NAME(__FunctionName) const FString& Ctxt = _CachedFunctionNameType::Get_STRING_##__FunctionName()
#define CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(__FunctionName) const FString& Ctxt = Context.IsEmpty() ? _CachedFunctionNameType::Get_STRING_##__FunctionName() : Context