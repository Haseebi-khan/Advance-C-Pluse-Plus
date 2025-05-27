#include <iostream>
#include <fstream>
#include <string>
#include <optional>
using namespace std;

string path = "D:\\Codes\\Advance-C-Pluse-Plus\\utility_Types\\4.2.fileOptional.txt";

string readFileasString(const string &path, bool &fileOpenedSuccessfuly)
{
    fstream afile;
    afile.open(path, ios::in);

    if (!afile.is_open())
    {
        return "Error in Opening in File.\n";
    }

    fileOpenedSuccessfuly = true;

    string line;
    int line_num = 0;
    while (getline(afile, line))
    {
        line_num++;
        // cout << line << endl;
        if (line_num == 8)
        {
            break;
        }
        
    }

    afile.close();

    return line;
}

optional<string> readFileasString2(const string &path)
{
    fstream afile;
    afile.open(path, ios::in);

    if (afile.is_open())
    {
        string line;
        int line_num = 0;
        while (getline(afile, line))
        {
            line_num++;
            // cout << line << endl;
            if (line_num == 10)
            {
                break;
            }
        }

        afile.close();
        
        return line;

    }

    return {};
}

int main()
{
    // bool fileOpenedSuccessfuly = false;
    // readFileasString(::path, fileOpenedSuccessfuly);

    // if (fileOpenedSuccessfuly)
    // {
    //     cout << "file was opened.\n";
    // }

    // optional<string> data = readFileasString2(::path);
                    //  OR 
    auto data = readFileasString2(::path);

    string value = data.value_or("Not Present"); // no data

    if(data)
    {
        cout << value <<endl;
        cout << "Data read successfully.\n";
    }
    else
    {
        cout << "File is not found.\n";
    }


    return 0;
}