extern "C" {
typedef void* HANDLE; typedef void* HMODULE; typedef void* HINSTANCE; typedef void* LPVOID; typedef const void* LPCVOID; typedef const wchar_t* LPCWSTR; typedef wchar_t* LPWSTR; typedef unsigned long DWORD; typedef unsigned long long SIZE_T; typedef int BOOL; typedef DWORD (__stdcall *LPTHREAD_START_ROUTINE)(LPVOID);
__declspec(dllimport) HMODULE __stdcall GetModuleHandleW(const wchar_t*);
__declspec(dllimport) BOOL __stdcall VirtualProtect(LPVOID,SIZE_T,DWORD,DWORD*);
__declspec(dllimport) BOOL __stdcall FlushInstructionCache(HANDLE,LPCVOID,SIZE_T);
__declspec(dllimport) HANDLE __stdcall GetCurrentProcess(void);
__declspec(dllimport) BOOL __stdcall DisableThreadLibraryCalls(HMODULE);
__declspec(dllimport) HANDLE __stdcall CreateThread(LPVOID,SIZE_T,LPTHREAD_START_ROUTINE,LPVOID,DWORD,DWORD*);
__declspec(dllimport) BOOL __stdcall CloseHandle(HANDLE);
__declspec(dllimport) DWORD __stdcall GetModuleFileNameW(HMODULE,wchar_t*,DWORD);
__declspec(dllimport) DWORD __stdcall GetEnvironmentVariableW(const wchar_t*,wchar_t*,DWORD);
__declspec(dllimport) DWORD __stdcall GetPrivateProfileStringW(const wchar_t*,const wchar_t*,const wchar_t*,wchar_t*,DWORD,const wchar_t*);
__declspec(dllimport) BOOL __stdcall WritePrivateProfileStringW(const wchar_t*,const wchar_t*,const wchar_t*,const wchar_t*);
__declspec(dllimport) DWORD __stdcall GetFileAttributesW(const wchar_t*);
}
extern "C" void* memset(void* d,int c,unsigned long long n){unsigned char*p=(unsigned char*)d;for(unsigned long long i=0;i<n;i++)p[i]=(unsigned char)c;return d;}
extern "C" void* memcpy(void* d,const void*s,unsigned long long n){unsigned char*a=(unsigned char*)d;const unsigned char*b=(const unsigned char*)s;for(unsigned long long i=0;i<n;i++)a[i]=b[i];return d;}
#define DLL_PROCESS_ATTACH 1
#define PAGE_EXECUTE_READWRITE 0x40
#define FILE_ATTRIBUTE_DIRECTORY 0x10UL
#define INVALID_FILE_ATTRIBUTES 0xFFFFFFFFUL
#define TRUE 1
#define FALSE 0

struct GoriHDRSettings { int allowHDR; int enableHDR; int uiComposite; int useHDR; int outputDevice; int gamut; int uiLevel10; int nits; int adapter; };
static HMODULE gSelf=0; static volatile long gReady=0; static bool gPatchActive=false; static bool gPatchSupported=false; static bool gNativeGateActive=false; static bool gNativeGateSupported=false; static bool gIntelPathActive=false; static bool gIntelPathSupported=false; static bool gPersist=false;
static volatile long gOutputHDREligible=-1; // -1 unknown, 0 SDR, 1 HDR
static wchar_t gEngineIni[700],gGameIni[700],gOwnIni[700],gConfigFlavor[64],gStatus[160]=L"Initializing...";
static GoriHDRSettings gSet={1,1,1,1,3,2,15,1000,-1};
static bool patchMem(unsigned char*d,const unsigned char*s,unsigned long n);
static bool gV13RHIHDRActive=false;
static unsigned char gV13RHIHDRInitial=0;
static const unsigned long long kGPUVendorRVA=0x065148E4ULL;
static const unsigned long long kGRHISupportsHDROutputRVA=0x06514A15ULL;

static bool isSupportedGPUVendor(unsigned int vendor){return vendor==0x10DE||vendor==0x1002||vendor==0x8086;}
static volatile long gNativeHDRRequested=-1; // -1 until Unreal/user settings state is known
static void* gUserSettingsSelf=0;
static bool gStartupProfileLoaded=false;
static bool gNativeFieldSynced=false;
static bool modUserWantsHDR(){return gSet.enableHDR!=0 && (gNativeHDRRequested<0 ? (gSet.useHDR!=0) : (gNativeHDRRequested!=0));}
static bool modRequestedHDROn(){return modUserWantsHDR();}
static bool modForceHDROn(){return modRequestedHDROn() && gOutputHDREligible!=0;} // unknown output may bootstrap; known SDR suspends only the effective output
static bool forceRHIHDRSupport(){
    unsigned char*b=(unsigned char*)GetModuleHandleW(0); if(!b)return false;
    unsigned int vendor=*(unsigned int*)(b+kGPUVendorRVA);
    if(!modForceHDROn()||!isSupportedGPUVendor(vendor)){gV13RHIHDRActive=false;return false;}
    unsigned char*p=b+kGRHISupportsHDROutputRVA;
    if(!gV13RHIHDRInitial)gV13RHIHDRInitial=*p;
    if(*p!=1){unsigned char one=1;if(!patchMem(p,&one,1)){gV13RHIHDRActive=false;return false;}}
    gV13RHIHDRActive=(*p==1);
    return gV13RHIHDRActive;
}


