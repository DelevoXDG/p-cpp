// Maksim Zdobnikau
// Kostkowy poker

// baca submit -f file.cpp -t 8 -l "C++ z obsluga plikow"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{

    int rounds = 0;

    //Players Info

    float roundsA = 0;
    float roundsB = 0;
    float roundsC = 0;
    float roundsD = 0;
    float roundsE = 0;

    float winsA = 0;
    float winsB = 0;
    float winsC = 0;
    float winsD = 0;
    float winsE = 0;

    float drawsA = 0;
    float drawsB = 0;
    float drawsC = 0;
    float drawsD = 0;
    float drawsE = 0;

    float losesA = 0;
    float losesB = 0;
    float losesC = 0;
    float losesD = 0;
    float losesE = 0;

    //Current Info
    int rCount = 0;
    char p1 = ' ';
    char p2 = ' ';

    int d11 = 0;
    int d12 = 0;
    int d13 = 0;
    int d14 = 0;

    int d21 = 0;
    int d22 = 0;
    int d23 = 0;
    int d24 = 0;

    int result1 = 0;
    int sum1 = 0;
    int sum2 = 0;
    int max1 = 0;
    int max12 = 0;
    int max2 = 0;
    int max22 = 0;
    int pairs = 0;
    int result2 = 0;
    int currentDie = 0;
    int outcome = 0;

    //GAME

    cin >> rounds;

    while (rCount < rounds)
    {

        //Match Info
        cin >> p1;
        cin >> d11;
        cin >> d12;
        cin >> d13;
        cin >> d14;

        cin >> p2;
        cin >> d21;
        cin >> d22;
        cin >> d23;
        cin >> d24;

        result1 = 0;
        result2 = 0;
        sum1 = 0;
        sum2 = 0;
        max1 = 0;
        max12 = 0;
        max2 = 0;
        max22 = 0;
        pairs = 0;
        currentDie = 0;
        outcome = 0;
        // 1 - p1 wins
        // 2 - draw
        // 3 - p2 wins

        //SECTION RESULTS: PLAYER 1
        pairs = 0;
        sum1 = d11 + d12 + d13 + d14;
        if ((d11 == d12) && (d11 == d13) && (d11 == d14))
        {
            result1 = 1; //Result - Quads
            max1 = d11;
        }
        else if ((d11 != d12) && (d11 != d13) && (d11 != d14) && (d12 != d13) && (d12 != d14) && (d13 != d14))
        {
            result1 = 2; //Result - Straight
        }
        else if ((d11 == d12 && d11 == d13) || (d11 == d12 && d11 == d14) || (d11 == d13 && d11 == d14) || (d12 == d13 && d12 == d14))
        {
            result1 = 4; //Result - Threes

            if ((d11 == d12 && d11 == d13) || (d11 == d12 && d11 == d14) || (d11 == d13 && d11 == d14))
                max1 = d11;
            else
                max1 = d12;
        }
        else if ((d11 == d12) || (d11 == d13) || (d11 == d14) || (d12 == d13) || (d12 == d14) || (d13 == d14))
        {
            currentDie = 0;
            pairs = 0;

            if (d11 == d12 || d11 == d13 || d11 == d14)
            {
                currentDie = d11;
                pairs++;
                if (currentDie > max1)
                    max1 = currentDie;
            }
            if (d12 == d13 || d12 == d14)
            {
                currentDie = d12;
                pairs++;
                if (currentDie > max1)
                    max1 = currentDie;
            }
            if (d13 == d14)
            {
                currentDie = d13;
                pairs++;
                if (currentDie > max1)
                    max1 = currentDie;
            }

            if (pairs == 1)
            {
                result1 = 5; //Result - One Pair
            }
            if (pairs == 2)
            {
                result1 = 3; //Result - Two Pair
            }
        }
        //RESULTS: PLAYER 1 - END
        pairs = 0;
        //SECTION RESULTS: PLAYER 2
        sum2 = d21 + d22 + d23 + d24;

        if ((d21 == d22) && (d21 == d23) && (d21 == d24))
        {
            //Result - Quads
            result2 = 1;
            max2 = d21;
        }
        else if ((d21 != d22) && (d21 != d23) && (d21 != d24) && (d22 != d23) && (d22 != d24) && (d23 != d24))
        {
            //Result - Straight
            result2 = 2;
        }
        else if ((d21 == d22 && d21 == d23) || (d21 == d22 && d21 == d24) || (d21 == d23 && d21 == d24) || (d22 == d23 && d22 == d24))
        {
            //Result - Threes
            result2 = 4;
            if ((d21 == d22 && d21 == d23) || (d21 == d22 && d21 == d24) || (d21 == d23 && d21 == d24))
                max2 = d21;
            else
                max2 = d22;
        }
        else if ((d21 == d22) || (d21 == d23) || (d21 == d24) || (d22 == d23) || (d22 == d24) || (d23 == d24))
        {
            //Result - Pairs
            currentDie = 0;
            pairs = 0;
            if (d21 == d22 || d21 == d23 || d21 == d24)
            {
                currentDie = d21;
                pairs++;
                if (currentDie > max2)
                    max2 = currentDie;
            }
            if (d22 == d23 || d22 == d24)
            {
                currentDie = d22;
                pairs++;
                if (currentDie > max2)
                    max2 = currentDie;
            }
            if (d23 == d24)
            {
                currentDie = d23;
                pairs++;
                if (currentDie > max2)
                    max2 = currentDie;
            }

            if (pairs == 1)
            {
                result2 = 5; //Result - One Pair
            }
            if (pairs == 2)
            {
                result2 = 3; //Result - Two Pair
            }
        }
        //RESULTS: PLAYER 2 - END

        //SECTION DETERMINE ROUND OUTCOME

        if (result1 > result2)
            outcome = 3;
        else if (result1 < result2)
            outcome = 1;
        else if (result1 == result2)
        {
            if (result1 == 1)
                outcome = 2;
            else if (result1 == 2)
                outcome = 2;
            else if (result1 == 3)
            {
                if (max1 > max2)
                    outcome = 1;
                else if (max1 < max2)
                    outcome = 3;
                else if (sum1 > sum2)
                    outcome = 1;
                else if (sum1 < sum2)
                    outcome = 3;
                else
                    outcome = 2;
            }
            else if (result1 == 4)
            {
                if (max1 > max2)
                    outcome = 1;
                else if (max1 < max2)
                    outcome = 3;
                else if (sum1 > sum2)
                    outcome = 1;
                else if (sum1 < sum2)
                    outcome = 3;
                else
                    outcome = 2;
            }
            else if (result1 == 5)
            {
                if (max1 > max2)
                    outcome = 1;
                else if (max1 < max2)
                    outcome = 3;
                else if (sum1 > sum2)
                    outcome = 1;
                else if (sum1 < sum2)
                    outcome = 3;
                else
                    outcome = 2;
            }
            else
            {
                if (sum1 > sum2)
                    outcome = 1;
                else if (sum1 < sum2)
                    outcome = 3;
                else
                    outcome = 2;
            }
        }
        else
        {
            if (sum1 > sum2)
                outcome = 1;
            else if (sum1 < sum2)
                outcome = 3;
            else
                outcome = 2;
        }

        //Rounds played Count
        if (p1 == 'a')
            roundsA++;
        if (p1 == 'b')
            roundsB++;
        if (p1 == 'c')
            roundsC++;
        if (p1 == 'd')
            roundsD++;
        if (p1 == 'e')
            roundsE++;
        //player2
        if (p2 == 'a')
            roundsA++;
        if (p2 == 'b')
            roundsB++;
        if (p2 == 'c')
            roundsC++;
        if (p2 == 'd')
            roundsD++;
        if (p2 == 'e')
            roundsE++;

        //Outcome Count

        if (outcome == 2)
        {
            //player1
            if (p1 == 'a')
                drawsA++;
            if (p1 == 'b')
                drawsB++;
            if (p1 == 'c')
                drawsC++;
            if (p1 == 'd')
                drawsD++;
            if (p1 == 'e')
                drawsE++;
            //player2
            if (p2 == 'a')
                drawsA++;
            if (p2 == 'b')
                drawsB++;
            if (p2 == 'c')
                drawsC++;
            if (p2 == 'd')
                drawsD++;
            if (p2 == 'e')
                drawsE++;
        }

        if (outcome == 1)
        {
            //player1
            if (p1 == 'a')
                winsA++;
            if (p1 == 'b')
                winsB++;
            if (p1 == 'c')
                winsC++;
            if (p1 == 'd')
                winsD++;
            if (p1 == 'e')
                winsE++;
            //player2
            if (p2 == 'a')
                losesA++;
            if (p2 == 'b')
                losesB++;
            if (p2 == 'c')
                losesC++;
            if (p2 == 'd')
                losesD++;
            if (p2 == 'e')
                losesE++;
        }

        if (outcome == 3)
        {
            //player1
            if (p1 == 'a')
                losesA++;
            if (p1 == 'b')
                losesB++;
            if (p1 == 'c')
                losesC++;
            if (p1 == 'd')
                losesD++;
            if (p1 == 'e')
                losesE++;
            //player2
            if (p2 == 'a')
                winsA++;
            if (p2 == 'b')
                winsB++;
            if (p2 == 'c')
                winsC++;
            if (p2 == 'd')
                winsD++;
            if (p2 == 'e')
                winsE++;
        }

        //SECTION SHOW ROUND RESULTS

        //NEXT ROUND
        rCount++;
    }
    //SECTION DISPLAY RESULTS PER PLAYER

    //A
    if (roundsA > 0)
    {
        cout << "gracz a" << endl;
        if (winsA > 0)
            cout << "    wygrane: " << (winsA / roundsA) * 100 << "%" << endl;
        if (drawsA > 0)
            cout << "    remisy: " << (drawsA / roundsA) * 100 << "%" << endl;
        if (losesA > 0)
            cout << "    przegrane: " << (losesA / roundsA) * 100 << "%" << endl;
        cout << endl;
    }
    //B
    if (roundsB > 0)
    {
        cout << "gracz b" << endl;
        if (winsB > 0)
            cout << "    wygrane: " << (winsB / roundsB) * 100 << "%" << endl;
        if (drawsB > 0)
            cout << "    remisy: " << (drawsB / roundsB) * 100 << "%" << endl;
        if (losesB > 0)
            cout << "    przegrane: " << (losesB / roundsB) * 100 << "%" << endl;
        cout << endl;
    }
    //C
    if (roundsC > 0)
    {
        cout << "gracz c" << endl;
        if (winsC > 0)
            cout << "    wygrane: " << (winsC / roundsC) * 100 << "%" << endl;
        if (drawsC > 0)
            cout << "    remisy: " << (drawsC / roundsC) * 100 << "%" << endl;
        if (losesC > 0)
            cout << "    przegrane: " << (losesC / roundsC) * 100 << "%" << endl;
        cout << endl;
    }
    //D
    if (roundsD > 0)
    {
        cout << "gracz d" << endl;
        if (winsD > 0)
            cout << "    wygrane: " << (winsD / roundsD) * 100 << "%" << endl;
        if (drawsD > 0)
            cout << "    remisy: " << (drawsD / roundsD) * 100 << "%" << endl;
        if (losesD > 0)
            cout << "    przegrane: " << (losesD / roundsD) * 100 << "%" << endl;
        cout << endl;
    }
    //E
    if (roundsE > 0)
    {
        cout << "gracz e" << endl;
        if (winsE > 0)
            cout << "    wygrane: " << (winsE / roundsE) * 100 << "%" << endl;
        if (drawsE > 0)
            cout << "    remisy: " << (drawsE / roundsE) * 100 << "%" << endl;
        if (losesE > 0)
            cout << "    przegrane: " << (losesE / roundsE) * 100 << "%" << endl;
        cout << endl;
    }

    return 0;
}