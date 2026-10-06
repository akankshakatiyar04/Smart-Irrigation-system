#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>
#include <cstdlib>
using namespace std;

const int TOTAL_ZONES=100;
const int TOTAL_NODES=101;

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

int randomNumber(int,int);

string nodeName(int node)
{
    if(node==0)
        return "Tank";

    return "Zone"+to_string(node);
}

void addPipe(int a,int b,int distance)
{
    for(int i=0;i<graph[a].size();i++)
    {
        if(graph[a][i].first==b)
        {
            graph[a][i].second=distance;

            for(int j=0;j<graph[b].size();j++)
            {
                if(graph[b][j].first==a)
                {
                    graph[b][j].second=distance;
                    return;
                }
            }
        }
    }

    graph[a].push_back(
        make_pair(b,distance)
    );

    graph[b].push_back(
        make_pair(a,distance)
    );
}

bool removePipe(int a,int b)
{
    bool removed=false;

    for(int i=0;i<graph[a].size();i++)
    {
        if(graph[a][i].first==b)
        {
            graph[a].erase(
                graph[a].begin()+i
            );

            removed=true;
            break;
        }
    }

    for(int i=0;i<graph[b].size();i++)
    {
        if(graph[b][i].first==a)
        {
            graph[b].erase(
                graph[b].begin()+i
            );

            break;
        }
    }

    return removed;
}

void showNetwork()
{
    cout << "\n====================================================\n";
    cout << "                 WATER PIPE NETWORK\n";
    cout << "====================================================\n";

    for(int i=0;i<TOTAL_NODES;i++)
    {
        cout << nodeName(i)
             << " -> ";

        if(graph[i].empty())
        {
            cout << "No pipes";
        }
        else
        {
            for(int j=0;j<graph[i].size();j++)
            {
                cout << nodeName(
                            graph[i][j].first
                        )
                     << "("
                     << graph[i][j].second
                     << ")";

                if(j<graph[i].size()-1)
                    cout << "  ";
            }
        }

        cout << endl;
    }
}

void dijkstra(
    int source,
    vector<int>& distance,
    vector<int>& parent)
{
    distance.assign(
        TOTAL_NODES,
        INT_MAX
    );

    parent.assign(
        TOTAL_NODES,
        -1
    );

    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    distance[source]=0;

    pq.push(
        make_pair(
            0,
            source
        )
    );

    while(!pq.empty())
    {
        int currentDistance=
            pq.top().first;

        int currentNode=
            pq.top().second;

        pq.pop();

        if(currentDistance>
           distance[currentNode])
        {
            continue;
        }

        for(int i=0;
            i<graph[currentNode].size();
            i++)
        {
            int nextNode=
                graph[currentNode][i].first;

            int pipeDistance=
                graph[currentNode][i].second;

            int newDistance=
                currentDistance+
                pipeDistance;

            if(newDistance<
               distance[nextNode])
            {
                distance[nextNode]=
                    newDistance;

                parent[nextNode]=
                    currentNode;

                pq.push(
                    make_pair(
                        newDistance,
                        nextNode
                    )
                );
            }
        }
    }
}

string getPath(
    int target,
    vector<int>& parent)
{
    vector<int> path;

    int current=target;

    while(current!=-1)
    {
        path.push_back(current);
        current=parent[current];
    }

    string result="";

    for(int i=path.size()-1;
        i>=0;
        i--)
    {
        result+=nodeName(path[i]);

        if(i!=0)
            result+=" -> ";
    }

    return result;
}

void changePipe()
{
    int choice;
    int a;
    int b;
    int distance;

    cout << "\n1. Add / Update a pipe\n";
    cout << "2. Remove a pipe\n";
    cout << "Choice: ";

    cin >> choice;

    cout << "First node (0 = Tank, 1-100 = Zones): ";
    cin >> a;

    cout << "Second node: ";
    cin >> b;

    if(a<0 ||
       a>=TOTAL_NODES ||
       b<0 ||
       b>=TOTAL_NODES ||
       a==b)
    {
        cout << "Invalid nodes!\n";
        return;
    }

    if(choice==1)
    {
        cout << "Distance / cost: ";
        cin >> distance;

        if(distance<=0)
        {
            cout << "Distance must be positive.\n";
            return;
        }

        addPipe(a,b,distance);

        cout << "Pipe saved.\n";
    }
    else if(choice==2)
    {
        if(removePipe(a,b))
            cout << "Pipe removed.\n";
        else
            cout << "Pipe not found.\n";
    }
    else
    {
        cout << "Invalid choice.\n";
    }
}

void setupFarm()
{
    string crops[]=
    {
        "Wheat",
        "Rice",
        "Maize",
        "Sugarcane",
        "Cotton"
    };

    for(int i=1;
        i<=TOTAL_ZONES;
        i++)
    {
        Zone z;

        z.id=i;

        z.crop=
            crops[(i-1)%5];

        z.moisture=
            randomNumber(30,65);

        z.temperature=
            randomNumber(20,40);

        z.rainfall=
            randomNumber(20,65);

        z.waterNeeded=
            randomNumber(100,400);

        z.priority=0;

        zones.push_back(z);
    }

    graph.resize(TOTAL_NODES);

    addPipe(0,1,10);

    for(int i=1;
        i<TOTAL_ZONES;
        i++)
    {
        addPipe(
            i,
            i+1,
            randomNumber(5,15)
        );
    }

    for(int i=1;
        i<=TOTAL_ZONES-5;
        i+=5)
    {
        addPipe(
            i,
            i+5,
            randomNumber(5,15)
        );
    }

    for(int i=1;
        i<=TOTAL_ZONES-10;
        i+=10)
    {
        addPipe(
            i,
            i+10,
            randomNumber(10,20)
        );
    }
}
