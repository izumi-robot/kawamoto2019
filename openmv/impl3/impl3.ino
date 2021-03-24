#include <Wire.h>

class CamPos {
public:
    uint16_t x, y;
    CamPos(uint8_t x, uint8_t y) : x(x), y(y) {}
    uint8_t to_string(char *dst) {
        if (dst == NULL) return 0;
        return sprintf(dst, "(%u, %u)", x, y);
    }
};

bool operator==(const CamPos &lh, const CamPos &rh) {
    return lh.x == rh.x && lh.y == rh.y;
}

bool operator!=(const CamPos &lh, const CamPos &rh) {
    return lh.x != rh.x || lh.y != rh.y;
}

#define IOP_IMPL(_op_) CamPos& operator _op_ ## = (CamPos &lh, const CamPos &rh) {\
    lh.x _op_ ## = rh.x; lh.y _op_ ## = rh.y; return lh; }
IOP_IMPL(+)
IOP_IMPL(-)
IOP_IMPL(*)
IOP_IMPL(/)
#undef IOP_IMPL

#define OP_IMPL(_op_) CamPos operator _op_ (const CamPos &lh, const CamPos &rh) {\
    CamPos res = lh; res _op_ ## = rh; return res; }
OP_IMPL(+)
OP_IMPL(-)
OP_IMPL(*)
OP_IMPL(/)
#undef OP_IMPL

class Frame {
public:
    CamPos *ball_pos, *yellow_goal_pos, *blue_goal_pos;
    #define X(_name_) _name_ ## _x
    #define Y(_name_) _name_ ## _y
    #define PARAM(_name_) uint16_t X(_name_), uint16_t Y(_name_)
    #define NEW_POS(_name_) new CamPos(X(_name_), Y(_name_))
    Frame(PARAM(ball), PARAM(yellow_goal), PARAM(blue_goal))
    : ball_pos(NEW_POS(ball)), yellow_goal_pos(NEW_POS(yellow_goal)), blue_goal_pos(NEW_POS(blue_goal)) {}
    #undef X
    #undef Y
    #undef PARAM
    #undef NEW_POS
    Frame(CamPos *ball_pos, CamPos *yellow_goal_pos, CamPos *blue_goal_pos)
    : ball_pos(ball_pos), yellow_goal_pos(yellow_goal_pos), blue_goal_pos(blue_goal_pos) {}
    ~Frame() {
        #define DELETE(_name_) if (_name_ ## _pos != NULL) delete _name_ ## _pos;
        DELETE(ball)
        DELETE(yellow_goal)
        DELETE(blue_goal)
        #undef DELETE
    }
    uint8_t to_string(char *dst) {
        if (dst == NULL) return 0;
        char *ptr = dst;
        if (ball_pos != NULL){
            ptr += sprintf(ptr, "ball_pos: ");
            ptr += ball_pos->to_string(ptr);
            *(ptr++) = '\n';
        }
        if (yellow_goal_pos != NULL) {
            ptr += sprintf(ptr, "yellow_goal_pos: ");
            ptr += yellow_goal_pos->to_string(ptr);
            *(ptr++) = '\n';
        }
        if (blue_goal_pos != NULL) {
            ptr += sprintf(ptr, "blue_goal_pos: ");
            ptr += blue_goal_pos->to_string(ptr);
            *(ptr++) = '\n';
        }
        *ptr = '\0';
        return ptr - dst;
    }
};