// V18: operate on the ACTUAL runtime Unreal console variables, not only the .ini files.
// These addresses come from the retail UE5.1 TAutoConsoleVariable registrations:
//
//   r.HDR.Display.ColorGamut   wrapper @ 0x0651A3C8, CVar* @ +8, thread data* @ +0x10
//   r.HDR.Display.OutputDevice wrapper @ 0x0651A3E0, CVar* @ +8, thread data* @ +0x10
//   r.HDR.EnableHDROutput      wrapper @ 0x0651A458, CVar* @ +8, thread data* @ +0x10
//
// UE's own integer CVar setter helper is RVA 0x00AB6EB0. It ultimately calls the
// CVar virtual Set() implementation with a SetBy priority. V20 uses ECVF_SetByConsole
// (0x09000000) for this TEST so stale .ini/device-profile priorities cannot override the
// runtime HDR tonemapper state while we are diagnosing the broken shipping path.
static const unsigned long long kColorGamutCVarPtrRVA      = 0x0651A3D0ULL;
static const unsigned long long kColorGamutDataPtrRVA      = 0x0651A3D8ULL;
static const unsigned long long kOutputDeviceCVarPtrRVA    = 0x0651A3E8ULL;
static const unsigned long long kOutputDeviceDataPtrRVA    = 0x0651A3F0ULL;
static const unsigned long long kEnableHDROutputCVarPtrRVA = 0x0651A460ULL;
static const unsigned long long kEnableHDROutputDataPtrRVA = 0x0651A468ULL;
static const unsigned long long kSetCVarIntRVA             = 0x00AB6EB0ULL;
static const int kSetByConsole = 0x09000000;

typedef void (__fastcall *SetCVarIntFn)(void*,int,int);
static bool gV15RuntimeCVarsActive=false;

static bool readRuntimeCVarPair(unsigned long long dataPtrRVA,int*out0,int*out1){
    unsigned char*b=(unsigned char*)GetModuleHandleW(0); if(!b)return false;
    int*p=*(int**)(b+dataPtrRVA); if(!p)return false;
    if(out0)*out0=p[0]; if(out1)*out1=p[1];
    return true;
}
static bool forceRuntimeHDRCVars(){
    unsigned char*b=(unsigned char*)GetModuleHandleW(0); if(!b)return false;
    unsigned int vendor=*(unsigned int*)(b+kGPUVendorRVA);
    if(!modForceHDROn()||!isSupportedGPUVendor(vendor)){gV15RuntimeCVarsActive=false;return false;}

    void*cvEnable=*(void**)(b+kEnableHDROutputCVarPtrRVA);
    void*cvOutput=*(void**)(b+kOutputDeviceCVarPtrRVA);
    void*cvGamut =*(void**)(b+kColorGamutCVarPtrRVA);
    if(!cvEnable||!cvOutput||!cvGamut){gV15RuntimeCVarsActive=false;return false;}

    SetCVarIntFn setInt=(SetCVarIntFn)(b+kSetCVarIntRVA);
    // Keep Unreal's actual runtime tonemapper and RHI settings coherent with HDR10 PQ.
    int out=gSet.outputDevice; if(out<0||out>6)out=3;
    int gam=gSet.gamut; if(gam<0||gam>4)gam=2;
    setInt(cvOutput,out,kSetByConsole);
    setInt(cvGamut, gam,kSetByConsole);
    setInt(cvEnable,1,kSetByConsole);

    int e0=0,e1=0,o0=0,o1=0,g0=0,g1=0;
    bool okE=readRuntimeCVarPair(kEnableHDROutputDataPtrRVA,&e0,&e1);
    bool okO=readRuntimeCVarPair(kOutputDeviceDataPtrRVA,&o0,&o1);
    bool okG=readRuntimeCVarPair(kColorGamutDataPtrRVA,&g0,&g1);
    // Depending on UE's thread context, one shadow slot can update a frame later.
    gV15RuntimeCVarsActive=okE&&okO&&okG&&(e0==1||e1==1)&&(o0==gSet.outputDevice||o1==gSet.outputDevice)&&(g0==gSet.gamut||g1==gSet.gamut);
    return gV15RuntimeCVarsActive;
}
static bool setRuntimeHDREnableOnly(int value){
    unsigned char*b=(unsigned char*)GetModuleHandleW(0); if(!b)return false;
    void*cvEnable=*(void**)(b+kEnableHDROutputCVarPtrRVA);
    if(!cvEnable)return false;
    SetCVarIntFn setInt=(SetCVarIntFn)(b+kSetCVarIntRVA);
    setInt(cvEnable,value?1:0,kSetByConsole);
    return true;
}

