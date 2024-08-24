#include "files.hpp"

const std::string datestamp_format = "%F";
const std::string timestamp_format = "%T";


File_Timestamp::File_Timestamp() :
    datestamp(""),
    timestamp("")
{
    update_timestamp();
}

File_Timestamp::~File_Timestamp()
{
}

void File_Timestamp::update_timestamp()
{
    time_t current_time = time(nullptr);
    struct tm* time_info = localtime(&current_time);

    char current_datestamp_buffer[11];
    strftime(current_datestamp_buffer, 11, datestamp_format.c_str(), time_info);
    datestamp = std::string(current_datestamp_buffer);

    char current_timestamp_buffer[9];
    strftime(current_timestamp_buffer, 9, timestamp_format.c_str(), time_info);
    timestamp = std::string(current_timestamp_buffer);
}

std::string File_Timestamp::get_datestamp() const
{
    return datestamp;
}

std::string File_Timestamp::get_timestamp() const
{
    return timestamp;
}

std::string File_Timestamp::get_datetimestamp() const
{
    return datestamp + "-" + timestamp;
}
