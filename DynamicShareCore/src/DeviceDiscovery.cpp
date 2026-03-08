#include "DeviceDiscovery.h"
#include "misc/uuid.h"
#include <sstream>

void DeviceDiscovery::SetupSender() {
    m_DeviceID = uuid::generate_uuid_v4();

    m_Endpoint = udp::endpoint(asio::ip::make_address(MULTICAST_ADDR), MULTICAST_PORT);
    if (!m_Socket.is_open()) m_Socket.open(udp::v4());
    m_Socket.bind(udp::endpoint(udp::v4(), 0));
    m_Socket.set_option(asio::ip::multicast::hops(1));
}

void DeviceDiscovery::SendMessage(const std::string& message) {
	std::string info = m_DeviceID + "?" + std::to_string(static_cast<int>(getOsName())) + "?" + this->GetLocalIP() + std::to_string(30001);
	//m_Socket.send_to(asio::buffer(message), m_Endpoint);
	m_Socket.send_to(asio::buffer(info), m_Endpoint);
}

void DeviceDiscovery::SetupReciever() {
    udp::endpoint listen_point(asio::ip::address_v4::any(), MULTICAST_PORT);
    if (!m_Socket.is_open()) m_Socket.open(listen_point.protocol());
    m_Socket.set_option(udp::socket::reuse_address(true));
    m_Socket.bind(listen_point);
    m_Socket.set_option(asio::ip::multicast::join_group(asio::ip::make_address(MULTICAST_ADDR)));
}

std::string DeviceDiscovery::RecieveMessage() {
    m_Socket.wait(udp::socket::wait_read);
    size_t len = m_Socket.receive_from(asio::buffer(m_Buffer), m_SenderEndpoint);
    return std::string(m_Buffer.data(), len);
}

void DeviceDiscovery::AddDevice(std::string& device_data) {
	Device n = Device::Empty();
	std::vector<std::string> tokens;
	std::stringstream ss(device_data);
	std::string token;

	while (std::getline(ss, token, '?')) {
		tokens.push_back(token);
	}

	for (const Device& d: m_Devices) {
		if(tokens[0] == d.device_id)
			break;

		n.device_id = tokens[0];
		n.os_type = static_cast<OSType>(std::stoi(tokens[1]));
		n.ip = tokens[2];
		n.port = MULTICAST_PORT;
	}

	m_Devices.push_back(n);
}