static const unsigned char kOrigSite1[5]={0xE8,0x2E,0x44,0xFD,0xFF};
static const unsigned char kOrigSite2[5]={0xE8,0xC4,0x30,0xFD,0xFF};
static const unsigned char kOrigCave[12]={0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC};
static const unsigned char kPatchSite1[5]={0xE8,0x2F,0x14,0x00,0x00};
static const unsigned char kPatchSite2[5]={0xE8,0xC5,0x00,0x00,0x00};
static const unsigned char kPatchCave[12]={0xC6,0x81,0x15,0x01,0x00,0x00,0x01,0xE9,0xF3,0x2F,0xFD,0xFF};
static bool eqb(const unsigned char*a,const unsigned char*b,unsigned long n){for(unsigned long i=0;i<n;i++)if(a[i]!=b[i])return false;return true;}
static void cpb(unsigned char*d,const unsigned char*s,unsigned long n){for(unsigned long i=0;i<n;i++)d[i]=s[i];}
static unsigned long wl(const wchar_t*s){unsigned long n=0;if(s)while(s[n])n++;return n;}
static void wc(wchar_t*d,unsigned long c,const wchar_t*s){unsigned long i=0;if(!d||!c)return;if(s)while(s[i]&&i+1<c){d[i]=s[i];i++;}d[i]=0;}
static void wa(wchar_t*d,unsigned long c,const wchar_t*s){unsigned long n=wl(d),i=0;if(!s)return;while(s[i]&&n+i+1<c){d[n+i]=s[i];i++;}d[n+i]=0;}
static bool weq(const wchar_t*a,const wchar_t*b){if(!a||!b)return false;unsigned long i=0;while(a[i]&&b[i]){if(a[i]!=b[i])return false;i++;}return a[i]==b[i];}
static bool truth(const wchar_t*s){return s&&s[0]&&(s[0]==L'1'||s[0]==L'T'||s[0]==L't'||s[0]==L'Y'||s[0]==L'y');}
static int pInt(const wchar_t*s,int d){if(!s||!s[0])return d;int sg=1,i=0,v=0;if(s[0]==L'-'){sg=-1;i=1;}bool any=false;for(;s[i]>=L'0'&&s[i]<=L'9';i++){v=v*10+(s[i]-L'0');any=true;if(v>20000)break;}return any?v*sg:d;}
static void iStr(int v,wchar_t*b){int p=0;if(v<0){b[p++]=L'-';v=-v;}wchar_t t[20];int n=0;do{t[n++]=(wchar_t)(L'0'+v%10);v/=10;}while(v&&n<19);while(n)b[p++]=t[--n];b[p]=0;}
static void f10Str(int v,wchar_t*b){int whole=v/10,frac=v%10;if(frac<0)frac=-frac;wchar_t a[32];iStr(whole,a);wc(b,32,a);wa(b,32,L".");wchar_t f[2]={(wchar_t)(L'0'+frac),0};wa(b,32,f);}
static void sibling(wchar_t*p,DWORD cap,const wchar_t*n){DWORD x=GetModuleFileNameW(gSelf,p,cap);if(!x||x>=cap){p[0]=0;return;}DWORD cut=x;while(cut>0&&p[cut-1]!=L'\\'&&p[cut-1]!=L'/')cut--;DWORD i=0;while(n[i]&&cut+i+1<cap){p[cut+i]=n[i];i++;}p[cut+i]=0;}
static bool patchMem(unsigned char*d,const unsigned char*s,unsigned long n){DWORD old=0;if(!VirtualProtect(d,n,PAGE_EXECUTE_READWRITE,&old))return false;cpb(d,s,n);FlushInstructionCache(GetCurrentProcess(),d,n);DWORD z=0;VirtualProtect(d,n,old,&z);return true;}
static void applyPatch(){unsigned char*b=(unsigned char*)GetModuleHandleW(0);if(!b)return;unsigned char*s1=b+0x01A6501DULL,*s2=b+0x01A66387ULL,*cv=b+0x01A66451ULL;if(eqb(s1,kPatchSite1,5)&&eqb(s2,kPatchSite2,5)&&eqb(cv,kPatchCave,12)){gPatchActive=gPatchSupported=true;return;}if(!(eqb(s1,kOrigSite1,5)&&eqb(s2,kOrigSite2,5)&&eqb(cv,kOrigCave,12))){gPatchActive=false;gPatchSupported=false;return;}gPatchSupported=true;if(patchMem(cv,kPatchCave,12)&&patchMem(s1,kPatchSite1,5)&&patchMem(s2,kPatchSite2,5))gPatchActive=eqb(s1,kPatchSite1,5)&&eqb(s2,kPatchSite2,5)&&eqb(cv,kPatchCave,12);}
static const unsigned char kOrigNativeHDRGate[6]={0x48,0x83,0xEC,0x28,0xE8,0x07};
static const unsigned char kPatchNativeHDRGate[6]={0xB0,0x01,0xC3,0x90,0x90,0x90};
static void applyNativeHDRGate(){unsigned char*b=(unsigned char*)GetModuleHandleW(0);if(!b)return;unsigned char*p=b+0x02E4D5B0ULL;if(eqb(p,kPatchNativeHDRGate,6)){gNativeGateActive=gNativeGateSupported=true;return;}if(!eqb(p,kOrigNativeHDRGate,6)){gNativeGateActive=false;gNativeGateSupported=false;return;}gNativeGateSupported=true;if(patchMem(p,kPatchNativeHDRGate,6))gNativeGateActive=eqb(p,kPatchNativeHDRGate,6);}

