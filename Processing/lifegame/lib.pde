public class LifeGame {
    public int cell_size, row_num, col_num;
    public color alive_color, dead_color;
    public boolean[][] cells, new_cells;

    boolean randBool() {
        int i = round(random(10));
        return (i % 2 == 1);
    }

    public LifeGame(int cell_size, color alive_color, color dead_color) {
        this.cell_size = cell_size;
        this.alive_color = alive_color;
        this.dead_color = dead_color;
    }

    public LifeGame(int cell_size, color alive_color) {
        this(cell_size, alive_color, #000000);
    }

    public LifeGame(int cell_size) {
        this(cell_size, #17FF50, #000000);
    }

    public LifeGame() {
        this(20, #17FF50, #000000);
    }

    public void setup() {
        this.row_num = round(height / this.cell_size);
        this.col_num = round(width / this.cell_size);
        this.cells = new boolean[this.row_num][this.col_num];
        this.new_cells = new boolean[this.row_num][this.col_num];
        for (int r=0; r<this.row_num; r++) {
            for(int c=0; c<this.col_num; c++) {
                this.cells[r][c] = this.randBool();
                this.new_cells[r][c] = false;
            }
        }
    }

    public void draw() {
        background(this.dead_color);
        fill(this.alive_color);
        for(int r=0; r<this.row_num; r++) {
            for(int c=0; c<this.col_num; c++) {
                if(this.cells[r][c]) {
                    rect(c * this.cell_size, r * this.cell_size, this.cell_size, this.cell_size);
                }
                int alive_count = this.aliveCount(r, c);
                if(alive_count == 3) {
                    this.new_cells[r][c] = true;
                } else if(alive_count == 2) {
                    this.new_cells[r][c] = this.cells[r][c];
                } else {
                    this.new_cells[r][c] = false;
                }
            }
        }
        for(int r=0; r<this.row_num; r++) {
            for(int c=0; c<this.col_num; c++) {
                this.cells[r][c] = this.new_cells[r][c];
            }
        }
        if((frameCount % 60) == 0) {
            println(frameRate);
        }
    }

    private boolean getCell(int row, int col) {
        boolean cell;
        try {
            cell = this.cells[row][col];
        } catch(Exception e) {
            cell = false;
        }
        return cell;
    }

    private int aliveCount(int r, int c) {
        int order[][] = {
            {r - 1, c - 1}, {r - 1, c}, {r - 1, c + 1},
            {r, c - 1}, {r, c + 1},
            {r + 1, c - 1}, {r + 1, c}, {r + 1, c + 1}
        }, count = 0;
        for(int[] l : order) {
            count += this.getCell(l[0], l[1])?1:0;
        }
        return count;
    }
}