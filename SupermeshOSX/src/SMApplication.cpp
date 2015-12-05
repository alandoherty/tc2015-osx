#include "SMApplication.h"
#include "SMSurface.h"
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <SDL2/SDL.h>

using namespace Awesomium;

#define WEBCORE static_cast<WebCore*>(m_WebCore)

void SMApplication::Run(){
    while(true) {
        // poll
        if (!m_Window->Poll())
            return;
        
        // render
        m_Window->Flip();
    }
    
    
    
    WebView* view = WEBCORE->CreateWebView(APP_WIDTH, APP_HEIGHT);
    view->LoadURL(WebURL(WSLit("http://google.co.uk")));
    
    // finish loading the page
    while (view->IsLoading())
        WEBCORE->Update();
    
    
}

void SMApplication::Initialize() {
    // initialize awesomium
    m_WebCore = (WebCore*)WebCore::Initialize(WebConfig());
    WEBCORE->set_surface_factory(new SMSurfaceFactory());
    
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