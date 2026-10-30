#include "furnace.hpp"

#include <iostream>

namespace incinerator
{

    Furnace::Furnace(int id, const std::string& name)
        : m_id{ id }
        , m_name{ name }
    {
        std::cout << "[Furnace] created: " << m_name << " (id=" << m_id << ")\n";
    }

    Furnace::~Furnace()
    {
        std::cout << "[Furnace] destroyed: " << m_name << "\n";
    }

    int Furnace::GetId() const
    {
        return m_id;
    }

    std::string Furnace::GetName() const
    {
        return m_name;
    }

    Furnace::State Furnace::GetState() const
    {
        return m_state;
    }

    double Furnace::GetTemperature() const
    {
        return m_temperature;
    }

    void Furnace::AddSensor(SensorType type, double initialValue)
    {
        m_sensors.emplace_back(type, initialValue);
    }

    void Furnace::UpdateTemperature(double value)
    {
        if (value > 1200.0)
        {
            std::cout << "[Furnace] error: temperature exceeds upper limit (1200)\n";
            return;
        }
        m_temperature = value;
    }

    void Furnace::SetState(State state)
    {
        m_state = state;
    }

    bool Furnace::CanProcess() const
    {
        if (m_state == State::eIdle)
        {
            std::cout << "[Furnace] cannot process: furnace is idle\n";
            return false;
        }
        if (m_state == State::eSafe)
        {
            std::cout << "[Furnace] cannot process: furnace is in safe state\n";
            return false;
        }
        return true;
    }

} // namespace incinerator