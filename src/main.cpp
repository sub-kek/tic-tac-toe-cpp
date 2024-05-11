#include <cstdio>

#define FIELD_SIZE 3

void print_matrix(int matrix[FIELD_SIZE][FIELD_SIZE]);
int main_loop();
char* get_walker_name(int _walker);
int get_winner(int matrix[FIELD_SIZE][FIELD_SIZE]);
bool is_array_equal(const int *a, const int *b, int lenght);
char get_walker_symbol(int walker);

enum LOOP_EXIT_CODES {
    SUCCESS = 0,
    REACHED_MAX_CYCLES = 1,
};

int matrix[FIELD_SIZE][FIELD_SIZE];

const int win_combinations[8][3] = {
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},
    {0, 3, 6},
    {1, 4, 7},
    {2, 5, 8},
    {0, 4, 8},
    {2, 4, 6},
};

int main() {
    for (int row = 0; row < FIELD_SIZE; row++) {
        for (int col = 0; col < FIELD_SIZE; col++) {
            matrix[row][col] = 0;
        }
    }

    int loopExitCode = main_loop();

    printf("\nLoop exit code: %d\n", loopExitCode);

    return loopExitCode;
}

void print_matrix(int matrix[FIELD_SIZE][FIELD_SIZE]) {
    int i = 0;
    
    for (int row = 0; row < FIELD_SIZE; row++) {
        for (int hor = 0; hor < FIELD_SIZE; hor++) {
            printf("----");
        }

        printf("-\n");
        
        for (int col = 0; col < FIELD_SIZE; col++) {
            i++;
            
            int dot = matrix[row][col];

            if (dot == 0) printf("| %d ", i);
            else printf("| %c ", get_walker_symbol(dot));
        }
        printf("|\n");
    }

    for (int hor = 0; hor < FIELD_SIZE; hor++) {
        printf("----");
    }

    printf("-\n");
}

int main_loop() {
    int cycles = 0;
    int walker = 1;
    
    while (true) {
        print_matrix(matrix);
        int winner = get_winner(matrix);
        if (winner != 0 || cycles >= FIELD_SIZE*FIELD_SIZE) {
            printf("\nWinned player %s\n", get_walker_name(winner));
            return LOOP_EXIT_CODES::SUCCESS;
        }

        while (true) {
            printf("Walk of player %s: ", get_walker_name(walker));
            int walkIndex;
            scanf("%d", &walkIndex);

            if (walkIndex > FIELD_SIZE*FIELD_SIZE) {
                printf("Cell not on Field!\n");
                continue;
            }
            
            walkIndex--;
        
            int walkRow = walkIndex / FIELD_SIZE;
            int walkCol = walkIndex - walkRow * FIELD_SIZE;

            if (matrix[walkRow][walkCol] != 0) {
                printf("Cell busy!\n");
                continue;
            }
        
            matrix[walkRow][walkCol] = walker;
            break;
        }

        // Сменить игрока
        if (walker == 1) walker = 2;
        else if (walker == 2) walker = 1;

        cycles++;
    }

    return LOOP_EXIT_CODES::SUCCESS;
}

char* get_walker_name(int _walker) {
    switch (_walker)
    {
    case 0:
        return "Neutral";
        break;
    case 1:
        return "Crosses";
        break;
    
    case 2:
        return "Zeros";
        break;
    }
}

int get_winner(int matrix[FIELD_SIZE][FIELD_SIZE]) {
    for (int comb = 0; comb < sizeof(win_combinations)/sizeof(*win_combinations); comb++) {
        int winner[3] = { 0, 0, 0 };

        for (int index = 0; index < sizeof(win_combinations[comb])/sizeof(*win_combinations[comb]); index++) {
            int row = win_combinations[comb][index] / FIELD_SIZE;
            int col = win_combinations[comb][index] - row * FIELD_SIZE;

            winner[index] = matrix[row][col];
        }

        int cross[3] = {1, 1, 1};
        int zeros[3] = {2, 2, 2};
        
        if (is_array_equal(winner, cross, 3)) return 1;
        else if (is_array_equal(winner, zeros, 3)) return 2;
    }

    return 0;
}

char get_walker_symbol(int walker) {
    switch (walker)
    {
    case 1:
        return 'X';
        break;

    case 2:
        return 'O';
    }
}

bool is_array_equal(const int *a, const int *b, int lenght) {
    for (int i = 0; i < lenght; ++i){
        if(a[i] != b[i]){ return false; }
    }
    return true;
}