// V10: local Intel extension for UGameUserSettings::EnableHDRDisplayOutput().
// Retail logic after the high-level support gate accepts NVIDIA (0x10DE) or AMD (0x1002)
// but skips the HDR-enable branch on Intel. We redirect ONLY the AMD helper call in this
// function to a leaf helper in unused .text padding that returns true for AMD OR Intel.
// Global vendor helpers remain untouched.
static const unsigned char kOrigIntelCall[5]={0xE8,0x57,0x43,0x4C,0xFF}; // call AMD helper @ RVA 0x02E0D890
static const unsigned char kPatchIntelCall[5]={0xE8,0x4C,0xBC,0x86,0x00}; // call local cave @ RVA 0x041B5185
static const unsigned char kOrigIntelCave[25]={
0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,0xCC,
0xCC,0xCC,0xCC,0xCC,0xCC};
static const unsigned char kPatchIntelCave[25]={
0x8B,0x05,0x59,0xF7,0x35,0x02,      // mov eax,[rip+0x0235F759] -> GPU vendor ID @ RVA 0x065148E4
0x3D,0x02,0x10,0x00,0x00,           // cmp eax,0x1002 (AMD)
0x74,0x09,                           // je true
0x3D,0x86,0x80,0x00,0x00,           // cmp eax,0x8086 (Intel)
0x0F,0x94,0xC0,                     // sete al
0xC3,                               // ret
0xB0,0x01,                          // true: mov al,1
0xC3};                              // ret
static void applyIntelHDRPath(){
    unsigned char*b=(unsigned char*)GetModuleHandleW(0);if(!b)return;
    unsigned char*call=b+0x03949534ULL,*cv=b+0x041B5185ULL;
    if(eqb(call,kPatchIntelCall,5)&&eqb(cv,kPatchIntelCave,25)){gIntelPathActive=gIntelPathSupported=true;return;}
    if(!(eqb(call,kOrigIntelCall,5)&&eqb(cv,kOrigIntelCave,25))){gIntelPathActive=false;gIntelPathSupported=false;return;}
    gIntelPathSupported=true;
    // Install helper before redirecting the live callsite.
    if(patchMem(cv,kPatchIntelCave,25)&&patchMem(call,kPatchIntelCall,5))
        gIntelPathActive=eqb(call,kPatchIntelCall,5)&&eqb(cv,kPatchIntelCave,25);
}

