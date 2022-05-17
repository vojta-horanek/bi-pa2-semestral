#ifndef TPOHB_CONSTANTS_H
#define TPOHB_CONSTANTS_H

inline static const int REAL_PIXEL_SIZE =
    5; // A scaling constant indicating how real pixels are scaled across the
// screen
inline static const int BLOCK_SIZE =
    16; // The m_ScreenWidth and m_ScreenHeight of a single block, excluding the
        // player

inline static const int BLOCK_PIXELS = REAL_PIXEL_SIZE * BLOCK_SIZE;

inline static const int WINDOW_WIDTH = 11; // in blocks
inline static const int WINDOW_HEIGHT = 8; // in blocks

#endif // TPOHB_CONSTANTS_H
