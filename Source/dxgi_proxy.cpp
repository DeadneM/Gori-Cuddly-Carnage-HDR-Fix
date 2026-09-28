extern "C" {
typedef void* HANDLE; typedef void* HMODULE; typedef void* HINSTANCE; typedef void* FARPROC; typedef void* LPVOID; typedef const void* LPCVOID; typedef void* HWND; typedef void* HMONITOR; typedef void* HDC; typedef void* HGDIOBJ; typedef void* HBITMAP; typedef void* HBRUSH; typedef void* HFONT; typedef const wchar_t* LPCWSTR; typedef wchar_t* LPWSTR; typedef const char* LPCSTR; typedef unsigned long DWORD; typedef unsigned long ULONG; typedef unsigned int UINT; typedef unsigned long long UINT64; typedef unsigned long long SIZE_T; typedef long LONG; typedef long HRESULT; typedef int BOOL; typedef short SHORT; typedef unsigned short WORD; typedef unsigned char BYTE; typedef float FLOAT; typedef long long LONG_PTR; typedef unsigned long long WPARAM; typedef long long LPARAM; typedef long long LRESULT;
struct POINT { LONG x; LONG y; }; struct RECT { LONG left,top,right,bottom; };
__declspec(dllimport) DWORD __stdcall GetSystemDirectoryW(wchar_t*,DWORD);
__declspec(dllimport) HMODULE __stdcall LoadLibraryW(const wchar_t*);
__declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE,const char*);
__declspec(dllimport) DWORD __stdcall GetModuleFileNameW(HMODULE,wchar_t*,DWORD);
__declspec(dllimport) BOOL __stdcall DisableThreadLibraryCalls(HMODULE);
__declspec(dllimport) BOOL __stdcall VirtualProtect(LPVOID,SIZE_T,DWORD,DWORD*);
__declspec(dllimport) SHORT __stdcall GetAsyncKeyState(int);
__declspec(dllimport) BOOL __stdcall GetCursorPos(POINT*);
__declspec(dllimport) BOOL __stdcall ScreenToClient(HWND,POINT*);
__declspec(dllimport) BOOL __stdcall GetClientRect(HWND,RECT*);
HMONITOR __stdcall MonitorFromWindow(HWND,DWORD);
LONG_PTR __stdcall SetWindowLongPtrW(HWND,int,LONG_PTR);
LRESULT __stdcall CallWindowProcW(LONG_PTR,HWND,UINT,WPARAM,LPARAM);
__declspec(dllimport) int __stdcall DrawTextW(HDC,LPCWSTR,int,RECT*,UINT);
__declspec(dllimport) int __stdcall FillRect(HDC,const RECT*,HBRUSH);
__declspec(dllimport) HDC __stdcall CreateCompatibleDC(HDC);
__declspec(dllimport) HBITMAP __stdcall CreateDIBSection(HDC,const void*,UINT,void**,HANDLE,DWORD);
__declspec(dllimport) BOOL __stdcall DeleteDC(HDC);
__declspec(dllimport) HFONT __stdcall CreateFontW(int,int,int,int,int,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,DWORD,LPCWSTR);
__declspec(dllimport) HBRUSH __stdcall CreateSolidBrush(DWORD);
__declspec(dllimport) BOOL __stdcall DeleteObject(HGDIOBJ);
__declspec(dllimport) BOOL __stdcall RoundRect(HDC,int,int,int,int,int,int);
__declspec(dllimport) HGDIOBJ __stdcall SelectObject(HDC,HGDIOBJ);
__declspec(dllimport) int __stdcall SetBkMode(HDC,int);
__declspec(dllimport) DWORD __stdcall SetTextColor(HDC,DWORD);
}
extern "C" int _fltused=0;

LONG_PTR __stdcall SetWindowLongPtrW(HWND h,int idx,LONG_PTR val){
    typedef LONG_PTR(__stdcall*F)(HWND,int,LONG_PTR); static F f=0; static HMODULE u=0;
    if(!f){if(!u)u=LoadLibraryW(L"user32.dll");if(u)f=(F)GetProcAddress(u,"SetWindowLongPtrW");}
    return f?f(h,idx,val):0;
}
LRESULT __stdcall CallWindowProcW(LONG_PTR prev,HWND h,UINT m,WPARAM w,LPARAM l){
    typedef LRESULT(__stdcall*F)(LONG_PTR,HWND,UINT,WPARAM,LPARAM); static F f=0; static HMODULE u=0;
    if(!f){if(!u)u=LoadLibraryW(L"user32.dll");if(u)f=(F)GetProcAddress(u,"CallWindowProcW");}
    return f?f(prev,h,m,w,l):0;
}
HMONITOR __stdcall MonitorFromWindow(HWND h,DWORD flags){
    typedef HMONITOR(__stdcall*F)(HWND,DWORD); static F f=0; static HMODULE u=0;
    if(!f){if(!u)u=LoadLibraryW(L"user32.dll");if(u)f=(F)GetProcAddress(u,"MonitorFromWindow");}
    return f?f(h,flags):0;
}
extern "C" void* memset(void*d,int c,unsigned long long n){unsigned char*p=(unsigned char*)d;for(unsigned long long i=0;i<n;i++)p[i]=(unsigned char)c;return d;}
extern "C" void* memcpy(void*d,const void*s,unsigned long long n){unsigned char*a=(unsigned char*)d;const unsigned char*b=(const unsigned char*)s;for(unsigned long long i=0;i<n;i++)a[i]=b[i];return d;}

#define DLL_PROCESS_ATTACH 1
#define PAGE_EXECUTE_READWRITE 0x40
#define VK_F10 0x79
#define VK_LBUTTON 0x01
#define GWLP_WNDPROC (-4)
#define WM_MOVE 0x0003
#define WM_WINDOWPOSCHANGED 0x0047
#define WM_DISPLAYCHANGE 0x007E
#define WM_MOUSEMOVE 0x0200
#define WM_LBUTTONDOWN 0x0201
#define WM_LBUTTONUP 0x0202
#define WM_MOUSEWHEEL 0x020A
#define MONITOR_DEFAULTTONEAREST 2
#define TRANSPARENT 1
#define FW_NORMAL 400
#define FW_BOLD 700
#define DEFAULT_CHARSET 1
#define OUT_DEFAULT_PRECIS 0
#define CLIP_DEFAULT_PRECIS 0
#define CLEARTYPE_QUALITY 5
#define DEFAULT_PITCH 0
#define FF_DONTCARE 0
#define DT_LEFT 0x0
#define DT_CENTER 0x1
#define DT_RIGHT 0x2
#define DT_VCENTER 0x4
#define DT_SINGLELINE 0x20
#define DIB_RGB_COLORS 0
#define BI_RGB 0
#define E_FAIL ((HRESULT)0x80004005L)
#define D3D11_CREATE_DEVICE_BGRA_SUPPORT 0x20
#define D3D11_BIND_CONSTANT_BUFFER 0x4
#define D3D11_BIND_SHADER_RESOURCE 0x8
#define D3D11_BIND_RENDER_TARGET 0x20
#define D3D11_USAGE_DYNAMIC 2
#define D3D11_CPU_ACCESS_WRITE 0x10000
#define D3D11_MAP_WRITE_DISCARD 4
#define D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST 4
#define D3D12_RESOURCE_STATE_PRESENT 0
#define D3D12_RESOURCE_STATE_RENDER_TARGET 0x4
#define DXGI_FORMAT_B8G8R8A8_UNORM 87
#define PANEL_W 720
#define PANEL_H 760
#define MAX_BUFFERS 8

struct GUID { unsigned long Data1; unsigned short Data2; unsigned short Data3; unsigned char Data4[8]; };
static bool geq(const GUID&a,const GUID&b){if(a.Data1!=b.Data1||a.Data2!=b.Data2||a.Data3!=b.Data3)return false;for(int i=0;i<8;i++)if(a.Data4[i]!=b.Data4[i])return false;return true;}
static const GUID IID_IUnknown={0,0,0,{0xC0,0,0,0,0,0,0,0x46}};
static const GUID IID_ID3D12Device={0x189819f1,0x1db6,0x4b57,{0xbe,0x54,0x18,0x21,0x33,0x9b,0x85,0xf7}};
static const GUID IID_ID3D11On12Device={0x85611e73,0x70a9,0x490e,{0x96,0x14,0xa9,0xe3,0x02,0x77,0x79,0x04}};
static const GUID IID_ID3D11Resource={0xdc8e63f3,0xd12b,0x4952,{0xb4,0x7b,0x5e,0x45,0x02,0x6a,0x86,0x2d}};
static const GUID IID_IDXGISwapChain3={0x94d99bdb,0xf1f8,0x4ab0,{0xb2,0x36,0x7d,0xa0,0x17,0x0e,0xda,0xb1}};
static const GUID IID_IDXGISwapChain4={0x3d585d5a,0xbd4a,0x489e,{0xb1,0xf4,0x3d,0xbc,0xb6,0x45,0x2f,0xfb}};
static const GUID IID_IDXGIOutput6={0x068346e8,0xaaec,0x4b84,{0xad,0xd7,0x13,0x7f,0x51,0x3f,0x77,0xa1}};

