#include <udp_server.hpp>

#include <boost/asio.hpp>

#include <iostream>

namespace riwa::bosch {
    udp_server::udp_server() : socket( io_context ) {}

    boost::system::error_code udp_server::open( unsigned short const port )
    {
        std::cout << "Opening Server:\n";

        boost::system::error_code error;
        auto                      endpoint = boost::asio::ip::udp::endpoint( boost::asio::ip::udp::v4(), port );

        std::cout << "Connecting...\n";

        socket.open( boost::asio::ip::udp::v4() );

        socket.bind( endpoint );

        if ( error ) {
            std::cout << "Could not bind: " << error.message() << std::endl;
            return error;
        }

        std::cout << "Waiting for a response\n";

        std::string init_message;
        read( init_message );
        write( init_message );

        return error;
    }

    boost::system::error_code udp_server::write( std::string const & data )
    {
        boost::system::error_code error;
        auto bytes = socket.send_to( boost::asio::buffer( data, data.length() ), client_endpoint, 0, error );
        std::cout << bytes << "  Bytes Wrote\n";
        return error;  //
    }

    // assumes messages start and end with "
    boost::system::error_code udp_server::read( std::string & data )
    {
        boost::system::error_code error;

        std::string curr_char;
        auto        bytes = socket.receive_from( boost::asio::buffer( curr_char, 1 ), client_endpoint, 0,
                                                 error );  // read start delimeter

        data.append( curr_char );
        while ( true ) {
            curr_char = "";
            bytes += socket.receive( boost::asio::buffer( curr_char, 1 ), 0,
                                     error );  // read start delimeter
            data.append( curr_char );
            if ( curr_char == "\"" )
                break;
        }

        std::cout << bytes << " Bytes Read\n";

        std::cout << "Read " << data << "\n";

        return error;
    }

    void udp_server::close() { std::cout << "Closing Server\n"; }
}  // namespace riwa::bosch