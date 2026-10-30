#include "batch.hpp"
#include "furnace.hpp"

#include <iostream>

using namespace incinerator;

void ProcessViaReference(Furnace& furnace)
{
    std::cout << "processing via reference: " << furnace.GetName() << "\n";
    furnace.UpdateTemperature(850.0);
}

void ProcessViaPointer(Furnace* furnace)
{
    std::cout << "processing via pointer: " << furnace->GetName() << "\n";
    furnace->UpdateTemperature(860.0);
}

int main()
{
    std::cout << "1. Composition: furnace owns sensors\n";
    {
        Furnace furnace(1, "Furnace-A");
        furnace.AddSensor(SensorType::eTemperature, 800.0);
        furnace.AddSensor(SensorType::eAirFlow, 120.0);
        furnace.SetState(Furnace::State::eRunning);
        furnace.UpdateTemperature(850.0);
    }
    std::cout << "furnace block exited: sensors destroyed automatically\n\n";

    std::cout << "2. Aggregation: batch uses external furnace\n";
    Furnace* sharedFurnace = new Furnace(2, "Furnace-B");
    sharedFurnace->SetState(Furnace::State::eRunning);

    {
        Batch batch(100, "household");
        batch.AssignFurnace(sharedFurnace);
        batch.StartProcessing();
        batch.Close();
    }
    std::cout << "batch destroyed, but furnace still alive\n";
    sharedFurnace->UpdateTemperature(900.0);
    std::cout << "furnace-B temperature after batch destroyed: "
        << sharedFurnace->GetTemperature() << "\n\n";

    std::cout << "3. Rule check: cannot process in idle furnace\n";
    sharedFurnace->SetState(Furnace::State::eIdle);
    Batch batch2(101, "industrial");
    batch2.AssignFurnace(sharedFurnace);
    batch2.StartProcessing();
    std::cout << "rule check demonstrated\n\n";

    std::cout << "4. Static / dynamic / references / pointers\n";
    Furnace staticFurnace(3, "Static-Furnace");
    staticFurnace.SetState(Furnace::State::eRunning);
    ProcessViaReference(staticFurnace);
    ProcessViaPointer(&staticFurnace);

    Furnace* heapFurnace = new Furnace(4, "Heap-Furnace");
    heapFurnace->SetState(Furnace::State::eRunning);
    ProcessViaPointer(heapFurnace);
    delete heapFurnace;

    std::cout << "\n5. Dynamic array of dynamic objects\n";
    Furnace** furnaces = new Furnace * [2];
    furnaces[0] = new Furnace(5, "Array-Furnace-1");
    furnaces[1] = new Furnace(6, "Array-Furnace-2");

    for (int i = 0; i < 2; ++i)
    {
        furnaces[i]->SetState(Furnace::State::eRunning);
        furnaces[i]->UpdateTemperature(800.0 + i * 10);
    }

    for (int i = 0; i < 2; ++i)
    {
        delete furnaces[i];
    }
    delete[] furnaces;

    delete sharedFurnace;

    std::cout << "\nend of main\n";
    return 0;
}