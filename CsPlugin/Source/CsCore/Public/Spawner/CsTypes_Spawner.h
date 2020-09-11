// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

// FCsSpawnerSpawnedObjects
#pragma region

class UObject;

/**
*/
struct CSCORE_API FCsSpawnerSpawnedObjects
{
public:

	int32 Group;

	TArray<TWeakObjectPtr<UObject>> WeakObjects;

	TArray<UObject*> Objects;

	FCsSpawnerSpawnedObjects() :
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
	}

	void Reset()
	{
		Group = INDEX_NONE;
		WeakObjects.Reset(WeakObjects.Max());
		Objects.Reset(Objects.Max());
	}
};

#pragma endregion FCsSpawnerSpawnedObjects