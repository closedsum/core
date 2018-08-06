namespace CgCore
{
    using System;

    [Flags]
    public enum ECgConsoleVariableFlag
    {
        Default = 0,
        Console = 1
    }

    public interface ICgConsoleVariable
    {
        string Name { get; set; }
        string Description { get; set; }
        int Flag { get; set; }
    }

    public class TCgConsoleVariable<T> : ICgConsoleVariable where T : struct
    {
        #region "Data Members"

        private string name;
        public string Name
        {
            get
            {
                return name;
            }
            set
            {
                name = value;
            }
        }

        private string description;
        public string Description
        {
            get
            {
                return description;
            }
            set
            {
                description = value;
            }
        }

        private int flag;
        public int Flag
        {
            get
            {
                return flag;
            }
            set
            {
                flag = value;
            }
        }

        public TCgProperty<T> Value;

        #endregion // Data Members

        public TCgConsoleVariable(string inName, T inValue, string inDescription, int inFlag)
        {
            Name = inName;
            Value = new TCgProperty<T>();
            Set(inValue);
            Description = inDescription;
            Flag = inFlag;

            ConsoleCommandsRepository.Instance.RegisterCommand(inName, Set);
        }

        public T Get()
        {
            return Value.Get();
        }

        public void Set(T inValue)
        {
            Value.Set(inValue);
        }

        public string Set(params string[] args)
        {
            // Check at least ONE argument is passed
            if (args.Length == 0)
                return "Failed to set " + Name;
            // Check argument is of type T
            object o = Convert.ChangeType((object)args[0], typeof(T));

            if (o == null)
                return "Invalid argument for " + Name + ". Must be type of " + typeof(T);

            Value.Set((T)Convert.ChangeType((object)args[0], typeof(T)));

            return Name + " set to " + Value.ToString();
        }

        public void AddEvent(TCgMulticastDelegate_OneParam<T>.Event del)
        {
            Value.OnChange_Event.Add(del);
        }
    }

    public sealed class FCgConsoleVariableLog : TCgConsoleVariable<bool>
    {
        public FCgConsoleVariableLog(string inName, bool inValue, string inDescription, int inFlag) : base(inName, inValue, inDescription, inFlag) { }

        public bool Log()
        {
            return Get();
        }
    }

    public sealed class FCgConsoleVariableDraw : TCgConsoleVariable<bool>
    {
        public FCgConsoleVariableDraw(string inName, bool inValue, string inDescription, int inFlag) : base(inName, inValue, inDescription, inFlag) { }

        public bool Draw()
        {
            return Get();
        }
    }
}
