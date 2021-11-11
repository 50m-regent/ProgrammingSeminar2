#include "reversi.h"
#include "message.h"

static inline const Vector vector_sum(const Vector v1, const Vector v2, const unsigned int called_line) {
    if (debug > 2) DEBUG(called_line, DEB_ADDING, v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
    return (Vector){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

static inline const int vec2i(const Vector v, const unsigned int called_line) {
    int i;

    if (
        (v.x < 0) || (v.y < 0) || (v.z < 0) ||
        (v.x >= board_size.x) || (v.y >= board_size.y) || (v.z >= board_size.z)
    ) i = -1;
    else i = board_size.x * (board_size.y * v.z + v.y) + v.x;

    if (debug > 2) DEBUG(called_line, DEB_INDEXING, v.x, v.y, v.z, i);
    return i;
}

void board_init(const unsigned int called_line) {
    board = (unsigned char *)malloc(sizeof (unsigned char) * board_size.x * board_size.y * board_size.z);
    memset(board, 0, sizeof (unsigned char) * board_size.x * board_size.y * board_size.z);

    board[vec2i((Vector){board_size.x / 2    , board_size.y / 2,     board_size.z / 2    }, __LINE__)] = 1;
    board[vec2i((Vector){board_size.x / 2    , board_size.y / 2,     board_size.z / 2 - 1}, __LINE__)] = 2;
    board[vec2i((Vector){board_size.x / 2    , board_size.y / 2 - 1, board_size.z / 2    }, __LINE__)] = 2;
    board[vec2i((Vector){board_size.x / 2    , board_size.y / 2 - 1, board_size.z / 2 - 1}, __LINE__)] = 1;
    board[vec2i((Vector){board_size.x / 2 - 1, board_size.y / 2,     board_size.z / 2    }, __LINE__)] = 2;
    board[vec2i((Vector){board_size.x / 2 - 1, board_size.y / 2,     board_size.z / 2 - 1}, __LINE__)] = 1;
    board[vec2i((Vector){board_size.x / 2 - 1, board_size.y / 2 - 1, board_size.z / 2    }, __LINE__)] = 1;
    board[vec2i((Vector){board_size.x / 2 - 1, board_size.y / 2 - 1, board_size.z / 2 - 1}, __LINE__)] = 2;

    if (debug > 1) DEBUG(called_line, DEB_BOARD);
}

const unsigned count_empty(const unsigned int called_line) {
    unsigned count = 0;
    for (unsigned i = 0; i < board_size.x * board_size.y * board_size.z; i++) if (!board[i]) count++;

    if (debug > 1) DEBUG(called_line, DEB_COUNTED);
    return count;
}

const unsigned char is_placeable(const Vector cell, const unsigned int called_line) {
    if (debug > 1) DEBUG(called_line, DEB_CHECK_PLACEABLE, cell.x, cell.y, cell.z, vec2i(cell, __LINE__));
    for (unsigned char i = 0; i < 27; i++) {
        const Vector delta = DELTAS[i];

        if (vec2i(vector_sum(vector_sum(cell, delta, __LINE__), delta, __LINE__), __LINE__) < 0) continue;

        if (debug > 2) DEBUG(called_line, DEB_CHECK_BY_DIR, delta.x, delta.y, delta.z);

        if (
            !board[vec2i(cell, __LINE__)] &&
            (board[vec2i(vector_sum(cell, delta, __LINE__), __LINE__)] == turn % 2 + 1) &&
            search(vector_sum(vector_sum(cell, delta, __LINE__), delta, __LINE__), delta, 0)
        ) {
            board[vec2i(cell, __LINE__)] = 3;

            if (debug > 1) DEBUG(called_line, DEB_PLACEABLE, delta.x, delta.y, delta.z);
            return 1;
        }
    }

    if (debug > 1) DEBUG(called_line, DEB_UNPLACEABLE);
    return 0;
}

const unsigned set_placeable(const unsigned int called_line) {
    unsigned count = 0;
    for (unsigned short x = 0; x < board_size.x; x++) {
        for (unsigned short y = 0; y < board_size.y; y++) {
            for (unsigned short z = 0; z < board_size.z; z++) {
                const Vector v = (Vector){x, y, z};
                if (debug > 1) DEBUG(called_line, DEB_SET_PLACEABLE, x, y, z, vec2i(v, __LINE__));

                if (board[vec2i(v, __LINE__)] == 3) board[vec2i(v, __LINE__)] = 0;
                if (is_placeable(v, __LINE__)) count++;
            }
        }
    }

    if (debug > 1) DEBUG(called_line, DEB_CALC_PLACEABLE);
    return count;
}

void out() {
    for (short x = 0; x < board_size.x; x++) {
        printf("X: %d\n Z", x);
        for (short z = 0; z < board_size.z; z++) printf(" %d", z);
        puts("\nY");

        for (short y = 0; y < board_size.y; y++) {
            printf("%d ", y);
            for (short z = 0; z < board_size.z; z++) {
                printf(" \x1b[42m%s", icons[board[vec2i((Vector){x, y, z}, __LINE__)]]);
            }
            puts("\x1b[49m");
        }
        puts("");
    }

    unsigned score[4] = {};
    for (unsigned i = 0; i < board_size.x * board_size.y * board_size.z; i++) score[board[i]]++;
    printf(MES_SCORE, icons[BLACK], score[BLACK], score[WHITE], icons[WHITE]);
}

void get_board_size() {
    unsigned short x, y, z;

    do {
        printf(MES_REQ_X); scanf("%hd", &x);

        if (x & 1) puts(MES_SIZE_ODD);
    } while(x & 1);
    
    do {
        printf(MES_REQ_Y); scanf("%hd", &y);

        if (y & 1) puts(MES_SIZE_ODD);
    } while(y & 1);

    do {
        printf(MES_REQ_Z); scanf("%hd", &z);

        if (z & 1) puts(MES_SIZE_ODD);
    } while(z & 1);

    board_size = (Vector){x, y, z};
}

const unsigned char search(const Vector now, const Vector delta, const unsigned char flip) {
    if (
        (vec2i(now, __LINE__) < 0) ||
        !board[vec2i(now, __LINE__)]
    ) return 0;
    if (board[vec2i(now, __LINE__)] == turn) return 1;
    if (flip) board[vec2i(now, __LINE__)] = turn;

    return search(vector_sum(now, delta, __LINE__), delta, flip);
}

const Vector get_move() {
    unsigned short x, y, z;
    Vector v;

    puts(MES_NEXT);

    do {
        printf(MES_REQ_X); scanf("%hd", &x);
        printf(MES_REQ_Y); scanf("%hd", &y);
        printf(MES_REQ_Z); scanf("%hd", &z);

        v = (Vector){x, y, z};
        if (
            (vec2i(v, __LINE__) < 0) ||
            (board[vec2i(v, __LINE__)] != 3)
        ) {
            puts(MES_UNPLACEABLE);
        }
    } while (
        (vec2i(v, __LINE__) < 0) ||
        (board[vec2i(v, __LINE__)] != 3)
    );

    return v;
}

void flip(const Vector move) {
    board[vec2i(move, __LINE__)] = turn;
    for (unsigned char i = 0; i < 27; i++) {
        const Vector delta = DELTAS[i];
        if (
            board[vec2i(vector_sum(move, delta, __LINE__), __LINE__)] == turn % 2 + 1 &&
            search(vector_sum(vector_sum(move, delta, __LINE__), delta, __LINE__), delta, 0)
        ) search(vector_sum(move, delta, __LINE__), delta, 1);
    }
}


void play(const unsigned int called_line) {
    while (count_empty(__LINE__)) {
        if (!set_placeable(__LINE__)) {
            puts(MES_PASS);
            continue;
        }

        if (debug > 0) {
            printf(MES_ANNOUNCE, icons[turn]);
            out();
        }
        
        flip(get_move());
        
        turn %= 2;
        turn++;
    }
}