#include "pico/stdlib.h"   // Inclui a biblioteca padrão para funcionalidades básicas como GPIO, temporização e comunicação serial.
#include "hardware/timer.h" // Inclui a biblioteca para gerenciamento de temporizadores de hardware.

#define LED_PIN_GREEN 11
#define LED_PIN_BLUE 12
#define LED_PIN_RED 13
#define BUTTON_A 5

static volatile int estado = 1;
static volatile bool alarme_atual = false;

// Função de callback que será chamada repetidamente pelo temporizador
// O tipo bool indica que a função deve retornar verdadeiro ou falso para continuar ou parar o temporizador.
int64_t turn_off_callback(alarm_id_t id, void *user_data) {

    if(estado == 3){
        gpio_put(LED_PIN_BLUE, false);
        estado=1;
        alarme_atual = false;
        return 0; 
    } else if(estado == 2){
        gpio_put(LED_PIN_GREEN, false);
        estado++;
    } else if(estado == 1){
        gpio_put(LED_PIN_RED, false);
        estado++;
    } 

    add_alarm_in_ms(2000, turn_off_callback, NULL, false);
    return 0;
}


int main() {

    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN,GPIO_OUT);
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    // Loop infinito que mantém o programa em execução.
    while (true) {

        if(gpio_get(BUTTON_A) == 0 && alarme_atual == false){
            sleep_ms(150);
            if(gpio_get(BUTTON_A) == 0){
                gpio_put(LED_PIN_RED, true);
                gpio_put(LED_PIN_GREEN, true);
                gpio_put(LED_PIN_BLUE, true);
                alarme_atual = true;
                add_alarm_in_ms(2000, turn_off_callback, NULL, false);
                
            }
        }
        sleep_ms(10);
    }
    return 0;
}
