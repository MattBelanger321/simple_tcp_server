#include <tcp_server.hpp>

int main()
{
    riwa::bosch::tcp_server server( 55555 );
    server.write( "suh dude\"" );
}