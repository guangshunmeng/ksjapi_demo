unit KSJApiC;

interface
uses
    KSJApiB;
    
type
KSJ_PREVIEWMODE = (
  PM_RAWDATA,
  PM_RGBDATA
);
KSJ_PREVIEWCALLBACK = procedure( pImageData : PByte; nWidth : Integer; nHeight : Integer; nBitCount : Integer; lpContext : Integer ); stdcall;
PKSJ_PREVIEWMODE = ^KSJ_PREVIEWMODE;


function KSJ_PreviewSetFieldOfView( nChannel : Integer;  nColumnStart : Integer; nRowStart : Integer; nColumnSize : Integer; nRowSize : Integer; ColumnAddressMode : KSJ_ADDRESSMODE; RowAddressMode : KSJ_ADDRESSMODE ) : Integer; stdcall;

function KSJ_PreviewGetFieldOfView( nChannel : Integer;  pnColumnStart : PInteger; pnRowStart : PInteger; pnColumnSize : PInteger; pnRowSize : PInteger; pColumnAddressMode : PKSJ_ADDRESSMODE; pRowAddressMode : PKSJ_ADDRESSMODE ) : Integer; stdcall;

function KSJ_PreviewGetSize       ( nChannel : Integer;  pnWidth : PInteger; pnHeight : PInteger )  : Integer; stdcall;

function KSJ_PreviewGetSizeEx     ( nChannel : Integer;  pnWidth : PInteger; pnHeight : PInteger; pnBitCount : PInteger )  : Integer; stdcall;

function KSJ_PreviewSetPos        ( nChannel : Integer;  hWnd : THandle; x : Integer; y : Integer; nWidth : Integer; nHeight : Integer )  : Integer; stdcall;

function KSJ_PreviewGetPos        ( nChannel : Integer;  px : PInteger; py : PInteger; pnWidth : PInteger; pnHeight : PInteger )  : Integer; stdcall;

function KSJ_PreviewSetMode        ( nChannel : Integer;  PreviewMode : KSJ_PREVIEWMODE )  : Integer; stdcall;

function KSJ_PreviewGetMode        ( nChannel : Integer;  pPreviewMode : PKSJ_PREVIEWMODE )  : Integer; stdcall;

function KSJ_PreviewStart          ( nChannel : Integer;  bStart : Boolean )  : Integer; stdcall;

function KSJ_PreviewPause          ( nChannel : Integer;  bPause : Boolean )  : Integer; stdcall;

function KSJ_PreviewGetPausedData  ( nChannel : Integer;  pData : PByte )  : Integer; stdcall;

function KSJ_PreviewGetPausedDataEx  ( nChannel : Integer;  pData : PByte; pnWidth : PInteger; pnHeight : PInteger; pnBitCount : PInteger )  : Integer; stdcall;

function KSJ_PreviewGetFrameRate  ( nChannel : Integer;  fFrameRate : PSingle )  : Integer; stdcall;

function KSJ_PreviewSetCallback  ( nChannel : Integer;  pfPreviewCallback : KSJ_PREVIEWCALLBACK; lpContext : Integer )  : Integer; stdcall;


implementation
function KSJ_PreviewSetFieldOfView; external 'KSJApi.DLL' name 'KSJ_PreviewSetFieldOfView';
function KSJ_PreviewGetFieldOfView; external 'KSJApi.DLL' name 'KSJ_PreviewGetFieldOfView';
function KSJ_PreviewGetSize; external 'KSJApi.DLL' name 'KSJ_PreviewGetSize';
function KSJ_PreviewGetSizeEx; external 'KSJApi.DLL' name 'KSJ_PreviewGetSizeEx';
function KSJ_PreviewSetPos; external 'KSJApi.DLL' name 'KSJ_PreviewSetPos';
function KSJ_PreviewGetPos; external 'KSJApi.DLL' name 'KSJ_PreviewGetPos';
function KSJ_PreviewSetMode; external 'KSJApi.DLL' name 'KSJ_PreviewSetMode';
function KSJ_PreviewGetMode; external 'KSJApi.DLL' name 'KSJ_PreviewGetMode';
function KSJ_PreviewStart; external 'KSJApi.DLL' name 'KSJ_PreviewStart';
function KSJ_PreviewPause; external 'KSJApi.DLL' name 'KSJ_PreviewPause';
function KSJ_PreviewGetPausedData; external 'KSJApi.DLL' name 'KSJ_PreviewGetPausedData';
function KSJ_PreviewGetPausedDataEx; external 'KSJApi.DLL' name 'KSJ_PreviewGetPausedDataEx';
function KSJ_PreviewGetFrameRate; external 'KSJApi.DLL' name 'KSJ_PreviewGetFrameRate';
function KSJ_PreviewSetCallback; external 'KSJApi.DLL' name 'KSJ_PreviewSetCallback';
end.
 