static bool existsFile(const wchar_t*p){DWORD a=GetFileAttributesW(p);return a!=INVALID_FILE_ATTRIBUTES&&!(a&FILE_ATTRIBUTE_DIRECTORY);}
static void makeCfgPath(wchar_t*out,const wchar_t*local,const wchar_t*flavor,const wchar_t*file){wc(out,700,local);wa(out,700,L"\\GoriCuddlyCarnage\\Saved\\Config\\");wa(out,700,flavor);wa(out,700,L"\\");wa(out,700,file);}
static void buildPaths(){wchar_t local[520]={0};DWORD n=GetEnvironmentVariableW(L"LOCALAPPDATA",local,520);sibling(gOwnIni,700,L"GoriHDRFix.ini");if(!n||n>=500){gEngineIni[0]=gGameIni[0]=0;wc(gConfigFlavor,64,L"local game INIs not found");return;}makeCfgPath(gEngineIni,local,L"Windows",L"Engine.ini");makeCfgPath(gGameIni,local,L"Windows",L"GameUserSettings.ini");if(existsFile(gEngineIni)||existsFile(gGameIni)){wc(gConfigFlavor,64,L"Windows + local mod INI");return;}makeCfgPath(gEngineIni,local,L"WindowsNoEditor",L"Engine.ini");makeCfgPath(gGameIni,local,L"WindowsNoEditor",L"GameUserSettings.ini");if(existsFile(gEngineIni)||existsFile(gGameIni)){wc(gConfigFlavor,64,L"WindowsNoEditor + local mod INI");return;}makeCfgPath(gEngineIni,local,L"Windows",L"Engine.ini");makeCfgPath(gGameIni,local,L"Windows",L"GameUserSettings.ini");wc(gConfigFlavor,64,L"Windows (new) + local mod INI");}
static bool getv(const wchar_t*sec,const wchar_t*key,const wchar_t*def,wchar_t*out,DWORD cap,const wchar_t*file){return GetPrivateProfileStringW(sec,key,def,out,cap,file)>0;}
static bool putv(const wchar_t*sec,const wchar_t*key,const wchar_t*val,const wchar_t*file){if(!WritePrivateProfileStringW(sec,key,val,file))return false;WritePrivateProfileStringW(0,0,0,file);wchar_t rb[128]={0};GetPrivateProfileStringW(sec,key,L"",rb,128,file);return weq(rb,val);}
static void loadGame(){wchar_t b[128];getv(L"/Script/Engine.RendererSettings",L"r.AllowHDR",L"True",b,128,gEngineIni);gSet.allowHDR=truth(b);getv(L"SystemSettings",L"r.HDR.EnableHDROutput",L"1",b,128,gEngineIni);gSet.enableHDR=truth(b);getv(L"SystemSettings",L"r.HDR.Display.OutputDevice",L"3",b,128,gEngineIni);gSet.outputDevice=pInt(b,3);if(gSet.outputDevice<0)gSet.outputDevice=0;if(gSet.outputDevice>6)gSet.outputDevice=6;getv(L"SystemSettings",L"r.HDR.Display.ColorGamut",L"2",b,128,gEngineIni);gSet.gamut=pInt(b,2);if(gSet.gamut<0)gSet.gamut=0;if(gSet.gamut>4)gSet.gamut=4;getv(L"SystemSettings",L"r.HDR.UI.CompositeMode",L"1",b,128,gEngineIni);gSet.uiComposite=truth(b);getv(L"SystemSettings",L"r.HDR.UI.Level",L"1.5",b,128,gEngineIni);int a=pInt(b,1);gSet.uiLevel10=a*10;for(unsigned long i=0;b[i];i++)if(b[i]==L'.'&&b[i+1]>=L'0'&&b[i+1]<=L'9'){gSet.uiLevel10=a*10+(b[i+1]-L'0');break;}getv(L"/Script/Engine.GameUserSettings",L"bUseHDRDisplayOutput",L"True",b,128,gGameIni);gSet.useHDR=truth(b);getv(L"/Script/Engine.GameUserSettings",L"HDRDisplayOutputNits",L"1000",b,128,gGameIni);gSet.nits=pInt(b,1000);getv(L"SystemSettings",L"r.GraphicsAdapter",L"-1",b,128,gEngineIni);gSet.adapter=pInt(b,-1);if(gSet.adapter<-1||gSet.adapter>1)gSet.adapter=-1;wc(gStatus,160,L"Reloaded from game INIs");}
static bool writeGame(){bool ok=true;wchar_t b[64];ok&=putv(L"/Script/Engine.RendererSettings",L"r.AllowHDR",gSet.allowHDR?L"True":L"False",gEngineIni);ok&=putv(L"SystemSettings",L"r.HDR.EnableHDROutput",gSet.enableHDR?L"1":L"0",gEngineIni);iStr(gSet.outputDevice,b);ok&=putv(L"SystemSettings",L"r.HDR.Display.OutputDevice",b,gEngineIni);iStr(gSet.gamut,b);ok&=putv(L"SystemSettings",L"r.HDR.Display.ColorGamut",b,gEngineIni);ok&=putv(L"SystemSettings",L"r.HDR.UI.CompositeMode",gSet.uiComposite?L"1":L"0",gEngineIni);f10Str(gSet.uiLevel10,b);ok&=putv(L"SystemSettings",L"r.HDR.UI.Level",b,gEngineIni);ok&=putv(L"/Script/Engine.GameUserSettings",L"bUseHDRDisplayOutput",gSet.useHDR?L"True":L"False",gGameIni);iStr(gSet.nits,b);ok&=putv(L"/Script/Engine.GameUserSettings",L"HDRDisplayOutputNits",b,gGameIni);iStr(gSet.adapter,b);ok&=putv(L"SystemSettings",L"r.GraphicsAdapter",b,gEngineIni);return ok;}
static bool verifyGame(){wchar_t b[128],e[64];getv(L"/Script/Engine.RendererSettings",L"r.AllowHDR",L"",b,128,gEngineIni);if(truth(b)!=(gSet.allowHDR!=0))return false;getv(L"SystemSettings",L"r.HDR.EnableHDROutput",L"",b,128,gEngineIni);if(truth(b)!=(gSet.enableHDR!=0))return false;iStr(gSet.outputDevice,e);getv(L"SystemSettings",L"r.HDR.Display.OutputDevice",L"",b,128,gEngineIni);if(!weq(b,e))return false;iStr(gSet.gamut,e);getv(L"SystemSettings",L"r.HDR.Display.ColorGamut",L"",b,128,gEngineIni);if(!weq(b,e))return false;getv(L"SystemSettings",L"r.HDR.UI.CompositeMode",L"",b,128,gEngineIni);if(truth(b)!=(gSet.uiComposite!=0))return false;f10Str(gSet.uiLevel10,e);getv(L"SystemSettings",L"r.HDR.UI.Level",L"",b,128,gEngineIni);if(!weq(b,e))return false;getv(L"/Script/Engine.GameUserSettings",L"bUseHDRDisplayOutput",L"",b,128,gGameIni);if(truth(b)!=(gSet.useHDR!=0))return false;iStr(gSet.nits,e);getv(L"/Script/Engine.GameUserSettings",L"HDRDisplayOutputNits",L"",b,128,gGameIni);if(!weq(b,e))return false;iStr(gSet.adapter,e);getv(L"SystemSettings",L"r.GraphicsAdapter",L"",b,128,gEngineIni);if(!weq(b,e))return false;return true;}
static bool saveOwn(){bool ok=true;wchar_t b[64];ok&=putv(L"HDRControl",L"Saved",L"1",gOwnIni);ok&=putv(L"HDRControl",L"AllowHDR",gSet.allowHDR?L"1":L"0",gOwnIni);ok&=putv(L"HDRControl",L"EnableHDR",gSet.enableHDR?L"1":L"0",gOwnIni);iStr(gSet.outputDevice,b);ok&=putv(L"HDRControl",L"OutputDevice",b,gOwnIni);iStr(gSet.gamut,b);ok&=putv(L"HDRControl",L"Gamut",b,gOwnIni);ok&=putv(L"HDRControl",L"UIComposite",gSet.uiComposite?L"1":L"0",gOwnIni);iStr(gSet.uiLevel10,b);ok&=putv(L"HDRControl",L"UILevel10",b,gOwnIni);ok&=putv(L"HDRControl",L"UseHDR",gSet.useHDR?L"1":L"0",gOwnIni);iStr(gSet.nits,b);ok&=putv(L"HDRControl",L"Nits",b,gOwnIni);iStr(gSet.adapter,b);ok&=putv(L"HDRControl",L"Adapter",b,gOwnIni);gPersist=ok;return ok;}
static bool loadOwn(){wchar_t b[128];getv(L"HDRControl",L"Saved",L"0",b,128,gOwnIni);if(!truth(b))return false;getv(L"HDRControl",L"AllowHDR",L"1",b,128,gOwnIni);gSet.allowHDR=truth(b);getv(L"HDRControl",L"EnableHDR",L"1",b,128,gOwnIni);gSet.enableHDR=truth(b);getv(L"HDRControl",L"OutputDevice",L"3",b,128,gOwnIni);gSet.outputDevice=pInt(b,3);if(gSet.outputDevice<0||gSet.outputDevice>6)gSet.outputDevice=3;getv(L"HDRControl",L"Gamut",L"2",b,128,gOwnIni);gSet.gamut=pInt(b,2);if(gSet.gamut<0||gSet.gamut>4)gSet.gamut=2;getv(L"HDRControl",L"UIComposite",L"1",b,128,gOwnIni);gSet.uiComposite=truth(b);getv(L"HDRControl",L"UILevel10",L"15",b,128,gOwnIni);gSet.uiLevel10=pInt(b,15);getv(L"HDRControl",L"UseHDR",L"1",b,128,gOwnIni);gSet.useHDR=truth(b);getv(L"HDRControl",L"Nits",L"1000",b,128,gOwnIni);gSet.nits=pInt(b,1000);getv(L"HDRControl",L"Adapter",L"-1",b,128,gOwnIni);gSet.adapter=pInt(b,-1);gPersist=true;return true;}


