#if !defined( __RIWA__BOSCH__CONVERTER_INTERFACE__HPP__ )
#define __RIWA__BOSCH__CONVERTER_INTERFACE__HPP__

#include <string>

namespace riwa::bosch {

    class converter_interface {
    public:
        converter_interface();

        converter_interface(
            std::string const port_name,
            int               baud                              //
            /*add any flags that you require as parameters*/ )  // if baud rate is require it may make more sense to
                                                                // make it an enum if there are only certain permissable
                                                                // values
            :
            converter_interface()
        {
            open( port_name, baud /*other flags if you add them*/ );
        }

        int transfer( float const & out );  // out is the value to send, returns status
                                            // code of operation

        bool is_connected();  // true if port is open

        int open( std::string const port_name,
                  int               baud                            //
                  /*add any flags that you require as parameters*/  //
        );                                                          // returns status code of operation

        int close();  // returns status code of operation

        ~converter_interface() { close(); };

    private:
    };

}  // namespace riwa::bosch

#endif