#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Traveler
{
public:
    // auto sorted
    map<long, vector<long>> colorEnds;
    // num of balls
    long n = 0;
    vector<vector<long>> dp = { {0,0,0,0} };

    void ReadInput();
    void OutputColorEnds();
    void DP();
};

void Traveler::ReadInput()
{
    cin >> n;
    // N <= 2*10^5
    long ballPos, ballColor;
    for (long i = 0; i < n; i++)
    {
        cin >> ballPos >> ballColor;
        // we just need to find the leftand right end of each color
        // because the optimal solution must gurantee that
        // each color starts end ends at its two ends.
        // the third element is step length
        // because we have to collect them all
        if (colorEnds.count(ballColor) == 0)
        {
            colorEnds.insert({ ballColor, {ballPos, ballPos} });
        }
        else
        {
            vector<long> ends = colorEnds[ballColor];
            ends[0] = min(ends[0], ballPos);
            ends[1] = max(ends[1], ballPos);
            colorEnds[ballColor] = ends;
        }
    }
}

void Traveler::OutputColorEnds()
{
    map<long, vector<long>>::const_iterator it;
    for (it = colorEnds.begin(); it != colorEnds.end(); ++it) {
        cout << "Color: " << it->first << " left: " << it->second[0] << " right: " << it->second[1] << endl;
    }
}

void Traveler::DP()
{
    // for each color
    map<long, vector<long>>::const_iterator it;
    long i = 1;
    for (it = colorEnds.begin(); it != colorEnds.end(); ++it) {
        vector<long> currentDP = {0,0,0,0};
        // leftEnd of current color
        long leftEnd = it->second[0];
        // rightEnd of current color
        long rightEnd = it->second[1];
        // stepLen is collecting length
        long stepLen = rightEnd - leftEnd;
        
        // if we start from the left end
        // steps continuing from the left end of the last step
        long lNumSteps = dp[i - 1][0] + stepLen + abs(dp[i - 1][1] - rightEnd);
        // steps continuing from the right end of the last step
        long rNumSteps = dp[i - 1][2] + stepLen + abs(dp[i - 1][3] - rightEnd);
        currentDP[0] = min(lNumSteps, rNumSteps);
        // start from right so end at left
        currentDP[1] = leftEnd;

        // if we start from the right end
        // steps continuing from the left end of the last step
        lNumSteps = dp[i - 1][0] + stepLen + abs(dp[i - 1][1] - leftEnd);
        // steps continuing from the right end of the last step
        rNumSteps = dp[i - 1][2] + stepLen + abs(dp[i - 1][3] - leftEnd);
        currentDP[2] = min(lNumSteps, rNumSteps);
        // start from right so end at left
        currentDP[3] = rightEnd;
        // cout << currentDP[0] << " " << currentDP[1] << " " << currentDP[2] << " " << currentDP[3] << endl;
        dp.push_back(currentDP);
        i++;
    }

    vector<long> currentDP = { 0,0,0,0 };
    long leftEnd = 0;
    // rightEnd of current color
    long rightEnd = 0;
    // stepLen is collecting length
    long stepLen = rightEnd - leftEnd;

    // if we start from the left end
    // steps continuing from the left end of the last step
    long lNumSteps = dp[i - 1][0] + stepLen + abs(dp[i - 1][1] - rightEnd);
    // steps continuing from the right end of the last step
    long rNumSteps = dp[i - 1][2] + stepLen + abs(dp[i - 1][3] - rightEnd);
    currentDP[0] = min(lNumSteps, rNumSteps);
    // start from right so end at left
    currentDP[1] = leftEnd;

    // if we start from the right end
    // steps continuing from the left end of the last step
    lNumSteps = dp[i - 1][0] + stepLen + abs(dp[i - 1][1] - leftEnd);
    // steps continuing from the right end of the last step
    rNumSteps = dp[i - 1][2] + stepLen + abs(dp[i - 1][3] - leftEnd);
    currentDP[2] = min(lNumSteps, rNumSteps);
    // start from right so end at left
    currentDP[3] = rightEnd;

    dp.push_back(currentDP);
    i++;
    // cout << currentDP[0] << " " << currentDP[1] << " " << currentDP[2] << " " << currentDP[3] << endl;
    cout << dp[i-1][0] << endl;
}

int main()
{
    Traveler traveler;
    // # read input
    traveler.ReadInput();
    // traveler.OutputColorEnds();
    traveler.DP();
    return 0;
} 