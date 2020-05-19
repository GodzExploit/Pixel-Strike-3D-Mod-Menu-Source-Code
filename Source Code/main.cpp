#include <pthread.h>
#include <jni.h>
#include <memory.h>
#include <dlfcn.h>
#include <cstdio>
#include <cstdlib>

#include "Includes/Logger.h"
#include "Patching/Patch.h"
#import "Includes/Utils.h"
#include "Includes/Offsets.h"

#if defined(__armv7__)
#include "X64Hook/And64InlineHook.hpp"
#else
#include "Substrate/CydiaSubstrate.h"
#endif

bool fireratev1 = false;
bool hasBurnDamage = false;
bool hipRecoil = false;
bool maxRecoil = false;
bool recoil = false;
bool ammo = false;
bool ammo2 = false;
bool blur = false;
bool pelletcount = false;
bool range = false;
bool fire = false;
bool fire2 = false;
bool fire3 = false;
bool NukeRunning = false;
bool NukeTime = false;
bool xpPerKill = false;
bool xpPerKill2 = false;
bool fireratev2 = false;
bool gadgetspam = false;
int fovModifier = 70;
int movementModifier = 5;
const char* spinnerExampleString;

struct Patches{
    Patch *miniMap;
}patch;

enum WeaponType{
    STANDARD = 0,
    SHOTGUN = 1,
    SNIPER = 2,
    DUAL = 3,
    MELEE = 4,
    GRENADE = 5,
    BURST = 6,
    AREA_DAMAGE = 7,
    CUSTOM = 8,
    PROJECTILE = 9
};

bool NewWeaponHookInitialized = false;
bool NukeControllerHook = false;
bool GameModeHook = false;
bool GameShellHook = false;
bool speedHackDetectorHook = false;
bool WeaponControllerHook = false;
bool RemoteWeaponControllerHook = false;
const char* libName = "libil2cpp.so";

void octo_hook(void *orig_fcn, void* new_fcn, void **orig_fcn_ptr)
{
#if defined(__armv7__)
    A64HookFunction(orig_fcn, new_fcn, orig_fcn_ptr);
#else
    MSHookFunction(orig_fcn, new_fcn, orig_fcn_ptr);
#endif
}


void(*old_NewWeapon)(void *instance);
void NewWeapon(void *instance) {
    if(instance != NULL) {
        if(!NewWeaponHookInitialized){
            //Check if this hook initialized. If so log
            NewWeaponHookInitialized = true;
            LOGI("GameManager_LateUpdate hooked");
        }
        if (fireratev1) {
            *(float *) ((uint64_t) instance + 0x74) = 999;
        }
        if (hasBurnDamage) {
            *(bool *) ((uint64_t) instance + 0xC3) = true;
        }
        if (hipRecoil) {
            *(float *) ((uint64_t) instance + 0x84) = 0;
        }
        if (maxRecoil) {
            *(float *) ((uint64_t) instance + 0x80) = 0;
        }
        if (recoil) {
            *(float *) ((uint64_t) instance + 0x7C) = 0;
        }
        if (ammo) {
            *(int *) ((uint64_t) instance + 0x64) = 999;
        }
        if (ammo2) {
            *(int *) ((uint64_t) instance + 0x60) = 999;
        }
        if (blur) {
            *(bool *) ((uint64_t) instance + 0x88) = false;
        }
        if (pelletcount) {
            *(int *) ((uint64_t) instance + 0xC4) = 50;
        }
        if (range) {
            *(int *) ((uint64_t) instance + 0x78) = 99999;
        }
        if (fire) {
            *(bool *) ((uint64_t) instance + 0x771C08) = true;
        }
        //Your code here
    }
    old_NewWeapon(instance);
}

void(*old_NukeController)(void *instance);
void NukeController(void *instance) {
    if(instance != NULL) {
        if(!NukeControllerHook){
            //Check if this hook initialized. If so log
            NukeControllerHook = true;
            LOGI("GameManager_LateUpdate hooked");
        }
        if (NukeRunning) {
            *(bool *) ((uint64_t) instance + 0x30) = true;
        }
        if (NukeTime) {
            *(float *) ((uint64_t) instance + 0x24) = 5.0;
        }
        //Your code here
    }
    old_NukeController(instance);
}

