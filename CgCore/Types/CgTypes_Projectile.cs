namespace CgCore
{
    public class CgData_ProjectileRef
    {
        public TCgAssetRef<CgData_Projectile> Data;
        public int Data_LoadFlags;

        private CgData_Projectile Data_Internal;

        public CgData_ProjectileRef()
        {
            //CS_SET_BLUEPRINT_BITFLAG(Data_LoadFlags, ECsLoadFlags::Game);
        }

        /*
        FCsData_ProjectilePtr& operator=(const FCsData_ProjectilePtr& B)
        {
            Data = B.Data;
            Data_LoadFlags = B.Data_LoadFlags;
            Data_Internal = B.Data_Internal;
            return *this;
        }

        bool operator ==(const FCsData_ProjectilePtr& B) const
	    {
		    return Data == B.Data && Data_LoadFlags == B.Data_LoadFlags && Data_Internal == B.Data_Internal;
	    }

        bool operator !=(const FCsData_ProjectilePtr& B) const
	    {
		    return !(*this == B);
        }
        */
        public CgData_Projectile Get()
	    {
		    return Data_Internal;
	    }
    }
}
