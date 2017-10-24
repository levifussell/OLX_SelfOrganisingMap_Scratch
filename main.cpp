#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <vector>

int parseQuery(int***** dt, std::string* query);
void parseSale(int***** dt, std::string* sale);
void splitTwoNumbers(std::string str, int &val1, int &val2);
void incrementDecisionTree(int***** dt,
        int d, int p, int c, int s, int r);
int queryDecisionTree(int***** dt,
        int d_start, int d_end, int p, int c, int s, int r);

//S:
// d: 1->100
const int COUNT_DAYS = 100;
// p_id: 1->10
const int COUNT_P = 11;
// c_id: 0, 1->4 (0 == undefined category)
const int COUNT_C = 5;
// s_id: 1->7
const int COUNT_S = 7;
// r_id: 0, 1->25 (0 == undefined region)
const int COUNT_R = 26;

//Q:
// d_start: 1->100
// d_end: none, 1->100 (none == could be missing)
// p_id: 1->10
// c_id: 0, 1->4 (0 == undefined category)
// s_id: 1->7
// r_id: 1->25 (0 == undefined region)

int main()
{
    //data is in the format of a 5D matrix
    //std::vector<std::vector<std::vector<int> > > data(COUNT_DAYS);
    int***** dt = new int****[COUNT_DAYS];
    for(int d = 0; d < COUNT_DAYS; ++d)
    {
        dt[d] = new int***[COUNT_P];
        for(int p = 0; p < COUNT_P; ++p)
        {
            dt[d][p] = new int**[COUNT_C];
            for(int c = 0; c < COUNT_C; ++c)
            {
                dt[d][p][c] = new int*[COUNT_S];
                for(int s = 0; s < COUNT_S; ++s)
                {
                    dt[d][p][c][s] = new int[COUNT_R];
                    for(int r = 0; r < COUNT_R; ++r)
                    {
                        dt[d][p][c][s][r] = 0;
                    }
                }
            }
        }
    }

    std::string lineCountStr;
    std::cin >> lineCountStr;
    int lineCount = atoi(lineCountStr.c_str());

    //read the lines out:
    const int LINE_INPUT_SIZE = 4;
    for(int i = 0; i < lineCount; ++i)
    {
        //each line consists of 4 inputs
        std::string line[LINE_INPUT_SIZE];
        for(int j = 0; j < LINE_INPUT_SIZE; ++j)
        {
            std::cin >> line[j];
        }

        if(line[0] == "Q")
        {
            int itemCount = parseQuery(dt, line);
            std::cout << itemCount << "\n";
        }
        else if(line[0] == "S")
            parseSale(dt, line);
    }

    //clear memory
    for(int d = 0; d < COUNT_DAYS; ++d)
    {
        for(int p = 0; p < COUNT_P; ++p)
        {
            for(int c = 0; c < COUNT_C; ++c)
            {
                for(int s = 0; s < COUNT_S; ++s)
                {
                    delete[] dt[d][p][c][s];
                }
                delete[] dt[d][p][c];
            }
            delete[] dt[d][p];
        }
        delete[] dt[d];
    }
    delete[] dt;

    return 0;
}

int parseQuery(int***** dt, std::string* query)
{
    std::cout << "PARSING QUERY\n";

    int d_start, d_end;
    splitTwoNumbers(query[1], d_start, d_end);

    //parse product and category
    int p_id, c_id;
    splitTwoNumbers(query[2], p_id, c_id);

    //parse state and region
    int s_id, r_id;
    splitTwoNumbers(query[3], s_id, r_id);

    std::cout << "DATA: " << "\n";
    std::cout << "d: " << d_start << "->"  << d_end << ", p_id: " << p_id << ", c_id: " << c_id << ", s_id: " << s_id << ", r_id: " << r_id << "\n";
    d_end = d_end == -1 ? d_start : d_end;
    int itemCount = queryDecisionTree(dt, d_start - 1, d_end, p_id - 1, c_id, s_id - 1, r_id);

    return itemCount;
}

void parseSale(int***** dt, std::string* sale)
{
    std::cout<< "PARSING SALE\n";

    // parse day count
    int dayCount = atoi(sale[1].c_str());

    //parse product and category
    int p_id, c_id;
    splitTwoNumbers(sale[2], p_id, c_id);

    //parse state and region
    int s_id, r_id;
    splitTwoNumbers(sale[3], s_id, r_id);

    //std::cout << "DATA: " << "\n";
    //std::cout << "d: " << dayCount << ", p_id: " << p_id << ", c_id: " << c_id << ", s_id: " << s_id << ", r_id: " << r_id << "\n";

    //add to the decision tree
    // start index from 0 (except those w/ undefined category)
    incrementDecisionTree(dt, dayCount - 1, p_id - 1, c_id, s_id - 1, r_id);
}

void splitTwoNumbers(std::string str, int &val1, int &val2)
{
    std::stringstream ss;
    ss.str(str);
    std::string item;
    std::vector<std::string> val;
    while(std::getline(ss, item, '.'))
    {
        //*(result++) = item;
        val.push_back(item);
    }

    //the first value will always exist
    val1 = atoi(val[0].c_str());
    //the second value may not exist
    val2 = -1;
    if(val.size() > 1)
        val2 = atoi(val[1].c_str());
}

void incrementDecisionTree(int***** dt,
        int d, int p, int c, int s, int r)
{
    if(c != -1 && r != -1)
        dt[d][p][c][s][r] += 1;

    //increment the case where we count all categoried from
    // some region
    if(r != -1)
        dt[d][p][0][s][r] += 1;

    //increment the case where we count all regions from
    // some category
    if(c != -1)
        dt[d][p][c][s][0] += 1;

    //always update the undefined category (to keep track of cumulative
    // products)
    dt[d][p][0][s][0] += 1;
}

int queryDecisionTree(int***** dt,
        int d_start, int d_end, int p, int c, int s, int r)
{
    int itemCount = 0;
    int c_cat = c == -1 ? 0 : c;
    int r_cat = r == -1 ? 0 : r;

    int P_MAX = p + 1;
    if(p < 0)
    {
        p = 0;
        P_MAX = COUNT_P;
    }
    int S_MAX = s + 1;
    if(s < 0)
    {
        s = 0;
        S_MAX = COUNT_S;
    }

    for(int d = d_start; d < d_end; ++d)
    {
        for(int i = p; i < P_MAX; ++i)
        {
            for(int j = s; j < S_MAX; ++j)
            {
                itemCount += dt[d][i][c_cat][j][r_cat];
            }
        }
    }

    return itemCount;
}
