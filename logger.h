
#ifndef PROTOTIPE_LOGGER_H
#define PROTOTIPE_LOGGER_H


#include <string>

namespace logger {
    void init_logger(const std::string& file_name);
    void write_trace(const std::string& log);
    void write_debug(const std::string& log);
    void write_info(const std::string& log);
}


#endif //PROTOTIPE_LOGGER_H
