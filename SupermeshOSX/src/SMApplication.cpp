#include "SMApplication.h"
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <SDL2/SDL.h>
#include <Awesomium/common/
using namespace Awesomium;

void SMApplication::Run(){
    while(true) {
        // poll
        if (!m_Window->Poll())
            return;
        
        // render
        m_Window->Flip();
    }
    
    WebCore* core = WebCore::Initialize(WebConfig());
    
    WebView* view = core->CreateWebView(APP_WIDTH, APP_HEIGHT);
    view->LoadURL(WebURL(WSLit("http://google.co.uk")));
    
    // finish loading the page
    while (view->IsLoading())
        core->Update();
    
    
}

void SMApplication::Initialize() {
    // initialize awesomium
    m_WebCore = (WebCore*)WebCore::Initialize(WebConfig());
    
    // create window
    m_Window = new SMWindow(APP_NAME, APP_WIDTH, APP_HEIGHT);
    
    // show window
    m_Window->Show();
}

void SMApplication::Shutdown() {
    // delete window
    delete m_Window;
    
    // shutdown webcore
    WebCore::Shutdown();
}