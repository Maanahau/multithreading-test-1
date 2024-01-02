#include "Logger.h"

#include "ILogSink.h"
#include "IReport.h"

#include <mutex>
#include <queue>
#include <vector>
#include <memory>

Logger* Logger::_instance {nullptr};

Logger* Logger::get_instance()
{
    if (!_instance)
    {
        _instance = new Logger();
    }

    return _instance;
}

void Logger::push_report(std::unique_ptr<IReport> report)
{
    std::lock_guard<std::mutex> lock (_report_queue_mutex);
    _pending_reports.push(std::move(report));
}

void Logger::flush_queue()
{
    std::lock_guard<std::mutex> queue_lock (_report_queue_mutex);
    std::lock_guard<std::mutex> vector_lock (_log_sinks_vector_mutex);

    while (!_pending_reports.empty())
    {
        IReport* const next_report = _pending_reports.front().get();
        for (const auto& log_sink : _log_sinks)
        {
            log_sink->log(next_report);
        }
        _pending_reports.pop();
    }
}

void Logger::add_logsink(std::unique_ptr<ILogSink> log_sink)
{
    std::lock_guard<std::mutex> lock (_log_sinks_vector_mutex);
    _log_sinks.push_back(std::move(log_sink));
}