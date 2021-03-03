String[] messages = {
    "□□□■□□□□□□■□□□□□□", "□□■□□□□■■■■■■■□□□", "□□□□□□□■□□□□□□□□□", "□□□□□■□□□□■□□□□□□",
    "□□□■□□□□□□■□□□□□□", "□□■□□□□■□□□□□■□□□", "□□□■□□□■□□□□□□□□□", "■■■■■■□□□□■■■■■■□",
    "□□■■■■■■□■■■■■■■□", "□□■□□□□■■■■■■■□□□", "□□□■□□□■□□□□□□□□□", "□□□□□■□□□□■□□□□□□",
    "□■□□■□□□□■□■□□□□□", "□□■□□□□■□□□□□■□□□", "□□□■■■■■■■■■■■□□□", "□■■■■■□□□□■■■■■□□",
    "■□□□□■□□■□□□■□□□□", "■■■■■□□■□□□□□■□□□", "□□■■□□□■□□□□□□□□□", "□□□□□■□□□□■□□□□□□",
    "□□□□□■□■□□□□■□□□□", "□□■□□□□■■■■■■■□□□", "□■■□□□□■□□□□□□□□□", "■■■■■■□□□□■■■■■■□",
    "□□□□□□□■□□□□□□□□□", "□□■□□□□□□□□□□□□□□", "□□□□□□□■□□□□□□□□□", "□□□□■□□□□□■□□□□□□",
    "□■■■■■■■■■■■■■■□□", "□□■□□■■■■■■■■■■■□", "■■■■■■■■■■■■■■■■□", "□□□■□□□■□□□□□□□□□",
    "□□□□□□□□□□□□□□□□□", "□□■□□□□■□□□□□□□□□", "□□□□□■□□□■□□□□□□□", "■■■■■■■■■■■■■■■■□",
    "□□□■□□□□□□□□■□□□□", "□□■□□□□■■■■■■■■■□", "□□□□□■□□□■□□□□□□□", "□□■□□□□■□□□□□■□□□",
    "□□□■■□□□□□□■■□□□□", "□□■■■□■□□■□□■□□■□", "□□□□□■□□□■□□□□□□□", "□□■■■■■■■■■■■■□□□",
    "□□□□■□□□□□□■□□□□□", "□■■□□■□□■■□■■□□■□", "□□□□■■□□□■□□□□□□□", "□□■□□□□■□□□□□■□□□",
    "□□□□■□□□□□■■□□□□□", "■■□□□□□■■□□■□□□■□", "□□□□■□□□□■□□□□□□□", "□□■■■■■■■■■■■■□□□",
    "□□□□□□□□□□■□□□□□□", "□□□□□□■■□□■■□□■■□", "□□□■■□□□□■□□□□□■□", "□□□□□□□■□□□□□□□□□",
    "■■■■■■■■■■■■■■■■□", "□□□□□□□□□■■□□□■□□", "□□■■□□□□□■■□□□■■□", "■■■■■■■■■■■■■■■■□",
    "□□□□□□□□□□□□□□□□□", "□□□□□□□□□□□□■■■□□", "■■■□□□□□□□■■■■■□□", "□□□□□□□■□□□□□□□□□",
};

int msg_size, row_len = 16, col_len = 4;

void setup () {
    size(360, 360); msg_size = 6; textAlign(LEFT, TOP); textSize(msg_size); fill(0);
}

void draw() {
    background(255); noLoop();
    for (int r = 0; r < row_len; r++) for (int c = 0; c < col_len; c++)
    text(messages[r * col_len + c], width / col_len * c, r * msg_size);
}


