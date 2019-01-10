#ifndef	__KSJ_CODE_H__
#define __KSJ_CODE_H__

/*-------------------------------------------------
	返回状态码
  ================================================*/
#define		RET_SUCCESS			    1      // 函数返回成功
#define		RET_PARAMERROR			-1     // 用户所传递的参数有误
#define		RET_MALLOCFAIL			-2     // 分配内存失败
#define		RET_NOTSUPPORT			-3     // 此函数的调用不被支持
#define		RET_DEVICENOTEXIST		-4     // 设备没有找到
#define		RET_DEVICENOTINIT		-5     // 设备没有初始化
#define		RET_VIOLATION			-6     // 此函数的调用与其他功能有冲突
#define		RET_NOPRIVILEGE			-7     // 没有特权
#define		RET_FAIL			    -8     // 函数调用失败（不做更详细的提示）
#define		RET_WRONG			    -9     // 调用错误
#define     RET_RECOVERY_SUCCESS    -10    // 设备进行了恢复并且恢复成功
#define     RET_RECOVERY_FAIL       -11    // 设备进行了恢复，但恢复失败了
#define     RET_BADFRAME            -12     // 由于UC500C在某些参数设置（RowSize, ColumnSize, RowSkip, ColumnSkip）后，紧接着的一帧会是无效帧
#define     RET_INVALIDFRAME        -13     // 数据传输中有错误，图像有部分数据丢失或没有图像数据（返回此值并不代表设备工作不正常）


#endif