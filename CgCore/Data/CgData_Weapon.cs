namespace CgCore
{
    public class MCgData_Weapon : MCgData
    {
        string ItemShortCode;

        public virtual bool UseInventory() { return false; }
    }
}