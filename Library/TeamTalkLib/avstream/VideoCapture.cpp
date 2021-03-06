/*
 * Copyright (c) 2005-2018, BearWare.dk
 * 
 * Contact Information:
 *
 * Bjoern D. Rasmussen
 * Kirketoften 5
 * DK-8260 Viby J
 * Denmark
 * Email: contact@bearware.dk
 * Phone: +45 20 20 54 59
 * Web: http://www.bearware.dk
 *
 * This source code is part of the TeamTalk SDK owned by
 * BearWare.dk. Use of this file, or its compiled unit, requires a
 * TeamTalk SDK License Key issued by BearWare.dk.
 *
 * The TeamTalk SDK License Agreement along with its Terms and
 * Conditions are outlined in the file License.txt included with the
 * TeamTalk SDK distribution.
 *
 */

#include "VideoCapture.h"

using namespace vidcap;

#if defined(ENABLE_MEDIAFOUNDATION)
#include "MFCapture.h"
typedef MFCapture videocapturedevice_t;

#elif defined(ENABLE_LIBVIDCAP)
#include "LibVidCap.h"
typedef LibVidCap videocapturedevice_t;

#elif defined(ENABLE_AVF)
#include "AVFCapture.h"
typedef AVFCapture videocapturedevice_t;

#elif defined(ENABLE_V4L2)
#include "V4L2Capture.h"
typedef V4L2Capture videocapturedevice_t;

#else

class NullVideoCapture : public VideoCapture
{
public:
    vidcap_devices_t GetDevices() { return vidcap_devices_t(); }

    bool InitVideoCapture(const ACE_TString& deviceid,
                          const media::VideoFormat& vidfmt) { return false; }
    
    bool StartVideoCapture() { return false; }

    void StopVideoCapture() {}

    media::VideoFormat GetVideoCaptureFormat() { return media::VideoFormat(); }

    bool RegisterVideoFormat(VideoCaptureCallback callback, media::FourCC fcc) { return false; }
    void UnregisterVideoFormat(media::FourCC fcc) {}
};
typedef NullVideoCapture videocapturedevice_t;
#endif

videocapture_t VideoCapture::Create()
{
    return videocapture_t(new videocapturedevice_t());
}
