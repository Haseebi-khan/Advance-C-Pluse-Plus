#include <iostream>
#include <vector>
#include <cstdint>

#include <map>
#include <unordered_map>

using namespace std;


struct CityRecordes
{
    string name;
    uint64_t Population;
    double latitude, Longitude;
};

int main()
{
    vector<CityRecordes> cities;

    cities.emplace_back("Lahore", 98770, 9.4, 3.3);
    cities.emplace_back("karachi", 56500, 3.4, 1.3);
    cities.emplace_back("islamabad", 12000, 2.4, 2.3);
    cities.emplace_back("kpk", 200000, 7.3, 6.3);
    cities.emplace_back("sukar", 83000, 5.6, 2.3);
    cities.emplace_back("hydraabad", 76000, 4.24, 1.1);

    for (const auto &city : cities)
    {
        if (city.name == "islamabad")
        {
            cout << "city Popullation: " << city.Population << endl;
        }
    }

    map<string, CityRecordes> cityMap;
    cityMap["Lahore"] = CityRecordes{"Lahore", 98770, 9.4, 3.3};
    cityMap["karachi"] = CityRecordes{"karachi", 56500, 3.4, 1.3};
    cityMap["islamabad"] = CityRecordes{"islamabad", 12000, 2.4, 2.3};
    cityMap["kpk"] = CityRecordes{"kpk", 200000, 7.3, 6.3};
    cityMap["quetta"] = CityRecordes{"sukar", 83000, 5.6, 2.3};
    cityMap["hydraabad"] = CityRecordes{"hydraabad", 76000, 4.24, 1.1};

    CityRecordes& QuettaData = cityMap["quetta"];
    cout << "Quetta Polpulation: " << QuettaData.Population <<endl;

    return 0;
}