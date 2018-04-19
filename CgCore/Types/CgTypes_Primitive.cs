// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
namespace CgCore
{
    using System.Collections.Generic;

    #region "Enums"

    public abstract class TCgEnum<T>
    {
        #region "Delegates"

        public delegate TCgEnum<T> Get(T t);
        public delegate TCgEnum<T> GetMAX();
        public delegate TCgEnum<T> ToType(string s);
        public delegate string ToStr(TCgEnum<T> e);

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
    }

    public class ECgEnum_byte : TCgEnum<byte>
    {
        public ECgEnum_byte() : base() { }
        public ECgEnum_byte(byte value) : base(value) { }
        public ECgEnum_byte(byte value, string name) : base(value, name) { }

        public static bool operator ==(ECgEnum_byte lhs, ECgEnum_byte rhs)
        {
            if (object.ReferenceEquals(lhs, null))
                return object.ReferenceEquals(rhs, null);
            if (object.ReferenceEquals(rhs, null))
                return false;
            return lhs.Value == rhs.Value && lhs.Name == rhs.Name;
        }

        public static bool operator !=(ECgEnum_byte lhs, ECgEnum_byte rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(ECgEnum_byte lhs, byte rhs)
        {
            return lhs.Value == rhs;
        }

        public static bool operator !=(ECgEnum_byte lhs, byte rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(byte lhs, ECgEnum_byte rhs)
        {
            return lhs == rhs.Value;
        }

        public static bool operator !=(byte lhs, ECgEnum_byte rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is ECgEnum_byte))
                return false;

            ECgEnum_byte rhs = (ECgEnum_byte)obj;

            if (Value != rhs.Value) return false;
            if (Name != rhs.Name) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return Value.GetHashCode() ^ Name.GetHashCode();
        }
    }

    public class ECgEnum_int : TCgEnum<int>
    {
        public ECgEnum_int() : base() { }
        public ECgEnum_int(int value) : base(value) { }
        public ECgEnum_int(int value, string name) : base(value, name) { }

        public static bool operator ==(ECgEnum_int lhs, ECgEnum_int rhs)
        {
            if (object.ReferenceEquals(lhs, null))
                return object.ReferenceEquals(rhs, null);
            if (object.ReferenceEquals(rhs, null))
                return false;
            return lhs.Value == rhs.Value && lhs.Name == rhs.Name;
        }

        public static bool operator !=(ECgEnum_int lhs, ECgEnum_int rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(ECgEnum_int lhs, int rhs)
        {
            return lhs.Value == rhs;
        }

        public static bool operator !=(ECgEnum_int lhs, int rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(int lhs, ECgEnum_int rhs)
        {
            return lhs == rhs.Value;
        }

        public static bool operator !=(int lhs, ECgEnum_int rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is ECgEnum_int))
                return false;

            ECgEnum_int rhs = (ECgEnum_int)obj;

            if (Value != rhs.Value) return false;
            if (Name != rhs.Name) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return Value.GetHashCode() ^ Name.GetHashCode();
        }
    }

    public class ECgEnum_uint : TCgEnum<uint>
    {
        public ECgEnum_uint() : base() { }
        public ECgEnum_uint(uint value) : base(value) { }
        public ECgEnum_uint(uint value, string name) : base(value, name) { }

        public static bool operator ==(ECgEnum_uint lhs, ECgEnum_uint rhs)
        {
            if (object.ReferenceEquals(lhs, null))
                return object.ReferenceEquals(rhs, null);
            if (object.ReferenceEquals(rhs, null))
                return false;
            return lhs.Value == rhs.Value && lhs.Name == rhs.Name;
        }

        public static bool operator !=(ECgEnum_uint lhs, ECgEnum_uint rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(ECgEnum_uint lhs, uint rhs)
        {
            return lhs.Value == rhs;
        }

        public static bool operator !=(ECgEnum_uint lhs, uint rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator ==(uint lhs, ECgEnum_uint rhs)
        {
            return lhs == rhs.Value;
        }

        public static bool operator !=(uint lhs, ECgEnum_uint rhs)
        {
            return !(lhs == rhs);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is ECgEnum_uint))
                return false;

            ECgEnum_uint rhs = (ECgEnum_uint)obj;

            if (Value != rhs.Value) return false;
            if (Name != rhs.Name) return false;
            return true;
        }

        public override int GetHashCode()
        {
            return Value.GetHashCode() ^ Name.GetHashCode();
        }
    }

    #endregion // Enums
}