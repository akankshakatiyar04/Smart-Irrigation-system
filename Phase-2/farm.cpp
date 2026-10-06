#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <iomanip>
#include <cstdlib>
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

extern vector<Zone> zones;
extern queue<Reading> sensorQueue;
extern vector<vector<pair<int,int>>> graph;
extern vector<string> history;
extern float tankWater;

int randomNumber(int min,int max)
{
    return rand()%(max-min+1)+min;
}

float calculatePriority(Zone z)
{
    float temperatureScore =
        ((z.temperature-10)/40.0)*100;

    if(temperatureScore < 0)
        temperatureScore=0;

    if(temperatureScore > 100)
        temperatureScore=100;

    return
        0.5*(100-z.moisture)
        +
        0.3*temperatureScore
        +
        0.2*(100-z.rainfall);
}

void addManualReading()
{
    Reading r;

    cout << "\nEnter zone id (1-100): ";
    cin >> r.zoneId;

    if(r.zoneId<1 || r.zoneId>100)
    {
        cout << "Invalid zone!\n";
        return;
    }

    cout << "Soil moisture (0-100 %): ";
    cin >> r.moisture;

    cout << "Temperature (C): ";
    cin >> r.temperature;

    cout << "Rainfall probability (0-100 %): ";
    cin >> r.rainfall;

    if(r.moisture<0 || r.moisture>100 ||
       r.rainfall<0 || r.rainfall>100)
    {
        cout << "Invalid sensor values!\n";
        return;
    }

    sensorQueue.push(r);

    cout << "Reading added to the sensor queue.\n";
}

void simulateReadings()
{
    cout << "\n====================================================\n";
    cout << "       GENERATING RANDOM SENSOR READINGS\n";
    cout << "====================================================\n";

    for(int i=1;i<=TOTAL_ZONES;i++)
    {
        Reading r;
        r.zoneId=i;

        int type=i%4;

        if(type==0)
        {
            r.moisture=randomNumber(20,45);
            r.temperature=randomNumber(32,40);
            r.rainfall=randomNumber(5,30);
        }
        else if(type==1)
        {
            r.moisture=randomNumber(70,95);
            r.temperature=randomNumber(20,30);
            r.rainfall=randomNumber(10,50);
        }
        else if(type==2)
        {
            r.moisture=randomNumber(35,65);
            r.temperature=randomNumber(20,35);
            r.rainfall=randomNumber(70,100);
        }
        else
        {
            r.moisture=randomNumber(40,65);
            r.temperature=randomNumber(25,38);
            r.rainfall=randomNumber(20,60);
        }

        sensorQueue.push(r);
    }

    cout << "\n100 random readings generated.\n";
}

void processQueue()
{
    if(sensorQueue.empty())
    {
        cout << "\nSensor queue is empty.\n";
        return;
    }

    cout << "\n====================================================\n";
    cout << "             PROCESSING SENSOR QUEUE\n";
    cout << "====================================================\n";

    int count=0;

    while(!sensorQueue.empty())
    {
        Reading r=sensorQueue.front();
        sensorQueue.pop();

        Zone &z=zones[r.zoneId-1];

        z.moisture=r.moisture;
        z.temperature=r.temperature;
        z.rainfall=r.rainfall;
        z.priority=calculatePriority(z);

        count++;

        cout << "Zone "
             << setw(3)
             << z.id
             << " -> Moisture "
             << setw(5)
             << z.moisture
             << "% | Priority "
             << fixed
             << setprecision(2)
             << z.priority
             << endl;
    }

    cout << "\n"
         << count
         << " readings processed.\n";
}

void showZones()
{
    cout << "\n";
    cout << "=====================================================================\n";
    cout << "                         FARM ZONES\n";
    cout << "=====================================================================\n";

    cout << left
         << setw(6) << "ID"
         << setw(14) << "Crop"
         << setw(10) << "Moist%"
         << setw(10) << "Temp"
         << setw(10) << "Rain%"
         << setw(12) << "Need(L)"
         << setw(10) << "Priority"
         << endl;

    cout << "---------------------------------------------------------------------\n";

    for(int i=0;i<zones.size();i++)
    {
        cout << left
             << setw(6) << zones[i].id
             << setw(14) << zones[i].crop
             << setw(10) << fixed << setprecision(1)
             << zones[i].moisture
             << setw(10) << zones[i].temperature
             << setw(10) << zones[i].rainfall
             << setw(12) << zones[i].waterNeeded
             << setw(10) << zones[i].priority
             << endl;
    }

    cout << "\nTotal zones: "
         << TOTAL_ZONES
         << endl;

    cout << "Water in tank: "
         << tankWater
         << " L\n";
}

