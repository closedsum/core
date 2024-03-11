// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CoreMinimal.h"

namespace NCsConsoleCommand
{
	namespace NParam
	{
		enum class EValue : uint8 
		{
			Integer,
			Float,
			Enum,
			String
		};

		struct CSCORE_API FInfo
		{
		public:

			FString Name;

			EValue  ValueType;

			float DefaultValue;

			bool bMinValue;
			float MinValue;

			bool bMaxValue;
			float MaxValue;

			TArray<FString> Values;

			FInfo() :
				Name(),
				ValueType(EValue::Integer),
				DefaultValue(0.0f),
				bMinValue(false),
				MinValue(0.0f),
				bMaxValue(false),
				MaxValue(0.0f),
				Values()
			{
			}

			FORCEINLINE void SetMinValue(const float& Val)
			{
				bMinValue = true;
				MinValue  = Val;
			}

			FORCEINLINE void SetMaxValue(const float& Val)
			{
				bMaxValue = true;
				MaxValue  = Val;
			}

			// Integer

			FORCEINLINE void SetInteger(const FString& InName, const float& InDefaultValue)
			{
				Name		 = InName;
				ValueType	 = EValue::Integer;
				DefaultValue = InDefaultValue;
			}

			FORCEINLINE void SetInteger(const FString& InName, const float& InDefaultValue, const float& InMinValue, const float& InMaxValue)
			{
				SetInteger(InName, InDefaultValue);
				SetMinValue(InMinValue);
				SetMaxValue(InMaxValue);
			}

			FORCEINLINE void SetIntegerMinOnly(const FString& InName, const float& InDefaultValue, const float& InMinValue)
			{
				SetInteger(InName, InDefaultValue);
				SetMinValue(InMinValue);
			}

			FORCEINLINE void SetIntegerMaxOnly(const FString& InName, const float& InDefaultValue, const float& InMaxValue)
			{
				SetInteger(InName, InDefaultValue);
				SetMaxValue(InMaxValue);
			}

			// Float

			FORCEINLINE void SetFloat(const FString& InName, const float& InDefaultValue)
			{
				Name		 = InName;
				ValueType	 = EValue::Float;
				DefaultValue = InDefaultValue;
			}

			FORCEINLINE void SetFloat(const FString& InName, const float& InDefaultValue, const float& InMinValue, const float& InMaxValue)
			{
				SetFloat(InName, InDefaultValue);
				SetMinValue(InMinValue);
				SetMaxValue(InMaxValue);
			}

			FORCEINLINE void SetFloatMinOnly(const FString& InName, const float& InDefaultValue, const float& InMinValue)
			{
				SetFloat(InName, InDefaultValue);
				SetMinValue(InMinValue);
			}

			FORCEINLINE void SetFloatMaxOnly(const FString& InName, const float& InDefaultValue, const float& InMaxValue)
			{
				SetFloat(InName, InDefaultValue);
				SetMaxValue(InMaxValue);
			}

			// Enum
			
			template<typename EnumMapType, typename EnumType>
			FORCEINLINE void SetEnumStruct(const FString& InName)
			{
				Name	  = InName;
				ValueType = EValue::Enum;

				Values.Reset(EnumMapType::Get().Num());

				for (const EnumType& Enum : EnumMapType::Get())
				{
					Values.Add(Enum.GetName());
				}
			}

			template<typename EnumMapType, typename EnumType>
			FORCEINLINE void SetEnum(const FString& InName)
			{
				Name	  = InName;
				ValueType = EValue::Enum;

				Values.Reset(EnumMapType::Get().Num());

				for (const EnumType& Enum : EnumMapType::Get())
				{
					Values.Add(EnumMapType::Get().ToString(Enum));
				}
			}

			// String

			FORCEINLINE void SetString(const FString& InName)
			{
				Name	  = InName;
				ValueType = EValue::String;
			}
		};
	}

	struct CSCORE_API FInfo
	{
	public:

		TArray<FString> Commands;
		TArray<FString> Definitions;
		int32 PrimaryDefinitionIndex;

	typedef NCsConsoleCommand::NParam::FInfo ParamInfoType;

		TArray<ParamInfoType> ParamInfos;

		FString Description;

		FInfo() :
			Commands(),
			Definitions(),
			PrimaryDefinitionIndex(0),
			ParamInfos(),
			Description()
		{
		}

		const FString& GetPrimaryCommand() const { return Commands[PrimaryDefinitionIndex]; }
		const FString& GetPrimaryDefintion() const { return Definitions[PrimaryDefinitionIndex]; }
	};
}

namespace NCsConsoleCommand
{
	namespace NManager
	{
		struct CSCORE_API FHandle
		{
		public:

			//static const FHandle Invalid;

		public:

			FGuid Handle;

			FHandle() :
				Handle()
			{
			}

			FORCEINLINE bool operator==(const FHandle& B) const
			{
				return Handle == B.Handle;
			}

			FORCEINLINE bool operator!=(const FHandle& B) const
			{
				return !(*this == B);
			}

			friend uint32 GetTypeHash(const FHandle& InHandle)
			{
				return GetTypeHash(InHandle.Handle);
			}

			FORCEINLINE bool IsValid() const { return Handle.IsValid(); }

			FORCEINLINE void New() { Handle = FGuid::NewGuid(); }

			FORCEINLINE void Reset() { Handle.Invalidate(); }
		};
	}
}