// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsMacro_Log.h"
#include "CsMacro_Proxy.h"
#include "Types/Enum/CsEnumMap.h"
// Log
#include "Utility/CsFXLog.h"

namespace NCsFX
{
	namespace NParameter
	{
		/**
		*/
		enum class EValue : uint8 
		{
			Int,
			Float,
			Vector,
			EValue_MAX
		};

		struct CSFX_API EMValue final : public TCsEnumMap<EValue>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMValue, EValue)
		};

		namespace NValue
		{
			typedef EValue Type;

			namespace Ref
			{
				extern CSFX_API const Type Int;
				extern CSFX_API const Type Float;
				extern CSFX_API const Type Vector;
				extern CSFX_API const Type EValue_MAX;
			}

			extern CSFX_API const uint8 MAX;

			FORCEINLINE uint32 GetSizeInBytes(const Type& InType)
			{
				if (InType == Type::Int)
					return sizeof(int32);
				if (InType == Type::Float)
					return sizeof(float);
				if (InType == Type::Vector)
					return sizeof(FVector3f);
				checkf(0, TEXT("NCsFX::NParameter::NValue::GetSizeInBytes: InType is NOT Valid."));
				return 0;
			}
		}
	}
}

using CsFXParameterValueType = NCsFX::NParameter::EValue;
using CsFXParameterValueMapType = NCsFX::NParameter::EMValue;

namespace NCsFX
{
	namespace NParameter
	{
		/**
		*/
		struct CSFX_API IParameter
		{
		private:

			// Allow clearer names without name collisions
			struct _
			{
				using ParameterValueType = NCsFX::NParameter::EValue;
			};

		public:

			virtual ~IParameter() {}

			virtual const int32& GetIndex() const = 0;

			virtual const FName& GetName() const = 0;

			virtual const _::ParameterValueType& GetValueType() const = 0;

			virtual void* GetValuePtr() const = 0;

			virtual uint32 GetSizeInBytes() const = 0;
		};
	}
}

using CsFXParameterType = NCsFX::NParameter::IParameter;

namespace NCsFX
{
	namespace NParameter
	{
		namespace NInt
		{
			using ParameterType = NCsFX::NParameter::IParameter;

			/**
			* Container holding information for Niagara Int Parameter
			*/
			struct CSFX_API FIntType : ParameterType
			{
			private:

				using ParameterValueType = NCsFX::NParameter::EValue;
				using ParameterValueMapType = NCsFX::NParameter::EMValue;

				int32 Index;

				CS_DECLARE_MEMBER_WITH_PROXY(Name, FName)

			public:

				ParameterValueType ValueType;

			private:

				CS_DECLARE_MEMBER_WITH_PROXY(Value, int32)

			public:

				FIntType() :
					Index(INDEX_NONE),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Name, NAME_None),
					ValueType(ParameterValueType::Int),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0)
				{
					CS_CTOR_SET_MEMBER_PROXY(Name);
					CS_CTOR_SET_MEMBER_PROXY(Value);
				}

				FORCEINLINE void SetIndex(const int32& InIndex) { Index = InIndex; }

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Name, FName)

				FORCEINLINE void SetValue(const int32& __value)
				{
					Value = __value;
					Value_Proxy = &Value;
				}
				FORCEINLINE void SetValue(int32* __value) { check(__value); Value_Proxy = __value; }
				FORCEINLINE const int32& GetValue() const { return *Value_Proxy; }

			// ParameterType (NCsFX::NParameter::IParameter)
			#pragma region
			public:

				FORCEINLINE const int32& GetIndex() const { return Index; }
				FORCEINLINE const ParameterValueType& GetValueType() const { return ValueType; }
				FORCEINLINE void* GetValuePtr() const { return (void*)const_cast<int32*>(Value_Proxy); }
				FORCEINLINE uint32 GetSizeInBytes() const { return sizeof(int32); }

			#pragma endregion ParameterType (NCsFX::NParameter::IParameter)

