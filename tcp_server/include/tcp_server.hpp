#if !defined( __RIWA__BOSCH__TCP_MANAGER__HPP__ )
#define __RIWA__BOSCH__TCP_MANAGER__HPP__

#include <string>

#include <boost/asio.hpp>

namespace riwa::bosch {
    class tcp_server {
    public:
        tcp_server();

        tcp_server( const unsigned short port ) : tcp_server() { open( port ); }  // create and open server

        boost::system::error_code open( unsigned short const port );

        void close();

        boost::system::error_code read( std::string & data );
        boost::system::error_code write( std::string const & data );

        ~tcp_server() { close(); }

    private:
        boost::asio::io_context        io_context;
        boost::asio::ip::tcp::socket   socket;
        boost::asio::ip::tcp::acceptor acceptor;
    };
}  // namespace riwa::bosch

#endif