void(*old_GameMode)(void *instance);
void GameMode(void *instance) {
    if(instance != NULL) {
        if(!GameModeHook){
            //Check if this hook initialized. If so log
            GameModeHook = true;
            LOGI("GameManager_LateUpdate hooked");
        }
        if (xpPerKill) {
            *(int *) ((uint64_t) instance + 0x30) = 5000;
        }
        //Your code here
    }
    old_GameMode(instance);
}

void(*old_GameShell)(void *instance);
void GameShell(void *instance) {
    if(instance != NULL) {
        if(!GameShellHook){
            //Check if this hook initialized. If so log
            GameShellHook = true;
            LOGI("GameManager_LateUpdate hooked");
        }
        if (xpPerKill2) {
            *(int *) ((uint64_t) instance + 0x104) = 5000;
        }
        //Your code here
    }
    old_GameShell(instance);
}

void(*old_SpeedHackDetector)(void *instance);
void SpeedHackDetector(void *instance) {
    if(instance != NULL) {
        if(!speedHackDetectorHook){
            //Check if this hook initialized. If so log
            speedHackDetectorHook = true;
            LOGI("GameManager_LateUpdate hooked");
            *(int *) ((uint64_t) instance + 0x3C) = 0;
        }
        //Your code here
    }
    old_SpeedHackDetector(instance);
}

void(*old_WeaponController)(void *instance);
void WeaponController(void *instance) {
    if(instance != NULL) {
        if(!WeaponControllerHook){
            //Check if this hook initialized. If so log
            WeaponControllerHook = true;
            LOGI("GameManager_LateUpdate hooked");
        }
        if (gadgetspam) {
            *(float *) ((uint64_t) instance + 0x80) = 0;
        }
        if (fireratev2) {
            *(float *) ((uint64_t) instance + 0xD8) = 0;
        }
        if (fire2) {
            *(float *) ((uint64_t) instance + 0x7DC81C) = true;
        }
        //Your code here
    }
    old_WeaponController(instance);
}

void(*old_RemoteWeaponController)(void *instance);
void RemoteWeaponController(void *instance) {
    if(instance != NULL) {
        if(!RemoteWeaponControllerHook){
            //Check if this hook initialized. If so log
            RemoteWeaponControllerHook = true;
            LOGI("GameManager_LateUpdate hooked");
        }
        if (fire3) {
            *(bool *) ((uint64_t) instance + 0x60) = true;
        }
        //Your code here
    }
    old_RemoteWeaponController(instance);
}

float (*old_get_fieldOfView)(void *instance);
float get_fieldOfView(void *instance) {
    if (instance != NULL && fovModifier > 1) {
        return (float)fovModifier;
    }
    return old_get_fieldOfView(instance);
}



// we will run our patches in a new thread so our while loop doesn't block process main thread
void* hack_thread(void*) {
    LOGI("I have been loaded. Mwuahahahaha");
    // loop until our target library is found
    do {
        sleep(1);
    } while (!isLibraryLoaded(libName));
    LOGI("I found the il2cpp lib. Address is: %p", (void*)findLibrary(libName));
    LOGI("Hooking GameManager_LateUpdate");
    octo_hook((void*)getAbsoluteAddress(libName, 0x771BB8), (void*)NewWeapon, (void**)&old_NewWeapon);
    octo_hook((void*)getAbsoluteAddress(libName, 0x5F6D74), (void*)NukeController, (void**)&old_NukeController);
    octo_hook((void*)getAbsoluteAddress(libName, 0x843B40), (void*)GameMode, (void**)&old_GameMode);
    octo_hook((void*)getAbsoluteAddress(libName, 0x847738), (void*)GameShell, (void**)&old_GameShell);
    octo_hook((void*)getAbsoluteAddress(libName, 0x12C5608), (void*)SpeedHackDetector, (void**)&old_SpeedHackDetector);
    octo_hook((void*)getAbsoluteAddress(libName, 0x7DE9FC), (void*)WeaponController, (void**)&old_WeaponController);
    octo_hook((void*)getAbsoluteAddress(libName, 0x1DC0F4C), (void*)RemoteWeaponController, (void**)&old_RemoteWeaponController);
    octo_hook((void*)getAbsoluteAddress(libName, 0x156E4A8), (void*)get_fieldOfView, (void**)&old_get_fieldOfView);
    patch.miniMap = Patch::Setup((void*)getAbsoluteAddress(libName, 0xF09D64), (char*)"\x01\x00\xa0\xe3\x1e\xff\x2f\xe1", 8);

    Patch::Setup((void*)getAbsoluteAddress(libName, 0x8C9DD0), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CheatController%SpeedHack
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x7545A4), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //ModMenu%BanPlayer
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x754674), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //ModMenu%DOBANPLAYER
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x7547D0), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //DoWarnPlayer
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x754454), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //KickPlayer
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x754700), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //WarnPlayer
    Patch::Setup((void*)getAbsoluteAddress(libName, 0xA2C060), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //BannedMenu%Show
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x1DB27A8), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //doConfirmBan
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x1DB26A0), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //ConfirmBan
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C3DE8), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C3C5C), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C3BD8), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x1984F9C), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x1984E34), (char*)"\x00\x00\xA0\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CHeaTDetect
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C4550), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C4B8C), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C472C), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C43DC), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C4EB8), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C586C), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C5248), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C51BC), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C5140), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C50CC), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C4C38), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C5D38), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C766C), (char*)"\x00\x00\xA0\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C5E18), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C61F4), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C8414), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C8418), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C841C), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C7AA8), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C6070), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12C5C38), (char*)"\x00\x00\xA0\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12CD9D8), (char*)"\x00\x00\xA0\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12CCCF4), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12CD144), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12CD1C4), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12CD25C), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12CDC60), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x12CCF28), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //CodeStage
    Patch::Setup((void*)getAbsoluteAddress(libName, 0x772100), (char*)"\x00\xF0\x20\xe3\x1e\xff\x2f\xe1", 8)->Apply(); //DelayedShoot
    return NULL;
}

