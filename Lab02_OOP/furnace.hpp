#pragma once

#include "sensor.hpp"

#include <cstddef>
#include <string>

namespace incinerator
{

    class Furnace
    {
    public:
        // Максимальное количество датчиков, которое можно установить в печь
        static constexpr std::size_t kMaxSensors{ 8 };

        enum class State
        {
            eRunning,
            eIdle,
            eSafe,
        };

        Furnace(int id, const std::string& name);
        ~Furnace();

        Furnace() = delete;
        Furnace(const Furnace&) = delete;
        Furnace& operator=(const Furnace&) = delete;

        [[nodiscard]] int GetId() const;
        [[nodiscard]] std::string GetName() const;
        [[nodiscard]] State GetState() const;
        [[nodiscard]] double GetTemperature() const;

        void AddSensor(SensorType type, double initialValue);
        void UpdateTemperature(double value);
        void SetState(State state);

        [[nodiscard]] bool CanProcess() const;

    private:
        int m_id{};
        std::string m_name{};
        State m_state{ State::eIdle };
        double m_temperature{ 20.0 };

        // Композиция: печь сама создает датчики (new) и сама удаляет их (delete)
        Sensor* m_sensors[kMaxSensors]{};
        std::size_t m_sensorCount{ 0 };
    };

} // namespace incinerator