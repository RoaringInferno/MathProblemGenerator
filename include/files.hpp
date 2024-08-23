#pragma once

#include <string>

class File_Timestamp
{
private:
    const std::string datestamp_format = "%Y-%m-%d";
    const std::string timestamp_format = "%H:%M:%S";
private:
    std::string datestamp;
    std::string timestamp;
public:
    File_Timestamp();
    ~File_Timestamp();

    void update_timestamp();

    std::string get_datestamp() const;
    std::string get_timestamp() const;
    std::string get_datetimestamp() const;
};