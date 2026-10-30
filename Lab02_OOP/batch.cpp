#include "batch.hpp"

#include <iostream>

namespace incinerator
{

    Batch::Batch(int id, const std::string& wasteClass)
        : m_id{ id }
        , m_wasteClass{ wasteClass }
    {
        std::cout << "[Batch] created: id=" << m_id << ", class=" << m_wasteClass << "\n";
    }

    Batch::~Batch()
    {
        std::cout << "[Batch] destroyed: id=" << m_id << "\n";
    }

    int Batch::GetId() const
    {
        return m_id;
    }

    Batch::Status Batch::GetStatus() const
    {
        return m_status;
    }

    Furnace* Batch::GetFurnace() const
    {
        return m_furnace;
    }

    void Batch::AssignFurnace(Furnace* furnace)
    {
        m_furnace = furnace;
    }

    void Batch::StartProcessing()
    {
        if (m_furnace == nullptr)
        {
            std::cout << "[Batch] error: no furnace assigned\n";
            return;
        }

        if (!m_furnace->CanProcess())
        {
            return;
        }

        m_status = Status::eProcessing;
        std::cout << "[Batch] id=" << m_id << " started processing\n";
    }

    void Batch::Close()
    {
        if (m_status != Status::eProcessing)
        {
            std::cout << "[Batch] error: batch is not in processing state\n";
            return;
        }
        m_status = Status::eClosed;
        std::cout << "[Batch] id=" << m_id << " closed\n";
    }

    void Batch::Reject()
    {
        m_status = Status::eRejected;
        std::cout << "[Batch] id=" << m_id << " rejected\n";
    }

} // namespace incinerator