// -----------------------------------------------------------------------------
// V12 native-HDR hook/tracer: observe the REAL UGameUserSettings::EnableHDRDisplayOutput
// call without forcing the native HDR gate, vendor branch or DXGI colorspace.
// Retail function: RVA 0x039494B0
// Entry arguments observed from disassembly:
//   RCX = this
//   DL  = first bool argument
//   R8D = integer argument (logged raw; expected display-nits-like value)
//   R9B = fourth bool argument
// V11 runtime evidence plus UE API docs identify these as bEnable, DisplayNits, bFromUserSettings.
// -----------------------------------------------------------------------------
static volatile unsigned long gTraceCount=0;
static bool gTraceInstalled=false;
static bool gTraceSupported=false;
static bool gV12GuardsActive=false;
static bool gV12GuardsSupported=false;
typedef void (__fastcall *EnableHDRFn)(void*, unsigned char, int, unsigned char);
static EnableHDRFn gOriginalEnableHDR=0;
static void updateTraceStatus(unsigned char,int,unsigned char){wchar_t tmp[32];int e0=0,e1=0,o0=0,o1=0,g0=0,g1=0;readRuntimeCVarPair(kEnableHDROutputDataPtrRVA,&e0,&e1);readRuntimeCVarPair(kOutputDeviceDataPtrRVA,&o0,&o1);readRuntimeCVarPair(kColorGamutDataPtrRVA,&g0,&g1);wc(gStatus,160,L"V20 CVARS E=");iStr(e0,tmp);wa(gStatus,160,tmp);wa(gStatus,160,L"/");iStr(e1,tmp);wa(gStatus,160,tmp);wa(gStatus,160,L" O=");iStr(o0,tmp);wa(gStatus,160,tmp);wa(gStatus,160,L"/");iStr(o1,tmp);wa(gStatus,160,tmp);wa(gStatus,160,L" G=");iStr(g0,tmp);wa(gStatus,160,tmp);wa(gStatus,160,L"/");iStr(g1,tmp);wa(gStatus,160,tmp);wa(gStatus,160,L" | Game=");iStr((int)gNativeHDRRequested,tmp);wa(gStatus,160,tmp);wa(gStatus,160,L" Out=");iStr((int)gOutputHDREligible,tmp);wa(gStatus,160,tmp);wa(gStatus,160,L" Calls=");iStr((int)gTraceCount,tmp);wa(gStatus,160,tmp);}

extern "C" __declspec(dllexport) void __fastcall V20_EnableHDRDisplayOutput_Hook(void*self,unsigned char enable,int rawR8,unsigned char rawR9){
    gTraceCount++;
    if(self)gUserSettingsSelf=self;

    // The first user-settings call is special. If a saved GoriHDRFix.ini profile
    // exists, restore its HDR preference into UE before UE's pre-gated DL value
    // can overwrite it. Gori's callsite computes DL from IsHDRAllowed() AND the
    // real bUseHDRDisplayOutput field at this+0x10C, so DL alone is not a reliable
    // representation of the menu toggle on this broken shipping path.
    if(rawR9 && self){
        unsigned char*p=(unsigned char*)self;
        unsigned char menuState=*(unsigned char*)(p+0x10C)?1:0;
        if(!gNativeFieldSynced && gStartupProfileLoaded){
            menuState=gSet.enableHDR?1:0;
            *(unsigned char*)(p+0x10C)=menuState;
            gNativeHDRRequested=menuState?1:0;
            gNativeFieldSynced=true;
        }else{
            gNativeFieldSynced=true;
            gNativeHDRRequested=menuState?1:0;
            if(gSet.enableHDR!=(int)menuState || gSet.useHDR!=(int)menuState){
                gSet.enableHDR=menuState?1:0;
                gSet.useHDR=menuState?1:0;
                saveOwn();
            }
        }
    }else if(gNativeHDRRequested<0){
        gNativeHDRRequested=gSet.enableHDR?1:0;
    }

    // Keep the user's requested state separate from the current display's
    // eligibility. On a known SDR monitor we suspend the effective HDR runtime,
    // but still pass the requested state through UE so this+0x10C is not erased.
    bool requested=modRequestedHDROn();
    bool effective=modForceHDROn();
    if(effective){forceRHIHDRSupport();forceRuntimeHDRCVars();}
    else setRuntimeHDREnableOnly(0);

    if(gOriginalEnableHDR)gOriginalEnableHDR(self,requested?1:0,requested?gSet.nits:rawR8,rawR9);

    if(effective)forceRuntimeHDRCVars();
    else setRuntimeHDREnableOnly(0);
    updateTraceStatus(enable,rawR8,rawR9);
}