struct DXGI_RATIONAL{UINT Numerator,Denominator;};
struct DXGI_MODE_DESC{UINT Width,Height;DXGI_RATIONAL RefreshRate;UINT Format,ScanlineOrdering,Scaling;};
struct DXGI_SAMPLE_DESC{UINT Count,Quality;};
struct DXGI_SWAP_CHAIN_DESC{DXGI_MODE_DESC BufferDesc;DXGI_SAMPLE_DESC SampleDesc;UINT BufferUsage,BufferCount;HWND OutputWindow;BOOL Windowed;UINT SwapEffect,Flags;};
struct DXGI_OUTPUT_DESC1{wchar_t DeviceName[32];RECT DesktopCoordinates;BOOL AttachedToDesktop;UINT Rotation;HMONITOR Monitor;UINT BitsPerColor;UINT ColorSpace;FLOAT RedPrimary[2],GreenPrimary[2],BluePrimary[2],WhitePoint[2];FLOAT MinLuminance,MaxLuminance,MaxFullFrameLuminance;};
struct D3D11_RESOURCE_FLAGS{UINT BindFlags,MiscFlags,CPUAccessFlags,StructureByteStride;};
struct D3D11_TEXTURE2D_DESC{UINT Width,Height,MipLevels,ArraySize,Format;DXGI_SAMPLE_DESC SampleDesc;UINT Usage,BindFlags,CPUAccessFlags,MiscFlags;};
struct D3D11_BUFFER_DESC{UINT ByteWidth,Usage,BindFlags,CPUAccessFlags,MiscFlags,StructureByteStride;};
struct D3D11_SAMPLER_DESC{UINT Filter,AddressU,AddressV,AddressW;float MipLODBias;UINT MaxAnisotropy,ComparisonFunc;float BorderColor[4];float MinLOD,MaxLOD;};
struct D3D11_MAPPED_SUBRESOURCE{void*pData;UINT RowPitch,DepthPitch;};
struct D3D11_VIEWPORT{float TopLeftX,TopLeftY,Width,Height,MinDepth,MaxDepth;};
struct BITMAPINFOHEADER{DWORD biSize;LONG biWidth,biHeight;WORD biPlanes,biBitCount;DWORD biCompression,biSizeImage;LONG biXPelsPerMeter,biYPelsPerMeter;DWORD biClrUsed,biClrImportant;};
struct RGBQUAD{BYTE rgbBlue,rgbGreen,rgbRed,rgbReserved;};
struct BITMAPINFO{BITMAPINFOHEADER bmiHeader;RGBQUAD bmiColors[1];};
struct GoriHDRSettings{int allowHDR,enableHDR,uiComposite,useHDR,outputDevice,gamut,uiLevel10,nits,adapter;};

static HMODULE gSelf=0,gReal=0,gAsi=0;
static HRESULT (__stdcall *pCreateDXGIFactory)(const GUID*,void**)=0;
static HRESULT (__stdcall *pCreateDXGIFactory1)(const GUID*,void**)=0;
static HRESULT (__stdcall *pCreateDXGIFactory2)(UINT,const GUID*,void**)=0;
static volatile long gInitState=0;

// ASI API
static int (__stdcall *apiReady)()=0;static int (__stdcall *apiPatchState)()=0;static void (__stdcall *apiGetSettings)(GoriHDRSettings*)=0;static void (__stdcall *apiGetStatus)(wchar_t*,int)=0;static void (__stdcall *apiGetFlavor)(wchar_t*,int)=0;static void (__stdcall *apiAdjust)(int,int)=0;static int (__stdcall *apiApply)()=0;static void (__stdcall *apiReload)()=0;static void (__stdcall *apiPreset)()=0;static void (__stdcall *apiTick)()=0;static void (__stdcall *apiSetOutputHDRAvailable)(int)=0;static int (__stdcall *apiGetEffectiveHDRRequested)()=0;

static void** vt(void*o){return o?*(void***)o:0;}
template<class T> static T vf(void*o,int i){return (T)(vt(o)[i]);}
static ULONG rel(void*o){if(!o)return 0;typedef ULONG(__stdcall*F)(void*);return vf<F>(o,2)(o);}
static ULONG addref(void*o){if(!o)return 0;typedef ULONG(__stdcall*F)(void*);return vf<F>(o,1)(o);}
static HRESULT qi(void*o,const GUID&g,void**p){if(!o||!p)return E_FAIL;typedef HRESULT(__stdcall*F)(void*,const GUID*,void**);return vf<F>(o,0)(o,&g,p);}
static bool ok(HRESULT h){return h>=0;}
static DWORD rgb(BYTE r,BYTE g,BYTE b){return (DWORD)(r|((DWORD)g<<8)|((DWORD)b<<16));}
static unsigned long slen(const char*s){unsigned long n=0;while(s&&s[n])n++;return n;}
static unsigned long wlen(const wchar_t*s){unsigned long n=0;while(s&&s[n])n++;return n;}
static void wcpy(wchar_t*d,int cap,const wchar_t*s){if(!d||cap<1)return;int i=0;if(s)while(s[i]&&i+1<cap){d[i]=s[i];i++;}d[i]=0;}
static void wcat(wchar_t*d,int cap,const wchar_t*s){int n=(int)wlen(d),i=0;if(!s)return;while(s[i]&&n+i+1<cap){d[n+i]=s[i];i++;}d[n+i]=0;}
static void istr(int v,wchar_t*b,int cap){if(cap<2)return;int p=0;if(v<0){b[p++]=L'-';v=-v;}wchar_t t[20];int n=0;do{t[n++]=(wchar_t)(L'0'+v%10);v/=10;}while(v&&n<19);while(n&&p+1<cap)b[p++]=t[--n];b[p]=0;}
static void f10str(int v,wchar_t*b,int cap){wchar_t a[32];istr(v/10,a,32);wcpy(b,cap,a);wcat(b,cap,L".");wchar_t z[2]={(wchar_t)(L'0'+(v<0?-v:v)%10),0};wcat(b,cap,z);}
static void appendName(wchar_t*path,DWORD cap,const wchar_t*name){DWORD n=0;while(n<cap&&path[n])n++;if(n&&path[n-1]!=L'\\'&&path[n-1]!=L'/'){if(n+1<cap)path[n++]=L'\\';}DWORD i=0;while(name[i]&&n+i+1<cap){path[n+i]=name[i];i++;}if(n+i<cap)path[n+i]=0;}
static void sibling(wchar_t*path,DWORD cap,const wchar_t*file){DWORD n=GetModuleFileNameW(gSelf,path,cap);if(!n||n>=cap){path[0]=0;return;}DWORD cut=n;while(cut>0&&path[cut-1]!=L'\\'&&path[cut-1]!=L'/')cut--;DWORD i=0;while(file[i]&&cut+i+1<cap){path[cut+i]=file[i];i++;}path[cut+i]=0;}
static HMODULE loadSystem(const wchar_t*name){wchar_t p[520]={0};DWORD n=GetSystemDirectoryW(p,520);if(!n||n>=500)return 0;appendName(p,520,name);return LoadLibraryW(p);}
static void dxlog(const char*){}
static void bindApi(){if(!gAsi)return;apiReady=(int(__stdcall*)())GetProcAddress(gAsi,"GoriHDR_IsReady");apiPatchState=(int(__stdcall*)())GetProcAddress(gAsi,"GoriHDR_GetPatchState");apiGetSettings=(void(__stdcall*)(GoriHDRSettings*))GetProcAddress(gAsi,"GoriHDR_GetSettings");apiGetStatus=(void(__stdcall*)(wchar_t*,int))GetProcAddress(gAsi,"GoriHDR_GetStatus");apiGetFlavor=(void(__stdcall*)(wchar_t*,int))GetProcAddress(gAsi,"GoriHDR_GetConfigFlavor");apiAdjust=(void(__stdcall*)(int,int))GetProcAddress(gAsi,"GoriHDR_Adjust");apiApply=(int(__stdcall*)())GetProcAddress(gAsi,"GoriHDR_Apply");apiReload=(void(__stdcall*)())GetProcAddress(gAsi,"GoriHDR_Reload");apiPreset=(void(__stdcall*)())GetProcAddress(gAsi,"GoriHDR_Preset");apiTick=(void(__stdcall*)())GetProcAddress(gAsi,"GoriHDR_Tick");apiSetOutputHDRAvailable=(void(__stdcall*)(int))GetProcAddress(gAsi,"GoriHDR_SetOutputHDRAvailable");apiGetEffectiveHDRRequested=(int(__stdcall*)())GetProcAddress(gAsi,"GoriHDR_GetEffectiveHDRRequested");}