extern "C"
JNIEXPORT jobjectArray JNICALL Java_com_dark_force_NativeLibrary_getListFT(JNIEnv *env, jclass jobj){
    jobjectArray ret;
    int i;
    const char *features[]= {"Burn Damage Mod", "No Recoil", "Ammo Mod", "No Blur Scope", "Range Mod", "Auto-Fire Mod", "PelletCount (Idk)", "Nuke-Mod", "XP Kill Hack", "Gadget-Spam", "FireRate 1", "FireRate 2", "Spinner_Weapon Shoot_weaponsList", "SeekBar_FOV Modifier_0_250", "SeekBar_Speed Modifier_0_250"};
    int Total_Feature = (sizeof features / sizeof features[0]); //Now you dont have to manually update the number everytime
    ret= (jobjectArray)env->NewObjectArray(Total_Feature,
                                           env->FindClass("java/lang/String"),
                                           env->NewStringUTF(""));

    for(i=0;i<Total_Feature;i++) {
        env->SetObjectArrayElement(
                ret,i,env->NewStringUTF(features[i]));
    }
    return(ret);
}


extern "C"
JNIEXPORT void JNICALL Java_com_dark_force_NativeLibrary_changeToggle(JNIEnv *env, jclass thisObj, jint number) {
    int i = (int) number;
    switch (i) {
        case 0:
            hasBurnDamage = !hasBurnDamage;
            break;
        case 1:
            hipRecoil = !hipRecoil;
            maxRecoil = !maxRecoil;
            recoil = !recoil;
            break;
        case 2:
            ammo = !ammo;
            ammo2 = !ammo2;
            break;
        case 3:
            blur = !blur;
            break;
        case 4:
            range = !range;
            break;
        case 5:
            fire = !fire;
            fire2 = !fire2;
            fire3 = !fire3;
            break;
        case 6:
            pelletcount = !pelletcount;
            break;
        case 7:
            NukeRunning = !NukeRunning;
            NukeTime = !NukeTime;
            break;
        case 8:
            xpPerKill = !xpPerKill;
            xpPerKill2 = !xpPerKill2;
            break;
        case 9:
            gadgetspam = !gadgetspam;
            break;
        case 10:
            fireratev1 = !fireratev1;
            break;
        case 11:
            fireratev2 = !fireratev2;
            break;
        default:
            break;
    }
    return;
}


extern "C"
JNIEXPORT void JNICALL Java_com_dark_force_NativeLibrary_init(JNIEnv * env, jclass obj){
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_dark_force_NativeLibrary_changeSpinner(JNIEnv *env, jclass clazz, jint i, jstring value) {
    int li = (int) i;
    switch (li) {
        case 12:
            spinnerExampleString = env->GetStringUTFChars(value, 0);
            break;
        default:
            break;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_dark_force_NativeLibrary_changeSeekBar(JNIEnv *env, jclass clazz, jint i, jint seekbarValue) {
    int li = (int) i;
    switch (li) {
        case 13:
            fovModifier = seekbarValue;
            break;
        default:
            break;
    }
    return;
}
