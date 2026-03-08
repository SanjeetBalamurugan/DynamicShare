#pragma once

#include "asio.hpp"
#include <string>
#include <thread>
#include <iostream>
#include <vector>

using asio::ip::udp;

#define MULTICAST_PORT 30001
#define MULTICAST_ADDR "239.255.0.1"

enum class OSType {
	NONE,

	WINDOWS,
	MACOS,
	LINUX
};

struct Device {
	std::string device_id;
	std::string ip;
	int port;
	OSType os_type;

	static Device Empty() {
		return {"XX", "0.0.0.0", -1, OSType::NONE};
	}
};

class DeviceDiscovery {
	public:
		DeviceDiscovery() : m_Socket(m_Context) {}
		
		void SetupSender();
		void SendMessage(const std::string& message);

		void SetupReciever();
		std::string RecieveMessage();
		void AddDevice(std::string& device_data);

		std::string GetLocalIP() { return m_Socket.local_endpoint().address().to_string(); }
		std::vector<Device> getDevices() { return m_Devices; }

	private:
		asio::io_context m_Context;
		udp::socket m_Socket;
		udp::endpoint m_Endpoint;

		std::vector<char> m_Buffer{std::vector<char>(1024)};
		udp::endpoint m_SenderEndpoint;

		std::vector<Device> m_Devices;
		std::string m_DeviceID;
};

inline OSType getOsName()
{
    #ifdef _WIN32 || _WIN64
    return OSType::WINDOWS;
    #elif __APPLE__ || __MACH__
    return OSType::MACOS;
    #elif __linux__
    return OSType::LINUX;
    #else
    return OSType::NONE;
    #endif
}                      

