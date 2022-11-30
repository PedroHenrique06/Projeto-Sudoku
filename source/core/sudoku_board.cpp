#include <algorithm>
#include "sudoku_board.h"

namespace sdkg {
    SBoard::SBoard()
    {
        // Empty board.
        std::fill( &board[0], &board[SB_SIZE*SB_SIZE], 0 );
    }

}
