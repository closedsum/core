// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

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
#define CS_FWD_DECLARE_CLASS_NAMESPACE_7(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __Ns7, __Class) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					namespace __Ns6 { \
						namespace __Ns7 { \
							class __Class; } } } } } } }
#define CS_FWD_DECLARE_CLASS_NAMESPACE_8(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __Ns7, __Ns8, __Class) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					namespace __Ns6 { \
						namespace __Ns7 { \
							namespace __Ns8 { \
								class __Class; } } } } } } } }
#define CS_FWD_DECLARE_CLASS_NAMESPACE_9(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __Ns7, __Ns8, __Ns9, __Class) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					namespace __Ns6 { \
						namespace __Ns7 { \
							namespace __Ns8 { \
								namespace __Ns9 { \
									class __Class; } } } } } } } } }

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
#define CS_FWD_DECLARE_STRUCT_NAMESPACE_7(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __Ns7, __Struct) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					namespace __Ns6 { \
						namespace __Ns7 { \
							struct __Struct; } } } } } } }
#define CS_FWD_DECLARE_STRUCT_NAMESPACE_8(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __Ns7, __Ns8, __Struct) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					namespace __Ns6 { \
						namespace __Ns7 { \
							namespace __Ns8 { \
								struct __Struct; } } } } } } } }
#define CS_FWD_DECLARE_STRUCT_NAMESPACE_9(__Ns1, __Ns2, __Ns3, __Ns4, __Ns5, __Ns6, __Ns7, __Ns8, __Ns9, __Struct) namespace __Ns1 { \
	namespace __Ns2 { \
		namespace __Ns3 { \
			namespace __Ns4 { \
				namespace __Ns5 { \
					namespace __Ns6 { \
						namespace __Ns7 { \
							namespace __Ns8 { \
								namespace __Ns9 { \
									struct __Struct; } } } } } } } } }

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