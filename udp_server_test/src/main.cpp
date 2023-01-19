#include <bits/chrono.h>
#include <udp_server.hpp>

#include <chrono>

#include <iostream>

#include <fstream>
#include <thread>

#include <condition_variable>
#include <mutex>

int main()
{
    riwa::bosch::udp_server server( 55555 );
    constexpr int           cycles = 80;

    std::mutex              mutex;
    std::condition_variable cond;

    std::chrono::high_resolution_clock clock;

    std::vector< std::chrono::microseconds > times;

    auto start_delay = clock.now();
    for ( int i = 0; i < cycles; i++ ) {

        std::string read_in;
        using namespace std::chrono_literals;

        // while ( end_delay - start_delay < 250ms ) {
        //     end_delay = clock.now();
        // }
        // std::this_thread::sleep_for( 250ms - ( end_delay - start_delay ) );

        auto start_timer = clock.now();
        start_delay      = clock.now();
        server.write( "\"Tessonics_Snd;1;1;32857;Spot_32857;TestWeldjob;1;Gun1_X;150;2;combination1;sheet1;"
                      "material1;80;sheet2;material2;70;\"" );
        server.read( read_in );
        auto end_timer = clock.now();

        auto end_delay = clock.now();

        times.push_back( std::chrono::duration_cast< std::chrono::microseconds >( end_timer - start_timer ) );
        int k = 0;
        for ( k = 0; k < 1000000000; k++ ) {
            int j = k;
            j++;
        }
        std::cout << k << "\n";
    }

    std::cout << "Intervals\n";

    std::ofstream out( "times.csv" );

    for ( auto x : times ) {
        std::cout << x << "\n";
        out << x.count() << ",";
    }
}