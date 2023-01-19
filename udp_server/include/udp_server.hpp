#if !defined( __RIWA__BOSCH__UDP_MANAGER__HPP__ )
#define __RIWA__BOSCH__UDP_MANAGER__HPP__

#include <string>

#include <boost/asio.hpp>

namespace riwa::bosch {
    class udp_server {
    public:
        udp_server();

        udp_server( const unsigned short port ) : udp_server() { open( port ); }  // create and open server

        boost::system::error_code open( unsigned short const port );

        void close();

        boost::system::error_code read( std::string & data );
        boost::system::error_code write( std::string const & data );

        ~udp_server() { close(); }

    private:
        boost::asio::io_context      io_context;
        boost::asio::ip::udp::socket socket;

        boost::asio::ip::udp::endpoint client_endpoint;
    };
}  // namespace riwa::bosch

#endif