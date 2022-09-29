#include <stdio.h>

typedef enum {
    start,
    button,
    led,
    cup,
    tea,
    coffee,
} state;

typedef enum {
    chip,
    select_drink,
    turn_led_on,
    cup_down,
    fill_cup,
    user_grabs_cup
} event;

state press_button() { return button; }
state turn_wait_led_on() { return led; }
state drop_cup() { return cup; }
state pour_tea() { return tea; }
state pour_coffee() { return coffee; }
state turn_green_led_on() { return led; }
state turn_led_off() { return start; }

void print_state(state s) {
    switch (s) {
        case start:
            printf("start -> ");
            break;
        case button:
            printf("button -> ");
            break;
        case led:
            printf("led -> ");
            break;
        case cup:
            printf("cup -> ");
            break;
        case tea:
            printf("tea -> ");
            break;
        case coffee:
            printf("coffee -> ");
            break;
        default:
            printf("ERRO\n");
            break;
    }
}

void transition(event e) {
    static state s = start;
    char user_input[2];

    while (1) {
        print_state(s);
        if (e == user_grabs_cup) e = chip;

        switch (s) {
            case start:
                if (e == chip) e = select_drink;
                s = press_button();
                break;
            case button:
                if (e == select_drink) e = turn_led_on;
                s = turn_wait_led_on();
                break;
            case led:
                if (e == turn_led_on) {
                    e = cup_down;
                    s = drop_cup();
                } else if (e == user_grabs_cup) {
                    e = chip;
                    s = turn_led_off();
                }
                break;
            case cup:
                if (e == cup_down) e = fill_cup;
                fgets(user_input, 2, stdin);
                if (user_input[0] == 'c') s = pour_coffee(); 
                else if (user_input[0] == 't') s = pour_tea(); 
                break;
            case tea:
                if (e == fill_cup) e = user_grabs_cup;
                s = turn_green_led_on();
                break;
            case coffee:
                if (e == fill_cup) e = user_grabs_cup;
                s = turn_green_led_on();
                break;
            default:
                printf("ERRO\n");
                break;
        }
    }
}

int main() {
    transition(start);

    return 0;
}