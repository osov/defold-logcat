#if defined(DM_PLATFORM_ANDROID)

#include <dmsdk/dlib/android.h>
#include "extension_private.h"
#include "com_defold_extension_ExtensionLogCat.h"
#include "extension_callback_private.h"

JNIEXPORT void JNICALL Java_com_defold_extension_ExtensionLogCat_AddToQueue(JNIEnv * env, jclass cls, jint jmsg, jstring jjson)
{
    const char* json = env->GetStringUTFChars(jjson, 0);
    dmLogCat::AddToQueueCallback((dmLogCat::MessageId)jmsg, json);
    env->ReleaseStringUTFChars(jjson, json);
}

namespace dmLogCat {

struct App
{
    jobject    m_AppJNI;
    jmethodID  m_Initialize;
    jmethodID  m_ReportEvent;
};

static App       g_app;

static void CallVoidMethod(jobject instance, jmethodID method)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    env->CallVoidMethod(instance, method);
}


static void CallVoidMethodChar(jobject instance, jmethodID method, const char* cstr)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr = env->NewStringUTF(cstr);
    env->CallVoidMethod(instance, method, jstr);
    env->DeleteLocalRef(jstr);
}


static void CallVoidMethodCharChar(jobject instance, jmethodID method, const char* cstr1, const char* cstr2)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr1 = env->NewStringUTF(cstr1);
    jstring jstr2 = env->NewStringUTF(cstr2);
    env->CallVoidMethod(instance, method, jstr1, jstr2);
    env->DeleteLocalRef(jstr1);
    env->DeleteLocalRef(jstr2);
}

static void InitJNIMethods(JNIEnv* env, jclass cls)
{
    g_app.m_Initialize = env->GetMethodID(cls, "initialize", "(Ljava/lang/String;)V");
    g_app.m_ReportEvent = env->GetMethodID(cls, "ReportEvent", "(Ljava/lang/String;Ljava/lang/String;)V");
}

void Initialize_Ext()
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();
    jclass cls = dmAndroid::LoadClass(env, "com.defold.extension.ExtensionLogCat");

    InitJNIMethods(env, cls);

    jmethodID jni_constructor = env->GetMethodID(cls, "<init>", "(Landroid/app/Activity;)V");

    g_app.m_AppJNI = env->NewGlobalRef(env->NewObject(cls, jni_constructor, threadAttacher.GetActivity()->clazz));
}

void Initialize(const char* unitId)
{
     CallVoidMethodChar(g_app.m_AppJNI, g_app.m_Initialize, unitId);
}

void ReportEvent(const char* s1, const char* s2)
{
    CallVoidMethodCharChar(g_app.m_AppJNI, g_app.m_ReportEvent, s1, s2);
}


void ActivateApp()
{
    //
}

}

#endif
