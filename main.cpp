#include "openvr.h"

#include <atomic>
#include <iostream>
#include <string>
#include <sstream>

#include <thread>
#include <mutex>

#include <filesystem>
#include <vector>

int main(int argc, char *argv[]) {
    vr::EVRInitError err = vr::VRInitError_None;
    vr::VR_Init(&err, vr::VRApplication_Scene);

    if (err != vr::VRInitError_None) {
        std::cout << "failed to init openvr! Err: " << vr::VR_GetVRInitErrorAsEnglishDescription(err) << std::endl;
        return 1;
    }

    while (true) {
        vr::VREvent_t vEvent;
        while (vr::VRSystem()->PollNextEvent(&vEvent, sizeof(vr::VREvent_t))) {
            switch (vEvent.eventType) {
                case vr::EVREventType::VREvent_Quit: {
                    return 0;
                }

                case vr::EVREventType::VREvent_StandingZeroPoseReset: {
                    std::cout << "standing zero pose reset" << std::endl;
                    break;
                }

                case vr::EVREventType::VREvent_SeatedZeroPoseReset: {
                    std::cout << "seated zero pose reset" << std::endl;
                    break;
                }

                default: {
                    break;
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}