				FORCEINLINE bool IsValidChecked(const FString& Context) const
				{
					// Check Name is Valid
					checkf(GetName() != NAME_None, TEXT("%s: GetName(): None is NOT Valid."), *Context);

					const FString NameAsString = GetName().ToString();

					checkf(NameAsString.StartsWith(TEXT("User.")), TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Parameter Name."), *Context, *NameAsString);
					// Check ValueType is Valid
					checkf(ValueType == ParameterValueType::Int, TEXT("%s: ValueType: %s is NOT Int."), *Context, ParameterValueMapType::Get().ToChar(ValueType));
					return true;
				}
			};
		}
	}
}

using CsFXIntParameterType = NCsFX::NParameter::NInt::FIntType;

namespace NCsFX
{
	namespace NParameter
	{
		namespace NFloat
		{
			using ParameterType = NCsFX::NParameter::IParameter;

			/**
			* Container holding information for Niagara Float Parameter
			*/
			struct CSFX_API FFloatType : ParameterType
			{
			private:

				using ParameterValueType = NCsFX::NParameter::EValue;
				using ParameterValueMapType = NCsFX::NParameter::EMValue;

				int32 Index;

				CS_DECLARE_MEMBER_WITH_PROXY(Name, FName)

			public:

				ParameterValueType ValueType;

			private:

				CS_DECLARE_MEMBER_WITH_PROXY(Value, float)

			public:

				FFloatType() :
					Index(INDEX_NONE),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Name, NAME_None),
					ValueType(ParameterValueType::Float),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0.0f)
				{
					CS_CTOR_SET_MEMBER_PROXY(Name);
					CS_CTOR_SET_MEMBER_PROXY(Value);
				}

				FORCEINLINE void SetIndex(const int32& InIndex) { Index = InIndex; }

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Name, FName)

				FORCEINLINE void SetValue(const float& __value)
				{
					Value = __value;
					Value_Proxy = &Value;
				}
				FORCEINLINE void SetValue(float* __value) { check(__value); Value_Proxy = __value; }
				FORCEINLINE const float& GetValue() const { return *Value_Proxy; }

			// ParameterType (NCsFX::NParameter::IParameter)
			#pragma region
			public:

				FORCEINLINE const int32& GetIndex() const { return Index; }
				FORCEINLINE const ParameterValueType& GetValueType() const { return ValueType; }
				FORCEINLINE void* GetValuePtr() const { return (void*)const_cast<float*>(Value_Proxy); }
				FORCEINLINE uint32 GetSizeInBytes() const { return sizeof(float); }

			#pragma endregion ParameterType (NCsFX::NParameter::IParameter)

				FORCEINLINE bool IsValidChecked(const FString& Context) const
				{
					// Check Name is Valid
					checkf(GetName() != NAME_None, TEXT("%s: GetName(): None is NOT Valid."), *Context);
					// Check ValueType is Valid
					checkf(ValueType == ParameterValueType::Float, TEXT("%s: ValueType: %s is NOT Float."), *Context, ParameterValueMapType::Get().ToChar(ValueType));
					return true;
				}
			};
		}
	}
}

namespace NCsFX
{
	namespace NParameter
	{
		namespace NVector
		{
			using ParameterType = NCsFX::NParameter::IParameter;

			/**
			* Container holding information for Niagara Vector Parameter
			*/
			struct CSFX_API FVectorType : ParameterType
			{
			private:

				using ParameterValueType = NCsFX::NParameter::EValue;
				using ParameterValueMapType = NCsFX::NParameter::EMValue;

				int32 Index;

				CS_DECLARE_MEMBER_WITH_PROXY(Name, FName)

			public:

				ParameterValueType ValueType;

			private:

				CS_DECLARE_MEMBER_WITH_PROXY(Value, FVector3f)

			public:

				FVectorType() :
					Index(INDEX_NONE),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Name, NAME_None),
					ValueType(ParameterValueType::Vector),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Value, 0.0f)
				{
					CS_CTOR_SET_MEMBER_PROXY(Name);
					CS_CTOR_SET_MEMBER_PROXY(Value);
				}

				FORCEINLINE void SetIndex(const int32& InIndex) { Index = InIndex; }

				CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Name, FName)

