#include <bits/chrono.h>
#include <tcp_server.hpp>

#include <chrono>

#include <iostream>

#include <fstream>
#include <thread>

#include <condition_variable>
#include <mutex>

int main()
{
    riwa::bosch::tcp_server server( 55555 );
    constexpr int           cycles = 80;

    std::mutex              mutex;
    std::condition_variable cond;

    std::chrono::high_resolution_clock clock;

    std::vector< std::chrono::microseconds > times;

    auto start_delay = clock.now();
    while ( true ) {
        std::string read_in;
        int         choice = 0;
        std::cin >> choice;
        switch ( choice ) {
        case 1:
            server.write( "\"Tessonics_Snd;1;1;32857;Spot_32857;TestWeldjob;1;Gun1_X;150;2;combination1;sheet1;"
                          "material1;80;sheet2;material2;70;\"" );
            server.read( read_in );
            break;
        case 2:
            server.write( "\"Tessonics_Snd;1;1;1;\"" );
            server.read( read_in );
            break;
        case 3:
            server.write( "\"Tessonics_Snd;1;1;0;\"" );
            server.read( read_in );
            break;
        }
    }
}