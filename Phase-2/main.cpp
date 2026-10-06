#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <iomanip>
using namespace std;

const int TOTAL_ZONES = 100;
const int TOTAL_NODES = 101;

struct Zone
{
    int id;
    string crop;
    float moisture;
    float temperature;
    float rainfall;
    float waterNeeded;
    float priority;
};

struct Reading
{
    int zoneId;
    float moisture;
    float temperature;
    float rainfall;
};

vector<Zone> zones;
queue<Reading> sensorQueue;
vector<vector<pair<int,int>>> graph;
vector<string> history;
float tankWater = 20000;

int randomNumber(int,int);
float calculatePriority(Zone);
string nodeName(int);

void addPipe(int,int,int);
bool removePipe(int,int);
void showNetwork();
void dijkstra(int,vector<int>&,vector<int>&);
string getPath(int,vector<int>&);
void changePipe();

void addManualReading();
void simulateReadings();
void processQueue();
void showZones();
void runIrrigation();
void forceIrrigationDemo();
void showHistory();
void addWater();
void setupFarm();

int main()
{
    srand((unsigned)time(0));
    setupFarm();

    int choice;

    do
    {
        cout << "\n=========================================\n";
        cout << "  SMART WATER MANAGEMENT & IRRIGATION\n";
        cout << "=========================================\n";
        cout << "1. Show farm zones\n";
        cout << "2. Enter a sensor reading manually\n";
        cout << "3. Simulate random sensor readings\n";
        cout << "4. Process sensor queue (calculate priority)\n";
        cout << "5. Run irrigation (priority + Dijkstra)\n";
        cout << "6. Show water pipe network\n";
        cout << "7. Change pipe network\n";
        cout << "8. Add water to tank\n";
        cout << "9. Show irrigation history\n";
        cout << "10. Force irrigation demo\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Invalid input.\n";
            continue;
        }

        switch(choice)
        {
            case 1:
                showZones();
                break;

            case 2:
                addManualReading();
                break;

            case 3:
                simulateReadings();
                break;

            case 4:
                processQueue();
                break;

            case 5:
                runIrrigation();
                break;

            case 6:
                showNetwork();
                break;

            case 7:
                changePipe();
                break;

            case 8:
                addWater();
                break;

            case 9:
                showHistory();
                break;

            case 10:
                forceIrrigationDemo();
                break;

            case 0:
                cout << "\nExiting program. Thank you!\n";
                break;

            default:
                cout << "\nInvalid choice, try again.\n";
        }

    }while(choice != 0);

    return 0;
}