// Factory + swapchain hooks
static void* gQueue=0;static HWND gHwnd=0;static void* gSwap3=0;static bool gNeedFullInit=true;static bool gNeedBackbuffers=true;
static volatile bool gTransition=false;static int gSuspendFrames=0;
static HWND gInputHwnd=0;static LONG_PTR gOldWndProc=0;static volatile LONG gMouseClientX=-32768,gMouseClientY=-32768;static volatile LONG gClickX=-32768,gClickY=-32768;static volatile LONG gClickSerial=0;static LONG gSeenClickSerial=0;
typedef HRESULT(__stdcall*FQI)(void*,const GUID*,void**);
typedef HRESULT(__stdcall*FCS)(void*,void*,const DXGI_SWAP_CHAIN_DESC*,void**);
typedef HRESULT(__stdcall*FCSH)(void*,void*,HWND,const void*,const void*,void*,void**);
typedef HRESULT(__stdcall*FCSC)(void*,void*,const void*,void*,void**);
struct FactoryRec{void**v;FQI qi;FCS cs;FCSH csh;FCSC csc;bool extended;};static FactoryRec gFac[8];static int gFacN=0;
typedef HRESULT(__stdcall*FPresent)(void*,UINT,UINT);typedef HRESULT(__stdcall*FPresent1)(void*,UINT,UINT,const void*);typedef HRESULT(__stdcall*FResize)(void*,UINT,UINT,UINT,UINT,UINT);typedef HRESULT(__stdcall*FResize1)(void*,UINT,UINT,UINT,UINT,UINT,const UINT*,void*const*);typedef HRESULT(__stdcall*FSetFS)(void*,BOOL,void*);typedef HRESULT(__stdcall*FResizeTarget)(void*,const DXGI_MODE_DESC*);typedef HRESULT(__stdcall*FCheckColorSpaceSupport)(void*,UINT,UINT*);typedef HRESULT(__stdcall*FSetColorSpace1)(void*,UINT);typedef HRESULT(__stdcall*FSetHDRMetaData)(void*,UINT,UINT,const void*);
struct SwapRec{void**v;FPresent p;FPresent1 p1;FResize r;FResize1 r1;FSetFS fs;FResizeTarget rt;FCheckColorSpaceSupport checkcs;FSetColorSpace1 cs1;FSetHDRMetaData hdr;};static SwapRec gSw[8];static int gSwN=0;
struct DXGI_HDR_METADATA_HDR10_MIN{WORD RedPrimary[2],GreenPrimary[2],BluePrimary[2],WhitePoint[2];UINT MaxMasteringLuminance,MinMasteringLuminance;WORD MaxContentLightLevel,MaxFrameAverageLightLevel;};
static volatile LONG gColorSpaceCalls=0,gHDRMetaCalls=0,gDXGICompletionCalls=0;static bool gColorSpaceCompleted=false;static UINT gCompletionSupport=0;static HRESULT gCompletionCheckHR=E_FAIL,gCompletionSetHR=E_FAIL;static UINT gLastColorSpace=0xFFFFFFFFu,gLastHDRMetaType=0xFFFFFFFFu,gLastHDRMetaSize=0,gSwapFormat=0;static HRESULT gLastColorSpaceHR=E_FAIL,gLastHDRMetaHR=E_FAIL;static UINT gMetaMaxMaster=0,gMetaMinMaster=0;static WORD gMetaMaxCLL=0,gMetaMaxFALL=0;
static bool gUiDirty=true;static bool gOutputKnown=false,gOutputHDR=false,gEffectiveHDR=false,gOutputDirty=true;static HMONITOR gOutputMonitor=0;static UINT gOutputColorSpace=0xFFFFFFFFu,gOutputBitsPerColor=0;static FLOAT gOutputMaxLuminance=0.0f;static UINT gOutputPollCounter=0;static UINT gRestoreColorSpace=0;static bool gHaveNativeHDRMeta=false;static DXGI_HDR_METADATA_HDR10_MIN gNativeHDRMeta={};
static bool patchSlot(void**s,void*v){DWORD old=0;if(!VirtualProtect(s,sizeof(void*),PAGE_EXECUTE_READWRITE,&old))return false;*s=v;DWORD z=0;VirtualProtect(s,sizeof(void*),old,&z);return true;}
static FactoryRec* findFac(void*o){void**v=vt(o);for(int i=0;i<gFacN;i++)if(gFac[i].v==v)return &gFac[i];return 0;}
static SwapRec* findSw(void*o){void**v=vt(o);for(int i=0;i<gSwN;i++)if(gSw[i].v==v)return &gSw[i];return 0;}
static bool requestedHDR(){if(!apiReady||!apiReady())return false;if(apiGetEffectiveHDRRequested)return apiGetEffectiveHDRRequested()!=0;GoriHDRSettings s={};if(!apiGetSettings)return false;apiGetSettings(&s);return s.enableHDR!=0;}
static bool queryContainingOutput(void*swap,bool*outHDR){if(outHDR)*outHDR=false;if(!swap)return false;typedef HRESULT(__stdcall*FCO)(void*,void**);void*out=0;if(!ok(vf<FCO>(swap,15)(swap,&out))||!out)return false;void*o6=0;HRESULT q=qi(out,IID_IDXGIOutput6,&o6);if(!ok(q)||!o6){rel(out);return false;}DXGI_OUTPUT_DESC1 d={};typedef HRESULT(__stdcall*FGD1)(void*,DXGI_OUTPUT_DESC1*);HRESULT h=vf<FGD1>(o6,27)(o6,&d);rel(o6);rel(out);if(!ok(h))return false;
    // Cross-check the swapchain output with the monitor that actually owns the game window.
    // On multi-monitor systems we refuse to apply PQ if DXGI still reports a stale output.
    HMONITOR wm=gHwnd?MonitorFromWindow(gHwnd,MONITOR_DEFAULTTONEAREST):0;
    if(wm&&d.Monitor&&wm!=d.Monitor){gOutputMonitor=d.Monitor;gOutputColorSpace=d.ColorSpace;gOutputBitsPerColor=d.BitsPerColor;gOutputMaxLuminance=d.MaxLuminance;return false;}
    gOutputMonitor=d.Monitor;gOutputColorSpace=d.ColorSpace;gOutputBitsPerColor=d.BitsPerColor;gOutputMaxLuminance=d.MaxLuminance;
    bool hdr=d.AttachedToDesktop&&d.ColorSpace==12;
    if(outHDR)*outHDR=hdr;return true;}
static void notifyOutputHDR(bool hdr){if(apiSetOutputHDRAvailable)apiSetOutputHDRAvailable(hdr?1:0);}
static void setTelemetryClear(HRESULT hm,HRESULT hc,UINT cs){gLastHDRMetaType=0;gLastHDRMetaSize=0;gLastHDRMetaHR=hm;gHDRMetaCalls++;gLastColorSpace=cs;gLastColorSpaceHR=hc;gColorSpaceCalls++;gColorSpaceCompleted=false;gUiDirty=true;}
static void disableSwapHDR(void*swap,SwapRec*r){if(!swap||!r)return;HRESULT hm=0,hc=0;UINT cs=gRestoreColorSpace;if(cs==12||cs==0xFFFFFFFFu)cs=0;if(r->hdr)hm=r->hdr(swap,0,0,0);if(r->cs1)hc=r->cs1(swap,cs);setTelemetryClear(hm,hc,cs);}
static bool completeHDR10ColorSpaceAfterNativeMetadata(void*self,SwapRec*r);
static void enableSwapHDRFromCapturedMetadata(void*swap,SwapRec*r){if(!swap||!r||!gHaveNativeHDRMeta||!r->hdr)return;HRESULT hm=r->hdr(swap,1,sizeof(DXGI_HDR_METADATA_HDR10_MIN),&gNativeHDRMeta);gLastHDRMetaType=1;gLastHDRMetaSize=sizeof(DXGI_HDR_METADATA_HDR10_MIN);gLastHDRMetaHR=hm;gHDRMetaCalls++;if(ok(hm))completeHDR10ColorSpaceAfterNativeMetadata(swap,r);gUiDirty=true;}
static void refreshOutputState(void*swap,bool force){if(!swap)return;if(!force&&!gOutputDirty&&(++gOutputPollCounter%60)!=0)return;gOutputDirty=false;bool wasKnown=gOutputKnown,wasHDR=gOutputHDR;HMONITOR wasMon=gOutputMonitor;UINT wasCS=gOutputColorSpace;bool hdr=false;bool known=queryContainingOutput(swap,&hdr);if(!known){gOutputKnown=false;gOutputHDR=false;return;}bool changed=!wasKnown||hdr!=wasHDR||gOutputMonitor!=wasMon||gOutputColorSpace!=wasCS;gOutputKnown=true;gOutputHDR=hdr;if(changed)notifyOutputHDR(hdr);}
static void syncHDRPolicy(void*swap,bool forceOutputRefresh){if(!swap)return;refreshOutputState(swap,forceOutputRefresh);SwapRec*r=findSw(swap);if(!r)return;bool req=requestedHDR();
    if(!gOutputKnown){if(gLastColorSpace==12)disableSwapHDR(swap,r);gEffectiveHDR=false;return;}
    bool effective=req&&gOutputHDR;if(effective!=gEffectiveHDR){if(!effective)disableSwapHDR(swap,r);else enableSwapHDRFromCapturedMetadata(swap,r);gEffectiveHDR=effective;}else if(!effective&&(gLastColorSpace==12||gLastHDRMetaType==1))disableSwapHDR(swap,r);}
static bool factory2Plus(const GUID*g){if(!g)return false;unsigned long d=g->Data1;return d==0x50c83a1c||d==0x25483823||d==0x1bc6ea02||d==0x7632e1f5||d==0xc1b6694f||d==0xa4966eed;}
static bool factoryIID(const GUID*g){if(!g)return false;unsigned long d=g->Data1;return d==0x7b7166ec||d==0x770aae78||factory2Plus(g);}

static void releaseBackbuffers();static void resetRenderer();static void onSwap(void*sc,void*queue,HWND hwnd);static void logSwapFormat();static void logTelemetrySummary();static void syncHDRPolicy(void*swap,bool forceOutputRefresh);
static HRESULT __stdcall HookPresent(void*self,UINT sync,UINT flags);static HRESULT __stdcall HookPresent1(void*self,UINT sync,UINT flags,const void*params);static HRESULT __stdcall HookResize(void*self,UINT n,UINT w,UINT h,UINT fmt,UINT flags);static HRESULT __stdcall HookResize1(void*self,UINT n,UINT w,UINT h,UINT fmt,UINT flags,const UINT*nodes,void*const*queues);static HRESULT __stdcall HookSetFS(void*self,BOOL fullscreen,void*out);static HRESULT __stdcall HookResizeTarget(void*self,const DXGI_MODE_DESC*mode);static HRESULT __stdcall HookSetColorSpace1(void*self,UINT cs);static HRESULT __stdcall HookSetHDRMetaData(void*self,UINT type,UINT size,const void*meta);
static HRESULT __stdcall HookFactoryQI(void*self,const GUID*iid,void**out);static HRESULT __stdcall HookCS(void*self,void*dev,const DXGI_SWAP_CHAIN_DESC*desc,void**out);static HRESULT __stdcall HookCSH(void*self,void*dev,HWND hwnd,const void*desc,const void*fs,void*restrictOut,void**out);static HRESULT __stdcall HookCSC(void*self,void*dev,const void*desc,void*restrictOut,void**out);

