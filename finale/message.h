#ifndef MESSAGE_H
#define MESSAGE_H

// Messages
#define MES_REQ_SIZE "Enter board size..."
#define MES_REQ_X "X<< "
#define MES_REQ_Y "Y<< "
#define MES_REQ_Z "Z<< "
#define MES_SIZE_ODD "Board size must be even number."
#define MES_UNPLACEABLE "That cell is not placeable."
#define MES_PASS "Pass..."
#define MES_ANNOUNCE "%s's turn\n"
#define MES_NEXT "Enter next move..."
#define MES_SCORE "%s%3u:%-3u%s\n"
#define MES_GAME_END "Game end."
#define MES_README "Move: 'A''S''D''F''H''J', Transition: 'G'"

// Debug messages
#define DEB_BASE "\x1b[33mAt \x1b[35m%15s\x1b[33m line \x1b[35m%3d\x1b[33m (From \x1b[35m%15s\x1b[33m line \x1b[35m%3d\x1b[33m): \x1b[39m"
#define DEB_BOARD "Board created.\n"
#define DEB_COUNTED "Counted empty cells.\n"
#define DEB_CALC_PLACEABLE "Calculated placeable cells.\n"
#define DEB_INDEXING "Indexing vector (%d, %d, %d): %4d\n"
#define DEB_ADDING "Adding vector (%d, %d, %d) and (%d, %d, %d): (%d, %d, %d)\n"
#define DEB_SET_PLACEABLE "Setting (%d, %d, %d) (i: %4d) if it's placeable.\n"
#define DEB_CHECK_PLACEABLE "Checking (%d, %d, %d) (i: %4d) if it's placeable or not.\n"
#define DEB_CHECK_BY_DIR "Looking direction (%2d, %2d, %2d)\n"
#define DEB_PLACEABLE "It's placeable with delta (%d, %d, %d).\n"
#define DEB_UNPLACEABLE "It isn't placeable.\n"

// For logging
#define DEBUG(called_line, ...) dladdr(__builtin_return_address(0), &info), printf(DEB_BASE, __func__, __LINE__, info.dli_sname, called_line), printf(__VA_ARGS__)

#endif