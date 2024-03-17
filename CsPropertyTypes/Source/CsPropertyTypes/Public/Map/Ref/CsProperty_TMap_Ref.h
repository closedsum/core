// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

template<typename KeyType, typename ValueType>
struct TCsProperty_TMap_Ref
{
public:
	ValueType DefaultValue;
	ValueType Value;
	ValueType Last_Value;

	TMap<KeyType, ValueType*> Values;
	TMap<KeyType, ValueType> Last_Values;

protected:
	bool IsDirty;

	TMap<KeyType, bool> IsDirtys;
public:
	TBaseDelegate<ValueType, const KeyType&> GetDelegate;
	TBaseDelegate<const ValueType&, const KeyType&> Override_Get;
	TBaseDelegate<const ValueType&, const KeyType&> Override_Subscript;
	TMulticastDelegate<void, const ValueType&> OnChange_Event;
	TMulticastDelegate<void, const KeyType&, const ValueType&> OnChangeMap_Event;
public:

	TCsProperty_TMap_Ref()
	{
		Values.Reset();
		Last_Values.Reset();

		IsDirty = false;
		IsDirtys.Reset();

		GetDelegate.Unbind();
		Override_Get.Unbind();
		Override_Subscript.Unbind();
		OnChange_Event.Clear();
		OnChangeMap_Event.Clear();
	}
	virtual ~TCsProperty_TMap_Ref() {}

	void SetDefaultValue(const ValueType& InDefaultValue)
	{
		DefaultValue = InDefaultValue;
	}

	void Init(const KeyType& Key)
	{
		Values.Add(Key, nullptr);
		Last_Values.Add(Key, DefaultValue);
		IsDirtys.Add(Key, false);
	}

	FORCEINLINE virtual void UpdateIsDirty()
	{
		IsDirty		= Value != Last_Value;
		Last_Value	= Value;

		if (IsDirty)
			OnChange_Event.Broadcast(Value);
	}

	FORCEINLINE virtual void UpdateIsDirty(const KeyType& Key)
	{
		IsDirtys[Key]	 = *(Values[Key]) != Last_Values[Key];
		Last_Values[Key] = *(Values[Key]);

		if (IsDirtys[Key])
			OnChangeMap_Event.Broadcast(Key, *(Values[Key]));
	}

	FORCEINLINE TCsProperty_TMap_Ref& operator=(const TCsProperty_TMap_Ref& B)
	{
		Value = B.Value;
		UpdateIsDirty();

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			*(Values[Key]) = *(B.Values[Key]);
			UpdateIsDirty(Key);
		}
		return *this;
	}

	FORCEINLINE bool operator==(const TCsProperty_TMap_Ref& B) const
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			if (*(Values[Key]) != *(B.Values[Key]))
				return false;
		}
		return Value == B;
	}

	FORCEINLINE bool operator!=(const TCsProperty_TMap_Ref& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Set(const ValueType& InValue)
	{
		Value = InValue;
		UpdateIsDirty();
	}

	FORCEINLINE void Set(const KeyType& Key, ValueType* InValue)
	{
		Values[Key] = InValue;
		UpdateIsDirty(Key);
	}

	FORCEINLINE const ValueType& operator[](const KeyType& Key)
	{
		return *(Values[Key]);
	}

	FORCEINLINE const ValueType& Get() { return Value; }
	FORCEINLINE const ValueType& Get(const KeyType& Key) { return *(Values[Key]); }

	FORCEINLINE ValueType GetEX(const KeyType& Key) { return GetDelegate.Execute(Key); }

	FORCEINLINE void Clear()
	{
		IsDirty = false;

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			IsDirtys[Key] = false;
		}
	}

	FORCEINLINE void Clear(const KeyType& Key)
	{
		IsDirtys[Key] = false;
	}

	void ResetValues()
	{
		Value = DefaultValue;
		Last_Value = Value;
		IsDirty = false;

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			Values[Key] = nullptr;
			Last_Values[Key] = Value;
			IsDirtys[Key] = false;
		}
	}

	void Reset()
	{
		ResetValues();

		GetDelegate.Unbind();
		OnChange_Event.Clear();
		OnChangeMap_Event.Clear();
	}

	FORCEINLINE bool HasChanged() { return IsDirty; }
	FORCEINLINE bool HasChanged(const KeyType& Key) { return IsDirtys[Key]; }

	FORCEINLINE void Resolve()
	{
		UpdateIsDirty();

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			UpdateIsDirty(Key);
		}
		Clear();
	}

	FORCEINLINE void Resolve(const KeyType& Key)
	{
		UpdateIsDirty(Key);
		Clear(Key);
	}
};