static void hookSwapVtable(void*sc){if(!sc||gSwN>=8)return;void**v=vt(sc);for(int i=0;i<gSwN;i++)if(gSw[i].v==v)return;SwapRec&r=gSw[gSwN++];r.v=v;r.p=(FPresent)v[8];r.fs=(FSetFS)v[10];r.r=(FResize)v[13];r.rt=(FResizeTarget)v[14];r.p1=0;r.r1=0;r.checkcs=0;r.cs1=0;r.hdr=0;patchSlot(&v[8],(void*)HookPresent);patchSlot(&v[10],(void*)HookSetFS);patchSlot(&v[13],(void*)HookResize);patchSlot(&v[14],(void*)HookResizeTarget);
// If this is SwapChain1+ the Present1 slot is valid; only patch on the SwapChain3 interface we explicitly QI below.
}
static void hookSwap3Vtable(void*sc3){if(!sc3||gSwN>=8)return;void**v=vt(sc3);for(int i=0;i<gSwN;i++)if(gSw[i].v==v){if(!gSw[i].p1){gSw[i].p1=(FPresent1)v[22];gSw[i].r1=(FResize1)v[39];patchSlot(&v[22],(void*)HookPresent1);patchSlot(&v[39],(void*)HookResize1);}if(!gSw[i].checkcs)gSw[i].checkcs=(FCheckColorSpaceSupport)v[37];if(!gSw[i].cs1){gSw[i].cs1=(FSetColorSpace1)v[38];patchSlot(&v[38],(void*)HookSetColorSpace1);}return;}SwapRec&r=gSw[gSwN++];r.v=v;r.p=(FPresent)v[8];r.fs=(FSetFS)v[10];r.r=(FResize)v[13];r.rt=(FResizeTarget)v[14];r.p1=(FPresent1)v[22];r.r1=(FResize1)v[39];r.checkcs=(FCheckColorSpaceSupport)v[37];r.cs1=(FSetColorSpace1)v[38];r.hdr=0;patchSlot(&v[8],(void*)HookPresent);patchSlot(&v[10],(void*)HookSetFS);patchSlot(&v[13],(void*)HookResize);patchSlot(&v[14],(void*)HookResizeTarget);patchSlot(&v[22],(void*)HookPresent1);patchSlot(&v[38],(void*)HookSetColorSpace1);patchSlot(&v[39],(void*)HookResize1);}
static void hookSwap4Vtable(void*sc4){if(!sc4)return;void**v=vt(sc4);for(int i=0;i<gSwN;i++)if(gSw[i].v==v){if(!gSw[i].checkcs)gSw[i].checkcs=(FCheckColorSpaceSupport)v[37];if(!gSw[i].cs1){gSw[i].cs1=(FSetColorSpace1)v[38];patchSlot(&v[38],(void*)HookSetColorSpace1);}if(!gSw[i].hdr){gSw[i].hdr=(FSetHDRMetaData)v[40];patchSlot(&v[40],(void*)HookSetHDRMetaData);}return;}if(gSwN>=8)return;SwapRec&r=gSw[gSwN++];r.v=v;r.p=(FPresent)v[8];r.fs=(FSetFS)v[10];r.r=(FResize)v[13];r.rt=(FResizeTarget)v[14];r.p1=(FPresent1)v[22];r.r1=(FResize1)v[39];r.checkcs=(FCheckColorSpaceSupport)v[37];r.cs1=(FSetColorSpace1)v[38];r.hdr=(FSetHDRMetaData)v[40];patchSlot(&v[8],(void*)HookPresent);patchSlot(&v[10],(void*)HookSetFS);patchSlot(&v[13],(void*)HookResize);patchSlot(&v[14],(void*)HookResizeTarget);patchSlot(&v[22],(void*)HookPresent1);patchSlot(&v[38],(void*)HookSetColorSpace1);patchSlot(&v[39],(void*)HookResize1);patchSlot(&v[40],(void*)HookSetHDRMetaData);}
static void hookFactory(void*f,bool extended){if(!f||gFacN>=8)return;void**v=vt(f);for(int i=0;i<gFacN;i++)if(gFac[i].v==v){if(extended&&!gFac[i].extended){gFac[i].extended=true;gFac[i].csh=(FCSH)v[15];gFac[i].csc=(FCSC)v[24];patchSlot(&v[15],(void*)HookCSH);patchSlot(&v[24],(void*)HookCSC);}return;}FactoryRec&r=gFac[gFacN++];r.v=v;r.qi=(FQI)v[0];r.cs=(FCS)v[10];r.csh=0;r.csc=0;r.extended=extended;patchSlot(&v[0],(void*)HookFactoryQI);patchSlot(&v[10],(void*)HookCS);if(extended){r.csh=(FCSH)v[15];r.csc=(FCSC)v[24];patchSlot(&v[15],(void*)HookCSH);patchSlot(&v[24],(void*)HookCSC);}}
static HRESULT __stdcall HookFactoryQI(void*self,const GUID*iid,void**out){FactoryRec*r=findFac(self);if(!r||!r->qi)return E_FAIL;HRESULT h=r->qi(self,iid,out);if(ok(h)&&out&&*out&&factoryIID(iid))hookFactory(*out,factory2Plus(iid));return h;}
static HRESULT __stdcall HookCS(void*self,void*dev,const DXGI_SWAP_CHAIN_DESC*desc,void**out){FactoryRec*r=findFac(self);if(!r||!r->cs)return E_FAIL;HRESULT h=r->cs(self,dev,desc,out);if(ok(h)&&out&&*out)onSwap(*out,dev,desc?desc->OutputWindow:0);return h;}
static HRESULT __stdcall HookCSH(void*self,void*dev,HWND hwnd,const void*desc,const void*fs,void*restrictOut,void**out){FactoryRec*r=findFac(self);if(!r||!r->csh)return E_FAIL;HRESULT h=r->csh(self,dev,hwnd,desc,fs,restrictOut,out);if(ok(h)&&out&&*out)onSwap(*out,dev,hwnd);return h;}
static HRESULT __stdcall HookCSC(void*self,void*dev,const void*desc,void*restrictOut,void**out){FactoryRec*r=findFac(self);if(!r||!r->csc)return E_FAIL;HRESULT h=r->csc(self,dev,desc,restrictOut,out);if(ok(h)&&out&&*out)onSwap(*out,dev,0);return h;}



// D3D11On12 renderer
static HMODULE gD11=0,gCompiler=0;static void*gD11Dev=0,*gD11Ctx=0,*gOn12=0,*gVS=0,*gPS=0,*gUITex=0,*gUISRV=0,*gSampler=0,*gCB=0;static void*gWrapped[MAX_BUFFERS]={0};static void*gRTV[MAX_BUFFERS]={0};static UINT gBufferCount=0,gWidth=0,gHeight=0;static bool gRendererReady=false;
static HDC gMemDC=0;static HBITMAP gDIB=0;static void*gPixels=0;static HFONT gFont=0,gBold=0,gTitle=0;static bool gVisible=false,gF10=false,gLB=false;static int gPanelX=20,gPanelY=20;

static int lpCoordX(LPARAM l){return (int)(SHORT)(l&0xFFFF);}
static int lpCoordY(LPARAM l){return (int)(SHORT)((l>>16)&0xFFFF);}
static LRESULT __stdcall GoriOverlayWndProc(HWND h,UINT msg,WPARAM wp,LPARAM lp){
    if(msg==WM_MOVE||msg==WM_WINDOWPOSCHANGED||msg==WM_DISPLAYCHANGE)gOutputDirty=true;
    if(msg==WM_MOUSEMOVE){gMouseClientX=lpCoordX(lp);gMouseClientY=lpCoordY(lp);if(gVisible)gUiDirty=true;}
    if(gVisible){
        if(msg==WM_LBUTTONDOWN){gClickX=lpCoordX(lp);gClickY=lpCoordY(lp);gClickSerial++;gUiDirty=true;return 0;}
        if(msg==WM_LBUTTONUP||msg==WM_MOUSEWHEEL)return 0;
        if(msg==WM_MOUSEMOVE)return 0;
    }
    return gOldWndProc?CallWindowProcW(gOldWndProc,h,msg,wp,lp):0;
}
static void hookInputWindow(HWND h){
    if(!h||h==gInputHwnd)return;
    LONG_PTR prev=SetWindowLongPtrW(h,GWLP_WNDPROC,(LONG_PTR)GoriOverlayWndProc);
    if(prev){gInputHwnd=h;gOldWndProc=prev;dxlog("[OK] Game-window input hook installed for in-game overlay.\r\n");}
}


typedef HRESULT(__stdcall*PFN_D3D11On12CreateDevice)(void*,UINT,const UINT*,UINT,void*const*,UINT,UINT,void**,void**,UINT*);
typedef HRESULT(__stdcall*PFN_D3DCompile)(LPCVOID,SIZE_T,LPCSTR,const void*,void*,LPCSTR,LPCSTR,UINT,UINT,void**,void**);
static PFN_D3D11On12CreateDevice pD3D11On12=0;static PFN_D3DCompile pD3DCompile=0;

