// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UObject;

namespace NCsDamage {
	namespace NRange {
		struct FResource; } }

namespace NCsDamage {
	namespace NRange {
		struct IRange; } }

namespace NCsDamage
{
	namespace NRange
	{
		/**
		* Container for an allocated object which implements the interface
		* IRange. This container is used to some what cleanly free
		* the object after use.
		*/
		struct CSCORE_API FAllocated
		{
		public:

			UObject* Root;

			FResource* Container;

			IRange* Range;

			FAllocated() :
				Root(nullptr),
				Container(nullptr),
				Range(nullptr)
			{
			}

			FORCEINLINE const IRange* GetRange() const
			{
				return Range;
			}

			void CopyFrom(UObject* InRoot, const IRange* From);

			void CopyFrom(const FAllocated* From);

			/**
			* Clear / null out all members and deallocate the Container.
			*/
			void Reset();
		};
	}
}