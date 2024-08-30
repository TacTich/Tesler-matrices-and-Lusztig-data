#include <bits/stdc++.h>
using namespace std;
long long m[1000][1000];
long long m0[1000][1000];

// Inputs the size of the matrix, the number of random steps, the number of overall trials, and the hook sum. In this algorithm, each random step allows the matrix to go down a covering or stay (we start with the maximal element). Outputs the probability distribution over all ranks, other related data and the average step efficiency (a step that goes down is effective and we count until a minimum element is reached)

int main() 
{
    srand((unsigned)time(0)); 
    // the mat size
    long long s;
    cin >> s;
    // num of steps
    long long k;
    cin >> k;
    // num of tries
    // long long n;
    // cin >> n;
    // the matrix

    // num of trials
    float t;
    cin >> t;

    // hook sum
    long long hookSum = 0;
    // max sum
    long long maxSum = 0;

    for (long long i = 1 ; i<= s ; i++)
        {
            for (long long j = 1 ; j <= s ; j++)
            {
                m0[i][j] = 0;
            }
        }

    for (long long i = 1; i <= s; i++)
    {
        int x;
        cin >> x;
        if (i == 1)
        {
            m0[i+1][i] = x;
        } else if (i == s)
        {
            m0[i][i] = m0[i][i-1] + x;
        } else 
        {
            m0[i+1][i] = m0[i][i-1] + x;
        }

        hookSum += x;
        maxSum += (s-i+1)*x;
        
    }


    // rank matrix
    float rankMatrix[maxSum + 1];
    for (int g = 0; g <= maxSum; g++) {
        rankMatrix[g] = 0;
    }

    float sumStepEfficiency = 0;

    for (long long f = 0; f < t; f++) {
        long long finalSum = 0;
        long long currentRank = 0;

    
    long long a_x, a_y, b_x, b_y;
    // cout << a_x << " " << a_y << '\n';
    long long tr = 0;

        for (long long i = 1 ; i<= s ; i++)
        {
            for (long long j = 1 ; j <= s ; j++)
            {
                m[i][j] = m0[i][j];
            }
        }

    bool reachedTheEnd = false;

    for (long long i_ = 1 ; i_<= k ; i_++)
    {
        long long currentSum = 0;
        
        for (long long i = 1; i <= s; i++)
            {
                for (long long j = 1; j < i ; j ++)
                {
                }
                for (long long j = i; j <= s ; j ++)
                {
                    currentSum += m[j][i];
                }
            }
        
        if (currentSum == hookSum)
        {
            reachedTheEnd = true;
        }
        
        // first number generator
        a_y = ( rand() % (s+1) ) + 1;
        // cout << "a_y = " << a_y << '\n';
        if ( a_y == (s+1) )
        {
            a_x = ( rand() % s) + 1;
            a_y = a_x;
        }
        else
        {
            a_x = ( rand() % s ) + 1;
            if (a_y > a_x)
            {
                swap(a_y, a_x);
            }
        }
        if (a_x == a_y)
        {
            b_x = ( rand() % (s-1) ) + 1;
            if (b_x >= a_x)
            {
                b_x++;
            }
            b_y = b_x;
            if ( m [ max(a_x,b_x) ] [ min(a_y,b_y) ] == 0 )
            {
                if (reachedTheEnd == false)
                {
                    tr++;
                }
                continue;
            }
            if ( m [ max(a_x,b_x) ] [ max(a_y,b_y) ] == 0 )
            {
                if (reachedTheEnd == false)
                    {
                        tr++;
                    }
                continue;
            }
            m[ min(a_x,b_x) ] [ min(a_y,b_y) ]++;
            m[ max(a_x,b_x) ] [ min(a_y,b_y) ]--;
            m[ max(a_x,b_x) ] [ max(a_y,b_y) ]--;
            continue;
        }
        if (a_x == a_y)
        {
            continue;
        }

        b_y = ( rand() % (s-2) ) + 1;
        if (b_y >= a_y)
        {
            b_y++;
        }
        if (b_y >= a_x)
        {
            b_y++;
        }

        long long q = min(min(a_x,a_y),b_y);
        long long t = max(max(a_x,a_y),b_y);
        long long r = a_x + a_y + b_y - q - t;

        if ( m[r][q] == 0 )
        {
            if (reachedTheEnd == false)
                {
                    tr++;
                }
            continue;
        }
        if ( m[t][r] == 0 )
        {
            if (reachedTheEnd == false)
                {
                    tr++;
                }
            continue;
        }

        m[t][r] --;
        m[r][q] --;
        m[t][q] ++;
        
        continue;
        
    }

        for (long long i = 1; i <= s; i++)
            {
                for (long long j = 1; j < i ; j ++)
                {
                }
                for (long long j = i; j <= s ; j ++)
                {
                    finalSum += m[j][i];
                }
            }

    long long realSteps = maxSum - finalSum;
        
    float stepEfficiency = (float)realSteps/(float)(realSteps + tr);
    sumStepEfficiency += stepEfficiency;

    currentRank = finalSum - hookSum + 1;
    rankMatrix[currentRank]++;

    }

    // average rank
    float averageRank = 0;

    float averageStepEfficiency = sumStepEfficiency/t;

    for (int h = 1; h <= (maxSum - hookSum + 1); h++){
        cout << h << " " << rankMatrix[h]/t << endl;
        averageRank += h * (rankMatrix[h]/t);
    }
    cout << "Average rank: " << averageRank << endl;
    cout << "Average rank ratio: " << (averageRank - 1)/(maxSum - hookSum) << endl;
    cout << "Average step efficiency: " << averageStepEfficiency << endl;
    
}