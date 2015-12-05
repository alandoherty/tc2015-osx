#ifndef SupermeshOSX_SMApplication_h
#define SupermeshOSX_SMApplication_h

#include "SMFramework.h"
#include "SMWindow.h"

//------------------------------------------------------------------------
// The application object.
//------------------------------------------------------------------------
class SMApplication {
private:
    SMWindow* m_Window;
    void* m_WebCore;
public:
    void Initialize();
    void Run();
    void Shutdown();
};

static SMApplication* g_App;
#endif
