// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Macro.h"
#pragma once

class UObject;

// NCsDamage::NRange::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NRange, FResource)
// NCsDamage::NRange::IRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NRange, IRange)
// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

namespace NCsDamage
{
	namespace NRange
	{
		/**
		* Container for an allocated object which implements the interface
		* IRange. This container is used to somewhat cleanly free
		* the object after use.
		*/
		struct CSCORE_API FAllocated
		{
		private:

			TWeakObjectPtr<UObject> Root;

			FResource* Container;

			IRange* Range;

		public:

			FAllocated() :
				Root(nullptr),
				Container(nullptr),
				Range(nullptr)
			{
			}

			~FAllocated();

			UObject* GetRoot() const;
			FORCEINLINE IRange* GetRange() { return Range; }
			FORCEINLINE const IRange* GetRange() const { return Range; }
			FORCEINLINE const FResource* GetContainer() const { return Container; }

			void CopyFrom(const FString& Context, UObject* InRoot, const IRange* From);

			#define DataType NCsDamage::NData::IData
			void SafeCopyFrom(const FString& Context, UObject* InRoot, const DataType* Data, void(*Log)(const FString&) = nullptr);
			#undef DataType

			void CopyFrom(const FAllocated* From);

			/**
			* Clear / null out all members and deallocate the Container.
			*/
			void Reset();
		};
	}
}