// V12 local native-HDR guard bypass, scoped ONLY to EnableHDRDisplayOutputInternal.
// Retail source logic is equivalent to:
//   if (bEnable && !(GRHISupportsHDROutput && IsHDRAllowed())) bEnable=false;
// V11 proved Gori always passed bEnable=0. V12 forces bEnable=1 in the hook and NOPs
// ONLY the two conditional branches that would force it back off. No global RHI flag,
// vendor helper, DXGI colorspace, or metadata function is modified.
static const unsigned char kV12GuardJcc1[6]={0x0F,0x84,0xAE,0x00,0x00,0x00}; // RVA 0x03949518
static const unsigned char kV12GuardJcc2[6]={0x0F,0x84,0x9A,0x00,0x00,0x00}; // RVA 0x03949525
static const unsigned char kNop6[6]={0x90,0x90,0x90,0x90,0x90,0x90};
static bool applyV12LocalHDRGuards(){
    unsigned char*b=(unsigned char*)GetModuleHandleW(0);if(!b)return false;
    unsigned char*j1=b+0x03949518ULL,*j2=b+0x03949525ULL;
    if(eqb(j1,kNop6,6)&&eqb(j2,kNop6,6)){gV12GuardsSupported=gV12GuardsActive=true;return true;}
    if(!(eqb(j1,kV12GuardJcc1,6)&&eqb(j2,kV12GuardJcc2,6))){gV12GuardsSupported=false;gV12GuardsActive=false;return false;}
    gV12GuardsSupported=true;
    if(!patchMem(j1,kNop6,6))return false;
    if(!patchMem(j2,kNop6,6))return false;
    gV12GuardsActive=eqb(j1,kNop6,6)&&eqb(j2,kNop6,6);
    return gV12GuardsActive;
}

static const unsigned char kEnableHDREntry15[15]={0x48,0x89,0x5C,0x24,0x08,0x48,0x89,0x6C,0x24,0x10,0x48,0x89,0x74,0x24,0x18};
static bool installV11Tracer(){
    unsigned char*b=(unsigned char*)GetModuleHandleW(0);if(!b)return false;
    unsigned char*entry=b+0x039494B0ULL;
    unsigned char*cave=b+0x008306F1ULL; // verified retail .text INT3 padding (large run)
    if(!eqb(entry,kEnableHDREntry15,15)){gTraceSupported=false;return false;}
    for(int i=0;i<48;i++)if(cave[i]!=0xCC){gTraceSupported=false;return false;}
    gTraceSupported=true;
    unsigned char tramp[29];
    for(int i=0;i<15;i++)tramp[i]=kEnableHDREntry15[i];
    tramp[15]=0xFF;tramp[16]=0x25;tramp[17]=0;tramp[18]=0;tramp[19]=0;tramp[20]=0;
    unsigned long long back=(unsigned long long)(entry+15);
    for(int i=0;i<8;i++)tramp[21+i]=(unsigned char)((back>>(i*8))&0xFF);
    if(!patchMem(cave,tramp,29))return false;
    gOriginalEnableHDR=(EnableHDRFn)cave;
    unsigned char hook[15]; hook[0]=0xFF;hook[1]=0x25;hook[2]=0;hook[3]=0;hook[4]=0;hook[5]=0;
    unsigned long long hp=(unsigned long long)&V20_EnableHDRDisplayOutput_Hook;
    for(int i=0;i<8;i++)hook[6+i]=(unsigned char)((hp>>(i*8))&0xFF);hook[14]=0x90;
    if(!patchMem(entry,hook,15))return false;
    gTraceInstalled=true;
    return true;
}


static DWORD __stdcall Worker(LPVOID){
    buildPaths();
    bool own=loadOwn();
    if(!own)loadGame();
    gStartupProfileLoaded=own;
    gNativeHDRRequested=gSet.enableHDR?1:0;
    applyPatch(); // validated V4B
    bool guards=applyV12LocalHDRGuards();
    bool tr=installV11Tracer();
    if(modForceHDROn()){forceRHIHDRSupport();forceRuntimeHDRCVars();}
    else setRuntimeHDREnableOnly(0);
    if(gPatchActive&&guards&&tr)wc(gStatus,160,own?L"V20 READY - local GoriHDRFix.ini restored":L"V20 READY - game profile loaded");
    else if(gPatchActive)wc(gStatus,160,L"V4B active; V20 runtime hook FAILED or unsupported");
    else wc(gStatus,160,L"V20 unsupported on this game build");
    gReady=1;
    return 0;
}

