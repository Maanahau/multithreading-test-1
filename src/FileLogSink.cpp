#include "FileLogSink.h"

#include "IReport.h"

#include <fstream>
#include <ostream>
#include <stdexcept>
#include <queue>
#include <memory>
#include <mutex>
#include <thread>

void FileLogSink::log(IReport* const report)
{
    std::lock_guard<std::mutex> lock (_queue_mutex);
    _pending_reports.push(std::unique_ptr<IReport>(report->clone()));
};

void FileLogSink::flush_queue()
{
    std::lock_guard<std::mutex> lock (_queue_mutex);

    std::ofstream stream (_file_path);
    if (!stream)
    {
        throw std::runtime_error("Error: couldn't open file " + _file_path + ".\n");
    }

    while(!_pending_reports.empty())
    {
        stream << _pending_reports.front()->get_content();
        _pending_reports.pop();
    }
}