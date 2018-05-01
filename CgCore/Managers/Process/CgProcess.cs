namespace CgCore
{
    using System.Diagnostics;

    public sealed class ECgProcess : ECgEnum_byte
    {
    }

    public sealed class CgProcessCache : CgPooledObjectCache<ECgProcess, TCgPooledObject<ECgProcess>>
    {
    }


    public class CgProcess : TCgPooledObject<ECgProcess>
    {
        public Process P;
        public bool IsOpen;

        public CgProcess() : base()
        {
            Cache = new CgProcessCache();
        }
    }
}
