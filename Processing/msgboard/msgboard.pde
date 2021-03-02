String[] messages = {
    "message card", "message card", "message card",
    "message card", "message card", "message card",
    "message card", "message card", "message card",
    "message card", "message card", "message card",
    "message card", "message card", "message card",
    "message card", "message card", "message card",
};
float msg_size;
int msg_len = 18;

void setup() {
    size(720, 720);
    msg_size = width / (messages[0] + messages[1] + messages[2]).length;
    textAlign(LEFT, TOP);
    textSize(msg_size);
}

void draw() {
    background(255);
    for (int i = 0; i < msg_len; i++) {
        int row = i / 3, col = i % 3;
        text(messages[i], width / 3 * col, row * msg_size);
    }
}