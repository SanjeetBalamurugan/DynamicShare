#include <iostream>
#include "DeviceDiscovery.h"

#ifdef _WIN64 || _WIN32
#include <conio.h>
#endif

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    
    DeviceDiscovery d;
    int mode = std::stoi(argv[1]);

    if (mode == 0) {
        d.SetupSender();
        std::string msg = "Hello from " + d.GetLocalIP() + ":" + std::to_string(MULTICAST_PORT);
        while (true) {
            d.SendMessage(msg);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } else if (mode == 1) {
        d.SetupReciever();
        while (true) {
		std::string device_data = d.RecieveMessage();
		std::cout << "Received: " << device_data << std::endl;
		d.AddDevice(device_data);

#ifdef _WIN32 || _WIN64
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 'q') break;
		}
#endif
        }
    }

    for (const Device& dv: d.getDevices()) {
	    dv.pprint();
    }

    return 0;
}
