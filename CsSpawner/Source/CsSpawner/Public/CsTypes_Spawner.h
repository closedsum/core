// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

// NCsSpawner::FSpawnedObjects
#pragma region

class UObject;

namespace NCsSpawner
{
	/**
	*/
	struct CSSPAWNER_API FSpawnedObjects
	{
	public:

		int32 Group;

		TArray<TWeakObjectPtr<UObject>> WeakObjects;

		TArray<UObject*> Objects;

		FSpawnedObjects() :
			Group(INDEX_NONE),
			WeakObjects(),
			Objects()
		{
		}

		void Add(UObject* Object)
		{
			Objects.Reset(Objects.Max());

			int32 Count = WeakObjects.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				if (WeakObjects[I].IsValid())
				{
					if (UObject* O = WeakObjects[I].Get())
					{
						Objects.Add(O);
					}
					else
					{
						WeakObjects.RemoveAt(I, 1, false);
					}
				}
				else
				{
					WeakObjects.RemoveAt(I, 1, false);
				}
			}

			Objects.Add(Object);
			WeakObjects.Add(Object);
		}

		void Reset()
		{
			Group = INDEX_NONE;
			WeakObjects.Reset(WeakObjects.Max());
			Objects.Reset(Objects.Max());
		}
	};
}

#pragma endregion NCsSpawner::FSpawnedObjects