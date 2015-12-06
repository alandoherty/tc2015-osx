#ifndef SMVideoFile_h
#define SMVideoFile_h

#include "SMFramework.h"
extern "C" {
    #include "libavformat/avformat.h"
}

class SMVideoFile {
private:
    AVFormatContext* m_FormatContext;
public:
    SMVideoFile(const char* path);
    ~SMVideoFile();
};

#endif