/*
□□□■□□□□■□□□■□□□□ □□□□□□□□□□□□□□□□□ □□□□□□□■□□□□□□□□□ □□□□□■□□□□■□□□□□□
□□□■□□□□■□□□■□□□□ □■■■■■■■■■■■■■■□□ □□□■□□□■□□□□□□□□□ ■■■■■■□□□□■■■■■■□
□□□■□□□□■□□□■■□□□ □■□□□□□■□□□□□□■□□ □□□■□□□■□□□□□□□□□ □□□□□■□□□□■□□□□□□
■■■■■■□■■□□□□■□□□ □■□□□□□■□□□□□□■□□ □□□■■■■■■■■■■■□□□ □■■■■■□□□□■■■■■□□
□□□■□□□■□□□□□■■□□ □■□□□□□■□□□□□□■□□ □□■■□□□■□□□□□□□□□ □□□□□■□□□□■□□□□□□
□□□■□□□■□□□□□□■□□ □■□□□□□■□□□□□□■□□ □■■□□□□■□□□□□□□□□ ■■■■■■□□□□■■■■■■□
□□■■□□■■□■□□□□■■□ □■□□□□□■□□□□□□■□□ □□□□□□□■□□□□□□□□□ □□□□■□□□□□■□□□□□□
□□■■■□□□□■□□□□□□□ □■■■■■■■■■■■■■■□□ ■■■■■■■■■■■■■■■■□ □□□■□□□■□□□□□□□□□
□□■■□■□□□■□□□□□□□ □■□□□□□■□□□□□□■□□ □□□□□■□□□■□□□□□□□ ■■■■■■■■■■■■■■■■□
□■□■□■□□□■□□□□□□□ □■□□□□□■□□□□□□■□□ □□□□□■□□□■□□□□□□□ □□■□□□□■□□□□□■□□□
□■□■□□□□■■□□□■□□□ □■□□□□□■□□□□□□■□□ □□□□□■□□□■□□□□□□□ □□■■■■■■■■■■■■□□□
■□□■□□□□■□□□□■□□□ □■□□□□□■□□□□□□■□□ □□□□■■□□□■□□□□□□□ □□■□□□□■□□□□□■□□□
□□□■□□□□■□□□□■□□□ □■□□□□□■□□□□□□■□□ □□□□■□□□□■□□□□□□□ □□■■■■■■■■■■■■□□□
□□□■□□□□■□□■■■■□□ □■□□□□□■□□□□□□■□□ □□□■■□□□□■□□□□□■□ □□□□□□□■□□□□□□□□□
□□□■□□□□■■■■□□■□□ □■■■■■■■■■■■■■■□□ □□■■□□□□□■■□□□■■□ ■■■■■■■■■■■■■■■■□
□□□■□□■■■□□□□□■■□ □□□□□□□□□□□□□□□□□ ■■■□□□□□□□■■■■■□□ □□□□□□□■□□□□□□□□□

□□□■□□□□□□■□□□□□□ □□■□□□□■■■■■■■□□□ □□□□□□□■□□□□□□□□□ □□□□□■□□□□■□□□□□□
□□□■□□□□□□■□□□□□□ □□■□□□□■□□□□□■□□□ □□□■□□□■□□□□□□□□□ ■■■■■■□□□□■■■■■■□
□□■■■■■■□■■■■■■■□ □□■□□□□■■■■■■■□□□ □□□■□□□■□□□□□□□□□ □□□□□■□□□□■□□□□□□
□■□□■□□□□■□■□□□□□ □□■□□□□■□□□□□■□□□ □□□■■■■■■■■■■■□□□ □■■■■■□□□□■■■■■□□
■□□□□■□□■□□□■□□□□ ■■■■■□□■□□□□□■□□□ □□■■□□□■□□□□□□□□□ □□□□□■□□□□■□□□□□□
□□□□□■□■□□□□■□□□□ □□■□□□□■■■■■■■□□□ □■■□□□□■□□□□□□□□□ ■■■■■■□□□□■■■■■■□
□□□□□□□■□□□□□□□□□ □□■□□□□□□□□□□□□□□ □□□□□□□■□□□□□□□□□ □□□□■□□□□□■□□□□□□
□■■■■■■■■■■■■■■□□ □□■□□■■■■■■■■■■■□ ■■■■■■■■■■■■■■■■□ □□□■□□□■□□□□□□□□□
□□□□□□□□□□□□□□□□□ □□■□□□□■□□□□□□□□□ □□□□□■□□□■□□□□□□□ ■■■■■■■■■■■■■■■■□
□□□■□□□□□□□□■□□□□ □□■□□□□■■■■■■■■■□ □□□□□■□□□■□□□□□□□ □□■□□□□■□□□□□■□□□
□□□■■□□□□□□■■□□□□ □□■■■□■□□■□□■□□■□ □□□□□■□□□■□□□□□□□ □□■■■■■■■■■■■■□□□
□□□□■□□□□□□■□□□□□ □■■□□■□□■■□■■□□■□ □□□□■■□□□■□□□□□□□ □□■□□□□■□□□□□■□□□
□□□□■□□□□□■■□□□□□ ■■□□□□□■■□□■□□□■□ □□□□■□□□□■□□□□□□□ □□■■■■■■■■■■■■□□□
□□□□□□□□□□■□□□□□□ □□□□□□■■□□■■□□■■□ □□□■■□□□□■□□□□□■□ □□□□□□□■□□□□□□□□□
■■■■■■■■■■■■■■■■□ □□□□□□□□□■■□□□■□□ □□■■□□□□□■■□□□■■□ ■■■■■■■■■■■■■■■■□
□□□□□□□□□□□□□□□□□ □□□□□□□□□□□□■■■□□ ■■■□□□□□□□■■■■■□□ □□□□□□□■□□□□□□□□□
*/