// Definição das bibliotecas a serem usadas na execução do código
#include "pico/stdlib.h"   
#include "hardware/timer.h" 

// Definição das portas GPIO dos LEDs e do botão A
#define LED_PIN_GREEN 11
#define LED_PIN_BLUE 12
#define LED_PIN_RED 13
#define BUTTON_A 5

// Definição de variável que determina qual LED será apagado
static volatile int estado = 1;
// Definição de booleano que impedirá a criação de um alarme enquanto outro estiver ativo
static volatile bool alarme_atual = false;

// Função de callback que será chamada repetidamente pelo temporizador
// O tipo bool indica que a função deve retornar verdadeiro ou falso para continuar ou parar o temporizador.
int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    // O valor de estado determinad qual LED será apagado
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
    //A função chama a si mesma antes de retornar 0 e se encerrar
    add_alarm_in_ms(2000, turn_off_callback, NULL, false);
    return 0;
}


int main() {
    // Os LEDs são configurados como inicializados e configurados como saída
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN,GPIO_OUT);

    // O botão é inicialiado, configurado como saída e o pull-up interno é ativado
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    // Loop infinito que mantém o programa em execução.
    while (true) {
        // Se o botão for pressionado e naõ houver alarmes ativos, ocorre um debouncing simples
        if(gpio_get(BUTTON_A) == 0 && alarme_atual == false){
            // Tempo de debouncing
            sleep_ms(150);
            // Se o botão continuar pressionado, os LEDs são acesos
            if(gpio_get(BUTTON_A) == 0){
                gpio_put(LED_PIN_RED, true);
                gpio_put(LED_PIN_GREEN, true);
                gpio_put(LED_PIN_BLUE, true);
                // O booleano é colocado como true para evitar alarmes simultâneos
                alarme_atual = true;
                // A função de alarme é chamada
                add_alarm_in_ms(2000, turn_off_callback, NULL, false);
                
            }
        }
        sleep_ms(10);
    }
    return 0;
}
