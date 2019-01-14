#include "parallel_checker.hpp"

using namespace std;

const pair<string, vector<string>> read_input(const string& filename)
{
    ifstream f(filename);
    string inequality;
    vector<string> constraints;

    getline(f, inequality);

    for (string line; getline(f, line);)
    {
        constraints.push_back(line);
    }

    return { inequality, constraints };
}

int main(int argc, const char * argv[])
{
    if (argc != 1 && argc != 4)
    {
        return 1;
    }

    long_d min_angle = 0.0;
    long_d max_angle = M_PI;
    long_d phi_angle = 0.0;

    if (argc == 4)
    {
        // For convenience, angles are expressed in degrees on the command line.
        min_angle = convert_degrees_to_radians(atof(argv[1]));
        max_angle = convert_degrees_to_radians(atof(argv[2]));
        phi_angle = convert_degrees_to_radians(atof(argv[3]));
    }

    try
    {
        auto input = read_input("inequality.txt");
        ParallelChecker parallel_checker(input.first,
                                         input.second,
                                         min_angle,
                                         max_angle,
                                         phi_angle);
        parallel_checker.run();
        parallel_checker.display_stats();
    }
    catch (const runtime_error& error)
    {
        cout << "ERROR! " << error.what() << endl;
    }

    return 0;
}
