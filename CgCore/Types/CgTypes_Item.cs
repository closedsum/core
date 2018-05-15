namespace CgCore
{
    using System;
    using System.Collections.Generic;

    using Newtonsoft.Json;

    public sealed class ECgItemType : ECgEnum_byte
    {
        public ECgItemType(byte value, string name) : base(value, name) { }
    }

    public sealed class ECgItemTypeEqualityComparer : IEqualityComparer<ECgItemType>
    {
        public bool Equals(ECgItemType lhs, ECgItemType rhs)
        {
            return lhs == rhs;
        }

        public int GetHashCode(ECgItemType x)
        {
            return x.GetHashCode();
        }
    }

    public class EMCgItemType : ECgEnumMap<ECgItemType, byte>
    {
        private static EMCgItemType _Instance;
        public static EMCgItemType Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgItemType();
                }
                return _Instance;
            }
        }

        public static EMCgItemType Get()
        {
            return Instance;
        }
    }

    public sealed class CgItemHistory
    {
        public Guid OwnerId;

        //ECsItemOwner OwnerType;

        public string OwnerName;

        Dictionary<string, object> Members;

        public CgItemHistory(Guid id, string name)
        {

        }
    }

    public sealed class CgItemProduct
    {
        public Guid Id;
        public string Name;

        CgItemHistory CurrentHistory;
        List<CgItemHistory> PreviousHistories;

        public CgItemProduct(Guid id, string name)
        {
            Id = id;
            Name = name;
            //CurrentHistory = new CgItemHistory();
            PreviousHistories = new List<CgItemHistory>();
        }
    }

    public sealed class CgItem
    {
        public bool IsAllocated;
        public bool IsSaved;

        public ECgItemType Type;

        public Guid Id;
        public string Address;
        public string ShortCode;
        public DateTime Created;
        public TimeSpan LifeTime;

        List<Guid> Contents;

        Dictionary<Guid, CgItemProduct> Products;

        public CgItem()
        {

        }

        public void ToJson()
        {
            
        }
    }
}