namespace CgCore
{
    using System;
    using System.Diagnostics;

    public sealed class ECgProcess : ECgEnum_byte
    {
        public ECgProcess(byte value, string name) : base(value, name) { }
    }
    
    public class EMCgProcess : ECgEnumMap<ECgProcess, byte>
    {
        private static EMCgProcess _Instance;
        public static EMCgProcess Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new EMCgProcess();
                }
                return _Instance;
            }
        }

        public static EMCgProcess Get()
        {
            return Instance;
        }
    }

    public sealed class CgProcessCache : CgPooledObjectCache<ECgProcess, TCgPooledObject<ECgProcess>>
    {
    }

    public class CgProcess : TCgPooledObject<ECgProcess>
    {
        public sealed class OutputDataRecieved : TCgMulticastDelegate_TwoParams<object, DataReceivedEventArgs> { }
        public sealed class ErrorDataRecieved : TCgMulticastDelegate_TwoParams<object, DataReceivedEventArgs> { }
        public sealed class Exited : TCgMulticastDelegate_TwoParams<object, EventArgs> { }

        #region "Data Members"

        public Process P;
        public bool IsRunning;

        public OutputDataRecieved OutputDataRecieved_Event;
        public ErrorDataRecieved ErrorDataRecieved_Event;
        public Exited Exited_Event;

        #endregion // Data Members

        public CgProcess() : base()
        {
            Cache = new CgProcessCache();

            OutputDataRecieved_Event = new OutputDataRecieved();
            ErrorDataRecieved_Event = new ErrorDataRecieved();
            Exited_Event = new Exited();
        }

        #region "Interface"

        public override void Allocate(int activeIndex, ICgPooledObjectPayload payload)
        {
            base.Allocate(activeIndex, payload);

            CgProcessPayload pay = (CgProcessPayload)payload;

            P.StartInfo.CreateNoWindow = pay.CreateNoWindow;
            P.StartInfo.UseShellExecute = pay.UseShellExecute;
            P.StartInfo.FileName = pay.FileName;
            P.StartInfo.Arguments = pay.Arguments;
            P.StartInfo.ErrorDialog = pay.ErrorDialog;
            P.StartInfo.RedirectStandardInput = pay.RedirectStandardInput;
            P.StartInfo.RedirectStandardOutput = pay.RedirectStandardOutput;
            P.StartInfo.RedirectStandardError = pay.RedirectStandardError;
            P.EnableRaisingEvents = pay.EnableRaisingEvents;

            pay.OutputDataRecieved_Event.CopyTo(OutputDataRecieved_Event);
            pay.ErrorDataRecieved_Event.CopyTo(ErrorDataRecieved_Event);
            pay.Exited_Event.CopyTo(Exited_Event);

            IsRunning = true;

            P.Start();

            if (pay.RedirectStandardError)
                P.BeginErrorReadLine();
            if (pay.RedirectStandardOutput)
                P.BeginOutputReadLine();
        }

        public override void DeAllocate()
        {
            base.DeAllocate();

            OutputDataRecieved_Event.Clear();
            ErrorDataRecieved_Event.Clear();
            Exited_Event.Clear();

            if (IsRunning)
                P.Kill();

            IsRunning = false;
        }

        #endregion // Interface

        public void RunCommand(string command)
        {
            // Convert string command to bytes
            byte[] buffer = System.Text.Encoding.ASCII.GetBytes(command);
            P.StandardInput.BaseStream.Write(buffer, 0, buffer.Length);
            // Add new line
            buffer = System.Text.Encoding.ASCII.GetBytes("\n");
            P.StandardInput.BaseStream.Write(buffer, 0, buffer.Length);
            // Flush command to be processed
            P.StandardInput.BaseStream.Flush();
        }

        public void OnOutputDataRecieved(object sender, DataReceivedEventArgs e)
        {
            OutputDataRecieved_Event.Broadcast(sender, e);
        }

        public void OnErrorDataRecieved(object sender, DataReceivedEventArgs e)
        {
            ErrorDataRecieved_Event.Broadcast(sender, e);
        }

        public void OnExited(object sender, EventArgs e)
        {
            Exited_Event.Broadcast(sender, e);

            IsRunning = false;
        }
    }
}
