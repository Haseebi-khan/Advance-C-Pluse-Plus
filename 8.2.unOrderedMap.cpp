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

    bool operator==(const CityRecordes &other) const
    {
        return name == other.name;
    }
};

namespace std
{
    template <>
    struct hash<CityRecordes>
    {
        // auto operator()(const CityRecordes& key)
        size_t operator()(const CityRecordes &key) const
        {
            return hash<string>()(key.name);
        }
    };
}

int main()
{
    unordered_map<CityRecordes, uint32_t> foundedMap;

    foundedMap[CityRecordes{"Smething", 50000, 2.4, 3.2}] = 1820;

    cout << foundedMap.at(CityRecordes{"Smething", 50000, 2.4, 3.2}) << endl;


    unordered_map<string, CityRecordes> cityMap;
    cityMap["Lahore"] = CityRecordes{"Lahore", 98770, 9.4, 3.3};
    cityMap["karachi"] = CityRecordes{"karachi", 56500, 3.4, 1.3};
    cityMap["islamabad"] = CityRecordes{"islamabad", 12000, 2.4, 2.3};
    cityMap["kpk"] = CityRecordes{"kpk", 200000, 7.3, 6.3};
    cityMap["quetta"] = CityRecordes{"sukar", 83000, 5.6, 2.3};
    cityMap["hydraabad"] = CityRecordes{"hydraabad", 76000, 4.24, 1.1};

    CityRecordes &QuettaData = cityMap["quetta"];
    cout << "Quetta Polpulation: " << QuettaData.Population << endl;

    // if the data is  not present it will insert.
    CityRecordes &dehliData = cityMap["Dehli"];
    cityMap["Dehli"].name = "Dehli";
    cityMap["Dehli"].Population = 87878000;
    cityMap["Dehli"].latitude = 1.2;
    cityMap["Dehli"].Longitude = 4.3;

    // it the best way to retrive the data without inserting data by using (at() method).
    CityRecordes &dehliData2 = cityMap["peshawar"];

    // if the type is const then we must use at method because index operator will not work.
    // for example

    // const auto &cities = cityMap;
    // if (cities.find("Dehli") != cities.end())
    // {
    //     const CityRecordes &Dehli = cities.at("Delhi");
    // }

    // for (auto &[name, Population] : cityMap)
    // for (auto &cityvalues : cityMap)
    // {
    //     string name = cityvalues.first;
    //     cout << name << endl;
    // }
    cityMap.erase("Lahore");
    for (auto &[name, city] : cityMap)
    {
        cout << "Name: " << name << "      Population: " << city.Population << " latitude: " << city.latitude << " Longitude: " << city.Longitude << endl;
    }

    return 0;
}