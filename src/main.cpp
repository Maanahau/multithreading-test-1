#include "Logger.h"

#include "LightSensor.h"
#include "TemperatureSensor.h"
#include "HumiditySensor.h"

#include "ScreenLogSink.h"
#include "FileLogSink.h"

#include <iostream>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <exception>
#include <memory>

int main()
{
    // Set seed for random sensor readings
    srand(std::time(nullptr));

    // Initialize logger;
    Logger* logger = Logger::get_instance();

    // Initialize log sinks
    FileLogSink* file_logsink = new FileLogSink("log.txt");

    logger->add_logsink(std::make_unique<ScreenLogSink>());
    logger->add_logsink(std::unique_ptr<FileLogSink>(file_logsink));


    // Initialize sensors
    std::cout << "Initializing sensors...\n";
    std::unique_ptr<LightSensor> light_sensor = std::make_unique<LightSensor>();
    std::unique_ptr<TemperatureSensor> temp_sensor = std::make_unique<TemperatureSensor>();
    std::unique_ptr<HumiditySensor> hum_sensor = std::make_unique<HumiditySensor>();

    // Start reading
    std::cout << "Starting threads...\n";
    std::thread t_light_sensor;
    std::thread t_temp_sensor;
    std::thread t_hum_sensor;

    try
    {
        t_light_sensor = std::thread(&LightSensor::read, light_sensor.get());
        t_temp_sensor = std::thread(&TemperatureSensor::read, temp_sensor.get());
        t_hum_sensor = std::thread(&HumiditySensor::read, hum_sensor.get());
    }
    catch (std::exception* e)
    {
        std::cerr << e->what();
        return 0;
    }

    for(int i = 0; i < 2; i++)
    {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        logger->flush_queue();
        file_logsink->flush_queue();
    }

    // Stop reading
    light_sensor->stop();
    temp_sensor->stop();
    hum_sensor->stop();

    t_light_sensor.join();
    t_temp_sensor.join();
    t_hum_sensor.join();
    std::cout << "Sensors stopped.\n";

    return 0;
}