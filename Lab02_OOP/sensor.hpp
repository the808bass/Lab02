#pragma once

namespace incinerator
{

    enum class SensorType
    {
        eTemperature,
        eAirFlow,
        eSteamPressure,
    };

    class Sensor
    {
    public:
        Sensor(SensorType type, double value);
        ~Sensor();

        [[nodiscard]] SensorType GetType() const;
        [[nodiscard]] double GetValue() const;

        void TakeReading(double value);

    private:
        SensorType m_type;
        double m_value{ 0.0 };
    };

} // namespace incinerator