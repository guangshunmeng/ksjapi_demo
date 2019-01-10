unit KSJCode;

interface

const
  RET_SUCCESS			       = 1;     // Function Success
  RET_PARAMERROR			   = -1;    // Parameter Error
  RET_MALLOCFAIL			   = -2;    // Memory Allocate Fail
  RET_NOTSUPPORT			   = -3;    // This type of Device not support this Function
  RET_DEVICENOTEXIST	   = -4;    // Device not exist
  RET_DEVICENOTINIT		   = -5;    // Device not Initialed
  RET_VIOLATION			     = -6;    // Operation violated
  RET_NOPRIVILEGE			   = -7;    // Operation No Privilege
  RET_FAIL			         = -8;    // Function Fail
  RET_WRONG			         = -9;    // Error
  RET_RECOVERY_SUCCESS   = -10;   // Device recovery successful
  RET_RECOVERY_FAIL      = -11;   // Device recovery fail
  RET_BADFRAME           = -12;   // Is bad frame
  RET_INVALIDFRAME       = -13;   // Is invalid frame

implementation

end.
