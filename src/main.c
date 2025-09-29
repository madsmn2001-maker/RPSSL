#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WINNING_SCORE 5

typedef enum {
    ROCK,      // 0
    LIZARD,    // 1
    SCISSORS,  // 2
    PAPER,     // 3
    SPOCK,     // 4
    NUM_SHAPES // 5
} Shape;

const char* SHAPE_NAMES[] = {
    "🪨", "🦎", "✂️", "🗒️", "🖖"
};

// Outcome matrix: 1 = player win, -1 = agent win, 0 = tie
const int OUTCOME_MATRIX[NUM_SHAPES][NUM_SHAPES] = {
    //      ROCK        LIZARD      SCISSORS      PAPER         SPOCK
    {  0,       1,       1,       -1,      -1 }, // ROCK
    { -1,       0,      -1,        1,       1 }, // LIZARD
    { -1,       1,       0,        1,      -1 }, // SCISSORS
    {  1,      -1,      -1,        0,       1 }, // PAPER
    {  1,      -1,       1,       -1,       0 }  // SPOCK
};

void print_shape_prompt() {
    printf("Select a shape:\n");
    for (int i = 0; i < NUM_SHAPES; i++) {
        printf("%d%s", i, SHAPE_NAMES[i]);
        if (i < NUM_SHAPES - 1)
            printf("  || ");
    }
    printf(" : ");
}

Shape get_valid_shape_input() {
    int choice;
    while (1) {
        print_shape_prompt();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); 
            printf("❌ Invalid input. Try again.\n\n");
            continue;
        }
        if (choice < 0 || choice >= NUM_SHAPES) {
            printf("❌ Shape key %d does not exist. Try again.\n\n", choice);
        } else {
            return (Shape)choice;
        }
    }
}

void play_game() {
    int player_score = 0;
    int agent_score = 0;

    srand((unsigned int)time(NULL));

    printf("Starting game 🎉\n\n");

    while (player_score < WINNING_SCORE && agent_score < WINNING_SCORE) {
        Shape player_choice = get_valid_shape_input();
        Shape agent_choice = (Shape)(rand() % NUM_SHAPES);

        printf("Agent: %s\n", SHAPE_NAMES[agent_choice]);


        int result = OUTCOME_MATRIX[player_choice][agent_choice];
        if (result == 1) {
            player_score++;
        } else if (result == -1) {
            agent_score++;
        }

        printf("👫:🤖  %d:%d\n\n", player_score, agent_score);
    }

    if (player_score == WINNING_SCORE) {
        printf("🎉 You won!\n");
    } else {
        printf("🤖 Agent won!\n");
    }
}

void show_menu() {
    char option;

    printf("Welcome to 🪨  ✂️  🗒️  🖖  🦎 !\n");
    printf("(s) Single player\n");
    printf("(e) Exit\n");

    while (1) {
        printf("Select an item: ");
        scanf(" %c", &option);

        if (option == 's') {
            play_game();
            break;
        } else if (option == 'e') {
            printf("Goodbye!\n");
            exit(0);
        } else {
            printf("❌ Invalid menu option. Try again.\n");
        }
    }
}

int main() {
    show_menu();
    return 0;
}