void runIrrigation()
{
    if(tankWater<=0)
    {
        cout << "\nTank is empty!\n";
        return;
    }

    priority_queue<pair<float,int>> pq;

    for(int i=0;i<zones.size();i++)
    {
        zones[i].priority=calculatePriority(zones[i]);

        pq.push(
            make_pair(
                zones[i].priority,
                zones[i].id
            )
        );
    }

    vector<int> distance;
    vector<int> parent;

    dijkstra(0,distance,parent);

    cout << "\n====================================================\n";
    cout << "              IRRIGATION SYSTEM\n";
    cout << "====================================================\n";

    int irrigated=0;
    int skipped=0;
    int partial=0;

    while(!pq.empty())
    {
        int zoneID=pq.top().second;
        pq.pop();

        Zone &z=zones[zoneID-1];

        cout << "\n----------------------------------------------------\n";

        cout << "Zone "
             << z.id
             << " ("
             << z.crop
             << ")";

        cout << "\nPriority: "
             << fixed
             << setprecision(2)
             << z.priority;

        cout << "\nMoisture: "
             << z.moisture
             << "%";

        cout << "\nRainfall: "
             << z.rainfall
             << "%";

        if(z.waterNeeded<=0)
        {
            cout << "\nDecision: SKIP";
            cout << "\nReason: Water requirement complete.";

            history.push_back(
                "Zone "+to_string(z.id)+
                ": skipped (water requirement complete)"
            );

            skipped++;
            continue;
        }

        if(distance[zoneID]==INT_MAX)
        {
            cout << "\nDecision: SKIP";
            cout << "\nReason: No pipe route.";

            history.push_back(
                "Zone "+to_string(z.id)+
                ": skipped (no route)"
            );

            skipped++;
            continue;
        }

        if(z.rainfall>=70 && z.moisture>=60)
        {
            cout << "\nDecision: SKIP";
            cout << "\nReason: Rain likely and soil is moist.";

            history.push_back(
                "Zone "+to_string(z.id)+
                ": skipped (rain + sufficient moisture)"
            );

            skipped++;
            continue;
        }

        float given=z.waterNeeded;

        if(z.rainfall>=70)
            given*=0.30;
        else if(z.moisture>=70)
            given*=0.25;
        else if(z.moisture>=55)
            given*=0.60;

        bool partialWater=false;

        if(given>tankWater)
        {
            given=tankWater;
            partialWater=true;
        }

        if(given<=0)
        {
            skipped++;
            continue;
        }

        float oldNeed=z.waterNeeded;

        tankWater-=given;

        float increase=
            (given/oldNeed)*30;

        z.moisture+=increase;

        if(z.moisture>100)
            z.moisture=100;

        z.waterNeeded-=given;

        if(z.waterNeeded<0)
            z.waterNeeded=0;

        cout << "\nDecision: IRRIGATE";

        cout << "\nRoute: "
             << getPath(zoneID,parent);

        cout << "\nPipe cost: "
             << distance[zoneID];

        cout << "\nWater given: "
             << fixed
             << setprecision(1)
             << given
             << " L";

        cout << "\nNew moisture: "
             << z.moisture
             << "%";

        cout << "\nRemaining water needed: "
             << z.waterNeeded
             << " L";

        cout << "\nPUMP ON -> VALVE OPEN -> Irrigation done (simulated)";

        if(partialWater)
        {
            cout << "\nWARNING: Partial irrigation.";
            partial++;
        }

        string record=
            "Zone "
            +to_string(z.id)
            +": "
            +to_string((int)given)
            +" L via "
            +getPath(zoneID,parent)
            +" (cost "
            +to_string(distance[zoneID])
            +")";

        history.push_back(record);

        irrigated++;

        if(tankWater<=0)
        {
            cout << "\nTank is now empty.\n";
            break;
        }
    }

    cout << "\n====================================================\n";
    cout << "                IRRIGATION SUMMARY\n";
    cout << "====================================================\n";

    cout << "Irrigated zones : "
         << irrigated
         << endl;

    cout << "Skipped zones   : "
         << skipped
         << endl;

    cout << "Partial zones   : "
         << partial
         << endl;

    cout << "Water remaining : "
         << tankWater
         << " L\n";
}

void forceIrrigationDemo()
{
    cout << "\n====================================================\n";
    cout << "             FORCED IRRIGATION DEMO\n";
    cout << "====================================================\n";

    for(int i=0;i<zones.size();i++)
    {
        zones[i].moisture=randomNumber(20,45);
        zones[i].temperature=randomNumber(30,40);
        zones[i].rainfall=randomNumber(0,30);
        zones[i].waterNeeded=randomNumber(100,250);
        zones[i].priority=calculatePriority(zones[i]);
    }

    cout << "\nAll zones have been given dry conditions.\n";
    cout << "Running irrigation now...\n";

    runIrrigation();
}

void showHistory()
{
    cout << "\n====================================================\n";
    cout << "                 IRRIGATION HISTORY\n";
    cout << "====================================================\n";

    if(history.empty())
    {
        cout << "No irrigation records yet.\n";
        return;
    }

    for(int i=0;i<history.size();i++)
    {
        cout << i+1
             << ". "
             << history[i]
             << endl;
    }
}

void addWater()
{
    float water;

    cout << "\nLitres to add: ";
    cin >> water;

    if(water<=0)
    {
        cout << "Enter a positive amount.\n";
        return;
    }

    tankWater+=water;

    cout << "Water added successfully.\n";

    cout << "Tank now has "
         << tankWater
         << " L\n";
}
