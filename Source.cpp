// Given a set S of  all the possible combinations of binary strings of length n
// find a maximum size subset S' of S with the property that
// the Hamming distance between every pair of strings in S' is at least d
#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>
using namespace std;

// Function to calculate the Hamming distance between two binaries
int hamming_distance(uint32_t a, uint32_t b)
{
    int count = 0;
    for (int i = 0; i < 32; i++)
    {
        if ((a & 1) != (b & 1))
            count++;
        a >>= 1;
        b >>= 1;
    }
    return count;
}

// Function to find the maximum size subset S' of S with the property that
// the Hamming distance between every pair of strings in S' is at least d
vector<uint32_t> brute_force(vector<uint32_t> S, int d)
{
    vector<uint32_t> S_prime;
    for (int i = 0; i < S.size(); i++)
    {
        vector<uint32_t> temp;
        temp.push_back(S[i]);
        for (int j = i + 1; j < S.size(); j++)
        {
            if (hamming_distance(S[i], S[j]) >= d) {
                // check that the hamming distance between S[j] and every string in temp is at least d
                bool flag = true;
                for (int k = 0; k < temp.size(); k++)
                {
                    if (hamming_distance(S[j], temp[k]) < d)
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                    temp.push_back(S[j]);
            }
        }
        if (temp.size() > S_prime.size())
            S_prime = temp;
    }
    return S_prime;
}

// implement the Bron�Kerbosch algorithm
void findMaximalCliqueBronKerboschSimple(vector<uint32_t> R, vector<uint32_t> P, vector<uint32_t> X, const uint32_t d, vector<vector<uint32_t> >& maximalCliques);

uint32_t bron_kerbosch(const uint32_t d, std::vector<uint32_t> P)
{
    vector<uint32_t> R;
    vector<uint32_t> X;
    vector<vector<uint32_t>> maximalCliques;

    findMaximalCliqueBronKerboschSimple(R, P, X, d, maximalCliques);

    uint32_t max = 0;
    for (uint32_t i = 0; i < maximalCliques.size(); i++)
    {
        if (maximalCliques[i].size() > max)
        {
            max = maximalCliques[i].size();
        }
    }

    return max;
}

void findMaximalCliqueBronKerboschSimple(vector<uint32_t> R, vector<uint32_t> P, vector<uint32_t> X, const uint32_t d, vector<vector<uint32_t> >& maximalCliques)
{
    if (P.empty() && X.empty())
    {
        maximalCliques.push_back(R);
    }
    else
    {
        for (uint32_t i = 0; i < P.size(); i++)
        {
            vector<uint32_t> newR = R;
            newR.push_back(P[i]);
            vector<uint32_t> newP;
            vector<uint32_t> newX;
            for (uint32_t j = 0; j < P.size(); j++)
            {
                if (hamming_distance(P[i], P[j]) >= d)
                {
                    newP.push_back(P[j]);
                }
            }
            for (uint32_t j = 0; j < X.size(); j++)
            {
                if (hamming_distance(P[i], X[j]) >= d)
                {
                    newX.push_back(X[j]);
                }
            }
            findMaximalCliqueBronKerboschSimple(newR, newP, newX, d, maximalCliques);
            for (uint32_t j = 0; j < P.size(); j++)
            {
                if (P[i] == P[j])
                {
                    P.erase(P.begin() + j);
                    break;
                }
            }
            X.push_back(P[i]);
        }
    }
}

int main()
{
    int n, d, m;
    cout << "Enter the length of the binary strings: ";
    cin >> n;
    cout << "Enter the Hamming distance: ";
    cin >> d;
    cout << "Enter 1 for brute_force 2 for Bron�Kerbosch algorithm: ";

    cin >> m;

    vector<uint32_t> S;
    for (int i = 0; i < pow(2, n); i++)
    {
        S.push_back(i);
    }

    vector<uint32_t> R;
    vector<uint32_t> X;
    if (m == 1)
    {
        auto start = chrono::high_resolution_clock::now();
        vector<uint32_t> S_prime = brute_force(S, d);
        cout << "n=" << n << " d=" << d << " A(n,d)=" << S_prime.size() << endl;
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Time taken by function: " << duration.count() / 1000000.0 << " seconds" << endl;

    }

    else if (m == 2)
    {
        auto start = chrono::high_resolution_clock::now();

        uint32_t S_prime = bron_kerbosch(d, S);
        cout << "n=" << n << " d=" << d << " A(n,d)=" << S_prime << endl;
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << "Time taken by function: " << duration.count() / 1000000.0 << " seconds" << endl;


    }

    else
    {
        cout << "Invalid method" << endl;
    }
    return 0;
}