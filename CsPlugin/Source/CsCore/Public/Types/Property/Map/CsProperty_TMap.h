// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

template<typename KeyType, typename ValueType>
struct TCsProperty_TMap
{
public:
	ValueType DefaultValue;
	ValueType Value;
	ValueType Last_Value;

	TMap<KeyType, ValueType> Values;
	TMap<KeyType, ValueType> Last_Values;

protected:
	bool IsDirty;

	TMap<KeyType, bool> IsDirtys;
public:
	TBaseDelegate<ValueType, const KeyType&> GetDelegate;
	TMulticastDelegate<void, const ValueType&> OnChange_Event;
	TMulticastDelegate<void, const KeyType&, const ValueType&> OnChangeMap_Event;

public:

	TCsProperty_TMap() 
	{
		Values.Reset();
		Last_Values.Reset();

		IsDirty = false;
		IsDirtys.Reset();

		GetDelegate.Unbind();
		OnChange_Event.Clear();
		OnChangeMap_Event.Clear();
	}
	virtual ~TCsProperty_TMap() {}

	void SetDefaultValue(const ValueType& InDefaultValue)
	{
		DefaultValue = InDefaultValue;
	}

	void Init(const KeyType& Key)
	{
		Values.Add(Key, DefaultValue);
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
		IsDirtys[Key]	 = Values[Key] != Last_Values[Key];
		Last_Values[Key] = Values[Key];

		if (IsDirtys[Key])
			OnChangeMap_Event.Broadcast(Key, Values[Key]);
	}

	FORCEINLINE TCsProperty_TMap& operator=(const TCsProperty_TMap& B)
	{
		Value = B.Value;
		UpdateIsDirty();

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			Values[Key] = B.Values[Key];
			UpdateIsDirty(Key);
		}
		return *this;
	}

	FORCEINLINE bool operator==(const TCsProperty_TMap& B) const
	{
		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			if (Values[Key] != B.Values[Key])
				return false;
		}
		return Value == B;
	}

	FORCEINLINE bool operator!=(const TCsProperty_TMap& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE void Set(const ValueType& InValue)
	{
		Value = InValue;
		UpdateIsDirty();
	}

	FORCEINLINE void Set(const KeyType& Key, const ValueType& InValue)
	{
		Values[Key] = InValue;
		UpdateIsDirty(Key);
	}

	FORCEINLINE ValueType& operator[](const KeyType& Key)
	{
		return Values[Key];
	}

	FORCEINLINE const ValueType& operator[](const KeyType& Key) const
	{
		return Values[Key];
	}

	FORCEINLINE const ValueType& Get() { return Value; }
	FORCEINLINE const ValueType& Get(const KeyType& Key) { return Values[Key]; }

	FORCEINLINE ValueType GetEX(const KeyType& Key) { return GetDelegate.Execute(Key); }

	FORCEINLINE void Clear()
	{
		IsDirty	= false;

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
		Value	   = DefaultValue;
		Last_Value = Value;
		IsDirty	   = false;

		TArray<KeyType> Keys;
		Values.GetKeys(Keys);

		for (const KeyType& Key : Keys)
		{
			Values[Key]	     = Value;
			Last_Values[Key] = Value;
			IsDirtys[Key]    = false;
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