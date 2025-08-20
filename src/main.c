#include <stdio.h>
#include "component.h"

#define DEBUG(a) \
    printf(_Generic((a), \
        char *: "[%s] @ [%s:%d]: %s\n", \
        const char *: "[%s] @ [%s:%d]: %s\n", \
        int   : "[%s] @ [%s:%d]: %d\n" \
    ), __func__, __FILE__, __LINE__, (a))


int main() {
    struct Component led = {
        .name = "LED",
        .pins = {
            [0] = {
                .name = "Input",
                .type = INPUT,
            },
        }
    };

    struct Component battery = {
        .name = "Battery",
        .pins = {
            [0] = {
                .name = "Output",
                .type = OUTPUT,
                .value = 1,
            },
        }
    };

    struct PortBoard port_board = {
        .ports = {
            [0] = {
                .name = "Port 1",
                .value = 0,
            },
        }
    };

    DEBUG(led.pins[0].is_connected ? "LED connected" : "LED not connected");
    DEBUG(led.pins[0].value ? "LED On" : "LED Off");

    DEBUG(battery.pins[0].is_connected ? "Battery connected" : "Battery not connected");
    DEBUG(battery.pins[0].value ? "Battery On\n" : "Battery Off\n");

    connect_pin_to_board(&led.pins[0], &port_board.ports[0]);
    connect_pin_to_board(&battery.pins[0], &port_board.ports[0]);

    DEBUG(led.pins[0].is_connected ? "LED connected" : "LED not connected");
    DEBUG(led.pins[0].value ? "LED On" : "LED Off");

    DEBUG(battery.pins[0].is_connected ? "Battery connected" : "Battery not connected");
    DEBUG(battery.pins[0].value ? "Battery On\n" : "Battery Off\n");

    DEBUG("Updating port board");

    update(&port_board);

    DEBUG(led.pins[0].value ? "LED On" : "LED Off");

    return 0;
}
