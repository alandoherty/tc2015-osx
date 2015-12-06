#ifndef SMApplication_h
#define SMApplication_h

#include "SMFramework.h"
#include "SMVideoFile.h"
#include <Awesomium/WebCore.h>

class SMApplication {
private:
    Awesomium::WebCore* m_WebCore;
    Awesomium::WebView* m_WebView;
    Awesomium::WebSession* m_WebSession;
    Awesomium::JSObject m_Global;
    Awesomium::JSObject m_StatusFunc;
    
    SMVideoFile* m_VideoFile;
public:
    Awesomium::WebView* Initialize();
    void Run();
    void Shutdown();
    void Open(const char* path);
    void On(Awesomium::WebString& name, Awesomium::JSObject& obj);
    
    void TriggerStatus(const char* path);
};

//------------------------------------------------------------------------
// Global application.
//------------------------------------------------------------------------
extern SMApplication* g_App;
#endif
