#ifndef SupermeshOSX_SMWindow_h
#define SupermeshOSX_SMWindow_h

#include "SMFramework.h"

class SMWindow {
private:
    void* m_Window;
    void* m_Renderer;
public:
    ~SMWindow();
    SMWindow(const char* title, SMInt32 width, SMInt32 height);
    
    void Show();
    SMBool Poll();
    void Hide();
    void Flip();
};

#endif
