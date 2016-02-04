#include "help.h"

Help::Help()
{
}

void Help::showHelp()
{
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"    ********  ********  ********  ********  ********  ********     "<<std::endl;
    std::cout<<"    ********  ********  ********  ********  ********  ********     "<<std::endl;
    std::cout<<"    **    **  **    **  **        **        **    **  **           "<<std::endl;
    std::cout<<"    **    **  ********  *******   **        **    **  **   ***       "<<std::endl;
    std::cout<<"    ** ** **  ****      **        **        **    **  **    **     "<<std::endl;
    std::cout<<"    **  ****  **  **    ********  ********  ********  ********     "<<std::endl;
    std::cout<<"    ********  **   ***  ********  ********  ********  ********     "<<std::endl;
     std::cout<<"          **                                                      "<<std::endl;
    std::cout<<std::endl;
    std::cout<<"  Acquisition, clusterization, recognition for 3D computer vision  "<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"    QRecog usage: QRecog [option1] [option2] ..."<<std::endl;
    std::cout<<std::endl;
    std::cout<<"         Options:"<<std::endl;
    std::cout<<"             -h: Show this help"<<std::endl;
    std::cout<<"             -s: Use simulation"<<std::endl;
    std::cout<<"             -usb: Use usb device"<<std::endl;
    std::cout<<"             -gv: Use GigE Vision device"<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"**********************************************************************"<<std::endl;
}
