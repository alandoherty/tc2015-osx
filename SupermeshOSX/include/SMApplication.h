#ifndef SMApplication_h
#define SMApplication_h

#include "SMFramework.h"
#include <Awesomium/WebCore.h>

class SMApplication {
private:
    Awesomium::WebCore* m_WebCore;
    Awesomium::WebView* m_WebView;
    Awesomium::WebSession* m_WebSession;
    
    Awesomium::JSObject m_StatusFunc;
    
public:
    Awesomium::WebView* Initialize();
    void Run();
    void Shutdown();
    void Open(const char* path);
};

//------------------------------------------------------------------------
// Global application.
//------------------------------------------------------------------------
static SMApplication* g_App;
#endif
