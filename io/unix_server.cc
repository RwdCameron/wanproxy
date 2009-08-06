#include <sys/socket.h>

#include <common/buffer.h>

#include <event/action.h>
#include <event/callback.h>
#include <event/event_system.h>

#include <io/file_descriptor.h>
#include <io/socket.h>
#include <io/unix_server.h>

UnixServer *
UnixServer::listen(const std::string& name)
{
	Socket *socket = Socket::create(PF_UNIX, SOCK_STREAM, "unix");
	if (socket == NULL) {
		ERROR("/unix/server") << "Unable to create socket.";
		return (NULL);
	}
	/*
	 * XXX
	 * After this we could leak a socket, sigh.  Need a blocking close, or
	 * a pool to return the socket to.
	 */
	if (!socket->bind(name, portp)) {
		ERROR("/unix/server") << "Socket bind failed, leaking socket.";
		return (NULL);
	}
	if (!socket->listen(10)) {
		ERROR("/unix/server") << "Socket listen failed, leaking socket.";
		return (NULL);
	}
	UnixServer *server = new UnixServer(socket);
	return (server);
}