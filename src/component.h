enum PinType {
    INPUT,
    OUTPUT,
    INOUT
};

struct Pin {
    char *name;
    enum PinType type;
    bool is_connected;
    int value;
    struct Port *port; // Pointer to the port this pin is connected to
};

struct Component {
    char *name;
    struct Pin pins[40];
};

struct Port {
    char *name;
    bool is_connected;
    int value;
    struct Pin *pins[10]; // Array of pointers to pins connected to this port
};

struct PortBoard {
    struct Port ports[100];
};

void connect_pin_to_board(struct Pin *pin, struct Port *port) {
    pin->is_connected = true;
    pin->port = port;

    for (int i = 0; i < 10; i++) {
        if (port->pins[i] == NULL) {
            port->pins[i] = pin;
            return;
        }
    }
}

void update(struct PortBoard *board) {
    for (int p = 0; p < 100; p++) {
        struct Port *port = &board->ports[p];
        if (!port->name) continue; // skip unused ports

        // Step 1: compute port value from outputs
        int port_value = 0;
        for (int i = 0; i < 10; i++) {
            struct Pin *pin = port->pins[i];
            if (pin && pin->type == OUTPUT && pin->value == 1) {
                port_value = 1;
                break;
            }
        }
        port->value = port_value;

        // Step 2: drive inputs with the port value
        for (int i = 0; i < 10; i++) {
            struct Pin *pin = port->pins[i];
            if (pin && pin->type == INPUT) {
                pin->value = port_value;
            }
        }
    }
}
