#ifndef SOCKETHANDLER_H
#define SOCKETHANDLER_H

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>

#include "CommonNetwork.h"
#include <memory>
#define STARTBUFFERSIZE 1024 *1024 *4
#include "Encryption.h"
#include <functional>
#include <vector>
#include "Traffic_Monitor.h"
#include <mutex>

namespace RemoteDesktop{
	enum PeerState{
		PEER_STATE_DISCONNECTED,
		PEER_STATE_CONNECTING,
		PEER_STATE_CONNECTED,
		PEER_STATE_EXCHANGING_KEYS,
	};
	class socket_wrapper{
	public:
		SOCKET socket;

		explicit socket_wrapper(SOCKET s) : socket(s) { }
		~socket_wrapper();
		
	};
	class SocketHandler{
		std::mutex _SendLock;
		std::vector<char> _ReceivedBuffer, _SendBuffer;
		int _ReceivedBufferCounter = 0;
		Network_Return _SendLoop(char* data, int len);

		Packet_Encrypt_Header _Encypt_Header;
		Encryption _Encyption;
		Network_Return _Encrypt_And_Send(NetworkMessages m, const NetworkMsg& msg); 
		Network_Return _Decrypt_Received_Data();
		Network_Return _Complete_Key_Exchange();
		
		std::unique_ptr<socket_wrapper> _Socket;
		Network_Return _Disconnect();
		

	public:
		explicit SocketHandler(SOCKET socket, bool client);

		Network_Return Exchange_Keys();
		PeerState State = PEER_STATE_DISCONNECTED;
		Network_Return Send(NetworkMessages m, const NetworkMsg& msg);
		Network_Return Receive();
		SOCKET get_Socket() const { return _Socket ? _Socket->socket : INVALID_SOCKET; }
		std::function<void(Packet_Header*, const char*, SocketHandler*)> Receive_CallBack;
		std::function<void(SocketHandler*)> Connected_CallBack;
		std::function<void(SocketHandler*)> Disconnect_CallBack;

		Traffic_Monitor Traffic;

	};
};

#endif