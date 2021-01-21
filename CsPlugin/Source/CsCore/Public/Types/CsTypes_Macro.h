// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
//#include "CsTypes_Macro.generated.h"
#pragma once

#define CS_EMPTY 0
#define CS_FIRST 0
#define CS_SINGLETON 1

#define CS_INVALID_LOOK_UP_CODE 255
#define CS_INVALID_LOOK_UP_CODE_MAX 65535

#define CS_INT32_BIT_MAX 15
#define CS_UINT32_BIT_MAX 31
#define CS_INT64_BIT_MAX 31
#define CS_UINT64_BIT_MAX 63

#define CS_TEST_BLUEPRINT_BITFLAG(Bitmask, Bit) (((Bitmask) & (1 << static_cast<uint32>(Bit))) > 0)
#define CS_SET_BLUEPRINT_BITFLAG(Bitmask, Bit) (Bitmask |= 1 << static_cast<uint32>(Bit))
#define CS_CLEAR_BLUEPRINT_BITFLAG(Bitmask, Bit) (Bitmask &= ~(1 << static_cast<uint32>(Bit)))

#define CS_TEST_BITFLAG(Bitmask, Bit) ((Bitmask & static_cast<uint32>(Bit)) == static_cast<uint32>(Bit))
#define CS_SET_BITFLAG(Bitmask, Bit) (Bitmask |= static_cast<uint32>(Bit))
#define CS_CLEAR_BITFLAG(Bitmask, Bit) (Bitmask &= ~static_cast<uint32>(Bit))

#if !UE_BUILD_SHIPPING
#define CS_NON_SHIPPING_EXPR(__Expr) __Expr
#else
#define CS_NON_SHIPPING_EXPR(__Expr)
#endif //#if !UE_BUILD_SHIPPING

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

#define CS_FWD_DECLARE_CLASS_NAMESPACE_1(__Ns1, __Class) namespace __Ns1 { class __Class; }
#define CS_FWD_DECLARE_CLASS_NAMESPACE_2(__Ns1, __Ns2, __Class) namespace __Ns1 { \
	namespace __Ns2 { \
		class __Class; } }
#define CS_FWD_DECLARE_CLASS_NAMESPACE_3(__Ns1, __Ns2, __Ns3, __Class) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			class __Class; } } }
#define CS_FWD_DECLARE_CLASS_NAMESPACE_4(__Ns1, __Ns2, __Ns3, __Ns4, __Class) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
			class __Class; } } } }
#define CS_FWD_DECLARE_CLASS_NAMESPACE_5(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Class) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					class __Class; } } } } }
#define CS_FWD_DECLARE_CLASS_NAMESPACE_6(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __Class) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					namespace __Ns6 { \
						class __Class; } } } } } }

#define CS_FWD_DECLARE_STRUCT_NAMESPACE_1(__Ns1, __Struct) namespace __Ns1 { struct __Struct; }
#define CS_FWD_DECLARE_STRUCT_NAMESPACE_2(__Ns1, __Ns2, __Struct) namespace __Ns1 { \
	namespace __Ns2 { \
		struct __Struct; } }
#define CS_FWD_DECLARE_STRUCT_NAMESPACE_3(__Ns1, __Ns2, __Ns3, __Struct) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			struct __Struct; } } }
#define CS_FWD_DECLARE_STRUCT_NAMESPACE_4(__Ns1, __Ns2, __Ns3, __Ns4, __Struct) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
			struct __Struct; } } } }
#define CS_FWD_DECLARE_STRUCT_NAMESPACE_5(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Struct) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					struct __Struct; } } } } }
#define CS_FWD_DECLARE_STRUCT_NAMESPACE_6(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __Struct) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					namespace __Ns6 { \
						struct __Struct; } } } } } }

#define CS_FWD_DECLARE_ENUM_CLASS_UINT8_NAMESPACE_1(__Ns1, __Enum) namespace __Ns1 { enum class __Enum : uint8; }
#define CS_FWD_DECLARE_ENUM_CLASS_UINT8_NAMESPACE_2(__Ns1, __Ns2, __Enum) namespace __Ns1 { \
	namespace __Ns2 { \
		enum class __Enum : uint8; } }
#define CS_FWD_DECLARE_ENUM_CLASS_UINT8_NAMESPACE_3(__Ns1, __Ns2, __Ns3, __Enum) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			enum class __Enum : uint8; } } }
#define CS_FWD_DECLARE_ENUM_CLASS_UINT8_NAMESPACE_4(__Ns1, __Ns2, __Ns3, __Ns4, __Enum) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
			enum class __Enum : uint8; } } } }
#define CS_FWD_DECLARE_ENUM_CLASS_UINT8_NAMESPACE_5(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Enum) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					enum class __Enum : uint8; } } } } }
#define CS_FWD_DECLARE_ENUM_CLASS_UINT8_NAMESPACE_6(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __Enum) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					namespace __Ns6 { \
						enum class __Enum : uint8; } } } } } }