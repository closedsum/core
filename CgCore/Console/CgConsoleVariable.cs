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

        private string _Name;
        public string Name
        {
            get
            {
                return _Name;
            }
            set
            {
                _Name = value;
            }
        }

        private string _Description;
        public string Description
        {
            get
            {
                return _Description;
            }
            set
            {
                _Description = value;
            }
        }

        private int _Flag;
        public int Flag
        {
            get
            {
                return _Flag;
            }
            set
            {
                _Flag = value;
            }
        }

        public TCgProperty<T> Value;

        #endregion // Data Members

        public TCgConsoleVariable(string name, T value, string description, int flag)
        {
            Name = name;
            Value = new TCgProperty<T>();
            Set(value);
            Description = description;
            Flag = flag;

            ConsoleCommandsRepository.Instance.RegisterCommand(name, Set);
        }

        public T Get()
        {
            return Value.Get();
        }

        public virtual void Set(T value)
        {
            Value.Set(value);
        }

        public virtual string Set(params string[] args)
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

    public class FCgConsoleVariable_bool : TCgConsoleVariable<bool>
    {
        public FCgConsoleVariable_bool(string name, bool value, string description, int flag) : base(name, value, description, flag) { }

        public override void Set(bool value)
        {
            Value.Set(value);
        }

        public override string Set(params string[] args)
        {
            // Check at least ONE argument is passed
            if (args.Length == 0)
                return "Failed to set " + Name;
            // Check argument is of type bool
            bool bValue = false;

            if (bool.TryParse(args[0], out bValue))
            {
                Value.Set(bValue);
                return Name + " set to " + Value.ToString();
            }
            // Check for 1 or 0
            else
            {
                // int
                int iValue = 0;
                if (Int32.TryParse(args[0], out iValue))
                {
                    if (iValue == 0)
                    {
                        Value.Set(false);
                        return Name + " set to " + Value.ToString();
                    }

                    if (iValue == 1)
                    {
                        Value.Set(true);
                        return Name + " set to " + Value.ToString();
                    }
                    return "Invalid value for " + Name + ". Must be true, false, 1, or 0.";
                }
                // float
                float fValue = 0.0f;
                    
                if (float.TryParse(args[0], out fValue))
                {
                    if (fValue == 0.0)
                    {
                        Value.Set(false);
                        return Name + " set to " + Value.ToString();
                    }

                    if (fValue == 1.0)
                    {
                        Value.Set(true);
                        return Name + " set to " + Value.ToString();
                    }
                    return "Invalid value for " + Name + ". Must be true, false, 1, or 0.";
                }
            }
            return "Invalid argument for " + Name + ". Must be type of " + typeof(bool);
        }
    }

    public sealed class FCgConsoleVariableLog : FCgConsoleVariable_bool
    {
        public FCgConsoleVariableLog(string name, bool value, string description, int flag) : base(name, value, description, flag) { }

        public bool Log()
        {
            return Get();
        }
    }

    public sealed class FCgConsoleVariableDraw : FCgConsoleVariable_bool
    {
        public FCgConsoleVariableDraw(string name, bool value, string description, int flag) : base(name, value, description, flag) { }

        public bool Draw()
        {
            return Get();
        }
    }
}
