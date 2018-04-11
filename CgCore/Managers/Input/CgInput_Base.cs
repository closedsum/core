namespace CgCore
{
    public abstract class CgInput_Base
    {
        public ECgInputAction Action;
        public CgInputInfo Info;
        public int ActionMap;
        public CgManager_Input Manager_Input;

        public CgInput_Base()
        {
            Action = ECgInputAction.NULL;
            ActionMap = 0;
            Manager_Input = null;
        }
    }
}
