#include "SMApplication.h"
#include "SMDataSource.h"
#include "SMVideoFile.h"
#include "SMMethodHandler.h"
extern "C" {
    #include "libavformat/avformat.h"
}


using namespace Awesomium;

 SMApplication* g_App = NULL;

//------------------------------------------------------------------------
// Initialize the application.
//------------------------------------------------------------------------
WebView* SMApplication::Initialize() {
    // initialize all codecs
    av_register_all();
    
    // setup config
    WebConfig config;
    config.remote_debugging_host = Awesomium::WSLit("127.0.0.1");
    config.remote_debugging_port = 1337;
    
    // create core
    m_WebCore = WebCore::Initialize(config);
    
    // create session
    m_WebSession = m_WebCore->CreateWebSession(WSLit(""), WebPreferences());
    m_WebSession->AddDataSource(WSLit("Supermesh"), new SMDataSource());
    
    // create view
    m_WebView = m_WebCore->CreateWebView(APP_WIDTH, APP_HEIGHT, m_WebSession, kWebViewType_Window);
    
    return m_WebView;
}

//------------------------------------------------------------------------
// Shutdown the application.
//------------------------------------------------------------------------
void SMApplication::Shutdown() {
    delete m_VideoFile;
}

void SMApplication::Open(const char* path) {
    // open video file
    m_VideoFile = new SMVideoFile(path);
    
    // trigger status
    TriggerStatus(path);
}

void SMApplication::Run() {
    // setup bindings
    JSValue result = m_WebView->CreateGlobalJavascriptObject(WSLit("supermesh"));
    m_Global = result.ToObject();
    m_Global.SetCustomMethod(WSLit("message"), false);
    m_Global.SetCustomMethod(WSLit("open"), false);
    m_Global.SetCustomMethod(WSLit("on"), false);
    
    // setup view
    m_WebView->set_js_method_handler(new SMMethodHandler());
    m_WebView->LoadURL(WebURL(WSLit("asset://Supermesh/index.html")));
    
    // validate bindings
    if (!result.IsObject()) {
        SMMessageBox("The app context failed to create, oh no", APP_NAME, MB_ERROR);
    }
}

void SMApplication::On(WebString& name, JSObject& obj) {
    if (name.Compare(WSLit("opened")) == 0) {
        m_StatusFunc = obj;
    }
    
    char* namePtr = SMWebStrToUTF8(name);
    printf("[supermesh] added event handler for %s", namePtr);
    free(namePtr);
}

void SMApplication::TriggerStatus(const char* path) {
    JSArray arr = JSArray(1);
    arr.Push(WebString::CreateFromUTF8(path, strlen(path)));
    m_StatusFunc.Invoke(WSLit("call"), arr);
}