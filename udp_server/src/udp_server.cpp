#include <stdexcept>
#include <udp_server.hpp>

#include <boost/asio.hpp>

#include <boost/array.hpp>
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

        boost::array< char, 9 > curr_char;
        socket.receive_from( boost::asio::buffer( curr_char, 9 ), client_endpoint, 0,
                             error );  // read start delimeter

        std::cout << "client responded\n";
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
        std::size_t               bytes;
        {
            boost::array< char, 20 > curr_char;
            bytes = socket.receive_from( boost::asio::buffer( curr_char, 117 ), client_endpoint, 0,
                                         error );  // read start delimeter
            std::cout << bytes << " bytes read\n";
        }

        return error;

        std::cout << data << "\n";
        while ( true ) {
            boost::array< char, 1 > curr_char;
            bytes += socket.receive_from( boost::asio::buffer( curr_char, 1 ), client_endpoint, 0,
                                          error );  // read start delimeter
            if ( bytes <= 0 ) {
                throw std::runtime_error( "Read 0 Bytes" );
            }

            data.append( { curr_char[0] } );

            if ( curr_char[0] == '\"' )
                break;
        }

        std::cout << bytes << " Bytes Read\n";

        std::cout << "Read " << data << "\n";

        return error;
    }

    void udp_server::close() { std::cout << "Closing Server\n"; }
}  // namespace riwa::bosch