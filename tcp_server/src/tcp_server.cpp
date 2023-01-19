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

    boost::system::error_code tcp_server::write( std::string const & data )
    {
        boost::system::error_code error;
        auto bytes = boost::asio::write( socket, boost::asio::buffer( data, data.length() ), error );
        std::cout << bytes << "  Bytes Wrote\n";
        return error;  //
    }

    // assumes messages start and end with "
    boost::system::error_code tcp_server::read( std::string & data )
    {
        boost::system::error_code error;

        std::string curr_char;

        auto bytes = boost::asio::read( socket, boost::asio::dynamic_buffer( curr_char ),
                                        boost::asio::transfer_exactly( 1 ), error );  // read start delimeter

        data.append( curr_char );
        while ( true ) {
            curr_char = "";
            bytes += boost::asio::read( socket, boost::asio::dynamic_buffer( curr_char ),
                                        boost::asio::transfer_exactly( 1 ), error );
            data.append( curr_char );
            if ( curr_char == "\"" )
                break;
        }

        std::cout << bytes << " Bytes Read\n";

        std::cout << "Read " << data << "\n";

        return error;
    }

    void tcp_server::close() { std::cout << "Closing Server\n"; }
}  // namespace riwa::bosch