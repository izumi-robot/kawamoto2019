void line(Vector2D p1, Vector2D p2) {
    line(p1.x, p1.y, p2.x, p2.y);
}

void arrow(Vector2D start_p, Vector2D end_p) {
    Vector2D diff = start_p.sub(end_p);
    float arrow_ang = diff.angle(), head_mag = diff.mag() / 9;
    Vector2D arrowhead_r = from_polar_coord(arrow_ang + PI / 3, head_mag);
    Vector2D arrowhead_l = from_polar_coord(arrow_ang + PI * 2 / 3, head_mag);
    arrowhead_r.iadd(end_p);
    arrowhead_l.iadd(end_p);

    line(start_p, end_p);
    line(end_p, arrowhead_r);
    line(end_p, arrowhead_l);
}