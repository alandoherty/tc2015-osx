#include "SMApplication.h"
#include "SMDataSource.h"
#include "SMMethodHandler.h"

using namespace Awesomium;

//------------------------------------------------------------------------
// Initialize the application.
//------------------------------------------------------------------------
WebView* SMApplication::Initialize() {
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
    WebView* m_WebView = m_WebCore->CreateWebView(APP_WIDTH, APP_HEIGHT, m_WebSession, kWebViewType_Window);
    
    // setup view
    m_WebView->set_js_method_handler(new SMMethodHandler());
    m_WebView->LoadURL(WebURL(WSLit("asset://Supermesh/index.html")));
    
    // setup bindings
    JSValue result = m_WebView->CreateGlobalJavascriptObject(WSLit("supermesh"));
    JSObject resultAsObj = result.ToObject();
    resultAsObj.SetCustomMethod(WSLit("message"), false);
    
    // validate bindings
    if (!result.IsObject()) {
        SMMessageBox("The app context failed to create, oh no", APP_NAME, MB_ERROR);
        return NULL;
    }
    
    return m_WebView;
}