static void releaseBackbuffers(){if(gD11Ctx){typedef void(__stdcall*FOM)(void*,UINT,void*const*,void*);typedef void(__stdcall*FPS_SRV)(void*,UINT,UINT,void*const*);typedef void(__stdcall*FF)(void*);void*nil[1]={0};vf<FPS_SRV>(gD11Ctx,8)(gD11Ctx,0,1,nil);vf<FOM>(gD11Ctx,33)(gD11Ctx,0,0,0);vf<FF>(gD11Ctx,111)(gD11Ctx);}for(int i=0;i<MAX_BUFFERS;i++){if(gRTV[i]){rel(gRTV[i]);gRTV[i]=0;}if(gWrapped[i]){rel(gWrapped[i]);gWrapped[i]=0;}}gBufferCount=0;gNeedBackbuffers=true;}
static void resetRenderer(){releaseBackbuffers();if(gCB){rel(gCB);gCB=0;}if(gSampler){rel(gSampler);gSampler=0;}if(gUISRV){rel(gUISRV);gUISRV=0;}if(gUITex){rel(gUITex);gUITex=0;}if(gPS){rel(gPS);gPS=0;}if(gVS){rel(gVS);gVS=0;}if(gOn12){rel(gOn12);gOn12=0;}if(gD11Ctx){rel(gD11Ctx);gD11Ctx=0;}if(gD11Dev){rel(gD11Dev);gD11Dev=0;}gRendererReady=false;gNeedFullInit=true;}
static void onSwap(void*sc,void*queue,HWND hwnd){if(gQueue!=queue){if(gQueue)rel(gQueue);gQueue=queue;if(gQueue)addref(gQueue);resetRenderer();}if(hwnd){gHwnd=hwnd;hookInputWindow(gHwnd);}if(gSwap3){rel(gSwap3);gSwap3=0;}hookSwapVtable(sc);void*s3=0;if(ok(qi(sc,IID_IDXGISwapChain3,&s3))&&s3){gSwap3=s3;hookSwap3Vtable(s3);}void*s4=0;if(ok(qi(sc,IID_IDXGISwapChain4,&s4))&&s4){hookSwap4Vtable(s4);rel(s4);}gNeedFullInit=true;gNeedBackbuffers=true;gOutputDirty=true;gEffectiveHDR=false;syncHDRPolicy(sc,true);}

static HRESULT compileShader(const char*src,const char*target,void**blob){if(!pD3DCompile)return E_FAIL;return pD3DCompile(src,slen(src),"gori_hdr_overlay",0,0,"main",target,0,0,blob,0);}
static bool createBitmap(){if(gMemDC)return true;gMemDC=CreateCompatibleDC(0);if(!gMemDC)return false;BITMAPINFO bi={};bi.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);bi.bmiHeader.biWidth=PANEL_W;bi.bmiHeader.biHeight=-PANEL_H;bi.bmiHeader.biPlanes=1;bi.bmiHeader.biBitCount=32;bi.bmiHeader.biCompression=BI_RGB;gDIB=CreateDIBSection(gMemDC,&bi,DIB_RGB_COLORS,&gPixels,0,0);if(!gDIB||!gPixels)return false;SelectObject(gMemDC,gDIB);gFont=CreateFontW(17,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,DEFAULT_PITCH|FF_DONTCARE,L"Segoe UI");gBold=CreateFontW(17,0,0,0,FW_BOLD,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,DEFAULT_PITCH|FF_DONTCARE,L"Segoe UI");gTitle=CreateFontW(29,0,0,0,FW_BOLD,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,DEFAULT_PITCH|FF_DONTCARE,L"Segoe UI");return true;}
static bool createBackbuffers(void*swap){releaseBackbuffers();DXGI_SWAP_CHAIN_DESC d={};typedef HRESULT(__stdcall*FGD)(void*,DXGI_SWAP_CHAIN_DESC*);if(!ok(vf<FGD>(swap,12)(swap,&d)))return false;gWidth=d.BufferDesc.Width;gHeight=d.BufferDesc.Height;gSwapFormat=d.BufferDesc.Format;logSwapFormat();if(d.OutputWindow)gHwnd=d.OutputWindow;if(gHwnd)hookInputWindow(gHwnd);if((!gWidth||!gHeight)&&gHwnd){RECT r={};if(GetClientRect(gHwnd,&r)){gWidth=(UINT)(r.right-r.left);gHeight=(UINT)(r.bottom-r.top);}}gBufferCount=d.BufferCount;if(gBufferCount<1)gBufferCount=2;if(gBufferCount>MAX_BUFFERS)gBufferCount=MAX_BUFFERS;typedef HRESULT(__stdcall*FGB)(void*,UINT,const GUID*,void**);FGB gb=vf<FGB>(swap,9);typedef HRESULT(__stdcall*FCWR)(void*,void*,const D3D11_RESOURCE_FLAGS*,UINT,UINT,const GUID*,void**);FCWR cwr=vf<FCWR>(gOn12,3);typedef HRESULT(__stdcall*FRTV)(void*,void*,const void*,void**);FRTV crtv=vf<FRTV>(gD11Dev,9);D3D11_RESOURCE_FLAGS rf={};rf.BindFlags=D3D11_BIND_RENDER_TARGET;for(UINT i=0;i<gBufferCount;i++){void*r12=0;if(!ok(gb(swap,i,&IID_IUnknown,&r12))||!r12)return false;if(!ok(cwr(gOn12,r12,&rf,D3D12_RESOURCE_STATE_RENDER_TARGET,D3D12_RESOURCE_STATE_PRESENT,&IID_ID3D11Resource,&gWrapped[i]))){rel(r12);return false;}rel(r12);if(!ok(crtv(gD11Dev,gWrapped[i],0,&gRTV[i])))return false;}gNeedBackbuffers=false;return true;}
static bool initRenderer(void*swap){if(gRendererReady&&!gNeedFullInit){if(gNeedBackbuffers)return createBackbuffers(swap);return true;}resetRenderer();if(!gQueue){dxlog("[ERROR] No D3D12 command queue captured. Overlay renderer cannot initialize.\r\n");return false;}void*d12=0;typedef HRESULT(__stdcall*FGD)(void*,const GUID*,void**);if(!ok(vf<FGD>(gQueue,7)(gQueue,&IID_ID3D12Device,&d12))||!d12){dxlog("[ERROR] Captured swap-chain device is not a D3D12 command queue.\r\n");return false;}if(!gD11)gD11=loadSystem(L"d3d11.dll");if(!gCompiler)gCompiler=loadSystem(L"d3dcompiler_47.dll");if(!gD11||!gCompiler){rel(d12);dxlog("[ERROR] Failed to load System32 d3d11.dll or d3dcompiler_47.dll.\r\n");return false;}pD3D11On12=(PFN_D3D11On12CreateDevice)GetProcAddress(gD11,"D3D11On12CreateDevice");pD3DCompile=(PFN_D3DCompile)GetProcAddress(gCompiler,"D3DCompile");if(!pD3D11On12||!pD3DCompile){rel(d12);dxlog("[ERROR] D3D11On12CreateDevice or D3DCompile export missing.\r\n");return false;}void*qs[1]={gQueue};HRESULT h=pD3D11On12(d12,D3D11_CREATE_DEVICE_BGRA_SUPPORT,0,0,qs,1,0,&gD11Dev,&gD11Ctx,0);rel(d12);if(!ok(h)||!gD11Dev||!gD11Ctx){dxlog("[ERROR] D3D11On12CreateDevice failed.\r\n");return false;}if(!ok(qi(gD11Dev,IID_ID3D11On12Device,&gOn12))||!gOn12){dxlog("[ERROR] ID3D11On12Device QueryInterface failed.\r\n");return false;}
const char*vs="cbuffer CB:register(b0){float4 rect;float4 screen;} struct O{float4 p:SV_POSITION;float2 uv:TEXCOORD0;}; O main(uint id:SV_VertexID){float2 u[6]={float2(0,0),float2(1,0),float2(0,1),float2(0,1),float2(1,0),float2(1,1)};O o;o.uv=u[id];float2 px=rect.xy+o.uv*rect.zw;o.p=float4(px.x/screen.x*2-1,1-px.y/screen.y*2,0,1);return o;}";
const char*ps="Texture2D tex0:register(t0);SamplerState smp:register(s0);struct I{float4 p:SV_POSITION;float2 uv:TEXCOORD0;};float4 main(I i):SV_TARGET{float4 c=tex0.Sample(smp,i.uv);return float4(c.rgb,1);}";
void*bvs=0,*bps=0;if(!ok(compileShader(vs,"vs_5_0",&bvs))||!ok(compileShader(ps,"ps_5_0",&bps))||!bvs||!bps){if(bvs)rel(bvs);if(bps)rel(bps);dxlog("[ERROR] Runtime shader compilation failed.\r\n");return false;}typedef void*(__stdcall*FBP)(void*);typedef SIZE_T(__stdcall*FBS)(void*);void*vptr=vf<FBP>(bvs,3)(bvs);SIZE_T vsz=vf<FBS>(bvs,4)(bvs);void*pptr=vf<FBP>(bps,3)(bps);SIZE_T psz=vf<FBS>(bps,4)(bps);typedef HRESULT(__stdcall*FVS)(void*,const void*,SIZE_T,void*,void**);if(!ok(vf<FVS>(gD11Dev,12)(gD11Dev,vptr,vsz,0,&gVS))||!ok(vf<FVS>(gD11Dev,15)(gD11Dev,pptr,psz,0,&gPS))){rel(bvs);rel(bps);dxlog("[ERROR] CreateVertexShader/CreatePixelShader failed.\r\n");return false;}rel(bvs);rel(bps);
D3D11_TEXTURE2D_DESC td={};td.Width=PANEL_W;td.Height=PANEL_H;td.MipLevels=1;td.ArraySize=1;td.Format=DXGI_FORMAT_B8G8R8A8_UNORM;td.SampleDesc.Count=1;td.Usage=D3D11_USAGE_DYNAMIC;td.BindFlags=D3D11_BIND_SHADER_RESOURCE;td.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE;typedef HRESULT(__stdcall*FCT)(void*,const D3D11_TEXTURE2D_DESC*,const void*,void**);if(!ok(vf<FCT>(gD11Dev,5)(gD11Dev,&td,0,&gUITex))){dxlog("[ERROR] CreateTexture2D for overlay failed.\r\n");return false;}typedef HRESULT(__stdcall*FCSRV)(void*,void*,const void*,void**);if(!ok(vf<FCSRV>(gD11Dev,7)(gD11Dev,gUITex,0,&gUISRV))){dxlog("[ERROR] CreateShaderResourceView failed.\r\n");return false;}D3D11_SAMPLER_DESC sd={};sd.Filter=0;sd.AddressU=sd.AddressV=sd.AddressW=3;sd.ComparisonFunc=8;sd.MaxLOD=3.4e38f;typedef HRESULT(__stdcall*FSS)(void*,const D3D11_SAMPLER_DESC*,void**);if(!ok(vf<FSS>(gD11Dev,23)(gD11Dev,&sd,&gSampler))){dxlog("[ERROR] CreateSamplerState failed.\r\n");return false;}D3D11_BUFFER_DESC bd={};bd.ByteWidth=32;bd.Usage=D3D11_USAGE_DYNAMIC;bd.BindFlags=D3D11_BIND_CONSTANT_BUFFER;bd.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE;typedef HRESULT(__stdcall*FCB)(void*,const D3D11_BUFFER_DESC*,const void*,void**);if(!ok(vf<FCB>(gD11Dev,3)(gD11Dev,&bd,0,&gCB))){dxlog("[ERROR] CreateBuffer constant buffer failed.\r\n");return false;}if(!createBitmap()){dxlog("[ERROR] GDI overlay bitmap creation failed.\r\n");return false;}if(!createBackbuffers(swap)){dxlog("[ERROR] Wrapped swap-chain backbuffer creation failed.\r\n");return false;}gRendererReady=true;gNeedFullInit=false;gUiDirty=true;dxlog("[OK] DXGI/D3D12 in-game overlay initialized through D3D11On12.\r\n");return true;}

