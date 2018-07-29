// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.Collections.Generic;
    using System.Reflection;

    #region "Enums"

    public interface ICgEnum
    {
        string GetName();
    }

    public abstract class TCgEnum<T> : ICgEnum where T : struct, IConvertible
    {
        #region "Delegates"

        public delegate TCgEnum<T> Get(T t);
        public delegate TCgEnum<T> GetMAX();
        public delegate TCgEnum<T> ToType(string s);
        public delegate string ToStr(TCgEnum<T> e);

        public delegate int ToMask(string s);
        public delegate string MaskToStr(int m);

        #endregion // Delegates

        #region "Data Members"

        public readonly T Value;
        public readonly string Name;

        #endregion // Data Members

        public TCgEnum()
        {
            Value = default(T);
            Name = "";
        }

        public TCgEnum(T value)
        {
            Value = value;
            Name = "";
        }

        public TCgEnum(T value, string name)
        {
            Value = value;
            Name = name;
        }

        public static implicit operator T(TCgEnum<T> e)
        {
            return e.Value;
        }

        public static implicit operator string(TCgEnum<T> e)
        {
            return e.Name;
        }

        public static bool operator ==(TCgEnum<T> lhs, TCgEnum<T> rhs)
        {
            if (object.ReferenceEquals(lhs, null))
                return object.ReferenceEquals(rhs, null);
            if (object.ReferenceEquals(rhs, null))
                return false;
            return lhs.Value.Equals(rhs.Value) && lhs.Name == rhs.Name;
        }

        public static bool operator !=(TCgEnum<T> lhs, TCgEnum<T> rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(TCgEnum<T> lhs, T rhs)
        {
            return lhs.Value.Equals(rhs);
        }

        public static bool operator !=(TCgEnum<T> lhs, T rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(T lhs, TCgEnum<T> rhs)
        {
            return lhs.Equals(rhs.Value);
        }

        public static bool operator !=(T lhs, TCgEnum<T> rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(TCgEnum<T> lhs, string rhs)
        {
            return lhs.Name ==rhs;
        }

        public static bool operator !=(TCgEnum<T> lhs, string rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(string lhs, TCgEnum<T> rhs)
        {
            return lhs == rhs.Name;
        }

        public static bool operator !=(string lhs, TCgEnum<T> rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is TCgEnum<T>))
                return false;

            TCgEnum<T> rhs = (TCgEnum<T>)obj;

            if (!Value.Equals(rhs.Value)) return false;
            if (Name != rhs.Name) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return Value.GetHashCode() ^ Name.GetHashCode();
        }

        public string GetName()
        {
            return Name;
        }
    }

    public class ECgEnum_byte : TCgEnum<byte>
    {
        public ECgEnum_byte() : base() { }
        public ECgEnum_byte(byte value) : base(value) { }
        public ECgEnum_byte(byte value, string name) : base(value, name) { }
    }

    public class ECgEnum_int : TCgEnum<int>
    {
        public ECgEnum_int() : base() { }
        public ECgEnum_int(int value) : base(value) { }
        public ECgEnum_int(int value, string name) : base(value, name) { }
    }

    public class ECgEnum_uint : TCgEnum<uint>
    {
        public ECgEnum_uint() : base() { }
        public ECgEnum_uint(uint value) : base(value) { }
        public ECgEnum_uint(uint value, string name) : base(value, name) { }
    }

    public class ECgEnumMap<EnumClass, EnumType>
        where EnumClass : TCgEnum<EnumType>
        where EnumType : struct, IConvertible
    {
        protected sealed class EnumTypeEqualityComparer : IEqualityComparer<EnumType>
        {
            public bool Equals(EnumType lhs, EnumType rhs)
            {
                return lhs.Equals(rhs);
            }

            public int GetHashCode(EnumType x)
            {
                return x.GetHashCode();
            }
        }

        private List<EnumClass> Enums;
        private Dictionary<string, EnumClass> StringMap;
        private Dictionary<EnumType, EnumClass> TypeMap;
        private EnumClass Max;

        public int Count
        {
            get { return Enums.Count; }
        }

        public ECgEnumMap()
        {
            Enums = new List<EnumClass>();
            StringMap = new Dictionary<string, EnumClass>();
            TypeMap = new Dictionary<EnumType, EnumClass>(new EnumTypeEqualityComparer());
        }

        public EnumClass Create(string name)
        {
            EnumClass e = null;

            StringMap.TryGetValue(name, out e);

            if (e != null)
            {
                FCgDebug.LogError(this.GetType().Name + ".Create: Enum with name: " + name + " already exists. It is being defined in move than one place.");
                return e;
            }

            Type type = typeof(EnumClass);
            // Get Constructor
            Type[] types = new Type[2];
            types[0]     = typeof(EnumType);
            types[1]     = typeof(string);
            ConstructorInfo constructor = type.GetConstructor(types);

            // Get Params for Constructor and create EnumClass
            object[] param  = new object[2];
            param[0]        = (EnumType)Convert.ChangeType(Enums.Count, typeof(EnumType));
            param[1]        = name;
            e               = (EnumClass)constructor.Invoke(param);

            Max = (EnumClass)constructor.Invoke(param);

            // Add to List and Maps
            EnumType index = (EnumType)Convert.ChangeType(Enums.Count, typeof(EnumType));

            Enums.Add(e);
            StringMap.Add(name, e);
            TypeMap.Add(index, e);

            return e;
        }

        public EnumClass this[string key]
        {
            get
            {
                EnumClass e = null;
                StringMap.TryGetValue(key, out e);

                if (e == null)
                    FCgDebug.LogError(this.GetType().Name + ".Get: No enum created of type: " + typeof(EnumClass).Name + " and name: " + key);
                return e;
            }
        }

        public EnumClass this[EnumType key]
        {
            get
            {
                EnumClass e = null;
                TypeMap.TryGetValue(key, out e);

                if (e == null)
                    FCgDebug.LogError(this.GetType().Name + ".Get: No enum created of type: " + typeof(EnumClass).Name + " and name: " + key);
                return e;
            }
        }

        public bool IsValidEnum(EnumClass e)
        {
            return Enums.Find(em => em == e) != null;
        }

        public bool IsValidEnum(string name)
        {
            return StringMap.ContainsKey(name);
        }

        public EnumClass GetEnumAt(int index)
        {
            return Enums[index];
        }

        public EnumClass GetSafeEnumAt(int index)
        {
            return index < Count ? Enums[index] : Max;
        }

        public EnumClass GetEnum(string name)
        {
            return StringMap[name];
        }

        public EnumClass GetSafeEnum(string name)
        {
            return IsValidEnum(name) ? StringMap[name] : Max;
        }

        public EnumClass GetEnum(EnumType type)
        {
            return TypeMap[type];
        }

        public EnumClass GetMAX()
        {
            return Max;
        }
    }

    public class ECgEnumMaskMap<EnumClass, EnumType>
        where EnumClass : TCgEnum<EnumType>
        where EnumType : struct, IConvertible
    {
        protected sealed class EnumTypeEqualityComparer : IEqualityComparer<EnumType>
        {
            public bool Equals(EnumType lhs, EnumType rhs)
            {
                return lhs.Equals(rhs);
            }

            public int GetHashCode(EnumType x)
            {
                return x.GetHashCode();
            }
        }

        private List<EnumClass> Enums;
        private Dictionary<string, EnumClass> StringMap;
        private Dictionary<EnumType, EnumClass> TypeMap;

        public int Count
        {
            get { return Enums.Count; }
        }

        public ECgEnumMaskMap()
        {
            Enums = new List<EnumClass>();
            StringMap = new Dictionary<string, EnumClass>();
            TypeMap = new Dictionary<EnumType, EnumClass>(new EnumTypeEqualityComparer());
        }

        public EnumClass Create(string name)
        {
            EnumClass e = null;

            StringMap.TryGetValue(name, out e);

            if (e != null)
            {
                FCgDebug.LogError(this.GetType().Name + ".Create: Enum with name: " + name + " already exists. It is being defined in move than one place.");
                return e;
            }

            Type type = typeof(EnumClass);
            // Get Constructor
            Type[] types = new Type[2];
            types[0] = typeof(EnumType);
            types[1] = typeof(string);
            ConstructorInfo constructor = type.GetConstructor(types);

            // Get Params for Constructor and create EnumClass
            object[] param = new object[2];
            param[0] = (EnumType)Convert.ChangeType(Enums.Count, typeof(EnumType));
            param[1] = name;
            e = (EnumClass)constructor.Invoke(param);

            // Add to List and Maps
            EnumType index = (EnumType)Convert.ChangeType(Enums.Count, typeof(EnumType));

            Enums.Add(e);
            StringMap.Add(name, e);
            TypeMap.Add(index, e);

            return e;
        }

        public EnumClass this[string key]
        {
            get
            {
                EnumClass e = null;
                StringMap.TryGetValue(key, out e);

                if (e == null)
                    FCgDebug.LogError(this.GetType().Name + ".Get: No enum created of type: " + typeof(EnumClass).Name + " and name: " + key);
                return e;
            }
        }

        public EnumClass this[EnumType key]
        {
            get
            {
                EnumClass e = null;
                TypeMap.TryGetValue(key, out e);

                if (e == null)
                    FCgDebug.LogError(this.GetType().Name + ".Get: No enum created of type: " + typeof(EnumClass).Name + " and name: " + key);
                return e;
            }
        }

        public int ToMask(string s)
        {
            int mask = 0;

            Dictionary<string, EnumClass>.KeyCollection keys = StringMap.Keys;

            foreach (string key in keys)
            {
                if (s.Contains(key))
                {
                    int value = (int)Convert.ChangeType(StringMap[key].Value, typeof(int));
                    mask     |= value;
                }
            }
            return mask;
        }

        public string MaskToStr(int m)
        {
            string s = "";

            Dictionary<string, EnumClass>.KeyCollection keys = StringMap.Keys;

            foreach (string key in keys)
            {
                int value = (int)Convert.ChangeType(StringMap[key].Value, typeof(int));

                if ((m & value) == value)
                    s += s == "" ? key : " | " + key;
            }
            return s;
        }
    }

    #endregion // Enums

    #region "Property"

        #region "Default"

    public interface ICgProperty
    {
        void UpdateIsDirty();
        void Clear();
        void ResetValue();
        void Reset();
        bool HasChanged();
        void MarkDirty();
        void Resolve();
    }

    public abstract class CgProperty : ICgProperty
    {
        public abstract void UpdateIsDirty();
        public abstract void Clear();
        public abstract void ResetValue();
        public abstract void Reset();
        public abstract bool HasChanged();
        public abstract void MarkDirty();
        public abstract void Resolve();
    }

    public class TCgProperty<T> : CgProperty 
        where T : struct
    {
        public sealed class OnChange : TCgMulticastDelegate_OneParam<T> { }

        #region "Data Members"

        public T Value;
        public T Last_Value;

        protected bool IsDirty;

        public OnChange OnChange_Event;

        #endregion // Data Members

        public TCgProperty()
        {
            OnChange_Event = new OnChange();
        }

        #region "Operators"

        public static bool operator ==(TCgProperty<T> lhs, TCgProperty<T> rhs)
        {
            if (object.ReferenceEquals(lhs, null))
                return object.ReferenceEquals(rhs, null);
            if (object.ReferenceEquals(rhs, null))
                return false;
            return lhs.Value.Equals(rhs.Value);
        }

        public static bool operator !=(TCgProperty<T> lhs, TCgProperty<T> rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(TCgProperty<T> lhs, T rhs)
        {
            return lhs.Value.Equals(rhs);
        }

        public static bool operator !=(TCgProperty<T> lhs, T rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(T lhs, TCgProperty<T> rhs)
        {
            return lhs.Equals(rhs.Value);
        }

        public static bool operator !=(T lhs, TCgProperty<T> rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is TCgProperty<T>))
                return false;

            TCgProperty<T> rhs = (TCgProperty<T>)obj;

            if (!Value.Equals(rhs.Value)) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return Value.GetHashCode();
        }

        #endregion // Operators

        public override void UpdateIsDirty()
        {
            IsDirty    = !Value.Equals(Last_Value);
            Last_Value = Value;

            if (IsDirty)
                OnChange_Event.Broadcast(Value);
        }

        public void Set(T inValue)
        {
            Value = inValue;
            UpdateIsDirty();
        }

        public T Get() { return Value; }

        public override void Clear()
        {
            IsDirty = false;
        }

        public override void ResetValue()
        {
            Value = default(T);
            Last_Value = Value;
            IsDirty = false;
        }

        public override void Reset()
        {
            ResetValue();

            OnChange_Event.Clear();
        }

        public override bool HasChanged() { return IsDirty; }
        public override void MarkDirty() { IsDirty = true; }

        public override void Resolve()
        {
            UpdateIsDirty();
            Clear();
        }
    }

        #endregion // Default

        #region "List"

    public class TCgProperty_TList<ValueType>
       where ValueType : struct, IConvertible
    {
        public sealed class FGet : TCgDelegate_Ret_OneParam<ValueType, int> { }
        public sealed class FOverride_Get : TCgDelegate_Ret_OneParam<ValueType, int> { }
        public sealed class FOverride_Subscript : TCgDelegate_Ret_OneParam<ValueType, int> { }
        public sealed class FOnChange : TCgMulticastDelegate_OneParam<ValueType> { }
        public sealed class FOnChangeList : TCgMulticastDelegate_TwoParams<int, ValueType> { }

        public ValueType DefaultValue;
        public ValueType Value;
        public ValueType Last_Value;

        public List<ValueType> Values;
        public List<ValueType> Last_Values;

        protected byte SIZE;
        protected bool IsDirty;

        protected List<bool> IsDirtys;

        public FGet Get_Call;
        public FOverride_Get Override_Get;
        public FOverride_Subscript Override_Subscript;
        public FOnChange OnChange_Event;
        public FOnChangeList OnChangeList_Event;

        public TCgProperty_TList()
        {
            DefaultValue = default(ValueType);
            Value = DefaultValue;
            Last_Value = Value;

            Values = new List<ValueType>();
            Last_Values = new List<ValueType>();

            IsDirtys = new List<bool>();

            Get_Call = new FGet();
            Override_Get = new FOverride_Get();
            Override_Subscript = new FOverride_Subscript();
            OnChange_Event = new FOnChange();
            OnChangeList_Event = new FOnChangeList();
        }

        public void SetDefaultValue(ValueType defaultValue)
        {
            DefaultValue = defaultValue;
        }

        public void Init(byte size)
        {
            for (int i = 0; i < size; ++i)
            {
                Values.Add(DefaultValue);
                Last_Values.Add(DefaultValue);
                IsDirtys.Add(false);
            }
        }

        public virtual void UpdateIsDirty()
        {
            IsDirty = !Value.Equals(Last_Value);
            Last_Value = Value;

            if (IsDirty)
                OnChange_Event.Broadcast(Value);
        }

        public virtual void UpdateIsDirtys(int index)
        {
            IsDirtys[index] = !Values[index].Equals(Last_Values[index]);
            Last_Values[index] = Values[index];

            if (IsDirtys[index])
                OnChangeList_Event.Broadcast(index, Values[index]);
        }
        /*
        bool operator ==(const TCsProperty_TMap& B) const
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

	     bool operator !=(const TCsProperty_TMap& B) const
	    {
		    return !(*this == B);
        }
        */

        public void Set(ValueType value)
        {
            Value = value;
            UpdateIsDirty();
        }

        public void Set(int index, ValueType value)
        {
            Values[index] = value;
            UpdateIsDirtys(index);
        }

        public ValueType this[int index]
        {
            get
            {
                if (Override_Subscript.IsBound())
                    return Override_Subscript.Execute(index);
                return Values[index];
            }
            set
            {
                Values[index] = value;
                UpdateIsDirtys(index);
            }
        }

        public ValueType Get() { return Value; }
        public ValueType Get(int index)
        {
            if (Override_Get.IsBound())
                return Override_Get.Execute(index);
            return Values[index];
        }

        public ValueType GetEX(int index) { return Get_Call.Execute(index); }

        public void Clear()
        {
            IsDirty = false;

            for (int i = 0; i < SIZE; ++i)
            {
                IsDirtys[i] = false;
            }
        }

        public void ResetValues()
        {
            Value = DefaultValue;
            Last_Value = Value;
            IsDirty = false;

            for (int i = 0; i < SIZE; ++i)
            {
                Values[i] = Value;
                Last_Values[i] = Value;
                IsDirtys[i] = false;
            }
        }

        public void Reset()
        {
            ResetValues();

            Get_Call.Unbind();
            Override_Get.Unbind();
            Override_Subscript.Unbind();
            OnChange_Event.Clear();
            OnChangeList_Event.Clear();
        }

        public bool HasChanged() { return IsDirty; }
        public bool HasChanged(int index) { return IsDirtys[index]; }

        public void Resolve()
        {
            UpdateIsDirty();

            for (int i = 0; i < SIZE; ++i)
            {
                UpdateIsDirtys(i);
            }
            Clear();
        }
    }

        #endregion // List

        #region "List Ref"

     public class TCgProperty_TListRef<ValueType>
        where ValueType : struct, IConvertible
    {
        public sealed class FGet : TCgDelegate_Ret_OneParam<ValueType, int> { }
        public sealed class FOverride_Get : TCgDelegate_Ret_OneParam<ValueType, int> { }
        public sealed class FOverride_Subscript : TCgDelegate_Ret_OneParam<ValueType, int> { }
        public sealed class FOnChange : TCgMulticastDelegate_OneParam<ValueType> { }
        public sealed class FOnChangeList : TCgMulticastDelegate_TwoParams<int, ValueType> { }

        public ValueType DefaultValue;
        public ValueType Value;
        public ValueType Last_Value;

        public List<object> Objects;
        public List<PropertyInfo> PropertyInfos;
        public List<ValueType> Last_Values;

        protected byte SIZE;
	    protected bool IsDirty;

        protected List<bool> IsDirtys;

	    public FGet Get_Call;
        public FOverride_Get Override_Get;
        public FOverride_Subscript Override_Subscript;
	    public FOnChange OnChange_Event;
	    public FOnChangeList OnChangeList_Event;

	    public TCgProperty_TListRef()
        {
            DefaultValue = default(ValueType);
            Value = DefaultValue;
            Last_Value = Value;

            Objects = new List<object>();
            PropertyInfos = new List<PropertyInfo>();
            Last_Values = new List<ValueType>();

            IsDirtys = new List<bool>();

            Get_Call = new FGet();
            Override_Get = new FOverride_Get();
            Override_Subscript = new FOverride_Subscript();
            OnChange_Event = new FOnChange();
            OnChangeList_Event = new FOnChangeList();
        }

        public void SetDefaultValue(ValueType defaultValue)
        {
            DefaultValue = defaultValue;
        }

        public void Init(byte size)
        {
            for (int i = 0; i < size; ++i)
            {
                Objects.Add(null);
                PropertyInfos.Add(null);
                Last_Values.Add(DefaultValue);
                IsDirtys.Add(false);
            }
        }

        public virtual void UpdateIsDirty()
        {
            IsDirty    = !Value.Equals(Last_Value);
            Last_Value = Value;

            if (IsDirty)
                OnChange_Event.Broadcast(Value);
        }

        public virtual void UpdateIsDirtys(int index)
        {
            ValueType value     = (ValueType)PropertyInfos[index].GetValue(Objects[index], null);
            IsDirtys[index]     = !value.Equals(Last_Values[index]);
            Last_Values[index]  = value;

            if (IsDirtys[index])
                OnChangeList_Event.Broadcast(index, value);
        }
        /*
        bool operator ==(const TCsProperty_TMap& B) const
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

	     bool operator !=(const TCsProperty_TMap& B) const
	    {
		    return !(*this == B);
        }
        */

        public void Set(ValueType value)
        {
            Value = value;
            UpdateIsDirty();
        }

        public void Set(int index, object o, string propertyName)
        {
            Objects[index] = o;
            PropertyInfos[index] = o.GetType().GetProperty(propertyName);
            UpdateIsDirtys(index);
        }

        public ValueType this[int index]
        {
            get
            {
                if (Override_Subscript.IsBound())
                    return Override_Subscript.Execute(index);
                return (ValueType)PropertyInfos[index].GetValue(Objects[index], null);
            }
        }

        public ValueType Get() { return Value; }
        public ValueType Get(int index)
        {
            if (Override_Get.IsBound())
                return Override_Get.Execute(index);
            return (ValueType)PropertyInfos[index].GetValue(Objects[index], null);
        }

        public ValueType GetEX(int index) { return Get_Call.Execute(index); }

        public void Clear()
        {
            IsDirty = false;

            for(int i = 0; i < SIZE; ++i)
		    {
                IsDirtys[i] = false;
            }
        }

        public void ResetValues()
        {
            Value = DefaultValue;
            Last_Value = Value;
            IsDirty = false;

            for (int i = 0; i < SIZE; ++i)
            {
                Objects[i] = null;
                PropertyInfos[i] = null;
                Last_Values[i] = Value;
                IsDirtys[i] = false;
            }
        }

        public void Reset()
        {
            ResetValues();

            Get_Call.Unbind();
            Override_Get.Unbind();
            Override_Subscript.Unbind();
            OnChange_Event.Clear();
            OnChangeList_Event.Clear();
        }

        public bool HasChanged() { return IsDirty; }
        public bool HasChanged(int index) { return IsDirtys[index]; }

        public void Resolve()
        {
            UpdateIsDirty();

            for (int i = 0; i < SIZE; ++i)
            {
                UpdateIsDirtys(i);
            }
            Clear();
        }    

        #endregion // List

        #region "Map"

    public class TCgProperty_TMap<KeyType, ValueType>
        where KeyType : struct
        where ValueType : struct, IConvertible
    {
        public sealed class FGet : TCgDelegate_Ret_OneParam<ValueType, KeyType> { }
        public sealed class FOnChange : TCgMulticastDelegate_OneParam<ValueType> { }
        public sealed class FOnChangeMap : TCgMulticastDelegate_TwoParams<KeyType, ValueType> { }

        public sealed class FKeyTypeEqualityComparer : IEqualityComparer<KeyType>
        {
            public bool Equals(KeyType lhs, KeyType rhs)
            {
                return lhs.Equals(rhs);
            }

            public int GetHashCode(KeyType x)
            {
                return x.GetHashCode();
            }
        }

        public ValueType DefaultValue;
        public ValueType Value;
        public ValueType Last_Value;

        public Dictionary<KeyType, ValueType> Values;
        public Dictionary<KeyType, ValueType> Last_Values;

	    protected bool IsDirty;

        protected Dictionary<KeyType, bool> IsDirtys;

	    public FGet Get_Call;
	    public FOnChange OnChange_Event;
	    public FOnChangeMap OnChangeMap_Event;

	    public TCgProperty_TMap()
        {
            Values = new Dictionary<KeyType, ValueType>(new FKeyTypeEqualityComparer());
            Last_Values = new Dictionary<KeyType, ValueType>(new FKeyTypeEqualityComparer());

            IsDirtys = new Dictionary<KeyType, bool>(new FKeyTypeEqualityComparer());

            Get_Call = new FGet();
            OnChange_Event = new FOnChange();
            OnChangeMap_Event = new FOnChangeMap();
        }

        public void SetDefaultValue(ValueType defaultValue)
        {
            DefaultValue = defaultValue;
        }

        public void Init(KeyType key)
        {
            Values.Add(key, DefaultValue);
            Last_Values.Add(key, DefaultValue);
            IsDirtys.Add(key, false);
        }

        public virtual void UpdateIsDirty()
        {
            IsDirty    = !Value.Equals(Last_Value);
            Last_Value = Value;

            if (IsDirty)
                OnChange_Event.Broadcast(Value);
        }

        public virtual void UpdateIsDirtys(KeyType key)
        {
            IsDirtys[key]     = !Values[key].Equals(Last_Values[key]);
            Last_Values[key] = Values[key];

            if (IsDirtys[key])
                OnChangeMap_Event.Broadcast(key, Values[key]);
        }
        /*
        bool operator ==(const TCsProperty_TMap& B) const
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

	     bool operator !=(const TCsProperty_TMap& B) const
	    {
		    return !(*this == B);
        }
        */

        public void Set(ValueType value)
        {
            Value = value;
            UpdateIsDirty();
        }

        public void Set(KeyType key, ValueType value)
        {
            Values[key] = value;
            UpdateIsDirtys(key);
        }

        public ValueType this[KeyType key]
        {
            get
            {
                return Values[key];
            }
            set
            {
                Values[key] = value;
                UpdateIsDirtys(key);
            }
        }

        public ValueType Get() { return Value; }
        public ValueType Get(KeyType key) { return Values[key]; }

        public ValueType GetEX(KeyType key) { return Get_Call.Execute(key); }

        public void Clear()
        {
            IsDirty = false;

            Dictionary<KeyType, ValueType>.KeyCollection keys = Values.Keys;

            foreach (KeyType key in keys)
		    {
                IsDirtys[key] = false;
            }
        }

        public void ResetValues()
        {
            Value = DefaultValue;
            Last_Value = Value;
            IsDirty = false;

            Dictionary<KeyType, ValueType>.KeyCollection keys = Values.Keys;

            foreach (KeyType key in keys)
            {
                Values[key] = Value;
                Last_Values[key] = Value;
                IsDirtys[key] = false;
            }
        }

        public void Reset()
        {
            ResetValues();

            Get_Call.Unbind();
            OnChange_Event.Clear();
            OnChangeMap_Event.Clear();
        }

        public bool HasChanged() { return IsDirty; }
        public bool HasChanged(KeyType key) { return IsDirtys[key]; }

        public void Resolve()
        {
            UpdateIsDirty();

            Dictionary<KeyType, ValueType>.KeyCollection keys = Values.Keys;

            foreach (KeyType key in keys)
            {
                UpdateIsDirtys(key);
            }
            Clear();
        }
    }

    public class TCgIntegralType_TMap<KeyType, ValueType> : TCgProperty_TMap<KeyType, ValueType>
        where KeyType : struct
        where ValueType : struct, IConvertible
    {
        public TCgIntegralType_TMap() { }
        /*
        public void Add(ValueType value)
        {
            Value += value;
            UpdateIsDirty();
        }

        void Add(KeyType key, ValueType value)
        {
            Values[key] += value;
            UpdateIsDirtys(key);
        }

        void Subtract(ValueType value)
        {
            Value -= value;
            UpdateIsDirty();
        }

        void Subtract(KeyType key, ValueType value)
        {
            Values[key] -= value;
            UpdateIsDirtys(key);
        }

        ValueType Max()
        {
            Dictionary<KeyType, ValueType>.KeyCollection keys = Values.Keys;

            ValueType max = DefaultValue;

            int i = 0;

            foreach (KeyType key in keys)
            {
                if (i == 0)
                    max = Values[key];
                else
                  max = (ValueType)Math.Max(max, Values[key]);
                ++i;
            }
            return max;
        }

        ValueType Min()
        {
            Dictionary<KeyType, ValueType>.KeyCollection keys = Values.Keys;

            ValueType min = DefaultValue;

            int i = 0;

            foreach (KeyType key in keys)
            {
                if (i == 0)
                    min = Values[key];
                else
                    min = (ValueType)Math.Max(min, Values[key]);
                ++i;
            }
            return min;
        }
        */
    }

    public class TCgIntegralType_TMap_byte<KeyType> : TCgIntegralType_TMap<KeyType, byte>
        where KeyType : struct
    {
	    public TCgIntegralType_TMap_byte()
        {
            DefaultValue = 0;
        }
    }

    public class TCgIntegralType_TMap_float<KeyType> : TCgIntegralType_TMap<KeyType, float>
        where KeyType : struct
    {
	    public TCgIntegralType_TMap_float()
        {
            DefaultValue = 0.0f;
        }
    }

    public class TCgProperty_TMap_bool<KeyType> : TCgProperty_TMap<KeyType, bool>
        where KeyType : struct
    {
	    TCgProperty_TMap_bool()
        {
            DefaultValue = false;
        }

        bool Or()
        {
            Dictionary<KeyType, bool>.KeyCollection keys = Values.Keys;

            bool or = false;

            int i = 0;

            foreach (KeyType key in keys)
            {
                if (i == 0)
                    or = Values[key];
                else
                   or |= Values[key];
                ++i;
            }
            return or;
        }

        bool And()
        {
            Dictionary<KeyType, bool>.KeyCollection keys = Values.Keys;

            bool and = false;

            int i = 0;

            foreach (KeyType key in keys)
            {
                if (i == 0)
                    and = Values[key];
                else
                    and &= Values[key];
                ++i;
            }
            return and;
        }
    }

        #endregion // Map

        #region "Map Ref"

    public class TCgProperty_TMapRef<KeyType, ValueType>
        where KeyType : struct
        where ValueType : struct, IConvertible
    {
        public sealed class FGet : TCgDelegate_Ret_OneParam<ValueType, KeyType> { }
        public sealed class FOverride_Get : TCgDelegate_Ret_OneParam<ValueType, KeyType> { }
        public sealed class FOverride_Subscript : TCgDelegate_Ret_OneParam<ValueType, KeyType> { }
        public sealed class FOnChange : TCgMulticastDelegate_OneParam<ValueType> { }
        public sealed class FOnChangeMap : TCgMulticastDelegate_TwoParams<KeyType, ValueType> { }

        public sealed class FKeyTypeEqualityComparer : IEqualityComparer<KeyType>
        {
            public bool Equals(KeyType lhs, KeyType rhs)
            {
                return lhs.Equals(rhs);
            }

            public int GetHashCode(KeyType x)
            {
                return x.GetHashCode();
            }
        }

        public ValueType DefaultValue;
        public ValueType Value;
        public ValueType Last_Value;

        public Dictionary<KeyType, object> Objects;
        public Dictionary<KeyType, PropertyInfo> PropertyInfos;
        public Dictionary<KeyType, ValueType> Last_Values;

	    protected bool IsDirty;

        protected Dictionary<KeyType, bool> IsDirtys;

	    public FGet Get_Call;
        public FOverride_Get Override_Get;
        public FOverride_Subscript Override_Subscript;
	    public FOnChange OnChange_Event;
	    public FOnChangeMap OnChangeMap_Event;

	    public TCgProperty_TMapRef()
        {
            Objects = new Dictionary<KeyType, object>(new FKeyTypeEqualityComparer());
            PropertyInfos = new Dictionary<KeyType, PropertyInfo>(new FKeyTypeEqualityComparer());
            Last_Values = new Dictionary<KeyType, ValueType>(new FKeyTypeEqualityComparer());

            IsDirtys = new Dictionary<KeyType, bool>(new FKeyTypeEqualityComparer());

            Get_Call = new FGet();
            Override_Get = new FOverride_Get();
            Override_Subscript = new FOverride_Subscript();
            OnChange_Event = new FOnChange();
            OnChangeMap_Event = new FOnChangeMap();
        }

        public void SetDefaultValue(ValueType defaultValue)
        {
            DefaultValue = defaultValue;
        }

        public void Init(KeyType key)
        {
            Objects.Add(key, null);
            PropertyInfos.Add(key, null);
            Last_Values.Add(key, DefaultValue);
            IsDirtys.Add(key, false);
        }

        public virtual void UpdateIsDirty()
        {
            IsDirty    = !Value.Equals(Last_Value);
            Last_Value = Value;

            if (IsDirty)
                OnChange_Event.Broadcast(Value);
        }

        public virtual void UpdateIsDirtys(KeyType key)
        {
            ValueType value = (ValueType)PropertyInfos[key].GetValue(Objects[key], null);
            IsDirtys[key]    = !value.Equals(Last_Values[key]);
            Last_Values[key] = value;

            if (IsDirtys[key])
                OnChangeMap_Event.Broadcast(key, value);
        }
        /*
        bool operator ==(const TCsProperty_TMap& B) const
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

	     bool operator !=(const TCsProperty_TMap& B) const
	    {
		    return !(*this == B);
        }
        */

        public void Set(ValueType value)
        {
            Value = value;
            UpdateIsDirty();
        }

        public void Set(KeyType key, object o, string propertyName)
        {
            Objects[key] = o;
            PropertyInfos[key] = o.GetType().GetProperty(propertyName);
            UpdateIsDirtys(key);
        }

        public ValueType this[KeyType key]
        {
            get
            {
                if (Override_Subscript.IsBound())
                    return Override_Subscript.Execute(key);
                return (ValueType)PropertyInfos[key].GetValue(Objects[key], null);
            }
        }

        public ValueType Get() { return Value; }
        public ValueType Get(KeyType key)
        {
            if (Override_Get.IsBound())
                return Override_Get.Execute(key);
            return (ValueType)PropertyInfos[key].GetValue(Objects[key], null);
        }

        public ValueType GetEX(KeyType key) { return Get_Call.Execute(key); }

        public void Clear()
        {
            IsDirty = false;

            Dictionary<KeyType, object>.KeyCollection keys = Objects.Keys;

            foreach (KeyType key in keys)
		    {
                IsDirtys[key] = false;
            }
        }

        public void ResetValues()
        {
            Value = DefaultValue;
            Last_Value = Value;
            IsDirty = false;

            Dictionary<KeyType, object>.KeyCollection keys = Objects.Keys;

            foreach (KeyType key in keys)
            {
                Objects[key] = null;
                PropertyInfos[key] = null;
                Last_Values[key] = Value;
                IsDirtys[key] = false;
            }
        }

        public void Reset()
        {
            ResetValues();

            Get_Call.Unbind();
            OnChange_Event.Clear();
            OnChangeMap_Event.Clear();
        }

        public bool HasChanged() { return IsDirty; }
        public bool HasChanged(KeyType key) { return IsDirtys[key]; }

        public void Resolve()
        {
            UpdateIsDirty();

            Dictionary<KeyType, object>.KeyCollection keys = Objects.Keys;

            foreach (KeyType key in keys)
            {
                UpdateIsDirtys(key);
            }
            Clear();
        }
    }

        #endregion // Map Ref

        #region "Class"

    public class TCgPropertyClass<T> : CgProperty where T : class
    {
        public sealed class OnChange : TCgMulticastDelegate_OneParam<T> { }

        #region "Data Members"

        public T Value;
        public T Last_Value;

        protected bool IsDirty;

        public OnChange OnChange_Event;

        #endregion // Data Members

        public TCgPropertyClass()
        {
            OnChange_Event = new OnChange();
        }

        #region "Operators"

        public static bool operator ==(TCgPropertyClass<T> lhs, TCgPropertyClass<T> rhs)
        {
            if (object.ReferenceEquals(lhs, null))
                return object.ReferenceEquals(rhs, null);
            if (object.ReferenceEquals(rhs, null))
                return false;
            return lhs.Value.Equals(rhs.Value);
        }

        public static bool operator !=(TCgPropertyClass<T> lhs, TCgPropertyClass<T> rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(TCgPropertyClass<T> lhs, T rhs)
        {
            return lhs.Value.Equals(rhs);
        }

        public static bool operator !=(TCgPropertyClass<T> lhs, T rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(T lhs, TCgPropertyClass<T> rhs)
        {
            return lhs.Equals(rhs.Value);
        }

        public static bool operator !=(T lhs, TCgPropertyClass<T> rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is TCgPropertyClass<T>))
                return false;

            TCgPropertyClass<T> rhs = (TCgPropertyClass<T>)obj;

            if (!Value.Equals(rhs.Value)) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return Value.GetHashCode();
        }

        #endregion // Operators

        public override void UpdateIsDirty()
        {
            IsDirty = !Value.Equals(Last_Value);

            if (IsDirty)
                OnChange_Event.Broadcast(Value);
        }

        public void Set(T inValue)
        {
            Value = inValue;
            UpdateIsDirty();
        }

        public T Get() { return Value; }

        public override void Clear()
        {
            Last_Value = Value;
            IsDirty = false;
        }

        public override void ResetValue()
        {
            Value = default(T);
            Last_Value = Value;
            IsDirty = false;
        }

        public override void Reset()
        {
            ResetValue();

            OnChange_Event.Clear();
        }

        public override bool HasChanged() { return IsDirty; }
        public override void MarkDirty() { IsDirty = true; }

        public override void Resolve()
        {
            UpdateIsDirty();
            Clear();
        }
    }

        #endregion // Class

    #endregion // Property

    #region "Flags"

    public interface ICgFlag
    {
        bool IsEqual();
    }

    public abstract class CgFlag : ICgFlag
    {
        public abstract bool IsEqual();
    }

    public class TCgFlagType<T> : CgFlag where T : struct
    {
        public sealed class OnEqual : CgMulticastDelegate { }

        #region "Data Members"

        public T StartValue;
        public T EndValue;

        public OnEqual OnEqual_Event;

        #endregion // Data Members

        public TCgFlagType(T startValue, T endValue)
        {
            StartValue    = startValue;
            EndValue      = endValue;
            OnEqual_Event = new OnEqual();
        }

        #region "Operators"

        public static bool operator ==(TCgFlagType<T> lhs, TCgFlagType<T> rhs)
        {
            if (object.ReferenceEquals(lhs, null))
                return object.ReferenceEquals(rhs, null);
            if (object.ReferenceEquals(rhs, null))
                return false;
            return lhs.StartValue.Equals(rhs.StartValue);
        }

        public static bool operator !=(TCgFlagType<T> lhs, TCgFlagType<T> rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(TCgFlagType<T> lhs, T rhs)
        {
            return lhs.StartValue.Equals(rhs);
        }

        public static bool operator !=(TCgFlagType<T> lhs, T rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(T lhs, TCgFlagType<T> rhs)
        {
            return lhs.Equals(rhs.StartValue);
        }

        public static bool operator !=(T lhs, TCgFlagType<T> rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is TCgFlagType<T>))
                return false;

            TCgFlagType<T> rhs = (TCgFlagType<T>)obj;

            if (!StartValue.Equals(rhs.StartValue)) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return StartValue.GetHashCode();
        }

        #endregion // Operators

        public void Init(T startValue, T endValue)
        {
            StartValue = startValue;
            EndValue = endValue;
        }

        public void SetStart(T startValue)
        {
            StartValue = startValue;
        }

        public void SetEnd(T endValue)
        {
            EndValue = endValue;

            if (StartValue.Equals(EndValue))
                OnEqual_Event.Broadcast();
        }

        public T GetStart() { return StartValue; }
        public T GetEnd() { return EndValue; }

        public void ResetValues()
        {
            StartValue = default(T);
            EndValue = default(T);
        }

        public void Reset()
        {
            ResetValues();

            OnEqual_Event.Clear();
        }

        public override bool IsEqual() { return StartValue.Equals(EndValue); }
    }

    #endregion "Flags"

    #region "Attribute"

    public class TFCgAttributeValue<T> where T : struct
    {
        public T Value;
        public T UnSetValue;
        public bool IsSet;

        public TFCgAttributeValue(T value)
        {
            Value = value;
            UnSetValue = default(T);
            IsSet = true;
        }

        public void Set(T value)
        {
            Value = value;
            IsSet = true;
        }

        public void UnSet()
        {
            Value = UnSetValue;
            IsSet = false;
        }

        public bool IsValid()
        {
            return IsSet ? !Value.Equals(UnSetValue) : true;
        }
    }

    public class TFCgAttributeRef<T> where T : class
    {
        public T Ref;
        public T UnSetRef;
        public bool IsSet;

        public TFCgAttributeRef(T inRef)
        {
            Ref = inRef;
            UnSetRef = default(T);
            IsSet = true;
        }

        public void Set(T inRef)
        {
            Ref = inRef;
            IsSet = true;
        }

        public void UnSet()
        {
            Ref = UnSetRef;
            IsSet = false;
        }

        public bool IsValid()
        {
            return IsSet ? Ref != UnSetRef : true;
        }
    }
    
    public sealed class FCgAttribute
    {
        private Type ValueType;
        private object Value;
        private object UnSetValue;
        private bool IsSet;

        public FCgAttribute()
        {
            ValueType = null;
            Value = null;
            UnSetValue = null;
            IsSet = false;
        }

        public void Set(object value)
        {
            Value      = value;
            ValueType  = value != null ? value.GetType() : null;
            UnSetValue = ValueType != null ? default(ValueType) : null;

            if (ValueType != null &&
                ValueType.IsClass)
            {
                if (value.Equals(null))
                {
                    IsSet = false;
                }
                else
                {
                    IsSet = true;
                }
            }
        }

        public void UnSet()
        {
            ValueType  = null;
            Value      = null;
            UnSetValue = null;
            IsSet      = false;
        }

        public bool IsValid()
        {
            return IsSet ? !Value.Equals(UnSetValue) : true;
        }

        public object Get()
        {
            return Value;
        }
    }

    #endregion // Attribute
}