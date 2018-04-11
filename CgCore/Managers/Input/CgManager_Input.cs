namespace CgCore
{
    using System;
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class CgManager_Input
    {
        #region "Constants"

        public static readonly ushort CG_INPUT_POOL_SIZE = 65535;
        public static readonly ushort CS_MAX_INPUT_FRAMES = 300;

        #endregion // Constants

        #region "Delegates"

        public delegate void CgManagerInput_Action(ECgInputAction action);
        public delegate void CgManagerInput_Axis(ECgInputAction action, float val);
        public delegate void CgManagerInput_Location_Raw(Vector3 v);

        #endregion // Delegates

        #region "Data Members"

        public MonoBehaviour InputOwner;

        private CgKeyInput[] RawKeyInputs;
        public List<CgKeyInput> RawKeyInputsPressed;

        protected ECgInputAction InputAction_MAX;
        protected byte INPUT_ACTION_MAX;

        public CgInput[] InputPool;

        public List<CgInput> QueuedInputsForNextFrame;

        private ushort CurrentInputPoolIndex;

        public CgInputFrame[] InputFrames;

        public int CurrentInputFrameIndex;

        CgInputFrame CurrentInputFrame;

        public int CurrentInputActionMap;

        #region "Actions"

        protected List<CgInput_Base> Inputs;
        protected List<CgInputInfo> Infos;
        protected List<ECgInputEvent> Actions;
        protected List<ECgInputEvent> Last_Actions;

                #region "Pressed Events"

        public CgManagerInput_Action Default_Event;
        public CgManagerInput_Action FirstPressed_Event;
        public CgManagerInput_Action Pressed_Event;
        public CgManagerInput_Action FirstReleased_Event;

                #endregion // Pressed Events

                #region "Axis Events

        public CgManagerInput_Axis Axis_Event;
        public CgManagerInput_Axis Axis_FirstMoved_Event;
        public CgManagerInput_Axis Axis_Moved_Event;
        public CgManagerInput_Axis Axis_FirstStationary_Event;
        public CgManagerInput_Axis Axis_Stationary_Event;

                #endregion // Axis Events

                #region "Location Events"

                    // Mouse

        public Vector3 CurrentMousePosition;

        public CgManagerInput_Location_Raw Mouse_Location_Raw;

                    // VR


                #endregion // Location Events

            #endregion // Action

        #endregion // Data Members

        public CgManager_Input()
        {
            // InputPool
            InputPool = new CgInput[CG_INPUT_POOL_SIZE];

            for (ushort i = 0; i < CG_INPUT_POOL_SIZE; ++i)
            {
                InputPool[i] = new CgInput(i);
            }

            QueuedInputsForNextFrame = new List<CgInput>();

            // InputFrames
            InputFrames = new CgInputFrame[CS_MAX_INPUT_FRAMES];

            for (ushort i = 0; i < CS_MAX_INPUT_FRAMES; ++i)
            {
                InputFrames[i] = new CgInputFrame();
            }

            // Initialize array of RawKeyInputs
            Array keyValues = Enum.GetValues(typeof(KeyCode));
            int keyCodeCount = keyValues.Length;

            RawKeyInputs = new CgKeyInput[keyCodeCount];

            for (int i = 0; i < keyCodeCount; ++i)
            {
                KeyCode key = (KeyCode)keyValues.GetValue(i);

                RawKeyInputs[i] = new CgKeyInput(key);
            }

            RawKeyInputsPressed = new List<CgKeyInput>();
        }

        private void RecordRawInputs()
        {
            RawKeyInputsPressed.Clear();

            int len = RawKeyInputs.Length;

            for (int i = 0; i < len; ++i)
            {
                CgKeyInput keyInput = RawKeyInputs[i];
                KeyCode key         = keyInput.Key;
                ECgInputEvent e     = keyInput.Event;

                // Pressed
                if (Input.GetKey(key))
                {
                    if (e == ECgInputEvent.FirstPressed)
                        keyInput.Set(ECgInputEvent.Pressed, Time.time, Time.unscaledTime, 0);
                    else
                        keyInput.Set(ECgInputEvent.FirstPressed, Time.time, Time.unscaledTime, 0);
                    RawKeyInputsPressed.Add(keyInput);
                }
                // Released
                else
                {
                    if (e == ECgInputEvent.FirstStationary)
                        keyInput.Set(ECgInputEvent.FirstReleased, Time.time, Time.unscaledTime, 0);
                    else
                        keyInput.Set(ECgInputEvent.Released, Time.time, Time.unscaledTime, 0);
                }
            }
        }

        public virtual void PreProcessInput(float deltaTime)
        {
            RecordRawInputs();

            CurrentMousePosition = Input.mousePosition;

            if (Mouse_Location_Raw != null)
                Mouse_Location_Raw(CurrentMousePosition);

            // VR
        }

        public virtual void PostProcessInput(float deltaTime)
        {
            // TODO: Potentially also capture sustained "released" inputs

            // TODO: This would be the place to process an action that is a combination of multiple inputs in a frame (or over multiple frames)

            CgInputFrame InputFrame = InputFrames[CurrentInputFrameIndex];

            // Add Queued Inputs
            int QueuedInputCount = QueuedInputsForNextFrame.Capacity;

            for (int i = 0; i < QueuedInputCount; ++i)
            {
                InputFrame.Inputs.Add(QueuedInputsForNextFrame[i]);
            }
            QueuedInputsForNextFrame.Clear();

            // Set FirstReleased Events to Released after 1 Frame

            // TODO: Potentially Optimize to O(n) versus O(n^2)
            for (byte i = 0; i < INPUT_ACTION_MAX; ++i)
            {
                CgInputInfo info      = Infos[i];
                ECgInputAction action = ECgInputAction.Get(i);
                int inputCount        = InputFrame.Inputs.Capacity;

                // Transition From FirstPressed to Pressed
                if (info.Event == ECgInputEvent.FirstPressed &&
                    info.Last_Event == ECgInputEvent.FirstPressed)
                {
                    bool Found = false;

                    for (byte j = 0; j < inputCount; ++j)
                    {
                        if (InputFrame.Inputs[j].Action == action)
                        {
                            Found = true;
                            break;
                        }
                    }

                    if (!Found)
                        info.Event = ECgInputEvent.Pressed;
                }
                // Transition from FirstReleased to Released
                if (info.Event == ECgInputEvent.FirstReleased &&
                    info.Last_Event == ECgInputEvent.FirstReleased)
                {
                    bool Found = false;

                    for (byte j = 0; j < inputCount; ++j)
                    {
                        if (InputFrame.Inputs[j].Action == action)
                        {
                            Found = true;
                            break;
                        }
                    }

                    if (!Found)
                        info.Event = ECgInputEvent.Released;
                }
                // Transition From FireMoved to Moved
                if (info.Event == ECgInputEvent.FirstMoved &&
                    info.Last_Event == ECgInputEvent.FirstMoved)
                {
                    bool Found = false;

                    for (byte j = 0; j < inputCount; ++j)
                    {
                        if (InputFrame.Inputs[j].Action == action)
                        {
                            Found = true;
                            break;
                        }
                    }

                    if (!Found)
                        info.Event = ECgInputEvent.Moved;
                }
                // Transition from FirstStationary to Stationary
                if (info.Event == ECgInputEvent.FirstStationary &&
                    info.Last_Event == ECgInputEvent.FirstStationary)
                {
                    bool Found = false;

                    for (byte j = 0; j < inputCount; ++j)
                    {
                        if (InputFrame.Inputs[j].Action == action)
                        {
                            Found = true;
                            break;
                        }
                    }

                    if (!Found)
                        info.Event = ECgInputEvent.Stationary;
                }
                // Update Last_Actions.
                info.Last_Event = info.Event;

                // Currently NO Bindings for PRESSED Inputs, so manually add them
                if (info.Event == ECgInputEvent.Pressed)
                    AddInput(action, ECgInputEvent.Pressed);
            }
            // Process Inputs
            int _inputCount = InputFrame.Inputs.Capacity;

            for (byte i = 0; i < _inputCount; ++i)
            {
                ProcessInput(InputOwner, null, InputFrame.Inputs[i], deltaTime);
            }

            /*
            // Log Actions
            if (CsCVarLogInputs->GetInt() == CS_CVAR_SHOW_LOG)
            {
                const FString InputActionMapAsString = (*InputActionMapMaskToString)(CurrentInputActionMap);

                UE_LOG(LogCs, Log, TEXT("ACsManager_Input::PostProcessInput: ActionMap: %s Frame: %d Time: %f DeltaTime: %f Count: %d"), *InputActionMapAsString, InputFrame.Frame, InputFrame.Time, InputFrame.DeltaTime, InputFrame.Inputs.Num());

                for (uint8 I = 0; I < InputCount; ++I)
                {
                    const FCsInput* Input = InputFrame.Inputs[I];

                    const FString&Action = (*InputActionToString)(Input->Action);
                    const FString&Event = ECsInputEvent::ToString(Input->Event);

                    // Void - No Value
                    if ((CsCVarLogInputAll->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogInputActions->GetInt() == CS_CVAR_SHOW_LOG) &&
                        Infos[(uint8)Input->Action]->ValueType == ECsInputValue::Void)
                    {
                        UE_LOG(LogCs, Log, TEXT("ACsManager_Input::PostProcessInput: %s: %s"), *Action, *Event);
                    }
                    // Float
                    if ((CsCVarLogInputAll->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogInputAxis->GetInt() == CS_CVAR_SHOW_LOG) &&
                        Infos[(uint8)Input->Action]->ValueType == ECsInputValue::Float)
                    {
                        UE_LOG(LogCs, Log, TEXT("ACsManager_Input::PostProcessInput: %s: %s Value: %f"), *Action, *Event, Input->Value);
                    }
                    // Vector
                    if ((CsCVarLogInputAll->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogInputLocations->GetInt() == CS_CVAR_SHOW_LOG) &&
                        Infos[(uint8)Input->Action]->ValueType == ECsInputValue::Vector)
                    {
                        UE_LOG(LogCs, Log, TEXT("ACsManager_Input::PostProcessInput: %s: %s Value: %s"), *Action, *Event, *Input->Location.ToString());
                    }
                    // Rotator
                    if ((CsCVarLogInputAll->GetInt() == CS_CVAR_SHOW_LOG || CsCVarLogInputRotations->GetInt() == CS_CVAR_SHOW_LOG) &&
                        Infos[(uint8)Input->Action]->ValueType == ECsInputValue::Rotator)
                    {
                        UE_LOG(LogCs, Log, TEXT("ACsManager_Input::PostProcessInput: %s: %s Value: %s"), *Action, *Event, *Input->Rotation.ToString());
                    }
                }
            }
            */
            // Copy the Current Input Frame
            CurrentInputFrame = InputFrame;
            // Determine Game Events
            //DetermineGameEvents(InputFrame.Inputs);
        }

        public virtual void ProcessInput(MonoBehaviour actionOwner, CgInput previousInput, CgInput currentInput, float deltaTime)
        {
            if (currentInput == null)
                return;
        }

        public void AllocateInput(ECgInputAction action, ECgInputEvent e, float value = 0f, Vector3 Location = new Vector3(), Vector3 Rotation = new Vector3())
        {
        }

        public virtual void AddInput(ECgInputAction action, ECgInputEvent e, float value = 0f, Vector3 Location = new Vector3(), Vector3 Rotation = new Vector3())
        {
        }
    }
}