				FORCEINLINE void SetValue(const FVector3f& __value)
				{
					Value = __value;
					Value_Proxy = &Value;
				}
				FORCEINLINE void SetValue(FVector3f* __value) { check(__value); Value_Proxy = __value; }
				FORCEINLINE const FVector3f& GetValue() const { return *Value_Proxy; }

			// ParameterType (NCsFX::NParameter::IParameter)
			#pragma region
			public:

				FORCEINLINE const int32& GetIndex() const { return Index; }
				FORCEINLINE const ParameterValueType& GetValueType() const { return ValueType; }
				FORCEINLINE void* GetValuePtr() const { return (void*)const_cast<FVector3f*>(Value_Proxy); }
				FORCEINLINE uint32 GetSizeInBytes() const { return sizeof(FVector3f); }

			#pragma endregion ParameterType (NCsFX::NParameter::IParameter)

				FORCEINLINE bool IsValidChecked(const FString& Context) const
				{
					// Check Name is Valid
					checkf(GetName() != NAME_None, TEXT("%s: GetName(): None is NOT Valid."), *Context);
					// Check ValueType is Valid
					checkf(ValueType == ParameterValueType::Vector, TEXT("%s: ValueType: %s is NOT Vector."), *Context, ParameterValueMapType::Get().ToChar(ValueType));
					return true;
				}
			};
		}
	}
}

namespace NCsFX
{
	namespace NParameter
	{
		namespace NScaled
		{
			struct CSFX_API IScaled
			{
			private:

				// Allow clearer names without name collisions
				struct _
				{
					using ParameterType = NCsFX::NParameter::IParameter;
				};

			public:

				virtual ~IScaled() {}

				virtual const int32& GetIndex() const = 0;

				virtual const _::ParameterType* GetParameter() const = 0;

				/** 
				* Whether Value should be used for applying any scaling or just
				* use the default Value from the FX System. 
				*
				* return
				*/
				virtual const bool& ShouldSetValue() const = 0;

				/**
				* Whether to apply the FX scale inversely.
				* 
				* return
				*/
				virtual const bool& ShouldApplyInverse() const = 0;

				/** 
				* Additional scale to apply to Parameter.
				* 
				* return
				*/
				virtual const float& GetScale() const = 0;
			};
		}
	}
}

using CsFXScaledParameterType = NCsFX::NParameter::NScaled::IScaled;

namespace NCsFX
{
	namespace NParameter
	{
		namespace NScaled
		{
			namespace NInt
			{
				using ScaledType = NCsFX::NParameter::NScaled::IScaled;

				/**
				* Container holding information for Niagara Int Parameter that will scale based on the FX scale.
				*/
				struct CSFX_API FIntType : ScaledType
				{
					using ParameterType = NCsFX::NParameter::IParameter;
					using IntParameterType = NCsFX::NParameter::NInt::FIntType;

				private:

					int32 Index;

				public:

					IntParameterType Parameter;

				private:

					/** Whether Value should be used for applying any scaling or just
						use the default Value from the FX System. */
					CS_DECLARE_MEMBER_WITH_PROXY(bValue, bool)
					/** Whether to apply the FX scale inversely. */
					CS_DECLARE_MEMBER_WITH_PROXY(bInverse, bool)
					/** Additional scale to apply to Parameter. */
					CS_DECLARE_MEMBER_WITH_PROXY(Scale, float)

				public:

					FIntType() :
						Index(INDEX_NONE),
						Parameter(),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(bValue, true),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(bInverse, false),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Scale, 1.0f)
					{
						CS_CTOR_SET_MEMBER_PROXY(bValue);
						CS_CTOR_SET_MEMBER_PROXY(bInverse);
						CS_CTOR_SET_MEMBER_PROXY(Scale);
					}

					FORCEINLINE void SetIndex(const int32& InIndex) 
					{ 
						Index = InIndex;

						Parameter.SetIndex(Index);
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bValue, bool)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bInverse, bool)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Scale, float)

					FORCEINLINE IntParameterType* GetParameterPtr() { return &Parameter; }

				// IScaled
				#pragma region
				public:

