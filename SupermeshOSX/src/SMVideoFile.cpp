#include "SMVideoFile.h"

extern "C" {
    #include "libavformat/avformat.h"
    #include "libavcodec/avcodec.h"
    #include "libavutil/avutil.h"
    #include "libavdevice/avdevice.h"
}

SMVideoFile::SMVideoFile(const char* path) {
    // allocate format context
    m_FormatContext = avformat_alloc_context();
    
    // open video file
    if(avformat_open_input(&m_FormatContext, path, 0, NULL) != 0)
    {
        printf("[supermesh] couldn't open file\n");
        return;
    }
    
    // get stream information
    if(avformat_find_stream_info(m_FormatContext, NULL) < 0)
    {
        printf("[supermesh] failed to find stream info\n");
        return;
    }
    
    // dump stream data
    av_dump_format(m_FormatContext, 0, path, false);
}

SMVideoFile::~SMVideoFile() {
    // close the video file
    avformat_close_input(&m_FormatContext);
}
