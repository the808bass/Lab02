#include "sensor.hpp"

#include <iostream>

namespace incinerator
{

    Sensor::Sensor(SensorType type, double value)
        : m_type{ type }
        , m_value{ value }
    {
        std::cout << "[Sensor] created (type=" << static_cast<int>(type) << ", value=" << value << ")\n";
    }

    Sensor::~Sensor()
    {
        std::cout << "[Sensor] destroyed (type=" << static_cast<int>(m_type) << ")\n";
    }

    SensorType Sensor::GetType() const
    {
        return m_type;
    }

    double Sensor::GetValue() const
    {
        return m_value;
    }

    void Sensor::TakeReading(double value)
    {
        if (value < 0.0)
        {
            std::cout << "[Sensor] error: reading cannot be negative\n";
            return;
        }
        m_value = value;
    }

} // namespace incinerator