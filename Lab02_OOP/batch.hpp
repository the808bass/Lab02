#pragma once

#include "furnace.hpp"

#include <string>

namespace incinerator
{

    class Batch
    {
    public:
        enum class Status
        {
            eAccepted,
            eProcessing,
            eClosed,
            eRejected,
        };

        Batch(int id, const std::string& wasteClass);
        ~Batch();

        [[nodiscard]] int GetId() const;
        [[nodiscard]] Status GetStatus() const;
        [[nodiscard]] Furnace* GetFurnace() const;

        void AssignFurnace(Furnace* furnace);
        void StartProcessing();
        void Close();
        void Reject();

    private:
        int m_id{};
        std::string m_wasteClass{};
        Status m_status{ Status::eAccepted };
        Furnace* m_furnace{ nullptr };
    };

} // namespace incinerator