					FORCEINLINE const int32& GetIndex() const { return Index; }
					FORCEINLINE const ParameterType* GetParameter() const { return &Parameter; }
					FORCEINLINE const bool& ShouldSetValue() const { return GetbValue(); }
					FORCEINLINE const bool& ShouldApplyInverse() const { return GetbInverse(); }
					//FORCEINLINE const float& GetScale() const;

				#pragma endregion IScaled

					FORCEINLINE bool IsValidChecked(const FString& Context) const
					{
						check(Parameter.IsValidChecked(Context));
						return true;
					}
				};
			}
		}
	}
}

namespace NCsFX
{
	namespace NParameter
	{
		namespace NScaled
		{
			namespace NFloat
			{
				using ScaledType = NCsFX::NParameter::NScaled::IScaled;

				/**
				* Container holding information for Niagara Float Parameter that will scale based on the FX scale.
				*/
				struct CSFX_API FFloatType : ScaledType
				{
					using ParameterType = NCsFX::NParameter::IParameter;
					using FloatParameterType = NCsFX::NParameter::NFloat::FFloatType;

				private:

					int32 Index;

				public:

					FloatParameterType Parameter;

				private:

					CS_DECLARE_MEMBER_WITH_PROXY(bValue, bool)
					CS_DECLARE_MEMBER_WITH_PROXY(bInverse, bool)
					CS_DECLARE_MEMBER_WITH_PROXY(Scale, float)

				public:

					FFloatType() :
						Index(INDEX_NONE),
						Parameter(),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(bValue, false),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(bInverse, false),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Scale, 1.0f)
					{
						CS_CTOR_SET_MEMBER_PROXY(bValue);
						CS_CTOR_SET_MEMBER_PROXY(bInverse);
						CS_CTOR_SET_MEMBER_PROXY(Scale);
					}

					FORCEINLINE void SetIndex(const int32& InIndex) 
					{ 
						Index = InIndex;

						Parameter.SetIndex(Index);
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bValue, bool)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bInverse, bool)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Scale, float)

					FORCEINLINE FloatParameterType* GetParameterPtr() { return &Parameter; }

				// IScaled
				#pragma region
				public:

					FORCEINLINE const int32& GetIndex() const { return Index; }
					FORCEINLINE const ParameterType* GetParameter() const { return &Parameter; }
					FORCEINLINE const bool& ShouldSetValue() const { return GetbValue(); }
					FORCEINLINE const bool& ShouldApplyInverse() const { return GetbInverse(); }
					//FORCEINLINE const float& GetScale() const;

				#pragma endregion IScaled

					FORCEINLINE bool IsValidChecked(const FString& Context) const
					{
						check(Parameter.IsValidChecked(Context));
						return true;
					}
				};
			}
		}
	}
}

namespace NCsFX
{
	namespace NParameter
	{
		namespace NScaled
		{
			namespace NVector
			{
				using ScaledType = NCsFX::NParameter::NScaled::IScaled;

				/**
				* Container holding information for Niagara Vector Parameter that will scale based on the FX scale.
				*/
				struct CSFX_API FVectorType : ScaledType
				{
					using ParameterType = NCsFX::NParameter::IParameter;
					using VectorParameterVectorType = NCsFX::NParameter::NVector::FVectorType;

				private:

					int32 Index;

				public:

					VectorParameterVectorType Parameter;

				private:

					CS_DECLARE_MEMBER_WITH_PROXY(bValue, bool)
					CS_DECLARE_MEMBER_WITH_PROXY(bInverse, bool)
					CS_DECLARE_MEMBER_WITH_PROXY(Scale, float)

				public:

					FVectorType() :
						Index(INDEX_NONE),
						Parameter(),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(bValue, false),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(bInverse, false),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Scale, 1.0f)
					{
						CS_CTOR_SET_MEMBER_PROXY(bValue);
						CS_CTOR_SET_MEMBER_PROXY(bInverse);
						CS_CTOR_SET_MEMBER_PROXY(Scale);
					}

					FORCEINLINE void SetIndex(const int32& InIndex) 
					{ 
						Index = InIndex;

						Parameter.SetIndex(Index);
					}

					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bValue, bool)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(bInverse, bool)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Scale, float)

