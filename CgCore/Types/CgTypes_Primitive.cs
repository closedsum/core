﻿// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System;
    using System.Collections.Generic;

    #region "Enums"

    public abstract class TCgEnum<T> where T : struct
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

    #endregion // Enums

    #region "Primitive Types"

    public class TCgPrimitiveType<T> where T : struct
    {
        #region "Data Members"

        public T Value;
        public T Last_Value;

        protected bool IsDirty;

        #endregion // Data Members

        public TCgDelegate_OneParam<T> OnChange_Event;

        #region "Operators"

        public static bool operator ==(TCgPrimitiveType<T> lhs, TCgPrimitiveType<T> rhs)
        {
            if (object.ReferenceEquals(lhs, null))
                return object.ReferenceEquals(rhs, null);
            if (object.ReferenceEquals(rhs, null))
                return false;
            return lhs.Value.Equals(rhs.Value);
        }

        public static bool operator !=(TCgPrimitiveType<T> lhs, TCgPrimitiveType<T> rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(TCgPrimitiveType<T> lhs, T rhs)
        {
            return lhs.Value.Equals(rhs);
        }

        public static bool operator !=(TCgPrimitiveType<T> lhs, T rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(T lhs, TCgPrimitiveType<T> rhs)
        {
            return lhs.Equals(rhs.Value);
        }

        public static bool operator !=(T lhs, TCgPrimitiveType<T> rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is TCgPrimitiveType<T>))
                return false;

            TCgPrimitiveType<T> rhs = (TCgPrimitiveType<T>)obj;

            if (!Value.Equals(rhs.Value)) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return Value.GetHashCode();
        }

        #endregion // Operators

        public void UpdateIsDirty()
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

        public T Get(){ return Value; }

        public void Clear()
        {
            Last_Value  = Value;
            IsDirty     = false;
        }

        public void ResetValue()
        {
            Value       = default(T);
            Last_Value  = Value;
            IsDirty     = false;
        }

        public void Reset()
        {
            ResetValue();

            OnChange_Event.Clear();
        }

        public bool HasChanged(){ return IsDirty; }
        public void MarkDirty() { IsDirty = true; }

        public void Resolve()
        {
            UpdateIsDirty();
            Clear();
        }
    }

    #endregion // Primitive Types
}