// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnumMap.h"
// Log
#include "Utility/CsLog.h"

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

		struct CSCORE_API EMValue final : public TCsEnumMap<EValue>
		{
			CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMValue, EValue)
		};

		namespace NValue
		{
			typedef EValue Type;

			namespace Ref
			{
				extern CSCORE_API const Type Int;
				extern CSCORE_API const Type Float;
				extern CSCORE_API const Type Vector;
				extern CSCORE_API const Type EValue_MAX;
			}

			extern CSCORE_API const uint8 MAX;

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

		/**
		*/
		struct CSCORE_API IParameter
		{
		public:

			virtual ~IParameter() {}

			virtual const int32& GetIndex() const = 0;

			virtual const FName& GetName() const = 0;

			virtual const EValue& GetValueType() const = 0;

			virtual void* GetValuePtr() const = 0;

			virtual uint32 GetSizeInBytes() const = 0;
		};

		namespace NInt
		{
			/**
			* Container holding information for Niagara Int Parameter
			*/
			struct CSCORE_API FIntType : IParameter
			{
			private:

				int32 Index;

				CS_DECLARE_MEMBER_WITH_PROXY(Name, FName)

			public:

				EValue ValueType;

			private:

				CS_DECLARE_MEMBER_WITH_PROXY(Value, int32)

			public:

				FIntType() :
					Index(INDEX_NONE),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Name, NAME_None),
					ValueType(EValue::Int),
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

			// IParameter
			#pragma region
			public:

				FORCEINLINE const int32& GetIndex() const { return Index; }
				FORCEINLINE const EValue& GetValueType() const { return ValueType; }
				FORCEINLINE void* GetValuePtr() const { return (void*)const_cast<int32*>(Value_Proxy); }
				FORCEINLINE uint32 GetSizeInBytes() const { return sizeof(int32); }

			#pragma endregion IParameter

				FORCEINLINE bool IsValidChecked(const FString& Context) const
				{
					// Check Name is Valid
					checkf(GetName() != NAME_None, TEXT("%s: GetName(): None is NOT Valid."), *Context);

					const FString NameAsString = GetName().ToString();

					checkf(NameAsString.StartsWith(TEXT("User.")), TEXT("%s: %s does NOT start with: 'User.' and is NOT a Valid Parameter Name."), *Context, *NameAsString);
					// Check ValueType is Valid
					checkf(ValueType == EValue::Int, TEXT("%s: ValueType: %s is NOT Int."), *Context, EMValue::Get().ToChar(ValueType));
					return true;
				}
			};
		}

		namespace NFloat
		{
			/**
			* Container holding information for Niagara Float Parameter
			*/
			struct CSCORE_API FFloatType : IParameter
			{
			private:

				int32 Index;

				CS_DECLARE_MEMBER_WITH_PROXY(Name, FName)

			public:

				EValue ValueType;

			private:

				CS_DECLARE_MEMBER_WITH_PROXY(Value, float)

			public:

				FFloatType() :
					Index(INDEX_NONE),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Name, NAME_None),
					ValueType(EValue::Float),
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

			// IParameter
			#pragma region
			public:

				FORCEINLINE const int32& GetIndex() const { return Index; }
				FORCEINLINE const EValue& GetValueType() const { return ValueType; }
				FORCEINLINE void* GetValuePtr() const { return (void*)const_cast<float*>(Value_Proxy); }
				FORCEINLINE uint32 GetSizeInBytes() const { return sizeof(float); }

			#pragma endregion IParameter

				FORCEINLINE bool IsValidChecked(const FString& Context) const
				{
					// Check Name is Valid
					checkf(GetName() != NAME_None, TEXT("%s: GetName(): None is NOT Valid."), *Context);
					// Check ValueType is Valid
					checkf(ValueType == EValue::Float, TEXT("%s: ValueType: %s is NOT Float."), *Context, EMValue::Get().ToChar(ValueType));
					return true;
				}
			};
		}

		namespace NVector
		{
			/**
			* Container holding information for Niagara Vector Parameter
			*/
			struct CSCORE_API FVectorType : IParameter
			{
			private:

				int32 Index;

				CS_DECLARE_MEMBER_WITH_PROXY(Name, FName)

			public:

				EValue ValueType;

			private:

				CS_DECLARE_MEMBER_WITH_PROXY(Value, FVector3f)

			public:

				FVectorType() :
					Index(INDEX_NONE),
					CS_CTOR_INIT_MEMBER_WITH_PROXY(Name, NAME_None),
					ValueType(EValue::Vector),
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

			// IParameter
			#pragma region
			public:

				FORCEINLINE const int32& GetIndex() const { return Index; }
				FORCEINLINE const EValue& GetValueType() const { return ValueType; }
				FORCEINLINE void* GetValuePtr() const { return (void*)const_cast<FVector3f*>(Value_Proxy); }
				FORCEINLINE uint32 GetSizeInBytes() const { return sizeof(FVector3f); }

			#pragma endregion IParameter

				FORCEINLINE bool IsValidChecked(const FString& Context) const
				{
					// Check Name is Valid
					checkf(GetName() != NAME_None, TEXT("%s: GetName(): None is NOT Valid."), *Context);
					// Check ValueType is Valid
					checkf(ValueType == EValue::Vector, TEXT("%s: ValueType: %s is NOT Vector."), *Context, EMValue::Get().ToChar(ValueType));
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
			struct CSCORE_API IScaled
			{
			public:

				virtual ~IScaled() {}

			#define ParameterType NCsFX::NParameter::IParameter

				virtual const int32& GetIndex() const = 0;

				virtual const ParameterType* GetParameter() const = 0;

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

			#undef ParameterType
			};

			namespace NInt
			{
				/**
				* Container holding information for Niagara Int Parameter that will scale based on the FX scale.
				*/
				struct CSCORE_API FIntType : IScaled
				{
				#define ParameterType NCsFX::NParameter::IParameter
				#define ParameterIntType NCsFX::NParameter::NInt::FIntType

				private:

					int32 Index;

				public:

					ParameterIntType Parameter;

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

					FORCEINLINE ParameterIntType* GetParameterPtr() { return &Parameter; }

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

				#undef ParameterType
				#undef ParameterIntType
				};
			}

			namespace NFloat
			{
				/**
				* Container holding information for Niagara Float Parameter that will scale based on the FX scale.
				*/
				struct CSCORE_API FFloatType : IScaled
				{
				#define ParameterType NCsFX::NParameter::IParameter
				#define ParameterFloatType NCsFX::NParameter::NFloat::FFloatType

				private:

					int32 Index;

				public:

					ParameterFloatType Parameter;

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

					FORCEINLINE ParameterFloatType* GetParameterPtr() { return &Parameter; }

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

				#undef ParameterType
				#undef ParameterFloatType
				};
			}

			namespace NVector
			{
				/**
				* Container holding information for Niagara Vector Parameter that will scale based on the FX scale.
				*/
				struct CSCORE_API FVectorType : IScaled
				{
				#define ParameterType NCsFX::NParameter::IParameter
				#define ParameterVectorType NCsFX::NParameter::NVector::FVectorType

				private:

					int32 Index;

				public:

					ParameterVectorType Parameter;

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

					FORCEINLINE ParameterVectorType* GetParameterPtr() { return &Parameter; }

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

				#undef ParameterType
				#undef ParameterVectorType
				};
			}
		}
	}
}

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
				UENUM(BlueprintType)
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

				struct CSCORE_API EMMethod final : public TCsEnumMap<EMethod>
				{
					CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMMethod, EMethod)
				};

				namespace NMethod
				{
					typedef EMethod Type;

					namespace Ref
					{
						extern CSCORE_API const Type Explicit;
						extern CSCORE_API const Type Owner_RootComponent;
						extern CSCORE_API const Type Parent_RootComponent;
						extern CSCORE_API const Type EMethod_MAX;
					}
				}

				#pragma endregion Method

				/**
				* Container holding information for Niagara Data Interface Parameter of type: Skeletal Mesh.
				*/
				struct CSCORE_API FSkeletalMeshType
				{
				#define MethodType NCsFX::NParameter::NDataInterface::NSkeletalMesh::EMethod

				private:

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
					bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

				#undef MethodType
				};
			}
		}
	}
}