					FORCEINLINE VectorParameterVectorType* GetParameterPtr() { return &Parameter; }

				// IScaled
				#pragma region
				public:

					FORCEINLINE const int32& GetIndex() const { return Index; }
					FORCEINLINE const ParameterType* GetParameter() const { return &Parameter; }
					FORCEINLINE const bool& ShouldSetValue() const { return GetbValue(); }
					FORCEINLINE const bool& ShouldApplyInverse() const { return GetbInverse(); }
					//FORCEINLINE const float& GetScale() const;

				#pragma endregion IScaled

					FORCEINLINE bool IsValidChecked(const FString& Context) const
					{
						check(Parameter.IsValidChecked(Context));
						return true;
					}
				};
			}
		}
	}
}

class USkeletalMeshComponent;

namespace NCsFX
{
	namespace NParameter
	{
		namespace NDataInterface
		{
			namespace NSkeletalMesh
			{
				// Method
				#pragma region

				/**
				* Describes how the Skeletal Mesh Data Interface is set or passed.
				*  Usually the parameter information is passed via an FX Payload.
				*/
				enum class EMethod : uint8
				{
					/** Set the Skeletal Mesh Component directly. */
					Explicit,
					/** Use the Root Component of the Owner.
						NOTE: The Root Component MUST be of type: USkeletalMeshComponent. */
					Owner_RootComponent,
					/** Use the Root Component of the Parent.
						NOTE: The Root Component MUST be of type: USkeletalMeshComponent. */
					Parent_RootComponent,
					EMethod_MAX
				};

				struct CSFX_API EMMethod final : public TCsEnumMap<EMethod>
				{
					CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMMethod, EMethod)
				};

				namespace NMethod
				{
					typedef EMethod Type;

					namespace Ref
					{
						extern CSFX_API const Type Explicit;
						extern CSFX_API const Type Owner_RootComponent;
						extern CSFX_API const Type Parent_RootComponent;
						extern CSFX_API const Type EMethod_MAX;
					}
				}

				#pragma endregion Method

				/**
				* Container holding information for Niagara Data Interface Parameter of type: Skeletal Mesh.
				*/
				struct CSFX_API FSkeletalMeshType
				{
					using MethodType = NCsFX::NParameter::NDataInterface::NSkeletalMesh::EMethod;

				private:

					CS_DECLARE_STATIC_LOG_WARNING

					int32 Index;
					/** Name of the Niagara Data Interface Parameter of type: Skeletal Mesh. */
					CS_DECLARE_MEMBER_WITH_PROXY(Name, FName)
					/** Describes how the Skeletal Mesh Data Interface is set or passed.
						Usually the parameter information is passed via an FX Payload. */
					CS_DECLARE_MEMBER_WITH_PROXY(Method, MethodType)
					/** Component to set for the Data Interface Parameters.
						NOTE: Only used if Method == MethodType::Explicit. */
					USkeletalMeshComponent* Component;

				public:

					FSkeletalMeshType() :
						Index(INDEX_NONE),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Name, NAME_None),
						CS_CTOR_INIT_MEMBER_WITH_PROXY(Method, MethodType::Explicit),
						Component(nullptr)
					{
						CS_CTOR_SET_MEMBER_PROXY(Name);
						CS_CTOR_SET_MEMBER_PROXY(Method);
					}

					FORCEINLINE void SetIndex(const int32& InIndex){ Index = InIndex; }
					FORCEINLINE const int32& GetIndex() const { return Index; }
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Name, FName)
					CS_DEFINE_SET_GET_MEMBER_WITH_PROXY(Method, MethodType)
					FORCEINLINE void SetComponent(USkeletalMeshComponent* InComponent) { Component = InComponent; }
					FORCEINLINE USkeletalMeshComponent* GetComponent() const { return Component; }

					bool IsValidChecked(const FString& Context) const;
					bool IsValid(const FString& Context, CS_FN_PARAM_DEFAULT_LOG_WARNING) const;
				};
			}
		}
	}
}