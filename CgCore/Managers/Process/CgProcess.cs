namespace CgCore
{
    using System;
    using System.Diagnostics;
    using System.Collections.Generic;

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

    public enum ECgProcessMonitorOutputEventPurpose : byte
    {
        FireOnce,
        Loop,
        MAX
    }

    public sealed class CgProcessMonitorOutputEvent
    {
        public sealed class CompletedEvent : TCgMulticastDelegate_OneParam<string> { }

        private string Name;
        public ECgProcessMonitorOutputEventPurpose Purpose;
        private CgStringParagraph Paragraph;
        private bool Completed;
        private CompletedEvent Event;

        public CgProcessMonitorOutputEvent(string name, CgStringParagraph paragraph, ECgProcessMonitorOutputEventPurpose purpose = ECgProcessMonitorOutputEventPurpose.FireOnce)
        {
            Name = name;
            Paragraph = paragraph;
            Event = new CompletedEvent();
        }

        public void AddEvent(CompletedEvent.Event e)
        {
            Event.Add(e);
        }

        public void ProcessOutput(string output)
        {
            if (Completed)
                return;

            Paragraph.ProcessInput(output);

            Completed = Paragraph.HasCompleted();

            if (Completed)
            {
                Event.Broadcast(Name);
            }
        }

        public void Clear()
        {
            Completed = false;
            Paragraph.Clear();
        }

        public void Reset()
        {
            Clear();
            Event.Clear();
        }

        public bool HasCompleted()
        {
            return Completed;
        }
    }


    public class CgProcess : TCgPooledObject<ECgProcess>
    {
        public static CgConsoleVariableLog LogCommandRequest = new CgConsoleVariableLog("log.process.command.request", false, "Log Process Command Request", (int)ECgConsoleVariableFlag.Console);

        public sealed class OutputDataRecieved : TCgMulticastDelegate_TwoParams<object, DataReceivedEventArgs> { }
        public sealed class ErrorDataRecieved : TCgMulticastDelegate_TwoParams<object, DataReceivedEventArgs> { }
        public sealed class Exited : TCgMulticastDelegate_TwoParams<object, EventArgs> { }

        #region "Data Members"

        public Process P;
        public bool IsRunning;

        public OutputDataRecieved OutputDataRecieved_Event;
        public ErrorDataRecieved ErrorDataRecieved_Event;
        public Exited Exited_Event;

        private List<CgProcessMonitorOutputEvent> MonitorOuputEvents;

        #endregion // Data Members

        public CgProcess() : base()
        {
            Cache = new CgProcessCache();

            OutputDataRecieved_Event = new OutputDataRecieved();
            ErrorDataRecieved_Event = new ErrorDataRecieved();
            Exited_Event = new Exited();

            MonitorOuputEvents = new List<CgProcessMonitorOutputEvent>();
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

            foreach (CgProcessMonitorOutputEvent e in pay.MonitorOuputEvents)
            {
                MonitorOuputEvents.Add(e);
            }

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

            MonitorOuputEvents.Clear();

            if (IsRunning)
                P.Kill();

            IsRunning = false;
        }

        #endregion // Interface

        public void RunCommand(string command)
        {
            P.StandardInput.Write(command);
            P.StandardInput.Write("\n");
            P.StandardInput.Flush();

            // TODO: Have an option to choose encoding
            /*
            // Convert string command to bytes
            byte[] buffer = System.Text.Encoding.ASCII.GetBytes(command);
            P.StandardInput.BaseStream.Write(buffer, 0, buffer.Length);
            // Add new line
            buffer = System.Text.Encoding.ASCII.GetBytes("\n");
            P.StandardInput.BaseStream.Write(buffer, 0, buffer.Length);
            // Flush command to be processed
            P.StandardInput.BaseStream.Flush();
            */
        }

        public void AddMonitorOuputEvent(CgProcessMonitorOutputEvent e)
        {
            MonitorOuputEvents.Add(e);
        }

        public void ProcessMonitorOutputEvents(string ouput)
        {
            int count = MonitorOuputEvents.Count;

            for (int i = count - 1; i >= 0; --i)
            {
                CgProcessMonitorOutputEvent o = MonitorOuputEvents[i];

                o.ProcessOutput(ouput);

                if (o.HasCompleted())
                {
                    o.Clear();

                    // FireOnce
                    if (o.Purpose == ECgProcessMonitorOutputEventPurpose.FireOnce)
                        MonitorOuputEvents.RemoveAt(i);
                }
            }
        }

        public void OnOutputDataRecieved(object sender, DataReceivedEventArgs e)
        {
            OutputDataRecieved_Event.Broadcast(sender, e);
            ProcessMonitorOutputEvents(e.Data);
        }

        public void OnErrorDataRecieved(object sender, DataReceivedEventArgs e)
        {
            ErrorDataRecieved_Event.Broadcast(sender, e);
            ProcessMonitorOutputEvents(e.Data);
        }

        public void OnExited(object sender, EventArgs e)
        {
            Exited_Event.Broadcast(sender, e);

            IsRunning = false;
        }
    }
}
