#include <stdio.h>
#include <stdlib.h>

void print_game_screen(int height, int width, int left_rocket_position, int right_rocket_position, int ball_x,
                       int ball_y);

int update_rocket_position(int height, int current_position, char symbol, char up, char down);

void clear_screen();

int main() {
    int height = 25;  // 25
    int width = 80;   // 80
    int left_rocket_position = height / 2;
    int right_rocket_position = height / 2;
    int ball_x = 1;
    int ball_y = height / 2;
    int ball_dx = 1;
    int ball_dy = 1;
    int score_of_first_player = 0;
    int score_of_second_player = 0;
    char symbol;
    int ball_update_counter = 0;
    int ball_update_threshold = 1;
    printf("\nThe score of the first player: %d\n\n\n", score_of_first_player);
    printf("The score of the second player: %d\n\n\n", score_of_second_player);
    print_game_screen(height, width, left_rocket_position, right_rocket_position, ball_x, ball_y);
    while (score_of_first_player != 21 && score_of_second_player != 21) {
        if (score_of_first_player == 21) {
            printf("\nWin the first player\n");
            break;
        } else if (score_of_second_player == 21) {
            printf("\nWin the second player\n");
            break;
        }
        if (scanf("%c", &symbol) == 1) {
            if (symbol == 'a' || symbol == 'z') {
                left_rocket_position = update_rocket_position(height, left_rocket_position, symbol, 'a', 'z');
            } else if (symbol == 'k' || symbol == 'm') {
                right_rocket_position =
                    update_rocket_position(height, right_rocket_position, symbol, 'k', 'm');
            } else if (symbol == 'q') {
                break;
            }
        }
        if (ball_update_counter >= ball_update_threshold) {
            ball_x += ball_dx;
            ball_y += ball_dy;
            if (ball_y <= 1 || ball_y >= height - 2) {
                ball_dy = -ball_dy;
            }
            if (ball_x == 1 && (ball_y == left_rocket_position || ball_y == left_rocket_position + 1 ||
                                ball_y == left_rocket_position - 1)) {
                ball_dx = -ball_dx;
            }
            if (ball_x == width - 2 &&
                (ball_y == right_rocket_position || ball_y == right_rocket_position + 1 ||
                 ball_y == right_rocket_position - 1)) {
                ball_dx = -ball_dx;
            }
            if (ball_x <= 0) {
                score_of_second_player++;
                ball_x = 1;
                ball_y = height / 2;
                ball_dx = 1;
                ball_dy = 1;
            } else if (ball_x >= width - 1) {
                score_of_first_player++;
                ball_x = width - 2;
                ball_y = height / 2;
                ball_dx = -1;
                ball_dy = -1;
            }
            ball_update_counter = 0;
        } else {
            ball_update_counter++;
        }

        clear_screen();
        printf("\nThe score of the first player: %d\n\n\n", score_of_first_player);
        printf("\nThe score of the second player: %d\n\n\n", score_of_second_player);
        print_game_screen(height, width, left_rocket_position, right_rocket_position, ball_x, ball_y);
    }

    return 0;
}

void print_game_screen(int height, int width, int left_rocket_position, int right_rocket_position, int ball_x,
                       int ball_y) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1) {
                printf("*");
            } else if (((i == left_rocket_position || i == left_rocket_position + 1 ||
                         i == left_rocket_position - 1) &&
                        j == 0) ||
                       ((i == right_rocket_position || i == right_rocket_position + 1 ||
                         i == right_rocket_position - 1) &&
                        j == width - 1)) {
                printf("#");
            } else if (i == ball_y && j == ball_x) {
                printf("@");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int update_rocket_position(int height, int current_position, char symbol, char up, char down) {
    if (symbol == up && current_position > 2) {
        current_position--;
    } else if (symbol == down && current_position < height - 3) {
        current_position++;
    }
    return current_position;
}

void clear_screen() { system("clear"); }