#ifndef FILE_LOG_SINK_H
#define FILE_LOG_SINK_H

#include "ILogSink.h"
#include "IReport.h"

#include <string>
#include <string_view>
#include <mutex>
#include <memory>
#include <queue>

class FileLogSink final : public ILogSink
{
public:

    FileLogSink(std::string_view file_path) : _file_path{file_path} {}

    void log(IReport* const report) override;
    void flush_queue();

private:

    std::string _file_path;
    std::mutex _queue_mutex;
    std::queue<std::unique_ptr<IReport>> _pending_reports;
};

#endif