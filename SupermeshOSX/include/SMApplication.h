#ifndef SMApplication_h
#define SMApplication_h

#include "SMFramework.h"
#include <Awesomium/WebCore.h>

class SMApplication {
private:
    Awesomium::WebCore* m_WebCore;
    Awesomium::WebView* m_WebView;
    Awesomium::WebSession* m_WebSession;
public:
    Awesomium::WebView* Initialize();
    void Run();
    void Shutdown();
};

//------------------------------------------------------------------------
// Global application.
//------------------------------------------------------------------------
static SMApplication* g_App;
#endif