static void fill(HDC dc,int l,int t,int r,int b,DWORD c){RECT q={l,t,r,b};HBRUSH br=CreateSolidBrush(c);FillRect(dc,&q,br);DeleteObject(br);}
static void text(HDC dc,int x,int y,int w,int h,const wchar_t*s,DWORD c,UINT a,HFONT f){RECT q={x,y,x+w,y+h};SetBkMode(dc,TRANSPARENT);SetTextColor(dc,c);if(f)SelectObject(dc,f);DrawTextW(dc,s,-1,&q,DT_SINGLELINE|DT_VCENTER|a);}
static const wchar_t*rowName(int i){static const wchar_t*n[9]={L"Allow HDR at startup",L"Enable HDR output",L"Output device",L"Color gamut",L"HDR UI composite",L"HDR UI level",L"Use HDR display output",L"Peak brightness",L"Graphics adapter"};return n[i];}
static void valstr(const GoriHDRSettings&s,int r,wchar_t*b,int cap){b[0]=0;if(r==0)wcpy(b,cap,s.allowHDR?L"ON":L"OFF");else if(r==1)wcpy(b,cap,s.enableHDR?L"ON":L"OFF");else if(r==2){istr(s.outputDevice,b,cap);wcat(b,cap,L"  raw");}else if(r==3){istr(s.gamut,b,cap);if(s.gamut==2)wcat(b,cap,L"  Rec.2020");}else if(r==4)wcpy(b,cap,s.uiComposite?L"ON":L"OFF");else if(r==5)f10str(s.uiLevel10,b,cap);else if(r==6)wcpy(b,cap,s.useHDR?L"ON":L"OFF");else if(r==7){istr(s.nits,b,cap);wcat(b,cap,L" nits");}else if(r==8){if(s.adapter==-1)wcpy(b,cap,L"Auto");else{istr(s.adapter,b,cap);wcat(b,cap,L"  adapter");}}}
static const wchar_t*fmtName(UINT f){if(f==10)return L"R16G16B16A16_FLOAT";if(f==24)return L"R10G10B10A2_UNORM";if(f==28)return L"R8G8B8A8_UNORM";if(f==87)return L"B8G8R8A8_UNORM";return L"Other / raw";}
static const wchar_t*csName(UINT c){if(c==0)return L"SDR sRGB / Rec.709";if(c==1)return L"scRGB linear";if(c==12)return L"HDR10 PQ / Rec.2020";if(c==17)return L"RGB G22 / Rec.2020";return L"Other / raw";}
static int hdrVerdict(){if(gColorSpaceCompleted&&ok(gCompletionSetHR))return 3;if(gColorSpaceCalls<=0||!ok(gLastColorSpaceHR))return 0;if(gLastColorSpace==12)return 2;if(gLastColorSpace==1&&gSwapFormat==10)return 2;if(gLastColorSpace==0)return -1;return 1;}
static void logSwapFormat(){if(gSwapFormat==10)dxlog("[INFO] Swapchain format: R16G16B16A16_FLOAT (10).\r\n");else if(gSwapFormat==24)dxlog("[INFO] Swapchain format: R10G10B10A2_UNORM (24).\r\n");else if(gSwapFormat==28)dxlog("[INFO] Swapchain format: R8G8B8A8_UNORM (28).\r\n");else if(gSwapFormat==87)dxlog("[INFO] Swapchain format: B8G8R8A8_UNORM (87).\r\n");else dxlog("[INFO] Swapchain format: Other / raw.\r\n");}
static void logTelemetrySummary(){int v=hdrVerdict();if(v==3)dxlog("[SUMMARY] Verdict: UE HDR ACTIVE + MISSING DXGI HDR10 COLORSPACE COMPLETED BY V20.\r\n");else if(v==2)dxlog("[SUMMARY] Verdict: NATIVE HDR CONFIRMED.\r\n");else if(v==-1)dxlog("[SUMMARY] Verdict: GAME SET SDR COLOR SPACE.\r\n");else if(v==1)dxlog("[SUMMARY] Verdict: NON-STANDARD COLOR SPACE.\r\n");else dxlog("[SUMMARY] Verdict: NO GAME HDR COLOR-SPACE CALL SEEN.\r\n");logSwapFormat();if(gColorSpaceCompleted)dxlog(ok(gCompletionSetHR)?"[SUMMARY] SetColorSpace1: HDR10 PQ / Rec.2020 (12) OK [V20 display-aware completion].\r\n":"[SUMMARY] SetColorSpace1: HDR10 PQ / Rec.2020 (12) FAILED [V20 completion].\r\n");else if(gColorSpaceCalls<=0)dxlog("[SUMMARY] SetColorSpace1: not observed.\r\n");else if(gLastColorSpace==12)dxlog(ok(gLastColorSpaceHR)?"[SUMMARY] SetColorSpace1: HDR10 PQ / Rec.2020 (12) OK.\r\n":"[SUMMARY] SetColorSpace1: HDR10 PQ / Rec.2020 (12) FAILED.\r\n");else if(gLastColorSpace==1)dxlog(ok(gLastColorSpaceHR)?"[SUMMARY] SetColorSpace1: scRGB linear (1) OK.\r\n":"[SUMMARY] SetColorSpace1: scRGB linear (1) FAILED.\r\n");else if(gLastColorSpace==0)dxlog(ok(gLastColorSpaceHR)?"[SUMMARY] SetColorSpace1: SDR Rec.709 (0) OK.\r\n":"[SUMMARY] SetColorSpace1: SDR Rec.709 (0) FAILED.\r\n");else dxlog(ok(gLastColorSpaceHR)?"[SUMMARY] SetColorSpace1: other/raw OK.\r\n":"[SUMMARY] SetColorSpace1: other/raw FAILED.\r\n");if(gHDRMetaCalls<=0)dxlog("[SUMMARY] SetHDRMetaData: not observed.\r\n");else if(gLastHDRMetaType==1)dxlog(ok(gLastHDRMetaHR)?"[SUMMARY] SetHDRMetaData: HDR10 OK.\r\n":"[SUMMARY] SetHDRMetaData: HDR10 FAILED.\r\n");else if(gLastHDRMetaType==0)dxlog(ok(gLastHDRMetaHR)?"[SUMMARY] SetHDRMetaData: NONE/cleared OK.\r\n":"[SUMMARY] SetHDRMetaData: NONE/cleared FAILED.\r\n");else dxlog(ok(gLastHDRMetaHR)?"[SUMMARY] SetHDRMetaData: other/raw OK.\r\n":"[SUMMARY] SetHDRMetaData: other/raw FAILED.\r\n");}
static void drawTelemetry(){int y=614;fill(gMemDC,28,y,692,742,rgb(20,23,36));text(gMemDC,42,y+4,620,28,L"LIVE HDR PIPELINE TELEMETRY",rgb(103,226,255),DT_LEFT,gBold);int v=hdrVerdict();const wchar_t*ver=v==3?L"UE HDR + DXGI HDR10 COLORSPACE COMPLETED":(v==2?L"NATIVE HDR CONFIRMED":(v==-1?L"GAME SET SDR COLOR SPACE":(v==1?L"NON-STANDARD COLOR SPACE":L"NO GAME HDR COLOR-SPACE CALL SEEN")));DWORD vc=(v==2||v==3)?rgb(99,255,181):(v==-1?rgb(255,105,130):rgb(255,208,104));text(gMemDC,42,y+32,620,26,ver,vc,DT_LEFT,gBold);wchar_t b[180]=L"Swapchain: ";wcat(b,180,fmtName(gSwapFormat));wcat(b,180,L"   |   SetColorSpace1: ");if(gColorSpaceCompleted){wcat(b,180,L"HDR10 PQ / Rec.2020  OK [V20 completed]");}else if(gColorSpaceCalls>0){wcat(b,180,csName(gLastColorSpace));wcat(b,180,ok(gLastColorSpaceHR)?L"  OK":L"  FAILED");}else wcat(b,180,L"not observed");text(gMemDC,42,y+60,620,22,b,rgb(213,216,233),DT_LEFT,gFont);wchar_t m[180]=L"HDR metadata: ";if(gHDRMetaCalls<=0)wcat(m,180,L"no SetHDRMetaData call observed");else if(gLastHDRMetaType==1&&ok(gLastHDRMetaHR)){wcat(m,180,L"HDR10  |  MaxCLL ");wchar_t n[24];istr((int)gMetaMaxCLL,n,24);wcat(m,180,n);wcat(m,180,L" nits  |  MaxFALL ");istr((int)gMetaMaxFALL,n,24);wcat(m,180,n);wcat(m,180,L" nits");}else if(gLastHDRMetaType==0)wcat(m,180,L"cleared / NONE");else wcat(m,180,ok(gLastHDRMetaHR)?L"non-HDR10 metadata call":L"metadata call FAILED");text(gMemDC,42,y+84,620,22,m,rgb(178,184,208),DT_LEFT,gFont);wchar_t o[180]=L"Active output: ";if(!gOutputKnown)wcat(o,180,L"unknown");else{wcat(o,180,gOutputHDR?L"HDR / PQ capable":L"SDR (HDR forcing suspended)");wcat(o,180,L"  |  output CS ");wchar_t n2[24];istr((int)gOutputColorSpace,n2,24);wcat(o,180,n2);wcat(o,180,L"  |  ");istr((int)gOutputBitsPerColor,n2,24);wcat(o,180,n2);wcat(o,180,L" bpc");}text(gMemDC,42,y+106,620,18,o,gOutputHDR?rgb(99,255,181):rgb(255,208,104),DT_LEFT,gFont);}
static void drawUI(){if(!gMemDC||!gPixels)return;fill(gMemDC,0,0,PANEL_W,PANEL_H,rgb(8,9,15));fill(gMemDC,2,2,PANEL_W-2,PANEL_H-2,rgb(17,18,29));fill(gMemDC,2,2,PANEL_W-2,6,rgb(74,223,255));fill(gMemDC,PANEL_W/2,2,PANEL_W-2,6,rgb(255,72,195));text(gMemDC,30,18,480,42,L"GORI HDR CONTROL",rgb(245,245,255),DT_LEFT,gTitle);text(gMemDC,31,58,600,24,L"DXGI / D3D12 in-game overlay  |  F10 hide/show",rgb(150,158,188),DT_LEFT,gFont);
int patch=apiPatchState?apiPatchState():0;const wchar_t*badge=patch==2?L"V4B RUNTIME FIX  ACTIVE":(patch==1?L"V4B RUNTIME FIX  FAILED":L"V4B RUNTIME FIX  UNSUPPORTED");fill(gMemDC,30,88,690,112,patch==2?rgb(23,69,55):rgb(75,29,47));text(gMemDC,42,88,630,24,badge,patch==2?rgb(99,255,181):rgb(255,123,151),DT_LEFT,gBold);GoriHDRSettings s={};if(apiGetSettings)apiGetSettings(&s);for(int i=0;i<9;i++){int y=124+i*40;fill(gMemDC,28,y,692,y+34,rgb(27,29,44));text(gMemDC,42,y,360,34,rowName(i),rgb(222,224,239),DT_LEFT,gFont);fill(gMemDC,444,y+3,236,y+31,rgb(39,42,62));text(gMemDC,452,y+3,28,28,L"<",rgb(74,223,255),DT_CENTER,gBold);wchar_t v[80];valstr(s,i,v,80);text(gMemDC,484,y+3,154,28,v,rgb(248,248,255),DT_CENTER,gBold);text(gMemDC,642,y+3,28,28,L">",rgb(255,88,200),DT_CENTER,gBold);}
fill(gMemDC,28,492,218,536,rgb(42,76,103));text(gMemDC,28,492,190,44,L"APPLY + VERIFY",rgb(255,255,255),DT_CENTER,gBold);fill(gMemDC,230,492,410,536,rgb(38,40,57));text(gMemDC,230,492,180,44,L"RELOAD INIs",rgb(235,236,246),DT_CENTER,gBold);fill(gMemDC,422,492,692,536,rgb(76,38,88));text(gMemDC,422,492,270,44,L"HDR 1000 PRESET",rgb(255,255,255),DT_CENTER,gBold);wchar_t st[180]=L"Waiting for ASI...";if(apiGetStatus)apiGetStatus(st,180);text(gMemDC,30,548,660,26,st,rgb(111,244,181),DT_LEFT,gBold);wchar_t fl[80]=L"";if(apiGetFlavor)apiGetFlavor(fl,80);wchar_t foot[180]=L"Config: ";wcat(foot,180,fl);wcat(foot,180,L"   |   Changes to renderer HDR values normally require a restart.");text(gMemDC,30,580,660,22,foot,rgb(133,139,164),DT_LEFT,gFont);drawTelemetry();int mx=(int)gMouseClientX-gPanelX,my=(int)gMouseClientY-gPanelY;if(mx>=0&&mx<PANEL_W&&my>=0&&my<PANEL_H){fill(gMemDC,mx-2,my-8,mx+2,my+9,rgb(255,255,255));fill(gMemDC,mx-8,my-2,mx+9,my+2,rgb(74,223,255));fill(gMemDC,mx-1,my-1,mx+2,my+2,rgb(255,72,195));}gUiDirty=true;}
static bool uploadUI(){if(!gUiDirty||!gUITex||!gPixels)return true;typedef HRESULT(__stdcall*FM)(void*,void*,UINT,UINT,UINT,D3D11_MAPPED_SUBRESOURCE*);typedef void(__stdcall*FU)(void*,void*,UINT);D3D11_MAPPED_SUBRESOURCE m={};if(!ok(vf<FM>(gD11Ctx,14)(gD11Ctx,gUITex,0,D3D11_MAP_WRITE_DISCARD,0,&m)))return false;unsigned char*src=(unsigned char*)gPixels;unsigned char*dst=(unsigned char*)m.pData;for(int y=0;y<PANEL_H;y++)memcpy(dst+(unsigned long long)y*m.RowPitch,src+(unsigned long long)y*PANEL_W*4,PANEL_W*4);vf<FU>(gD11Ctx,15)(gD11Ctx,gUITex,0);gUiDirty=false;return true;}
static void input(UINT sw,UINT sh){
    bool f=(GetAsyncKeyState(VK_F10)&0x8000)!=0;
    if(f&&!gF10){gVisible=!gVisible;gUiDirty=true;}
    gF10=f;
    if(apiTick)apiTick();
    if(!gVisible)return;
    LONG serial=gClickSerial;
    if(serial!=gSeenClickSerial){
        gSeenClickSerial=serial;
        int lx=(int)gClickX-gPanelX,ly=(int)gClickY-gPanelY;
        if(lx>=0&&lx<PANEL_W&&ly>=0&&ly<PANEL_H){
            if(ly>=124&&ly<484){
                int row=(ly-124)/40;
                if(row>=0&&row<9&&lx>=444&&lx<680){
                    int dir=lx<562?-1:1;
                    if(apiAdjust)apiAdjust(row,dir);
                    drawUI();
                }
            }else if(ly>=492&&ly<536){
                if(lx>=28&&lx<218){if(apiApply)apiApply();drawUI();}
                else if(lx>=230&&lx<410){if(apiReload)apiReload();drawUI();}
                else if(lx>=422&&lx<692){if(apiPreset)apiPreset();drawUI();}
            }
        }
    }
}
static void render(void*swap){input(gWidth,gHeight);if(gTransition)return;if(gSuspendFrames>0){gSuspendFrames--;return;}if(!gVisible)return;if(!initRenderer(swap))return;if(!gWidth||!gHeight)return;gPanelX=(int)gWidth-PANEL_W-28;if(gPanelX<18)gPanelX=18;gPanelY=28;if(gUiDirty||!gPixels)drawUI();if(!uploadUI())return;UINT idx=0;if(gSwap3){typedef UINT(__stdcall*FCI)(void*);idx=vf<FCI>(gSwap3,36)(gSwap3);}if(idx>=gBufferCount)idx=0;if(!gWrapped[idx]||!gRTV[idx])return;void*arr[1]={gWrapped[idx]};typedef void(__stdcall*FAR)(void*,void*const*,UINT);vf<FAR>(gOn12,5)(gOn12,arr,1);D3D11_MAPPED_SUBRESOURCE m={};typedef HRESULT(__stdcall*FM)(void*,void*,UINT,UINT,UINT,D3D11_MAPPED_SUBRESOURCE*);typedef void(__stdcall*FU)(void*,void*,UINT);if(ok(vf<FM>(gD11Ctx,14)(gD11Ctx,gCB,0,D3D11_MAP_WRITE_DISCARD,0,&m))){float*c=(float*)m.pData;c[0]=(float)gPanelX;c[1]=(float)gPanelY;c[2]=(float)PANEL_W;c[3]=(float)PANEL_H;c[4]=(float)gWidth;c[5]=(float)gHeight;c[6]=c[7]=0;vf<FU>(gD11Ctx,15)(gD11Ctx,gCB,0);}typedef void(__stdcall*FVS_CB)(void*,UINT,UINT,void*const*);typedef void(__stdcall*FPS_SRV)(void*,UINT,UINT,void*const*);typedef void(__stdcall*FPS)(void*,void*,void*const*,UINT);typedef void(__stdcall*FPS_S)(void*,UINT,UINT,void*const*);typedef void(__stdcall*FVS)(void*,void*,void*const*,UINT);typedef void(__stdcall*FIAIL)(void*,void*);typedef void(__stdcall*FIAPT)(void*,UINT);typedef void(__stdcall*FOM)(void*,UINT,void*const*,void*);typedef void(__stdcall*FRSV)(void*,UINT,const D3D11_VIEWPORT*);typedef void(__stdcall*FD)(void*,UINT,UINT);D3D11_VIEWPORT vp={0,0,(float)gWidth,(float)gHeight,0,1};void*rt[1]={gRTV[idx]},*cb[1]={gCB},*srv[1]={gUISRV},*sam[1]={gSampler};vf<FOM>(gD11Ctx,33)(gD11Ctx,1,rt,0);vf<FRSV>(gD11Ctx,44)(gD11Ctx,1,&vp);vf<FIAIL>(gD11Ctx,17)(gD11Ctx,0);vf<FIAPT>(gD11Ctx,24)(gD11Ctx,D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);vf<FVS>(gD11Ctx,11)(gD11Ctx,gVS,0,0);vf<FVS_CB>(gD11Ctx,7)(gD11Ctx,0,1,cb);vf<FPS>(gD11Ctx,9)(gD11Ctx,gPS,0,0);vf<FPS_SRV>(gD11Ctx,8)(gD11Ctx,0,1,srv);vf<FPS_S>(gD11Ctx,10)(gD11Ctx,0,1,sam);vf<FD>(gD11Ctx,13)(gD11Ctx,6,0);void*nil[1]={0};vf<FPS_SRV>(gD11Ctx,8)(gD11Ctx,0,1,nil);vf<FAR>(gOn12,4)(gOn12,arr,1);typedef void(__stdcall*FF)(void*);vf<FF>(gD11Ctx,111)(gD11Ctx);}
static HRESULT __stdcall HookPresent(void*self,UINT sync,UINT flags){SwapRec*r=findSw(self);if(!r||!r->p)return E_FAIL;syncHDRPolicy(self,false);render(self);return r->p(self,sync,flags);}
static HRESULT __stdcall HookPresent1(void*self,UINT sync,UINT flags,const void*params){SwapRec*r=findSw(self);if(!r||!r->p1)return E_FAIL;syncHDRPolicy(self,false);render(self);return r->p1(self,sync,flags,params);}
static HRESULT __stdcall HookSetColorSpace1(void*self,UINT cs){SwapRec*r=findSw(self);if(!r||!r->cs1)return E_FAIL;refreshOutputState(self,true);bool effective=requestedHDR()&&gOutputKnown&&gOutputHDR;UINT actual=cs;if(cs==12&&!effective)actual=(gRestoreColorSpace==12||gRestoreColorSpace==0xFFFFFFFFu)?0:gRestoreColorSpace;HRESULT hr=r->cs1(self,actual);gColorSpaceCompleted=(actual==12)&&ok(hr);gLastColorSpace=actual;gLastColorSpaceHR=hr;gColorSpaceCalls++;if(actual!=12&&ok(hr))gRestoreColorSpace=actual;gUiDirty=true;return hr;}
static bool completeHDR10ColorSpaceAfterNativeMetadata(void*self,SwapRec*r){
    if(!self||!r||!r->checkcs||!r->cs1)return false;
    refreshOutputState(self,true);if(!requestedHDR()||!gOutputKnown||!gOutputHDR)return false;
    UINT support=0;HRESULT chk=r->checkcs(self,12,&support);gCompletionCheckHR=chk;gCompletionSupport=support;
    if(!ok(chk)||!(support&1))return false;
    HRESULT hr=r->cs1(self,12);gCompletionSetHR=hr;gDXGICompletionCalls++;gLastColorSpace=12;gLastColorSpaceHR=hr;gColorSpaceCalls++;gColorSpaceCompleted=ok(hr);gUiDirty=true;
    return ok(hr);
}
static HRESULT __stdcall HookSetHDRMetaData(void*self,UINT type,UINT size,const void*meta){SwapRec*r=findSw(self);if(!r||!r->hdr)return E_FAIL;if(type==1&&meta&&size>=sizeof(DXGI_HDR_METADATA_HDR10_MIN)){memcpy(&gNativeHDRMeta,meta,sizeof(DXGI_HDR_METADATA_HDR10_MIN));gHaveNativeHDRMeta=true;const DXGI_HDR_METADATA_HDR10_MIN*m=(const DXGI_HDR_METADATA_HDR10_MIN*)meta;gMetaMaxMaster=m->MaxMasteringLuminance;gMetaMinMaster=m->MinMasteringLuminance;gMetaMaxCLL=m->MaxContentLightLevel;gMetaMaxFALL=m->MaxFrameAverageLightLevel;}refreshOutputState(self,true);
    // Unknown output is not treated as SDR. Let Unreal submit its native metadata,
    // but wait for a positively identified HDR containing output before forcing PQ.
    if(type==1&&!gOutputKnown){HRESULT hr=r->hdr(self,type,size,meta);gLastHDRMetaType=type;gLastHDRMetaSize=size;gLastHDRMetaHR=hr;gHDRMetaCalls++;gUiDirty=true;return hr;}
    bool effective=requestedHDR()&&gOutputHDR;if(type==1&&!effective){HRESULT hm=r->hdr(self,0,0,0);UINT cs=(gRestoreColorSpace==12||gRestoreColorSpace==0xFFFFFFFFu)?0:gRestoreColorSpace;HRESULT hc=r->cs1?r->cs1(self,cs):0;setTelemetryClear(hm,hc,cs);return hm;}HRESULT hr=r->hdr(self,type,size,meta);gLastHDRMetaType=type;gLastHDRMetaSize=size;gLastHDRMetaHR=hr;gHDRMetaCalls++;gUiDirty=true;if(type==1&&ok(hr)&&effective&&!(gLastColorSpace==12&&ok(gLastColorSpaceHR)))completeHDR10ColorSpaceAfterNativeMetadata(self,r);if(type==0)gColorSpaceCompleted=false;return hr;}
