#include "daemon.hpp"

int main(int argc, char** argv)
{
    std::vector<std::string> arguments(argc-1);
    for (unsigned int i = 1; i < argc; i++)
    {
        arguments[i-1] = std::string(argv[i]);
    }
    
    Daemon master;
    master.execute(arguments);
    master.cleanup_spawn();
    master.ask();
    return 0;
}