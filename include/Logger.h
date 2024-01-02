#ifndef LOGGER_H
#define LOGGER_H

#include "IReport.h"
#include "ILogSink.h"

#include <mutex>
#include <vector>
#include <queue>
#include <memory>

class Logger final
{
public:

    static Logger* get_instance();

    void push_report(std::unique_ptr<IReport> report);
    void flush_queue();
    void add_logsink(std::unique_ptr<ILogSink> log_sink);

private:

    Logger() = default;

    Logger(const Logger&) = delete;
    void operator=(const Logger&) = delete;

    static Logger* _instance;

    std::mutex _report_queue_mutex;
    std::mutex _log_sinks_vector_mutex;

    std::queue<std::unique_ptr<IReport>> _pending_reports;
    std::vector<std::unique_ptr<ILogSink>> _log_sinks;
};

#endif