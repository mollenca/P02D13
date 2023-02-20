#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FIELD_WIDTH 80
#define FIELD_HEIGHT 25
#define MAX_GEN 200000

void render(int state[][FIELD_WIDTH]);
void init_state(int state[][FIELD_WIDTH]);
int change_state(int state[][FIELD_WIDTH], int next_state[][FIELD_WIDTH]);
void reset_state(int state[][FIELD_WIDTH]);
void copy_state(int state[][FIELD_WIDTH], int next_state[][FIELD_WIDTH]);
int check_coord(int max_coord, int coord);
int check_stability(int state[][FIELD_WIDTH], int next_state[][FIELD_WIDTH]);
void print_the_end();
void print_start_game();

int main() {
    int state[FIELD_HEIGHT][FIELD_WIDTH];
    int next_state[FIELD_HEIGHT][FIELD_WIDTH];
    int _gen = 0;
    double speed = 0.3;
    int is_stable = 0;

    print_start_game();

    scanf("%lf", &speed);

    speed = speed * 1000000;

    init_state(state);
    reset_state(next_state);
    render(state);
    usleep(speed * 3);

    while (_gen < MAX_GEN && !is_stable) {
        change_state(state, next_state);  // computing next state
        is_stable = check_stability(state, next_state);

        copy_state(state, next_state);  // set current state with next state

        reset_state(next_state);  // reset next_state for next filling

        render(state);  // render state

        _gen++;
        usleep(speed);  // time delay
    }
    print_the_end();

    return 0;
}

void render(int state[][FIELD_WIDTH]) {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            printf("%c", state[i][j] ? '+' : ' ');
        }
        if (i != FIELD_HEIGHT - 1) printf("\n");
    }
}

void init_state(int state[][FIELD_WIDTH]) {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            scanf("%d", &state[i][j]);
        }
    }
}

void reset_state(int state[][FIELD_WIDTH]) {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            state[i][j] = 0;
        }
    }
}

int change_state(int state[][FIELD_WIDTH], int next_state[][FIELD_WIDTH]) {
    int neibs = 0;
    int neib_i, neib_j;
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            next_state[i][j] = 0;

            for (int i_n = i - 1; i_n <= i + 1; i_n++) {
                for (int j_n = j - 1; j_n <= j + 1; j_n++) {
                    neib_i = check_coord(FIELD_HEIGHT, i_n);
                    neib_j = check_coord(FIELD_WIDTH, j_n);

                    neibs += state[neib_i][neib_j];
                }
            }

            if (!state[i][j] && neibs == 3) next_state[i][j] = 1;
            if (state[i][j] && (neibs == (2 + 1) || neibs == (3 + 1)))
                next_state[i][j] = 1;  // + 1 caused by calculating neibs with the checking cell

            neibs = 0;
        }
    }

    return 0;
}

void copy_state(int state[][FIELD_WIDTH], int next_state[][FIELD_WIDTH]) {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            state[i][j] = next_state[i][j];
        }
    }
}

int check_coord(int max_coord, int coord) {
    int new_coord = coord;
    if (coord >= max_coord) new_coord = 0;
    if (coord < 0) new_coord = max_coord - 1;

    return new_coord;
}

int check_stability(int state[][FIELD_WIDTH], int next_state[][FIELD_WIDTH]) {
    int is_stable = 1;

    for (int i = 0; is_stable && i < FIELD_HEIGHT; i++) {
        for (int j = 0; is_stable && j < FIELD_WIDTH; j++) {
            if (state[i][j] != next_state[i][j]) is_stable = 0;
        }
    }

    return is_stable;
}

void print_start_game() {
    printf("\n\n\n");
    printf("Welcome to the...\n\n\n\n\n\n\n\n\n\n");
    printf("\t\t\t   GAME OF LIFE\n\n\n");
    printf("\n\n\n\n\n\n\n\n");

    printf("Enter the game speed(in seconds): \n");
}

void print_the_end() {
    printf("\n\n\n\n\n\n\n\n\n");
    printf("\tThe End!!!\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("\tThanks for playing <3...\n\n\n");
}