extern "C" __declspec(dllexport) int __stdcall GoriHDR_IsReady(){return gReady?1:0;}
extern "C" __declspec(dllexport) int __stdcall GoriHDR_GetPatchState(){return gPatchActive?2:(gPatchSupported?1:0);}
extern "C" __declspec(dllexport) void __stdcall GoriHDR_GetSettings(GoriHDRSettings*out){if(out)*out=gSet;}
extern "C" __declspec(dllexport) void __stdcall GoriHDR_GetStatus(wchar_t*out,int cap){if(out&&cap>0)wc(out,(unsigned long)cap,gStatus);}
extern "C" __declspec(dllexport) void __stdcall GoriHDR_GetConfigFlavor(wchar_t*out,int cap){if(out&&cap>0)wc(out,(unsigned long)cap,gConfigFlavor);}
extern "C" __declspec(dllexport) void __stdcall GoriHDR_Adjust(int row,int dir){if(!gReady)return;switch(row){case 0:gSet.allowHDR=!gSet.allowHDR;break;case 1:gSet.enableHDR=!gSet.enableHDR;gSet.useHDR=gSet.enableHDR;gNativeHDRRequested=gSet.enableHDR?1:0;if(gUserSettingsSelf){*(unsigned char*)((unsigned char*)gUserSettingsSelf+0x10C)=gSet.enableHDR?1:0;gNativeFieldSynced=true;}break;case 2:gSet.outputDevice+=dir;if(gSet.outputDevice<0)gSet.outputDevice=6;if(gSet.outputDevice>6)gSet.outputDevice=0;break;case 3:gSet.gamut+=dir;if(gSet.gamut<0)gSet.gamut=4;if(gSet.gamut>4)gSet.gamut=0;break;case 4:gSet.uiComposite=!gSet.uiComposite;break;case 5:gSet.uiLevel10+=dir;if(gSet.uiLevel10<1)gSet.uiLevel10=1;if(gSet.uiLevel10>50)gSet.uiLevel10=50;break;case 6:gSet.useHDR=!gSet.useHDR;break;case 7:gSet.nits+=dir*50;if(gSet.nits<100)gSet.nits=100;if(gSet.nits>10000)gSet.nits=10000;break;case 8:gSet.adapter+=dir;if(gSet.adapter>1)gSet.adapter=-1;if(gSet.adapter<-1)gSet.adapter=1;break;}if(modForceHDROn()){forceRHIHDRSupport();forceRuntimeHDRCVars();}else setRuntimeHDREnableOnly(0);bool saved=saveOwn();wc(gStatus,160,saved?L"Changed + auto-saved beside ASI":L"Changed - local GoriHDRFix.ini save FAILED");}
extern "C" __declspec(dllexport) int __stdcall GoriHDR_Apply(){if(!gReady)return 0;bool own=saveOwn();bool game=writeGame()&&verifyGame();bool ok=own&&game;wc(gStatus,160,ok?L"SAVED + VERIFIED":(own?L"Mod profile saved; game INI verification failed":L"SAVE FAILED"));return ok?1:0;}
extern "C" __declspec(dllexport) void __stdcall GoriHDR_Reload(){if(!gReady)return;if(loadOwn())wc(gStatus,160,L"Reloaded local GoriHDRFix.ini");else loadGame();gNativeHDRRequested=gSet.enableHDR?1:0;if(gUserSettingsSelf){*(unsigned char*)((unsigned char*)gUserSettingsSelf+0x10C)=gSet.enableHDR?1:0;gNativeFieldSynced=true;}if(modForceHDROn()){forceRHIHDRSupport();forceRuntimeHDRCVars();}else setRuntimeHDREnableOnly(0);}
extern "C" __declspec(dllexport) void __stdcall GoriHDR_Preset(){if(!gReady)return;gSet.allowHDR=gSet.enableHDR=gSet.uiComposite=gSet.useHDR=1;gSet.outputDevice=3;gSet.gamut=2;gSet.uiLevel10=15;gSet.nits=1000;gSet.adapter=-1;gNativeHDRRequested=1;if(gUserSettingsSelf){*(unsigned char*)((unsigned char*)gUserSettingsSelf+0x10C)=1;gNativeFieldSynced=true;}if(modForceHDROn()){forceRHIHDRSupport();forceRuntimeHDRCVars();}bool saved=saveOwn();wc(gStatus,160,saved?L"HDR1000 preset loaded + auto-saved":L"HDR1000 preset loaded - save FAILED");}
extern "C" __declspec(dllexport) void __stdcall GoriHDR_SetOutputHDRAvailable(int available){gOutputHDREligible=available?1:0;if(!gReady)return;if(modForceHDROn()){forceRHIHDRSupport();forceRuntimeHDRCVars();}else setRuntimeHDREnableOnly(0);}
extern "C" __declspec(dllexport) int __stdcall GoriHDR_GetOutputHDRAvailable(){return gOutputHDREligible>0?1:0;}
extern "C" __declspec(dllexport) int __stdcall GoriHDR_GetEffectiveHDRRequested(){return modForceHDROn()?1:0;}
extern "C" __declspec(dllexport) void __stdcall GoriHDR_Tick(){if(gUserSettingsSelf&&gNativeFieldSynced){unsigned char live=*(unsigned char*)((unsigned char*)gUserSettingsSelf+0x10C)?1:0;if((long)live!=gNativeHDRRequested){gNativeHDRRequested=live?1:0;gSet.enableHDR=live?1:0;gSet.useHDR=live?1:0;saveOwn();}}if(modForceHDROn()){forceRHIHDRSupport();forceRuntimeHDRCVars();}else setRuntimeHDREnableOnly(0);}

extern "C" BOOL __stdcall DllMain(HINSTANCE h,DWORD r,LPVOID){if(r==DLL_PROCESS_ATTACH){gSelf=(HMODULE)h;DisableThreadLibraryCalls((HMODULE)h);HANDLE t=CreateThread(0,0,Worker,0,0,0);if(t)CloseHandle(t);}return 1;}
