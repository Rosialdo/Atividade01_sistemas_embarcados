#include <stdio.h>

typedef enum {
    start,
    button,
    red_led,
    cup,
    tea,
    coffee,
    green_led
} state;

typedef enum {
    chip,
    select_drink,
    turn_red_led_on,
    cup_down,
    fill_cup,
    user_grabs_cup,
    turn_green_led_on
} event;

state press_button() { return button; }
state turn_wait_led_on() { return red_led; }
state drop_cup() { return cup; }
state pour_tea() { return tea; }
state pour_coffee() { return coffee; }
state turn_ready_led_on() { return green_led; }
state turn_led_off() { return start; }

void print_state(state s) {
    switch (s) {
        case start:
            printf("start -> ");
            break;
        case button:
            printf("button -> ");
            break;
        case red_led:
            printf("red_led -> ");
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
        case green_led:
            printf("green_led -> ");
            break;
        default:
            printf("ERRO\n");
            break;
    }
}

void transition(event e) {
    static state s = start;
    char user_input;

    while (1) {
        print_state(s);
        if (e == turn_green_led_on) e = chip;

        switch (s) {
            case start:
                if (e == chip) e = select_drink;
                s = press_button();
                break;
            case button:
                if (e == select_drink) e = turn_red_led_on;
                s = turn_wait_led_on();
                break;
            case red_led:
                if (e == turn_red_led_on) e = cup_down;
                s = drop_cup();
                break;
            case cup:
                if (e == cup_down) e = fill_cup;
                scanf(" %c", &user_input);
                if (user_input == 'c') s = pour_coffee(); 
                else if (user_input == 't') s = pour_tea(); 
                break;
            case tea:
                if (e == fill_cup) e = user_grabs_cup;
                s = turn_ready_led_on();
                break;
            case coffee:
                if (e == fill_cup) e = user_grabs_cup;
                s = turn_ready_led_on();
                break;
            case green_led:
                if (e == user_grabs_cup) e = turn_green_led_on;
                s = turn_led_off();
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