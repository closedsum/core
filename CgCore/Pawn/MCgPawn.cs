namespace CgCore
{
    using System.Collections;
    using System.Collections.Generic;
    using UnityEngine;

    public class FCgPawnViewTraceInfo
    {
        public static readonly byte INVALID_TRACE_REQUEST_ID = 255;

        public bool bAsync;
        public bool bForce;
        public byte RequestId;

        public float Range;
        public float RangeSq;

        public Vector3 HitLocation;

        public RaycastHit HitResult;

        public List<RaycastHit> OutHits;

        public FCgPawnViewTraceInfo()
        {
            RequestId = INVALID_TRACE_REQUEST_ID;
        }
    }

    public class MCgPawn : MonoBehaviour, ICgObject
    {
        #region "Data Members"

            #region "Interface"

        private ulong _UniqueObjectId;
        public ulong UniqueObjectId
        {
            get { return _UniqueObjectId; }
            set { _UniqueObjectId = value; }
        }

            #endregion // Interface

            #region "Setup"

        public sealed class FOnSetupFinished : TCgMulticastDelegate_OneParam<byte> { }
        public FOnSetupFinished OnSetupFinished_Event;

            #endregion // Setup

            #region "State"

                #region "Health"

        public float Health;

        public FCgProperty_Ref_float HealthHandle;

        public sealed class FOnChange_Health : TCgMulticastDelegate_ThreeParams<byte, float, float> { }
        public FOnChange_Health OnChange_Health_Event;

                #endregion // Health

        //public sealed class FOnApplyDamage_Result : TCgMulticastDelegate_TwoParams<byte, FCgDamageResult> { }
        //public FOnApplyDamage_Result OnApplyDamage_Result_Event;

                #region "Spawn"

        public bool bFirstSpawn;

        public sealed class FOnFirstSpawn : TCgMulticastDelegate_OneParam<MCgPawn> { }
        public FOnFirstSpawn OnFirstSpawn_Event;

        public int SpawnCount;

        public Vector3 SpawnLocation;
        public Vector3 SpawnRotation;

        public float RespawnTime;

        public FCgRoutine HandleRespawnTimer_Internal_Routine;

        public sealed class FOnHandleRespawnTimerFinished : TCgMulticastDelegate_OneParam<byte>{}
        public FOnHandleRespawnTimerFinished OnHandleRespawnTimerFinished_Event;

        public bool bSpawnedAndActive;

               #endregion // Spawn

            #endregion // State

            #region "View"

        public ECgViewType CurrentViewType;

        public Vector3 CurrentViewRotation;
        public Vector3 CurrentViewRotationDelta;

        public Vector3 CurrentViewLocation;
        public Vector3 CurrentViewDir;
        public Vector3 CurrentViewDirXY;
        public Vector3 CurrentViewRight;
        public Vector3 CurrentViewRightXY;
        public Vector3 CurrentViewUp;

        public bool bPerformViewTrace;

        public FCgPawnViewTraceInfo ViewTraceInfo;

            #endregion // View

            #region "Body / Root"

        public Vector3 CurrentRootRotation;
        public Vector3 CurrentRootLocation;
        public Vector3 CurrentBodyLocation;
        public Vector3 CurrentFeetLocation;
        public Vector3 CurrentRootDir;
        public Vector3 CurrentRootDirXY;
        public Vector3 CurrentRootRight;
        public Vector3 CurrentRootRightXY;

            #endregion // Body / Root

            #region "Movement"

        private Transform MyTransform;

        public Vector3 CurrentVelocity;
        public Vector3 CurrentVelocityDir;
        public Vector3 CurrentVelocityXY;
        public Vector3 CurrentVelocityDirXY;
        public Vector3 CurrentVelocityZ;
        public Vector3 CurrentVelocityDirZ;
       
        public float CurrentSpeed;
        public float CurrentSpeedSq;
        public float CurrentSpeedXY;
        public float CurrentSpeedXYSq;
        public float CurrentSpeedZ;
        public float CurrentSpeedZSq;

        public Vector3 CurrentVelocityRight;
        public Vector3 CurrentVelocityRightXY;

        public Vector3 CurrentCapsuleVelocity;
        public Vector3 CurrentCapsuleVelocityDir;
        public Vector3 CurrentCapsuleVelocityXY;
        public Vector3 CurrentCapsuleVelocityDirXY;
        public Vector3 CurrentCapsuleVelocityZ;
        public Vector3 CurrentCapsuleVelocityDirZ;

        public float CurrentCapsuleSpeed;
        public float CurrentCapsuleSpeedSq;
        public float CurrentCapsuleSpeedXY;
        public float CurrentCapsuleSpeedXYSq;
        public float CurrentCapsuleSpeedZ;
        public float CurrentCapsuleSpeedZSq;

        public Vector3 CurrentCapsuleVelocityRight;
        public Vector3 CurrentCapsuleVelocityRightXY;

        public float CurrentMoveRightLeftValue;

            #endregion // Movement

            #region "Data"

        public bool bCacheData;

        public MCgData_Character MyData_Character;
        public MCgData_CharacterMeshSkin MyData_CharacterMeshSkin;
        public MCgData_CharacterMaterialSkin MyData_CharacterMaterialSkin;

            #endregion // Data

            #region "Weapons"

        public FECgWeaponSlot CurrentWeaponSlot;
        public TCgPropertyClass_Ref<FECgWeaponSlot> CurrentWeaponSlotHandle;

        public sealed class FOnChange_CurrentWeaponSlot : TCgMulticastDelegate_ThreeParams<byte, FECgWeaponSlot, FECgWeaponSlot> { }
        public FOnChange_CurrentWeaponSlot OnChange_CurrentWeaponSlot_Event;

        public byte CurrentWeaponIndex;
        public FECgWeaponSlot LastWeaponSlot;
        public byte LastWeaponIndex;
        public byte CurrentWeaponCount;
        public byte MaxWeaponCount;

        public List<MCgWeapon> Weapons;

        public List<MCgData_Weapon> Data_Weapons;
        public List<MCgData_WeaponMaterialSkin> Data_WeaponMaterialSkins;

             #endregion // Weapons

            #region Sense

            #endregion Sense

            #region "Managers"

        public FCgManager_Sense Manager_Sense;

            #endregion // Managers

        #endregion // Data Members

        // Use this for initialization
        void Start()
        {   
        }

        public virtual void Init()
        {
            MCgGameInstance.Get().RegisterUniqueObject(this);

            MyTransform = GetComponent<Transform>();
        }

        public virtual void OnUpdate(float deltaTime)
        {
            OnUpdate_Handle_Movement(deltaTime);
        }

        #region "Setup"

        public virtual void OnUpdate_HandleSetup()
        {
        }

        #endregion // Setup

        #region "State"

            #region "Health

        public virtual void SetHealth(float health)
        {

        }

        public virtual void OnChange_Health(float value)
        {

        }

        public virtual void Die()
        {

        }

            #endregion // Health

        public virtual void ApplyDamage(FCgDamageEvent e)
        {

        }

        public virtual void OnApplyDamage_Result(FCgDamageResult r)
        {

        }

            #region "Spawn"

        public virtual void OnFirstSpawn()
        {

        }

        public void HandleRespawnTimer()
        {

        }

        public static IEnumerator HandleRespawnTimer_Internal(MCgPawn p)
        {
            yield return null;
        }

        public virtual void OnHandleRespawnTimerFinished(byte mappingId)
        {

        }

            #endregion Spawn

            #region "Routine"

        public virtual bool AddRoutine(FCgRoutine r)
        {
            return false;
        }

        public virtual bool RemoveRoutine(FCgRoutine r)
        {
            return false;
        }

            #endregion // Routine

            #region "View"

        public virtual ECgViewType GetCurrentViewType()
        {
            return ECgViewType.MAX;
        }

        public virtual void PerformViewTrace()
        {

        }

        public virtual void PerformViewTrace_Respone(byte requestId, FCgTraceResponse response)
        {

        }

        public virtual void RecordView()
        {

        }

            #endregion // View

            #region "Body / Root"

        public virtual void RecordRoot()
        {

        }

            #endregion // Body / Root

            #region "Movement"

        public virtual void RecordVelocityAndSpeed()
        {

        }

            #endregion // Movement

            #region "Data"

        public MCgDataMapping GetDataMapping()
        {
            return null;
        }

        public T GetDataMapping<T>() where T : MCgDataMapping
        {
            return (T)GetDataMapping();
        }

        public MCgData_Character GetMyData_Character()
        {
            return MyData_Character;
        }

        public T GetMyData_Character<T>() where T : MCgData_Character
        {
            return (T)GetMyData_Character();
        }

        public MCgData_CharacterMeshSkin GetMyData_CharacterMeshSkin()
        {
            return MyData_CharacterMeshSkin;
        }

        public T GetMyData_CharacterMeshSkin<T>() where T : MCgData_CharacterMeshSkin
        {
            return (T)GetMyData_CharacterMeshSkin();
        }

        public MCgData_CharacterMaterialSkin GetMyData_CharacterMaterialSkin()
        {
            return MyData_CharacterMaterialSkin;
        }

        public T GetMyData_CharacterMaterialSkin<T>() where T : MCgData_CharacterMaterialSkin
        {
            return (T)GetMyData_CharacterMaterialSkin();
        }

        public virtual void SetDatas()
        {

        }

        public virtual void ApplyData_Character()
        {

        }

        public virtual void OnRespawn_ApplyData_Character()
        {

        }

            #endregion // data

            #region "Weapon"

        public MCgWeapon GetWeapon(FECgWeaponSlot slot)
        {
            return Weapons[slot.Value];
        }

        public T GetWeapon<T>(FECgWeaponSlot slot) where T : MCgWeapon
        {
            return (T)GetWeapon(slot);
        }

        public MCgWeapon GetCurrentWeapon()
        {
            return GetWeapon(CurrentWeaponSlot);
        }

        public T GetCurrentWeapon<T>() where T : MCgWeapon
        {
            return (T)GetCurrentWeapon();
        }

        public MCgData_Weapon GetData_Weapon(FECgWeaponSlot slot)
        {
            return Data_Weapons[slot.Value];
        }

        public T GetData_Weapon<T>(FECgWeaponSlot slot) where T : MCgData_Weapon
        {
            return (T)GetData_Weapon(slot);
        }

            #endregion // Weapon

        #endregion // State

        public virtual void OnUpdate_Handle_Movement(float deltaTime)
        {
            MyTransform.position += deltaTime * CurrentVelocity;
        }

        public void SetSpeed(float speed)
        {
            CurrentSpeed = speed;
            //CurrentVelocity = speed * CurrentDirection;
        }

        #region "Managers"

        public virtual FCgManager_Inventory GetMyManager_Inventory()
        {
            return null;
        }

        #endregion // Managers
    }
}
