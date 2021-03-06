#include <iostream>
#include <cstdlib>

#define EXP_CNT 100000
#define NODE_CNT 13
#define MAX_WEIGHT 1000
#define MAX_STEP 100

#include "increasedDecimal.hpp"
#include "decreasedDecimal.hpp"
#include "orthoTransposition.hpp"
#include "lexiOrder.hpp"
#include "randomOrder.hpp"
#include "shuffledOrder.hpp"

int w[EXP_CNT][NODE_CNT][NODE_CNT];

inline void init() {
    for (int i = 0; i < EXP_CNT; i++)
        for (int j = 0; j < NODE_CNT; j++)
            for (int k = 0; k < NODE_CNT; k++)
                w[i][j][k] = rand() % (MAX_WEIGHT + 1);
}

inline double* tryout(void (*next_perm)(int[], int)) {
    double* res = new double[MAX_STEP + 1];
    int p[NODE_CNT];
    int s;
    for (int i = 0; i < EXP_CNT; i++) {
        for (int j = 0; j < NODE_CNT - 1; j++) p[j] = j;
        res[0] += s = MAX_WEIGHT * NODE_CNT;
        for (int step = 1; step <= MAX_STEP; step++) {
            int t = w[i][NODE_CNT - 1][p[0]] + w[i][p[NODE_CNT - 2]][NODE_CNT - 1];
            for (int j = 0; j < NODE_CNT - 2; j++) t += w[i][p[j]][p[j + 1]];
            s = (t < s ? t : s);
            res[step] += s;
            next_perm(p, NODE_CNT - 1);
        }
        // if (i % 1000 == 999) printf("%d / %d\n", i + 1, EXP_CNT);
    }

    for (int step = 0; step <= MAX_STEP; step++)
        res[step] /= double(EXP_CNT);
    return res;
}

#define PRINT_RESULT(func) \
    double* res_##func = tryout(func); \
    printf(#func","); \
    for (int i = 1; i <= MAX_STEP; i++) { \
        printf("%.3lf%s", res_##func[i], i==MAX_STEP?"":","); \
    } \
    puts("");

int main() {
    srand(114514);
    init();
    
    PRINT_RESULT(next_perm_shuffled);
    PRINT_RESULT(next_perm_random);
    PRINT_RESULT(next_perm_lexi);
    PRINT_RESULT(next_perm_increased);
    PRINT_RESULT(next_perm_decreased);
    PRINT_RESULT(next_perm_ortho);

    return 0;
}