static HRESULT __stdcall HookResize(void*self,UINT n,UINT w,UINT h,UINT fmt,UINT flags){
    SwapRec*r=findSw(self);if(!r||!r->r)return E_FAIL;
    gTransition=true;resetRenderer();
    HRESULT hr=r->r(self,n,w,h,fmt,flags);
    gNeedFullInit=true;gNeedBackbuffers=true;gUiDirty=true;gSuspendFrames=20;gOutputDirty=true;gTransition=false;
    dxlog(ok(hr)?"[INFO] ResizeBuffers completed; overlay renderer will rebuild.\r\n":"[WARN] ResizeBuffers failed.\r\n");
    return hr;
}
static HRESULT __stdcall HookResize1(void*self,UINT n,UINT w,UINT h,UINT fmt,UINT flags,const UINT*nodes,void*const*queues){
    SwapRec*r=findSw(self);if(!r||!r->r1)return E_FAIL;
    gTransition=true;resetRenderer();
    HRESULT hr=r->r1(self,n,w,h,fmt,flags,nodes,queues);
    if(ok(hr)&&queues&&queues[0]&&gQueue!=queues[0]){if(gQueue)rel(gQueue);gQueue=queues[0];addref(gQueue);}
    gNeedFullInit=true;gNeedBackbuffers=true;gUiDirty=true;gSuspendFrames=20;gOutputDirty=true;gTransition=false;
    dxlog(ok(hr)?"[INFO] ResizeBuffers1 completed; overlay renderer will rebuild.\r\n":"[WARN] ResizeBuffers1 failed.\r\n");
    return hr;
}
static HRESULT __stdcall HookSetFS(void*self,BOOL fullscreen,void*out){
    SwapRec*r=findSw(self);if(!r||!r->fs)return E_FAIL;
    gTransition=true;resetRenderer();
    HRESULT hr=r->fs(self,fullscreen,out);
    gNeedFullInit=true;gNeedBackbuffers=true;gUiDirty=true;gSuspendFrames=30;gOutputDirty=true;gTransition=false;
    dxlog(ok(hr)?"[INFO] Fullscreen/windowed transition completed; overlay renderer reset.\r\n":"[WARN] SetFullscreenState failed.\r\n");
    return hr;
}
static HRESULT __stdcall HookResizeTarget(void*self,const DXGI_MODE_DESC*mode){
    SwapRec*r=findSw(self);if(!r||!r->rt)return E_FAIL;
    gTransition=true;resetRenderer();
    HRESULT hr=r->rt(self,mode);
    gNeedFullInit=true;gNeedBackbuffers=true;gUiDirty=true;gSuspendFrames=20;gOutputDirty=true;gTransition=false;
    dxlog(ok(hr)?"[INFO] ResizeTarget completed; overlay renderer reset.\r\n":"[WARN] ResizeTarget failed.\r\n");
    return hr;
}

