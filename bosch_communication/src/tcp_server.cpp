#include <tcp_server.hpp>

#include <boost/asio.hpp>

#include <iostream>

namespace riwa::bosch {
    tcp_server::tcp_server() : socket( io_context ), acceptor( io_context ) {}

    boost::system::error_code tcp_server::open( unsigned short const port )
    {
        std::cout << "Opening Server:\n";

        boost::system::error_code error;
        auto                      endpoint = boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), port );

        std::cout << "Connecting...\n";
        acceptor.open( endpoint.protocol(), error );

        if ( error ) {
            std::cout << "Acceptor is not open: " << error.message() << std::endl;
            return error;
        }

        acceptor.set_option( boost::asio::ip::tcp::acceptor::reuse_address( true ) );
        acceptor.bind( endpoint, error );

        if ( error ) {
            std::cout << "Could not bind: " << error.message() << std::endl;
            return error;
        }

        std::cout << "Waiting for a Connection\n";
        acceptor.listen();
        acceptor.accept( socket, error );

        if ( error ) {
            std::cout << "Could Not Accept Connection: " << error.message() << std::endl;
            return error;
        }

        std::cout << "Connection Open!\n";

        return error;
    }

    void tcp_server::close()
    {
        std::cout << "Closing Server\n";
        acceptor.close();
        socket.close();
    }
}  // namespace riwa::bosch