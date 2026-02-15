#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;

static inline int idx(int r, int c, int N)
{
    return r * N + c;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        int N, A, B;
        cin >> N >> A >> B;

        vector<string> grid(N);
        for (int i = 0; i < N; i++)
        {
            cin >> grid[i];
        }

        vector<bool> usedFirst(N * N, false), remain(N * N, false);

        bool impossible = false;

        for (int r = 0; r < N && !impossible; r++)
        {
            for (int c = 0; c < N && !impossible; c++)
            {
                if (grid[r][c] == 'B')
                {
                    if (r < B || c < A)
                    {
                        impossible = true;
                        break;
                    }
                    int p = idx(r - B, c - A, N), q = idx(r, c, N);
                    if (remain[p])
                    {
                        impossible = true;
                        break;
                    }
                    usedFirst[q] = true;
                    usedFirst[p] = true;
                    remain[p] = true;
                }
            }
        }
        if (impossible)
        {
            cout << -1 << "\n";
            continue;
        }

        for (int r = 0; r < N && !impossible; r++)
        {
            for (int c = 0; c < N && !impossible; c++)
            {
                if (grid[r][c] == 'W')
                {
                    if (usedFirst[idx(r, c, N)])
                    {
                        impossible = true;
                        break;
                    }
                    if (r >= B && c >= A)
                    {
                        int p = idx(r - B, c - A, N);
                        if (remain[p])
                        {
                            impossible = true;
                            break;
                        }
                    }
                }
            }
        }
        if (impossible)
        {
            cout << -1 << "\n";
            continue;
        }

        for (int r = 0; r < N; r++)
        {
            for (int c = 0; c < N; c++)
            {
                if (grid[r][c] == 'G')
                {
                    int currentIdx = idx(r, c, N);

                    bool canUseSecond = false;
                    int rp = r - B, cp = c - A;
                    int cost2 = INT_MAX, pidx = -1;

                    if (rp >= 0 && cp >= 0)
                    {
                        pidx = idx(rp, cp, N);
                        if (!remain[pidx] && grid[rp][cp] != 'W')
                        {
                            cost2 = usedFirst[pidx] ? 0 : 1;
                            canUseSecond = true;
                        }
                    }
                    int cost1 = usedFirst[currentIdx] ? 0 : 1;

                    if (canUseSecond && cost2 < cost1)
                    {
                        if (!usedFirst[pidx])
                            usedFirst[pidx] = true;
                        remain[pidx] = true;
                    }
                    else
                    {
                        if (!usedFirst[currentIdx])
                            usedFirst[currentIdx] = true;
                    }
                }
            }
        }

        if (impossible)
        {
            cout << -1 << "\n";
        }
        else
        {
            long long answer = 0;
            for (bool f : usedFirst)
            {
                if (f)
                    ++answer;
            }
            cout << answer << "\n";
        }
    }
    return 0;
}