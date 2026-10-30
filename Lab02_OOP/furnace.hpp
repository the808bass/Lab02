#pragma once

#include "sensor.hpp"

#include <string>
#include <vector>

namespace incinerator
{

    class Furnace
    {
    public:
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
        std::vector<Sensor> m_sensors{};
    };

} // namespace incinerator