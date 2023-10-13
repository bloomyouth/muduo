server:
	g++ Util.cpp client.cpp -o ../bin/client -std=c++11 && \
	g++ Channel.cpp Util.cpp Epoll.cpp server.cpp InetAddress.cpp Socket.cpp -o ../bin/server -std=c++11
clean:
	rm server && rm client