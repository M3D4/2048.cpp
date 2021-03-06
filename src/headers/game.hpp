#ifndef GAME_H
#define GAME_H

#include "gameboard.hpp"
#include "global.hpp"
#include <array>

enum Directions { UP, DOWN, RIGHT, LEFT };

class Game {
private:
  enum ContinueStatus { STATUS_END_GAME = 0, STATUS_CONTINUE = 1 };
  enum { COMPETITION_GAME_BOARD_PLAY_SIZE = 4 };

  enum GameStatusFlag {
    FLAG_WIN,
    FLAG_END_GAME,
    FLAG_SAVED_GAME,
    FLAG_INPUT_ERROR,
    FLAG_ENDLESS_MODE,
    FLAG_QUESTION_STAY_OR_QUIT,
    MAX_NO_GAME_STATUS_FLAGS
  };

  using gamestatus_t = std::array<bool, MAX_NO_GAME_STATUS_FLAGS>;

  gamestatus_t gamestatus{};

  enum IntendedMoveFlag {
    FLAG_MOVE_LEFT,
    FLAG_MOVE_RIGHT,
    FLAG_MOVE_UP,
    FLAG_MOVE_DOWN,
    MAX_NO_INTENDED_MOVE_FLAGS
  };

  using intendedmove_t = std::array<bool, MAX_NO_INTENDED_MOVE_FLAGS>;
  intendedmove_t intendedmove{};

  ull bestScore;
  double duration;
  GameBoard gamePlayBoard;
  RandInt randInt;
  bool noSave;

  bool get_and_process_game_stats_string_data(std::istream &stats_file);
  bool load_game_stats_from_file(std::string filename);
  bool initialiseContinueBoardArray();
  bool soloGameLoop();
  void drawEndScreen();
  void drawBoard() const;
  void drawGameState();
  void drawScoreBoard(std::ostream &out_stream) const;
  bool check_input_ansi(char c);
  bool check_input_wasd(char c);
  bool check_input_vim(char c);
  bool check_input_other(char c);
  void input();
  void decideMove(Directions);

  bool collaspeTiles(point2D_t pt, point2D_t pt_offset);
  bool shiftTiles(point2D_t pt, point2D_t pt_offset);
  bool collasped_or_shifted_tiles(point2D_t pt, point2D_t pt_offset);
  bool check_recursive_offset_in_game_bounds(point2D_t pt, point2D_t pt_offset);

  void move(point2D_t pt, point2D_t pt_offset);
  void statistics() const;
  void saveStats() const;
  void saveScore() const;
  void saveState() const;
  void playGame(ContinueStatus);
  ull setBoardSize();

  void drawEndOfGamePrompt();
  void drawGraphics();
  void endlessGameLoop();
  void process_gamelogic();
  bool process_intendedMove();
  bool process_gameStatus();
  void drawInputError();
  void drawInputControls();

public:
  Game() : bestScore(0), duration(0.0), noSave(false) {}
  void startGame();
  void continueGame();
};

#endif