static void initializeProxy(){if(gInitState==2||gInitState==1)return;gInitState=1;dxlog("[SESSION] Gori HDR DXGI V20 display-aware runtime initialized.\r\n");gReal=loadSystem(L"dxgi.dll");if(gReal){pCreateDXGIFactory=(HRESULT(__stdcall*)(const GUID*,void**))GetProcAddress(gReal,"CreateDXGIFactory");pCreateDXGIFactory1=(HRESULT(__stdcall*)(const GUID*,void**))GetProcAddress(gReal,"CreateDXGIFactory1");pCreateDXGIFactory2=(HRESULT(__stdcall*)(UINT,const GUID*,void**))GetProcAddress(gReal,"CreateDXGIFactory2");}wchar_t a[520];sibling(a,520,L"GoriHDRFix.asi");if(a[0])gAsi=LoadLibraryW(a);bindApi();gInitState=2;}
extern "C" HRESULT __stdcall CreateDXGIFactory(const GUID*riid,void**pp){initializeProxy();HRESULT h=pCreateDXGIFactory?pCreateDXGIFactory(riid,pp):E_FAIL;if(ok(h)&&pp&&*pp)hookFactory(*pp,false);return h;}
extern "C" HRESULT __stdcall CreateDXGIFactory1(const GUID*riid,void**pp){initializeProxy();HRESULT h=pCreateDXGIFactory1?pCreateDXGIFactory1(riid,pp):E_FAIL;if(ok(h)&&pp&&*pp)hookFactory(*pp,false);return h;}
extern "C" HRESULT __stdcall CreateDXGIFactory2(UINT f,const GUID*riid,void**pp){initializeProxy();HRESULT h=pCreateDXGIFactory2?pCreateDXGIFactory2(f,riid,pp):E_FAIL;if(ok(h)&&pp&&*pp)hookFactory(*pp,true);return h;}
extern "C" BOOL __stdcall DllMain(HINSTANCE h,DWORD reason,LPVOID){if(reason==DLL_PROCESS_ATTACH){gSelf=(HMODULE)h;DisableThreadLibraryCalls((HMODULE)h);}return 1;}
